#include "SCIDK_Lib.h"
#include  <stdlib.h>
#include <stdint.h>
#include  <stdbool.h>

#include "RegisterFile.h"

#include  "circular_buffer.h"



#include  "TrigTest6_lib.h"


SCILIB int USB2_ConnectDevice( char *IPAddress_or_SN, NI_HANDLE *handle)
{
	return SCIDK_ConnectUSB( IPAddress_or_SN, handle);
}

SCILIB int USB2_CloseConnection(NI_HANDLE *handle)
{
	return NI_CloseConnection(handle);
}

SCILIB int USB2_ListDevices(char *ListOfDevice, char *model,  int *Count)
{
	return NI_USBEnumerate(ListOfDevice, model, Count);
}

SCILIB int __abstracted_mem_write(uint32_t *data, uint32_t count, 
										uint32_t address, 
										uint32_t timeout_ms, NI_HANDLE *handle, 
										uint32_t *written_data)
{
	return NI_WriteData(data,  count,  address, REG_ACCESS, timeout_ms, handle, written_data);
}


SCILIB int __abstracted_mem_read(uint32_t *data, uint32_t count, 
										uint32_t address, 
										uint32_t timeout_ms, NI_HANDLE *handle, 
										uint32_t *read_data, uint32_t *valid_data)
{
	return NI_ReadData(data,  count, address,  REG_ACCESS, timeout_ms, handle, read_data, valid_data);
}

SCILIB int __abstracted_fifo_write(uint32_t *data, uint32_t count, 
										uint32_t address, 
										uint32_t timeout_ms, NI_HANDLE *handle, 
										uint32_t *written_data)
{
	return NI_WriteData(data,  count,  address, STREAMING, timeout_ms, handle, written_data);
}
	
SCILIB int __abstracted_fifo_read(uint32_t *data, uint32_t count, 
										uint32_t address, 
										uint32_t address_status, 
										bool blocking,
										uint32_t timeout_ms, NI_HANDLE *handle, 
										uint32_t *read_data, uint32_t *valid_data)
{
	return NI_ReadData(data,  count, address,  STREAMING, timeout_ms, handle, read_data, valid_data);
}
	
SCILIB int __abstracted_reg_write(uint32_t data, uint32_t address, NI_HANDLE *handle)
{
	return NI_WriteReg(data, address, handle);
}

SCILIB int __abstracted_reg_read(uint32_t *data, uint32_t address, NI_HANDLE *handle)
{
	return NI_ReadReg(data,  address,  handle);
}


SCILIB int IICUser_OpenControllerInit(uint32_t ControlAddress, uint32_t StatusAddress, NI_HANDLE *handle, NI_IIC_HANDLE *IIC_Handle)
{
	return NI_IICUser_OpenController(ControlAddress, StatusAddress, handle, IIC_Handle);
}

SCILIB int IICUser_ReadData(uint8_t address, uint8_t *value, int len, uint8_t *value_read, int len_read, NI_IIC_HANDLE *IIC_Handle)
{
	return NI_IICUser_ReadData(address, value, len, value_read, len_read, IIC_Handle);
}

SCILIB int IICUser_WriteData(uint8_t address, uint8_t *value, int len, NI_IIC_HANDLE *IIC_Handle)
{
	return NI_IICUser_WriteData(address, value, len, IIC_Handle);
}

SCILIB char *ReadFirmwareInformation(NI_HANDLE *handle)
{
	return ReadFirmwareInformationApp(handle);
}



//-----------------------------------------------------------------
//-
//-  Utility_ALLOCATE_DOWNLOAD_BUFFER
//-
//-	 This function take as input a pointer to a buffer handle (not pre-allocated void*) and fill it
//-  with the pointer to the circular buffer to store data acquired from a board FIFO that is waiting
//-  to be processed.
//-  The buffer_size specify the size of the buffer to be allocated
//-  ARGUMENTS:
//- 	            buffer_handle   PARAM_OUT   void ** 
//-			Handle to the buffer
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-  
//- 	            buffer_size   PARAM_IN   uint32_t
//- 		size in word (32 bit) of the buffer to be allocated
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-  
//-  RETURN [int]
//- 	Return if the function has been succesfully executed
//- 		0) Success
//- 		-1) Error
//-
//-  EXAMPLE:
//-
//-		void *BufferDownloadHandler = NULL;
//-		Utility_ALLOCATE_DOWNLOAD_BUFFER(&BufferDownloadHandler, 1024*1024);
//-----------------------------------------------------------------

