#!/usr/bin/env python3

# This script compiles statistics from individual test programs 
# It wil extract the data we want from a given project, and then 
# dump the formatted output into a "workdir" such that many of these 
# tables can be catted together
# Usage: ./genfinal.py <program name>

import sys,csv,json
from typing import List

# Input format
# TEST,REFACTOR_LINES,REFACTOR_TOTAL,ANNOTATED_LINES,ANNOTATED_TOTAL,LEFT_LINES,LEFT_TOTAL
#  0  |      1       |     2        |        3      |      4       |

# NOTE: uncomment/swap to omit lines left from table
# Output format:
outheader = ['Program', 'Version', 'Lines Refactored', 'Lines Annotated', 'Lines Left',  '#ptr', '#ntarr', '#arr', '#wild', '#bounds', '#casts']
#outheader = ['Program', 'Version', 'Lines Refactored', 'Lines Annotated', '#ptr', '#ntarr', '#arr', '#wild', '#bounds', '#casts']
# If run w/ no arguments, just output the header
if len(sys.argv) < 2:
    print(','.join(outheader))
    exit(0)

program=sys.argv[1]


# Process a given row into our desired global output
def process_row(row : List[str]) -> str:
    row = row_to_int(row)
    version = row[0] 
    if version == 'manual':
        out = [program, version, compute_percentage(row[1], row[2]), compute_percentage(row[3], row[4]), 'N/A'] + loadstats(version)
# NOTE: uncomment/swap to omit lines left from table
#        out = [program, version, compute_percentage(row[1], row[2]), compute_percentage(row[3], row[4])] + loadstats(version)
    else:
        out = [program, version, 'N/A', compute_percentage(row[3], row[4]), compute_percentage(row[5], row[6])] + loadstats(version)
# NOTE: uncomment/swap to omit lines left from table
#        out = [program, version, 'N/A', compute_percentage(row[3], row[4])] + loadstats(version)
    assert(len(out) == len(outheader))
    return ','.join(out)

    

# Given a kind of test load the statistics file produced by that run of 3c
def loadstats(test_name: str) -> List[str]:
    try:
        with open('./%s/%s' % (program, test_to_statsfile(test_name))) as f:
            stats = json.load(f) 
    except FileNotFoundError:
        return ['N/A'] * 6
    # Select
    ptrstats = stats['AggregateStats'][0]['TotalStats']
    casts = sum(stats['AggregateStats'][3]['PerformanceStats'][1]['ReWriteStats'].values())
    bounds = stats['AggregateStats'][1]['ArrBoundsStats']['NumPointersNeedBounds']
    return [str(i) for i in [ptrstats['ptr'], ptrstats['ntarr'], ptrstats['arr'], ptrstats['wild'], bounds, casts]]


# Map test case name to statistics file name
def test_to_statsfile(test_name : str) -> str:
    if test_name == 'orig':
        return 'origstats.json.aggregate.json'
    elif test_name == 'revert':
        return 'revertstats.json.aggregate.json'
    elif test_name == 'manual':
        return 'manualstats.json.aggregate.json'
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
