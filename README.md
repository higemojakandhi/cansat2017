# cansat2017
CanSat Project by Wolve'Z at Keio University

# Author
Kandai Watanabe, Daisuke Kobayashi, Kota Mori, Naoto Yoshida, Koyanagi, Ono

# Main Authors
 - Kandai Watanabe
 - Yoshihara

# How it looks
![image](https://user-images.githubusercontent.com/11141442/37876280-fd132724-3084-11e8-819d-f48af3b8c678.png)

 
# Hardware
## Boards
 - Arduino
 
## Sensors
### Nine Axis (9DOF: Accelerometer, Gyrometer, Magnetometer) 
MPU9250
sources used:
https://github.com/kriswiner/MPU9250
https://github.com/sparkfun/SparkFun_MPU-9250-DMP_Arduino_Library

### Motor
I guess I used Daisen Geared Motor 100:1 (RA250100-58Y91)
https://www.vstone.co.jp/robotshop/index.php?main_page=product_info&cPath=72_194_197&products_id=603

### Motor Driver
Rohm H Full Bridge Driver BD6211
http://www.rohm.co.jp/web/japan/products/-/product/BD6211F

### Light
Do not remember, really cheap one

### GPS
GMS7-CR6(SIRF-IV) 
http://akizukidenshi.com/download/ds/canmore/GMS7-CR6_v1.0_ak.pdf

### Data Logger
OpenLog
https://www.switch-science.com/catalog/2716/

### Wireless 
XBee


# Overview
## cansat2017.ino 
 * init
 * loop 

## cansat.cpp
 * sequences

## nineaxis.cpp
 * IMU data
 * Attitude Estimation


