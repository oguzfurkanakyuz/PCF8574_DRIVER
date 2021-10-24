# PCF8574 I/O Expansion Module
## Overview
 [PCF8574](https://www.nxp.com/docs/en/data-sheet/PCF8574_PCF8574A.pdf "PCF8574") is an I/O expander module that interface with I2C bidirectional bus. The module can control 8 different digital I/O line. The block diagram of the module is given in Figure 1.
 
 ![](https://github.com/oguzfurkanakyuz/PCF8574_DRIVER/blob/main/img/Block_Diagram.PNG)
 > Figure 1. Block Diagram of PCF8574 Module
 
 
 PCF8574 works as a slave device and has configurable slave addresses. A0, A1, and A2 pins are address configuration pins of the module. There are 8 possible device address with these pins. Also, the module has different addresses for read and write modes. Address configuration of the module is given below in Figure 2.
 
 ![](https://github.com/oguzfurkanakyuz/PCF8574_DRIVER/blob/main/img/Address_Conf.PNG)
  > Figure 2. Slave Address Configuration

The last bit of the byte is the mode selection bit. Read mode selected when the bit set to 1, write mode selected when the bit set to 0. The configuration bits are pulled HIGH in the PCF8574 module boards (commercial shield boards), it means A0, A1 and A2 bits are 1 in these boards. The read/write addresses of these boards given in below Table 1. 0x4E must be send to the I2C bus for the write operation, 0x4F must be send the I2C bus for the read operation.

>Table 1. Read/Write Addresses

| Fixed | Fixed | Fixed | Fixed | A2 | A1 | A0 | R/W | Address |           |
|:-----:|:-----:|:-----:|:-----:|:--:|:--:|:--:|:---:|:-------:|-----------|
|   0   |   1   |   1   |   1   |  1 |  1 |  1 |  0  |   0x4E  | **Write** |
|   0   |   1   |   1   |   1   |  1 |  1 |  1 |  1  |   0x4F  | **Read**  |

The PCF8574 module returns the current pin situations when the 0x4F address is sent. However, the desired pin configuration must be sent in write operation in addition to 0x4E address. Each bidirectional line is controlled with 1-bit of byte. The corresponding bit is set to 1 to turn HIGH the output, and set to 0 to turn LOW the output. The output data configuration is given below.

>Table 2. Output Data Configurations

|   P7  |   P6  |   P5  |   P4  |   P3  |   P2  |   P1  |   P0  | Address |
|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-------:|
|   0   |   0   |   0   |   0   |   0   |   0   |   0   | **1** |   0x01  |
|   0   |   0   |   0   |   0   |   0   |   0   | **1** |   0   |   0x02  |
|   0   |   0   |   0   |   0   |   0   | **1** |   0   |   0   |   0x04  |
|   0   |   0   |   0   |   0   | **1** |   0   |   0   |   0   |   0x08  |
|   0   |   0   |   0   | **1** |   0   |   0   |   0   |   0   |   0x10  |
|   0   |   0   | **1** |   0   |   0   |   0   |   0   |   0   |   0x20  |
|   0   | **1** |   0   |   0   |   0   |   0   |   0   |   0   |   0x40  |
| **1** |   0   |   0   |   0   |   0   |   0   |   0   |   0   |   0x80  |


## How To Use
- "PCF8574.h" must be included to the "Inc" file of STM32 project.
- "PCF8574.c" must be included to the "Src" file of STM32 project.
- The generated I2C HandleTypeDef of the STM32 project must be modified in "PCF8574.h" file. You can find this definition under the "Private variables" in "main.c". Then modify the row like 'hi2c1', 'hi2c2' etc.

`extern I2C_HandleTypeDef hi2c1;`

## Functions
### Expander_Write_Pin()
Expander_Write_Pin() is a void function that set or reset the output pins. The function gets the desired pins as 8-bit data and gets the desired state with a specific state definitions. 

`void Expander_Write_Pin(uint8_t PinNumber,Expander_PinState_t Expander_State)`

- The PinNumber definitions was assigned as "Px_OUT". "P0_OUT" definition is used to express P0 pin, "P1_OUT1 used for P1 pin, etc.

- "EXPANDER_PIN_SET" and "EXPANDER_PIN_RESET" definitions are used to express pin states. 

**Example :**  Expander_Write_Pin(P4_OUT, EXPANDER_PIN_RESET) => P4 pin turn to the LOW (reset) state.

**Example :**  Expander_Write_Pin(P6_OUT, EXPANDER_PIN_SET)   => P6 pin turn to the HIGH  (set) state.

Expander_Write_Pin() function can handle multi-pin operations. Therefore it is possible to set or reset more than pins.

**Example :**  Expander_Write_Pin(P0_OUT | P1_OUT, EXPANDER_PIN_RESET) => P0 and P1 pin turns to the LOW (reset) state.

**Example :**  Expander_Write_Pin(P0_OUT | P3_OUT | P7_OUT, EXPANDER_PIN_SET)   => P0, P3, and P7 pin turns to the HIGH  (set) state.

### Expander_Toggle_Pin()
Expander_Toggle_Pin() is a void function that turns the current state to the reverse state. The function gets the desired pins as 8-bit data, the function can handle multi-pin operations also.

`void Expander_Toggle_Pin(uint8_t PinNumber)`

**Example :**  Expander_Toggle_Pin(P0_OUT) => P0 pin turn to reverse state.

**Example :**  Expander_Toggle_Pin(P0_OUT | P3_OUT)   => P0, and P3 pin turns to reverse state.

### Expander_Read_Data()
Expander_Read_Data() is function that return the current data of output pins. The function does not take any input data and returns current data as 8-bit data.

`uint8_t Expander_Read_Data()`

### Expander_Read_Pin()
Expander_ReadPin() is funtion that return the current state of desired pin, funciton can works for only 1-bit. The fuction gets desired pin as 8-bit data, and returns the current state as specific state definitions. The funciton returns 'EXPANDER_PIN_SET' if the pin is HIGH, returns 'EXPANDER_PIN_RESET' if the pin is LOW.

`Expander_PinState_t Expander_Read_Pin(uint8_t PinNumber)`