SCILIB int Utility_ALLOCATE_DOWNLOAD_BUFFER(void **buffer_handle, uint32_t buffer_size)
{
	uint32_t * buffer = malloc(buffer_size * sizeof(uint32_t));
	if (buffer == NULL) return -1;
	cbuf_handle_t cbuf = circular_buf_init(buffer, buffer_size);
	*buffer_handle = cbuf;
	return 0;
}




//-----------------------------------------------------------------
//-
//-  Utility_ENQUEUE_DATA_IN_DOWNLOAD_BUFFER
//-
//-	 This function take as input a pointer to a buffer handle allocated with the function 
//-  Utility_ALLOCATE_DOWNLOAD_BUFFER and fill it with the content of the array val
//-  If the buffer is full the function fails and the output parameter 
//-  The buffer_size specify the size of the buffer to be allocated enqueued_data willl
//-	 contain the number of word that has been enqueued in the buffer
//-
//-  ARGUMENTS:
//- 	            buffer_handle   PARAM_IN   void *
//-			Handle to the buffer
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-  
//- 	            val			   PARAM_IN   uint32_t *
//-			input data vector downloaded from a FIFO from the board
//- 		DEFAULT: 
//- 		OPTIONAL: False
//- 
//- 	            size   			PARAM_IN   uint32_t 
//- 		number of valid word in the val vector
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-  
//- 	            enqueued_data   PARAM_OUT   uint32_t *
//-			number of word of the val vector really enqueued in the circular buffer
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//-  RETURN [int]
//- 	Return if the function has been succesfully executed
//- 		0) Success
//- 		-1) Not all word enqueued in the buffer
//-
//-  EXAMPLE:
//-
//-		FRAME_ImageReadout_0_DOWNLOAD(&data_frame, N_Packet * (9+4), timeout_frame, &handle, &read_data_frame, &valid_data_frame);
//-		Utility_ENQUEUE_DATA_IN_DOWNLOAD_BUFFER(BufferDownloadHandler, data_frame, valid_data_frame, &valid_data_enqueued);
//-----------------------------------------------------------------

SCILIB int Utility_ENQUEUE_DATA_IN_DOWNLOAD_BUFFER(void *buffer_handle, int32_t *val, uint32_t size, uint32_t *enqueued_data)
{
	cbuf_handle_t cbuf;
	uint32_t i;
	uint32_t data_counter=0;
	cbuf = ((cbuf_handle_t)buffer_handle);
	for (i = 0; i < size; i++)
	{
		if (circular_buf_full(cbuf))
		{
			*enqueued_data = data_counter;
			return -1;
		}
		data_counter++;
		circular_buf_put(cbuf, val[i]);
	}
	*enqueued_data = data_counter;
	return 0;
}


//-----------------------------------------------------------------
//-
//-  Utility_PEAK_DATA_FORM_DOWNLOAD_BUFFER
//-
//-	 This function take as input a pointer to a buffer handle allocated with the function 
//-  Utility_ALLOCATE_DOWNLOAD_BUFFER and retrive one data from the buffer (head of the FIFO)
//-  If the buffer is rmpty function fails with -1 error
//-  The buffer_size specify the size of the buffer to be allocated enqueued_data willl
//-	 contain the number of word that has been enqueued in the buffer
//-
//-  ARGUMENTS:
//- 	            buffer_handle   PARAM_IN   void *
//-			Handle to the buffer
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-  
//- 	            val			   PARAM_OUT   uint32_t *
//-			head of the buffer
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//-  RETURN [int]
//- 	Return if the function has been succesfully executed
//- 		0) Success
//- 		-1) Empty
//-
//-  EXAMPLE:
//-----------------------------------------------------------------


