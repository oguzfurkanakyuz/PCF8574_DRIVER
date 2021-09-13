
#include "PCF8574.h"


/**
  * @brief  Expander_Write_Pin() sets or resets the desired outputs.
  *
  * @param  PinNumber specifies the output pins of PCF8574, @def_group Expander_Output_Pins.
  *
  * @param  Expander_State specifies the desired situation for selected pins.
  * 		This parameter can be one of the Expander_PinState_t enum values:
  *            @arg EXPANDER_PIN_RESET: to clear the port pin.
  *            @arg EXPANDER_PIN_SET  : to set the port pin.
  *
  * @return None
  */

void Expander_Write_Pin(uint8_t PinNumber,Expander_PinState_t Expander_State)
{
	uint8_t pData_read = 0x00U;
	uint8_t pData_write = 0x00U;

	/* if{} state specifies the situation of SET operation */
	if(Expander_State == EXPANDER_PIN_SET)
	{
		/* Read existing output value of PCF8574 */
		HAL_I2C_Master_Receive(&hi2c1, DEVICE_ADDRESS_READ, &pData_read, 1, 100);

		pData_write = pData_read | PinNumber;
		HAL_I2C_Master_Transmit(&hi2c1, DEVICE_ADDRESS_WRITE, &pData_write, 1, 100);
	}

	/* else{} state specifies the situation of RESET operation */
	else
	{
		uint8_t fake_position = 0x00U;
		uint8_t last_position = 0x00U;

		/* Find the desired reset pins by comparing bit by bit */
		for(uint8_t position = 0x00U; position <= MAX_PIN_NUMBER; position++)
		{
			fake_position = (0x1U << position);
			last_position = (PinNumber & fake_position);

			if(fake_position == last_position)
			{
				/* Read existing output value of PCF8574 */
				HAL_I2C_Master_Receive(&hi2c1, DEVICE_ADDRESS_READ, &pData_read, 1, 100);

				/* Reset the desired pin with saved other pins configuration */
				pData_write = ( (pData_read) & (~fake_position) );

				/* Send resetted data */
				HAL_I2C_Master_Transmit(&hi2c1, DEVICE_ADDRESS_WRITE, &pData_write, 1, 100);
			}
		}
	}
}

/**
  * @brief  Expander_Read_Pin() returns the existing state of desired pin.
  *
  * @return This parameter can be one of the Expander_PinState_t enum values:
  *            @arg EXPANDER_PIN_RESET: to clear the port pin.
  *            @arg EXPANDER_PIN_SET  : to set the port pin.
  */

Expander_PinState_t Expander_Read_Pin(uint8_t PinNumber)
{
	/* Read existing output data to compare desired pin*/
	uint8_t pData = 0x00U;
	HAL_I2C_Master_Receive(&hi2c1, DEVICE_ADDRESS_READ, &pData, 1, 100);

	if(PinNumber & pData)
	{
		return EXPANDER_PIN_SET;
	}
	else
	{
		return EXPANDER_PIN_RESET;
	}

}

void Expander_Toggle_Pin(uint8_t PinNumber)
{

	uint8_t fake_position = 0x00U;
	uint8_t last_position = 0x00U;

	for(uint8_t position = 0x00U; MAX_PIN_NUMBER; position++)
	{
		uint8_t pData_read = 0x00U;
		HAL_I2C_Master_Receive(&hi2c1, DEVICE_ADDRESS_READ, &pData_read, 1, 100);

		fake_position = (0x1U << position);
		last_position = ()

	}

}


/**
  * @brief  Expander_Read_Data() returns the existing output data of PCF8574.
  *
  * @return 8-bit output data of PCF8574.
  */
uint8_t Expander_Read_Data()
{
	uint8_t pData_read = 0x00U;
	HAL_I2C_Master_Receive(&hi2c1, DEVICE_ADDRESS_READ, &pData_read, 1, 100);

	return pData_read;
}
