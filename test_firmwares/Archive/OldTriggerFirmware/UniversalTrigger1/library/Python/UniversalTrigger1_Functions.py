



import UniversalTrigger1_RegisterFile
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

def REG_ratereset_GET(handle):
    [err, data] = __abstracted_reg_read(UniversalTrigger1_RegisterFile.SCI_REG_ratereset, handle)
    return err, data

def REG_ratereset_SET(data, handle):
    err = __abstracted_reg_write(data, UniversalTrigger1_RegisterFile.SCI_REG_ratereset, handle)
    return err

def REG_thrsh_GET(handle):
    [err, data] = __abstracted_reg_read(UniversalTrigger1_RegisterFile.SCI_REG_thrsh, handle)
    return err, data

def REG_thrsh_SET(data, handle):
    err = __abstracted_reg_write(data, UniversalTrigger1_RegisterFile.SCI_REG_thrsh, handle)
    return err

def REG_polarity_GET(handle):
    [err, data] = __abstracted_reg_read(UniversalTrigger1_RegisterFile.SCI_REG_polarity, handle)
    return err, data

def REG_polarity_SET(data, handle):
    err = __abstracted_reg_write(data, UniversalTrigger1_RegisterFile.SCI_REG_polarity, handle)
    return err

def REG_top_GET(handle):
    [err, data] = __abstracted_reg_read(UniversalTrigger1_RegisterFile.SCI_REG_top, handle)
    return err, data

def REG_top_SET(data, handle):
    err = __abstracted_reg_write(data, UniversalTrigger1_RegisterFile.SCI_REG_top, handle)
    return err

def REG_gate_GET(handle):
    [err, data] = __abstracted_reg_read(UniversalTrigger1_RegisterFile.SCI_REG_gate, handle)
    return err, data

def REG_gate_SET(data, handle):
    err = __abstracted_reg_write(data, UniversalTrigger1_RegisterFile.SCI_REG_gate, handle)
    return err

def REG_inhib_GET(handle):
    [err, data] = __abstracted_reg_read(UniversalTrigger1_RegisterFile.SCI_REG_inhib, handle)
    return err, data

def REG_inhib_SET(data, handle):
    err = __abstracted_reg_write(data, UniversalTrigger1_RegisterFile.SCI_REG_inhib, handle)
    return err

def REG_delay_GET(handle):
    [err, data] = __abstracted_reg_read(UniversalTrigger1_RegisterFile.SCI_REG_delay, handle)
    return err, data

def REG_delay_SET(data, handle):
    err = __abstracted_reg_write(data, UniversalTrigger1_RegisterFile.SCI_REG_delay, handle)
    return err

def REG_disable_det_0_GET(handle):
    [err, data] = __abstracted_reg_read(UniversalTrigger1_RegisterFile.SCI_REG_disable_det_0, handle)
    return err, data

def REG_disable_det_0_SET(data, handle):
    err = __abstracted_reg_write(data, UniversalTrigger1_RegisterFile.SCI_REG_disable_det_0, handle)
    return err

def REG_disable_det_1_GET(handle):
    [err, data] = __abstracted_reg_read(UniversalTrigger1_RegisterFile.SCI_REG_disable_det_1, handle)
    return err, data

def REG_disable_det_1_SET(data, handle):
    err = __abstracted_reg_write(data, UniversalTrigger1_RegisterFile.SCI_REG_disable_det_1, handle)
    return err

def REG_disable_det_2_GET(handle):
    [err, data] = __abstracted_reg_read(UniversalTrigger1_RegisterFile.SCI_REG_disable_det_2, handle)
    return err, data

def REG_disable_det_2_SET(data, handle):
    err = __abstracted_reg_write(data, UniversalTrigger1_RegisterFile.SCI_REG_disable_det_2, handle)
    return err

def REG_disable_det_3_GET(handle):
    [err, data] = __abstracted_reg_read(UniversalTrigger1_RegisterFile.SCI_REG_disable_det_3, handle)
    return err, data

def REG_disable_det_3_SET(data, handle):
    err = __abstracted_reg_write(data, UniversalTrigger1_RegisterFile.SCI_REG_disable_det_3, handle)
    return err

def REG_disable_det_4_GET(handle):
    [err, data] = __abstracted_reg_read(UniversalTrigger1_RegisterFile.SCI_REG_disable_det_4, handle)
    return err, data

