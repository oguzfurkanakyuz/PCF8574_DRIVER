
#ifndef INC_PCF8574_H_
#define INC_PCF8574_H_

#include "stdio.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"

extern I2C_HandleTypeDef hi2c1;		// Configure according to your I2C_HandleTypeDef structure address.


/*
 * PCF8574 module address configuration:  	0 1 0 0 (A2) (A1) (A0) (R/W)
 *  				write configuration:	0 1 0 0  1    1    1    0 = 0x4E
 *  				read  configuration:	0 1 0 0  1    1    1    1 = 0x4F
 */
#define DEVICE_ADDRESS_WRITE	(uint16_t)0x4E	// Configure according to your slave address selection.
#define DEVICE_ADDRESS_READ 	(uint16_t)0x4F	// Configure according to your slave address selection.

#define MAX_PIN_NUMBER (uint8_t)0x07

/**
  * @brief  PCF8574 bit set and bit reset enumeration
  */
typedef enum
{
	EXPANDER_PIN_RESET = 0x0U,
	EXPANDER_PIN_SET   = (!EXPANDER_PIN_RESET)

}Expander_PinState_t;

/*
 * 	@def_group Expander_Output_Pins
 */
#define P0_OUT	( (uint8_t) 0X01 )
#define P1_OUT	( (uint8_t) 0X02 )
#define P2_OUT	( (uint8_t) 0X04 )
#define P3_OUT	( (uint8_t) 0X08 )
#define P4_OUT	( (uint8_t) 0X10 )
#define P5_OUT	( (uint8_t) 0X20 )
#define P6_OUT	( (uint8_t) 0X40 )
#define P7_OUT	( (uint8_t) 0X80 )

void Expander_Write_Pin(uint8_t PinNumber,Expander_PinState_t Expander_State);
void Expander_Toggle_Pin(uint8_t PinNumber);
Expander_PinState_t Expander_Read_Pin(uint8_t PinNumber);
uint8_t Expander_Read_Data();

#endif /* INC_PCF8574_H_ */
