







import TrigTest3_RegisterFile
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
	

def REG_pol_GET(handle):
    [err, data] = __abstracted_reg_read(TrigTest3_RegisterFile.SCI_REG_pol, handle)
    return err, data

def REG_pol_SET(data, handle):
    err = __abstracted_reg_write(data, TrigTest3_RegisterFile.SCI_REG_pol, handle)
    return err

def REG_thrs_GET(handle):
    [err, data] = __abstracted_reg_read(TrigTest3_RegisterFile.SCI_REG_thrs, handle)
    return err, data

def REG_thrs_SET(data, handle):
    err = __abstracted_reg_write(data, TrigTest3_RegisterFile.SCI_REG_thrs, handle)
    return err

def REG_inhib_GET(handle):
    [err, data] = __abstracted_reg_read(TrigTest3_RegisterFile.SCI_REG_inhib, handle)
    return err, data

def REG_inhib_SET(data, handle):
    err = __abstracted_reg_write(data, TrigTest3_RegisterFile.SCI_REG_inhib, handle)
    return err

def REG_top_GET(handle):
    [err, data] = __abstracted_reg_read(TrigTest3_RegisterFile.SCI_REG_top, handle)
    return err, data

def REG_top_SET(data, handle):
    err = __abstracted_reg_write(data, TrigTest3_RegisterFile.SCI_REG_top, handle)
    return err

def REG_delay_GET(handle):
    [err, data] = __abstracted_reg_read(TrigTest3_RegisterFile.SCI_REG_delay, handle)
    return err, data

def REG_delay_SET(data, handle):
    err = __abstracted_reg_write(data, TrigTest3_RegisterFile.SCI_REG_delay, handle)
    return err

def REG_gate_GET(handle):
    [err, data] = __abstracted_reg_read(TrigTest3_RegisterFile.SCI_REG_gate, handle)
    return err, data

def REG_gate_SET(data, handle):
    err = __abstracted_reg_write(data, TrigTest3_RegisterFile.SCI_REG_gate, handle)
    return err

def REG_inttime_GET(handle):
    [err, data] = __abstracted_reg_read(TrigTest3_RegisterFile.SCI_REG_inttime, handle)
    return err, data

def REG_inttime_SET(data, handle):
    err = __abstracted_reg_write(data, TrigTest3_RegisterFile.SCI_REG_inttime, handle)
    return err

def REG_preint_GET(handle):
    [err, data] = __abstracted_reg_read(TrigTest3_RegisterFile.SCI_REG_preint, handle)
    return err, data

def REG_preint_SET(data, handle):
    err = __abstracted_reg_write(data, TrigTest3_RegisterFile.SCI_REG_preint, handle)
    return err

def REG_pileup_GET(handle):
    [err, data] = __abstracted_reg_read(TrigTest3_RegisterFile.SCI_REG_pileup, handle)
    return err, data

def REG_pileup_SET(data, handle):
    err = __abstracted_reg_write(data, TrigTest3_RegisterFile.SCI_REG_pileup, handle)
    return err

def REG_gain_GET(handle):
    [err, data] = __abstracted_reg_read(TrigTest3_RegisterFile.SCI_REG_gain, handle)
    return err, data

def REG_gain_SET(data, handle):
    err = __abstracted_reg_write(data, TrigTest3_RegisterFile.SCI_REG_gain, handle)
    return err

def REG_ofs_GET(handle):
    [err, data] = __abstracted_reg_read(TrigTest3_RegisterFile.SCI_REG_ofs, handle)
    return err, data

def REG_ofs_SET(data, handle):
    err = __abstracted_reg_write(data, TrigTest3_RegisterFile.SCI_REG_ofs, handle)
    return err

def REG_baseline_GET(handle):
    [err, data] = __abstracted_reg_read(TrigTest3_RegisterFile.SCI_REG_baseline, handle)
    return err, data

def REG_baseline_SET(data, handle):
    err = __abstracted_reg_write(data, TrigTest3_RegisterFile.SCI_REG_baseline, handle)
    return err
def REG_ANALOG_OFFSET_SET(data, handle):
    err = __abstracted_reg_write(data, TrigTest3_RegisterFile.SCI_REG_ANALOG_OFFSET, handle)
    return err




def RATE_METER_RateMeter_0_GET_DATA(channels, timeout_ms, handle):
    [err, data, read_data, valid_data] = __abstracted_mem_read(channels, TrigTest3_RegisterFile.SCI_REG_RateMeter_0_FIFOADDRESS, timeout_ms, handle)
    return err, data, read_data, valid_data




def RATE_METER_RateMeter_0_GET_DATA_COUNTS(channels, timeout_ms, handle):
    [err, data, read_data, valid_data] = __abstracted_mem_read(channels, TrigTest3_RegisterFile.SCI_REG_RateMeter_0_FIFOADDRESS + 512, timeout_ms, handle)
    return err, data, read_data, valid_data



