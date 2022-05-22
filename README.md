# esp-idf-smb-client
SMB client example for esp-idf.   
"SMB (Server Message Block)" is a standard file sharing protocol in Windows networks.   
You can access Windows shared folder from esp32.   
This project use [SMB2/3 userspace client](https://github.com/sahlberg/libsmb2).

# Software requirements
esp-idf v4.4 or later.   
This is because this version supports ESP32-C3.   

# Installation
```
git clone https://github.com/nopnop2002/esp-idf-smb-client
cd esp-idf-smb-client
git clone https://github.com/sahlberg/libsmb2 components/libsmb2
cd smb2-ls
idf.py set-target {esp32/esp32s2/esp32s3/esp32c3}
idf.py menuconfig
idf.py flash
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
IP address or mDNS of shared host.   
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
