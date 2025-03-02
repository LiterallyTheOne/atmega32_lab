# Session 3: multiple 7segments

## Goal

![s3_goal](figures/s3_goal.gif)
![s3_goal_board](figures/s3_goal_board.gif)

## Bonus

![s3_bonus](figures/s3_bonus.gif)
![s3_bonus_board](figures/s3_bonus_board.gif)

## Shift

We can shift a number, multiple times like below:

```c
number << how_many
```

for example:

```c
int a = 0b10; // 2
int b = 2;

int c = a << b; 
// c = 8

```

## Change only the value of one index

So that we know with shift we can only change one index
of a number like below.

```c
number |= 1 << which_index;
```

For example:

```c
int a = 0b00100010; // 34
int b = 2;

a |= 1 << b; // 38
```

Another example with `PORTB`:

```c
PORTB |= 1 << 2;
```

To make a value of a certain index of a number,
we can use a code like this.

```c
PORTB &= ~(1 << 3);
// 1 << 2 == 0b100
// ~(1 << 2) == 0b011
```
