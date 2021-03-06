#!/usr/bin/env python

# Author: Andrea Stagi <stagi.andrea@gmail.com>
# Description: just a test for DallasTemperature
# Dependencies: None

from nanpy import DallasTemperature

sensors = DallasTemperature(5)

while True:
    print("There are %d devices connected on pin %d" % (sensors.getDeviceCount(), sensors.pin))
    sensors.requestTemperatures(0)
    addr = sensors.getAddress(0)
    temp = sensors.getTempC(addr)
    print("The temperature, in Celsius degrees is %0.2f" % temp)
    print("Let's convert it in Fahrenheit degrees: %0.2f" % DallasTemperature.toFahrenheit(temp))

