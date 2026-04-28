
















import Spilver1TestFirmware_RegisterFile
from ctypes import *
import array
import numpy as np

import os
mydll = cdll.LoadLibrary(os.path.dirname(__file__) +'/R5560_SDKLib.dll')

def Init():
    return 0

def ConnectDevice(board):
    c_s = c_char_p(board.encode('ascii'))
    da= mydll.R5560_HandleAllocator()
    handle = c_void_p(da)
    err = mydll.R5560_ConnectTCP(c_s, 8888, handle)
    return err, handle

def CloseConnect(handle):
    err = mydll.NI_CloseConnection((handle))
    return err    
    
def ListDevices():
    str_devices=""
    dev_count =-1
    return str_devices, dev_count 

def __abstracted_reg_write(data, address, handle):
    err = mydll.NI_WriteReg(data, address, (handle))
    return err

def __abstracted_reg_read(address, handle):
    data = c_uint(0)
    err = mydll.NI_ReadReg(byref(data), address, (handle))
    return err, data.value

def __abstracted_mem_write(data, count, address, timeout_ms, handle):
    written_data = c_uint(0)
    err = mydll.NI_WriteData(data, count, address, (handle), byref(written_data))
    return err, written_data.value

def __abstracted_mem_read(count, address, timeout_ms, handle):
    data = (c_uint * (2* count))()
    read_data = c_uint(0)
    valid_data = c_uint(0)
    err = mydll.NI_ReadData(byref(data), count, address, (handle), byref(read_data))
    valid_data=read_data
    return err, data, read_data.value, valid_data.value

def __abstracted_fifo_write(data, count, address, address_status, timeout_ms, handle):
    return -1

def __abstracted_fifo_read(count, address, address_status, blocking, timeout_ms, handle):
    data = (c_uint * (2 * count))()
    read_data = c_uint(0)
    valid_data = c_uint(0)
    err = mydll.NI_ReadFifo(byref(data), count, address, address_status, (1 if blocking else 2), timeout_ms, (handle), byref(read_data))
    valid_data=read_data
    return err, data, read_data, valid_data     
    
def __abstracted_DMA_read(dma_channel, handle):
    count = 2*1024*1024;
    data = (c_ulonglong * (count))()
    read_data = c_uint(0)
    err = mydll.NI_DMA_Read(dma_channel, byref(data), count, byref(read_data), (handle))
    vd = (read_data.value / 8);
    return err, data, vd     
    
def __abstracted_DMA_CONFIG(dma_channel, blocking, timeout, buffer_length, handle):
    err = mydll.NI_DMA_SetOptions(dma_channel, blocking, timeout, buffer_length, (handle))
    return err
    
    
def gray_to_bin(num, nbit):
    temp = num ^ (num >> 8)
    temp ^= (temp >> 4)
    temp ^= (temp >> 2)
    temp ^= (temp >> 1)
    return temp    

def REG_thrs_low_0_GET(handle):
    [err, data] = __abstracted_reg_read(Spilver1TestFirmware_RegisterFile.SCI_REG_thrs_low_0, handle)
    return err, data

def REG_thrs_low_0_SET(data, handle):
    err = __abstracted_reg_write(data, Spilver1TestFirmware_RegisterFile.SCI_REG_thrs_low_0, handle)
    return err

def REG_thrs_low_1_GET(handle):
    [err, data] = __abstracted_reg_read(Spilver1TestFirmware_RegisterFile.SCI_REG_thrs_low_1, handle)
    return err, data

def REG_thrs_low_1_SET(data, handle):
    err = __abstracted_reg_write(data, Spilver1TestFirmware_RegisterFile.SCI_REG_thrs_low_1, handle)
    return err

def REG_offset_0_GET(handle):
    [err, data] = __abstracted_reg_read(Spilver1TestFirmware_RegisterFile.SCI_REG_offset_0, handle)
    return err, data

def REG_offset_0_SET(data, handle):
    err = __abstracted_reg_write(data, Spilver1TestFirmware_RegisterFile.SCI_REG_offset_0, handle)
    return err

def REG_gate_low_trig_GET(handle):
    [err, data] = __abstracted_reg_read(Spilver1TestFirmware_RegisterFile.SCI_REG_gate_low_trig, handle)
    return err, data

def REG_gate_low_trig_SET(data, handle):
    err = __abstracted_reg_write(data, Spilver1TestFirmware_RegisterFile.SCI_REG_gate_low_trig, handle)
    return err

