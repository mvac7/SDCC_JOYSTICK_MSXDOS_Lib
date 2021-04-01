/* =============================================================================
   Test 1
   version: v0.9b (2/12/2020)
   author: mvac7
   description:
      Test SDCC JOYSTICK MSX-DOS Library
============================================================================= */

#include "../include/newTypes.h"
#include "../include/msxSystemVars.h"
#include "../include/msxBIOS.h"
#include "../include/msxDOS.h"

#include "../include/memory.h"
#include "../include/textmode.h"
#include "../include/keyboard.h"
#include "../include/joystick.h"

#define  SYSTEM 0x0005  // MSX-DOS entry

#define  HALT __asm halt __endasm   //wait for the next interrupt


#define HINT     0x0038 //Z80 INT (RST $38)  · IM 1 interrupts entry poin

#define HKEYI	 0xFD9A //Hook KEYI. Interrupt handler device other than the VDP. (RS-232C, MSX-Midi, etc) 
#define HTIMI	 0xFD9F //Hook TIMI. Interrupt handler VDP VBLANK




void test();

void printTrig(signed char value);
void printDIR(char A);

void System(char code);



// constants  ------------------------------------------------------------------

const char text01[] = "Test1 SDCC JOYSTICK MSX-DOS Lib";
const char text02[] = "v0.9b (02/12/2020)";

// Functions -------------------------------------------------------------------



//
void main(void)
{
  
  CLS();
    
  test();  

  
//EXIT MSXDOS ------------------------------------------------------------------
  CLS();
  
  KillBuffer();
    
  System(_TERM0); 
//--------------------------------------------------------------------- end EXIT    
}



// call system functions 
// see MSX Assembly Page > MSX-DOS 2 function calls
// http://map.grauw.nl/resources/dos2_functioncalls.php
void System(char code) __naked
{
code;
__asm
	push IX
	ld   IX,#0
	add  IX,SP

	ld   C,4(IX)
	call SYSTEM

	pop  IX
    ret
__endasm; 
}



// TEST ###############################################################
void test()
{
  char isExit = 0;
  
  char dir=0;
  char dirCURSOR=0;
  char dirJOY1=0;
  char dirJOY2=0;
  
  signed char button=0;
  signed char spaceBar=0;
  signed char but1JOY1=0;
  signed char but2JOY1=0;
  signed char but1JOY2=0;
  signed char but2JOY2=0;
      
  LOCATE(0,0);
  PRINT(text01);
  LOCATE(0,1);
  PRINT(text02);
  PRINT("\n\nHold down ESC key to exit to DOS");
  
  LOCATE(0,5);
  PRINT(">Test STICK() & STRIG()");
  
  LOCATE(3,7);
  PRINT("*Cursor Keys");
  LOCATE(4,8);
  PRINT("STICK(0)= ");
  LOCATE(4,9);
  PRINT("STRIG(0)=");  
  
  LOCATE(3,11);
  PRINT("*Joystick A");
  LOCATE(4,12);
  PRINT("STICK(1)= ");
  LOCATE(4,13);
  PRINT("STRIG(1)=");
  LOCATE(4,14);
  PRINT("STRIG(3)=");
  
  LOCATE(3,16);
  PRINT("*Joystick B");
  LOCATE(4,17);
  PRINT("STICK(2)=");
  LOCATE(4,18);
  PRINT("STRIG(2)=");
  LOCATE(4,19);
  PRINT("STRIG(4)=");
    

  while(isExit<60)
  {
    HALT;
    
    if (!(GetKeyMatrix(7)&Bit2)) isExit++;
    else isExit=0;
    
    //------------------------- cursor keys
    dir = STICK(CURSORKEYS);
    if(dirCURSOR!=dir){
        LOCATE(14,8);
        printDIR(dir);
        dirCURSOR=dir;
    }
    
    button=STRIG(KEYBOARD_BUTTON);
    if(spaceBar!=button){
        spaceBar = button;
        LOCATE(14,9);    
        printTrig(spaceBar);
    }
      
    //------------------------- joy1
    dir = STICK(JOYSTICKA);
    if(dirJOY1!=dir){
        LOCATE(14,12);
        printDIR(dir);
        dirJOY1=dir;
    }
    
    button=STRIG(JOYSTICKA_BUTTONA);
    if(but1JOY1!=button){
        but1JOY1 = button;
        LOCATE(14,13);
        printTrig(but1JOY1); 
    }
    
    button=STRIG(JOYSTICKA_BUTTONB);
    if(but2JOY1!=button){
        but2JOY1 = button;
        LOCATE(14,14);
        printTrig(but2JOY1); 
    }   
    
    //------------------------- joy2
    dir = STICK(JOYSTICKB);
    if(dirJOY2!=dir){
        LOCATE(14,17);
        printDIR(dir);
        dirJOY2=dir;
    }    
       
    button=STRIG(JOYSTICKB_BUTTONA);
    if(but1JOY2!=button){
        but1JOY2 = button;
        LOCATE(14,18);
        printTrig(but1JOY2); 
    }
    
    button=STRIG(JOYSTICKB_BUTTONB);
    if(but2JOY2!=button){
        but2JOY2 = button;
        LOCATE(14,19);
        printTrig(but2JOY2); 
    }
   
  }

}



void printTrig(signed char value)
{
  if(value==BUTTON_PRESSED) PRINT("pressed");
  else PRINT("       ");
}



void printDIR(char state)
{
  switch (state) 
  {
    case JOYSTICK_INACTIVE:
      PRINT("            "); 
      break;
    case JOYSTICK_UP:
      PRINT("Up          ");  
      break;
    case JOYSTICK_UP_RIGHT:
      PRINT("Up & Right  ");  
      break;
    case JOYSTICK_RIGHT:
      PRINT("Right       ");  
      break;
    case JOYSTICK_DOWN_RIGHT:
      PRINT("Down & Right");  
      break;
    case JOYSTICK_DOWN:
      PRINT("Down        ");  
      break;
    case JOYSTICK_DOWN_LEFT:
      PRINT("Down & Left ");  
      break;
    case JOYSTICK_LEFT:
      PRINT("Left        ");  
      break;
    case JOYSTICK_UP_LEFT:
      PRINT("Up & Left   ");  
      break;
  }
}

