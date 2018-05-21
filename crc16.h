#ifndef __CRC16__
#define __CRC16__

/*------------------- CRC-16У���㷨 -----------------------------
1.Ԥ��һ��16 bits�Ĵ���Ϊ0xFFFF,��Ϊcrc�Ĵ���;
2.�ѵ�һ��byte������crc�Ĵ�����8λ�������,�������crc�Ĵ�������8λ���䣻
3.��crc�Ĵ�������һλ����0���λ����������Ƶ��Ƴ�λ��
4.����Ƴ�λΪ0:�ظ���3��;����Ƴ�λΪ1:crc�Ĵ�����0xA001�������
5.�ظ�����3�Ͳ���4��ֱ������8�Σ�����1 byte���ݾʹ�����ɣ�
6.�ظ�����2������5��������һ���ֽڵĴ���
7.����ҪУ��������ֽڰ����������������ɺ󣬵õ�һ��16 bits��crcУ���룻
8.��crcУ�����8λ��ǰ����8λ�ں󣬸�����ҪУ����ֽ������棻
*/

// crc16У����
class crc16_res
{
public:
	unsigned char LowByte;    // ���ֽ�
	unsigned char HighByte;   // ���ֽ�
	bool Flag;                // У���Ƿ�ɹ�
	crc16_res(unsigned char L, unsigned char H, bool F):LowByte(L),HighByte(H),Flag(F) {}
};

////У�������(C���԰汾)���βηֱ�Ϊ��У�����ݺ����ݸ���
//crc16_res crc16(unsigned char* data, int n)
//{	
//	unsigned short crc = 0xFFFF; //У���룬��ʼֵΪ0xFFFF
//	unsigned short temp;         //�������
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

//У�������(C++�汾)���βηֱ�Ϊ��У�������������ݸ���
//data����Ϊָ�������
template <class T>
crc16_res crc16(T data, int n)
{
	unsigned short crc = 0xFFFF; //У���룬��ʼֵΪ0xFFFF
	unsigned short temp;         //�������
	int i, j;

	// �豣֤data[0]�������͵ĳ��Ȳ�����unsigned short
	// ������ܷ����������
	// �������ΪcrcΪ2 byte��data[0]Ϊ1 byte
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