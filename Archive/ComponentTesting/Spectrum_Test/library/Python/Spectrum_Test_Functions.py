


import Spectrum_Test_RegisterFile
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

def REG_disable_det_1_GET(handle):
    [err, data] = __abstracted_reg_read(Spectrum_Test_RegisterFile.SCI_REG_disable_det_1, handle)
    return err, data

def REG_disable_det_1_SET(data, handle):
    err = __abstracted_reg_write(data, Spectrum_Test_RegisterFile.SCI_REG_disable_det_1, handle)
    return err

def REG_gate_l_GET(handle):
    [err, data] = __abstracted_reg_read(Spectrum_Test_RegisterFile.SCI_REG_gate_l, handle)
    return err, data

def REG_gate_l_SET(data, handle):
    err = __abstracted_reg_write(data, Spectrum_Test_RegisterFile.SCI_REG_gate_l, handle)
    return err

def REG_polarity_GET(handle):
    [err, data] = __abstracted_reg_read(Spectrum_Test_RegisterFile.SCI_REG_polarity, handle)
    return err, data

def REG_polarity_SET(data, handle):
    err = __abstracted_reg_write(data, Spectrum_Test_RegisterFile.SCI_REG_polarity, handle)
    return err

def REG_thrsh_1_GET(handle):
    [err, data] = __abstracted_reg_read(Spectrum_Test_RegisterFile.SCI_REG_thrsh_1, handle)
    return err, data

def REG_thrsh_1_SET(data, handle):
    err = __abstracted_reg_write(data, Spectrum_Test_RegisterFile.SCI_REG_thrsh_1, handle)
    return err

def REG_inhib_GET(handle):
    [err, data] = __abstracted_reg_read(Spectrum_Test_RegisterFile.SCI_REG_inhib, handle)
    return err, data

def REG_inhib_SET(data, handle):
    err = __abstracted_reg_write(data, Spectrum_Test_RegisterFile.SCI_REG_inhib, handle)
    return err

def REG_delay_GET(handle):
    [err, data] = __abstracted_reg_read(Spectrum_Test_RegisterFile.SCI_REG_delay, handle)
    return err, data

def REG_delay_SET(data, handle):
    err = __abstracted_reg_write(data, Spectrum_Test_RegisterFile.SCI_REG_delay, handle)
    return err

def REG_gate_u_GET(handle):
    [err, data] = __abstracted_reg_read(Spectrum_Test_RegisterFile.SCI_REG_gate_u, handle)
    return err, data

def REG_gate_u_SET(data, handle):
    err = __abstracted_reg_write(data, Spectrum_Test_RegisterFile.SCI_REG_gate_u, handle)
    return err

def REG_top_1_GET(handle):
    [err, data] = __abstracted_reg_read(Spectrum_Test_RegisterFile.SCI_REG_top_1, handle)
    return err, data

def REG_top_1_SET(data, handle):
    err = __abstracted_reg_write(data, Spectrum_Test_RegisterFile.SCI_REG_top_1, handle)
    return err

def REG_int_time_GET(handle):
    [err, data] = __abstracted_reg_read(Spectrum_Test_RegisterFile.SCI_REG_int_time, handle)
    return err, data

def REG_int_time_SET(data, handle):
    err = __abstracted_reg_write(data, Spectrum_Test_RegisterFile.SCI_REG_int_time, handle)
    return err

def REG_pre_int_GET(handle):
    [err, data] = __abstracted_reg_read(Spectrum_Test_RegisterFile.SCI_REG_pre_int, handle)
    return err, data

def REG_pre_int_SET(data, handle):
    err = __abstracted_reg_write(data, Spectrum_Test_RegisterFile.SCI_REG_pre_int, handle)
    return err

def REG_baseline_GET(handle):
    [err, data] = __abstracted_reg_read(Spectrum_Test_RegisterFile.SCI_REG_baseline, handle)
    return err, data

def REG_baseline_SET(data, handle):
    err = __abstracted_reg_write(data, Spectrum_Test_RegisterFile.SCI_REG_baseline, handle)
    return err

def REG_stopwrite_GET(handle):
    [err, data] = __abstracted_reg_read(Spectrum_Test_RegisterFile.SCI_REG_stopwrite, handle)
    return err, data

def REG_stopwrite_SET(data, handle):
    err = __abstracted_reg_write(data, Spectrum_Test_RegisterFile.SCI_REG_stopwrite, handle)
    return err

def REG_write_GET(handle):
    [err, data] = __abstracted_reg_read(Spectrum_Test_RegisterFile.SCI_REG_write, handle)
    return err, data

def REG_write_SET(data, handle):
    err = __abstracted_reg_write(data, Spectrum_Test_RegisterFile.SCI_REG_write, handle)
    return err

def REG_read_GET(handle):
    [err, data] = __abstracted_reg_read(Spectrum_Test_RegisterFile.SCI_REG_read, handle)
    return err, data

def REG_read_SET(data, handle):
    err = __abstracted_reg_write(data, Spectrum_Test_RegisterFile.SCI_REG_read, handle)
    return err



def SPECTRUM_Spectrum_1_RESET(handle):
    err = __abstracted_reg_write(2, Spectrum_Test_RegisterFile.SCI_REG_Spectrum_1_CONFIG, handle)
    return err

def SPECTRUM_Spectrum_1_START(handle):
    err = __abstracted_reg_write(4, Spectrum_Test_RegisterFile.SCI_REG_Spectrum_1_CONFIG, handle)
    return err

def SPECTRUM_Spectrum_1_FLUSH(handle):
    err = __abstracted_reg_write(1, Spectrum_Test_RegisterFile.SCI_REG_Spectrum_1_CONFIG, handle)
    return err

def SPECTRUM_Spectrum_1_STOP(handle):
    err = __abstracted_reg_write(0, Spectrum_Test_RegisterFile.SCI_REG_Spectrum_1_CONFIG, handle)
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
    err = __abstracted_reg_write(rebin_value, Spectrum_Test_RegisterFile.SCI_REG_Spectrum_1_CONFIG_REBIN, handle)
    acq_mode=0
    if (AcquisitionMode =="Event"):
        acq_mode=(1 << 30) + TargetValue
    if (AcquisitionMode =="Time"):
        acq_mode=(1 << 31) + TargetValue*1000
    err = __abstracted_reg_write(acq_mode, Spectrum_Test_RegisterFile.SCI_REG_Spectrum_1_CONFIG_LIMIT, handle)
    return err

def SPECTRUM_Spectrum_1_GET_STATUS(handle):
    [err, status] = __abstracted_reg_read(Spectrum_Test_RegisterFile.SCI_REG_Spectrum_1_STATUS, handle)
    return err, status

def SPECTRUM_Spectrum_1_GET_DATA(Bin, timeout_ms, handle):
    [err, data, read_data, valid_data] = __abstracted_mem_read(Bin, Spectrum_Test_RegisterFile.SCI_REG_Spectrum_1_FIFOADDRESS, timeout_ms, handle)
    return err, data, read_data, valid_data

