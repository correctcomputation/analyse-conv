PATH_TO_SRC=./
NAME = All
TARGETS = Olden parson Ptrdist

all: final.tex final.txt

final.tex: final.csv
	./pretify.py > final.tex

final.txt: final.csv
	column -ts, final.csv > final.txt

final.csv:
	TARGETS="$(TARGETS)" ./tally_report.sh 

clean:
	rm -f final.tex final.txt final.csv  
	TARGETS="$(TARGETS)" ./clean.sh
	
