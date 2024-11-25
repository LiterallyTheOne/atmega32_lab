# Session 9: Time Interuppt

## Time Interrupt

`Time Interrupt` has a timer, when it reaches
to a specific condition, an interrupt would occur.

Atmega32 has 3 main timers.

* `Timer0`: 8-bit
* `Timer1`: 16-bit
* `Timer2`: 8-bit

We will be working with `Timer0`.

### `TIMSK`

`TIMSK` stands for `Timer/Counter Interrupt Mask Register`.
`OCIE` stands for `Output Compare Match Interrupt Enable`.
`TOIE` stands for `Timer/Counter0 Overflow Interrupt Enable`.

| bit           | 7     | 6     | 5      | 4      | 3      | 2     | 1     | 0     |
| ------------- | ----- | ----- | ------ | ------ | ------ | ----- | ----- | ----- |
| name          | OCIE2 | TOIE2 | TICIE1 | OCIE1A | OCIE1B | TOIE1 | OCIE0 | TOIE0 |
| Read/Write    | R/W   | R/W   | R/W    | R/W    | R/W    | R/W   | R/W   | R/W   |
| initial value | 0     | 0     | 0      | 0      | 0      | 0     | 0     | 0     |

We need to compare the value of timer with `OCR0` register so we should
write a code like below:

```c
TIMSK |= 1 << OCIE0
```

### `TCCR0`

`TCCR0` stands for `Timer/Counter Clock Sources`.
To work with `Timer0`, we should initialize some indexes of this register.
Table below shows all the available indexes.

| bit           | 7    | 6     | 5     | 4     | 3     | 2    | 1    | 0    |
| ------------- | ---- | ----- | ----- | ----- | ----- | ---- | ---- | ---- |
| name          | FOC0 | WGM00 | COM01 | COM00 | WGM01 | CS02 | CS01 | CS00 |
| Read/Write    | R/W  | R/W   | R/W   | R/W   | R/W   | R/W  | R/W  | R/W  |
| initial value | 0    | 0     | 0     | 0     | 0     | 0    | 0    | 0    |

| WGM00 | WGM01 | Timer0 mode selection bit          |
| ----- | ----- | ---------------------------------- |
| 0     | 0     | Normal                             |
| 0     | 1     | CTC (Clear timer on Compare Match) |
| 1     | 0     | PWM, Phase correct                 |
| 1     | 1     | Fast PWM                           |

We need to compare with the `OCR0` register, so we set
`WMG01` index to 1.

```c
TCCR0 |= 1 << WMG01
```

| CS02 | CS01 | CS00 | Description                                             |
| ---- | ---- | ---- | ------------------------------------------------------- |
| 0    | 0    | 0    | No clock source (Timer/Counter stopped).                |
| 0    | 0    | 1    | clkI/O/(No prescaling)                                  |
| 0    | 1    | 0    | clkI/O/8 (From pre-scaler)                              |
| 0    | 1    | 1    | clkI/O/64 (From pre-scaler)                             |
| 1    | 0    | 0    | clkI/O/256 (From pre-scaler)                            |
| 1    | 0    | 1    | clkI/O/1024 (From pre-scaler)                           |
| 1    | 1    | 0    | External clock source on T0 pin. Clock on falling edge. |
| 1    | 1    | 1    | External clock source on T0 pin. Clock on rising edge.  |

now we should our `pre-scaler` which controls how much frequency should reach to
the `timer0`.
For example if our chip is running with `8Mhz`, if we put our
`pre-scaler` value to 8, the `timer0` would get `1Mhz` of frequency.
We can control `pre-scaler` as shown in the table above.
For example, the code below puts the pre-scaler to `1024`.

```c
TCCR0 |= 1 << CS00;
TCCR0 |= 1 << CS02;
```

### `TCNT0`

`TCNT` stands for `Timer/Counter Register`.
Any time a clock reaches the timer, this increments.
It has only 8bits so it can only reach to `255`.

### `OCR0`

`OCR` stands for `Output Compare Register`.
The value of `TCNT0` gets compare with `OCR0`.
If `TCNT0` reaches the value of `OCR0`,
an interrupt would occur.