SCILIB int Utility_PEAK_DATA_FORM_DOWNLOAD_BUFFER(void *buffer_handle, int32_t *val)
{
	cbuf_handle_t cbuf;
	cbuf = (cbuf_handle_t)buffer_handle;
	if (circular_buf_empty(cbuf))
		return -1;
	circular_buf_get(cbuf, val);
	return 0;
}

//-----------------------------------------------------------------
//-
//-  free_FRAME_packet_collection
//-
//-	 This function take as input a pointer to a decoded packets and release the memory
//-
//-  ARGUMENTS:
//- 	            buffer_handle   PARAM_IN   t_FRAME_packet_collection *
//-			Packet to be released
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//-  RETURN [void]
//-
//-  EXAMPLE:
//-		FRAME_ImageReadout_0_RECONSTRUCT_DATA(BufferDownloadHandler, &decoded_packets);
//-		... processing code ...
//-		free_FRAME_packet_collectionvoid(&decoded_packets);
//-----------------------------------------------------------------


SCILIB void free_FRAME_packet_collection (t_FRAME_packet_collection *decoded_packets)
{
	int i;
	for (i = 0; i < decoded_packets->allocated_packets; i++)
	{
		free(decoded_packets->packets[i].Energy);
	}
	free(decoded_packets->packets);
}



SCILIB void free_packet_collection (t_generic_event_collection *decoded_packets)
{
	int i;
	for (i = 0; i < decoded_packets->valid_packets; i++)
	{
		free(decoded_packets->packets[i].payload);
	}
	free(decoded_packets->packets);
}


