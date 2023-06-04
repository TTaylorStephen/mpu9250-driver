#ifndef CONSTANT_HH
#define CONSTANT_HH

#include "types.hh"
#include <cmath>

#define GRAVITY 9.80665
#define PI 3.14159265359

#define SENSITIVITY 131
#define FSR_14BIT pow(2,14)
#define FSR_16BIT pow(2,16)
#define FSR_2G 2.0
#define FSR_4G 2.0
#define FSR_8G 2.0
#define FSR_16G 2.0
#define FSR_250DPS 250.0
#define FSR_500DPS 500.0
#define FSR_1000DPS 1000.0
#define FSR_2000DPS 2000.0
#define FSR_MAG 4912.0/1000.0 // microguass -> milliguass

#define ACCEL_RESOLUTION accel.resolution._2G
#define GYRO_RESOLUTION gyro.resolution._250DPS
#define MAG_RESOLUTION mag.resolution._14BIT

#endif