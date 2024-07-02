



import sync_test_RegisterFile
from ctypes import *
import os

mydll = cdll.LoadLibrary(os.path.dirname(__file__) +'/niusb3_core.dll')

def Init():
    err = mydll.NI_USB3_Init()
    return err

def ConnectDevice(board):
    handle = c_void_p(256)
    err = mydll.NI_USB3_ConnectDevice(board, byref(handle))
    return err, handle

def CloseConnect(handle):
    err = mydll.NI_USB3_CloseConnection(byref(handle))
    return err    
    
def ListDevices():
    count = c_int(0)
    s = create_string_buffer(2048)
    err = mydll.NI_USB3_ListDevices(byref(s), 0, byref(count))
    str_con = (s.value.decode('ascii')) 
    str_devices = str_con.split(';')
    dev_count = count.value
    return str_devices, dev_count 

def __abstracted_reg_write(data, address, handle):
    err = mydll.NI_USB3_WriteReg(data, address, byref(handle))
    return err

def __abstracted_reg_read(address, handle):
    data = c_uint(0)
    err = mydll.NI_USB3_ReadReg(byref(data), address, byref(handle))
    return err, data.value

def __abstracted_mem_write(data, count, address, timeout_ms, handle):
    written_data = c_uint(0)
    err = mydll.NI_USB3_WriteData(data, count, address, 0, timeout_ms, byref(handle), byref(written_data))
    return err, written_data.value

def __abstracted_fifo_read(count, address, address_status, blocking, timeout_ms, handle):
    data = (c_uint * (2* count))()
    read_data = c_uint(0)
    valid_data = c_uint(0)
    err = mydll.NI_USB3_ReadData(byref(data), count, address, 0, timeout_ms, byref(handle), byref(read_data), byref(valid_data))
    return err, data, read_data.value, valid_data.value

def __abstracted_fifo_write(data, count, address, timeout_ms, handle):
    written_data = c_uint(0)
    err = mydll.NI_USB3_WriteData(data, count, address, 1, timeout_ms, byref(handle), byref(written_data))
    return err, written_data.value

def __abstracted_fifo_read(count, address, timeout_ms, handle):
    data = (c_uint * (2 * count))()
    read_data = (c_int * 1)()
    valid_data = (c_int * 1)()
    err = mydll.NI_USB3_ReadData(byref(data), count, address, 1, timeout_ms, byref(handle), byref(read_data), byref(valid_data))
    return err, data, read_data, valid_data     
    
#def SetAFEBaseAddress(handle):
#    err = mydll.NI_USB3_SetIICControllerBaseAddress(sync_test_RegisterFile.SCI_AFE_REG_CTRL, sync_test_RegisterFile.SCI_AFE_REG_MON, byref(handle))
#    return err

def SetAFEOffset(top, value, handle):
    err = mydll.NI_USB3_SetOffset(top, value, byref(handle))   
    return err

def SetAFEImpedance(value, handle):
    err = mydll.NI_USB3_SetImpedance(value, byref(handle))
    return err




def RATE_METER_RateMeter_0_GET_DATA(channels, timeout_ms, handle):
    [err, data, read_data, valid_data] = __abstracted_mem_read(channels, sync_test_RegisterFile.SCI_REG_RateMeter_0_FIFOADDRESS, timeout_ms, handle)
    return err, data, read_data, valid_data




def RATE_METER_RateMeter_0_GET_DATA_COUNTS(channels, timeout_ms, handle):
    [err, data, read_data, valid_data] = __abstracted_mem_read(channels, sync_test_RegisterFile.SCI_REG_RateMeter_0_FIFOADDRESS + 512, timeout_ms, handle)
    return err, data, read_data, valid_data