def SPECTRUM_Spectrum_0_RESET(handle):
    err = __abstracted_reg_write(2, TrigTest3_RegisterFile.SCI_REG_Spectrum_0_CONFIG, handle)
    return err

def SPECTRUM_Spectrum_0_START(handle):
    err = __abstracted_reg_write(4, TrigTest3_RegisterFile.SCI_REG_Spectrum_0_CONFIG, handle)
    return err

def SPECTRUM_Spectrum_0_FLUSH(handle):
    err = __abstracted_reg_write(1, TrigTest3_RegisterFile.SCI_REG_Spectrum_0_CONFIG, handle)
    return err

def SPECTRUM_Spectrum_0_STOP(handle):
    err = __abstracted_reg_write(0, TrigTest3_RegisterFile.SCI_REG_Spectrum_0_CONFIG, handle)
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
    err = __abstracted_reg_write(rebin_value, TrigTest3_RegisterFile.SCI_REG_Spectrum_0_CONFIG_REBIN, handle)
    acq_mode=0
    if (AcquisitionMode =="Event"):
        acq_mode=(1 << 30) + TargetValue
    if (AcquisitionMode =="Time"):
        acq_mode=(1 << 31) + TargetValue*1000
    err = __abstracted_reg_write(acq_mode, TrigTest3_RegisterFile.SCI_REG_Spectrum_0_CONFIG_LIMIT, handle)
    return err

def SPECTRUM_Spectrum_0_GET_STATUS(handle):
    [err, status] = __abstracted_reg_read(TrigTest3_RegisterFile.SCI_REG_Spectrum_0_STATUS, handle)
    return err, status

def SPECTRUM_Spectrum_0_GET_DATA(Bin, timeout_ms, handle):
    [err, data, read_data, valid_data] = __abstracted_mem_read(Bin, TrigTest3_RegisterFile.SCI_REG_Spectrum_0_FIFOADDRESS, timeout_ms, handle)
    return err, data, read_data, valid_data



def OSCILLOSCOPE_Oscilloscope_0_START(handle):
    err = __abstracted_reg_write(0, TrigTest3_RegisterFile.SCI_REG_Oscilloscope_0_CONFIG_ARM, handle)
    if (err != 0):
       return False
    err = __abstracted_reg_write(1, TrigTest3_RegisterFile.SCI_REG_Oscilloscope_0_CONFIG_ARM, handle)
    if (err != 0):
       return False
    return True

def OSCILLOSCOPE_Oscilloscope_0_SET_DECIMATOR(OscilloscopeDecimator, handle):
    err = __abstracted_reg_write(OscilloscopeDecimator, TrigTest3_RegisterFile.SCI_REG_Oscilloscope_0_CONFIG_DECIMATOR, handle)
    return err

def OSCILLOSCOPE_Oscilloscope_0_SET_PRETRIGGER(OscilloscopePreTrigger, handle):
    err = __abstracted_reg_write(OscilloscopePreTrigger, TrigTest3_RegisterFile.SCI_REG_Oscilloscope_0_CONFIG_PRETRIGGER, handle)
    return err

def OSCILLOSCOPE_Oscilloscope_0_SET_TRIGGER_LEVEL(OscilloscopeTriggerLevel, handle):
    err = __abstracted_reg_write(OscilloscopeTriggerLevel, TrigTest3_RegisterFile.SCI_REG_Oscilloscope_0_CONFIG_TRIGGER_LEVEL, handle)
    return err

def OSCILLOSCOPE_Oscilloscope_0_SET_TRIGGER_MODE(OscilloscopeTriggerMode, OscilloscopeTriggerChannel, OscilloscopeTriggerEdge, handle):
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
    err = __abstracted_reg_write(triggermode, TrigTest3_RegisterFile.SCI_REG_Oscilloscope_0_CONFIG_TRIGGER_MODE, handle)
    return err

def OSCILLOSCOPE_Oscilloscope_0_GET_STATUS(handle):
    [err, status] = __abstracted_reg_read(TrigTest3_RegisterFile.SCI_REG_Oscilloscope_0_READ_STATUS, handle)
    return err, status

def OSCILLOSCOPE_Oscilloscope_0_GET_POSITION(handle):
    [err, position] = __abstracted_reg_read(TrigTest3_RegisterFile.SCI_REG_Oscilloscope_0_READ_POSITION, handle)
    return err, position

def OSCILLOSCOPE_Oscilloscope_0_GET_DATA(timeout_ms, handle):
    [err, data, read_data, valid_data] = __abstracted_mem_read(2048, TrigTest3_RegisterFile.SCI_REG_Oscilloscope_0_FIFOADDRESS, timeout_ms, handle)
    return err, data, read_data, valid_data

def OSCILLOSCOPE_Oscilloscope_0_RECONSTRUCT_DATA(OscilloscopeData, OscilloscopePosition, OscilloscopePreTrigger):
    OscilloscopeChannels = 2
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

