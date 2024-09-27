# Session 2: Counter on 7 segments

## Our goal

![7segments counter](figures/7seg_counter.gif)

## Create a new CodeVisionAVR project

We should make a new CodeVisionAVR project
with `ATmega32` selected as the cip.
Then we remove all the comments and all the
initialization, because we want to make
an initialization of our own.

Your code should like this:

```c
#include <mega32.h>

void main(void)
{
    while (1)
    {
    };
}
```

## Define variables in the first block

CodVisionAVR requires us to declare all the variables
that we want in the first block.
So we are not allowed to define a variable
in a routine.

```c
#include <mega32.h>

void main(void)
{
    int a;
    
    while (1)
    {
    };
}
```

## DDR (Data Direction Register)

We can set a pin as an input or an output.
To do so we should just change the DDR of that pin
to `0` or `1`.

* `0`: input
* `1`: output

```c
DDRA.0 = 0;
```

## Declare a bit in C

We can use `0b` to declare a number in a bit format.
For example:

* `0b1` = `1`
* `0b101` = `5`
* `0b11111111` = `255`

## Declare a hex in C

We can use `0x` to declare a number in hex format.
Range of a hex number is between `[0 to 15]` which
is presented like this: `1 2 3 4 5 6 7 8 9 A B C D E F`.
For example:

* `0xF`= `15`
* `0x2F`: $2 \times 16 + 15$ = `47`

## Using hex to initialize our pins

## Initialization

## 7seg config

![ATmega32 7segments](figures/atmega32_7segments.jpg)

![ATmega32 7segments 4](figures/atmega32_7segments_4.jpg)

# 7seg initialization

## Create numbers

## Show numbers on 7seg

## Delay

## Counter

## Buzzer config

## Add buzzer

