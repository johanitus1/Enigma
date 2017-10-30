#ifndef ROTOR_HH
#define ROTOR_HH

#include <vector>

#include <iostream>
#include <fstream>
//#include <sstream>

#include <stdlib.h>


using namespace std;

class Rotor
{
private:
	struct pin
	{
		char c;
		pin* p;
	};

	static const int size = 94;

	vector<pin*> left;
	vector<pin*> right;

	char pos;
	char inici;

public:
  /** @brief
 	 * \pre
 	 * \post
 	 */
	Rotor();

	/** @brief
	 * \pre
	 * \post
	 */
	Rotor(string type);

	/** @brief
   * \pre
   * \post
   */
	~Rotor();

	/** @brief
	 * crypt a char from the left
	 * \pre
	 * \post
	 */
	void set_pos(char p);

	/** @brief
	 * crypt a char from the left
	 * \pre
	 * \post
	 */
	char crypt_char_fl(char m);

	/** @brief
	 * crypt a char from the left
	 * \pre
	 * \post
	 */
	char crypt_char_fr(char m);

	bool turn();

	/** @brief
	 * \pre
	 * \post
	 */
	void write() const;

	/** @brief
	 * \pre
	 * \post
	 */
	Rotor* load(ifstream &arxiu);

	/** @brief
	 * \pre
	 * \post
	 */
	void save(ofstream &arxiu) const;

	/** @brief
	 * \pre
	 * \post
	 */
	void read();

private:
	int map(char c) const
	{
		return int(c - '!');
	}

	char map(int c) const
	{
		return char(c + int('!'));
	}

	char rotate_l(char c) const
	{
		int ic = int(c);
		ic -= '!';
		ic += int(pos - '!');
		if (ic > int('~') - int('!'))
		{
			ic -= int('~') - int('!') + 1;
		}
		ic += int('!');
		return char(ic);
	}

	char rotate_r(char c) const
	{
		int ic = int(c);
		ic -= '!';
		ic -= int(pos - '!');
		if (ic < 0)
		{
			ic += int('~') - int('!') + 1;
		}
		ic += int('!');
		return char(ic);
	}
};

#endif //ROTOR_HH
