






import test3_RegisterFile
from ctypes import *
import array
import numpy as np
import os

mydll = cdll.LoadLibrary(os.path.dirname(__file__) +'/SCIDK_Lib.dll')

def ConnectDevice(board):
    handle = c_void_p(256)
    err = mydll.SCIDK_ConnectUSB(board, byref(handle))
    return err, handle

def CloseConnect(handle):
    err = mydll.NI_CloseConnection(byref(handle))
    return err	
	
def ListDevices():
    count = c_int(0)
    s = create_string_buffer(2048)
    err = mydll.NI_USBEnumerate(byref(s), b"SCIDK", byref(count))
    str_con = (s.value.decode('ascii')) 
    str_devices = str_con.split(';')
    dev_count = count.value
    return str_devices, dev_count 

def __abstracted_reg_write(data, address, handle):
    err = mydll.NI_WriteReg(data, address, byref(handle))
    return err

def __abstracted_reg_read(address, handle):
    data = c_uint(0)
    err = mydll.NI_ReadReg(byref(data), address, byref(handle))
    return err, data.value

def __abstracted_mem_write(data, count, address, timeout_ms, handle):
    written_data = c_uint(0)
    err = mydll.NI_WriteData(data, count, address, 0, timeout_ms, byref(handle), byref(written_data))
    return err, written_data.value

def __abstracted_mem_read(count, address, timeout_ms, handle):
    data = (c_uint * (2* count))()
    read_data = c_uint(0)
    valid_data = c_uint(0)
    err = mydll.NI_ReadData(byref(data), count, address, 0, timeout_ms, byref(handle), byref(read_data), byref(valid_data))
    return err, data, read_data.value, valid_data.value

def __abstracted_fifo_write(data, count, address, timeout_ms, handle):
    written_data = c_uint(0)
    err = mydll.NI_WriteData(data, count, address, 1, timeout_ms, byref(handle), byref(written_data))
    return err, written_data.value

def __abstracted_fifo_read(count, address, address_status, blocking, timeout_ms, handle):
    data = (c_uint * (2 * count))()
    read_data = c_uint(0)
    valid_data = c_uint(0)
    err = mydll.NI_ReadData(byref(data), count, address, 1, timeout_ms, byref(handle), byref(read_data), byref(valid_data))
    return err, data, read_data, valid_data 	
	

def REG_CN_GET(handle):
    [err, data] = __abstracted_reg_read(test3_RegisterFile.SCI_REG_CN, handle)
    return err, data

def REG_CN_SET(data, handle):
    err = __abstracted_reg_write(data, test3_RegisterFile.SCI_REG_CN, handle)
    return err

def REG_pol_GET(handle):
    [err, data] = __abstracted_reg_read(test3_RegisterFile.SCI_REG_pol, handle)
    return err, data

def REG_pol_SET(data, handle):
    err = __abstracted_reg_write(data, test3_RegisterFile.SCI_REG_pol, handle)
    return err

def REG_thrs_GET(handle):
    [err, data] = __abstracted_reg_read(test3_RegisterFile.SCI_REG_thrs, handle)
    return err, data

def REG_thrs_SET(data, handle):
    err = __abstracted_reg_write(data, test3_RegisterFile.SCI_REG_thrs, handle)
    return err

def REG_inhib_GET(handle):
    [err, data] = __abstracted_reg_read(test3_RegisterFile.SCI_REG_inhib, handle)
    return err, data

def REG_inhib_SET(data, handle):
    err = __abstracted_reg_write(data, test3_RegisterFile.SCI_REG_inhib, handle)
    return err

def REG_top_GET(handle):
    [err, data] = __abstracted_reg_read(test3_RegisterFile.SCI_REG_top, handle)
    return err, data

def REG_top_SET(data, handle):
    err = __abstracted_reg_write(data, test3_RegisterFile.SCI_REG_top, handle)
    return err

def REG_delay_GET(handle):
    [err, data] = __abstracted_reg_read(test3_RegisterFile.SCI_REG_delay, handle)
    return err, data

def REG_delay_SET(data, handle):
    err = __abstracted_reg_write(data, test3_RegisterFile.SCI_REG_delay, handle)
    return err

def REG_gate_GET(handle):
    [err, data] = __abstracted_reg_read(test3_RegisterFile.SCI_REG_gate, handle)
    return err, data

def REG_gate_SET(data, handle):
    err = __abstracted_reg_write(data, test3_RegisterFile.SCI_REG_gate, handle)
    return err

def REG_gatel_GET(handle):
    [err, data] = __abstracted_reg_read(test3_RegisterFile.SCI_REG_gatel, handle)
    return err, data

def REG_gatel_SET(data, handle):
    err = __abstracted_reg_write(data, test3_RegisterFile.SCI_REG_gatel, handle)
    return err

def REG_xdelay_GET(handle):
    [err, data] = __abstracted_reg_read(test3_RegisterFile.SCI_REG_xdelay, handle)
    return err, data

