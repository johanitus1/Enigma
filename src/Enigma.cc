#include "Enigma.hh"

using namespace std;

	//Constructores.
	Enigma::Enigma()
	{
		Switch = vector<char>(127);
		for (char i = 0; i < 127; ++i)
		{
			Switch[int(i)] = i;
		}
		endReturn = Rotor("END_RETURN");
	}

	Enigma::~Enigma()
	{

	}

	//Set-Get
	void Enigma::set_key1(string data)
	{
		if (data.size() != Position.size())
		{
			cout << "<< La clau ha de tanir longitud igual al nombre de rotors." << endl;
		}
		else
		{
			int size = Position.size();
			for (int i = 0; i < size; ++i)
			{
				this -> Rotors[Position[i]] -> set_pos(data[i]);
			}
		}
	}

	void Enigma::set_key2(string data)
	{
		Switch = vector<char>(int('~') + 1);
		for (char i = 0; i <= int('~'); ++i)
		{
			Switch[int(i)] = i;
		}

		istringstream iss(data);
		string set;
		while(getline(iss, set, ' '))
		{
			Switch[int(set[0])] = set[1];
			Switch[int(set[1])] = set[0];
		}
	}

	void Enigma::set_rotors(string data)
	{
		istringstream iss(data);
		string rotor_name;
		Position = vector<int>(0);
		while(getline(iss, rotor_name, ' '))
		{
			Position.push_back(atoi(rotor_name.c_str())-1);
		}
	}

	//Actions
	void Enigma::add_rotor()
	{
		Rotor *nou;
		nou -> read();
		this -> Rotors.push_back(nou);
	}

	void Enigma::write_rotors() const
	{
		int nRotors = this -> Rotors.size();
		for (int i = 0; i < nRotors; ++i)
		{
			cout << endl;
			cout << "Rotor number " << i+1 << endl;
			this -> Rotors[i] -> write();
			cout << endl;
		}
	}

	string Enigma::encrypt()
	{
		string message;
		bool eom = false;
		while (not eom)
		{
			string aux;
			cout << "\t";
			getline(cin, aux);
			if (aux.size() >= 5 and aux.substr(aux.size()-5, aux.size()) == "~~#~~")
			{
				eom = true;
				aux = aux.substr(0, aux.size()-5);
				message += aux;
			}
			else message += (aux + " ");
		}

		for (int i = 0; i < message.size(); ++i)
		{
			turn();
			if (message[i] == ' ')
				message[i] = '_';

			message[i] = this -> Switch[int(message[i])];

			for (int j = 0; j < Position.size(); ++j)
			{
				message[i] = this -> Rotors[Position[j]] -> crypt_char_fl(message[i]);
			}

			message[i] = endReturn.crypt_char_fl(message[i]);

			for (int j = Position.size()-1; j >= 0; --j)
			{
				message[i] = this -> Rotors[Position[j]] -> crypt_char_fr(message[i]);
			}
			message[i] = this -> Switch[int(message[i])];
		}
		return message;
	}

	//Input-Output
	void Enigma::save(string path) const
	{
		ofstream arxiu(path.c_str());
		int nRotors = Rotors.size();
		arxiu << nRotors << endl;
		for (int i = 0; i < nRotors; ++i)
		{
			this -> Rotors[i] -> save(arxiu);
			arxiu << endl;
		}
		arxiu.close();
	}

	void Enigma::load(string path)
	{
		ifstream arxiu(path.c_str());
		int nRotors;
		arxiu >> nRotors;
		this -> Rotors = vector<Rotor*>(nRotors);
		for (int i = 0; i < nRotors; ++i)
		{
			this -> Rotors[i] = new Rotor();
			this -> Rotors[i] -> load(arxiu);
		}
		arxiu.close();
	}

	void Enigma::write_rotor(int n)
	{
		cout << "<< Rotor " << n << ": ";
		this -> Rotors[n] -> write();
		cout << endl;
	}


/**
void Enigma::load(string path){
	//for save ofstream arxiu("avions.txt");
	ifstream info_enigma(path);
	int nLletres;
	info_enigma >> nLletres;
	crossPanel = CrossPanel(nLletres);
	crossPanel.llegir(info_enigma);
	info_enigma >> nRotors;
	rotors = Rotors(nRotors);
	rotors.llegir(info_enigma);
	info_enigma.close();

}
*/
