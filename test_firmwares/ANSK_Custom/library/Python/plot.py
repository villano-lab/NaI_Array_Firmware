#Imports
import matplotlib.pyplot as plt
import matplotlib
import pandas as pd
import numpy as np

#Settings
matplotlib.use('tkagg') #Choose backend that can be x-forwarded to windows

#Get and arrange data
data50 = pd.read_csv("../../data/source_Na22/approx00-05-15_t250_i100-50-200_h50_g100-5.csv",header=None,usecols=[0]).to_numpy().flatten()
data80 = pd.read_csv("../../data/source_Na22/approx00-05-15_t250_i100-80-200_h50_g100-5.csv",header=None,usecols=[0]).to_numpy().flatten()
data20 = pd.read_csv("../../data/source_Na22/approx00-06-15_t250_i100-20-200_h50_g100-5",header=None,usecols=[0]).to_numpy().flatten()
#sourcedata = np.subtract(sourcedata,200*8192) 	#subtract the baseline (8192) times the gate value.
#backgrounddata = np.subtract(backgrounddata,200*8192)
min = min(data80.min(),data50.min(),data20.min())
max = max(data80.max(),data50.max(),data20.max())
print("min: ",min,", max: ",max)
#print(sourcedata)
#print("source data length: ",len(sourcedata))
#print("background data length: ",len(backgrounddata))
if min - max <= 10000:
	bins = np.linspace(min,max)
else:
	bins = np.linspace(min,max,10000)

#print(data)

#plot
plt.hist(data80,bins=bins,label="pre=80",alpha=0.6)
plt.hist(data50,bins=bins,label="pre=50",alpha=0.6)
plt.hist(data20,bins=bins,label="pre=20",alpha=0.6)
plt.legend()
plt.show()
