#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <scisdk/scisdk_defines.h>
#include <scisdk/SciSDK_DLL.h>
#include <scisdk/NIErrorCode.h>

#define BOARD_SERIAL_NUMBER "13251"


int main(int argc, char* argv[]){
	void *handle = SCISDK_InitLib();
	int ret;
	uint32_t    val;


	int adddevice = SCISDK_AddNewDevice( "usb:13251", "DT1260","RegisterFile.json", "board0", handle);
	printf("Add device:%d\n",adddevice);
	if(adddevice != 0){
		printf("Unable to create device.\n");
		return(adddevice);
	}
	
	return 0;
}
