#ifndef BRUTEFORCE
#define BRUTEFORCE

#include <vector>
#include <string>
#include <fstream>
#include <limits>  
#include <iostream>
#include <ctime>
#include <omp.h>
#include <bitset>

#include "Cryptosystem.h"

class Bruteforce {
public:
	Bruteforce() = default;
	Bruteforce(std::string m_plainTextFilename, std::string m_encTextFilename);
	void brute(void);

private:
	std::vector<uint32_t> getBlocksText(std::string fileName);

private:
	std::string m_plainTextFilename;
	std::string m_encTextFilename;
	std::vector<uint32_t> plaintText;
	std::vector<uint32_t> encText; 
	Cryptosystem cs; 
};
#endif // !BRUTEFORCE