SCILIB int REG_pol_GET(uint32_t *val, NI_HANDLE *handle)
{
     return __abstracted_reg_read(val, SCI_REG_pol, handle);
}
SCILIB int REG_pol_SET(uint32_t val, NI_HANDLE *handle)
{
     return __abstracted_reg_write(val, SCI_REG_pol, handle);
}
SCILIB int REG_thrs_GET(uint32_t *val, NI_HANDLE *handle)
{
     return __abstracted_reg_read(val, SCI_REG_thrs, handle);
}
SCILIB int REG_thrs_SET(uint32_t val, NI_HANDLE *handle)
{
     return __abstracted_reg_write(val, SCI_REG_thrs, handle);
}
SCILIB int REG_inhib_GET(uint32_t *val, NI_HANDLE *handle)
{
     return __abstracted_reg_read(val, SCI_REG_inhib, handle);
}
SCILIB int REG_inhib_SET(uint32_t val, NI_HANDLE *handle)
{
     return __abstracted_reg_write(val, SCI_REG_inhib, handle);
}
SCILIB int REG_top_GET(uint32_t *val, NI_HANDLE *handle)
{
     return __abstracted_reg_read(val, SCI_REG_top, handle);
}
SCILIB int REG_top_SET(uint32_t val, NI_HANDLE *handle)
{
     return __abstracted_reg_write(val, SCI_REG_top, handle);
}
SCILIB int REG_delay_GET(uint32_t *val, NI_HANDLE *handle)
{
     return __abstracted_reg_read(val, SCI_REG_delay, handle);
}
SCILIB int REG_delay_SET(uint32_t val, NI_HANDLE *handle)
{
     return __abstracted_reg_write(val, SCI_REG_delay, handle);
}
SCILIB int REG_gate_GET(uint32_t *val, NI_HANDLE *handle)
{
     return __abstracted_reg_read(val, SCI_REG_gate, handle);
}
SCILIB int REG_gate_SET(uint32_t val, NI_HANDLE *handle)
{
     return __abstracted_reg_write(val, SCI_REG_gate, handle);
}
SCILIB int REG_inttime_GET(uint32_t *val, NI_HANDLE *handle)
{
     return __abstracted_reg_read(val, SCI_REG_inttime, handle);
}
SCILIB int REG_inttime_SET(uint32_t val, NI_HANDLE *handle)
{
     return __abstracted_reg_write(val, SCI_REG_inttime, handle);
}
SCILIB int REG_preint_GET(uint32_t *val, NI_HANDLE *handle)
{
     return __abstracted_reg_read(val, SCI_REG_preint, handle);
}
SCILIB int REG_preint_SET(uint32_t val, NI_HANDLE *handle)
{
     return __abstracted_reg_write(val, SCI_REG_preint, handle);
}
SCILIB int REG_pileup_GET(uint32_t *val, NI_HANDLE *handle)
{
     return __abstracted_reg_read(val, SCI_REG_pileup, handle);
}
SCILIB int REG_pileup_SET(uint32_t val, NI_HANDLE *handle)
{
     return __abstracted_reg_write(val, SCI_REG_pileup, handle);
}
SCILIB int REG_gain_GET(uint32_t *val, NI_HANDLE *handle)
{
     return __abstracted_reg_read(val, SCI_REG_gain, handle);
}
SCILIB int REG_gain_SET(uint32_t val, NI_HANDLE *handle)
{
     return __abstracted_reg_write(val, SCI_REG_gain, handle);
}
SCILIB int REG_ofs_GET(uint32_t *val, NI_HANDLE *handle)
{
     return __abstracted_reg_read(val, SCI_REG_ofs, handle);
}
SCILIB int REG_ofs_SET(uint32_t val, NI_HANDLE *handle)
{
     return __abstracted_reg_write(val, SCI_REG_ofs, handle);
}
SCILIB int REG_baseline_GET(uint32_t *val, NI_HANDLE *handle)
{
     return __abstracted_reg_read(val, SCI_REG_baseline, handle);
}
SCILIB int REG_baseline_SET(uint32_t val, NI_HANDLE *handle)
{
     return __abstracted_reg_write(val, SCI_REG_baseline, handle);
}
SCILIB int REG_gatel_GET(uint32_t *val, NI_HANDLE *handle)
{
     return __abstracted_reg_read(val, SCI_REG_gatel, handle);
}
SCILIB int REG_gatel_SET(uint32_t val, NI_HANDLE *handle)
{
     return __abstracted_reg_write(val, SCI_REG_gatel, handle);
}
SCILIB int REG_xdelay_GET(uint32_t *val, NI_HANDLE *handle)
{
     return __abstracted_reg_read(val, SCI_REG_xdelay, handle);
}
SCILIB int REG_xdelay_SET(uint32_t val, NI_HANDLE *handle)
{
     return __abstracted_reg_write(val, SCI_REG_xdelay, handle);
}
SCILIB int REG_ANALOG_OFFSET_SET(uint32_t val, NI_HANDLE *handle)
{
     return __abstracted_reg_write(val, SCI_REG_ANALOG_OFFSET, handle);
}
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

SCILIB int RATE_METER_RateMeter_0_GET_DATA(uint32_t *val, uint32_t channels, int32_t timeout, NI_HANDLE *handle, uint32_t *read_data, uint32_t *valid_data)
{
return __abstracted_mem_read(val, channels, SCI_REG_RateMeter_0_FIFOADDRESS, timeout, handle, read_data, valid_data);

}
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

SCILIB int RATE_METER_RateMeter_0_GET_DATA_COUNTS(uint32_t *val, uint32_t channels, int32_t timeout, NI_HANDLE *handle, uint32_t *read_data, uint32_t *valid_data)
{
return __abstracted_mem_read(val, channels, SCI_REG_RateMeter_0_FIFOADDRESS+512, timeout, handle, read_data, valid_data);

}
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

{
return __abstracted_reg_write(4,SCI_REG_Spectrum_0_CONFIG, handle);

}
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

{
return __abstracted_reg_write(0,SCI_REG_Spectrum_0_CONFIG, handle);

}
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

{
return __abstracted_reg_write(1,SCI_REG_Spectrum_0_CONFIG, handle);

}
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

{
return __abstracted_reg_write(2,SCI_REG_Spectrum_0_CONFIG, handle);

}
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

{
     int32_t limit = 0;
     int r_rebin = __abstracted_reg_write(rebin, SCI_REG_Spectrum_0_CONFIG_REBIN, handle);
     limit = (1 << (limit_mode + 29)) + limit_value; 
     int r_limit = __abstracted_reg_write(limit, SCI_REG_Spectrum_0_CONFIG_LIMIT, handle);
     if (r_rebin == 0 & r_limit == 0)
         return 0;
     else
         return -1;

}
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