def REG_baseline_0_GET(handle):
    [err, data] = __abstracted_reg_read(Spilver1TestFirmware_RegisterFile.SCI_REG_baseline_0, handle)
    return err, data

def REG_baseline_0_SET(data, handle):
    err = __abstracted_reg_write(data, Spilver1TestFirmware_RegisterFile.SCI_REG_baseline_0, handle)
    return err

def REG_delay_low_trig_GET(handle):
    [err, data] = __abstracted_reg_read(Spilver1TestFirmware_RegisterFile.SCI_REG_delay_low_trig, handle)
    return err, data

def REG_delay_low_trig_SET(data, handle):
    err = __abstracted_reg_write(data, Spilver1TestFirmware_RegisterFile.SCI_REG_delay_low_trig, handle)
    return err

def REG_int_time_GET(handle):
    [err, data] = __abstracted_reg_read(Spilver1TestFirmware_RegisterFile.SCI_REG_int_time, handle)
    return err, data

def REG_int_time_SET(data, handle):
    err = __abstracted_reg_write(data, Spilver1TestFirmware_RegisterFile.SCI_REG_int_time, handle)
    return err

def REG_coinc_window_GET(handle):
    [err, data] = __abstracted_reg_read(Spilver1TestFirmware_RegisterFile.SCI_REG_coinc_window, handle)
    return err, data

def REG_coinc_window_SET(data, handle):
    err = __abstracted_reg_write(data, Spilver1TestFirmware_RegisterFile.SCI_REG_coinc_window, handle)
    return err

def REG_polarity_GET(handle):
    [err, data] = __abstracted_reg_read(Spilver1TestFirmware_RegisterFile.SCI_REG_polarity, handle)
    return err, data

def REG_polarity_SET(data, handle):
    err = __abstracted_reg_write(data, Spilver1TestFirmware_RegisterFile.SCI_REG_polarity, handle)
    return err

def REG_pre_int_GET(handle):
    [err, data] = __abstracted_reg_read(Spilver1TestFirmware_RegisterFile.SCI_REG_pre_int, handle)
    return err, data

def REG_pre_int_SET(data, handle):
    err = __abstracted_reg_write(data, Spilver1TestFirmware_RegisterFile.SCI_REG_pre_int, handle)
    return err

def REG_pileup_inib_GET(handle):
    [err, data] = __abstracted_reg_read(Spilver1TestFirmware_RegisterFile.SCI_REG_pileup_inib, handle)
    return err, data

def REG_pileup_inib_SET(data, handle):
    err = __abstracted_reg_write(data, Spilver1TestFirmware_RegisterFile.SCI_REG_pileup_inib, handle)
    return err

def REG_thrs_high_0_GET(handle):
    [err, data] = __abstracted_reg_read(Spilver1TestFirmware_RegisterFile.SCI_REG_thrs_high_0, handle)
    return err, data

def REG_thrs_high_0_SET(data, handle):
    err = __abstracted_reg_write(data, Spilver1TestFirmware_RegisterFile.SCI_REG_thrs_high_0, handle)
    return err

def REG_gain_1_GET(handle):
    [err, data] = __abstracted_reg_read(Spilver1TestFirmware_RegisterFile.SCI_REG_gain_1, handle)
    return err, data

def REG_gain_1_SET(data, handle):
    err = __abstracted_reg_write(data, Spilver1TestFirmware_RegisterFile.SCI_REG_gain_1, handle)
    return err

def REG_thrs_high_1_GET(handle):
    [err, data] = __abstracted_reg_read(Spilver1TestFirmware_RegisterFile.SCI_REG_thrs_high_1, handle)
    return err, data

def REG_thrs_high_1_SET(data, handle):
    err = __abstracted_reg_write(data, Spilver1TestFirmware_RegisterFile.SCI_REG_thrs_high_1, handle)
    return err

def REG_offset_1_GET(handle):
    [err, data] = __abstracted_reg_read(Spilver1TestFirmware_RegisterFile.SCI_REG_offset_1, handle)
    return err, data

def REG_offset_1_SET(data, handle):
    err = __abstracted_reg_write(data, Spilver1TestFirmware_RegisterFile.SCI_REG_offset_1, handle)
    return err

def REG_gate_high_trig_GET(handle):
    [err, data] = __abstracted_reg_read(Spilver1TestFirmware_RegisterFile.SCI_REG_gate_high_trig, handle)
    return err, data

def REG_gate_high_trig_SET(data, handle):
    err = __abstracted_reg_write(data, Spilver1TestFirmware_RegisterFile.SCI_REG_gate_high_trig, handle)
    return err

def REG_baseline_1_GET(handle):
    [err, data] = __abstracted_reg_read(Spilver1TestFirmware_RegisterFile.SCI_REG_baseline_1, handle)
    return err, data

def REG_baseline_1_SET(data, handle):
    err = __abstracted_reg_write(data, Spilver1TestFirmware_RegisterFile.SCI_REG_baseline_1, handle)
    return err

def REG_gain_0_GET(handle):
    [err, data] = __abstracted_reg_read(Spilver1TestFirmware_RegisterFile.SCI_REG_gain_0, handle)
    return err, data

def REG_gain_0_SET(data, handle):
    err = __abstracted_reg_write(data, Spilver1TestFirmware_RegisterFile.SCI_REG_gain_0, handle)
    return err



def SPECTRUM_Spectrum_0_RESET(handle):
    err = __abstracted_reg_write(2, Spilver1TestFirmware_RegisterFile.SCI_REG_Spectrum_0_CONFIG, handle)
    return err

def SPECTRUM_Spectrum_0_START(handle):
    err = __abstracted_reg_write(4, Spilver1TestFirmware_RegisterFile.SCI_REG_Spectrum_0_CONFIG, handle)
    return err

def SPECTRUM_Spectrum_0_FLUSH(handle):
    err = __abstracted_reg_write(1, Spilver1TestFirmware_RegisterFile.SCI_REG_Spectrum_0_CONFIG, handle)
    return err

def SPECTRUM_Spectrum_0_STOP(handle):
    err = __abstracted_reg_write(0, Spilver1TestFirmware_RegisterFile.SCI_REG_Spectrum_0_CONFIG, handle)
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
    err = __abstracted_reg_write(rebin_value, Spilver1TestFirmware_RegisterFile.SCI_REG_Spectrum_0_CONFIG_REBIN, handle)
    acq_mode=0
    if (AcquisitionMode =="Event"):
        acq_mode=(1 << 30) + TargetValue
    if (AcquisitionMode =="Time"):
        acq_mode=(1 << 31) + TargetValue*1000
    err = __abstracted_reg_write(acq_mode, Spilver1TestFirmware_RegisterFile.SCI_REG_Spectrum_0_CONFIG_LIMIT, handle)
    return err

def SPECTRUM_Spectrum_0_GET_STATUS(handle):
    [err, status] = __abstracted_reg_read(Spilver1TestFirmware_RegisterFile.SCI_REG_Spectrum_0_STATUS, handle)
    return err, status

def SPECTRUM_Spectrum_0_GET_DATA(Bin, timeout_ms, handle):
    [err, data, read_data, valid_data] = __abstracted_mem_read(Bin, Spilver1TestFirmware_RegisterFile.SCI_REG_Spectrum_0_FIFOADDRESS, timeout_ms, handle)
    return err, data, read_data, valid_data



def OSCILLOSCOPE_Oscilloscope_raw_START(handle):
    err = __abstracted_reg_write(0, Spilver1TestFirmware_RegisterFile.SCI_REG_Oscilloscope_raw_CONFIG_ARM, handle)
    if (err != 0):
       return False
    err = __abstracted_reg_write(1, Spilver1TestFirmware_RegisterFile.SCI_REG_Oscilloscope_raw_CONFIG_ARM, handle)
    if (err != 0):
       return False
    return True

def OSCILLOSCOPE_Oscilloscope_raw_SET_DECIMATOR(OscilloscopeDecimator, handle):
    err = __abstracted_reg_write(OscilloscopeDecimator, Spilver1TestFirmware_RegisterFile.SCI_REG_Oscilloscope_raw_CONFIG_DECIMATOR, handle)
    return err

def OSCILLOSCOPE_Oscilloscope_raw_SET_PRETRIGGER(OscilloscopePreTrigger, handle):
    err = __abstracted_reg_write(OscilloscopePreTrigger, Spilver1TestFirmware_RegisterFile.SCI_REG_Oscilloscope_raw_CONFIG_PRETRIGGER, handle)
    return err

def OSCILLOSCOPE_Oscilloscope_raw_SET_TRIGGER_LEVEL(OscilloscopeTriggerLevel, handle):
    err = __abstracted_reg_write(OscilloscopeTriggerLevel, Spilver1TestFirmware_RegisterFile.SCI_REG_Oscilloscope_raw_CONFIG_TRIGGER_LEVEL, handle)
    return err