def REG_disable_det_4_SET(data, handle):
    err = __abstracted_reg_write(data, UniversalTrigger1_RegisterFile.SCI_REG_disable_det_4, handle)
    return err

def REG_disable_det_5_GET(handle):
    [err, data] = __abstracted_reg_read(UniversalTrigger1_RegisterFile.SCI_REG_disable_det_5, handle)
    return err, data

def REG_disable_det_5_SET(data, handle):
    err = __abstracted_reg_write(data, UniversalTrigger1_RegisterFile.SCI_REG_disable_det_5, handle)
    return err

def REG_disable_det_6_GET(handle):
    [err, data] = __abstracted_reg_read(UniversalTrigger1_RegisterFile.SCI_REG_disable_det_6, handle)
    return err, data

def REG_disable_det_6_SET(data, handle):
    err = __abstracted_reg_write(data, UniversalTrigger1_RegisterFile.SCI_REG_disable_det_6, handle)
    return err

def REG_disable_det_7_GET(handle):
    [err, data] = __abstracted_reg_read(UniversalTrigger1_RegisterFile.SCI_REG_disable_det_7, handle)
    return err, data

def REG_disable_det_7_SET(data, handle):
    err = __abstracted_reg_write(data, UniversalTrigger1_RegisterFile.SCI_REG_disable_det_7, handle)
    return err

def REG_disable_det_8_GET(handle):
    [err, data] = __abstracted_reg_read(UniversalTrigger1_RegisterFile.SCI_REG_disable_det_8, handle)
    return err, data

def REG_disable_det_8_SET(data, handle):
    err = __abstracted_reg_write(data, UniversalTrigger1_RegisterFile.SCI_REG_disable_det_8, handle)
    return err

def REG_disable_det_9_GET(handle):
    [err, data] = __abstracted_reg_read(UniversalTrigger1_RegisterFile.SCI_REG_disable_det_9, handle)
    return err, data

def REG_disable_det_9_SET(data, handle):
    err = __abstracted_reg_write(data, UniversalTrigger1_RegisterFile.SCI_REG_disable_det_9, handle)
    return err

def REG_disable_det_10_GET(handle):
    [err, data] = __abstracted_reg_read(UniversalTrigger1_RegisterFile.SCI_REG_disable_det_10, handle)
    return err, data

def REG_disable_det_10_SET(data, handle):
    err = __abstracted_reg_write(data, UniversalTrigger1_RegisterFile.SCI_REG_disable_det_10, handle)
    return err

def REG_disable_det_11_GET(handle):
    [err, data] = __abstracted_reg_read(UniversalTrigger1_RegisterFile.SCI_REG_disable_det_11, handle)
    return err, data

def REG_disable_det_11_SET(data, handle):
    err = __abstracted_reg_write(data, UniversalTrigger1_RegisterFile.SCI_REG_disable_det_11, handle)
    return err

def REG_disable_det_12_GET(handle):
    [err, data] = __abstracted_reg_read(UniversalTrigger1_RegisterFile.SCI_REG_disable_det_12, handle)
    return err, data

def REG_disable_det_12_SET(data, handle):
    err = __abstracted_reg_write(data, UniversalTrigger1_RegisterFile.SCI_REG_disable_det_12, handle)
    return err

def REG_disable_det_13_GET(handle):
    [err, data] = __abstracted_reg_read(UniversalTrigger1_RegisterFile.SCI_REG_disable_det_13, handle)
    return err, data

def REG_disable_det_13_SET(data, handle):
    err = __abstracted_reg_write(data, UniversalTrigger1_RegisterFile.SCI_REG_disable_det_13, handle)
    return err

def REG_disable_det_14_GET(handle):
    [err, data] = __abstracted_reg_read(UniversalTrigger1_RegisterFile.SCI_REG_disable_det_14, handle)
    return err, data

def REG_disable_det_14_SET(data, handle):
    err = __abstracted_reg_write(data, UniversalTrigger1_RegisterFile.SCI_REG_disable_det_14, handle)
    return err

def REG_disable_det_15_GET(handle):
    [err, data] = __abstracted_reg_read(UniversalTrigger1_RegisterFile.SCI_REG_disable_det_15, handle)
    return err, data

