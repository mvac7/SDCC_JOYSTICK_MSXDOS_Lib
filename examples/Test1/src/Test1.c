/* =============================================================================
   Test1 JOYSTICK MSX-DOS Library
   Version: v1.0b (10/February/2023)
   Author: mvac7
   
   Description:
      Test SDCC JOYSTICK MSX-DOS Library
      
   History of versions:
   - v1.0b (10/February/2023) For v2 of the library and log format output 
   - v0.9b (2/12/2020)    
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



// -----------------------------------------------------------------------------

void test();

void printTrig(char Ntrigger);
void printDIR(char Njoy, char state);

void System(char code);



// ----------------------------------------------------------------------------- constants

const char text01[] = "Test1 SDCC JOYSTICK MSX-DOS Lib\n";
const char text02[] = "v1.0b (10/February/2023)\n";
const char text03[] = "by mvac7/303bcn\n";
const char text04[] = "Test of STICK and STRING.\n";


// ----------------------------------------------------------------------------- Functions

//
void main(void)
{
  
  CLS();
    
  test();  

  
//EXIT MSXDOS ------------------------------------------------------------------
 
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
  boolean spaceBar_pressed=false;
  boolean but1JOY1_pressed=false;
  boolean but2JOY1_pressed=false;
  boolean but1JOY2_pressed=false;
  boolean but2JOY2_pressed=false;

      
  PRINT(text01);
  PRINT(text02);
  PRINT(text03);
  PRINT(text04);
  PRINT("Hold down [ESC] key to return to DOS\n");
  
   

  while(isExit<60)
  {
    HALT;
    
    if (!(GetKeyMatrix(7)&Bit2)) isExit++;
    else isExit=0;
    
    //------------------------- cursor keys
    dir = STICK(CURSORKEYS);
    if(dir!=JOYSTICK_INACTIVE){
        if(dir!=dirCURSOR)
        {
            printDIR(CURSORKEYS, dir);
            dirCURSOR=dir;
        }
    }else dirCURSOR=JOYSTICK_INACTIVE;
    
   
    button=STRIG(SPACEBAR_BUTTON);
    if(button==BUTTON_PRESSED)
    {
        if(!spaceBar_pressed){
            printTrig(SPACEBAR_BUTTON);
            spaceBar_pressed = true;
        }    
    }else spaceBar_pressed = false; 
    
      
    //------------------------- joy1
    dir = STICK(JOYSTICKA);
    if(dir!=JOYSTICK_INACTIVE){
        if(dir!=dirJOY1)
        {
            printDIR(JOYSTICKA, dir);
            dirJOY1=dir;
        }
    }else dirJOY1=JOYSTICK_INACTIVE;
   
    button=STRIG(JOYSTICKA_BUTTONA);
    if(button==BUTTON_PRESSED)
    {
        if(!but1JOY1_pressed){
            printTrig(JOYSTICKA_BUTTONA);
            but1JOY1_pressed = true;
        }    
    }else but1JOY1_pressed = false;
    
    button=STRIG(JOYSTICKA_BUTTONB);
    if(button==BUTTON_PRESSED)
    {
        if(!but2JOY1_pressed){
            printTrig(JOYSTICKA_BUTTONB);
            but2JOY1_pressed = true;
        }    
    }else but2JOY1_pressed = false;
    

    
    //------------------------- joy2
    dir = STICK(JOYSTICKB);
    if(dir!=JOYSTICK_INACTIVE){
        if(dir!=dirJOY2)
        {
            printDIR(JOYSTICKB, dir);
            dirJOY2=dir;
        }
    }else dirJOY2=JOYSTICK_INACTIVE;
    
    button=STRIG(JOYSTICKB_BUTTONA);
    if(button==BUTTON_PRESSED)
    {
        if(!but1JOY2_pressed){
            printTrig(JOYSTICKB_BUTTONA);
            but1JOY2_pressed = true;
        }    
    }else but1JOY2_pressed = false;
    
    button=STRIG(JOYSTICKB_BUTTONB);
    if(button==BUTTON_PRESSED)
    {
        if(!but2JOY2_pressed){
            printTrig(JOYSTICKB_BUTTONB);
            but2JOY2_pressed = true;
        }    
    }else but2JOY2_pressed = false;
   
   
  }
  
  PRINT("End Test");

}




void printTrig(char Ntrigger)
{
  switch (Ntrigger) 
  {
    case SPACEBAR_BUTTON:
      PRINT("Keyboard   - [Spacebar]");  
      break;
      
    case JOYSTICKA_BUTTONA:
      PRINT("Joystick 1 - [Button 1]");  
      break;
    
    case JOYSTICKA_BUTTONB:
      PRINT("Joystick 1 - [Button 2]");  
      break;

    case JOYSTICKB_BUTTONA:
      PRINT("Joystick 2 - [Button 1]");  
      break;
    
    case JOYSTICKB_BUTTONB:
      PRINT("Joystick 2 - [Button 2]");  
      break;
  }
  PRINT(" pressed\n");
}



void printDIR(char Njoy, char state)
{
  if (Njoy==1) PRINT("Joystick 1 - ");
  else if (Njoy==2) PRINT("Joystick 2 - ");
  else PRINT("Keyboard   - "); 


  switch (state) 
  {
    /*case JOYSTICK_INACTIVE:
      PRINT("            "); 
      break;*/
    case JOYSTICK_UP:
      PRINT("[Up]");  
      break;
    case JOYSTICK_UP_RIGHT:
      PRINT("[Up] & [Right]");  
      break;
    case JOYSTICK_RIGHT:
      PRINT("[Right]");  
      break;
    case JOYSTICK_DOWN_RIGHT:
      PRINT("[Down] & [Right]");  
      break;
    case JOYSTICK_DOWN:
      PRINT("[Down]");  
      break;
    case JOYSTICK_DOWN_LEFT:
      PRINT("[Down] & [Left]");  
      break;
    case JOYSTICK_LEFT:
      PRINT("[Left]");  
      break;
    case JOYSTICK_UP_LEFT:
      PRINT("[Up] & [Left]");  
      break;
  }
  
  PRINT("\n");
}