SCILIB int SPECTRUM_Spectrum_0_STATUS(uint32_t *status,NI_HANDLE *handle)
{
return __abstracted_reg_read(status, SCI_REG_Spectrum_0_STATUS, handle);

}
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

SCILIB int SPECTRUM_Spectrum_0_DOWNLOAD(uint32_t *val, uint32_t size, int32_t timeout, NI_HANDLE *handle, uint32_t *read_data, uint32_t *valid_data)
{
return __abstracted_mem_read(val, size, SCI_REG_Spectrum_0_FIFOADDRESS, timeout, handle, read_data, valid_data);

}
//-----------------------------------------------------------------
//-
//- OSCILLOSCOPE_Oscilloscope_0_START
//-
//- Start Oscilloscope acquisition.
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

SCILIB int OSCILLOSCOPE_Oscilloscope_0_START(NI_HANDLE *handle)

{
int r1 = __abstracted_reg_write(0,SCI_REG_Oscilloscope_0_CONFIG_ARM, handle);
int r2 = __abstracted_reg_write(1,SCI_REG_Oscilloscope_0_CONFIG_ARM, handle);
if ((r1 == 0) && (r2 == 0))
    return 0;
else
    return -1;

}
//-----------------------------------------------------------------
//-
//- OSCILLOSCOPE_Oscilloscope_0_SET_PARAMETERS
//-
//- Configure oscilloscope parameters
//-
//- ARGUMENTS:
//- 	       decimator   PARAM_IN    int32_t
//- 		Set decimator value. 0: no decimation, 1: divide by two, ...
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//- 	             pre   PARAM_IN    int32_t
//- 		Set the length in samples of pre-trigger buffer
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//- 	software_trigger   PARAM_IN    int32_t
//- 		Generate software trigger to force start acquisition (1:generate trigger)
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//- 	  analog_trigger   PARAM_IN    int32_t
//- 		Enable threshold trigger on analog input of selected channel
//- 		DEFAULT: 
//- 		OPTIONAL: False
//- 		0) Disable
//- 		1) Enable
//-
//- 	digital0_trigger   PARAM_IN    int32_t
//- 		Enable digital trigger on digital in 0 of selected channel
//- 		DEFAULT: 
//- 		OPTIONAL: False
//- 		0) Disable
//- 		1) Enable
//-
//- 	digital1_trigger   PARAM_IN    int32_t
//- 		Enable digital trigger on digital in 1 of selected channel
//- 		DEFAULT: 
//- 		OPTIONAL: False
//- 		0) Disable
//- 		1) Enable
//-
//- 	digital2_trigger   PARAM_IN    int32_t
//- 		Enable digital trigger on digital in 2 of selected channel
//- 		DEFAULT: 
//- 		OPTIONAL: False
//- 		0) Disable
//- 		1) Enable
//-
//- 	digital3_trigger   PARAM_IN    int32_t
//- 		Enable digital trigger on digital in 3 of selected channel
//- 		DEFAULT: 
//- 		OPTIONAL: False
//- 		0) Disable
//- 		1) Enable
//-
//- 	 trigger_channel   PARAM_IN    int32_t
//- 		Select channel of the oscilloscope connected to the trigger logic
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//- 	    trigger_edge   PARAM_IN    int32_t
//- 		Select channel of the oscilloscope connected to the trigger logic
//- 		DEFAULT: 
//- 		OPTIONAL: False
//- 		0) Rising
//- 		1) Falling
//-
//- 	   trigger_level   PARAM_IN    int32_t
//- 		Level in LSB of the leading edge comparator on analog input. Use only with analog_trigger=1
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

