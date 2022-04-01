#Imports
import matplotlib.pyplot as plt
import matplotlib
import pandas as pd
import numpy as np

#Settings
matplotlib.use('tkagg') #Choose backend that can be x-forwarded to windows

#Get and arrange data
data5 = pd.read_csv("../../data/source_Na22/00-03-11_t250_i100-20-200_h50_g100-5.csv",header=None,usecols=[0]).to_numpy().flatten()
data4 = pd.read_csv("../../../ANSK_Custom4/data/source_Na22/00-05-08_t250_i100-20-200_h50_g100-5.csv",header=None,usecols=[0]).to_numpy().flatten()
#sourcedata = np.subtract(sourcedata,200*8192) 	#subtract the baseline (8192) times the gate value.
#backgrounddata = np.subtract(backgrounddata,200*8192)
min = min(data5.min(),data4.min())
max = max(data5.max(),data4.max())
print("min: ",min,", max: ",max)
#print(sourcedata)
#print("source data length: ",len(sourcedata))
#print("background data length: ",len(backgrounddata))
if min - max <= 10000:
	bins = np.arange(min,max) #bin sizes of 1
else:
	bins = np.linspace(min,max,10000) #make wider bins to avoid too much memory usage.

#print(data)

#plot
plt.hist(data5,bins=bins,label="Firmware Version 5",alpha=0.6)  
plt.hist(data4,bins=bins,label="Firmware Version 4",alpha=0.6)
plt.legend()
plt.show()
