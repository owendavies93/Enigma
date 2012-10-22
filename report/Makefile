all: EoIP.pdf

.phoney: all clean

EoIP.pdf: EoIP.tex
	pdflatex EoIP.tex

clean:
	rm -f *.aux 
	rm -f *.log
	rm -f *.pdf
