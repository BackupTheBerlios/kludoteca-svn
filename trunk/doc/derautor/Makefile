all:
	if [ -f derautor.pdf ]; then rm derautor.pdf; fi
	pdflatex derautor.tex
	if [ -f derautor.pdf ]; then xpdf derautor.pdf; else echo "Error generando presentacion"; fi

clean:
	rm *~ *.backup *.aux *.snm *.log  *.dvi *.out 2> /dev/null || true
	
