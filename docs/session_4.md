# Session 4: LED and Interrupts

## Goal

## Bonus point

## LEDs

## Shift

## Change only one value

## Interrupt

### `GICR`

`GICR` stands for `General Interrupt Control Register`

| bit           | 7    | 6    | 5    | 4 | 3 | 2 | 1     | 0    | 
|---------------|------|------|------|---|---|---|-------|------|
| name          | INT1 | INT0 | INT2 | - | - | - | IVSEL | IVCE | 
| Read/Write    | R/W  | R/W  | R/W  | R | R | R | R/W   | R/W  | 
| initial value | 0    | 0    | 0    | 0 | 0 | 0 | 0     | 0    | 

### `MCUCR`

`MCUCR` stands for `MCU Control Register`.

| bit           | 7   | 6   | 5   | 4   | 3     | 2     | 1     | 0     | 
|---------------|-----|-----|-----|-----|-------|-------|-------|-------|
| name          | SE  | SM2 | SM1 | SM0 | ISC11 | ISC10 | ISC01 | ISC00 | 
| Read/Write    | R/W | R/W | R/W | R/W | R/W   | R/W   | R/W   | R/W   | 
| initial value | 0   | 0   | 0   | 0   | 0     | 0     | 0     | 0     | 

### `MCUCSR`

`MCUCSR` stands for `MCU Control and Status Register`.

| bit           | 7   | 6    | 5 | 4       | 3       | 2       | 1       | 0       | 
|---------------|-----|------|---|---------|---------|---------|---------|---------|
| name          | JTD | ISC2 | - | JTRF    | WDRF    | BORF    | EXTRF   | PORF    | 
| Read/Write    | R/W | R/W  | R | R/W     | R/W     | R/W     | R/W     | R/W     | 
| initial value | 0   | 0    | 0 | depends | depends | depends | depends | depends | 

### `GIFR`

`GIFR` stands for `General Interrupt Flag Register`

| bit           | 7     | 6     | 5     | 4 | 3 | 2 | 1 | 0 | 
|---------------|-------|-------|-------|---|---|---|---|---|
| name          | INTF1 | INTF0 | INTF2 | - | - | - | - | - | 
| Read/Write    | R/W   | R/W   | R/W   | R | R | R | R | R | 
| initial value | 0     | 0     | 0     | 0 | 0 | 0 | 0 | 0 | 

### `#asm`

#### `sei`

#### `cli`

### Interrupt Service Routine (ISR) function

## Time Interrupt

