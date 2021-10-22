
#include "PCF8574.h"


/**
  * @brief  Expander_Write_Pin() sets or resets the desired outputs.
  *
  * @param  PinNumber specifies the output pins of PCF8574, @def_group Expander_Output_Pins.
  *
  * @param  Expander_State specifies the desired situation for selected pins.
  * 		This parameter can be one of the Expander_PinState_t enum values:
  *            @arg EXPANDER_PIN_RESET: set pin to LOW state.
  *            @arg EXPANDER_PIN_SET  : set pin to HIGH state.
  *
  * @return None
  */

void Expander_Write_Pin(uint8_t PinNumber,Expander_PinState_t Expander_State)
{
	uint8_t pData_read = 0x00U;
	uint8_t pData_write = 0x00U;

	/* "if{}" state specifies the situation of SET operation */
	if(Expander_State == EXPANDER_PIN_SET)
	{
		/* Read existing output value of PCF8574 */
		HAL_I2C_Master_Receive(&hi2c1, DEVICE_ADDRESS_READ, &pData_read, 1, 100);

		/* Set desired pin */
		pData_write = pData_read | PinNumber;

		/* Send the new data via I2C */
		HAL_I2C_Master_Transmit(&hi2c1, DEVICE_ADDRESS_WRITE, &pData_write, 1, 100);
	}

	/* "else{}" state specifies the situation of RESET operation */
	else
	{
		uint8_t fake_position = 0x00U;
		uint8_t last_position = 0x00U;

		/* Find the desired pins with comparing bit by bit */
		for(uint8_t position = 0x00U; position <= MAX_PIN_NUMBER; position++)
		{

			fake_position = (0x1U << position);
			last_position = (PinNumber & fake_position);

			/* Equality of fake_position and last_position variables refer to the desired pin is found */
			if(fake_position == last_position)
			{
				/* Read existing output value of PCF8574 */
				HAL_I2C_Master_Receive(&hi2c1, DEVICE_ADDRESS_READ, &pData_read, 1, 100);

				/* Reset the desired pin with saved other pins configuration */
				pData_write = ( (pData_read) & (~fake_position) );

				/* Send the new data via I2C*/
				HAL_I2C_Master_Transmit(&hi2c1, DEVICE_ADDRESS_WRITE, &pData_write, 1, 100);
			}
		}
	}
}

/**
  * @brief  Expander_Read_Pin() returns the existing state of desired pin.
  *
  * @return This parameter can be one of the Expander_PinState_t enum values:
  *            @arg EXPANDER_PIN_RESET: if pin is LOW state.
  *            @arg EXPANDER_PIN_SET  : if pin is HIGH state.
  */

Expander_PinState_t Expander_Read_Pin(uint8_t PinNumber)
{
	/* Read existing output data to compare with desired pin*/
	uint8_t pData = 0x00U;
	HAL_I2C_Master_Receive(&hi2c1, DEVICE_ADDRESS_READ, &pData, 1, 100);

	/* Compare existing data and PinNumber.
	 * Return SET if the result of comparison is 1.
	 * Return RESET if the result of comparison is 0.
	 */
	if(PinNumber & pData)
	{
		return EXPANDER_PIN_SET;
	}
	else
	{
		return EXPANDER_PIN_RESET;
	}

}

/**
  * @brief  Expander_Toggle_Pin() reversed the situation of desired pins.
  *
  * @param  PinNumber specifies the output pins of PCF8574, @def_group Expander_Output_Pins.
  *
  * @return None
  */
void Expander_Toggle_Pin(uint8_t PinNumber)
{

	uint8_t pData_write   = 0x00U;
	uint8_t fake_position = 0x00U;
	uint8_t last_position = 0x00U;

	/* Find the desired pins with comparing bit by bit */
	for(uint8_t position = 0x00U; position <= MAX_PIN_NUMBER; position++)
	{

		fake_position = (0x1U << position);
		last_position = (PinNumber & fake_position);

		/* Equality of fake_position and last_position variables refer to the desired pin is found */
		if(fake_position == last_position)
		{
			uint8_t pData_read = 0x00U;

			/* Read existing output value of PCF8574 */
			HAL_I2C_Master_Receive(&hi2c1, DEVICE_ADDRESS_READ, &pData_read, 1, 100);

			/* "if{}" state specifies current situation of the desired pin is HIGH */
			if(last_position & pData_read)
			{
				/* Set desired pin from HIGH to LOW */
				pData_write = (pData_read) & (~last_position);
				HAL_I2C_Master_Transmit(&hi2c1, DEVICE_ADDRESS_WRITE, &pData_write, 1, 10);
			}

			/* "else{}" state specifies current situation of the desired pin is LOW */
			else
			{
				/* Set desired pin from LOW to HIGH */
				pData_write = (pData_read) | (last_position);
				HAL_I2C_Master_Transmit(&hi2c1, DEVICE_ADDRESS_WRITE, &pData_write, 1, 10);
			}
		}

	}

}


/**
  * @brief  Expander_Read_Data() returns the existing output data of PCF8574.
  *
  * @return 8-bit available output data of PCF8574.
  */
uint8_t Expander_Read_Data()
{
	uint8_t pData_read = 0x00U;
	HAL_I2C_Master_Receive(&hi2c1, DEVICE_ADDRESS_READ, &pData_read, 1, 100);

	return pData_read;
}
