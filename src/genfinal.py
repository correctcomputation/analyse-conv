#!/usr/bin/env python3

import sys,csv,pdb,json


# Input format
# TEST,TOTAL_LINES,LINES_CHANGED
#  0  |      1    |     2      |
outheader = ['Program', 'Ver', 'Lines Refactored', 'Lines Annotated', '#ptr', '#ntarr', '#arr', '#wild', '#bounds', '#casts']

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

def is3c(test_name):
    return test_name == 'orig-to-3c-orig' or test_name == 'revert-to-3c-revert'

def test_to_statsfile(test_name):
    if test_name == 'orig-to-3c-orig':
        return 'origstats.json.aggregate.json'
    elif test_name == 'revert-to-3c-revert':
        return 'revertstats.json.aggregate.json'
    else:
        raise Error("This kind of test doesn't have pointer stats!")

def loadstats(test_name):
    with open('./%s/%s' % (program, test_to_statsfile(test_name))) as f:
        stats = json.load(f) 
    # Select
    stats = stats['AggregateStats'][0]['TotalStats']
    return [str(i) for i in ['N/A', stats['ptr'], stats['ntarr'], stats['arr'], stats['wild'], 'N/A', 'N/A']]


def process_row(row):
    row = row_to_int(row)
    refact = compute_percentage(row[2], row[1])
    test = row[0]
    ptrstats = loadstats(test) if is3c(test) else ['N/A'] * 7
    outrow = [program, row[0], refact] + ptrstats
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
