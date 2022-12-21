/* 
 * File:   i2c.h
 * Author: ENG-Ahmed Maged
 *
 * Created on August 10, 2022, 1:14 PM
 */

#ifndef I2C_H
#define	I2C_H

#include <xc.h>
#include <avr/interrupt.h>
#include "gpio.h"

#define I2C_PORT            		GPIOC

#define I2C_SCL_PIN			GPIO_PIN0
#define I2C_SDA_PIN			GPIO_PIN1

#define I2C_BUFFER_SIZE 8
#ifndef F_CPU 
#define F_CPU 16000000UL
#endif

typedef enum {
	I2C_FREQ_100K = 100000UL,
	I2C_FREQ_250K = 250000UL,
	I2C_FREQ_400K = 400000UL
} I2C_Freq_Mode_t;

typedef enum {
    I2C_PULLUP_ON,
    I2C_PULLUP_OFF
}I2C_PullUp;

void I2C_Init(I2C_Freq_Mode_t freq_mode, I2C_PullUp i2c_pullup);
uint8_t I2C_Transceiver_Busy(void);
uint8_t I2C_Get_State_Info(void);
uint8_t I2C_Get_Receive_Flag(void);
void I2C_Start_Transceiver_With_Data(unsigned char*, uint8_t);
void I2C_Start_Transceiver(void);
unsigned char I2C_Get_Data_From_Transceiver(unsigned char*, uint8_t);


#define I2C_READ_BIT                0
#define I2C_ADR_BITS                1
#define TRUE                        1
#define FALSE                       0                   
#define I2C_START                  0x08
#define I2C_REP_START              0x10
#define I2C_ARB_LOST               0x38                    
#define I2C_MTX_ADR_ACK            0x18 
#define I2C_MTX_ADR_NACK           0x20
#define I2C_MTX_DATA_ACK           0x28
#define I2C_MTX_DATA_NACK          0x30
#define I2C_MRX_ADR_ACK            0x40
#define I2C_MRX_ADR_NACK           0x48
#define I2C_MRX_DATA_ACK           0x50
#define I2C_MRX_DATA_NACK          0x58
#define I2C_NO_STATE               0xF8
#define I2C_BUS_ERROR              0x00

#endif	/* I2C_H */