SCILIB int OSCILLOSCOPE_Oscilloscope_0_SET_PARAMETERS(int32_t decimator, int32_t pre, int32_t software_trigger, int32_t analog_trigger, int32_t digital0_trigger, int32_t digital1_trigger, int32_t digital2_trigger, int32_t digital3_trigger, int32_t trigger_channel, int32_t trigger_edge, int32_t trigger_level, NI_HANDLE *handle)
{
int32_t triggermode = 0;
int r_decimator = __abstracted_reg_write(decimator, SCI_REG_Oscilloscope_0_CONFIG_DECIMATOR, handle);
int r_pre = __abstracted_reg_write(pre, SCI_REG_Oscilloscope_0_CONFIG_PRETRIGGER, handle);
int r_triglevel = __abstracted_reg_write(trigger_level, SCI_REG_Oscilloscope_0_CONFIG_TRIGGER_LEVEL, handle);
triggermode = (trigger_channel << 8)  + (software_trigger << 7 ) + (trigger_edge << 3) + (software_trigger << 1) + analog_trigger + (digital0_trigger << 2) + (digital1_trigger << 2) + digital1_trigger + (digital2_trigger << 2) + (digital2_trigger << 1) + (digital3_trigger << 2) + (digital3_trigger << 1) + digital3_trigger ; 
int r_triggermode = __abstracted_reg_write(triggermode, SCI_REG_Oscilloscope_0_CONFIG_TRIGGER_MODE, handle);
if (r_decimator == 0 & r_pre == 0 & r_triglevel == 0 & r_triggermode == 0)
    return 0;
else
    return -1;

}
//-----------------------------------------------------------------
//-
//- OSCILLOSCOPE_Oscilloscope_0_STATUS
//-
//- Get Oscilloscope status
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

SCILIB int OSCILLOSCOPE_Oscilloscope_0_STATUS(uint32_t *status,NI_HANDLE *handle)
{
return __abstracted_reg_read(status, SCI_REG_Oscilloscope_0_READ_STATUS, handle);

}
//-----------------------------------------------------------------
//-
//- OSCILLOSCOPE_Oscilloscope_0_POSITION
//-
//- Get Oscilloscope trigger position. The trigger position indicate the position in the output buffer of each channels where the sample at t0 occureed. PRE-TRIGGER samples before t0 is the pre-trigger data.
//-
//- ARGUMENTS:
//- 	        position  PARAM_OUT    int32_t
//- 		Return the trigger position in the data set in order to correct recustruct the pre-prigger and post trigger data
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

SCILIB int OSCILLOSCOPE_Oscilloscope_0_POSITION(int32_t *position,NI_HANDLE *handle)
{
return __abstracted_reg_read(position, SCI_REG_Oscilloscope_0_READ_POSITION, handle);

}
//-----------------------------------------------------------------
//-
//- OSCILLOSCOPE_Oscilloscope_0_DOWNLOAD
//-
//- Download data from oscilloscope buffer. Please note that downloaded data is not time ordered and the trigger position info data must be obtained using the OSCILLOSCOPE_Oscilloscope_0POSITION function 
//- 
//- USAGE: 
//-     OSCILLOSCOPE_Oscilloscope_0_DOWNLOAD(data_buffer, BUFFER_SIZE_Oscilloscope_0, 1000, handle, rd, vp);
//- 
//-
//- ARGUMENTS:
//- 	             val  PARAM_OUT   uint32_t
//- 		uint32_t buffer data with preallocated size of at list 'size' parameters + 16 word
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//- 	             val   PARAM_IN       size
//- 		number of word to download from the buffer. Use macro BUFFER_SIZE_Oscilloscope_0 to get actual oscilloscope buffer size on FPGA
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