def OSCILLOSCOPE_Oscilloscope_raw_SET_TRIGGER_MODE(OscilloscopeTriggerMode, OscilloscopeTriggerChannel, OscilloscopeTriggerEdge, handle):
    AnalogTrigger = 0
    Digital0Trigger = 0
    Digital1Trigger = 0
    Digital2Trigger = 0
    Digital3Trigger = 0
    SoftwareTrigger = 0
    if (OscilloscopeTriggerMode == "Analog"):
        AnalogTrigger = 1
    if (OscilloscopeTriggerMode == "Digital0"):
        Digital0Trigger = 1
    if (OscilloscopeTriggerMode == "Digital1"):
        Digital1Trigger = 1
    if (OscilloscopeTriggerMode == "Digital2"):
        Digital2Trigger = 1
    if (OscilloscopeTriggerMode == "Digital3"):
        Digital3Trigger = 1
    if (OscilloscopeTriggerMode == "Free"):
        SoftwareTrigger = 1
    if (OscilloscopeTriggerEdge == "Rising"):
        Edge = 0
    else:
        Edge = 1
    triggermode = c_int(0)
    triggermode = (OscilloscopeTriggerChannel << 8)  + (SoftwareTrigger << 7 ) + (Edge << 3) + (SoftwareTrigger << 1) + AnalogTrigger +(Digital0Trigger << 2) + (Digital1Trigger << 2) + Digital1Trigger + (Digital2Trigger << 2) + (Digital2Trigger << 1) + (Digital3Trigger << 2) + (Digital3Trigger << 1) + Digital3Trigger
    err = __abstracted_reg_write(triggermode, Spilver1TestFirmware_RegisterFile.SCI_REG_Oscilloscope_raw_CONFIG_TRIGGER_MODE, handle)
    return err

def OSCILLOSCOPE_Oscilloscope_raw_GET_STATUS(handle):
    [err, status] = __abstracted_reg_read(Spilver1TestFirmware_RegisterFile.SCI_REG_Oscilloscope_raw_READ_STATUS, handle)
    return err, status

def OSCILLOSCOPE_Oscilloscope_raw_GET_POSITION(handle):
    [err, position] = __abstracted_reg_read(Spilver1TestFirmware_RegisterFile.SCI_REG_Oscilloscope_raw_READ_POSITION, handle)
    return err, position

def OSCILLOSCOPE_Oscilloscope_raw_GET_DATA(timeout_ms, handle):
    [err, data, read_data, valid_data] = __abstracted_mem_read(4096, Spilver1TestFirmware_RegisterFile.SCI_REG_Oscilloscope_raw_FIFOADDRESS, timeout_ms, handle)
    return err, data, read_data, valid_data

