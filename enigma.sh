#Set variables
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

#Compiler funtion
Compile() {
	touch $2
	g++ -o $2 -c $1
}

#Creating the bin directory.
CreateBin() {
	if [ -d bin ] ;
	then
		echo -e "${GREEN}The bin directory already exists.${NC}" ;
	else
		if mkdir bin ;
		then
			echo -e  "${GREEN}The bin directory has been created correctly.${NC}"	;
		else
			echo -e "${RED}Error: Could not create bin directory.${NC}" ;
			kill -SIGKILL $$ ;
		fi;
	fi;
}

#Creating the tmp directory.
CreateTmp() {
	if [ -d tmp ] ;
	then
		echo -e "${GREEN}The tmp directory already exists.${NC}" ;
		rm -fr tmp ;
	fi;
	if mkdir tmp ;
	then echo -e "${GREEN}The tmp directory has been created correctly.${NC}" ;
	else echo -e "${Error: Could not create tmp directory.}${NC}" ; kill -SIGKILL $$ ;
	fi;
}

#Compiling the main object (program.cc)
CompileProgram() {
	if [ -f ./tmp/program.o ] ;
	then
		echo -e "${GREEN}The file program.o already exists.${NC}" ;
	else
		if [ -f ./src/program.cc ] && [ -f ./src/Enigma.hh ] ;
		then
			if Compile ./src/program.cc ./tmp/program.o ;
			then echo -e "${GREEN}program.cc compiled successfully.${NC}" ;
			else echo -e "${RED}Error: program.cc could not be compiled successfully.${NC}" ;
			fi;
		fi;
	fi;
}

#Compiling the Enigma object (Enigma.cc)
CompileEnigma() {
	if [ -f ./tmp/Enigma.o ] ;
	then
		echo -e "${GREEN}The file Enigma.o already exists.${NC}" ;
	else
		if [ -f ./src/Enigma.cc ] && [ -f ./src/Enigma.hh ] && [ -f ./src/Rotor.hh ] ;
		then
			if Compile ./src/Enigma.cc ./tmp/Enigma.o ;
			then echo -e "${GREEN}Enigma.cc compiled successfully.${NC}" ;
			else echo -e "${RED}Error: Enigma.cc could not be compiled successfully.${NC}" ;
			fi;
		fi;
	fi;
}
#compiling the rotor object (Rotor.cc)
CompileRotor() {
	if [ -f ./tmp/Rotor.o ] ;
	then
		echo -e "${GREEN}The file Roto.o already exists.${NC}" ;
	else
		if [ -f ./src/Rotor.cc ] && [ -f ./src/Rotor.hh ] ;
		then
			if Compile ./src/Rotor.cc ./tmp/Rotor.o ;
				then echo -e "${GREEN}Rotor.cc compiled successfully.${NC}" ;
        else echo -e "${RED}Error: Rotor.cc could not be compiled successfully.${NC}"
			fi;
		else echo -e "${RED}Could not find all resources to compile Rotor.o${NC}"
		fi;
	fi;
}

CompileKey1() {
	if [ -f ./tmp/key1gen.o ] ;
	then
		echo -e "${GREEN}The file key1gen.o already exists.${NC}" ;
	else
		if [ -f ./src/KEYGEN/KEY1/key1gen.cc] ;
		then
			if Compile ./src/KEYGEN/KEY1/key1gen.cc ./tmp/key1gen.o ;
			then echo -e "${GREEN}The file key1gen.cc has been compiled succesfully.${NC}" ;
			else echo -e "${RED}The file key1gen.cc could not be compiled succesfully.${NC}" ;
			fi ;
		else echo -e "${RED}Could not find all resources to compile key1gen.o${NC}" ;
		fi;
	fi;
}


CompileKey2() {
	if [ -f ./tmp/key2gen.o ] ;
	then
		echo -e "${GREEN}The file key2gen.o already exists.${NC}" ;
	else
		if [ -f ./src/KEYGEN/KEY2/key2gen.cc] ;
		then
			if Compile ./src/KEYGEN/KEY2/key2gen.cc ./tmp/key2gen.o ;
			then echo -e "${GREEN}The file key2gen.cc has been compiled succesfully.${NC}" ;
			else echo -e "${RED}The file key2gen.cc could not be compiled succesfully.${NC}" ;
			fi ;
		else echo -e "${RED}Could not find all resources to compile key1gen.o${NC}" ;
		fi;
	fi;
}

CreateKey1() {
	CompileKey1 ;
}

CreateKey2() {
	CompileKey2 ;
}

#Linking all the files into Enigma.
Link() {
	if [ -f ./tmp/program.o ] ;
	then
		if [ -f ./tmp/Enigma.o ] ;
        	then
	        	if [ -f ./tmp/Rotor.o ] ;
	                then
	                	if g++ -o ./bin/Enigma ./tmp/program.o ./tmp/Enigma.o ./tmp/Rotor.o ;
				then echo -e "${GREEN}All object have been linked succesfuly to Enigma.${NC}" ;
	                	else echo -e "${RED}Error: Could not link properly.${NC}" ;
				fi;
			else
				echo "${RED}Could not link Enigma, \"Rotor.o\" does not exists.${NC}" ;
				kill -SIGKILL $$ ;
	                fi;
		else
			echo "${RED}Could not link Enigma, \"Enigma.o\" does not exists.${NC}" ;
			kill -SIGKILL $$ ;
        	fi;
	else
		echo -e "${RED}Could not link Enigma, \"program.o\" does not exists.${NC}" ;
		kill -SIGKILL $$ ;
	fi;
}

CreateKey1() {
	#Generates all the rotors.
}

CreateKey2() {

}

#Deletes the tmp folder and the files inside it.
DeleteTmp() {
	if [ -d ./tmp ] ;
	then
		if rm -rf ./tmp ;
		then echo -e "${GREEN}The directory tmp successfully deleted.${NC}" ;
		else echo -e "${RED}Error: Could not delete the directory tmp.${NC}" ;
		fi;
	fi;
}

#Deletes the bin folder and the files inside it.
DeleteBin() {
	if [ -d ./bin ] ;
	then
		if rm -fr ./bin ;
		then echo -e "${GREEN}The directory bin successfully deleted.${NC}" ;
		else echo -e "${RED}Error: Could not delete the directory bin.${NC}" ;
		fi;
	fi;
}

#Unsets all the declared variables and functions.
CleanFunctions() {
	unset NC
	unset RED
	unset GREEN

	unset Compile
	unset CreateBin
	unset CreateTmp
	unset CompileProgram
	unset CompileEnigma
	unset CompileRotor
	unset Link
	unset DeleteTmp
	unset DeleteBin
	unset CompileKey1
	unset CompileKey2
	unset CreateKey1
	unset CreateKey2
	unset CleanFunctions
}

#Main execution branch.
if [ $# -eq 0 ] ;
then
	#Default execution
	CreateBin	;
	CreateTmp	;
	CompileProgram	;
	CompileEnigma	;
	CompileRotor	;
	Link		;
	DeleteTmp	;
else
	if [ $# -eq 1 ] ;
	then
		if [ $1 == clean ] ;
		then
			#Deletes the bin and tmp.
			DeleteBin		;
			DeleteTmp		;
			echo Terminated.	;
			exit ;
		else
	 		if [ $1 == KEYGEN ] ;
			#Creates a set of keys for the enigma program.
			then
				CreateBin  ;
				CreateTmp  ;
				CreateKey1 ;
				CreateKey2 ;
				DeleteTmp  ;
				exit ;
			fi;
		fi;
	fi;
fi;
CleanFunctions
