






import sdfghjkl_RegisterFile
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

def REG_CN_GET(handle):
    [err, data] = __abstracted_reg_read(sdfghjkl_RegisterFile.SCI_REG_CN, handle)
    return err, data

def REG_CN_SET(data, handle):
    err = __abstracted_reg_write(data, sdfghjkl_RegisterFile.SCI_REG_CN, handle)
    return err

def REG_pol_GET(handle):
    [err, data] = __abstracted_reg_read(sdfghjkl_RegisterFile.SCI_REG_pol, handle)
    return err, data

def REG_pol_SET(data, handle):
    err = __abstracted_reg_write(data, sdfghjkl_RegisterFile.SCI_REG_pol, handle)
    return err

def REG_thrs_GET(handle):
    [err, data] = __abstracted_reg_read(sdfghjkl_RegisterFile.SCI_REG_thrs, handle)
    return err, data

def REG_thrs_SET(data, handle):
    err = __abstracted_reg_write(data, sdfghjkl_RegisterFile.SCI_REG_thrs, handle)
    return err

def REG_inhib_GET(handle):
    [err, data] = __abstracted_reg_read(sdfghjkl_RegisterFile.SCI_REG_inhib, handle)
    return err, data

def REG_inhib_SET(data, handle):
    err = __abstracted_reg_write(data, sdfghjkl_RegisterFile.SCI_REG_inhib, handle)
    return err

def REG_top_GET(handle):
    [err, data] = __abstracted_reg_read(sdfghjkl_RegisterFile.SCI_REG_top, handle)
    return err, data

def REG_top_SET(data, handle):
    err = __abstracted_reg_write(data, sdfghjkl_RegisterFile.SCI_REG_top, handle)
    return err

def REG_delay_GET(handle):
    [err, data] = __abstracted_reg_read(sdfghjkl_RegisterFile.SCI_REG_delay, handle)
    return err, data

def REG_delay_SET(data, handle):
    err = __abstracted_reg_write(data, sdfghjkl_RegisterFile.SCI_REG_delay, handle)
    return err

def REG_xdelay_GET(handle):
    [err, data] = __abstracted_reg_read(sdfghjkl_RegisterFile.SCI_REG_xdelay, handle)
    return err, data

def REG_xdelay_SET(data, handle):
    err = __abstracted_reg_write(data, sdfghjkl_RegisterFile.SCI_REG_xdelay, handle)
    return err

def REG_gate_GET(handle):
    [err, data] = __abstracted_reg_read(sdfghjkl_RegisterFile.SCI_REG_gate, handle)
    return err, data

def REG_gate_SET(data, handle):
    err = __abstracted_reg_write(data, sdfghjkl_RegisterFile.SCI_REG_gate, handle)
    return err

def REG_gatel_GET(handle):
    [err, data] = __abstracted_reg_read(sdfghjkl_RegisterFile.SCI_REG_gatel, handle)
    return err, data

def REG_gatel_SET(data, handle):
    err = __abstracted_reg_write(data, sdfghjkl_RegisterFile.SCI_REG_gatel, handle)
    return err

def REG_inttime_GET(handle):
    [err, data] = __abstracted_reg_read(sdfghjkl_RegisterFile.SCI_REG_inttime, handle)
    return err, data

def REG_inttime_SET(data, handle):
    err = __abstracted_reg_write(data, sdfghjkl_RegisterFile.SCI_REG_inttime, handle)
    return err

def REG_preint_GET(handle):
    [err, data] = __abstracted_reg_read(sdfghjkl_RegisterFile.SCI_REG_preint, handle)
    return err, data

def REG_preint_SET(data, handle):
    err = __abstracted_reg_write(data, sdfghjkl_RegisterFile.SCI_REG_preint, handle)
    return err

def REG_gain_GET(handle):
    [err, data] = __abstracted_reg_read(sdfghjkl_RegisterFile.SCI_REG_gain, handle)
    return err, data

def REG_gain_SET(data, handle):
    err = __abstracted_reg_write(data, sdfghjkl_RegisterFile.SCI_REG_gain, handle)
    return err

def REG_ofs_GET(handle):
    [err, data] = __abstracted_reg_read(sdfghjkl_RegisterFile.SCI_REG_ofs, handle)
    return err, data

