# esp-idf-smb-client
SMB client example for esp-idf.   
"SMB (Server Message Block)" is a standard file sharing protocol in Windows networks.   
You can access Windows shared folder from esp32.   
This project use [SMB2/3 userspace client](https://github.com/sahlberg/libsmb2).

# Software requirements
ESP-IDF V5.0 or later.   
ESP-IDF V4.4 release branch reached EOL in July 2024.   

# Installation
```
git clone https://github.com/nopnop2002/esp-idf-smb-client
cd esp-idf-smb-client
git clone https://github.com/sahlberg/libsmb2 components/libsmb2
cp esp-idf/CMakeLists.txt components/libsmb2/
cd smb2-ls
idf.py set-target {esp32/esp32s2/esp32s3/esp32c2/esp32c3/esp32c6}
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
Password with shared folder permissions.
- CONFIG_SMB_HOST   
IP address or mDNS host name of shared host.   
- CONFIG_SMB_PATH   
Shared path name.

![config-main](https://user-images.githubusercontent.com/6020549/119461488-b5e0cb00-bd7a-11eb-8e7a-12e9a2859787.jpg)
![config-app-1](https://user-images.githubusercontent.com/6020549/169681869-234719cf-d043-467f-a339-abf0c2ac7eb6.jpg)

When a password is required to access the shared folder.   

![config-app-2](https://user-images.githubusercontent.com/6020549/169681877-ce4da211-bc92-4546-995c-cc16bb65ba51.jpg)

Specify the SMB Host in one of the following formats.   
- IP address like 192.168.10.120   
- mDNS hostname like smbhost.local   

![config-app3](https://user-images.githubusercontent.com/6020549/220567598-abde2ecd-32fb-4d39-a53f-9a9b23f22078.jpg)

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


# smbclient
You can check the services provided by the host using smbclient.   
```
$ smbclient -L LANDISK-HDL-AA1.local -U admin
Enter WORKGROUP\admin's password:

        Sharename       Type      Comment
        ---------       ----      -------
        LAN DISK Log    Disk      HDL-AA Share for Log files
        disk1           Disk      HDL-AA RAID share
        IPC$            IPC       IPC Service (HDL-AA series)
SMB1 disabled -- no workgroup available
```
