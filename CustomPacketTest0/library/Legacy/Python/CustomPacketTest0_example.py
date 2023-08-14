from CustomPacketTest0_Functions import *
from ctypes import *
import matplotlib.pyplot as plt
import time

board = "192.168.15.116"

if (1==1):

    Init()
    [err, handle] = ConnectDevice(board)
    if (err == 0):
        print("Successful connection to board ", board)
    else:
        print("Connection Error")


    plt.ion()
    plt.show()
    N_Packet = 100
    Timeout_ms = 1000
    N_Total_Events = 10000
    ReadDataNumber = 0
    if (CPACK_CP_0_RESET(handle) != 0):
        print("Reset Error!")
    if (CPACK_CP_0_START(handle) == True):
        [err, Frame_Status] = CPACK_CP_0_GET_STATUS(handle)
        if (Frame_Status >0):
            while(ReadDataNumber < N_Total_Events):
                [err, Frame_Data, Frame_Read_Data, Frame_Valid_Data] = CPACK_CP_0_GET_DATA(N_Packet, Timeout_ms, handle)
                [Time_Code, Pack_Id, Energy] = CPACK_CP_0_RECONSTRUCT_DATA(Frame_Data)                 
                ReadDataNumber += N_Packet
                print("Event Id: ", Pack_Id[0])
                plt.cla()
                plt.plot(Energy[0])
                plt.pause(0.01)
                print("Total Acquired Events: ", ReadDataNumber)
        else:
            print("Status Error")
    else:
        print("Start Error")

*/
