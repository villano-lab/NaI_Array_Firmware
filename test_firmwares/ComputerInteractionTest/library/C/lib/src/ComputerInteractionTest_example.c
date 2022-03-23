#include "Def.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include  "ComputerInteractionTest_lib.h"

#define BOARD_IP_ADDRESS "134.84.150.42"




int main(int argc, char* argv[])
{
	NI_HANDLE handle;
	int ret;
	uint32_t    val;


	R_Init();


	if(R_ConnectDevice(BOARD_IP_ADDRESS, 8888, &handle) != 0) { printf("Unable to connect to the board!\n"); return (-1); };
#ifndef CUSTOM_EXAMPLE		
	
	

	
#else

#endif
uint32_t data = 2;
printf("%d\n",data);

while(1){
	ret = REG_integral_GET(&data, &handle);
	printf("%d\n",ret);
	printf("%d\n",data);
}
	return 0;
}

 