def REG_disable_det_15_SET(data, handle):
    err = __abstracted_reg_write(data, UniversalTrigger1_RegisterFile.SCI_REG_disable_det_15, handle)
    return err

def REG_disable_det_16_GET(handle):
    [err, data] = __abstracted_reg_read(UniversalTrigger1_RegisterFile.SCI_REG_disable_det_16, handle)
    return err, data

def REG_disable_det_16_SET(data, handle):
    err = __abstracted_reg_write(data, UniversalTrigger1_RegisterFile.SCI_REG_disable_det_16, handle)
    return err

def REG_disable_det_17_GET(handle):
    [err, data] = __abstracted_reg_read(UniversalTrigger1_RegisterFile.SCI_REG_disable_det_17, handle)
    return err, data

def REG_disable_det_17_SET(data, handle):
    err = __abstracted_reg_write(data, UniversalTrigger1_RegisterFile.SCI_REG_disable_det_17, handle)
    return err

def REG_disable_det_18_GET(handle):
    [err, data] = __abstracted_reg_read(UniversalTrigger1_RegisterFile.SCI_REG_disable_det_18, handle)
    return err, data

def REG_disable_det_18_SET(data, handle):
    err = __abstracted_reg_write(data, UniversalTrigger1_RegisterFile.SCI_REG_disable_det_18, handle)
    return err

def REG_disable_det_19_GET(handle):
    [err, data] = __abstracted_reg_read(UniversalTrigger1_RegisterFile.SCI_REG_disable_det_19, handle)
    return err, data

def REG_disable_det_19_SET(data, handle):
    err = __abstracted_reg_write(data, UniversalTrigger1_RegisterFile.SCI_REG_disable_det_19, handle)
    return err

def REG_disable_det_20_GET(handle):
    [err, data] = __abstracted_reg_read(UniversalTrigger1_RegisterFile.SCI_REG_disable_det_20, handle)
    return err, data

def REG_disable_det_20_SET(data, handle):
    err = __abstracted_reg_write(data, UniversalTrigger1_RegisterFile.SCI_REG_disable_det_20, handle)
    return err

def REG_disable_det_21_GET(handle):
    [err, data] = __abstracted_reg_read(UniversalTrigger1_RegisterFile.SCI_REG_disable_det_21, handle)
    return err, data

def REG_disable_det_21_SET(data, handle):
    err = __abstracted_reg_write(data, UniversalTrigger1_RegisterFile.SCI_REG_disable_det_21, handle)
    return err

def REG_disable_det_22_GET(handle):
    [err, data] = __abstracted_reg_read(UniversalTrigger1_RegisterFile.SCI_REG_disable_det_22, handle)
    return err, data

def REG_disable_det_22_SET(data, handle):
    err = __abstracted_reg_write(data, UniversalTrigger1_RegisterFile.SCI_REG_disable_det_22, handle)
    return err

def REG_disable_det_23_GET(handle):
    [err, data] = __abstracted_reg_read(UniversalTrigger1_RegisterFile.SCI_REG_disable_det_23, handle)
    return err, data

def REG_disable_det_23_SET(data, handle):
    err = __abstracted_reg_write(data, UniversalTrigger1_RegisterFile.SCI_REG_disable_det_23, handle)
    return err

def REG_disable_det_24_GET(handle):
    [err, data] = __abstracted_reg_read(UniversalTrigger1_RegisterFile.SCI_REG_disable_det_24, handle)
    return err, data

def REG_disable_det_24_SET(data, handle):
    err = __abstracted_reg_write(data, UniversalTrigger1_RegisterFile.SCI_REG_disable_det_24, handle)
    return err




def RATE_METER_RateMeter_0_GET_DATA(channels, timeout_ms, handle):
    [err, data, read_data, valid_data] = __abstracted_mem_read(channels, UniversalTrigger1_RegisterFile.SCI_REG_RateMeter_0_FIFOADDRESS, timeout_ms, handle)
    return err, data, read_data, valid_data




def RATE_METER_RateMeter_0_GET_DATA_COUNTS(channels, timeout_ms, handle):
    [err, data, read_data, valid_data] = __abstracted_mem_read(channels, UniversalTrigger1_RegisterFile.SCI_REG_RateMeter_0_FIFOADDRESS + 512, timeout_ms, handle)
    return err, data, read_data, valid_data
