# smb2-mkdir   
Create directory in a shared directory

# Installation

```
git clone https://github.com/nopnop2002/esp-idf-smb-client
cd esp-idf-smb-client
git clone https://github.com/sahlberg/libsmb2 components/libsmb2
cp esp-idf/CMakeLists.txt components/libsmb2/
cd smb2-mkdir
idf.py set-target {esp32/esp32s2/esp32s3/esp32c3}
idf.py menuconfig
idf.py flash
```

# How to use
Build and run the farmware.   
It will create smb2-mkdir directory in a shared folder.   

