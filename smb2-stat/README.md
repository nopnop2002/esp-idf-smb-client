# smb2-stat   
Obtain file information in a shared directory

# Installation

```
git clone https://github.com/nopnop2002/esp-idf-smb-client
cd esp-idf-smb-client
git clone https://github.com/sahlberg/libsmb2 components/libsmb2
cp esp-idf/CMakeLists.txt components/libsmb2/
cd smb2-stat
idf.py set-target {esp32/esp32s2/esp32s3/esp32c3}
idf.py menuconfig
idf.py flash
```

# How to use   
Create [esp-idf-stat] in the shared folder.   
It can be either a directory or a file.   

# Screen Shot   
esp-idf-stat is normal file:   
![smb2-stat-1](https://user-images.githubusercontent.com/6020549/119463428-b7ab8e00-bd7c-11eb-93aa-dbb3c9ca0bb8.jpg)

esp-idf-stat is directory:   
![smb2-stat-2](https://user-images.githubusercontent.com/6020549/119463434-b8442480-bd7c-11eb-8abd-a9a44a5cbfa0.jpg)

