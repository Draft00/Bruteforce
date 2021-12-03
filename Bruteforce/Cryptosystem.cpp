#include "Cryptosystem.h"

uint32_t Cryptosystem::calculate(uint32_t plaintText, uint32_t key)
{
	std::tuple<uint16_t, uint16_t, uint32_t, uint16_t> keys = this->getRaundKeys(key);
	uint32_t resultText = this->layMessi(plaintText, std::get<0>(keys));
	resultText = this->feistel(resultText, std::get<1>(keys));
	resultText = this->sp32(resultText, std::get<2>(keys));
	resultText = this->layMessi(resultText, std::get<3>(keys));
	return resultText;
}

std::tuple<uint16_t, uint16_t, uint32_t, uint16_t> Cryptosystem::getRaundKeys(uint32_t key)
{
    uint16_t key_part1 = (key & 0xffff0000) >> 16;
    uint16_t key_part2 = key & 0x0000ffff;
    uint16_t key1 = rol(key_part1, 10);
    uint16_t key2 = key_part1 ^ 17361 ^ key_part2;
    uint32_t key3 = (((key_part1 ^ 9860) | key_part2) << 16) | (key_part1 & (key_part2 ^ 16759));
    uint16_t key4 = key_part1 & key_part2;

    return std::make_tuple(key1, key2, key3, key4);
}

uint32_t Cryptosystem::feistel(uint32_t plaintText, uint16_t key)
{
    uint16_t X2 = plaintText & 0x0000ffff;
    uint16_t X1 = (plaintText & 0xffff0000) >> 16;
	return (X2 << 16) | (X1 ^ this->sp16(X2, key));
}

uint32_t Cryptosystem::layMessi(uint32_t plainText, uint16_t key)
{
	uint16_t X2 = plainText & 0x0000ffff;
	uint16_t X1 = (plainText & 0xffff0000) >> 16;

	uint32_t result = ((X1 ^ this->sp16(X1 ^ X2, key)) << 16) | (X2 ^ this->sp16(X1 ^ X2, key));
	return result;
}

uint32_t Cryptosystem::sp32(uint32_t key, uint32_t text)
{
	uint32_t x = text;
	uint32_t x_result = x ^ key;
	uint32_t SBlockResult = 0;
	uint32_t PBlockResult = 0;
	uint32_t bits_4 = 0;

	//применяем S
	for (int i = 28; i > -1; i = i - 4)
	{
		bits_4 = x_result >> i;
		bits_4 &= 0xF;
		uint32_t elem = this->m_S[bits_4];
		SBlockResult |= elem;
		if (i >= 4) SBlockResult <<= 4;
	}

	//Применяем P
	for (int w = 0; w < 32; w++)
	{
		uint32_t bit = SBlockResult & 1;
		bit <<= (this->m_SP_A * w + this->m_SP_B) % 32;
		PBlockResult |= bit;
		SBlockResult >>= 1;
	}
	return PBlockResult;
}

uint16_t Cryptosystem::sp16(uint16_t key, uint16_t text)
{
	uint16_t x_result = text ^ key;
	uint16_t SBlockResult = 0;
	uint16_t PBlockResult = 0;
	uint16_t bits_4;

	//применяем S
	for (int i = 12; i > -1; i = i - 4)
	{
		bits_4 = x_result >> i;
		bits_4 &= 0xF;
		uint16_t elem = this->m_S[bits_4];
		SBlockResult |= elem;
		if (i >= 4) SBlockResult <<= 4;
	}

	//Применяем P
	for (int w = 0; w < 16; w++)
	{
		uint32_t bit = SBlockResult & 1;
		bit <<= (this->m_SP_A * w + this->m_SP_B) % 16;
		PBlockResult |= bit;
		SBlockResult >>= 1;
	}
	return PBlockResult;
}

uint16_t Cryptosystem::rol(uint16_t a, uint16_t n)
{
	uint16_t t1, t2;
	n = n % (sizeof(a) * 8);
	t1 = a << n;
	t2 = a >> (sizeof(a) * 8 - n);
	return t1 | t2;
}


