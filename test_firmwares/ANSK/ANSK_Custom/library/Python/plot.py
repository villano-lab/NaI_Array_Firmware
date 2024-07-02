#Imports
import matplotlib.pyplot as plt
import matplotlib
import pandas as pd
import numpy as np

#Settings
matplotlib.use('tkagg') #Choose backend that can be x-forwarded to windows

#Get and arrange data
data150 = pd.read_csv("../../data/source_Na22/approx00-05-37_t250_i150-20-200_h50_g100-5.csv",header=None,usecols=[0]).to_numpy().flatten()
data100 = pd.read_csv("../../data/source_Na22/approx00-06-15_t250_i100-20-200_h50_g100-5.csv",header=None,usecols=[0]).to_numpy().flatten()
data50 = pd.read_csv("../../data/source_Na22/approx00-05-30_t250_i50-20-200_h50_g100-5.csv",header=None,usecols=[0]).to_numpy().flatten()
data25 = pd.read_csv("../../data/source_Na22/approx00-05-00_t250_i25-20-200_h50_g100-5.csv",header=None,usecols=[0]).to_numpy().flatten()
#sourcedata = np.subtract(sourcedata,200*8192) 	#subtract the baseline (8192) times the gate value.
#backgrounddata = np.subtract(backgrounddata,200*8192)
min = min(data100.min(),data150.min(),data50.min(),data25.min())
max = max(data100.max(),data150.max(),data50.max(),data25.max())
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
plt.hist(data100,bins=bins,label="integration time 100",alpha=0.6) 
plt.hist(data150,bins=bins,label="integration time 150",alpha=0.6)
plt.hist(data50,bins=bins,label="integration time 50",alpha=0.6)
plt.hist(data25,bins=bins,label="integration time 25",alpha=0.6)
plt.legend()
plt.show()
