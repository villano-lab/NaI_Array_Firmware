#include "Def.h"
#include <stdint.h>
#include <stdlib.h>
#include  <stdbool.h>


#pragma once
#ifndef __R5560_SCICOMPILER_H
#define __R5560_SCICOMPILER_H
#endif

#ifdef __cplusplus
extern "C" {
#endif


#ifdef _WIN32
#ifdef SCICOMPILER_EXPORTS
#define SCILIB __declspec(dllexport)
#else
#define SCILIB __declspec(dllimport)
#endif
#else
#ifdef SCICOMPILER_EXPORTS
#define SCILIB __attribute__((visibility("default")))
#else
#define SCILIB
#endif
#endif


#define NI_HANDLE tR5560_Handle

typedef struct
{
	uint64_t Time_Code;
	uint32_t Id;
	uint32_t Pack_Id;
	uint32_t *Energy;
	uint32_t Valid;
} t_FRAME_packet;


typedef struct
{
	t_FRAME_packet *packets;
	int allocated_packets;
	int valid_packets;
} t_FRAME_packet_collection;



typedef struct
{
	int board;
	uint64_t timestamp;
	uint64_t triggerid;
	void *payload;
}t_generic_event;

typedef struct
{
	t_generic_event *packets;
	int allocated_packets;
	int valid_packets;
} t_generic_event_collection;





SCILIB int R_ConnectDevice( char *IPAddress, uint32_t port, NI_HANDLE *handle);
SCILIB int R_CloseConnection(NI_HANDLE *handle);
SCILIB int R_Init();

SCILIB int __abstracted_mem_write(uint32_t *data, uint32_t count, 
										uint32_t address,  
										uint32_t timeout_ms, NI_HANDLE *handle, 
										uint32_t *written_data);

SCILIB int __abstracted_mem_read(uint32_t *data, uint32_t count, 
										uint32_t address, 
										uint32_t timeout_ms, NI_HANDLE *handle, 
										uint32_t *read_data, uint32_t *valid_data);
										

SCILIB int __abstracted_fifo_write(uint32_t *data, uint32_t count,
	uint32_t address,
	uint32_t address_status,
	uint32_t timeout_ms, NI_HANDLE *handle,
	uint32_t *written_data);
	
SCILIB int __abstracted_fifo_read(uint32_t *data, uint32_t count, 
										uint32_t address, 
										uint32_t address_status, 
										bool blocking,
										uint32_t timeout_ms, NI_HANDLE *handle, 
										uint32_t *read_data, uint32_t *valid_data);
SCILIB int __abstracted_reg_write(uint32_t data, uint32_t address, NI_HANDLE *handle);
SCILIB int __abstracted_reg_read(uint32_t *data, uint32_t address, NI_HANDLE *handle);

SCILIB int Utility_PEAK_DATA_FORM_DOWNLOAD_BUFFER(void *buffer_handle, int32_t *val);

SCILIB int Utility_ENQUEUE_DATA_IN_DOWNLOAD_BUFFER(void *buffer_handle, int32_t *val, uint32_t size, uint32_t *enqueued_data);

SCILIB int Utility_ALLOCATE_DOWNLOAD_BUFFER(void **buffer_handle, uint32_t buffer_size);

SCILIB void free_packet_collection(t_generic_event_collection *decoded_packets);

SCILIB void free_FRAME_packet_collectionvoid(t_FRAME_packet_collection *decoded_packets);
SCILIB void free_PETIROCFRAME_packet_collection(t_ASIC_packet_collection *decoded_packets);


SCILIB int ClearBuffer(void *buffer_handle);

#ifdef __cplusplus
}
#endif



SCILIB int REG_ratereset_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_ratereset_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_thrsh_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_thrsh_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_polarity_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_polarity_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_top_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_top_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_gate_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_gate_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_inhib_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_inhib_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_delay_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_delay_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_disable_det_0_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_disable_det_0_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_disable_det_1_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_disable_det_1_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_disable_det_2_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_disable_det_2_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_disable_det_3_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_disable_det_3_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_disable_det_4_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_disable_det_4_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_disable_det_5_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_disable_det_5_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_disable_det_6_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_disable_det_6_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_disable_det_7_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_disable_det_7_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_disable_det_8_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_disable_det_8_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_disable_det_9_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_disable_det_9_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_disable_det_10_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_disable_det_10_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_disable_det_11_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_disable_det_11_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_disable_det_12_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_disable_det_12_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_disable_det_13_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_disable_det_13_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_disable_det_14_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_disable_det_14_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_disable_det_15_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_disable_det_15_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_disable_det_16_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_disable_det_16_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_disable_det_17_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_disable_det_17_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_disable_det_18_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_disable_det_18_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_disable_det_19_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_disable_det_19_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_disable_det_20_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_disable_det_20_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_disable_det_21_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_disable_det_21_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_disable_det_22_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_disable_det_22_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_disable_det_23_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_disable_det_23_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_disable_det_24_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_disable_det_24_SET(uint32_t val, NI_HANDLE *handle);
//-----------------------------------------------------------------
//-
//- RATE_METER_RateMeter_0_GET_DATA
//-
//- USAGE: 
//- 
//-
//- ARGUMENTS:
//- 	             val  PARAM_OUT   uint32_t
//- 		uint32_t buffer data with preallocated size of at list 'size' parameters + 16 word
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//- 	             val   PARAM_IN   channels
//- 		number of word to download from the buffer.
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//- 	             val   PARAM_IN    int32_t
//- 		timeout in ms
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//- 	          handle PARAM_INOUT  NI_HANDLE
//- 		Connection handle to the board
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//- 	       read_data  PARAM_OUT    int32_t
//- 		number of word read from the buffer
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//- 	      valid_data  PARAM_OUT    int32_t
//- 		number of word valid in the buffer
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//-
//- RETURN [int]
//- 	Return if the function has been succesfully executed
//- 		0) Success
//- 		-1) Error
//-
//-----------------------------------------------------------------

SCILIB int RATE_METER_RateMeter_0_GET_DATA(uint32_t *val, uint32_t channels, int32_t timeout, NI_HANDLE *handle, uint32_t *read_data, uint32_t *valid_data);
//-----------------------------------------------------------------
//-
//- RATE_METER_RateMeter_0_GET_DATA_COUNTS
//-
//- USAGE: 
//- 
//-
//- ARGUMENTS:
//- 	             val  PARAM_OUT   uint32_t
//- 		uint32_t buffer data with preallocated size of at list 'size' parameters + 16 word
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//- 	             val   PARAM_IN   channels
//- 		number of word to download from the buffer.
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//- 	             val   PARAM_IN    int32_t
//- 		timeout in ms
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//- 	          handle PARAM_INOUT  NI_HANDLE
//- 		Connection handle to the board
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//- 	       read_data  PARAM_OUT    int32_t
//- 		number of word read from the buffer
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//- 	      valid_data  PARAM_OUT    int32_t
//- 		number of word valid in the buffer
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//-
//- RETURN [int]
//- 	Return if the function has been succesfully executed
//- 		0) Success
//- 		-1) Error
//-
//-----------------------------------------------------------------

SCILIB int RATE_METER_RateMeter_0_GET_DATA_COUNTS(uint32_t *val, uint32_t channels, int32_t timeout, NI_HANDLE *handle, uint32_t *read_data, uint32_t *valid_data);