def OSCILLOSCOPE_Oscilloscope_raw_RECONSTRUCT_DATA(OscilloscopeData, OscilloscopePosition, OscilloscopePreTrigger):
    OscilloscopeChannels = 4
    OscilloscopeSamples = 1024
    Analog = list(range(OscilloscopeSamples*OscilloscopeChannels))
    Digital0 = list(range(OscilloscopeSamples*OscilloscopeChannels))
    Digital1 = list(range(OscilloscopeSamples*OscilloscopeChannels))
    Digital2 = list(range(OscilloscopeSamples*OscilloscopeChannels))
    Digital3 = list(range(OscilloscopeSamples*OscilloscopeChannels))
    for n in range(OscilloscopeChannels):
        current = OscilloscopePosition - OscilloscopePreTrigger
        if ((current) > 0):
            k = 0
            for i in range(current, OscilloscopeSamples-1):
                Analog[k+ OscilloscopeSamples * n] = OscilloscopeData[i+ OscilloscopeSamples * n] & 65535
                Digital0[k+ OscilloscopeSamples * n] = (OscilloscopeData[i+ OscilloscopeSamples * n] >> 16 & 1)
                Digital1[k+ OscilloscopeSamples * n] = (OscilloscopeData[i+ OscilloscopeSamples * n] >> 17 & 1)
                Digital2[k+ OscilloscopeSamples * n] = (OscilloscopeData[i+ OscilloscopeSamples * n] >> 18 & 1)
                Digital3[k+ OscilloscopeSamples * n] = (OscilloscopeData[i+ OscilloscopeSamples * n] >> 19 & 1)
                k = k + 1
            for i in range(0, current-1):
                Analog[k+ OscilloscopeSamples * n] = OscilloscopeData[i+ OscilloscopeSamples * n] & 65535
                Digital0[k+ OscilloscopeSamples * n] = (OscilloscopeData[i+ OscilloscopeSamples * n] >> 16 & 1)
                Digital1[k+ OscilloscopeSamples * n] = (OscilloscopeData[i+ OscilloscopeSamples * n] >> 17 & 1)
                Digital2[k+ OscilloscopeSamples * n] = (OscilloscopeData[i+ OscilloscopeSamples * n] >> 18 & 1)
                Digital3[k+ OscilloscopeSamples * n] = (OscilloscopeData[i+ OscilloscopeSamples * n] >> 19 & 1)
                k = k + 1
        else:
            k = 0
            for i in range(OscilloscopeSamples+current, OscilloscopeSamples-1):
                Analog[k+ OscilloscopeSamples * n] = OscilloscopeData[i+ OscilloscopeSamples * n] & 65535
                Digital0[k+ OscilloscopeSamples * n] = (OscilloscopeData[i+ OscilloscopeSamples * n] >> 16 & 1)
                Digital1[k+ OscilloscopeSamples * n] = (OscilloscopeData[i+ OscilloscopeSamples * n] >> 17 & 1)
                Digital2[k+ OscilloscopeSamples * n] = (OscilloscopeData[i+ OscilloscopeSamples * n] >> 18 & 1)
                Digital3[k+ OscilloscopeSamples * n] = (OscilloscopeData[i+ OscilloscopeSamples * n] >> 19 & 1)
                k = k + 1
            for i in range(0, OscilloscopeSamples+current-1):
                Analog[k+ OscilloscopeSamples * n] = OscilloscopeData[i+ OscilloscopeSamples * n] & 65535
                Digital0[k+ OscilloscopeSamples * n] = (OscilloscopeData[i+ OscilloscopeSamples * n] >> 16 & 1)
                Digital1[k+ OscilloscopeSamples * n] = (OscilloscopeData[i+ OscilloscopeSamples * n] >> 17 & 1)
                Digital2[k+ OscilloscopeSamples * n] = (OscilloscopeData[i+ OscilloscopeSamples * n] >> 18 & 1)
                Digital3[k+ OscilloscopeSamples * n] = (OscilloscopeData[i+ OscilloscopeSamples * n] >> 19 & 1)
                k = k + 1
    return Analog, Digital0, Digital1,Digital2, Digital3



def SPECTRUM_Spectrum_1_RESET(handle):
    err = __abstracted_reg_write(2, Spilver1TestFirmware_RegisterFile.SCI_REG_Spectrum_1_CONFIG, handle)
    return err

def SPECTRUM_Spectrum_1_START(handle):
    err = __abstracted_reg_write(4, Spilver1TestFirmware_RegisterFile.SCI_REG_Spectrum_1_CONFIG, handle)
    return err

def SPECTRUM_Spectrum_1_FLUSH(handle):
    err = __abstracted_reg_write(1, Spilver1TestFirmware_RegisterFile.SCI_REG_Spectrum_1_CONFIG, handle)
    return err

def SPECTRUM_Spectrum_1_STOP(handle):
    err = __abstracted_reg_write(0, Spilver1TestFirmware_RegisterFile.SCI_REG_Spectrum_1_CONFIG, handle)
    return err

def SPECTRUM_Spectrum_1_SET_PARAMETERS(Bin, AcquisitionMode, TargetValue, handle):
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
    err = __abstracted_reg_write(rebin_value, Spilver1TestFirmware_RegisterFile.SCI_REG_Spectrum_1_CONFIG_REBIN, handle)
    acq_mode=0
    if (AcquisitionMode =="Event"):
        acq_mode=(1 << 30) + TargetValue
    if (AcquisitionMode =="Time"):
        acq_mode=(1 << 31) + TargetValue*1000
    err = __abstracted_reg_write(acq_mode, Spilver1TestFirmware_RegisterFile.SCI_REG_Spectrum_1_CONFIG_LIMIT, handle)
    return err

def SPECTRUM_Spectrum_1_GET_STATUS(handle):
    [err, status] = __abstracted_reg_read(Spilver1TestFirmware_RegisterFile.SCI_REG_Spectrum_1_STATUS, handle)
    return err, status

