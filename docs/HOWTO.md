# How to use the Joystick MSX-DOS SDCC Library (fR3eL Project)

---

## Index

- [1 Description](#1-Description)
- [2 Requirements](#2-Requirements)
- [3 Definitions](#3-Definitions)
    - [3.1 Joystick type](#31-Joystick-type)
    - [3.2 Joystick state](#32-Joystick-state)
    - [3.3 Trigger type](#33-Trigger-type)
    - [3.4 Trigger state](#34-Trigger-state)
- [4 Functions](#4-Functions)
    - [4.1 STICK](#41-STICK)
    - [4.2 STRIG](#42-STRIG)
- [5 References](#5-References)

<br/>

---

## 1 Description

Library with basic functions for reading joystick controllers or cursor keys of MSX computers.

This library does not use the MSX BIOS. It reads directly from the internal PSG ports to read the joysticks and from the PPI port to read the keyboard cursor keys. 
It is designed to develop MSX-DOS applications or other formats that do not require the use of the BIOS.

Use them for developing MSX applications using Small Device C Compiler (SDCC).

This project is an Open Source library. 
You can add part or all of this code in your application development or include it in other libraries/engines.

This library is part of the [MSX fR3eL Project](https://github.com/mvac7/SDCC_MSX_fR3eL).


<br/>

---


## 2 Requirements

- [Small Device C Compiler (SDCC) v4.1](http://sdcc.sourceforge.net/)
- [Hex2bin v2.5](http://hex2bin.sourceforge.net/)


<br/>

---

## 3 Definitions

### 3.1 Joystick type

Label | value
----- | -----
CURSORKEYS | 0
JOYSTICKA | 1
JOYSTICKB | 2


### 3.2 Joystick state

Label | value
----- | -----
JOYSTICK_INACTIVE | 0
JOYSTICK_UP | 1
JOYSTICK_UP_RIGHT | 2
JOYSTICK_RIGHT | 3
JOYSTICK_DOWN_RIGHT | 4
JOYSTICK_DOWN | 5
JOYSTICK_DOWN_LEFT | 6
JOYSTICK_LEFT | 7
JOYSTICK_UP_LEFT | 8


### 3.3 Trigger type

Label | value
----- | -----
SPACEBAR_BUTTON | 0
KEYBOARD_BUTTON | 0
JOYSTICKA_BUTTONA | 1
JOYSTICKB_BUTTONA | 2
JOYSTICKA_BUTTONB | 3
JOYSTICKB_BUTTONB | 4


### 3.4 Trigger state

Label | value
----- | -----
BUTTON_UNPRESSED | 0
BUTTON_PRESSED | -1

<br/>

---

## 4 Functions


### 4.1 STICK

Returns the joystick status.

`char STICK(char joy)`

The direction combinations of the game controllers follow the same logic as the BIOS GTSTCK function:
- UP+DOWN+RIGHT+LEFT = 0 
- UP+DOWN = 0
- RIGHT+LEFT=0 
- UP+LEFT+DOWN = LEFT
- UP+RIGHT+DOWN = RIGHT
- LEFT+UP+RIGHT = UP
- LEFT+DOWN+RIGHT = DOWN



#### Input

[char] cursor/joystick device number 


#### Output 

[char] state value 

value | state
----- | -----
0 | inactive
1 | up
2 | up & right
3 | right
4 | down & right
5 | down
6 | down & left
7 | left
8 | up & left


#### Example
  
```c
  char joyval;
  
  joyval = STICK(JOYSTICKA);
  
  if (joyval!=JOYSTICK_INACTIVE){  
    switch (joyval) 
    {     
      case JOYSTICK_UP:
        moveUp();
        break;
  
      case JOYSTICK_RIGHT:              
        moveRight();
        break;
  
      case JOYSTICK_DOWN:
        moveDown();
        break;
  
      case JOYSTICK_LEFT:
        moveDown();
        break;   
    }
  }
```


### 4.2 STRIG

Returns the trigger status.

`signed char STRIG(char triggerN)`

#### Input

[char] cursor/joystick button identifier 

value | button
----- | ------
0 | space key
1 | Joystick 1 - button 1
2 | Joystick 2 - button 1
3 | Joystick 1 - button 2
4 | Joystick 2 - button 2
                    

#### Output: 

[signed char] status value 

value | description
----- | -----------
 0 | inactive
-1 | when the space key or the joystick/mouse button is pressed down 


#### Example
  
```c
  signed char press;
  
  press = STRIG(KEYBOARD_BUTTON); //spacebar
  if (press==BUTTON_UNPRESSED) press = STRIG(JOYSTICKA_BUTTONA);
  if (press==BUTTON_PRESSED) Fire();
```

<br/>

---

## 5 References

- MSX2 Technical Handbook - Chapter 5 - Access to peripherals through BIOS - [5.2 Joystick use](https://konamiman.github.io/MSX2-Technical-Handbook/md/Chapter5a.html#52-joystick-use)  
- The MSX Red Book - 3. Programmable Sound Generator - [Register 14 and 15](https://github.com/gseidler/The-MSX-Red-Book/blob/master/the_msx_red_book.md#register_14)

<br/>

---

![Creative Commons License](https://i.creativecommons.org/l/by-nc/4.0/88x31.png) 
<br/>This document is licensed under a [Creative Commons Attribution-NonCommercial 4.0 International License](http://creativecommons.org/licenses/by-nc/4.0/).
