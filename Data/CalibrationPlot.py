# Python script to calculate MEAN and STDDEV of calibration .csv files

import pandas as pd
import sys

if len(sys.argv) == 1:
    print('/!\ ATTENTION!\nUsage: python3 HexToDec.py FileName.csv')
    exit()

path = sys.argv[1]

df = pd.read_csv(path) #Produces a DataFrame type

# print(df.tP1)

for i in range(2,5):
    s_i = df.iloc[:,i] # Series of the i_th Hex column
    print('mean:', s_i.mean(), 'std:', s_i.std())
    
