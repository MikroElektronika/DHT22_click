![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# DHT22 Click

---

- **CIC Prefix**  : DHT22
- **Author**      : Nenad Filipovic
- **Verison**     : 1.0.0
- **Date**        : Dec 2018.

---

### Software Support

We provide a library for the DHT22 Click on our [LibStock](https://libstock.mikroe.com/projects/view/1211/dht22-click) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

The library covers all the necessary functions to control DHT22 Click board. 
Library performs the communication with the device via CS pin as output and input.
Library have drivers for sending start signal to the sensor, release the bus to wait the sensor response signal function, 
for reading data from sensor ( humidity and temperature data ) and for calculating temperature and humidity data
and for converting sensory data into percent humidity [ % RH ] and degree Celsius [ °C ].


Key functions :

- ``` uint32_t dht22_getSensorData() ``` - Reading data from the sensor function
- ``` uint16_t dht22_calculateTemperature( uint32_t sensorData ) ``` - Calculate the temperature data function
- ``` uint16_t dht22_calculateHumidity( uint32_t sensorData ) ``` - Calculate the humidity data function

**Examples Description**

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


```.c

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

```

Additional Functions :

- dht22_displayTempHum() - Write log to Usart Terminal of humidity and temperature as a two-digit number.

The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/1211/dht22-click) page.

Other mikroE Libraries used in the example:

- UART
- Conversions


**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
---
