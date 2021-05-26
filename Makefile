
all: 
	cd src && ($(MAKE) ; cp final.txt ../ ; cp final.tex ../)

clean: 
	rm -f final.tex final.txt
	cd src && $(MAKE) clean

