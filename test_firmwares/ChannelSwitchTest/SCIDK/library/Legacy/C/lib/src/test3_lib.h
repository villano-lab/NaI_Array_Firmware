#include "RegisterFile.h"
#include "Def.h"
#include <stdint.h>
#include <stdlib.h>
#include  <stdbool.h>

#ifdef __cplusplus
#ifdef SCICOMPILER_EXPORTS
#define SCILIB extern "C" __declspec(dllexport) 
#else
#define SCILIB extern "C" __declspec(dllimport)
#endif
#else
#define SCILIB __declspec(dllexport) 
#endif

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


SCILIB int USB2_ListDevices(char *ListOfDevice, char *model,  int *Count);
SCILIB int USB2_ConnectDevice(char *serial_number, NI_HANDLE *handle);
SCILIB int USB2_CloseConnection(NI_HANDLE *handle);

SCILIB int __abstracted_mem_write(uint32_t *data, uint32_t count, 
										uint32_t address,  
										uint32_t timeout_ms, NI_HANDLE *handle, 
										uint32_t *written_data);
SCILIB int __abstracted_fifo_read(uint32_t *data, uint32_t count, 
										uint32_t address, 
										uint32_t timeout_ms, NI_HANDLE *handle, 
										uint32_t *read_data, uint32_t *valid_data);
