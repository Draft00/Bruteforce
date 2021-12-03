#ifndef CRYPTOSYSTEM_H
#define CRYPTOSYSTEM_H

#include <cstdint>
#include <vector>
#include <tuple>

class Cryptosystem
{

public:
	Cryptosystem() = default;
	uint32_t calculate(uint32_t plaintText, uint32_t key);
	

private:
	std::tuple<uint16_t, uint16_t, uint32_t, uint16_t> getRaundKeys(uint32_t key);
	uint32_t feistel(uint32_t plaintText, uint16_t key);
	uint32_t layMessi(uint32_t plainText, uint16_t key);
	uint32_t sp32(uint32_t key, uint32_t text);
	uint16_t sp16(uint16_t key, uint16_t text);
	uint16_t rol(uint16_t a, uint16_t n);

private:
	uint16_t m_SP_A = 29;
	uint16_t m_SP_B = 31;
	uint16_t m_S[16] { 9, 15, 3, 13, 12, 0, 2, 10, 8, 11, 1, 7, 5, 6, 14, 4 };
};


#endif // !CRYPTOSYSTEM_H