#include <iostream>
#include <cstdlib>
#include "crc16.h"

int main()
{
	unsigned char bytes[6] = { 0x02,0x06,0x08,0x02,0x00,0xC8};

	auto datas = crc16(bytes,6);

	int L = datas.LowByte;
	int H = datas.HighByte;

	std::cout << "LowByte: " << std::hex << L << std::endl;
	std::cout << "HighByte: " << std::hex << H << std::endl;

	system("pause");
	return 0;
}