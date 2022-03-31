#Imports
import matplotlib.pyplot as plt
import matplotlib
import pandas as pd
import numpy as np

#Settings
matplotlib.use('tkagg') #Choose backend that can be x-forwarded to windows

#Get and arrange data
sourcedata = pd.read_csv("../../data/source_Na22/approx00-05-00_t250_i100-80-200-h50_g100-5.csv",header=None,usecols=[0]).to_numpy().flatten()
backgrounddata = pd.read_csv("../../data/out.csv",header=None,usecols=[0]).to_numpy().flatten()
#sourcedata = np.subtract(sourcedata,200*8192) 	#subtract the baseline (8192) times the gate value.
#backgrounddata = np.subtract(backgrounddata,200*8192)
min = sourcedata.min()
max = sourcedata.max()
print("min: ",min,", max: ",max)
print(sourcedata)
print("source data length: ",len(sourcedata))
print("background data length: ",len(backgrounddata))
if min - max <= 10000:
	bins = np.linspace(min,max)
else:
	bins = np.linspace(min,max,10000)

#print(data)

#plot
plt.hist(backgrounddata,bins=bins)
plt.hist(sourcedata,bins=bins)

plt.show()
