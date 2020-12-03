# SDCC Joystick MSX-DOS Functions Library

Author: mvac7 [mvac7303b@gmail.com]

Architecture: MSX

Format: C Object (SDCC .rel)

Programming language: C and Z80 assembler
 




## 1. Introduction

This project is an Open Source library with basic functions for reading joystick controllers or cursor keys of MSX computers.

Use them for developing MSX applications using Small Device C Compiler (SDCC).

This library uses functions from the MSX BIOS through interslot calls (CALSLT), so that they can be used in MSXDOS applications.

Includes two applications for test and learning purposes.



## 2. Acknowledgments
  
Thanks for Info & help, to:

* Avelino Herrera > http://msx.atlantes.org/index_es.html
* Nerlaska > http://albertodehoyonebot.blogspot.com.es
* Andrear > http://andrear.altervista.org/home/msxsoftware.php
* Sapphire/Z80ST > http://z80st.auic.es/
* Fubu > http://www.gamerachan.org/fubu/
* MSX Assembly Page > http://map.grauw.nl/resources/msxbios.php
* Portar MSX Tech Doc > http://nocash.emubase.de/portar.htm
* MSX Resource Center > http://www.msx.org/
* Karoshi MSX Community (RIP 2007-2020)
* BlueMSX >> http://www.bluemsx.com/
* OpenMSX >> http://openmsx.sourceforge.net/
* Meisei  >> ?



## 3. Requirements

* Small Device C Compiler (SDCC) v3.9 http://sdcc.sourceforge.net/
* Hex2bin v2.5 http://hex2bin.sourceforge.net/ 



## 4. Functions

* char STICK(char joy) - Returns the joystick status.
* signed char STRIG(char joy) - Returns the trigger status.