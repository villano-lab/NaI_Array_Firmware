#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <dlfcn.h>
#include "SCIDK_Lib.h"
#include "../scisdk_rebuild/scisdk_defines.h"
#include "../scisdk_rebuild/SciSDK_DLL.h"
#include "../scisdk_rebuild/NIErrorCode.h"
#include "../scisdk_rebuild/scisdk_core.h"
#include "Legacy/R76Replica_lib.h"
//#include "UniversalTriggerShared.h"

//#define BOARD_SERIAL_NUMBER "13251"
//HINSTANCE h_lib_instance = dlopen("./scisdk_rebuild/caen_feelib.so", RTLD_LAZY); //sigsegv

char board_address[14] = "usb:13251";//"usb:0403:6001";
char model[7] = "DT1260";
char regfileloc[24] = "../../RegisterFile.json";
char name[6] = "SCIDK";
char serial[6] = "13251";

int adddevice;

int main(int argc, char* argv[]){
	SciSDK sdk; //this has to be here instead of global scope? magic.
	NI_HANDLE *test_handle;
        SciSDK* _sdk = new SciSDK;
	SciSDK* _sdk2 = new SciSDK;
	//_sdk = (SciSDK*)test_handle;

	//int adddevice = SCISDK_AddNewDevice(board_address,model,regfileloc,name,&test_handle);
	/*SciSDK* _sdk = (SciSDK*)test_handle;
	_sdk->AddNewDevice(board_address,model,regfileloc,name);//*/

	/*uint32_t (*connectUSB)(char*, NI_HANDLE*);
	// *(void**)(&connectUSB) = dlsym(h_lib_instance, "SCIDK_ConnectUSB");
	connectUSB = SCIDK_ConnectUSB;

	adddevice = connectUSB(serial,&test_handle);
	std::cout << "returned " << adddevice << " when following instructions;\n";
	adddevice = connectUSB((char*)"0403",&test_handle);
	std::cout << "returned " << adddevice << " when following code;\n";
	adddevice = connectUSB((char*)"0403:6001",&test_handle);
	std::cout << "returned " << adddevice << " when following attempt.\n";// */
	std::cout << sizeof(SciSDK*) << ", " << sizeof(NI_HANDLE*) << std::endl;
	std::cout << _sdk << ", " << std::endl; //test_handle << std::endl;

	/*std::cout << "====================\n";
	std::cout << "dev size: " << _sdk->devs.size() << std::endl;// */
	//adddevice = sdk.AddNewDevice(board_address,model,regfileloc,name);
	//adddevice = _sdk->AddNewDevice(board_address,model,regfileloc,name); //good one
	//std::cout << test_handle << ", " << sdk << std::endl;
	adddevice = SCIDK_ConnectUSB(serial,(NI_HANDLE*)_sdk2);
	std::cout << "dev size: ";
	std::cout << sdk.devs.size() << std::endl;
	std::cout << "====================\n" << adddevice << std::endl << std::endl;

	uint32_t value = 5;
	std::cout << value << std::endl;
	NI_WriteReg(0,0xFFFFFFFF,(NI_HANDLE*)_sdk2);
        NI_ReadReg(&value,0xFFFFFFFF,(NI_HANDLE*)_sdk2);

        //std::cout << "Attempting register set.\n";
	//test_handle = &sdk; //already done */
        value = REG_reset_SET(1,(NI_HANDLE*)_sdk2); //segfault
	std::cout << value << std::endl;// */

	//SciSDK_Device* retval = sdk.FindDeviceByName(name); //runs ok but doesn't seem to do anything when called this way.
	//std::cout << retval << std::endl;
	return adddevice;
}
