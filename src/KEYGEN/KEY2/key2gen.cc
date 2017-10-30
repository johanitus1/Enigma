#include <iostream>
using namespace std;

#include <vector>
#include <cstdlib>
#include <ctime>

struct data
{
	int dia;
	int mes;
	int any;

	data& operator++(int)
	{
		dia++;
		if (mes == 2){
			bool adt = (any % 4 == 0 and ((any / 100) % 4 == 0 or any % 100 != 0)) ? 1 : 0;
			if(dia > 28 + adt){mes++;dia = 1;}
		}
		else if (mes == 1 or mes == 3 or mes == 5 or mes == 7 or mes == 8 or mes == 10 or mes == 12)
		{
			if (dia > 31){mes++;dia = 1;}
		}
		else if (dia > 30){mes++;dia = 1;}
		if (mes > 12){any++; mes = 1;}
		return *this;
	}

	void print()
	{
		if (dia < 10) cout << 0;
		cout << dia << '/';
		if (mes < 10) cout << 0;
		cout << mes << '/';
		cout << any;
	}
};

int main()
{
	vector<bool> v(127, false);
	vector<char> c(0);
	for (char a ='!'; a <= '~'; ++a)
	{
		c.push_back(a);
	}

	int nKey2, j = 0;


	srand(time(0));
	data d;
	//cout << "Data inici[dd mm aaaa]: ";
	cin >> d.dia >> d.mes >> d.any;
	//cout << "Numero de claus a generar: ";
	cin >> nKey2;
	while(j++ < nKey2)
	{
		v = vector<bool>(127, false);
		srand(rand());
		d.print();
		cout << ":\t";
		for (int i = 0; i < 30; ++i)
		{
			char ch;
			do {
				ch = c[rand() % c.size()];
			} while(v[int(ch)]);
			v[int(ch)] = true;
			cout << ch;
			do {
				ch = c[rand() % c.size()];
			} while(v[int(ch)]);
			v[int(ch)] = true;
			cout << ch << ' ';
		}
		cout << endl;
		//k = c[rand() % c.size()];
		d++;
	}
}
