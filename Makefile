
all: 
	cd src && (make ; cp final.txt ../ ; cp final.tex ../)

clean: 
	rm -f final.tex final.txt
	cd src && make clean

