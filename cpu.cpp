#include "cpu.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
using namespace std;


void cpu::init(){
	pc = 0x00;
	opcode = 0;
	sr = 0;
	x = true;
	
	for(int i; i < 128; i++){
		R[i] = 0;
	}	
	
	for(int i; i < 256; i++){
		memory[i] = 0;
	}
	
	A = 0;
	cache = 0;
}

void cpu::cycle(){
	
	opcode = memory[pc];
	switch(opcode & 0xF0){
		case 0x00:
			A = R[opcode & 0x0F];
			pc += 1;
			printf("Copied\n");
		break;
		
		case 0x10:
			A = opcode & 0x0F;
			pc += 1;
			printf("Written\n");
		break;
		
		case 0x20:
			R[opcode & 0x0F] = A;
			pc += 1;
			printf("Copied\n");
		break;
		
		case 0x30:
			cache = A + R[opcode & 0x0F];
			A = cache;
			pc += 1;
			printf("Added\n");
		break;
		
		case 0x40:
			cache = A - R[opcode & 0x0F];
			A = cache;
			pc += 1;
			printf("Subtracted\n");
		break;
		
		case 0x50:
			cache = A * R[opcode & 0x0F];
			A = cache;
			pc += 1;
			printf("Multiplied");
		break;
		
		case 0x60:
			cache = A / R[opcode & 0x0F];
			A = cache;
			pc += 1;
			printf("Divided");
		break;
		
		case 0x70:
			pc = opcode & 0x0F;
			printf("Jumped");
		break;
		
		case 0x80:
			if (A >= 0){
				pc = opcode & 0x0F;
				printf("Jumped");
			}			
			else{
				pc += 1;
				printf("Continued");
			}
		break;
		
		case 0x90:
			if (A > 0){
				pc = opcode & 0x0F;
				printf("Jumped");
		}
			else{
				pc += 1;
				printf("Continued");
			}
				
		break;
		
		case 0xA0:
			if (A <= 0){
				pc = opcode & 0x0F;
				printf("Jumped");
			}
			else{
				pc += 1;
				printf("Continued");
			}
		break;
		
		case 0xB0:
			if (A < 0){
				pc = opcode & 0x0F;
				printf("Jumped");
			}
			else{
				pc += 1;
				printf("Continued");
			}
		break;
		
		case 0xC0:
			if (A == 0){
				pc = opcode & 0x0F;
				printf("Jumped");
			}
			else{
				pc += 1;
				printf("Continued");
			}
		break;
		
		case 0xD0:
			if (A != 0){
				pc = opcode & 0x0F;
				printf("Jumped");
			}
			else{
				pc += 1;
				printf("Continued");
			}
		break;
		
		case 0xE0:
			printf("End\n");
			x = false;
			exit(0);
		break;
		
		case 0xF0:
			printf("Output: ");
			cout << static_cast<unsigned>(A) << endl;
			pc += 1;
		break;
		
		
		default:
			printf ("Unknown opcode: 0x%X\n", opcode);
}
			
}

bool cpu::load(const char * filename)
{
	init();
	printf("Loading: %s\n", filename);
		
	// Open file
	FILE * pFile = fopen(filename, "rb");
	if (pFile == NULL)
	{
		fputs ("File error", stderr); 
		return false;
	}

	// Check file size
	fseek(pFile , 0 , SEEK_END);
	long lSize = ftell(pFile);
	rewind(pFile);
	printf("Filesize: %d\n", (int)lSize);
	
	// Allocate memory to contain the whole file
	char * buffer = (char*)malloc(sizeof(char) * lSize);
	if (buffer == NULL) 
	{
		fputs ("Memory error", stderr); 
		return false;
	}

	// Copy the file into the buffer
	size_t result = fread (buffer, 1, lSize, pFile);
	if (result != lSize) 
	{
		fputs("Reading error",stderr); 
		return false;
	}

	// Copy buffer to memory
	if((256) > lSize)
	{
		for(int i = 0; i < lSize; ++i)
			memory[i] = buffer[i];
		while(x = true){
			cycle();
		}
	}
	else
		printf("Error: ROM too big for memory");
	
	
	// Close file, free buffer
	fclose(pFile);
	free(buffer);
	
	

	return true;
}
