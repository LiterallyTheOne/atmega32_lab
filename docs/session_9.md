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

We can create `PWM` with all three timers.
As you can see on the picture below, each corresponding pin for each timer is shown.

![s9_atmega32_oc_pins](figures/s9_atmega32_oc_pins.jpg)

* `Timer0`:
  * `OC0` -> `PB3`
* `Timer1`:
  * `OC1A` -> `PD4`
  * `OC1B` -> `PD5`
* `Timer2`:
  * `OC2` -> `PD7`

In `Timer0` and `Timer2` for generating the desired frequency we only can use a `prescaler` which
could only take values of: [1, 8, 64, 256, 1024].
As you can see this numbers are limiting.
But for `Timer1` in addition to a `prescaler`, we have another variable called `ICR1` that can
be used to control the desired freqeuency which we are going to explain more about it later.
So to generate the desired frequency for our servo motor we will be using `Timer1`.

## `Timer1`

As we discussed in the previous session, we have three timers in Atmega32.
The only timer that is `16bit` is Timer1.
To put `Timer1` in `PWM` mode, we have some registers that we are going to talk about them.

### `TCCR1A` and `TCCR1B`

Timer/Counter Register Description (TCCR) is a way that we control our timer setup.
For `Timer1` we have two registers `TCCR1A` and `TCCR1B`.

| TCCR1A        | 7      | 6      | 5      | 4      | 3     | 2     | 1     | 0     |
| ------------- | ------ | ------ | ------ | ------ | ----- | ----- | ----- | ----- |
| name          | COM1A1 | COM1A0 | COM1B1 | COM1B0 | FOC1A | FOC1B | WGM11 | WGM10 |
| Read/Write    | R/W    | R/W    | R/W    | R/W    | R/W   | R/W   | R/W   | R/W   |
| initial value | 0      | 0      | 0      | 0      | 0     | 0     | 0     | 0     |

| TCCR1B        | 7     | 6     | 5   | 4     | 3     | 2    | 1    | 0    |
| ------------- | ----- | ----- | --- | ----- | ----- | ---- | ---- | ---- |
| name          | ICNC1 | ICEC1 | -   | WGM13 | WGM12 | CS12 | CS11 | CS10 |
| Read/Write    | R/W   | R/W   | R/W | R/W   | R/W   | R/W  | R/W  | R/W  |
| initial value | 0     | 0     | 0   | 0     | 0     | 0    | 0    | 0    |

| COM1A1/COM1B1 | COM1A0/COM1B0 | Description (in fast PWM mode)                                                                                                                                        |
| ------------- | ------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| 0             | 0             | Normal port operation, OC1A/OC1B disconnected.                                                                                                                        |
| 0             | 1             | WGM13:0 = 15: Toggle OC1A on Compare Match, OC1B disconnected (normal port operation). For all other WGM13:0 settings, normal port operation, OC1A/OC1B disconnected. |
| 1             | 0             | Clear OC1A/OC1B on compare match, set OC1A/OC1B at BOTTOM, (non-inverting mode)                                                                                       |
| 1             | 1             | Set OC1A/OC1B on compare match, clear OC1A/OC1B at BOTTOM, (inverting mode)                                                                                           |

Because we need to clear `OC1A` which is connected to `PD6` get cleared every time
it reaches the value of `OCR1A`, we put it in the `non-inverting mode`.

```cpp
TCCR1A |= (1 << COM1A1)
```

## Connect servo motor to ATmega32 in SimulIDE

To add a servo motor in SimulIDE, we should go to
`Outputs/Motors/Servo Motor`.
Then we
