The Silicon Labs Humidity and Temperature sensor is an accurate enviornment sensor with an I2C interface. My driver implements only a small portion of its functionality.

- Iniitalize the device with the ESP32 ADC port - only number one is implemented in the current tool chain
- Reset the device
- Get the measured humidity as a percentage
- Get the temperature with an option for celsius or fahrenheit

Next steps are to bullet proof the interface
