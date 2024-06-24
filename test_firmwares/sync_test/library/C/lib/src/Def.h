#include <windows.h>
#include <stdlib.h>
#include <stdbool.h>
#pragma once


typedef enum 
{
	NOT_CONNECTED = 0,
	CONNECTED = 1
}USB_CONNECTION_STATUS ;


typedef struct NI_HANDLE
{
	void  *device_handle;
	USB_CONNECTION_STATUS connection_status;
}NI_HANDLE;

typedef enum 
{
	REG_ACCESS = 0,
	STREAMING = 1
} USB_BUS_MODE;


typedef struct NI_IIC_HANDLE
{
	NI_HANDLE *dev_con;
	uint32_t __IICBASEADDRESS;
	uint32_t __IICBASEADDRESS_STATUS;
} NI_IIC_HANDLE;
