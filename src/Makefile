PATH_TO_SRC=./
NAME = All
TARGETS ?= Olden Ptrdist

report:
	# Grab our headers
	./genfinal.py  > final.csv
	# Loop through targets and start 
	# append their final result to the global final
	for target in $(TARGETS); do \
		(cd $$target && ($(MAKE) report VERSIONS= \
			"3c-manual 3c-em-orig 3c-revert-em-manual 3c-em-tweak"; \
		$(MAKE) $@)); \
		cat $$target/final.csv >> final.csv; \
		true; \
	done
	-./pretify.py > final.tex
	-column -ts, final.csv > final.txt

report_fmt_early:
	# Grab our headers
	./genfinal_early.py  > final.csv
	# Loop through targets and start 
	# append their final result to the global final
	for target in $(TARGETS); do \
		(cd $$target && ($(MAKE) report_fmt_early VERSIONS= \
			"fmt-3c-em-orig_early fmt-revert-em-manual_early fmt-3c-revert-em-manual_early fmt-em-manual_early fmt-em-orig_early fmt-em-tweak fmt-3c-em-tweak"; \
		$(MAKE) $@)); \
		cat $$target/final.csv >> final.csv; \
		true; \
	done
	-./pretify.py > final.tex
	-column -ts, final.csv > final.txt

bear-test:
	for target in $(TARGETS) ; do \
		(cd $$target && \
		$(MAKE) $@) || exit 1; \
	done

clean:
	rm -f final.tex final.txt final.csv  
	for target in $(TARGETS); do \
	  (cd $$target && $(MAKE) clean); \
	done
