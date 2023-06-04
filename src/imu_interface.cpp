#include "imu_interface.hh"

namespace steveO{


	imu::imu(const char* device): i2c(device) {
		int file = init_i2c_device();
		getScales();
		mpuGetBias();
 		printf("Device Open with File Descriptor %d: Success\n\n", file);
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
			double time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(current_time-start_time).count()/1000.0;			
			if(time_elapsed<=5.0){
				readGyro(), readAccel();
				gx_total += gyro.wx.deg, gy_total += gyro.wy.deg, gz_total += gyro.wz.deg;
				ax_total += accel.x, ay_total += accel.y, az_total += accel.z;
			} else{
				gyro.x_offset=gx_total/count, gyro.y_offset=gy_total/count, gyro.z_offset=gz_total/count;
				accel.x_offset=ax_total/count, accel.y_offset=ay_total/count, accel.z_offset=(az_total/count)-1;				
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

		gyro.wx.deg=(data[0]*GYRO_RESOLUTION)-gyro.x_offset;
		gyro.wy.deg=(data[1]*GYRO_RESOLUTION)-gyro.y_offset;
		gyro.wz.deg=(data[2]*GYRO_RESOLUTION)-gyro.z_offset;

		gyro.wx.rad=gyro.wx.deg*(PI/180);
		gyro.wy.rad=gyro.wy.deg*(PI/180);
		gyro.wz.rad=gyro.wz.deg*(PI/180);

		printf("Gyroscope Data in Degrees: %f, %f, %f\n\n", gyro.wx.deg, gyro.wy.deg, gyro.wz.deg);
		printf("Gyroscope Data in Radians: %f, %f, %f\n\n", gyro.wx.rad, gyro.wy.rad, gyro.wz.rad);

	}
	
	
	int imu::readAccel(){
		uint8_t buff[6]={0};
		int data[3]={0};
		
		readBytes(IMU_ADD, ACCEL_XOUT_H, 6, &buff[0]);
		data[0]=(((int16_t)buff[0] << 8) | buff[1]);
		data[1]=(((int16_t)buff[2] << 8) | buff[3]);
		data[2]=(((int16_t)buff[4] << 8) | buff[5]);
	
		accel.x=(data[0]*ACCEL_RESOLUTION)-accel.x_offset;
		accel.y=(data[1]*ACCEL_RESOLUTION)-accel.y_offset;
		accel.z=(data[2]*ACCEL_RESOLUTION)-accel.z_offset;
		printf("Accelerometer Data: %f, %f, %f\n\n", accel.x, accel.y, accel.z);
	}
		

	double imu::getScales(){
		accel.resolution._2G     = FSR_2G/FSR_16BIT; 
		accel.resolution._4G     = FSR_4G/FSR_16BIT; 
		accel.resolution._8G     = FSR_8G/FSR_16BIT; 
		accel.resolution._16G    = FSR_16G/FSR_16BIT; 
		gyro.resolution._250DPS  = FSR_250DPS/FSR_16BIT;
		gyro.resolution._500DPS  = FSR_500DPS/FSR_16BIT;
		gyro.resolution._1000DPS = FSR_1000DPS/FSR_16BIT;
		gyro.resolution._2000DPS = FSR_2000DPS/FSR_16BIT;
		mag.resolution._14BIT    = FSR_MAG/FSR_14BIT;
		mag.resolution._16BIT    = FSR_MAG/FSR_16BIT;
	}	
	
}


int main(void){
	char dev[] = "/dev/i2c-1";	
	steveO::imu mpu9250(dev);
	
	while(true){
		//mpu9250.whoAmI();
		mpu9250.readGyro();
		mpu9250.readAccel();
	}
	
	return 0;
}