def REG_xdelay_SET(data, handle):
    err = __abstracted_reg_write(data, test3_RegisterFile.SCI_REG_xdelay, handle)
    return err

def REG_inttime_GET(handle):
    [err, data] = __abstracted_reg_read(test3_RegisterFile.SCI_REG_inttime, handle)
    return err, data

def REG_inttime_SET(data, handle):
    err = __abstracted_reg_write(data, test3_RegisterFile.SCI_REG_inttime, handle)
    return err

def REG_preint_GET(handle):
    [err, data] = __abstracted_reg_read(test3_RegisterFile.SCI_REG_preint, handle)
    return err, data

def REG_preint_SET(data, handle):
    err = __abstracted_reg_write(data, test3_RegisterFile.SCI_REG_preint, handle)
    return err

def REG_pileup_GET(handle):
    [err, data] = __abstracted_reg_read(test3_RegisterFile.SCI_REG_pileup, handle)
    return err, data

def REG_pileup_SET(data, handle):
    err = __abstracted_reg_write(data, test3_RegisterFile.SCI_REG_pileup, handle)
    return err

def REG_gain_GET(handle):
    [err, data] = __abstracted_reg_read(test3_RegisterFile.SCI_REG_gain, handle)
    return err, data

def REG_gain_SET(data, handle):
    err = __abstracted_reg_write(data, test3_RegisterFile.SCI_REG_gain, handle)
    return err

def REG_ofs_GET(handle):
    [err, data] = __abstracted_reg_read(test3_RegisterFile.SCI_REG_ofs, handle)
    return err, data

def REG_ofs_SET(data, handle):
    err = __abstracted_reg_write(data, test3_RegisterFile.SCI_REG_ofs, handle)
    return err

def REG_bl_GET(handle):
    [err, data] = __abstracted_reg_read(test3_RegisterFile.SCI_REG_bl, handle)
    return err, data

def REG_bl_SET(data, handle):
    err = __abstracted_reg_write(data, test3_RegisterFile.SCI_REG_bl, handle)
    return err

def REG_noflip0flip1_GET(handle):
    [err, data] = __abstracted_reg_read(test3_RegisterFile.SCI_REG_noflip0flip1, handle)
    return err, data

def REG_noflip0flip1_SET(data, handle):
    err = __abstracted_reg_write(data, test3_RegisterFile.SCI_REG_noflip0flip1, handle)
    return err
def REG_ANALOG_OFFSET_SET(data, handle):
    err = __abstracted_reg_write(data, test3_RegisterFile.SCI_REG_ANALOG_OFFSET, handle)
    return err



def SPECTRUM_Spectrum_0_RESET(handle):
    err = __abstracted_reg_write(2, test3_RegisterFile.SCI_REG_Spectrum_0_CONFIG, handle)
    return err

def SPECTRUM_Spectrum_0_START(handle):
    err = __abstracted_reg_write(4, test3_RegisterFile.SCI_REG_Spectrum_0_CONFIG, handle)
    return err

def SPECTRUM_Spectrum_0_FLUSH(handle):
    err = __abstracted_reg_write(1, test3_RegisterFile.SCI_REG_Spectrum_0_CONFIG, handle)
    return err

def SPECTRUM_Spectrum_0_STOP(handle):
    err = __abstracted_reg_write(0, test3_RegisterFile.SCI_REG_Spectrum_0_CONFIG, handle)
    return err

def SPECTRUM_Spectrum_0_SET_PARAMETERS(Bin, AcquisitionMode, TargetValue, handle):
    rebin_value=0
    if (Bin == 8192):
        rebin_value= 1
    if (Bin == 4096):
        rebin_value= 2
    if (Bin == 2048):
        rebin_value= 3
    if (Bin == 1024):
        rebin_value= 4
    if (Bin == 512):
        rebin_value= 5
    if (Bin == 256):
        rebin_value= 6
    if (Bin == 128):
        rebin_value= 7
    err = __abstracted_reg_write(rebin_value, test3_RegisterFile.SCI_REG_Spectrum_0_CONFIG_REBIN, handle)
    acq_mode=0
    if (AcquisitionMode =="Event"):
        acq_mode=(1 << 30) + TargetValue
    if (AcquisitionMode =="Time"):
        acq_mode=(1 << 31) + TargetValue*1000
    err = __abstracted_reg_write(acq_mode, test3_RegisterFile.SCI_REG_Spectrum_0_CONFIG_LIMIT, handle)
    return err

def SPECTRUM_Spectrum_0_GET_STATUS(handle):
    [err, status] = __abstracted_reg_read(test3_RegisterFile.SCI_REG_Spectrum_0_STATUS, handle)
    return err, status

def SPECTRUM_Spectrum_0_GET_DATA(Bin, timeout_ms, handle):
    [err, data, read_data, valid_data] = __abstracted_mem_read(Bin, test3_RegisterFile.SCI_REG_Spectrum_0_FIFOADDRESS, timeout_ms, handle)
    return err, data, read_data, valid_data



