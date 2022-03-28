#Imports
import matplotlib.pyplot as plt
import matplotlib
import pandas as pd
import numpy as np

#Settings
matplotlib.use('tkagg') #Choose backend that can be x-forwarded to windows

#Get and arrange data
sourcedata = pd.read_csv("../../data/out.csv",header=None,usecols=[0]).to_numpy().flatten()
#backgrounddata = pd.read_csv("../../data/out.csv",header=None,usecols=[0]).to_numpy().flatten()
sourcedata = np.subtract(sourcedata,200*8192) 	#subtract the baseline (8192) times the gate value.
#backgrounddata = np.subtract(backgrounddata,200*8192)
#bins = np.arange(min(backgrounddata.min(),sourcedata.min()),max(backgrounddata.max(),sourcedata.max()))#Data are bin numbers, so distance <1 will cause gaps.
bins = np.arange(sourcedata.min(),sourcedata.max())

#print(data)

#plot
plt.hist(sourcedata,bins=bins)
#plt.hist(backgrounddata,bins=bins)
plt.show()
