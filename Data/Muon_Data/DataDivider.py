# DataDivider.py
# This file takes the csv and DIVIDES it into 3 csv of every COLUMN (tP1, tP2, tP3)

import pandas as pd
import sys

path = sys.argv[1]

df = pd.read_csv(path) #Produces a DataFrame type

path_P1 = 'R3_background_P1.csv'
path_P2 = 'R3_background_P2.csv'
path_P3 = 'R3_background_P3.csv'

df_P1 = df.copy()
df_P2 = df.copy()
df_P3 = df.copy()

######################## P1 ######################
del df_P1['tP2']
del df_P1['tP3']

for i in range(len(df_P1)):
    if df_P1['tP1'][i] == 4095:
        df_P1 = df_P1.drop(i)

######################## P2 ######################
del df_P2['tP1']
del df_P2['tP3']

for i in range(len(df_P2)):
    if df_P2['tP2'][i] == 4095:
        df_P2 = df_P2.drop(i)

######################## P3 ######################
del df_P3['tP1']
del df_P3['tP2']

for i in range(len(df_P3)):
    if df_P3['tP3'][i] == 4095:
        df_P3 = df_P3.drop(i)

#################################################
df_P1.to_csv(path_P1, header=True, index=False)
df_P2.to_csv(path_P2, header=True, index=False)
df_P3.to_csv(path_P3, header=True, index=False)

