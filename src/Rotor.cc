
#include "Rotor.hh"

Rotor::Rotor()
{
	pos = '!';
	inici = '!';
	left = vector<pin*>(size);
	right = vector<pin*>(size);
	for (char i = '!'; i <= '~'; ++i)
	{
		int pos = map(i);
		left[pos] = new pin;
		right[pos] = new pin;
		left[pos] -> c = i;
		right[pos] -> c = i;
	}
}

Rotor::Rotor(string type)
{
	left = vector<pin*>(size);
	right = vector<pin*>(size);
	if (type == "END_RETURN")
	{
		pos = '!';
		inici = '!';

		int hSize = size/2;

		for (int i = size-1; i >= 0; --i)
		{
			left[i] = new pin;
			right[i] = new pin;
			left[i] -> c = map(i);
			right[i] -> c = map(i);
			if (i < hSize)
			{
				left[i] -> p = left[i+hSize];
				right[i] -> p = right[i+hSize];
				left[i+hSize] -> p = left[i];
				right[i+hSize] -> p = right[i];
			}

		}
	}
}


Rotor::~Rotor()
{
	/**
	for (int i = 0; i < size; ++i)
	{
		delete left[i];
		delete right[i];
	}
	*/
}

void Rotor::set_pos(char p)
{
	pos = p;
	// Cambiar la possicio.
}

char Rotor::crypt_char_fl(char m)
{
	char rm;   // Rotated
	char urk;  // UnRotatetKripted
	char k;    // Kripted
	rm = rotate_l(m);
	int pos = map(rm);
	if (left[pos] -> p != NULL)
	{
		urk = left[pos] -> p -> c;
		k = rotate_r(urk);
	}
	else
	{
		k = '!';
		cout << "<< Internal Error." << endl;
	}
	return k;
}

char Rotor::crypt_char_fr(char m)
{
	char rm;   // Rotated
	char urk;  // UnRotatetKripted
	char k;    // Kripted
	rm = rotate_l(m);
	int pos = map(rm);
	if (right[pos] -> p != NULL)
	{
		urk = right[pos] -> p -> c;
		k = rotate_r(urk);
	}
	else
	{
		k = '!';
		cout << "<< Internal Error." << endl;
	}
	return k;
}

bool Rotor::turn()
{
	bool res = pos == inici;
	++pos;
	if(pos > '~') pos = '!';
	return res;
}

void Rotor::write() const
{
	int size = left.size();
	cout << "\t";
	for (int i = 0; i < size; ++i)
	{
		if (left[i] -> p != NULL)
			cout << left[i] -> p -> c << ' ';
		else
		{
			cout << left[i] -> c << " is null." << endl;
		}
	}
	cout << endl;
}

Rotor* Rotor::load(ifstream &arxiu)
{
	arxiu >> this -> inici;
	for (int i = 0; i < size; ++i)
	{
		char con;
		arxiu >> con;
		this -> left[i] -> p = this -> right[map(con)];
		this -> right[map(con)] -> p = this -> left[i];
	}
	return this;
}

void Rotor::save(ofstream &arxiu) const
{
	arxiu << inici;
	for (int i = 0; i < size; ++i)
	{
		arxiu << ' ' << left[i] -> p -> c;
	}
}

void Rotor::read()
{
	for (int i = 0; i < size; ++i)
	{
		cout << "\tConneccio amb " << map(i) << ": ";
		char con;
		cin >> con;
		left[i] -> p = right[map(con)];
		right[map(con)] -> p = left[i];
	}
}
