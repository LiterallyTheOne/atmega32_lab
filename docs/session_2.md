# Session 2: Counter on 7 segments

## Our goal

![7segments counter](figures/7seg_counter.gif)

## Create a new CodeVisionAVR project

We should make a new CodeVisionAVR project
with `ATmega32` selected as the chip.
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
is presented like this: `0 1 2 3 4 5 6 7 8 9 A B C D E F`.
For example:

* `0xF`= `15`
* `0x2F`: $2 \times 16 + 15$ = `47`

## Using hex to initialize our pins

Now if we want to initialize our pins we can do
something like this:

```c
PORTB = 0x00;
DDRB = 0xFF;
```

Which means all the Directions of port `B` are set
to outputs and all the initialize values are set
to `0`.

## 7seg config

As you can see on the picture below,
All the leds in each 7segments are connected
to each pins of `PORTB`.

![ATmega32 7segments](figures/atmega32_7segments.jpg)

As it is illustrated in the image below,
To disable or enable each 7segment, we can
use [4, 7] pins in `PORTC`.

![ATmega32 7segments 4](figures/atmega32_7segments_4.jpg)


:::{important}
All the pins in this experiment are
getting **activated** when we put `0`
in them.
:::


## 7seg initialization

As you can see in the **7seg config** we only need to
control `PORTB` and pins from [4, 7] of `PORTC`.
To do so we should put those pin as outputs also
we put 0 for initialization value. The result would be
something like this:

```c

PORTB = 0x00;
DDRB = 0xFF; // 0b11111111

PORTC = 0x00;
DDRC = 0xF0; // 0b11110000

```

## Create numbers

As we said:

* `0`: `light on`
* `1`: `light off`

So if we combine them together we can create numbers.
for example for number `0` we have:

* `0`: `0b11000000`, `0xC0`

Now you should find the other numbers.

## Put numbers in an array

In order to store the numbers we can define
an array like this:

```c
ch numbers[10]=
    {
        0xC0,
        ...
    };

```

## Delay

To be able to see the numbers for some time
We use `delay_ms`.
In order to do so, we first should import it like this:

```c
#include <delay.h>
```

Then we can use `delay_ms` in our code that makes a 
delay in **milliseconds**. For example `delay_ms(2000)`,
makes a delay for `2 second`.


## Counter

Now that we have stored all the numbers in an array,
and we know how to use `delay_ms`, it is time to
make a countdown.

## Buzzer config

![buzzer config](figures/atmega32_buzzer.jpg)

As you can see on the picture above,
buzzer is connected to the `0` pin of `PORTC`.
In order to work with buzzer we should change
the `PORTC.0` as an output.
After that we can control our buzzer like below:

* `1`: `activate`
* `0`: `deactivate`

## Add buzzer

Now you can add a buzzer sound to the end of the counter
with changing only some simple codes.

