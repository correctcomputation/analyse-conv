#!/usr/bin/env python3

# This script compiles statistics from individual test programs 
# It wil extract the data we want from a given project, and then 
# dump the formatted output into a "workdir" such that many of these 
# tables can be catted together
# Usage: ./genfinal.py <program name>

import sys,csv,json
from typing import List


# Input format
# TEST,TOTAL_LINES,LINES_CHANGED
#  0  |      1    |     2      |
# Output format:
outheader = ['Program', 'Ver', 'Lines Refactored', 'Lines Annotated', '#ptr', '#ntarr', '#arr', '#wild', '#bounds', '#casts']

# If run w/ no arguments, just output the header
if len(sys.argv) < 2:
    print(','.join(outheader))
    exit(0)

program=sys.argv[1]


# Process a given row into our desired global output
def process_row(row : List[str]) -> str:
    row = row_to_int(row)
    test = row[0]
    refact = compute_percentage(row[2], row[1]) if test == 'orig-to-revert' else 'N/A'
    ptrstats = loadstats(test) if is3c(test) else ['N/A'] * 7
    outrow = [program, row[0], refact] + ptrstats
    assert(len(outrow) == len(outheader))
    return ','.join(outrow)

# Given a kind of test load the statistics file produced by that run of 3c
def loadstats(test_name: str) -> List[str]:
    with open('./%s/%s' % (program, test_to_statsfile(test_name))) as f:
        stats = json.load(f) 
    # Select
    stats = stats['AggregateStats'][0]['TotalStats']
    return [str(i) for i in ['N/A', stats['ptr'], stats['ntarr'], stats['arr'], stats['wild'], 'N/A', 'N/A']]

# Is this a test case that we have statistics for?
def is3c(test_name : str) -> bool:
    return test_name == 'orig-to-3c-orig' or test_name == 'revert-to-3c-revert'

# Map test case name to statistics file name
def test_to_statsfile(test_name : str) -> str:
    if test_name == 'orig-to-3c-orig':
        return 'origstats.json.aggregate.json'
    elif test_name == 'revert-to-3c-revert':
        return 'revertstats.json.aggregate.json'
    else:
        raise Error("This kind of test doesn't have pointer stats!")

# Compute percentage and format correctly
def compute_percentage(figure: int, total: int) -> str:
    assert(figure <= total)
    perc = (figure / total) * 100.0
    return '%d (%.2f %%)' % (figure, perc)



def safe_to_int(item):
    try:
        return int(item)
    except ValueError:
        return item

def row_to_int(row):
    return [safe_to_int(item) for item in row]

#-------------------------------------------------------------------------------- 
# Main
#-------------------------------------------------------------------------------- 


# Open the relevent file, parse CSV
with open('./' + program + '/diffs.sum') as f:
    reader = csv.reader(f)
    in_rows = [row for row in reader][1:]


outrows = [process_row(row) for row in in_rows]

# Write to workdir

outname = 'workdir/%s__result.csv' % program

with open(outname, 'w') as f:
    f.write('\n'.join(outrows))
    f.write('\n')
