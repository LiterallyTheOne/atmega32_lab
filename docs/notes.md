# Notes

## Expressions

| Expression | meaning                     |
| ---------- | --------------------------- |
| DDR        | Data Direction Register     |
| ADC        | Analog to Digital converter |

## `avrdude` useful commands

| reason                     | command                                                                |
| -------------------------- | ---------------------------------------------------------------------- |
| upload to Atmega32         | `avrdude -c usbasp -p m32 -U flash:w:.pio/build/ATmega32/firmware.hex` |
| set low fuse ATmega32      | `avrdude -c usbasp -p m32 -U lfuse:w:0xe4:m`                           |
| set high fuse bit ATmega32 | `avrdude -c usbasp -p m32 -U hfuse:w:0xd9:m`                           |

## Control global interrupts

| function | action                    |
| -------- | ------------------------- |
| `sei()`  | enable global interrupts  |
| `cli()`  | disable global interrupts |

## Interrupt

### `GICR`

`GICR` stands for `General Interrupt Control Register`.

| bit           | 7    | 6    | 5    | 4   | 3   | 2   | 1     | 0    |
| ------------- | ---- | ---- | ---- | --- | --- | --- | ----- | ---- |
| name          | INT1 | INT0 | INT2 | -   | -   | -   | IVSEL | IVCE |
| Read/Write    | R/W  | R/W  | R/W  | R   | R   | R   | R/W   | R/W  |
| initial value | 0    | 0    | 0    | 0   | 0   | 0   | 0     | 0    |

To enable `Interrupt1` to work we put the value of the 7th index of `GICR` to 1,
to do so we can use a code like this:

```c
GICR |= 1 << INT1;
```

### `MCUCR`

`MCUCR` stands for `MCU Control Register`.
`ISC` stands for `Interrupt Sense Control`.
It basically controls when should an Interrupt occur.
As you can see we can config our Interrupt to happen in different situations.

| bit           | 7   | 6   | 5   | 4   | 3     | 2     | 1     | 0     |
| ------------- | --- | --- | --- | --- | ----- | ----- | ----- | ----- |
| name          | SE  | SM2 | SM1 | SM0 | ISC11 | ISC10 | ISC01 | ISC00 |
| Read/Write    | R/W | R/W | R/W | R/W | R/W   | R/W   | R/W   | R/W   |
| initial value | 0   | 0   | 0   | 0   | 0     | 0     | 0     | 0     |

| ISC11 | ISC10 | Description                                                | figure                                                     |
| ----- | ----- | ---------------------------------------------------------- | ---------------------------------------------------------- |
| 0     | 0     | The low level of INT1 generates an interrupt request.      | ![s7_interrupt_stage_1](figures/s7_interrupt_stages_1.jpg) |
| 0     | 1     | Any logical change on INT1 generates an interrupt request. | ![s7_interrupt_stage_2](figures/s7_interrupt_stages_2.jpg) |
| 1     | 0     | The falling edge of INT1 generates an interrupt request.   | ![s7_interrupt_stage_3](figures/s7_interrupt_stages_3.jpg) |
| 1     | 1     | The rising edge of INT1 generates an interrupt request.    | ![s7_interrupt_stage_4](figures/s7_interrupt_stages_4.jpg) |

| ISC01 | ISC00 | Description                                                | figures                                                    |
| ----- | ----- | ---------------------------------------------------------- | ---------------------------------------------------------- |
| 0     | 0     | The low level of INT0 generates an interrupt request.      | ![s7_interrupt_stage_1](figures/s7_interrupt_stages_1.jpg) |
| 0     | 1     | Any logical change on INT0 generates an interrupt request. | ![s7_interrupt_stage_2](figures/s7_interrupt_stages_2.jpg) |
| 1     | 0     | The falling edge of INT0 generates an interrupt request.   | ![s7_interrupt_stage_3](figures/s7_interrupt_stages_3.jpg) |
| 1     | 1     | The rising edge of INT0 generates an interrupt request.    | ![s7_interrupt_stage_4](figures/s7_interrupt_stages_4.jpg) |

### `MCUCSR`

`MCUCSR` stands for `MCU Control and Status Register`.
The only thing that we should know in this table is `ISC2`.
This register can handle how `interrup2` will be triggerd
(Falling edge or rising edge).

| bit           | 7   | 6    | 5   | 4       | 3       | 2       | 1       | 0       |
| ------------- | --- | ---- | --- | ------- | ------- | ------- | ------- | ------- |
| name          | JTD | ISC2 | -   | JTRF    | WDRF    | BORF    | EXTRF   | PORF    |
| Read/Write    | R/W | R/W  | R   | R/W     | R/W     | R/W     | R/W     | R/W     |
| initial value | 0   | 0    | 0   | depends | depends | depends | depends | depends |

### `GIFR`

`GIFR` stands for `General Interrupt Flag Register`.
When an interrupt happens, a corresponding index of
this register will be set to 1.
If we write 1 to any of the indexes manually, we
can clear the flag.

| bit           | 7     | 6     | 5     | 4   | 3   | 2   | 1   | 0   |
| ------------- | ----- | ----- | ----- | --- | --- | --- | --- | --- |
| name          | INTF1 | INTF0 | INTF2 | -   | -   | -   | -   | -   |
| Read/Write    | R/W   | R/W   | R/W   | R   | R   | R   | R   | R   |
| initial value | 0     | 0     | 0     | 0   | 0   | 0   | 0   | 0   |
