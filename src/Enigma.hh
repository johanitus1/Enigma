 #ifndef ENIGMA_HH
#define ENIGMA_HH

#include "Rotor.hh"

#include <iostream>
#include <fstream>
#include <sstream>

#include <stdlib.h>
#include <vector>

using namespace std;

class Enigma {
private:
	//Rotors related
	vector<Rotor*> Rotors;
	vector<int> Position;
	Rotor endReturn;

	//Switch related
	vector<char> Switch; // key 2

	string code; //key 1

public:

	//Constructores.

	/** @brief
	 * \pre cert
	 * \post rotors es buit, position te mida 6 i esta ple de 0's.
	 */
	Enigma();

	/** @brief
	 * \pre
	 * \post
	 */
	~Enigma();

	//Set-Get

	/** @brief
	 * \pre
	 * \post
	 */
	void set_key1(string data);

	/** @brief
	 * \pre
	 * \post
	 */
	void set_key2(string data);

	/** @brief
	 * \pre
	 * \post
	 */
	void set_rotors(string data);

	//Actions

	/** @brief
	 * \pre
	 * \post
	 */
	void add_rotor();

	/** @brief
	 * \pre
	 * \post
	 */
	void write_rotors() const;

	/** @brief
	 * \pre
	 * \post
	 */
	string encrypt();

	//Input-Output

	/** @brief
	 * \pre
	 * \post
	 */
	void save(string path) const;

	/** @brief
	 * \pre
	 * \post
	 */
	void load(string path);

  void write_rotor(int n);

private:
	void turn()
	{
		int size = Position.size();
		bool done = true;
		for (int i = 0;done and i < size; ++i)
		{
			done = Rotors[Position[i]] -> turn();
		}
	}

};

#endif //ENIGMA_HH
