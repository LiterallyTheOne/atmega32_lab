# Session 3: Different numbers in 7 segments

## Our goal

As you can see on the gif below, our goal for this session
is to make different numbers on different individual 7segments.

![7segments date](figures/7segments_date.gif)

### Bonus point

For bonus points we can make a slider as shown in the
gif below.

![7segments date 2](figures/7segments_date_2.gif)

## Review

### DDR (Data Direction Register)

To make a pin an input or an output.
for example:

* `DDRB = 0xF0` or `DDRB = 0b1111000`

### numbers

In the last session we learned how to make different
numbers on the 7segments.
In case you missed it here are the numbers:

```json
{
  "0": "0xC0",
  "1": "0xF9",
  "2": "0xA4",
  "3": "0xB0",
  "4": "0xB0",
  "5": "0x92",
  "6": "0x82",
  "7": "0xF8",
  "8": "0x80",
  "9": "0x90"
}

```

## 7segments config for each 7segment

![ATmega32 7segments 4](figures/atmega32_7segments_4.jpg)

As you can see on the picture below, to control which
7segment to work we can use pins [4, 7] in `PORTC`.

:::{important}
pins are
getting **activated** when we put `0`
in them.
:::

## Work on only one 7segments

To work with only one 7segment, we can simply
put `1` for the rest of them.

for example to only work with the most left
7segment we can have a setup like this:

```c
PORTC.7 = 1;
PORTC.6 = 1;
PORTC.5 = 1;
PORTC.4 = 0;
```

## Delay to show them simultaneously

We can't show all the numbers at the same time on the
7segments, so we should do a trick that it looks like
we are showing them simultaneously.
In order to do so we are using a small delay
for example about `5ms`.

For example to show `12` from left to right on
the 7segments we can do something like this
(imagine that we have all the numbers stored in an
array with the name of `numbers`):

```c
PORTC.7 = 1;
PORTC.6 = 1;
PORTC.5 = 1;
PORTC.4 = 0;

PORTB = numbers[1];
delay_ms(5);

PORTC.7 = 1;
PORTC.6 = 1;
PORTC.5 = 0;
PORTC.4 = 1;

PORTB = numbers[2];
delay_ms(5);

```

## Function

So now we have a way to create our numbers, let's put
it in a function.
On the top of our `main` function we are going to define
a function like below:

```c
void f1(int idx, int number){

}
```

Now I put the approach that I had in this function.

```c
void f1(int idx, int number){

    PORTC.7 = 1;
    PORTC.6 = 1;
    PORTC.5 = 1;
    PORTC.4 = 0;

    PORTB = numbers[1];
    delay_ms(5);

}
```

now I adopt it with the arguments that I had,
first I start with `number`.

```c
void f1(int idx, int number){

    PORTC.7 = 1;
    PORTC.6 = 1;
    PORTC.5 = 1;
    PORTC.4 = 0;

    PORTB = numbers[number];
    delay_ms(5);

}
```

Then I put the initial value of each `pin` to one, then I
write a `switch case` for the different indexes.

```c
void f1(int idx, int number){

    PORTC.7 = 1;
    PORTC.6 = 1;
    PORTC.5 = 1;
    PORTC.4 = 1;
    
    switch (idx)
    {
    case 0:
        PORTC .7 = 0;
        break;
    case 1:
        PORTC .6 = 0;
        break;
    case 2:
        PORTC .5 = 0;
        break;
    case 3:
        PORTC .4 = 0;
        break;
    }

    PORTB = numbers[number];
    delay_ms(5);
}
```

Now I have a function that I can use to write numbers
on each 7segment.

## Replace the approach with the function

Now we replace the code with the function that we wrote
previously.


```c
f1(3, 1);
f2(2, 2);

```

## Put them in a for loop

To do this for a period of time we can use a `for` loop.

something like this:

```c
for(i=0; i<100; i++){
    f1(3, 1);
    f2(2, 2);
}

for(i=0; i<100; i++){
    f1(3, 3);
    f2(2, 4);
}
```


The reason that we can't put a delay between these two,
is that we want each 7segment to have its value.
If we put delay only the last number will show.

## String