# Session 9: servo motor, PWM, and ADC

## Goal

TODO: fill

### Bonus

TODO: fill

## Servo Motor

![s9_servo](figures/s9_servo.jpg)

Servo motor is a type of electeric motor that is designed for precise control.
It is widely used in robotics.
We can control the position of the servo motor by sending a PWM signal to it.
In this session, we will be using a simple DC servo motor wich only take
angles in range of [-90, 90].
The desired `PWM` frequency for this servo motor is `50Hz`.
This servo motor has three pins: VCC, GND, and signal.
We are connecting those pins like this:

* VCC -> 5V (Fixed voltage)
* GND -> GND
* Signal -> `PD5` of ATmega32

## PWM

`PWM` (Pulse Width Modulation), is a technique for controlling the power delivered to a component.  
In this technique we use different width of pulses in a signal.
These signals swith between `0` and `1`.
The percentage of the time that a pulse is `1` is called **duty cycle**.
The pictures below show two examples of 100Hz `PWM`, one with the 30% duty cycle and the other 60%.

![s9_pwm_100hz_30d](figures/s9_pwm_100hz_30d.png)
![s9_pwm_100hz_60d](figures/s9_pwm_100hz_60d.png)

## Create `PWM` on ATmega32

We can create `PWM` using Timers on ATmega32.
We have three timers on Atmega32:

* Timer0: 8bit
* Timer1: 16bit
* Timer2: 8bit

In `Timer0` and `Timer2` for generating the desired frequency we only can use a `prescaler` which
could only take values of: [1, 8, 64, 256, 1024].
As you can see this numbers are limiting.
But for `Timer1` in addition to a `prescaler`, we have another variable called `ICR1` that can
be used to control the desired freqeuency which we are going to explain more about it later.
So to generate the desired frequency for our servo motor we will be using `Timer1`.

## Timer1

## Connect servo motor to ATmega32 in SimulIDE

To add a servo motor in SimulIDE, we should go to
`Outputs/Motors/Servo Motor`.
Then we