def SPECTRUM_Spectrum_1_GET_DATA(Bin, timeout_ms, handle):
    [err, data, read_data, valid_data] = __abstracted_mem_read(Bin, Spilver1TestFirmware_RegisterFile.SCI_REG_Spectrum_1_FIFOADDRESS, timeout_ms, handle)
    return err, data, read_data, valid_data




def RATE_METER_RateMeter_1_GET_DATA(channels, timeout_ms, handle):
    [err, data, read_data, valid_data] = __abstracted_mem_read(channels, Spilver1TestFirmware_RegisterFile.SCI_REG_RateMeter_1_FIFOADDRESS, timeout_ms, handle)
    return err, data, read_data, valid_data




def RATE_METER_RateMeter_1_GET_DATA_COUNTS(channels, timeout_ms, handle):
    [err, data, read_data, valid_data] = __abstracted_mem_read(channels, Spilver1TestFirmware_RegisterFile.SCI_REG_RateMeter_1_FIFOADDRESS + 512, timeout_ms, handle)
    return err, data, read_data, valid_data



def LISTMODULE_List_1_RESET(handle):
    err = __abstracted_reg_write(2, Spilver1TestFirmware_RegisterFile.SCI_REG_List_1_CONFIG, handle)
    return err

def LISTMODULE_List_1_START(handle):
    err = __abstracted_reg_write(2, Spilver1TestFirmware_RegisterFile.SCI_REG_List_1_CONFIG, handle)
    if (err != 0):
       return False
    err = __abstracted_reg_write(1, Spilver1TestFirmware_RegisterFile.SCI_REG_List_1_CONFIG, handle)
    if (err != 0):
       return False
    return True

def LISTMODULE_List_1_GET_STATUS(handle):
    [err, status] = __abstracted_reg_read(Spilver1TestFirmware_RegisterFile.SCI_REG_List_1_STATUS, handle)
    flags = status & 0xf
    data_available = status >> 8
    return err, flags, data_available

def LISTMODULE_List_1_GET_DATA(Data_Number, timeout_ms, handle):
    [err, data, read_data, valid_data] = __abstracted_fifo_read(Data_Number, Spilver1TestFirmware_RegisterFile.SCI_REG_List_1_FIFOADDRESS, Spilver1TestFirmware_RegisterFile.SCI_REG_List_1_STATUS,1, timeout_ms, handle)
    return err, data, read_data, valid_data



def LISTMODULE_List_0_RESET(handle):
    err = __abstracted_reg_write(2, Spilver1TestFirmware_RegisterFile.SCI_REG_List_0_CONFIG, handle)
    return err

def LISTMODULE_List_0_START(handle):
    err = __abstracted_reg_write(2, Spilver1TestFirmware_RegisterFile.SCI_REG_List_0_CONFIG, handle)
    if (err != 0):
       return False
    err = __abstracted_reg_write(1, Spilver1TestFirmware_RegisterFile.SCI_REG_List_0_CONFIG, handle)
    if (err != 0):
       return False
    return True

def LISTMODULE_List_0_GET_STATUS(handle):
    [err, status] = __abstracted_reg_read(Spilver1TestFirmware_RegisterFile.SCI_REG_List_0_STATUS, handle)
    flags = status & 0xf
    data_available = status >> 8
    return err, flags, data_available

def LISTMODULE_List_0_GET_DATA(Data_Number, timeout_ms, handle):
    [err, data, read_data, valid_data] = __abstracted_fifo_read(Data_Number, Spilver1TestFirmware_RegisterFile.SCI_REG_List_0_FIFOADDRESS, Spilver1TestFirmware_RegisterFile.SCI_REG_List_0_STATUS,1, timeout_ms, handle)
    return err, data, read_data, valid_data




def RATE_METER_RateMeter_0_GET_DATA(channels, timeout_ms, handle):
    [err, data, read_data, valid_data] = __abstracted_mem_read(channels, Spilver1TestFirmware_RegisterFile.SCI_REG_RateMeter_0_FIFOADDRESS, timeout_ms, handle)
    return err, data, read_data, valid_data




def RATE_METER_RateMeter_0_GET_DATA_COUNTS(channels, timeout_ms, handle):
    [err, data, read_data, valid_data] = __abstracted_mem_read(channels, Spilver1TestFirmware_RegisterFile.SCI_REG_RateMeter_0_FIFOADDRESS + 512, timeout_ms, handle)
    return err, data, read_data, valid_data

