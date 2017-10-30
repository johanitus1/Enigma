#include <iostream>
using namespace std;

#include <vector>
#include <cstdlib>
#include <ctime>

int main()
{
	vector<bool> v(127, false);
	vector<char> c(0);

	for (char a ='!'; a <= '~'; ++a)
	{
		c.push_back(a);
	}

	int nRotors, j = 0;
	cin >> nRotors;
	srand(time(0));
	int setrand = rand();
        cout << setrand << endl;
	srand(setrand);
	cout << nRotors << endl;

	while(j++ < nRotors)
	{
		int r = rand();
		if (r < 0) r *= -1;
		r %= 1000000;
		for(int i = 0; i < r; ++i)
		{
			srand(rand());
		}
		char h = c[rand() % c.size()];
		cout << h << ' ';
		for (int i = 0; i < 94; ++i)
		{
			char k;
			do
			{
				k = c[rand() % c.size()];
			}
			while(v[int(k)]);
			v[int(k)] = true;
			cout << k << ' ';
		}
		cout << endl;
		v = vector<bool>(127, false);
	}
}
