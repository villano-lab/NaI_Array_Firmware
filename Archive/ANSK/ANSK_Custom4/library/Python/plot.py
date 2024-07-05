#Imports
import matplotlib.pyplot as plt
import matplotlib
import pandas as pd
import numpy as np

#Settings
matplotlib.use('tkagg') #Choose backend that can be x-forwarded to windows

#Get and arrange data
data3 = pd.read_csv("../../../ANSK_Custom3/data/source_Na22/approx00-05-37_t250_i50-20-200_h50_g100-5.csv",header=None,usecols=[0]).to_numpy().flatten()
data1 = pd.read_csv("../../../ANSK_Custom/data/source_Na22/approx00-05-30_t250_i50-20-200_h50_g100-5.csv",header=None,usecols=[0]).to_numpy().flatten()
data4 = pd.read_csv("../../data/source_Na22/00-05-06_t250_i50-20-200_h50_g100-5.csv",header=None,usecols=[0]).to_numpy().flatten()
data42 = pd.read_csv("../../data/source_Na22/00-05-08_t250_i100-20-200_h50_g100-5.csv",header=None,usecols=[0]).to_numpy().flatten()
data43 = pd.read_csv("../../data/source_Na22/00-05-17_t250_i150-20-200_h50_g100-5.csv",header=None,usecols=[0]).to_numpy().flatten()
#sourcedata = np.subtract(sourcedata,200*8192) 	#subtract the baseline (8192) times the gate value.
#backgrounddata = np.subtract(backgrounddata,200*8192)
min = min(data3.min(),data1.min(),data4.min(),data42.min(),data43.min())
max = max(data3.max(),data1.max(),data4.max(),data42.max(),data43.max())
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
plt.hist(data3,bins=bins,label="Firmware Version 3",alpha=0.6) 
plt.hist(data1,bins=bins,label="Firmware Version 1",alpha=0.6) 
plt.hist(data4,bins=bins,label="Firmware Version 4",alpha=0.6)
plt.hist(data42,bins=bins,label="Firmware Version 4, inttime 100",alpha=0.6)
plt.hist(data43,bins=bins,label="Firmware Version 4, inttime 150",alpha=0.6)
plt.legend()
plt.show()
