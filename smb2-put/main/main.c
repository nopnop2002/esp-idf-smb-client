/* SMB Client Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sys.h"

#include "smb2.h"
#include "libsmb2.h"
#include "libsmb2-raw.h"

#define MAXBUF 64
uint8_t buf[MAXBUF];
uint32_t pos;

/* FreeRTOS event group to signal when we are connected*/
static EventGroupHandle_t s_wifi_event_group;

/* The event group allows multiple bits for each event, but we only care about two events:
 * - we are connected to the AP with an IP
 * - we failed to connect after the maximum amount of retries */
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT BIT1

static const char *TAG = "main";

static int s_retry_num = 0;

static void event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data)
{
	if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
		esp_wifi_connect();
	} else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
		if (s_retry_num < CONFIG_ESP_MAXIMUM_RETRY) {
			esp_wifi_connect();
			s_retry_num++;
			ESP_LOGI(TAG, "retry to connect to the AP");
		} else {
			xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
		}
		ESP_LOGI(TAG,"connect to the AP fail");
	} else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
		ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
		ESP_LOGI(TAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
		s_retry_num = 0;
		xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
	}
}

void wifi_init_sta(void)
{
	s_wifi_event_group = xEventGroupCreate();

	ESP_ERROR_CHECK(esp_netif_init());

	ESP_ERROR_CHECK(esp_event_loop_create_default());
	esp_netif_create_default_wifi_sta();

	wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK(esp_wifi_init(&cfg));

	esp_event_handler_instance_t instance_any_id;
	esp_event_handler_instance_t instance_got_ip;
	ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
		ESP_EVENT_ANY_ID,
		&event_handler,
		NULL,
		&instance_any_id));
	ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
		IP_EVENT_STA_GOT_IP,
		&event_handler,
		NULL,
		&instance_got_ip));

	wifi_config_t wifi_config = {
		.sta = {
			.ssid = CONFIG_ESP_WIFI_SSID,
			.password = CONFIG_ESP_WIFI_PASSWORD,
			/* Setting a password implies station will connect to all security modes including WEP/WPA.
			 * However these modes are deprecated and not advisable to be used. Incase your Access point
			 * doesn't support WPA2, these mode can be enabled by commenting below line */
			.threshold.authmode = WIFI_AUTH_WPA2_PSK,

			.pmf_cfg = {
				.capable = true,
				.required = false
			},
		},
	};
	ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA) );
	ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config) );
	ESP_ERROR_CHECK(esp_wifi_start() );

	ESP_LOGI(TAG, "wifi_init_sta finished.");

	/* Waiting until either the connection is established (WIFI_CONNECTED_BIT) or connection failed for the maximum
	 * number of re-tries (WIFI_FAIL_BIT). The bits are set by event_handler() (see above) */
	EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
		WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
		pdFALSE,
		pdFALSE,
		portMAX_DELAY);

	/* xEventGroupWaitBits() returns the bits before the call returned, hence we can test which event actually
	 * happened. */
	if (bits & WIFI_CONNECTED_BIT) {
		ESP_LOGI(TAG, "connected to ap SSID:%s", CONFIG_ESP_WIFI_SSID);
	} else if (bits & WIFI_FAIL_BIT) {
		ESP_LOGI(TAG, "Failed to connect to SSID:%s, password:%s", CONFIG_ESP_WIFI_SSID, CONFIG_ESP_WIFI_PASSWORD);
	} else {
		ESP_LOGE(TAG, "UNEXPECTED EVENT");
	}

	/* The event will not be processed after unregister */
	ESP_ERROR_CHECK(esp_event_handler_instance_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, instance_got_ip));
	ESP_ERROR_CHECK(esp_event_handler_instance_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID, instance_any_id));
	vEventGroupDelete(s_wifi_event_group);
}

void app_main(void)
{
	//Initialize NVS
	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);

	ESP_LOGI(TAG, "ESP_WIFI_MODE_STA");
	wifi_init_sta();

	struct smb2_context *smb2;
	struct smb2_url *url;
	struct smb2fh *fh;

	smb2 = smb2_init_context();
	if (smb2 == NULL) {
		ESP_LOGE(TAG, "Failed to init context");
		while(1){ vTaskDelay(1); }
	}

	ESP_LOGI(TAG, "CONFIG_SMB_USER=[%s]",CONFIG_SMB_USER);
	ESP_LOGI(TAG, "CONFIG_SMB_HOST=[%s]",CONFIG_SMB_HOST);
	ESP_LOGI(TAG, "CONFIG_SMB_PATH=[%s]",CONFIG_SMB_PATH);
	char smburl[64];
	//strcpy(smburl, "smb://nop@192.168.10.50/share/esp-idf-put.txt");
	sprintf(smburl, "smb://%s@%s/%s/esp-idf-put.txt", CONFIG_SMB_USER, CONFIG_SMB_HOST, CONFIG_SMB_PATH);
	ESP_LOGI(TAG, "smburl=%s", smburl);

#if CONFIG_SMB_NEED_PASSWORD
	smb2_set_password(smb2, CONFIG_SMB_PASSWORD);
#endif

	url = smb2_parse_url(smb2, smburl);
	if (url == NULL) {
		ESP_LOGE(TAG, "Failed to parse url: %s", smb2_get_error(smb2));
		while(1){ vTaskDelay(1); }
	}

	smb2_set_security_mode(smb2, SMB2_NEGOTIATE_SIGNING_ENABLED);

	if (smb2_connect_share(smb2, url->server, url->share, url->user) < 0) {
		ESP_LOGE(TAG, "smb2_connect_share failed. %s", smb2_get_error(smb2));
		while(1){ vTaskDelay(1); }
	}


	ESP_LOGI(TAG, "url->path=%s", url->path);
	fh = smb2_open(smb2, url->path, O_WRONLY|O_CREAT);
	if (fh == NULL) {
		ESP_LOGE(TAG, "smb2_open failed. %s", smb2_get_error(smb2));
		while(1){ vTaskDelay(1); }
	}

	for (int line=0;line<10;line++) {
		sprintf((char *)buf, "This is Text# %d\n", line);
		smb2_write(smb2, fh, buf, strlen((char *)buf));
	}
				
	smb2_close(smb2, fh);
	smb2_disconnect_share(smb2);
	smb2_destroy_url(url);
	smb2_destroy_context(smb2);
}
