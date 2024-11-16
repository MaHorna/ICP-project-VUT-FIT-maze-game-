CC=g++

all: 
	qmake src/icp_projekt_xhorna17.pro -o src/Makefile
	$(MAKE) -C src

run: all
	cd src; ./icp_projekt_xhorna17

doxygen:
	doxygen doc/Doxyfile
	
pack:
	zip -r xhorna17.zip src/ examples/ doc/ README.txt Makefile
	
clean:
	rm -rf src/*.o src/Makefile src/icp_projekt_xhorna17 src/moc_* doc/html doc/latex

