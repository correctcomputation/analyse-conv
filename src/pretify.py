#!/usr/bin/env python3 

import csv,sys

with open('final.csv') as f:
    rows = [row for row in csv.reader(f)]

header = rows[0]
rows = rows[1:]

def escape(s):
    return s.replace('%', '\\%').replace('#', '\\#')

cs = 'c' * len(header)
print('\\tabcolsep=0.11cm')
print('\\begin{tabular}{||%s||}' % ' '.join(cs))
print('\\hline')
print(' & '.join(map(escape, header)) + ' \\\\ [0.5ex]')
print('\\hline\\hline')
for row in rows:
    print(' & '.join(map(escape, row)) + ' \\\\')
    print('\\hline')

print('\\end{tabular}')

