#include "i2c_driver.hh"

namespace steveO{


	i2c::i2c(const char* device): dev(device){};
	
	int i2c::init(){
		if((fd = open(dev, O_RDWR))<0){ perror("Failed to open the i2c bus"); return -1; }
		else { printf("Device Opened Successfully\n\n"); return fd; }
	}
	
	
	int i2c::readByte(uint8_t dev_add, uint8_t reg_add){

		if(ioctl(fd,I2C_SLAVE,dev_add)<0){
			perror("failed to add icm20948\n");
			return -1;
		}	
		uint8_t request[1];
		request[0]=reg_add;
		if(write(fd,request,1)!=1){
			perror("failed to request data\n");
		}
		uint8_t response[1];
		if(read(fd,response,1)!=1){
			perror("failed to read data\n");
			return -1;
		}
		return response[0];
	}


	int i2c::readBytes(uint8_t dev_add, uint8_t reg_add, uint8_t num_bytes, uint8_t * buf){

		if(ioctl(fd,I2C_SLAVE,dev_add)<0){
		perror("failed to add icm20948\n");
		return -1;
		}
			
		uint8_t request[1];
		request[0]=reg_add;
		if(write(fd,request,1)!=1){
			perror("write multiple bytes failed:\n");
			return -1;
		}
	
		uint8_t response[num_bytes];
		if(read(fd,response,num_bytes)<0){
			perror("error reasing multiple bytes:");
			return -1;
		}
		
		for(int i=0; i<num_bytes; i++){
			//printf("multiple bytes read = %X\n\n", response[i]);	
			buf[i]=response[i];
		}
		return 0;	

	}
	
	
}


//int main(void){ return 0;}
