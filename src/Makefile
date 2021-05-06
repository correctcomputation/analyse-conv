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

bear-test:
	for target in $(TARGETS) ; do \
		(cd $$target && \
		make $@) || exit 1; \
	done

clean:
	rm -f final.tex final.txt final.csv  
	TARGETS="$(TARGETS)" ./clean.sh
	
