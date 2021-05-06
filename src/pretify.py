#!/usr/bin/env python3 
# Produce a latex table from the final CSV

import csv,sys

with open('final.csv') as f:
    rows = [row for row in csv.reader(f)]

header = rows[0]
rows = rows[1:]

def escape(s):
    return s.replace('%', '\\%').replace('#', '\\#')

cs = 'c' * (len(header) + 1)
print('\\tabcolsep=0.11cm')
print('\\begin{tabular}{||%s||}' % ' '.join(cs))
print('\\hline')
print('BM & ' + ' & '.join(map(escape, header)) + ' \\\\ [0.5ex]')
print('\\hline\\hline')
bm = 'olde'
rownum = 0
last_prog = rows[0][0]
colors = ['\\rowcolor{white}','\\rowcolor[rgb]{0.8,0.8,0.8}']
color = 0
for row in rows:
    if row[0 : 2] == ['anagram','manual']:
        bm = 'ptrd'
        print('\\hline')
    if row[0] != last_prog:
        color = 1 - color
        last_prog = row[0]
    print(colors[color])
    print(bm + ' & ' + ' & '.join(map(escape, row)) + ' \\\\')
    print('\\hline')
    bm = ''
    rownum += 1

print('\\end{tabular}')

