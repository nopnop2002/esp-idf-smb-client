# smb2-put   
Write to a file in a shared directory

# Installation for ESP32

```
git clone https://github.com/nopnop2002/esp-idf-smb-client
cd esp-idf-smb-client/smb2-put
git clone https://github.com/sahlberg/libsmb2 components/libsmb2
idf.py set-target esp32
idf.py menuconfig
idf.py flash
```

# Installation for ESP32-S2

```
git clone https://github.com/nopnop2002/esp-idf-smb-client
cd esp-idf-smb-client/smb2-put
git clone https://github.com/sahlberg/libsmb2 components/libsmb2
idf.py set-target esp32s2
idf.py menuconfig
idf.py flash
```

# How to use
Build and run the farmware.   
Create esp-idf-put.txt in a shared folder.   
```
This is Text# 0
This is Text# 1
This is Text# 2
This is Text# 3
This is Text# 4
This is Text# 5
This is Text# 6
This is Text# 7
This is Text# 8
This is Text# 9
```

