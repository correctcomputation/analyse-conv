#!/usr/bin/env python3 
# Produce a latex table from the final CSV

import csv,sys

with open('final.csv') as f:
    rows = [row for row in csv.reader(f)]

header = rows[0]
rows = rows[1:]

NAcolor = '\color{gray}'

def escape(s):
    if s == 'N/A':
        return '-'
    elif s == '0 (0.00 %)':
        return r'\textcolor{green}{\textbf{0 (0.00 \%)}}'
    else:
        return s.replace('%', '\\%').replace('#', '\\#')

def print_benchmark_header(bm):
    print(r'''
\midrule
\multicolumn{11}{c}{\textbf{%s}}\\
\midrule
'''.strip('\n') % bm)

# It might be cleaner to put this header in `manualtab.tex` in the paper, but
# \input of part of a table can cause problems in LaTeX
# (https://tex.stackexchange.com/questions/583927/misplaced-noalign-error-with-input-in-a-table-after-the-2020-fall-latex-releas).
print(r'''
\begin{tabular}{c|c|ccc|cccc|c|c}
\toprule
\multirow{2}{*}{\textbf{Program}} & \multirow{2}{*}{\textbf{Variation}} & \multicolumn{3}{c|}{\textbf{Source changes}} & \multicolumn{4}{c|}{\textbf{Pointers}}                       & \multirow{2}{*}{\textbf{Bounds}} & \multirow{2}{*}{\textbf{Casts}}                                                  \\ \cline{3-9} 
                                  &                                     & \textbf{Refactored}   & \textbf{Annotated} & \textbf{Left}  & \ptrb & \arrb & \ntarrb & \textbf{wild} &                                  & \\ 
'''.strip('\n'))

print_benchmark_header('Olden')
rownum = 0
last_prog = rows[0][0]
colors = ['\\rowcolor{white}','\\rowcolor[rgb]{0.8,0.8,0.8}']
color = 0
for row in rows:
    if row[0 : 2] == ['anagram','manual']:
        print_benchmark_header('PtrDist')
    if row[0] != last_prog:
        color = 1 - color
        last_prog = row[0]
    print(colors[color])
    # Match the idiosyncratic formatting of the existing table in the paper for
    # now to facilitate comparison. Once we're happy, we can clean up the
    # formatting.
    print(('' if rownum == 0 else ' ') + ' & '.join(map(escape, row)) + ' \\\\')
    print('')
    rownum += 1

print('\\bottomrule')
print('\\end{tabular}')