def REG_ofs_SET(data, handle):
    err = __abstracted_reg_write(data, sdfghjkl_RegisterFile.SCI_REG_ofs, handle)
    return err

def REG_bl_GET(handle):
    [err, data] = __abstracted_reg_read(sdfghjkl_RegisterFile.SCI_REG_bl, handle)
    return err, data

def REG_bl_SET(data, handle):
    err = __abstracted_reg_write(data, sdfghjkl_RegisterFile.SCI_REG_bl, handle)
    return err

def REG_flip_GET(handle):
    [err, data] = __abstracted_reg_read(sdfghjkl_RegisterFile.SCI_REG_flip, handle)
    return err, data

def REG_flip_SET(data, handle):
    err = __abstracted_reg_write(data, sdfghjkl_RegisterFile.SCI_REG_flip, handle)
    return err

def REG_pileup_GET(handle):
    [err, data] = __abstracted_reg_read(sdfghjkl_RegisterFile.SCI_REG_pileup, handle)
    return err, data

def REG_pileup_SET(data, handle):
    err = __abstracted_reg_write(data, sdfghjkl_RegisterFile.SCI_REG_pileup, handle)
    return err

def REG_reset_GET(handle):
    [err, data] = __abstracted_reg_read(sdfghjkl_RegisterFile.SCI_REG_reset, handle)
    return err, data

def REG_reset_SET(data, handle):
    err = __abstracted_reg_write(data, sdfghjkl_RegisterFile.SCI_REG_reset, handle)
    return err



def SPECTRUM_Spectrum_0_RESET(handle):
    err = __abstracted_reg_write(2, sdfghjkl_RegisterFile.SCI_REG_Spectrum_0_CONFIG, handle)
    return err

def SPECTRUM_Spectrum_0_START(handle):
    err = __abstracted_reg_write(4, sdfghjkl_RegisterFile.SCI_REG_Spectrum_0_CONFIG, handle)
    return err

def SPECTRUM_Spectrum_0_FLUSH(handle):
    err = __abstracted_reg_write(1, sdfghjkl_RegisterFile.SCI_REG_Spectrum_0_CONFIG, handle)
    return err

def SPECTRUM_Spectrum_0_STOP(handle):
    err = __abstracted_reg_write(0, sdfghjkl_RegisterFile.SCI_REG_Spectrum_0_CONFIG, handle)
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
    err = __abstracted_reg_write(rebin_value, sdfghjkl_RegisterFile.SCI_REG_Spectrum_0_CONFIG_REBIN, handle)
    acq_mode=0
    if (AcquisitionMode =="Event"):
        acq_mode=(1 << 30) + TargetValue
    if (AcquisitionMode =="Time"):
        acq_mode=(1 << 31) + TargetValue*1000
    err = __abstracted_reg_write(acq_mode, sdfghjkl_RegisterFile.SCI_REG_Spectrum_0_CONFIG_LIMIT, handle)
    return err

def SPECTRUM_Spectrum_0_GET_STATUS(handle):
    [err, status] = __abstracted_reg_read(sdfghjkl_RegisterFile.SCI_REG_Spectrum_0_STATUS, handle)
    return err, status

def SPECTRUM_Spectrum_0_GET_DATA(Bin, timeout_ms, handle):
    [err, data, read_data, valid_data] = __abstracted_mem_read(Bin, sdfghjkl_RegisterFile.SCI_REG_Spectrum_0_FIFOADDRESS, timeout_ms, handle)
    return err, data, read_data, valid_data



def OSCILLOSCOPE_Oscilloscope_0_START(handle):
    err = __abstracted_reg_write(0, sdfghjkl_RegisterFile.SCI_REG_Oscilloscope_0_CONFIG_ARM, handle)
    if (err != 0):
       return False
    err = __abstracted_reg_write(1, sdfghjkl_RegisterFile.SCI_REG_Oscilloscope_0_CONFIG_ARM, handle)
    if (err != 0):
       return False
    return True

def OSCILLOSCOPE_Oscilloscope_0_SET_DECIMATOR(OscilloscopeDecimator, handle):
    err = __abstracted_reg_write(OscilloscopeDecimator, sdfghjkl_RegisterFile.SCI_REG_Oscilloscope_0_CONFIG_DECIMATOR, handle)
    return err

