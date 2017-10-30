all:
	if [! -f bin ] ; \
	then \
		mkdir bin ; \
	fi;
	if [! -f tmp ] ; \
	then \
		mkdir tmp ; \
	fi;

	if [! -f ./tmp/program.o ] ; \
	then \
		$(MAKE) -C ./src program.o ; \
	fi;

	if [! -f ./tmp/Enigma.o ] ; \
	then \
		$(MAKE) -C ./src Enigma.o ; \
	fi;

	if [! -f ./tmp/Rotor.o ] ; \
	then \
		$(MAKE) -C ./src Rotor.o ; \
	fi;

	if [ -f ./tmp/programa.o] ; \
	then \
		if [ -f ./tmp/Enigma.o ] ; \
		then \
			if [ -f ./tmp/Rotor.o ] ; \
			then \
				g++ -o program.exe program.o Enigma.o Rotor.o ; \
			fi; \
		fi; \
	fi;


program.o: program.cc Enigma.hh
	g++ -c program.cc -o ../tmp/program.o

Enigma.o: Enigma.hh Rotor.hh Enigma.cc
	g++ -c Enigma.cc -o ../tmp/Enigma.o

Rotor.o: Rotor.hh Rotor.cc
	g++ -c Rotor.cc -o ../tmp/Rotor.o

clean: clean_bin clean_tmp clean_src
clean_bin:
	if [ -f ./bin ] ; \
	then \
		rm -rf ./bin -y ; \
	fi;

clean_tmp:
	if [ -f ./tmp ] ; \
	then \
		rm -rf ./tmp -y ; \
	fi;

clean_src:
	if [ -f ./src/*.o ] ; \
	then \
		rm -f ./src/*.o ; \
	fi;
	if [ -f ./src/*.gch ] ; \
	then \
		rm -f ./src/*.gch ; \
	fi;
	if [ -f ./src/*.exe ] ; \
	then \
		rm -f ./src/*.exe ; \
	fi;
