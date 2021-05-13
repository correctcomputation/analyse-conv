PATH_TO_SRC=./
NAME = All
TARGETS = Olden Ptrdist

all: checkenv final.tex final.txt

checkenv:
	./checkenv.sh

final.tex: final.csv
	./pretify.py > final.tex

final.txt: final.csv
	column -ts, final.csv > final.txt

final.csv:
	TARGETS="$(TARGETS)" ./tally_report.sh 

include $(PATH_TO_SRC)Makefile.directory

