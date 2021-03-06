// TestLibUdis86.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "udis86.h"


int _tmain(int argc, _TCHAR* argv[])
{
	/*
	00401423 >/$  68 98204000   push    00402098                         ;  ASCII "Hello world!"
	00401428  |.  68 04304000   push    00403004
	0040142D  |.  E8 2E010000   call    00401560
	00401432  |.  83C4 08       add     esp, 8
	00401435  |.  68 04304000   push    00403004
	0040143A  |.  E8 21000000   call    00401460
	0040143F  |.  68 A5204000   push    004020A5                         ; /pModule = "kernel32.dll"
	00401444  |.  E8 CD000000   call    <jmp.&KERNEL32.GetModuleHandleA> ; \GetModuleHandleA
	00401449  |.  A3 00304000   mov     dword ptr [403000], eax
	0040144E  |.  FF35 00304000 push    dword ptr [403000]
	00401454  |.  E8 6BFFFFFF   call    004013C4
	00401459  |.  50            push    eax                              ; /ExitCode
	*/
	char data[125] = {
		0x68, 0x98, 0x20, 0x40, 0x00, 0x68, 0x04, 0x30, 0x40, 0x00, 0xE8, 0x2E, 0x01, 0x00, 0x00, 0x83,
		0xC4, 0x08, 0x68, 0x04, 0x30, 0x40, 0x00, 0xE8, 0x21, 0x00, 0x00, 0x00, 0x68, 0xA5, 0x20, 0x40,
		0x00, 0xE8, 0xCD, 0x00, 0x00, 0x00, 0xA3, 0x00, 0x30, 0x40, 0x00, 0xFF, 0x35, 0x00, 0x30, 0x40,
		0x00, 0xE8, 0x6B, 0xFF, 0xFF, 0xFF, 0x50, 0xE8, 0xAB, 0x00, 0x00, 0x00, 0xC3, 0x8B, 0x44, 0x24,
		0x04, 0x6A, 0x00, 0x6A, 0x00, 0x50, 0x6A, 0x00, 0xFF, 0x15, 0x38, 0x20, 0x40, 0x00, 0xC2, 0x04,
		0x00, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0xFF, 0x25, 0x90,
		0x20, 0x40, 0x00, 0xFF, 0x25, 0x88, 0x20, 0x40, 0x00, 0xFF, 0x25, 0x84, 0x20, 0x40, 0x00, 0xFF,
		0x25, 0x80, 0x20, 0x40, 0x00, 0xFF, 0x25, 0x7C, 0x20, 0x40, 0x00, 0xFF, 0x25
	};

	ud ud_obj;  
	ud_init(&ud_obj);  //初始化结构体
	ud_set_mode(&ud_obj, 32); //设置为32位cpu
	ud_set_syntax(&ud_obj, UD_SYN_INTEL); //汇编语法为intel语法
	ud_set_pc(&ud_obj, 0x00401423); //设置反汇编的基址
	ud_set_input_buffer(&ud_obj, (uint8_t*)data, sizeof(data)); //设置反汇编的机器码
	unsigned int  nLen = 0; 
	while ((nLen = ud_disassemble(&ud_obj) != 0))//反汇编一条指令
	{
		char szdisasmBuff[0xff] = { 0 };
		strcpy(szdisasmBuff, ud_insn_asm(&ud_obj));
		printf(szdisasmBuff);
	}
	

	return 0;
}