SCILIB int OSCILLOSCOPE_Oscilloscope_0_DOWNLOAD(uint32_t *val, uint32_t size, int32_t timeout, NI_HANDLE *handle, uint32_t *read_data, uint32_t *valid_data)
{
return __abstracted_mem_read(val, size, SCI_REG_Oscilloscope_0_FIFOADDRESS, timeout, handle, read_data, valid_data);

}
//-----------------------------------------------------------------
//-
//- OSCILLOSCOPE_Oscilloscope_0_RECONSTRUCT
//-
//- Take as input the downloaded buffer and decode the the different track for each channels. Channel order is the following: [0...1023] Channel 1, [1024...2047] Channel2
//- 
//- 
//-
//- ARGUMENTS:
//- 	        data_osc   PARAM_IN   uint32_t
//- 		uint32_t buffer containing the raw data download with the DOWNLOAD function
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//- 	        position   PARAM_IN   uint32_t
//- 		Position of the trigger obtained with the POSITION function
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//- 	     pre_trigger   PARAM_IN    int32_t
//- 		Length of the pre-trigger
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//- 	     read_analog  PARAM_OUT   uint32_t
//- 		Analog track reordered in time. Data are encoded in unsigned data format between -32576 and 32576
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//- 	   read_digital0  PARAM_OUT   uint32_t
//- 		Digital track 0 reordered
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//- 	   read_digital1  PARAM_OUT   uint32_t
//- 		Digital track 1 reordered
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//- 	   read_digital2  PARAM_OUT   uint32_t
//- 		Digital track 2 reordered
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//- 	   read_digital3  PARAM_OUT   uint32_t
//- 		Digital track 3 reordered
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

SCILIB int OSCILLOSCOPE_Oscilloscope_0_RECONSTRUCT(uint32_t *data_osc, uint32_t position, int32_t pre_trigger, uint32_t *read_analog, uint32_t *read_digital0, uint32_t *read_digital1, uint32_t *read_digital2, uint32_t *read_digital3)
{
int n_ch = 3;
int n_samples = 1024;
if (position > n_samples) return -1;
for(int n=0; n< n_ch; n++)
{
	int current = position - pre_trigger;
	if (current > 0)
    {
	    int k = 0;
	    for (int i = current; i < n_samples - 1; i++)
        {
		 read_analog[k + (n_samples*n)] = data_osc[i + (n_samples*n)] & 65535;
		 read_digital0[k + (n_samples*n)] = data_osc[i + (n_samples*n)] >> 16 & 1;
		 read_digital1[k + (n_samples*n)] = data_osc[i + (n_samples*n)] >> 17 & 1;
		 read_digital2[k + (n_samples*n)] = data_osc[i + (n_samples*n)] >> 18 & 1;
		 read_digital3[k + (n_samples*n)] = data_osc[i + (n_samples*n)] >> 19 & 1;
             k++;
        }
	    for (int i = 0; i < current - 1; i++)
        {
		 read_analog[k + (n_samples*n)] = data_osc[i + (n_samples*n)] & 65535;
		 read_digital0[k + (n_samples*n)] = data_osc[i + (n_samples*n)] >> 16 & 1;
		 read_digital1[k + (n_samples*n)] = data_osc[i + (n_samples*n)] >> 17 & 1;
		 read_digital2[k + (n_samples*n)] = data_osc[i + (n_samples*n)] >> 18 & 1;
		 read_digital3[k + (n_samples*n)] = data_osc[i + (n_samples*n)] >> 19 & 1;
             k++;
        }
    }
    else
    {
	    int k = 0;
	    for (int i = n_samples+current; i < n_samples - 1; i++)
        {
		 read_analog[k + (n_samples*n)] = data_osc[i + (n_samples*n)] & 65535;
		 read_digital0[k + (n_samples*n)] = data_osc[i + (n_samples*n)] >> 16 & 1;
		 read_digital1[k + (n_samples*n)] = data_osc[i + (n_samples*n)] >> 17 & 1;
		 read_digital2[k + (n_samples*n)] = data_osc[i + (n_samples*n)] >> 18 & 1;
		 read_digital3[k + (n_samples*n)] = data_osc[i + (n_samples*n)] >> 19 & 1;
             k++;
        }
	    for (int i = 0; i < n_samples + current - 1; i++)
        {
		 read_analog[k + (n_samples*n)] = data_osc[i + (n_samples*n)] & 65535;
		 read_digital0[k + (n_samples*n)] = data_osc[i + (n_samples*n)] >> 16 & 1;
		 read_digital1[k + (n_samples*n)] = data_osc[i + (n_samples*n)] >> 17 & 1;
		 read_digital2[k + (n_samples*n)] = data_osc[i + (n_samples*n)] >> 18 & 1;
		 read_digital3[k + (n_samples*n)] = data_osc[i + (n_samples*n)] >> 19 & 1;
             k++;
        }
    }
}
return 0;

}
//-----------------------------------------------------------------
//-
//- SPECTRUM_Spectrum_NoDelay_START
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

