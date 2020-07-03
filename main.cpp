#include <stdio.h>
#include <iostream>
#include "cpu.h"
using namespace std;

cpu mycpu;

int main(int argc, char **argv)
{		
	// Load game
	if(!mycpu.load(argv[1]))	
		return 1;
	

}
