# smb2-mkdir   
Create directory in a shared directory

# Installation for ESP32

```
git clone https://github.com/nopnop2002/esp-idf-smb-client
cd esp-idf-smb-client/smb2-mkdir
git clone https://github.com/sahlberg/libsmb2 components/libsmb2
idf.py set-target esp32
idf.py menuconfig
idf.py flash
```

# Installation for ESP32-S2

```
git clone https://github.com/nopnop2002/esp-idf-smb-client
cd esp-idf-smb-client/smb2-mkdir
git clone https://github.com/sahlberg/libsmb2 components/libsmb2
idf.py set-target esp32s2
idf.py menuconfig
idf.py flash
```

# How to use
Build and run the farmware.   
It will create smb2-mkdir directory in a shared folder.   

