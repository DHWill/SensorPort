/**
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */



#include "platform.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistdio.h>

//#include <linux/i2c-dev.h>
//#include <i2c/smbus.h>

extern "C" {
	#include <linux/i2c.h>
    #include <linux/i2c-dev.h>
    #include <i2c/smbus.h>
}

/* File access modes for `open' and `fcntl'.  */
/*for Pretty IDE https://github.com/lattera/glibc/blob/master/bits/fcntl.h*/
#define	O_RDONLY	0	/* Open read-only.  */
#define	O_WRONLY	1	/* Open write-only.  */
#define	O_RDWR		2	/* Open read/write.  */

//   i2c_smbus_write_quick(int file, __u8 value);
//  __s32 i2c_smbus_read_byte(int file);
//  __s32 i2c_smbus_write_byte(int file, __u8 value);
//  __s32 i2c_smbus_read_byte_data(int file, __u8 command);
//  __s32 i2c_smbus_write_byte_data(int file, __u8 command, __u8 value);
//  __s32 i2c_smbus_read_word_data(int file, __u8 command);
//  __s32 i2c_smbus_write_word_data(int file, __u8 command, __u16 value);
//  __s32 i2c_smbus_process_call(int file, __u8 command, __u16 value);
//  __s32 i2c_smbus_read_block_data(int file, __u8 command, __u8 *values);
//  __s32 i2c_smbus_write_block_data(int file, __u8 command, __u8 length,
//                                   __u8 *values);
//      * Using I2C Write, equivalent of
//      * i2c_smbus_write_word_data(file, reg, 0x6543)
//      */
//    char buf[10];
//     buf[0] = RegisterAdress;
//     buf[1] = 0x00;
//     buf[2] = 0x00;
//
////    char high= (p_value>>8) & 0xff;
////    char low= p_value & 0xff;
//
//    /* Using I2C Read, equivalent of i2c_smbus_read_byte(file) */
////    if (read(m_busFD, buf, 1) != 1) {
////    	return status;
////      /* ERROR HANDLING: i2c transaction failed */
////    } else {
////      /* buf[0] contains the read byte */
////    	&p_value = buf[0];
////    }
//    i2c_smbus_read_byte_data(m_busFD,RegisterAdress);



//int addr = 0x29;

uint8_t RdByte(VL53L5CX_Platform *p_platform,uint16_t RegisterAdress,uint8_t *p_value){
	/* Need to be implemented by customer. This function returns 0 if OK
	 * Setup the i2c port for WR on i2c Address 0x52	 */
	uint8_t status = 255;
//	int addr = 0x52; /* The I2C address */

	int m_busFD = open("/dev/i2c-4", O_RDWR);
    if(m_busFD < 0){
    	std::cout << "could not open ioctl: /dev/i2c-4 O_RDWR" << std::endl;
        return status;
    }
    if (ioctl(m_busFD, I2C_SLAVE, p_platform->address) < 0){
    	std::cout << "could not open ioctl: /dev/i2c-4 O_RDWR" << std::endl;
    	return status;
    }

    int byte = i2c_smbus_read_byte_data(m_busFD, RegisterAdress);
    std::cout << byte << std::endl;
    *p_value = byte;

    close(m_busFD);
    status = 0;
	return status;
}

uint8_t WrByte(VL53L5CX_Platform *p_platform,uint16_t RegisterAdress,uint8_t value){
	/* Need to be implemented by customer. This function returns 0 if OK */

	uint8_t status = 255;
//	int addr = 0x52; /* The I2C address */

	int m_busFD = open("/dev/i2c-4", O_RDWR);
	if(m_busFD < 0){
		std::cout << "could not open ioctl: /dev/i2c-4 O_RDWR" << std::endl;
		return status;
	}
	if (ioctl(m_busFD, I2C_SLAVE, p_platform->address) < 0){
		std::cout << "could not open ioctl: /dev/i2c-4 O_RDWR" << std::endl;
		return status;
	}
	 i2c_smbus_write_byte_data(m_busFD, RegisterAdress, value);
	 close(m_busFD);

    status = 0;
	return status;
}

uint8_t WrMulti(VL53L5CX_Platform *p_platform,uint16_t RegisterAdress,uint8_t *p_values,uint32_t size){
	uint8_t status = 255;
	
		/* Need to be implemented by customer. This function returns 0 if OK */

	return status;
}

uint8_t RdMulti(VL53L5CX_Platform *p_platform,uint16_t RegisterAdress,uint8_t *p_values,uint32_t size){
	uint8_t status = 255;
	
	/* Need to be implemented by customer. This function returns 0 if OK */
	
	return status;
}

uint8_t Reset_Sensor(VL53L5CX_Platform *p_platform){
	uint8_t status = 0;
	
	/* (Optional) Need to be implemented by customer. This function returns 0 if OK */
	
	/* Set pin LPN to LOW */
	/* Set pin AVDD to LOW */
	/* Set pin VDDIO  to LOW */
	WaitMs(p_platform, 100);

	/* Set pin LPN of to HIGH */
	/* Set pin AVDD of to HIGH */
	/* Set pin VDDIO of  to HIGH */
	WaitMs(p_platform, 100);

	return status;
}

void SwapBuffer(uint8_t *buffer, uint16_t size){
	uint32_t i, tmp;
	
	/* Example of possible implementation using <string.h> */
	for(i = 0; i < size; i = i + 4) 
	{
		tmp = (
		  buffer[i]<<24)
		|(buffer[i+1]<<16)
		|(buffer[i+2]<<8)
		|(buffer[i+3]);
		
		memcpy(&(buffer[i]), &tmp, 4);
	}
}	

uint8_t WaitMs(VL53L5CX_Platform *p_platform, uint32_t TimeMs){

	uint8_t status = 255;


	/* Need to be implemented by customer. This function returns 0 if OK */
	usleep(TimeMs * 1000);
	
	return status;
}
