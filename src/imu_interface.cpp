#include "imu_interface.hh"

namespace steveO{


	imu::imu(const char* device): i2c(device) {
		init();
 		printf("Device ON\n\n");

	}


	int imu::whoAmI(){
		uint8_t address=readByte(IMU_ADD, IMU_WHO_AM_I);
		printf("MPU9250 address = %X\n\n", address);
		return address;
	}
	
	
	int imu::mpuGetBias(){
	
		double gx_total=0, gy_total=0, gz_total=0;
		double ax_total=0, ay_total=0, az_total=0;
		double count=0;
		auto start_time = std::chrono::high_resolution_clock::now();
		
		while(true){
			auto current_time = std::chrono::high_resolution_clock::now();
			double dt = std::chrono::duration_cast<std::chrono::milliseconds>(current_time-start_time).count()/1000.0;
			//printf("%f\n\n", dt);
			
			if(dt<=5.0){
				readGyro(), readAccel();
				gx_total += gyro.wx.deg, gy_total += gyro.wy.deg, gz_total += gyro.wz.deg;
				ax_total += accel.x, ay_total += accel.y, az_total += accel.z;
			} else{
				gyro.x_offset=gx_total/count, gyro.y_offset=gy_total/count, gyro.z_offset=gz_total/count;
				accel.x_offset=ax_total/count, accel.y_offset=ay_total/count, accel.z_offset=az_total/count;				
				printf("Average Gyroscope Values: %f, %f, %f\n\n", gyro.x_offset, gyro.y_offset, gyro.z_offset);
				printf("Average Accelerometer Values: %f, %f, %f\n\n", accel.x_offset, accel.y_offset, accel.z_offset);
				sleep(1);
				break;
			}
			count+=1;
		}
	}
	
	

	int imu::readGyro(){
		uint8_t buff[6]={0};
		int data[3]={0};
		
		readBytes(IMU_ADD, GYRO_XOUT_H, 6, &buff[0]);
		data[0]=(((int16_t)buff[0] << 8) | buff[1]);
		data[1]=(((int16_t)buff[2] << 8) | buff[3]);
		data[2]=(((int16_t)buff[4] << 8) | buff[5]);
		
		gyro.wx.deg=((float)data[0]/GYRO_SENSITIVITY)-gyro.x_offset;
		gyro.wy.deg=((float)data[1]/GYRO_SENSITIVITY)-gyro.y_offset;
		gyro.wz.deg=((float)data[2]/GYRO_SENSITIVITY)-gyro.z_offset;
	
		printf("Gyroscope Data: %f, %f, %f\n\n", gyro.wx.deg, gyro.wx.deg, gyro.wx.deg);
	}
	
	
	int imu::readAccel(){
		uint8_t buff[6]={0};
		int data[3]={0};
		
		readBytes(IMU_ADD, ACCEL_XOUT_H, 6, &buff[0]);
		data[0]=(((int16_t)buff[0] << 8) | buff[1]);
		data[1]=(((int16_t)buff[2] << 8) | buff[3]);
		data[2]=(((int16_t)buff[4] << 8) | buff[5]);
		
		accel.x=(data[0]*GRAVITY/16384)-accel.x_offset;
		accel.y=(data[1]*GRAVITY/16384)-accel.y_offset;
		accel.z=(data[2]*GRAVITY/16384)-accel.z_offset;
	
		printf("Accelerometer Data: %f, %f, %f\n\n", accel.x, accel.y, accel.z);
	}
		
	imu::~imu(){ close(fd); }
	
}


int main(void){
	char dev[] = "/dev/i2c-1";	
	steveO::imu mpu9250(dev);
	
	mpu9250.mpuGetBias();
	while(true){
		//mpu9250.whoAmI();
		//sleep(1);
		//mpu9250.readGyro();
		mpu9250.readAccel();
	}
	
	return 0;
}




