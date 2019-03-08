/*
    __dht22_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__dht22_driver.h"
#include "__dht22_hal.c"

/* ------------------------------------------------------------------- MACROS */



/* ---------------------------------------------------------------- VARIABLES */

#ifdef   __DHT22_DRV_I2C__
static uint8_t _slaveAddress;
#endif

/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */

void dht22_csHigh();

void dht22_csLow();

uint8_t dht22_getCS();

/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */

void dht22_csHigh()
{
    hal_gpio_csSet( 1 );
}

void dht22_csLow()
{
    hal_gpio_csSet( 0 );
}

uint8_t dht22_getCS()
{
    return hal_gpio_csGet();
}

/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __DHT22_DRV_SPI__

void dht22_spiDriverInit(T_DHT22_P gpioObj, T_DHT22_P spiObj)
{
    hal_spiMap( (T_HAL_P)spiObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif
#ifdef   __DHT22_DRV_I2C__

void dht22_i2cDriverInit(T_DHT22_P gpioObj, T_DHT22_P i2cObj, uint8_t slave)
{
    _slaveAddress = slave;
    hal_i2cMap( (T_HAL_P)i2cObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif
#ifdef   __DHT22_DRV_UART__

void dht22_uartDriverInit(T_DHT22_P gpioObj, T_DHT22_P uartObj)
{
    hal_uartMap( (T_HAL_P)uartObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif

// GPIO Only Drivers - remove in other cases
void dht22_gpioDriverInit(T_DHT22_P gpioObj)
{
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
}

/* ----------------------------------------------------------- IMPLEMENTATION */


/* Sends start signal to the sensor function */
void dht22_startSignal()
{
    uint8_t timeout;

    dht22_csHigh();

    Delay_100ms();

    dht22_csLow();

    Delay_1ms();
    Delay_1ms();

    dht22_csHigh();
}

/* Release the bus to wait the sensor response signal function */
uint8_t dht22_checkSensorResponse()
{
    uint8_t timeout;

    timeout = 200;

    while ( dht22_getCS() )
    {
        Delay_1us();

        if ( !timeout-- )
            return 0;
    }
    
    while ( !dht22_getCS() )
        Delay_1us();

    while ( dht22_getCS() )
        Delay_1us();
    
    return 1;
}

/* Reading data from the sensor function */
uint32_t dht22_getSensorData()
{
    uint8_t cnt_i ;
    uint8_t cnt_j ;
    uint8_t sensorByteBuffer;
    uint32_t result;
    uint8_t readBuffer[ 5 ];
    
    result = 0x00000000;
    
    for ( cnt_i = 0; cnt_i < 5; cnt_i++ )
    {
        for ( cnt_j = 1; cnt_j <= 8; cnt_j++ )
                {
            while ( !dht22_getCS() )
                Delay_1us();

            Delay_10us();
            Delay_10us();
            Delay_10us();

            sensorByteBuffer <<= 1;

            if ( dht22_getCS() )
            {
                sensorByteBuffer |= 1;

                Delay_22us();
                Delay_22us();
                Delay_1us();

                while ( dht22_getCS() )
                    Delay_1us();

            }
        }

    readBuffer[ cnt_i ] = sensorByteBuffer;
    
    }

    result = readBuffer[ 0 ];
    result <<= 8;
    result |= readBuffer[ 1 ];
    result <<= 8;
    result |= readBuffer[ 2 ];
    result <<= 8;
    result |= readBuffer[ 3 ];

    return result;
}

/* Calculate the temperature data function */
uint16_t dht22_calculateTemperature( uint32_t sensorData )
{
    uint16_t temperature;

    temperature = ( uint16_t ) sensorData ;
    
    return temperature;
}

/* Calculate the temperature in degrees Celsius function */
float dht22_calcTempC( uint32_t sensorData )
{
    uint16_t tempData;
    float result;
    
    result = 0.0;

    tempData = ( uint16_t ) sensorData ;
    
    result = tempData / 10.0;

    return result;
}

/* Calculate the humidity data function */
uint16_t dht22_calculateHumidity( uint32_t sensorData )
{
    uint16_t humidity;

    humidity = ( uint16_t ) ( sensorData >> 16 );

    return humidity;
}

/* Calculate the humidity in percentage function */
float dht22_calcHumidity( uint32_t sensorData )
{
    uint16_t humData;
    float result;

    result = 0.0;

    humData = ( uint16_t ) sensorData ;

    result = humData / 10.0;

    return result;
}




/* -------------------------------------------------------------------------- */
/*
  __dht22_driver.c

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