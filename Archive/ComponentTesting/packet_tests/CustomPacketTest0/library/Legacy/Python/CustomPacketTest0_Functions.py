


import CustomPacketTest0_RegisterFile
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




def CPACK_CP_0_RESET(handle):
    err = __abstracted_reg_write(2, CustomPacketTest0_RegisterFile.SCI_REG_CP_0_CONFIG, handle)
    err = __abstracted_reg_write(0, CustomPacketTest0_RegisterFile.SCI_REG_CP_0_CONFIG, handle)
    return err

def CPACK_CP_0_FLUSH(handle):
    err = __abstracted_reg_write(4, CustomPacketTest0_RegisterFile.SCI_REG_CP_0_CONFIG, handle)
    err = __abstracted_reg_write(0, CustomPacketTest0_RegisterFile.SCI_REG_CP_0_CONFIG, handle)
    return err

def CPACK_CP_0_START(handle):
    err = __abstracted_reg_write(2, CustomPacketTest0_RegisterFile.SCI_REG_CP_0_CONFIG, handle)
    if (err != 0):
       return False
    err = __abstracted_reg_write(0, CustomPacketTest0_RegisterFile.SCI_REG_CP_0_CONFIG, handle)
    if (err != 0):
       return False
    err = __abstracted_reg_write(1, CustomPacketTest0_RegisterFile.SCI_REG_CP_0_CONFIG, handle)
    if (err != 0):
       return False
    return True

def CPACK_CP_0_GET_STATUS(handle):
    [err, status] = __abstracted_reg_read(CustomPacketTest0_RegisterFile.SCI_REG_CP_0_READ_STATUS, handle)
    status = status & 0xf
    return err, status

def CPACK_CP_0_GET_AVAILABLE_DATA(handle):
    [err, status] = __abstracted_reg_read(CustomPacketTest0_RegisterFile.SCI_REG_CP_0_READ_VALID_WORDS, handle)
    return err, status

def CPACK_CP_0_GET_DATA(n_packet, timeout_ms, handle):
    data_length = n_packet *( 3 + <<<NUMBER OF PACKET LINES AFTER THE HEADER HERE>>>)
    [err, data, read_data, valid_data] = __abstracted_fifo_read(data_length, CustomPacketTest0_RegisterFile.SCI_REG_CP_0_FIFOADDRESS, CustomPacketTest0_RegisterFile.SCI_REG_CP_0_READ_STATUS, True, timeout_ms, handle)
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

