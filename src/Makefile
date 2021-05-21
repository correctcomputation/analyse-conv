PATH_TO_SRC=./
NAME = All
TARGETS ?= Olden Ptrdist

all: final.tex final.txt

final.tex: final.csv
	./pretify.py > final.tex

final.txt: final.csv
	column -ts, final.csv > final.txt

final.csv:
	# Grab our headers
	./genfinal.py  > final.csv
	# Loop through targets and start 
	# append their final result to the global final
	for target in $(TARGETS); do \
	  (cd $$target && make && make stats); \
	  cat $$target/final.csv >> final.csv; \
	done

bear-test:
	for target in $(TARGETS) ; do \
		(cd $$target && \
		make $@) || exit 1; \
	done

clean:
	rm -f final.tex final.txt final.csv  
	for target in $(TARGETS); do \
	  (cd $$target && make clean); \
	done
