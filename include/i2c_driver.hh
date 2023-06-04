#ifndef I2C_DRIVER_HH
#define I2C_DRIVER_HH

#include <iostream>
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

namespace steveO{

	class i2c{

		public:
			i2c(const char* device);
			int init();
			int readByte(uint8_t dev_add, uint8_t reg_add);
			int readBytes(uint8_t dev_add, uint8_t reg_add, uint8_t num_bytes, uint8_t * buf);
			
		protected:
			const char* dev;
			int fd;
			
			i2c(const i2c& dev);
			i2c& operator=(const i2c& dev);	
		
	};

}

#endif
