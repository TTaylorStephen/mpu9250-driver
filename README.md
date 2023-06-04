#### MPU9250/AK8932 Driver 

- WIP/Laying out initial framework
- Current functionality includes: reading/calibrating gyroscope + accelerometer data


To build:
```
    cd ~/ && git clone git@github.com:TTaylorStephen/mpu9250Driver.git
    cd mpu9250Driver
    mkdir build
    cd build
    cmake .. && make
```