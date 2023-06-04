#ifndef TYPES_HH
#define TYPES_HH


namespace steveO{
	
	struct angularVel{
		double deg;
		double rad;
	};
	
	struct gyroStream{
		
		angularVel wx, wy, wz;
		double x_offset, y_offset, z_offset;
	}; gyroStream gyro;
	
	struct accelStream{
		double x, y, z;
		double x_offset, y_offset, z_offset;
	}; accelStream accel;
	
}


#endif
