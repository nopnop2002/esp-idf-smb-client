# smb2-put   
Write to a file in a shared directory

# Installation

```
git clone https://github.com/nopnop2002/esp-idf-smb-client
cd esp-idf-smb-client
git clone https://github.com/sahlberg/libsmb2 -b libsmb2-6.2 components/libsmb2
cp esp-idf/CMakeLists.txt components/libsmb2/
cd smb2-put
idf.py set-target {esp32/esp32s2/esp32s3/esp32c3}
idf.py menuconfig
idf.py flash
```


# How to use
Build and run the farmware.   
It will create esp-idf-put.txt in a shared folder.   
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

