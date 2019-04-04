/*****************************************************************************
* Filename:          D:\work\lprs2\2013_2014\Resene_vezbe\lab56\basic_system/drivers/vga_periph_mem_v1_00_a/src/vga_periph_mem.c
* Version:           1.00.a
* Description:       vga_periph_mem Driver Source File
* Date:              Wed Mar 05 10:25:21 2014 (by Create and Import Peripheral Wizard)
*****************************************************************************/


/***************************** Include Files *******************************/

#include "vga_periph_mem.h"
Xuint32 cursor_position;
/************************** Function Definitions ***************************/

void set_cursor(Xuint32 new_value){
	cursor_position = new_value;
}

void clear_text_screen(Xuint32 BaseAddress){
	int i;
	for (i = 0; i < 4800; i++){
		VGA_PERIPH_MEM_mWriteMemory(BaseAddress + TEXT_MEM_OFF + i*4, 0x20);//text_ooff
	}
}

void print_char(Xuint32 BaseAddress,unsigned char sign){
	VGA_PERIPH_MEM_mWriteMemory(BaseAddress + TEXT_MEM_OFF + cursor_position, sign);
}

void print_string(Xuint32 BaseAddress, unsigned char string_s[], int lenght){
	int i;
	for (i = 0; i < lenght; i++){
		VGA_PERIPH_MEM_mWriteMemory(BaseAddress + TEXT_MEM_OFF + cursor_position + i*4, (string_s[i]-0x40));
	}
}

void clear_graphics_screen(Xuint32 BaseAddress){
	int i;
	for (i = 0; i < 9600; i++){
	    VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + i*4, 0x0);
	}
}

void clear_screen(Xuint32 BaseAddress){
	int i;
		for (i = 0; i < 4800; i++){
			VGA_PERIPH_MEM_mWriteMemory(BaseAddress + TEXT_MEM_OFF + i*4, 0x20);//text_ooff
		}
		for (i = 0; i < 9600; i++){
		    VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + i*4, 0x0);
		}


}

void set_foreground(Xuint32 BaseAddress,long color){
	 VGA_PERIPH_MEM_mWriteMemory( BaseAddress + 0x10, color);
}

void set_background(Xuint32 BaseAddress,long color){
	 VGA_PERIPH_MEM_mWriteMemory( BaseAddress + 0x14, color);
}



void draw_square(Xuint32 BaseAddress){
	int i, j, k;
		for (j = 0; j < 480; j++){
			for (k = 0; k<(640/32); k++){
				i = j*(640/32) + k;
				if ((j > 200) && (j < 280) && (k > 8) && (k < 12)) {
					VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + i*4, 0xFFFFFFFF);
				}
				else{
					VGA_PERIPH_MEM_mWriteMemory(BaseAddress + GRAPHICS_MEM_OFF + i*4, 0x0);
				}
			}
		}
}

void move(Xuint32 BaseAddress,unsigned char string_s[],int length){
	int i;
	int j;
	for(j=0;j<500;j++){

		clear_text_screen(BaseAddress);
		print_string(BaseAddress,string_s,length);
		for(i=0;i<1000000;i++);
		//VGA_PERIPH_MEM_mWriteMemory(BaseAddress + TEXT_MEM_OFF + cursor_position + i*4 +j*4-1, 0x20 );
		set_cursor(cursor_position+1);
	}
}
