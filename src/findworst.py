#!/usr/bin/env python3

import csv,pdb
from collections import defaultdict

def isint(s : str) -> bool:
    try:
        x = int(s)
        return True
    except ValueError:
        return False

with open('final.csv') as f:
    table = [row for row in csv.reader(f) if len(row) != 0 and isint(row[4])] 

data = defaultdict(dict)


for row in table:
    if row[1] == 'manual':
        data[row[0]]['manual'] = int(row[4])
    elif row[1] == 'revert':
        data[row[0]]['revert'] = int(row[4])
    else:
        continue

results = [[name, v['manual'], v['revert'], abs(v['manual'] - v['revert'])] for (name,v) in data.items()] 
results.sort(key = lambda r: r[3])

print('Program,Manual Ptrs,Revert Ptrs,Difference')
for result in results[::-1]:
    print(','.join(map(str, result)))