SCILIB int SPECTRUM_Spectrum_NoDelay_START(NI_HANDLE *handle)

{
return __abstracted_reg_write(4,SCI_REG_Spectrum_NoDelay_CONFIG, handle);

}
//-----------------------------------------------------------------
//-
//- SPECTRUM_Spectrum_NoDelay_STOP
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

SCILIB int SPECTRUM_Spectrum_NoDelay_START(NI_HANDLE *handle)

{
return __abstracted_reg_write(0,SCI_REG_Spectrum_NoDelay_CONFIG, handle);

}
//-----------------------------------------------------------------
//-
//- SPECTRUM_Spectrum_NoDelay_FLUSH
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

SCILIB int SPECTRUM_Spectrum_NoDelay_START(NI_HANDLE *handle)

{
return __abstracted_reg_write(1,SCI_REG_Spectrum_NoDelay_CONFIG, handle);

}
//-----------------------------------------------------------------
//-
//- SPECTRUM_Spectrum_NoDelay_RESET
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

SCILIB int SPECTRUM_Spectrum_NoDelay_START(NI_HANDLE *handle)

{
return __abstracted_reg_write(2,SCI_REG_Spectrum_NoDelay_CONFIG, handle);

}
//-----------------------------------------------------------------
//-
//- SPECTRUM_Spectrum_NoDelay_SET_PARAMETERS
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

SCILIB int SPECTRUM_Spectrum_NoDelay_SET_PARAMETERS(int32_t rebin, int32_t limit_mode, int32_t limit_value, NI_HANDLE *handle);

{
     int32_t limit = 0;
     int r_rebin = __abstracted_reg_write(rebin, SCI_REG_Spectrum_NoDelay_CONFIG_REBIN, handle);
     limit = (1 << (limit_mode + 29)) + limit_value; 
     int r_limit = __abstracted_reg_write(limit, SCI_REG_Spectrum_NoDelay_CONFIG_LIMIT, handle);
     if (r_rebin == 0 & r_limit == 0)
         return 0;
     else
         return -1;

}
//-----------------------------------------------------------------
//-
//- SPECTRUM_Spectrum_NoDelay_STATUS
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

SCILIB int SPECTRUM_Spectrum_NoDelay_STATUS(uint32_t *status,NI_HANDLE *handle)
{
return __abstracted_reg_read(status, SCI_REG_Spectrum_NoDelay_STATUS, handle);

}
//-----------------------------------------------------------------
//-
//- SPECTRUM_Spectrum_NoDelay_DOWNLOAD
//-
//- Download data from buffer. Please note that downloaded data is not time ordered and the trigger position info data must be obtained using the OSCILLOSCOPE_Spectrum_NoDelayPOSITION function 
//- 
//- USAGE: 
//-     OSCILLOSCOPE_Spectrum_NoDelay_DOWNLOAD(data_buffer, BUFFER_SIZE_Spectrum_NoDelay, 1000, handle, rd, vp);
//- 
//-
//- ARGUMENTS:
//- 	             val  PARAM_OUT   uint32_t
//- 		uint32_t buffer data with preallocated size of at list 'size' parameters + 16 word
//- 		DEFAULT: 
//- 		OPTIONAL: False
//-
//- 	             val   PARAM_IN       size
//- 		number of word to download from the buffer. Use macro BUFFER_SIZE_Spectrum_NoDelay to get actual oscilloscope buffer size on FPGA
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

SCILIB int SPECTRUM_Spectrum_NoDelay_DOWNLOAD(uint32_t *val, uint32_t size, int32_t timeout, NI_HANDLE *handle, uint32_t *read_data, uint32_t *valid_data)
{
return __abstracted_mem_read(val, size, SCI_REG_Spectrum_NoDelay_FIFOADDRESS, timeout, handle, read_data, valid_data);

}