def LISTMODULE_Digitizer_0_RESET(handle):
    err = __abstracted_reg_write(2, test3_RegisterFile.SCI_REG_Digitizer_0_CONFIG, handle)
    return err

def LISTMODULE_Digitizer_0_START(handle, channels):
    err = __abstracted_reg_write(2 + (channels<<8), test3_RegisterFile.SCI_REG_Digitizer_0_CONFIG, handle)
    if (err != 0):
       return False
    err = __abstracted_reg_write(0 + (channels<<8), test3_RegisterFile.SCI_REG_Digitizer_0_CONFIG, handle)
    if (err != 0):
       return False
    err = __abstracted_reg_write(1 + (channels<<8), test3_RegisterFile.SCI_REG_Digitizer_0_CONFIG, handle)
    if (err != 0):
       return False
    return True

def LISTMODULE_Digitizer_0_SetLen(handle, length):
    err = __abstracted_reg_write(length, test3_RegisterFile.SCI_REG_Digitizer_0_ACQ_LEN, handle)
    if (err != 0):
       return False
    return True

def LISTMODULE_Digitizer_0_GET_STATUS(handle):
    [err, status] = __abstracted_reg_read(test3_RegisterFile.SCI_REG_Digitizer_0_STATUS, handle)
    status = status & 0xf
    return err, status

def LISTMODULE_Digitizer_0_GET_DATA(Data_Number, timeout_ms, handle):
    [err, data, read_data, valid_data] = __abstracted_fifo_read(Data_Number, test3_RegisterFile.SCI_REG_Digitizer_0_FIFOADDRESS, test3_RegisterFile.SCI_REG_Digitizer_0_STATUS,1, timeout_ms, handle)
    return err, data, read_data, valid_data




def CPACK_CP_0_RESET(handle):
	err = __abstracted_reg_write(2, test3_RegisterFile.SCI_REG_CP_0_CONFIG, handle)
	err = __abstracted_reg_write(0, test3_RegisterFile.SCI_REG_CP_0_CONFIG, handle)
	return err

def CPACK_CP_0_FLUSH(handle):
	err = __abstracted_reg_write(4, test3_RegisterFile.SCI_REG_CP_0_CONFIG, handle)
	err = __abstracted_reg_write(0, test3_RegisterFile.SCI_REG_CP_0_CONFIG, handle)
	return err

def CPACK_CP_0_START(handle):
	err = __abstracted_reg_write(2, test3_RegisterFile.SCI_REG_CP_0_CONFIG, handle)
	if (err != 0):
	   return False
	err = __abstracted_reg_write(0, test3_RegisterFile.SCI_REG_CP_0_CONFIG, handle)
	if (err != 0):
	   return False
	err = __abstracted_reg_write(1, test3_RegisterFile.SCI_REG_CP_0_CONFIG, handle)
	if (err != 0):
	   return False
	return True

def CPACK_CP_0_GET_STATUS(handle):
	[err, status] = __abstracted_reg_read(test3_RegisterFile.SCI_REG_CP_0_READ_STATUS, handle)
	status = status & 0xf
	return err, status

def CPACK_CP_0_GET_AVAILABLE_DATA(handle):
	[err, status] = __abstracted_reg_read(test3_RegisterFile.SCI_REG_CP_0_READ_VALID_WORDS, handle)
	return err, status

def CPACK_CP_0_GET_DATA(n_packet, timeout_ms, handle):
	data_length = n_packet *( 3 + <<<NUMBER OF PACKET LINES AFTER THE HEADER HERE>>>)
	[err, data, read_data, valid_data] = __abstracted_fifo_read(data_length, test3_RegisterFile.SCI_REG_CP_0_FIFOADDRESS, test3_RegisterFile.SCI_REG_CP_0_READ_STATUS, True, timeout_ms, handle)
	return err, data, read_data, valid_data


def CPACK_CP_0_RECONSTRUCT_DATA(FrameData):
	in_sync = 0
	tot_data = len(FrameData)
	n_ch = <<<NUMBER OF PACKET LINES AFTER THE HEADER HERE>>>
	n_packet = tot_data / (n_ch + 3)
	event_energy, Time_Code, Pack_Id, Energy = ([] for i in range(4))
	for i in range(len(FrameData)):
		mpe = FrameData[i]
		if (in_sync == 0):
			if (mpe != 0x<<<YOUR HEADER HERE>>>):
				continue
			in_sync = 1
			continue
		if (in_sync == 1):
			event_timecode = mpe 
			Time_Code.append(event_timecode)
			in_sync = 2
			continue
		if (in_sync == 2):
			Pack_Id.append(mpe)
			in_sync = 3
			ch_index = 0
			continue
		if (in_sync == 3):
			if (mpe == 0x<<<YOUR HEADER HERE>>>):
				in_sync = 1
			else:
				ev_energy = mpe
				event_energy.append(ev_energy)
				ch_index += 1
				if (ch_index == n_ch):
					Energy.append(event_energy)
					event_energy = []
					in_sync = 0
	return Time_Code, Pack_Id, Energy
