
all: 
	bash -c "cd src && make && cp final.txt ../ && cp final.tex ../"

clean: 
	rm -f final.tex final.txt
	bash -c "cd src && make clean"

