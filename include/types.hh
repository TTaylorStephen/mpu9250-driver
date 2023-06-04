#ifndef TYPES_HH
#define TYPES_HH


namespace steveO{
	

	struct gyroStream{
		struct res{
			double _250DPS, _500DPS, _1000DPS, _2000DPS;
		}; res resolution;

		struct angularVel{
			double deg, rad; 
		}; angularVel wx, wy, wz;
		
		double x_offset, y_offset, z_offset;
	}; 
	
	struct accelStream{
		struct res{
			double _2G, _4G, _8G, _16G;
		}; res resolution;

		double x, y, z;
		double x_offset, y_offset, z_offset;

	}; 

	struct magStream{
		struct res{
			double _14BIT, _16BIT;
		}; res resolution;

	}; 
	
}


#endif