def OSCILLOSCOPE_Oscilloscope_0_SET_PRETRIGGER(OscilloscopePreTrigger, handle):
    err = __abstracted_reg_write(OscilloscopePreTrigger, sdfghjkl_RegisterFile.SCI_REG_Oscilloscope_0_CONFIG_PRETRIGGER, handle)
    return err

def OSCILLOSCOPE_Oscilloscope_0_SET_TRIGGER_LEVEL(OscilloscopeTriggerLevel, handle):
    err = __abstracted_reg_write(OscilloscopeTriggerLevel, sdfghjkl_RegisterFile.SCI_REG_Oscilloscope_0_CONFIG_TRIGGER_LEVEL, handle)
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
    err = __abstracted_reg_write(triggermode, sdfghjkl_RegisterFile.SCI_REG_Oscilloscope_0_CONFIG_TRIGGER_MODE, handle)
    return err

def OSCILLOSCOPE_Oscilloscope_0_GET_STATUS(handle):
    [err, status] = __abstracted_reg_read(sdfghjkl_RegisterFile.SCI_REG_Oscilloscope_0_READ_STATUS, handle)
    return err, status

def OSCILLOSCOPE_Oscilloscope_0_GET_POSITION(handle):
    [err, position] = __abstracted_reg_read(sdfghjkl_RegisterFile.SCI_REG_Oscilloscope_0_READ_POSITION, handle)
    return err, position

def OSCILLOSCOPE_Oscilloscope_0_GET_DATA(timeout_ms, handle):
    [err, data, read_data, valid_data] = __abstracted_mem_read(2048, sdfghjkl_RegisterFile.SCI_REG_Oscilloscope_0_FIFOADDRESS, timeout_ms, handle)
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




def CPACK_FIFO_RESET(handle):
    err = __abstracted_reg_write(2, sdfghjkl_RegisterFile.SCI_REG_FIFO_CONFIG, handle)
    err = __abstracted_reg_write(0, sdfghjkl_RegisterFile.SCI_REG_FIFO_CONFIG, handle)
    return err

def CPACK_FIFO_FLUSH(handle):
    err = __abstracted_reg_write(4, sdfghjkl_RegisterFile.SCI_REG_FIFO_CONFIG, handle)
    err = __abstracted_reg_write(0, sdfghjkl_RegisterFile.SCI_REG_FIFO_CONFIG, handle)
    return err

def CPACK_FIFO_START(handle):
    err = __abstracted_reg_write(2, sdfghjkl_RegisterFile.SCI_REG_FIFO_CONFIG, handle)
    if (err != 0):
       return False
    err = __abstracted_reg_write(0, sdfghjkl_RegisterFile.SCI_REG_FIFO_CONFIG, handle)
    if (err != 0):
       return False
    err = __abstracted_reg_write(1, sdfghjkl_RegisterFile.SCI_REG_FIFO_CONFIG, handle)
    if (err != 0):
       return False
    return True

def CPACK_FIFO_GET_STATUS(handle):
    [err, status] = __abstracted_reg_read(sdfghjkl_RegisterFile.SCI_REG_FIFO_READ_STATUS, handle)
    status = status & 0xf
    return err, status

def CPACK_FIFO_GET_AVAILABLE_DATA(handle):
    [err, status] = __abstracted_reg_read(sdfghjkl_RegisterFile.SCI_REG_FIFO_READ_VALID_WORDS, handle)
    return err, status

def CPACK_FIFO_GET_DATA(n_packet, timeout_ms, handle):
    data_length = n_packet *( 3 + <<<NUMBER OF PACKET LINES AFTER THE HEADER HERE>>>)
    [err, data, read_data, valid_data] = __abstracted_fifo_read(data_length, sdfghjkl_RegisterFile.SCI_REG_FIFO_FIFOADDRESS, sdfghjkl_RegisterFile.SCI_REG_FIFO_READ_STATUS, True, timeout_ms, handle)
    return err, data, read_data, valid_data


def CPACK_FIFO_RECONSTRUCT_DATA(FrameData):
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

