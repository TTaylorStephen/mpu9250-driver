#ifndef IMU_INTERFACE_HH
#define IMU_INTERFACE_HH

#include <chrono>

#include "i2c_interface.hh"
#include "register_map.hh"
#include "constant.hh"
#include "types.hh"


#define GRAVITY 9.80665
#define PI 3.14159265359


namespace steveO{
	
	class imu : public i2c 
	{
		
		public:
			imu(const char* device);
			~imu();
			double setRefs();
			int mpuGetBias();
			int readGyro();
			int readAccel();
			int whoAmI();
			
			gyroStream gyro;
			accelStream accel;
			double gyro_offset;

		private:
			imu(const imu& dev);
			imu& operator=(const imu& dev);	
	};

}


#endif
