
report%: 
	cd src && ($(MAKE) $@; cp final* ../)

clean: 
	rm -f final.tex final.txt
	cd src && $(MAKE) clean

