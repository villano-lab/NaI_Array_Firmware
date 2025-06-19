#Imports
import matplotlib.pyplot as plt
import matplotlib
import pandas as pd
import numpy as np

#Settings
matplotlib.use('tkagg') #Choose backend that can be x-forwarded to windows

#Get and arrange data
data = pd.read_csv("out.csv",header=None,usecols=[0]).to_numpy().flatten()
data = np.subtract(data[data != 0],8192)
bins = np.arange(data.min(),data.max()) #These are bin numbers, so distance 1 is always best.
#print(data)

#plot
plt.hist(data,bins=bins)
plt.show()
