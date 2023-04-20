# Lab2 2023 - Hex to Dec

import pandas as pd
import sys

if len(sys.argv) == 1:
    print('/!\ ATTENTION!\nUsage: python3 HexToDec.py FileName.csv')
    exit()

path = sys.argv[1]

def HexToDec(s):
    l = []
    for el in s:
        elDec = int(el, 16)
        l.append(elDec)
    s = pd.Series(data=l)
    return s


df = pd.read_csv(path, header=None) #Produces a DataFrame type
# print(df)

for i in range(3,6):
    s_i = df.iloc[:,i] # Series of the i_th Hex column
    s_i = HexToDec(s_i)
    del df[i]
    df.insert(i, i, s_i)

del df[0] # Delete the first column of "_" which is useless
df.columns = ['N_event', 't_trig', 'tP1', 'tP2', 'tP3']
df.to_csv(path, header=True, index=False)
