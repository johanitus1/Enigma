#include <iostream>
#include <string>
#include "Enigma.hh"

using namespace std;

int main() {
	// char = 10 ==> char = '\n'
	Enigma enigma;

	cout << "Enigma machine constructed." << endl;

	enigma.load("./key1file.dat");

	cout << endl << "Default configuration loaded." << endl;
	cout << endl;
	cout << "///------------------------------ENIGMA------------------------------///" << endl << ">> " << endl;

	string comand;
	string op;
	string data;

	do
	{
		//Input analysis
		cout << ">> ";
		getline(cin, comand);
		if (comand.find(' ') <= comand.size())
		{
			op = comand.substr(0, comand.find(' '));
			data = comand.substr(comand.find(' ') + 1);
		}
		else
		{
			op = comand;
			data = "";
		}

		//Operation
		if (op == "encrypt")
		{
			string encrypted = enigma.encrypt();
			cout << "\t" << encrypted << endl;
		}
		else if (op == "set_key1")
		{
			enigma.set_key1(data);
		}
		else if (op == "set_key2")
		{
			enigma.set_key2(data);
		}
		else if (op == "set_rotors")
		{
			enigma.set_rotors(data);
		}
		else if (op == "add_rotor")
		{
			enigma.add_rotor();
		}
		else if (op == "save")
		{
			if (data == "")
			{
				enigma.save("./key1file.dat");
			}
			else
			{
				enigma.save("./" + data + ".dat");
			}
		}
		else if (op == "load")
		{
			if (data == "")
			{
				enigma.load("./key1file.dat");
			}
			else
			{
				enigma.load("./" + data + ".dat");
			}
		}
		else if (op == "write")
		{
			if (data != "")
				enigma.write_rotor(atoi(data.c_str()));
			else enigma.write_rotors();
		}
		else if (op == "clear")
		{
			if (system("CLS"))
			{
				system("reset");
			}
		}
		else if (op == "help")
		{
			cout << "\tencrypt:\tencrypts a message, ended with the sequence ~~$~~, with the predefined keys." << endl;
			cout << "\tset_key1:\tsets the rotors into possition given by the 6 char input." << endl;
			cout << "\tset_key2:\tsets the switch type key given the 15 pairs of chars input." << endl;
			cout << "\tset_rotors:\tplaces de rotors given by the 6 string input." << endl;
			cout << "\tlist_rotors:\tshows a list of all the rotors (the used ones next to its possition)." << endl;
			cout << "\tadd_rotor:\tcreates a new rotor." << endl;
			cout << "\tsave:\t\tsaves all the data into a file." << endl;
			cout << "\tload:\t\tloads a file into de machine." << endl;
			cout << "\twrite:\t\tshow all the rotors or the specified one." << endl;
			cout << "\tclear:\t\tcleans the terminal." << endl;
			cout << "\thelp:\t\tdisplays this help guide." << endl;
		}
		else if (op != "exit" and op != "")
		{
			cout << "\tThe operation \"" << op << "\" is unknown." << endl;
		}
	}while(op != "exit");

	enigma.save("./key1file.dat");

	cout  << endl << "\t---Gracies per utilitzar el programa.---" << endl << endl;
}
