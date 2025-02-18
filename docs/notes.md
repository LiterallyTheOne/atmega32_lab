# Notes

## Expressions

| Expression | meaning                     |
| ---------- | --------------------------- |
| DDR        | Data Direction Register     |
| ADC        | Analog to Digital converter |

## `avrdude` useful commands

| reason | command |
|--------|-------- |
| upload to Atmega32 |`avrdude -c usbasp -p m32 -U flash:w:.pio/build/ATmega32/firmware.hex` |
| set low fuse ATmega32 | `avrdude -c usbasp -p m32 -U lfuse:w:0xe4:m` |
| set high fuse bit ATmega32 | `avrdude -c usbasp -p m32 -U hfuse:w:0xd9:m` |
