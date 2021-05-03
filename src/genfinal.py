#!/usr/bin/env python3

import sys,csv,pdb


# Input format
# TEST,TOTAL_LINES,LINES_CHANGED
#  0  |      1    |     2      |
outheader = ['Program', 'Ver', 'Lines Refactored', 'Lines Annotated', '#ptr', '#ntarr', '#wild', '#bounds', '#casts']

if len(sys.argv) < 2:
    print(','.join(outheader))
    exit(0)

program=sys.argv[1]

def safe_to_int(item):
    try:
        return int(item)
    except ValueError:
        return item

def row_to_int(row):
    return [safe_to_int(item) for item in row]

def compute_percentage(figure, total):
    assert(figure <= total)
    perc = (figure / total) * 100.0
    return '%d (%.2f %%)' % (figure, perc)

def process_row(row):
    row = row_to_int(row)
    refact = compute_percentage(row[2], row[1])
    outrow = [program, row[0], refact, 'NA', 'NA', 'NA', 'NA', 'NA', 'NA']
    assert(len(outrow) == len(outheader))
    return ','.join(outrow)


with open('./' + program + '/diffs.sum') as f:
    reader = csv.reader(f)
    in_rows = [row for row in reader][1:]


outrows = [process_row(row) for row in in_rows]

outname = 'workdir/%s__result.csv' % program

with open(outname, 'w') as f:
    f.write('\n'.join(outrows))
    f.write('\n')
