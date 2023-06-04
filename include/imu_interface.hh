#ifndef IMU_INTERFACE_HH
#define IMU_INTERFACE_HH

#include <chrono>
#include "i2c_interface.hh"
#include "register_map.hh"
#include "constant.hh"
#include "types.hh"

namespace steveO{
	
	class imu : public i2c 
	{
		
		public:
			imu(const char* device);
			double getScales();
			int mpuGetBias();
			int readGyro();
			int readAccel();
			int whoAmI();
			gyroStream gyro;
			accelStream accel;
			magStream mag;

		private:
			imu(const imu& dev);
			imu& operator=(const imu& dev);	
	};

}


#endif
