/*
Example for DHT22 Click

    Date          : Dec 2018.
    Author        : Nenad Filipovic

Test configuration PIC32 :
    
    MCU                : P32MX795F512L
    Dev. Board         : EasyPIC Fusion v7
    PIC32 Compiler ver : v4.0.0.0

---

Description :

The application is composed of three sections :

- System Initialization - Initializes GPIO and LOG structures, set CS pin as input/output.
- Application Initialization - Initialization driver enable's - GPIO and start write log.
- Application Task - (code snippet) This is a example which demonstrates the use of DHT22 Click board.
     DHT22 Click communicates with sensor via CS pin and display humidity and temperature value by
     set the CS pin as output and sends start signal to the sensor,
     set the CS pin as input and release the bus to wait the sensor response signal,
     reading data from the sensor and display calculated value of the humidity and temperature data.
     Results are being sent to the Usart Terminal where you can track their changes.
     All data logs write on usb uart changes for every 1 sec.

Additional Functions :

- dht22_displayTempHum() - Write log to Usart Terminal of humidity and temperature as a two-digit number.

*/

#include "Click_DHT22_types.h"
#include "Click_DHT22_config.h"


uint16_t humidity;
uint16_t temperature;
uint32_t sensorData;
char logText[ 50 ];

void dht22_displayTempHum()
{
    mikrobus_logWrite( " Humidity   : ", _LOG_TEXT );
    IntToStr( humidity / 10, logText );
    ltrim( logText );
    mikrobus_logWrite( logText, _LOG_TEXT );
    mikrobus_logWrite( ".", _LOG_TEXT );
    IntToStr( humidity % 10, logText );
    ltrim( logText );
    mikrobus_logWrite( logText, _LOG_TEXT );
    mikrobus_logWrite( " %", _LOG_LINE );

    mikrobus_logWrite( " Temperature: ", _LOG_TEXT );
    IntToStr( temperature / 10, logText );
    ltrim( logText );
    mikrobus_logWrite( logText, _LOG_TEXT );
    mikrobus_logWrite( ".", _LOG_TEXT );
    IntToStr( temperature % 10, logText );
    ltrim( logText );
    mikrobus_logWrite( logText, _LOG_TEXT );
    mikrobus_logWrite( " °C", _LOG_LINE );
    mikrobus_logWrite( "----------------------", _LOG_LINE );
}

void systemInit()
{
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_CS_PIN, _GPIO_INPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_CS_PIN, _GPIO_OUTPUT );

    mikrobus_logInit( _LOG_USBUART_A, 9600 );

    Delay_100ms();
}

void applicationInit()
{
    dht22_gpioDriverInit( (T_DHT22_P)&_MIKROBUS1_GPIO );

    mikrobus_logWrite( "----------------------", _LOG_LINE );
    mikrobus_logWrite( "     DHT22  Click     ", _LOG_LINE );
    mikrobus_logWrite( "----------------------", _LOG_LINE );

    Delay_100ms();
}

void applicationTask()
{
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_CS_PIN, _GPIO_OUTPUT );

    dht22_startSignal();

    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_CS_PIN, _GPIO_INPUT );

    if ( dht22_checkSensorResponse() )
    {
        sensorData = dht22_getSensorData();

        if ( sensorData != 0 )
        {
            temperature = dht22_calculateTemperature( sensorData );

            humidity = dht22_calculateHumidity( sensorData );

            dht22_displayTempHum();
        }
    }

    Delay_1sec();
}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
            applicationTask();
    }
}