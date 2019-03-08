/*
    __dht22_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __dht22_driver.h
@brief    DHT22 Driver
@mainpage DHT22 Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   DHT22
@brief      DHT22 Click Driver
@{

| Global Library Prefix | **DHT22** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **Dec 2018.**      |
| Developer             | **Nenad Filipovic**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"

#ifndef _DHT22_H_
#define _DHT22_H_

/** 
 * @macro T_DHT22_P
 * @brief Driver Abstract type 
 */
#define T_DHT22_P    const uint8_t*

/** @defgroup DHT22_COMPILE Compilation Config */              /** @{ */

//  #define   __DHT22_DRV_SPI__                            /**<     @macro __DHT22_DRV_SPI__  @brief SPI driver selector */
//  #define   __DHT22_DRV_I2C__                            /**<     @macro __DHT22_DRV_I2C__  @brief I2C driver selector */                                          
// #define   __DHT22_DRV_UART__                           /**<     @macro __DHT22_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
/** @defgroup DHT22_VAR Variables */                           /** @{ */



                                                                       /** @} */
/** @defgroup DHT22_TYPES Types */                             /** @{ */



                                                                       /** @} */
#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup DHT22_INIT Driver Initialization */              /** @{ */

#ifdef   __DHT22_DRV_SPI__
void dht22_spiDriverInit(T_DHT22_P gpioObj, T_DHT22_P spiObj);
#endif
#ifdef   __DHT22_DRV_I2C__
void dht22_i2cDriverInit(T_DHT22_P gpioObj, T_DHT22_P i2cObj, uint8_t slave);
#endif
#ifdef   __DHT22_DRV_UART__
void dht22_uartDriverInit(T_DHT22_P gpioObj, T_DHT22_P uartObj);
#endif

// GPIO Only Drivers - remove in other cases
void dht22_gpioDriverInit(T_DHT22_P gpioObj);
                                                                       /** @} */
/** @defgroup DHT22_FUNC Driver Functions */                   /** @{ */



/**
 * @brief Sends start signal to the sensor function
 *
 * The function sends the start signal to
 * the tempemperature and humidity sensor AM2302 on the DHT22 Click.
 *
 * @note
 * Before calling this function it is necessary to set the CS pin as output.
 */
void dht22_startSignal();

/**
 * @brief Release the bus to wait the sensor response signal function
 *
 * @return result
 * - 0 : ERROR, Sensor not responding.
 * - 1 : The sensor responded and is ready to read data.
 *
 * The function release the bus to wait the sensor response signal from
 * the sensor AM2302 on the DHT22 Click.
 *
 * @note
 * Before calling this function it is necessary to :
 * - 1. : sends start signal to the sensor by calling dht22_startSignal() function.
 * - 2. : set the CS pin as input.
 */
uint8_t dht22_checkSensorResponse();

/**
 * @brief Reading data from the sensor function
 *
 * @return result                    
 * 32-bit read value from the sensor ( temperature and humidity data )
 *
 * The function reading data from
 * the sensor AM2302 on the DHT22 Click.
 *
 * @note
 * Before calling this function it is necessary to :
 * - 1. : set the CS pin as output.
 * - 2. : sends start signal to the sensor by calling dht22_startSignal() function.
 * - 3. : set the CS pin as input.
 * - 4. : release the bus to wait the sensor response signal by calling dht22_checkSensorResponse() function.
 */
uint32_t dht22_getSensorData();

/**
 * @brief Calculate the temperature data function
 *
 * @param[in] sensorData                   
 * 32-bit read value from the sensor ( temperature and humidity data )
 *
 * @return result
 * 16-bit temperature data
 *
 * The function calculate the temperature data from sensor data reading from
 * the sensor AM2302 on the DHT22 Click.
 *
 * @note
 * The 16-bit temperature data should be divided by 10
 * to obtain the exact temperature value in degrees Celsius [ °C ].
 */
uint16_t dht22_calculateTemperature( uint32_t sensorData );

/**
 * @brief Calculate the temperature in degrees Celsius function
 *
 * @param[in] sensorData
 * 32-bit read value from the sensor ( temperature and humidity data )
 *
 * @return result
 * float temperature in degrees Celsius [ °C ]
 *
 * The function calculate the temperature in degrees Celsius [ °C ] 
 * from sensor data reading from the sensor AM2302 on the DHT22 Click.
 */
float dht22_calcTempC( uint32_t sensorData );

/**
 * @brief Calculate the humidity data function
 *
 * @param[in] sensorData
 * 32-bit read value from the sensor ( temperature and humidity data )
 *
 * @return result
 * 16-bit humidity data
 *
 * The function calculate the humidity data from sensor data reading from
 * the sensor AM2302 on the DHT22 Click.
 *
 * @note
 * The 16-bit humidity data should be divided by 10
 * to obtain the exact percentage of humidity [ % RH ].
 */
uint16_t dht22_calculateHumidity( uint32_t sensorData );

/**
 * @brief Calculate the humidity in percentage function
 *
 * @param[in] sensorData
 * 32-bit read value from the sensor ( temperature and humidity data )
 *
 * @return result
 * float percentage of humidity [ % RH ]
 *
 * The function calculate the percentage of humidity [ % RH ]
 * from sensor data reading from the sensor AM2302 on the DHT22 Click.
 */
float dht22_calcHumidity( uint32_t sensorData );




                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_DHT22_STM.c
    @example Click_DHT22_TIVA.c
    @example Click_DHT22_CEC.c
    @example Click_DHT22_KINETIS.c
    @example Click_DHT22_MSP.c
    @example Click_DHT22_PIC.c
    @example Click_DHT22_PIC32.c
    @example Click_DHT22_DSPIC.c
    @example Click_DHT22_AVR.c
    @example Click_DHT22_FT90x.c
    @example Click_DHT22_STM.mbas
    @example Click_DHT22_TIVA.mbas
    @example Click_DHT22_CEC.mbas
    @example Click_DHT22_KINETIS.mbas
    @example Click_DHT22_MSP.mbas
    @example Click_DHT22_PIC.mbas
    @example Click_DHT22_PIC32.mbas
    @example Click_DHT22_DSPIC.mbas
    @example Click_DHT22_AVR.mbas
    @example Click_DHT22_FT90x.mbas
    @example Click_DHT22_STM.mpas
    @example Click_DHT22_TIVA.mpas
    @example Click_DHT22_CEC.mpas
    @example Click_DHT22_KINETIS.mpas
    @example Click_DHT22_MSP.mpas
    @example Click_DHT22_PIC.mpas
    @example Click_DHT22_PIC32.mpas
    @example Click_DHT22_DSPIC.mpas
    @example Click_DHT22_AVR.mpas
    @example Click_DHT22_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __dht22_driver.h

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */