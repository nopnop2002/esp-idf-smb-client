# esp-idf-smb-client
SMB client example for esp-idf.   
"SMB (Server Message Block)" is a standard file sharing protocol in Windows networks.   
You can access Windows shared folder from esp32.   
This project use [SMB2/3 userspace client](https://github.com/sahlberg/libsmb2).

# Software requirements
esp-idf v4.3 or later.   


# Installation for ESP32
```
git clone https://github.com/nopnop2002/esp-idf-smb-client
cd esp-idf-smb-client/smb2-ls
git clone https://github.com/sahlberg/libsmb2 components/libsmb2
idf.py set-target esp32
idf.py menuconfig
idf.py flash
```

# Installation for ESP32-S2
```
git clone https://github.com/nopnop2002/esp-idf-smb-client
cd esp-idf-smb-client/smb2-ls
git clone https://github.com/sahlberg/libsmb2 components/libsmb2
idf.py set-target esp32s2
idf.py menuconfig
idf.py flash
```

# Installation for esp-idf v4.4 or later.   
The following function names have changed in esp-idf v4.4:   
MD5Init --> esp_rom_md5_init   
MD5Update --> esp_rom_md5_update   
MD5Final --> esp_rom_md5_final   

Therefore, it is necessary to add the following to the end of components/libsmb2/include/esp/config.h.   
```
#define MD5Init esp_rom_md5_init
#define MD5Update esp_rom_md5_update
#define MD5Final esp_rom_md5_final
```

# Configuration   
You have to set this config value with menuconfig.   
- CONFIG_ESP_WIFI_SSID   
SSID (network name) to connect to.
- CONFIG_ESP_WIFI_PASSWORD   
WiFi password (WPA or WPA2) to use.
- CONFIG_ESP_MAXIMUM_RETRY   
Set the Maximum retry to avoid station reconnecting to the AP unlimited when the AP is really inexistent.
- CONFIG_SMB_USER   
Username with shared folder permissions.
- CONFIG_SMB_NEED_PASSWORD   
Shared access requires password.
- CONFIG_SMB_PASSWORD   
Password of Username.
- CONFIG_SMB_HOST   
IP address of shared host.   
__mDMS name cannot be used.__   
- CONFIG_SMB_PATH   
Shared path name.

![config-main](https://user-images.githubusercontent.com/6020549/119461488-b5e0cb00-bd7a-11eb-8e7a-12e9a2859787.jpg)
![config-app](https://user-images.githubusercontent.com/6020549/119461477-b37e7100-bd7a-11eb-9167-7f7e1f65dd2d.jpg)

When a password is required to access the shared folder.
![config-password](https://user-images.githubusercontent.com/6020549/119465484-ab283500-bd7e-11eb-8b3f-2c8ecf9443bb.jpg)


# Examples
- smb2-ls   
 Shared directory file list

- smb2-cat   
 Read from a file in a shared directory

- smb2-put   
 Write to a file in a shared directory

- smb2-stat   
 Obtain file information in a shared directory

- smb2-mkdir   
 Create directory in a shared directory
