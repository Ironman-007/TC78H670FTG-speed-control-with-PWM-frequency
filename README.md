# TC78H670FTG-speed-control-with-PWM-frequency

## Platform:
I'm using this stepping motor ([FAULHABER 0620](https://www.faulhaber.com/en/products/series/dm0620/))for a robot poject. This motor has a 18 degree stepping angle. Without microstepping, while running, the motor will shake and the motion is not smooth. To solve this problem, I use the TC78H670FTG for driving the motor, and this motor driver supports microstepping.

## Platform:
#### hardware:
[Adafruit Feather nRF52840 Express](https://www.adafruit.com/product/4062),
[SparkFun ProDriver - Stepper Motor Driver (TC78H670FTG)](https://www.sparkfun.com/products/16836)

#### firmware development:
VSCode + PlatformIO

## Function:
Control the stepper motor through microstepping, and change the speed through the frequency of the PWM.

## Result:


https://user-images.githubusercontent.com/64370012/202924459-56f4cd26-0f1c-4944-ab36-5ae387e88ca6.mov