SCILIB int __abstracted_fifo_write(uint32_t *data, uint32_t count, 
										uint32_t address,  
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

SCILIB void free_FRAME_packet_collectionvoid(t_FRAME_packet_collection *decoded_packets);
SCILIB void free_packet_collection(t_generic_event_collection *decoded_packets);

SCILIB int IICUser_OpenControllerInit(uint32_t ControlAddress, uint32_t StatusAddress, NI_HANDLE *handle,  NI_IIC_HANDLE *IIC_Handle);
SCILIB int IICUser_ReadData(uint8_t address, uint8_t *value, int len, uint8_t *value_read, int len_read, NI_IIC_HANDLE *IIC_Handle);
SCILIB int IICUser_WriteData(uint8_t address, uint8_t *value, int len, NI_IIC_HANDLE *IIC_Handle);

SCILIB char *ReadFirmwareInformation(NI_HANDLE *handle);























typedef struct  {
    uint32_t row[2];
}t_CP_0_struct;



SCILIB int REG_CN_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_CN_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_pol_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_pol_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_thrs_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_thrs_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_inhib_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_inhib_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_top_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_top_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_delay_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_delay_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_gate_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_gate_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_gatel_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_gatel_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_xdelay_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_xdelay_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_inttime_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_inttime_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_preint_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_preint_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_pileup_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_pileup_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_gain_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_gain_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_ofs_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_ofs_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_bl_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_bl_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_noflip0flip1_GET(uint32_t *val, NI_HANDLE *handle);
SCILIB int REG_noflip0flip1_SET(uint32_t val, NI_HANDLE *handle);
SCILIB int REG_ANALOG_OFFSET_SET(uint32_t val, NI_HANDLE *handle);
//-----------------------------------------------------------------
//-
//- SPECTRUM_Spectrum_0_START
//-
//- Start acquisition.
//-
//- ARGUMENTS:
//- 	          handle PARAM_INOUT  NI_HANDLE
//- 		Connection handle to the board
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

SCILIB int SPECTRUM_Spectrum_0_START(NI_HANDLE *handle)
;
//-----------------------------------------------------------------
//-
//- SPECTRUM_Spectrum_0_STOP
//-
//- Stop acquisition.
//-
//- ARGUMENTS:
//- 	          handle PARAM_INOUT  NI_HANDLE
//- 		Connection handle to the board
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

SCILIB int SPECTRUM_Spectrum_0_START(NI_HANDLE *handle)
;
//-----------------------------------------------------------------
//-
//- SPECTRUM_Spectrum_0_FLUSH
//-
//- Flush spectrum
//-
//- ARGUMENTS:
//- 	          handle PARAM_INOUT  NI_HANDLE
//- 		Connection handle to the board
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

SCILIB int SPECTRUM_Spectrum_0_START(NI_HANDLE *handle)
;
//-----------------------------------------------------------------
//-
//- SPECTRUM_Spectrum_0_RESET
//-
//- RESET spectrum
//-
//- ARGUMENTS:
//- 	          handle PARAM_INOUT  NI_HANDLE
//- 		Connection handle to the board
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

SCILIB int SPECTRUM_Spectrum_0_START(NI_HANDLE *handle)
;
//-----------------------------------------------------------------
//-
//- SPECTRUM_Spectrum_0_SET_PARAMETERS
//-
//- Configure oscilloscope parameters
//-
//- ARGUMENTS:
//- 	           rebin   PARAM_IN    int32_t
//- 		Rebin factor
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//- 	      limit_mode   PARAM_IN    int32_t
//- 		Limit Mode: 0) No Limit, 1) Total Counts, 2) Real Time
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//- 	     limit_value   PARAM_IN    int32_t
//- 		Limit value: in counts or in ms depends on limit mode
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//- 	          handle PARAM_INOUT  NI_HANDLE
//- 		Connection handle to the board
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

SCILIB int SPECTRUM_Spectrum_0_SET_PARAMETERS(int32_t rebin, int32_t limit_mode, int32_t limit_value, NI_HANDLE *handle);
;
//-----------------------------------------------------------------
//-
//- SPECTRUM_Spectrum_0_STATUS
//-
//- Get Spectrum status
//-
//- ARGUMENTS:
//- 	          status  PARAM_OUT    int32_t
//- 		Return the oscilloscope status
//- 		DEFAULT: 
//- 		OPTIONAL: False
//- 		0) Stop
//- 		1) Running
//-
//- 	          handle PARAM_INOUT  NI_HANDLE
//- 		Connection handle to the board
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

SCILIB int SPECTRUM_Spectrum_0_STATUS(uint32_t *status,NI_HANDLE *handle);
//-----------------------------------------------------------------
//-
//- SPECTRUM_Spectrum_0_DOWNLOAD
//-
//- Download data from buffer. Please note that downloaded data is not time ordered and the trigger position info data must be obtained using the OSCILLOSCOPE_Spectrum_0POSITION function 
//- 
//- USAGE: 
//-     OSCILLOSCOPE_Spectrum_0_DOWNLOAD(data_buffer, BUFFER_SIZE_Spectrum_0, 1000, handle, rd, vp);
//- 
//-
//- ARGUMENTS:
//- 	             val  PARAM_OUT   uint32_t
//- 		uint32_t buffer data with preallocated size of at list 'size' parameters + 16 word
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//- 	             val   PARAM_IN       size
//- 		number of word to download from the buffer. Use macro BUFFER_SIZE_Spectrum_0 to get actual oscilloscope buffer size on FPGA
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

SCILIB int SPECTRUM_Spectrum_0_DOWNLOAD(uint32_t *val, uint32_t size, int32_t timeout, NI_HANDLE *handle, uint32_t *read_data, uint32_t *valid_data);
//-----------------------------------------------------------------
//-
//- LISTMODULE_Digitizer_0_RESET
//-
//- Clear list content
//-
//- ARGUMENTS:
//- 	          handle PARAM_INOUT  NI_HANDLE
//- 		Connection handle to the board
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

SCILIB int LISTMODULE_Digitizer_0_RESET(NI_HANDLE *handle)
;
//-----------------------------------------------------------------
//-
//- LISTMODULE_Digitizer_0_START
//-
//- Start List acquisition. The list is automatically flushed upon start operation. The function set the number of acquired channels
//-
//- ARGUMENTS:
//- 	          handle PARAM_INOUT  NI_HANDLE
//- 		Connection handle to the board
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

SCILIB int LISTMODULE_Digitizer_0_START(NI_HANDLE *handle, int nchannels)
;
//-----------------------------------------------------------------
//-
//- LISTMODULE_Digitizer_0_SetLen
//-
//- Start List acquisition. The list is automatically flushed upon start operation. The function set the number of acquired channels
//-
//- ARGUMENTS:
//- 	          handle PARAM_INOUT  NI_HANDLE
//- 		Connection handle to the board
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

SCILIB int LISTMODULE_Digitizer_0_SetLen(NI_HANDLE *handle, int length)
;
//-----------------------------------------------------------------
//-
//- LISTMODULE_Digitizer_0_STATUS
//-
//- Get List status
//-
//- ARGUMENTS:
//- 	          status  PARAM_OUT    int32_t
//- 		Return the oscilloscope status
//- 		DEFAULT: 
//- 		OPTIONAL: False
//- 		0) No data available
//- 		1) Data available
//-
//- 	          handle PARAM_INOUT  NI_HANDLE
//- 		Connection handle to the board
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

SCILIB int LISTMODULE_Digitizer_0_STATUS(uint32_t *status, NI_HANDLE *handle)
;
//-----------------------------------------------------------------
//-
//- LISTMODULE_Digitizer_0_DOWNLOAD
//-
//- Download data from fifo buffer. If data are not available the command stall until the timout occuredUSAGE: 
//-     LISTMODULE_Digitizer_0_DOWNLOAD(data_buffer, BUFFER_SIZE_Digitizer_0, 1000, handle, rd, vp);
//- 
//-
//- ARGUMENTS:
//- 	             val  PARAM_OUT   uint32_t
//- 		uint32_t buffer data with preallocated size of at list 'size' parameters + 16 word
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//- 	            size   PARAM_IN   uint32_t
//- 		number of word to download from the buffer.
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//- 	         timeout   PARAM_IN    int32_t
//- 		timeout in ms
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//- 	          handle PARAM_INOUT  NI_HANDLE
//- 		Connection handle to the board
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//- 	       read_data  PARAM_OUT   uint32_t
//- 		number of word read from the buffer
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//- 	      valid_data  PARAM_OUT   uint32_t
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

SCILIB int LISTMODULE_Digitizer_0_DOWNLOAD(uint32_t *val, uint32_t size, int32_t timeout, NI_HANDLE *handle, uint32_t *read_data, uint32_t *valid_data)
;
//-----------------------------------------------------------------
//-
//- CPACK_CP_0_START
//-
//- Start acquisition.
//-
//- ARGUMENTS:
//- 	          handle PARAM_INOUT  NI_HANDLE
//- 		Connection handle to the board
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

SCILIB int CPACK_CP_0_START(NI_HANDLE *handle)
;
//-----------------------------------------------------------------
//-
//- CPACK_CP_0_STOP
//-
//- Start acquisition.
//-
//- ARGUMENTS:
//- 	          handle PARAM_INOUT  NI_HANDLE
//- 		Connection handle to the board
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

SCILIB int CPACK_CP_0_STOP(NI_HANDLE *handle)
;
//-----------------------------------------------------------------
//-
//- CPACK_CP_0_RESET
//-
//- Reset counters and FIFO
//-
//- ARGUMENTS:
//- 	          handle PARAM_INOUT  NI_HANDLE
//- 		Connection handle to the board
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

SCILIB int CPACK_CP_0_RESET(NI_HANDLE *handle);
//-----------------------------------------------------------------
//-
//- CPACK_CP_0_FLUSH
//-
//- Clear Fifo Content
//-
//- ARGUMENTS:
//- 	          handle PARAM_INOUT  NI_HANDLE
//- 		Connection handle to the board
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

SCILIB int CPACK_CP_0_FLUSH(NI_HANDLE *handle);
//-----------------------------------------------------------------
//-
//- CPACK_CP_0_STATUS
//-
//- Get status
//-
//- ARGUMENTS:
//- 	          status  PARAM_OUT    int32_t
//- 		Return the status:
//- 		DEFAULT: 
//- 		OPTIONAL: False
//- 		bit[0] = 0) No data available
//- 		bit[0] = 1) Data available
//- 		bit[1] = 1) Running
//- 		bit[2] = 1) Full
//-
//- 	          handle PARAM_INOUT  NI_HANDLE
//- 		Connection handle to the board
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

SCILIB int CPACK_CP_0_STATUS(uint32_t *status,NI_HANDLE *handle);
//-----------------------------------------------------------------
//-
//- CPACK_CP_0_DATA_AVAILABLE
//-
//- Return number of word available in the FIFO
//-
//- ARGUMENTS:
//- 	          status  PARAM_OUT    int32_t
//- 		Return the status (1) data available (0) no data
//- 		DEFAULT: 
//- 		OPTIONAL: False
//- 		bit[0] = 0) No data available
//- 		bit[0] = 1) Data available
//- 		bit[1] = 1) Running
//- 		bit[2] = 1) Full
//-
//- 	          handle PARAM_INOUT  NI_HANDLE
//- 		Connection handle to the board
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

SCILIB int CPACK_CP_0_DATA_AVAILABLE(uint32_t *status,NI_HANDLE *handle);
//-----------------------------------------------------------------
//-
//- CPACK_CP_0_DOWNLOAD
//-
//- Download data from buffer. Data in the buffer respect the packet layout defined in the Packet Creator Tool
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
//- 	             val   PARAM_IN       size
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

SCILIB int CPACK_CP_0_DOWNLOAD(uint32_t *val, uint32_t size, int32_t timeout, NI_HANDLE *handle, uint32_t *read_data, uint32_t *valid_data);
//-----------------------------------------------------------------
//-
//- CPACK_CP_0_RECONSTRUCT_DATA
//-
//- Take in input a circular buffer (buffer_handle) allocated with the function Utility_ALLOCATE_DOWNLOAD_BUFFER 
//- And filled with downloaded data Utility_ENQUEUE_DATA_IN_DOWNLOAD_BUFFER And decoded the packet  
//- created with the Image (Frame Transfer block).
//- The function internally allocate the output data structure t_FRAME_packet_collection And fill it with packed data
//- decoded. Release the memory allocated by the function with free_FRAME_packet_collectionvoid(buffer) function
//- in order to avoid memory leakage
//- ----------------------------------------
//- USAGE: 
//-   t_FRAME_packet_collection decoded_packets; 
//-   uint32_t data_frame[100000]; 
//-   void *BufferDownloadHandler = NULL;
//- 
//-   Utility_ALLOCATE_DOWNLOAD_BUFFER(&BufferDownloadHandler, 1024*1024);
//-   .... initialize frame transfer ....
//-   while (1){
//-     CPACK_CP0_DOWNLOAD(&data_frame, N_Packet * (PacketSize), timeout_frame, &handle, &read_data_frame, &valid_data_frame); 
//-     Utility_ENQUEUE_DATA_IN_DOWNLOAD_BUFFER(BufferDownloadHandler, data_frame, valid_data_frame, &valid_data_enqueued); 
//-     if (CPACK_CP_0_RECONSTRUCT_DATA(BufferDownloadHandler, &decoded_packets) == 0) { 
//-         .... process data contained in decoded_packets....
//-         free_FRAME_packet_collectionvoid(&decoded_packets);
//-     }
//- 
//- 
//- 
//- 
//- THIS FUNCTION MUST BE CONFIGURED IN FUNCTION OF THE PACKET LAYOUT DEFINED IN THE TOOL!
//- 
//- 
//- 
//- This Is just the skeleton for the decoded function!
//- In the state 3 of the thate machine in the code the packet decoder extract every line from the packet
//- for example if the payload of your packet Is 8 channels of 16 bits alligned 2 channels per row
//- 1:   0xFFFFFFFF      %%HEADER                            Decoded in state 0
//- 2:   0xtttttttt      %%TIMECODE                          Decoded in state 1
//- 3:   0xpppppppp      %%PACKET COUNTER                    Decoded in state 2
//- 4:   IN1    IN2      %%16 BIT DATA * 2 Channels          Decoded in state 3
//- 5:   IN3    IN4      %%16 BIT DATA * 2 Channels          Decoded in state 3
//- 6:   IN5    IN6      %%16 BIT DATA * 2 Channels          Decoded in state 3
//- 7:   IN7    IN7      %%16 BIT DATA * 2 Channels          Decoded in state 3
//- <<<NUMBER OF PACKET LINES AFTER THE HEADER HERE>>> must be set to 4 (the line containing the payload 4...7)
//- You can change the state machine in an arbitrary way in order to correctly decode packets and extract every single channels
//- This function example works as is for the following packet format
//- 1:   0xFFFFFFFF      %%HEADER                            Decoded in state 0
//- 2:   0xtttttttt      %%TIMECODE                          Decoded in state 1
//- 3:   0xpppppppp      %%PACKET COUNTER                    Decoded in state 2
//- 4:   IN1             %%32 BIT DATA                       Decoded in state 3
//- 5:   IN2             %%32 BIT DATA                       Decoded in state 3
//- 6:   IN3             %%32 BIT DATA                       Decoded in state 3
//- 7:   IN4             %%32 BIT DATA                       Decoded in state 3
//- 
//-
//- ARGUMENTS:
//- 	   buffer_handle   PARAM_IN       void
//- 		void pointer to the allocated memory area
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//- 	 decoded_packets  PARAM_OUT t_FRAME_packet_collection
//- 		Output vector containing the decoded data
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

SCILIB int CPACK_CP_0_RECONSTRUCT_DATA(void *buffer_handle, t_generic_event_collection *decoded_packets);
