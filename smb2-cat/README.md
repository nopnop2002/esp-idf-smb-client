# smb2-cat   
Read from a file in a shared directory

# Installation
```
git clone https://github.com/nopnop2002/esp-idf-smb-client
cd esp-idf-smb-client
git clone https://github.com/sahlberg/libsmb2 components/libsmb2
cd smb2-cat
idf.py set-target {esp32/esp32s2/esp32s3/esp32c3}
idf.py menuconfig
idf.py flash
```

# How to use   
Create esp-idf-cat.txt in the shared folder.   
The content does not matter.   
It's mine.   
```
11111111111111111
aaaaaaaaaaaaaaaaa
22222222222222222
bbbbbbbbbbbbbbbbb
```
Build and run the farmware.

# Screen Shot   
![smb2-cat](https://user-images.githubusercontent.com/6020549/119466565-b3cd3b00-bd7f-11eb-98fb-58220dcd494d.jpg)
