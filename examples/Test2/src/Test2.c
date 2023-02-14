/* =============================================================================
   Test 2
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
#include "../include/keyboard.h"
#include "../include/joystick.h"
#include "../include/VDP_TMS9918A.h"
#include "../include/vprint.h"



// ----------------------------------------------------------------------------- 
#define  SYSTEM 0x0005  // MSX-DOS entry

#define  HALT __asm halt __endasm   //wait for the next interrupt


// ----------------------------------------------------------------------------- 
void test();

void printDIR(byte x, byte y, char A);

void System(char code);

void SCREEN0();
void SCREEN1();


// ----------------------------------------------------------------------------- constants


const char text01[] = "Test2 SDCC JOYSTICK MSX-DOS Lib";
const char text02[] = "v0.9b (3/12/2020)";


// map size width:32 height:24
// Size= 768
const char Joytest_MAP[]={
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x4B,0x65,0x79,0x62,0x6F,0x61,0x72,0x64,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x18,0x17,0x19,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x16,0x20,0x16,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x18,0x17,0x1B,0x20,0x1A,0x17,0x19,0x18,0x17,0x17,0x17,0x17,0x17,0x19,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x16,0x20,0x20,0x20,0x20,0x20,0x16,0x16,0x20,0x20,0x20,0x20,0x20,0x16,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x1A,0x17,0x19,0x20,0x18,0x17,0x1B,0x1A,0x17,0x17,0x17,0x17,0x17,0x1B,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x16,0x20,0x16,0x20,0x20,0x20,0x53,0x50,0x41,0x43,0x45,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x1A,0x17,0x1B,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x4A,0x6F,0x79,0x73,0x74,0x69,0x63,0x6B,0x20,0x41,0x20,0x20,0x20,0x20,
0x20,0x4A,0x6F,0x79,0x73,0x74,0x69,0x63,0x6B,0x20,0x42,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x18,0x17,0x19,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x18,0x17,0x19,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x16,0x20,0x16,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x16,0x20,0x16,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x18,0x17,0x1B,0x20,0x1A,0x17,0x19,0x18,0x17,0x19,0x18,0x17,0x19,0x20,
0x20,0x18,0x17,0x1B,0x20,0x1A,0x17,0x19,0x18,0x17,0x19,0x18,0x17,0x19,0x20,0x20,
0x20,0x20,0x16,0x20,0x20,0x20,0x20,0x20,0x16,0x16,0x20,0x16,0x16,0x20,0x16,0x20,
0x20,0x16,0x20,0x20,0x20,0x20,0x20,0x16,0x16,0x20,0x16,0x16,0x20,0x16,0x20,0x20,
0x20,0x20,0x1A,0x17,0x19,0x20,0x18,0x17,0x1B,0x1A,0x17,0x1B,0x1A,0x17,0x1B,0x20,
0x20,0x1A,0x17,0x19,0x20,0x18,0x17,0x1B,0x1A,0x17,0x1B,0x1A,0x17,0x1B,0x20,0x20,
0x20,0x20,0x20,0x20,0x16,0x20,0x16,0x20,0x20,0x20,0x31,0x20,0x20,0x32,0x20,0x20,
0x20,0x20,0x20,0x16,0x20,0x16,0x20,0x20,0x20,0x31,0x20,0x20,0x32,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x1A,0x17,0x1B,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x1A,0x17,0x1B,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20};


// Project: tMSgFX_def_tilesets
// tileset pattern
// Tiles range: 0 to 125
// Size= 1008
const unsigned char TILESET_FONT[]={
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xAA,0x55,0xAA,0x55,0xAA,0x55,0xAA,0x55,0x00,0x01,0x03,0x07,0x0F,0x1F,0x3F,0x7F,
0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0xFE,0xFF,0x7F,0x3F,0x1F,0x0F,0x07,0x03,0x01,0x00,
0xFF,0xFE,0xFC,0xF8,0xF0,0xE0,0xC0,0x80,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,
0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x18,0xFF,0xFF,0x00,0x00,0x00,
0x00,0x00,0x00,0xFF,0xFF,0x18,0x18,0x18,0x18,0x18,0x18,0xF8,0xF8,0x18,0x18,0x18,
0x18,0x18,0x18,0x1F,0x1F,0x18,0x18,0x18,0x18,0x18,0x18,0xFF,0xFF,0x18,0x18,0x18,
0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,
0x00,0x00,0x00,0x0F,0x1F,0x18,0x18,0x18,0x00,0x00,0x00,0xF0,0xF8,0x18,0x18,0x18,
0x18,0x18,0x18,0x1F,0x0F,0x00,0x00,0x00,0x18,0x18,0x18,0xF8,0xF0,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x0C,0x0C,0x0C,0x00,0x0C,0x00,
0x00,0x14,0x14,0x00,0x00,0x00,0x00,0x00,0x00,0x14,0x3E,0x14,0x3E,0x14,0x00,0x00,
0x08,0x3E,0x68,0x3E,0x0B,0x3E,0x08,0x00,0x00,0x33,0x36,0x0C,0x1B,0x33,0x00,0x00,
0x00,0x38,0x6C,0x3D,0x66,0x3D,0x00,0x00,0x00,0x18,0x30,0x00,0x00,0x00,0x00,0x00,
0x06,0x0C,0x0C,0x0C,0x0C,0x0C,0x06,0x00,0x30,0x18,0x18,0x18,0x18,0x18,0x30,0x00,
0x00,0x5A,0x3C,0x7E,0x3C,0x5A,0x00,0x00,0x00,0x18,0x18,0x7E,0x18,0x18,0x00,0x00,
0x00,0x00,0x00,0x00,0x18,0x18,0x10,0x00,0x00,0x00,0x00,0x7E,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x06,0x0C,0x18,0x30,0x60,0x00,0x00,
0x00,0x3E,0x63,0x63,0x63,0x3E,0x00,0x00,0x00,0x18,0x38,0x18,0x18,0x3C,0x00,0x00,
0x00,0x7E,0x03,0x3E,0x60,0x7F,0x00,0x00,0x00,0x7E,0x03,0x1E,0x03,0x7E,0x00,0x00,
0x00,0x63,0x63,0x7F,0x03,0x03,0x00,0x00,0x00,0x7F,0x60,0x7E,0x03,0x7E,0x00,0x00,
0x00,0x3E,0x60,0x7E,0x63,0x3E,0x00,0x00,0x00,0x7F,0x03,0x06,0x0C,0x0C,0x00,0x00,
0x00,0x3E,0x63,0x3E,0x63,0x3E,0x00,0x00,0x00,0x3E,0x63,0x3F,0x03,0x3E,0x00,0x00,
0x00,0x18,0x18,0x00,0x18,0x18,0x00,0x00,0x00,0x18,0x18,0x00,0x18,0x18,0x10,0x00,
0x00,0x0C,0x18,0x30,0x18,0x0C,0x00,0x00,0x00,0x00,0x3C,0x00,0x3C,0x00,0x00,0x00,
0x00,0x30,0x18,0x0C,0x18,0x30,0x00,0x00,0x00,0x1E,0x33,0x06,0x0C,0x00,0x0C,0x00,
0x3E,0x41,0x5D,0x55,0x5F,0x40,0x3E,0x00,0x00,0x3E,0x63,0x7F,0x63,0x63,0x00,0x00,
0x00,0x7E,0x63,0x7E,0x63,0x7E,0x00,0x00,0x00,0x3F,0x60,0x60,0x60,0x3F,0x00,0x00,
0x00,0x7E,0x63,0x63,0x63,0x7E,0x00,0x00,0x00,0x7F,0x60,0x7C,0x60,0x7F,0x00,0x00,
0x00,0x7F,0x60,0x7C,0x60,0x60,0x00,0x00,0x00,0x3F,0x60,0x67,0x63,0x3F,0x00,0x00,
0x00,0x63,0x63,0x7F,0x63,0x63,0x00,0x00,0x00,0x0C,0x0C,0x0C,0x0C,0x0C,0x00,0x00,
0x00,0x0C,0x0C,0x0C,0x0C,0x38,0x00,0x00,0x00,0x63,0x66,0x7C,0x66,0x63,0x00,0x00,
0x00,0x60,0x60,0x60,0x60,0x7F,0x00,0x00,0x00,0x63,0x77,0x7F,0x6B,0x63,0x00,0x00,
0x00,0x63,0x73,0x7B,0x6F,0x67,0x00,0x00,0x00,0x3E,0x63,0x63,0x63,0x3E,0x00,0x00,
0x00,0x7E,0x63,0x63,0x7E,0x60,0x00,0x00,0x00,0x3E,0x63,0x6B,0x66,0x3D,0x00,0x00,
0x00,0x7E,0x63,0x63,0x7E,0x63,0x00,0x00,0x00,0x3F,0x60,0x3E,0x03,0x7E,0x00,0x00,
0x00,0x7E,0x18,0x18,0x18,0x18,0x00,0x00,0x00,0x63,0x63,0x63,0x63,0x3E,0x00,0x00,
0x00,0x63,0x63,0x63,0x36,0x1C,0x00,0x00,0x00,0x63,0x6B,0x7F,0x77,0x63,0x00,0x00,
0x00,0x63,0x36,0x1C,0x36,0x63,0x00,0x00,0x00,0x66,0x66,0x3C,0x18,0x18,0x00,0x00,
0x00,0x7E,0x0C,0x18,0x30,0x7E,0x00,0x00,0x0E,0x0C,0x0C,0x0C,0x0C,0x0C,0x0E,0x00,
0x00,0x60,0x30,0x18,0x0C,0x06,0x00,0x00,0x38,0x18,0x18,0x18,0x18,0x18,0x38,0x00,
0x10,0x38,0x6C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3E,0x03,0x3F,0x63,0x7F,0x00,0x00,
0x60,0x7E,0x63,0x63,0x63,0x7E,0x00,0x00,0x00,0x3F,0x60,0x60,0x60,0x3F,0x00,0x00,
0x03,0x3F,0x63,0x63,0x63,0x3F,0x00,0x00,0x00,0x3E,0x63,0x7F,0x60,0x3E,0x00,0x00,
0x00,0x3E,0x60,0x78,0x60,0x60,0x00,0x00,0x00,0x3E,0x63,0x63,0x3F,0x03,0x3E,0x00,
0x60,0x7E,0x63,0x63,0x63,0x63,0x00,0x00,0x0C,0x00,0x0C,0x0C,0x0C,0x0C,0x00,0x00,
0x0C,0x00,0x0C,0x0C,0x0C,0x0C,0x38,0x00,0x00,0x60,0x66,0x7C,0x66,0x63,0x00,0x00,
0x18,0x18,0x18,0x18,0x18,0x18,0x00,0x00,0x00,0x7E,0x6B,0x6B,0x6B,0x6B,0x00,0x00,
0x00,0x7E,0x63,0x63,0x63,0x63,0x00,0x00,0x00,0x3E,0x63,0x63,0x63,0x3E,0x00,0x00,
0x00,0x7E,0x63,0x63,0x63,0x7E,0x60,0x00,0x00,0x3F,0x63,0x63,0x63,0x3F,0x03,0x00,
0x00,0x3F,0x60,0x60,0x60,0x60,0x00,0x00,0x00,0x3F,0x60,0x3E,0x03,0x7E,0x00,0x00,
0x18,0x3E,0x18,0x18,0x18,0x0E,0x00,0x00,0x00,0x63,0x63,0x63,0x63,0x3E,0x00,0x00,
0x00,0x63,0x63,0x63,0x36,0x1C,0x00,0x00,0x00,0x63,0x6B,0x6B,0x6B,0x36,0x00,0x00,
0x00,0x66,0x3C,0x18,0x3C,0x66,0x00,0x00,0x00,0x63,0x63,0x63,0x3F,0x03,0x3E,0x00,
0x00,0x7E,0x0C,0x18,0x30,0x7E,0x00,0x00,0x06,0x0C,0x0C,0x18,0x0C,0x0C,0x06,0x00,
0x18,0x18,0x18,0x00,0x18,0x18,0x18,0x00,0x30,0x18,0x18,0x0C,0x18,0x18,0x30,0x00,
0x3C,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x3C};



// ----------------------------------------------------------------------------- Functions


//
void main(void)
{
  char colorInk=0;
  char colorBG=0;
  char colorBDR=0;
  char scrcolumns=0;
  
  colorInk=PEEK(FORCLR);
  colorBG=PEEK(BAKCLR);
  colorBDR=PEEK(BDRCLR);
  scrcolumns=PEEK(LINLEN);
  
    
  test();

  

//EXIT MSXDOS ------------------------------------------------------------------
  //put the screen as it was.
  COLOR(colorInk,colorBG,colorBDR);

  if(scrcolumns<33) SCREEN1();
  else SCREEN0();
  
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



/* =============================================================================
 SCREEN0
 
 Description: 
           Switch to T1 or T2 mode (SCREEN 0), 40 or 80 columns x 24 lines.
           Notice: To set the T2 mode, you must first set 80 columns with the 
           WIDTH instruction.
 Input:    -
 Output:   -
============================================================================= */
void SCREEN0() __naked
{
__asm
  push IX
  
  ld   A,(#LINLEN)
  ld   (#LINL40),A   ;copy columns seting with WIDTH to LINL40 system var
   
  ld   IX,#INITXT
  ld   IY,(EXPTBL-1)
  call CALSLT
  ei
    
  pop  IX
  ret  
__endasm;
}



/* =============================================================================
 SCREEN1
 
 Description: 
           Switch to G1 mode (SCREEN 1), 32 columns x 24 lines.
 Input:    -
 Output:   -
============================================================================= */
void SCREEN1() __naked
{
__asm
  push IX
  
  ld   A,(#LINLEN)   ;get a last value set with WIDTH function 
  ld   (#LINL32),A   ;set system variable
   
  ld   IX,#INIT32
  ld   IY,(EXPTBL-1)
  call CALSLT
  ei
    
  pop  IX
  ret  
__endasm;
}



// TEST ###############################################################
void test()
{
  char A=0;
  char isExit = 0;
  
  COLOR(LIGHT_GREEN,DARK_GREEN,DARK_GREEN);    
  SCREEN(1);

  //copy to VRAM tileset, only gfx patterns
  CopyToVRAM((uint) TILESET_FONT,BASE7,127*8);
  
  CopyToVRAM((uint) Joytest_MAP,BASE5,768);
  
  VPRINT(0,0,text01);
  VPRINT(0,1,text02);
  VPRINT(0,2,"Hold down ESC key to exit to DOS");
  VPRINT(0,3,">Test STICK() & STRIG()");
 
  while(isExit<60)
  {
    HALT;
    
    if (!(GetKeyMatrix(7)&Bit2)) isExit++;
    else isExit=0;
    
    A = STICK(CURSORKEYS);
    printDIR(3,8,A);
    
    if (STRIG(KEYBOARD_BUTTON)==BUTTON_PRESSED) VPRINT(10,10,"~~~~~");
    else VPRINT(10,10,"     "); 
    
    //Joy A
    A = STICK(JOYSTICKA);
    printDIR(3,17,A);

    if (STRIG(JOYSTICKA_BUTTONA)==BUTTON_PRESSED) VPRINT(10,19,"~");
    else VPRINT(10,19," ");

    if (STRIG(JOYSTICKA_BUTTONB)==BUTTON_PRESSED) VPRINT(13,19,"~");
    else VPRINT(13,19," ");
    
    //Joy B
    A = STICK(JOYSTICKB);
    printDIR(18,17,A);      

    if (STRIG(JOYSTICKB_BUTTONA)==BUTTON_PRESSED) VPRINT(25,19,"~");
    else VPRINT(25,19," ");

    if (STRIG(JOYSTICKB_BUTTONB)==BUTTON_PRESSED) VPRINT(28,19,"~");
    else VPRINT(28,19," ");
    
  }
  
}


void printDIR(byte x, byte y, char state)
{
  char up[]=" ";
  char down[]=" ";
  char left[]=" ";
  char right[]=" ";
  
  switch (state) 
  {
    case JOYSTICK_UP:
      up[0]=126;  
      break;
    case JOYSTICK_UP_RIGHT:
      up[0]=126;
      right[0]=126;   
      break;
    case JOYSTICK_RIGHT:
      right[0]=126;   
      break;
    case JOYSTICK_DOWN_RIGHT:
      down[0]=126;
      right[0]=126;   
      break;
    case JOYSTICK_DOWN:
      down[0]=126;  
      break;
    case JOYSTICK_DOWN_LEFT:
      down[0]=126;
      left[0]=126;   
      break;
    case JOYSTICK_LEFT:
      left[0]=126;
      break;
    case JOYSTICK_UP_LEFT:
      up[0]=126;
      left[0]=126;  
      break;
  }
  
  VPRINT(x+2,y,up);//up
  VPRINT(x+2,y+4,down);//down
  VPRINT(x,y+2,left);//left
  VPRINT(x+4,y+2,right);//right 
      
  return;
}

