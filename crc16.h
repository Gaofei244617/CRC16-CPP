#ifndef __CRC16__
#define __CRC16__

/*------------------- CRC-16校验算法 -----------------------------
1.预置一个16 bits寄存器为0xFFFF,称为crc寄存器;
2.把第一个byte数据与crc寄存器低8位异或运算,结果存于crc寄存器，高8位不变；
3.把crc寄存器右移一位，用0填补高位，并检查右移的移出位；
4.如果移出位为0:重复第3步;如果移出位为1:crc寄存器与0xA001进行异或；
5.重复步骤3和步骤4，直到右移8次，这样1 byte数据就处理完成；
6.重复步骤2到步骤5，进行下一个字节的处理；
7.将需要校验的所有字节按照上述步骤计算完成后，得到一个16 bits的crc校验码；
8.将crc校验码低8位在前，高8位在后，附在需要校验的字节流后面；
*/

// crc16校验结果
class crc16_res
{
public:
	unsigned char LowByte;    // 低字节
	unsigned char HighByte;   // 高字节
	bool Flag;                // 校验是否成功
	crc16_res(unsigned char L, unsigned char H, bool F):LowByte(L),HighByte(H),Flag(F) {}
};

////校验码计算(C语言版本)，形参分别为待校验数据和数据个数
//crc16_res crc16(unsigned char* data, int n)
//{	
//	unsigned short crc = 0xFFFF; //校验码，初始值为0xFFFF
//	unsigned short temp;         //缓存变量
//	int i, j;
//
//	for (i = 0; i < n; i++)
//	{
//		crc = crc ^ *(data+i);
//		for (j = 0; j < 8; j++)
//		{
//			temp = crc & 0x0001;
//			if (temp != 0)
//			{
//				crc >>= 1;
//				crc = crc ^ 0xA001;
//			}
//			else
//			{
//				crc >>= 1;
//			}
//		}
//	}
//
//	return crc16_res(crc & 0x00FF, crc >> 8);
//}

//校验码计算(C++版本)，形参分别为待校验数据流和数据个数
//data类型为指针或容器
template <class T>
crc16_res crc16(T data, int n)
{
	unsigned short crc = 0xFFFF; //校验码，初始值为0xFFFF
	unsigned short temp;         //缓存变量
	int i, j;

	// 需保证data[0]数据类型的长度不大于unsigned short
	// 否则可能发生数据溢出
	// 理想情况为crc为2 byte，data[0]为1 byte
	if (sizeof(data[0]) <= sizeof(unsigned short))
	{
		for (i = 0; i < n; i++)
		{
			crc = crc ^ data[i];
			for (j = 0; j < 8; j++)
			{
				temp = crc & 0x0001;
				if (temp != 0)
				{
					crc >>= 1;
					crc = crc ^ 0xA001;
				}
				else
				{
					crc >>= 1;
				}
			}
		}

		return crc16_res(crc & 0x00FF, crc >> 8, true);
	}
	return crc16_res(0xFF, 0xFF, false);
}

#endif