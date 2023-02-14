# Joystick MSX-DOS SDCC Library (fR3eL Project)

```
Author: mvac7 (aka aorante)
Architecture: MSX
Format: C Object (SDCC .rel)
Programming language: C and Z80 assembler
```



## Description

This project is an Open Source library with basic functions for reading joystick controllers or cursor keys of MSX computers.

Use them for developing MSX applications using Small Device C Compiler (SDCC).

This library uses functions from the MSX BIOS through interslot calls (CALSLT), so that they can be used in MSXDOS applications.

In the source code (\examples), you can find applications for testing and learning purposes.

This library is part of the [MSX fR3eL Project](https://github.com/mvac7/SDCC_MSX_fR3eL).

Enjoy it!



## Requirements

* Small Device C Compiler (SDCC) v3.9 http://sdcc.sourceforge.net/
* Hex2bin v2.5 http://hex2bin.sourceforge.net/ 


## Definitions

### Joystick type

Label | value
----- | -----
CURSORKEYS | 0
JOYSTICKA | 1
JOYSTICKB | 2


### Joystick state

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


### Trigger type

Label | value
----- | -----
SPACEBAR_BUTTON | 0
KEYBOARD_BUTTON | 0
JOYSTICKA_BUTTONA | 1
JOYSTICKB_BUTTONA | 2
JOYSTICKA_BUTTONB | 3
JOYSTICKB_BUTTONB | 4


### Trigger state

Label | value
----- | -----
BUTTON_UNPRESSED | 0
BUTTON_PRESSED | -1



## Functions


### STICK

Returns the joystick status.

`char STICK(char joy)`


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




### STRIG

Returns the trigger status.

`signed char STRIG(char joy)`

#### Input

[char] cursor/joystick button identifier 

value | button
----- | ------
0 | space key
1 | button 1 joystick 1
2 | button 1 joystick 2
3 | button 2 joystick 1
4 | button 2 joystick 2
                    

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

