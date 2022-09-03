// PyAES.cpp: 定義應用程式的進入點。
//


#include <iostream>
#include <string>
#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "..\include\PyAES.h"

/////////////////////////////////

BYTE SBox[16][16] =
{ {0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76},
{0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0},
{0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15},
{0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75},
{0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84},
{0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf},
{0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8},
{0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2},
{0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73},
{0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb},
{0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79},
{0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08},
{0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a},
{0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e},
{0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf},
{0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16}
};//s-盒

BYTE InvSBox[16][16] =
{ {0x52,0x09,0x6a,0xd5,0x30,0x36,0xa5,0x38,0xbf,0x40,0xa3,0x9e,0x81,0xf3,0xd7,0xfb},
{0x7c,0xe3,0x39,0x82,0x9b,0x2f,0xff,0x87,0x34,0x8e,0x43,0x44,0xc4,0xde,0xe9,0xcb},
{0x54,0x7b,0x94,0x32,0xa6,0xc2,0x23,0x3d,0xee,0x4c,0x95,0x0b,0x42,0xfa,0xc3,0x4e},
{0x08,0x2e,0xa1,0x66,0x28,0xd9,0x24,0xb2,0x76,0x5b,0xa2,0x49,0x6d,0x8b,0xd1,0x25},
{0x72,0xf8,0xf6,0x64,0x86,0x68,0x98,0x16,0xd4,0xa4,0x5c,0xcc,0x5d,0x65,0xb6,0x92},
{0x6c,0x70,0x48,0x50,0xfd,0xed,0xb9,0xda,0x5e,0x15,0x46,0x57,0xa7,0x8d,0x9d,0x84},
{0x90,0xd8,0xab,0x00,0x8c,0xbc,0xd3,0x0a,0xf7,0xe4,0x58,0x05,0xb8,0xb3,0x45,0x06},
{0xd0,0x2c,0x1e,0x8f,0xca,0x3f,0x0f,0x02,0xc1,0xaf,0xbd,0x03,0x01,0x13,0x8a,0x6b},
{0x3a,0x91,0x11,0x41,0x4f,0x67,0xdc,0xea,0x97,0xf2,0xcf,0xce,0xf0,0xb4,0xe6,0x73},
{0x96,0xac,0x74,0x22,0xe7,0xad,0x35,0x85,0xe2,0xf9,0x37,0xe8,0x1c,0x75,0xdf,0x6e},
{0x47,0xf1,0x1a,0x71,0x1d,0x29,0xc5,0x89,0x6f,0xb7,0x62,0x0e,0xaa,0x18,0xbe,0x1b},
{0xfc,0x56,0x3e,0x4b,0xc6,0xd2,0x79,0x20,0x9a,0xdb,0xc0,0xfe,0x78,0xcd,0x5a,0xf4},
{0x1f,0xdd,0xa8,0x33,0x88,0x07,0xc7,0x31,0xb1,0x12,0x10,0x59,0x27,0x80,0xec,0x5f},
{0x60,0x51,0x7f,0xa9,0x19,0xb5,0x4a,0x0d,0x2d,0xe5,0x7a,0x9f,0x93,0xc9,0x9c,0xef},
{0xa0,0xe0,0x3b,0x4d,0xae,0x2a,0xf5,0xb0,0xc8,0xeb,0xbb,0x3c,0x83,0x53,0x99,0x61},
{0x17,0x2b,0x04,0x7e,0xba,0x77,0xd6,0x26,0xe1,0x69,0x14,0x63,0x55,0x21,0x0c,0x7d},
};//逆s-盒

BYTE Rc[31] =
{ 0x00, 0x01,0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8,
0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d,
0xfa, 0xef, 0xc5,0x91 };
////////////////////////////////

CAES::CAES()//type=true時為加密文件,type=false時為加密字符串
{
	int i;
	for (i = 0; i < 4; i++)//置空
	{
		key[i] = NULL;
		w[i] = NULL;
	}

	State = NULL;
	/////////////////////////////////////////////////////

}

CAES::~CAES()
{
	for (int i = 0; i < 4; i++)//釋放原有的內存並置空
	{
		if (key[i] != NULL)
		{
			delete key[i];
			key[i] = NULL;
		}
		if (w[i] != NULL)
		{
			delete w[i];
			w[i] = NULL;
		}
	}
}


bool CAES::SetKeys(KeySize keySize, const char* sKey)
{
	int i, j;
	switch (keySize)
	{
	case KeySize::BIT128:
		this->Nk = 4;//128÷8÷4
		this->Nr = 10;//Nr = Nk + 6;
		break;
	case KeySize::BIT192:
		this->Nk = 6;//192÷8÷4
		this->Nr = 12;//Nr = Nk + 6;
		break;
	case KeySize::BIT256:
	default:
		this->Nk = 8;//256÷8÷4
		this->Nr = 14;//Nr = Nk + 6;
		break;
	}
	for (i = 0; i < 4; i++)//釋放原有的內存並置空
	{
		if (key[i] != NULL)
		{
			delete key[i];
			key[i] = NULL;
		}
		if (w[i] != NULL)
		{
			delete w[i];
			w[i] = NULL;
		}
	}
	for (i = 0; i < 4; i++)//動態創建字鑰數組
	{
		key[i] = new BYTE[Nk];
		if (key[i] == NULL)
		{
			return false;
		}
	}
	for (i = 0; i < 4; i++)//動態創建密鑰調度表
	{
		w[i] = new BYTE[4 * (Nr + 1)];
		if (w[i] == NULL)
		{
			return false;
		}
	}
	for (i = 0; i < 4; i++)//獲得密鑰
		for (j = 0; j < Nk; j++)
			key[i][j] = (BYTE)sKey[Nk * i + j];
	//key[i][j]=(byte)sKey.GetAt(Nk*i+j);
	KeyExpansion();//生成密鑰調度表
	return true;
}
void CAES::SubBytes()//字節代替變換
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			State[i][j] = SBox[(State[i][j] >> 4) & 0x0F][State[i][j] & 0x0F];
}

void CAES::ShiftRows()//循環移位
{
	BYTE4 temp[4];
	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			temp[r].w[c] = this->State[r][c];
		}
	}

	for (int r = 1; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			this->State[r][c] = temp[r].w[(c + r) % 4];
		}
	}
}

void CAES::MixColumns()//列混合變換
{
	BYTE4 temp[4];
	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			temp[r].w[c] = this->State[r][c];
		}
	}

	for (int c = 0; c < 4; ++c)
	{
		this->State[0][c] = (BYTE)(
			(int)GfCalc(temp[0].w[c], GfCalcMode::MODE02) ^
			(int)GfCalc(temp[1].w[c], GfCalcMode::MODE03) ^
			(int)GfCalc(temp[2].w[c], GfCalcMode::MODE01) ^
			(int)GfCalc(temp[3].w[c], GfCalcMode::MODE01));
		this->State[1][c] = (BYTE)(
			(int)GfCalc(temp[0].w[c], GfCalcMode::MODE01) ^
			(int)GfCalc(temp[1].w[c], GfCalcMode::MODE02) ^
			(int)GfCalc(temp[2].w[c], GfCalcMode::MODE03) ^
			(int)GfCalc(temp[3].w[c], GfCalcMode::MODE01));
		this->State[2][c] = (BYTE)(
			(int)GfCalc(temp[0].w[c], GfCalcMode::MODE01) ^
			(int)GfCalc(temp[1].w[c], GfCalcMode::MODE01) ^
			(int)GfCalc(temp[2].w[c], GfCalcMode::MODE02) ^
			(int)GfCalc(temp[3].w[c], GfCalcMode::MODE03));
		this->State[3][c] = (BYTE)(
			(int)GfCalc(temp[0].w[c], GfCalcMode::MODE03) ^
			(int)GfCalc(temp[1].w[c], GfCalcMode::MODE01) ^
			(int)GfCalc(temp[2].w[c], GfCalcMode::MODE01) ^
			(int)GfCalc(temp[3].w[c], GfCalcMode::MODE02));
	}
}

void CAES::AddRoundKey(int round)//輪密鑰加法變換
{
	int i, j, k = round * 4;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			State[i][j] = State[i][j] ^ w[i][k + j];
}

void CAES::KeyExpansion()//密鑰擴展
{
	BYTE temp[4], tp;
	int i, j, x;
	for (i = 0; i < Nk; i++)//生成前Nk個字
	{
		w[0][i] = key[0][i];
		w[1][i] = key[1][i];
		w[2][i] = key[2][i];
		w[3][i] = key[3][i];
	}
	while (i < 4 * (Nr + 1))//生成後幾個字
	{
		for (j = 0; j < 4; j++)
			temp[j] = w[j][i - 1];
		if (i % Nk == 0)
		{
			tp = temp[0];
			temp[0] = temp[1];
			temp[1] = temp[2];
			temp[2] = temp[3];
			temp[3] = tp;
			for (j = 0; j < 4; j++)
				temp[j] = SBox[(temp[j] >> 4) & 0x0F][temp[j] & 0x0F];
			x = Rc[i / Nk];
			temp[0] = temp[0] ^ x;
		}
		else
			if (Nk > 6 && (i % Nk == 4))
				for (j = 0; j < 4; j++)
					temp[j] = SBox[(temp[j] >> 4) & 0x0F][temp[j] & 0x0F];
		for (j = 0; j < 4; j++)
			w[j][i] = (w[j][i - Nk]) ^ temp[j];
		i++;
	}
	for (int k = 0; k <= Nr; k++)//實現密鑰的每16個字節為一個矩陣的矩陣轉置(對字符串加密/解密有影響)
		for (i = 0; i < 3; i++)
		{
			x = 4 * k;
			for (j = i + 1; j < 4; j++)
			{
				tp = w[i][x + j];
				w[i][x + j] = w[j][x + i];
				w[j][x + i] = tp;
			}
		}

}

void CAES::InvShiftRows()//循環右移函數(0000000000)
{

	BYTE4 temp[4];
	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			temp[r].w[c] = this->State[r][c];
		}
	}
	for (int r = 1; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			this->State[r][(c + r) % 4] = temp[r].w[c];
		}
	}
}

void CAES::InvSubBytes()//利用逆S盒InvSBox實現逆字節代替變換
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			State[i][j] = InvSBox[(State[i][j] >> 4) & 0x0F][State[i][j] & 0x0F];
}

void CAES::InvMixColumns()
{
	BYTE4 temp[4];
	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			temp[r].w[c] = this->State[r][c];
		}
	}

	for (int c = 0; c < 4; ++c)
	{
		this->State[0][c] = (BYTE)(
			(int)GfCalc(temp[0].w[c], GfCalcMode::MODE0e) ^
			(int)GfCalc(temp[1].w[c], GfCalcMode::MODE0b) ^
			(int)GfCalc(temp[2].w[c], GfCalcMode::MODE0d) ^
			(int)GfCalc(temp[3].w[c], GfCalcMode::MODE09));
		this->State[1][c] = (BYTE)(
			(int)GfCalc(temp[0].w[c], GfCalcMode::MODE09) ^
			(int)GfCalc(temp[1].w[c], GfCalcMode::MODE0e) ^
			(int)GfCalc(temp[2].w[c], GfCalcMode::MODE0b) ^
			(int)GfCalc(temp[3].w[c], GfCalcMode::MODE0d));
		this->State[2][c] = (BYTE)(
			(int)GfCalc(temp[0].w[c], GfCalcMode::MODE0d) ^
			(int)GfCalc(temp[1].w[c], GfCalcMode::MODE09) ^
			(int)GfCalc(temp[2].w[c], GfCalcMode::MODE0e) ^
			(int)GfCalc(temp[3].w[c], GfCalcMode::MODE0b));
		this->State[3][c] = (BYTE)(
			(int)GfCalc(temp[0].w[c], GfCalcMode::MODE0b) ^
			(int)GfCalc(temp[1].w[c], GfCalcMode::MODE0d) ^
			(int)GfCalc(temp[2].w[c], GfCalcMode::MODE09) ^
			(int)GfCalc(temp[3].w[c], GfCalcMode::MODE0e));
	}
}


void CAES::Encrypt(BYTE* input, BYTE* output)
{
	BYTE in[4][4];
	BYTE* temp = &(in[0][0]);
	for (int i = 0; i < 16; i++)
		*(temp + i) = *(input + i);
	State = in;

	int j, k = 0;
	AddRoundKey(0);
	for (j = 1; j < Nr; j++)
	{
		SubBytes();
		ShiftRows();
		MixColumns();
		AddRoundKey(j);
	}
	SubBytes();
	ShiftRows();
	AddRoundKey(j);

	for (int n = 0; n < 16; n++)
		*(output + n) = *(temp + n);
}


std::vector<char> CAES::EncryptBuffer(const std::vector<char>& input)
{
	std::vector<char> output(input);
	int size = static_cast<int>(input.size());

	int count = size / 16;
	BYTE pin[16], pout[16];

	int len = size % 16;
	if (count > 0)
	{
		int n = 0;
		for (int i = 0; i < count * 16; i += 16)
		{
			for (n = 0; n < 16; n++)
				pin[n] = output.at(i + n);
			Encrypt(pin, pout);
			for (n = 0; n < 16; n++)
				output.at(i + n) = pout[n];
		}
		if (len > 0)
		{
			int k;
			for (int n = 0; n < 16 - len; n++)
				pin[n] = pout[len + n];
			k = 0;
			for (int n = 16 - len, i = count * 16; n < 16; n++)
			{
				pin[n] = output.at(i + k); k++;
			}
			Encrypt(pin, pout);
			k = count * 16 - (16 - len);
			for (int n = 0; n < 16; n++)
			{
				output.at(k) = pout[n]; k++;
			}
		}
	}
	return output;
}

//wchar_t* CAES::EncryptString(wchar_t* input)
//{
//	EncryptBuffer((BYTE*)input, (int)wcslen(input) * 2);
//	return input;
//}
//char* CAES::EncryptStringA(char* input)
//{
//	EncryptBuffer((BYTE*)input, (int)strlen(input));
//	return input;
//}
//CString &CAES::EncryptString(CString &input)
//{
//	EncryptBuffer((BYTE *)input.GetBuffer(0),input.GetLength());
//	return input;
//}

//void CAES::EncryptFile(CString SourceFile,CString TagerFile)
//{
//	CFile sfile(SourceFile, CFile::modeRead);
//	CFile tfile(TagerFile, CFile::modeCreate | CFile::modeWrite);
//	int size = (int)sfile.GetLength();
//	int len = 0;
//	BYTE buffer[1024];
//	int curlen = 0;
//	while (curlen < size)
//	{
//		len = sfile.Read(buffer,1024);
//		EncryptBuffer(buffer,len);
//		tfile.Write(buffer,len);
//		curlen += len;
//	}
//	sfile.Close();
//	tfile.Close();
//
//}

void CAES::Decrypt(BYTE* input, BYTE* output)
{
	BYTE in[4][4];
	BYTE* temp = &(in[0][0]);
	BYTE tempinput[16];
	memset(tempinput, 5, 16);
	memcpy(tempinput, input, 16);
	for (int i = 0; i < 16; i++)
		*(temp + i) = tempinput[i];
	State = in;

	int j, k = 0;
	AddRoundKey(Nr);
	for (j = Nr - 1; j > 0; j--)
	{
		InvShiftRows();
		InvSubBytes();
		AddRoundKey(j);
		InvMixColumns();
	}
	InvShiftRows();
	InvSubBytes();
	AddRoundKey(j);

	for (int n = 0; n < 16; n++)
		output[n] = *(temp + n);
}

std::vector<char> CAES::DecryptBuffer(const std::vector<char>& input)
{
	std::vector<char> output(input);
	int size = static_cast<int>(input.size());

	int count = size / 16;
	BYTE pin[16], pout[16];

	int len = size % 16;
	int n = 0;
	int i = 0;
	if (count > 0)
	{
		if (len > 0)
		{
			int k;
			for (n = 0, i = count * 16 - (16 - len); n < 16; n++)
			{
				pin[n] = output.at(i + n);
			}
			Decrypt(pin, pout);
			k = count * 16 - (16 - len);
			for (n = 0; n < 16; n++)
			{
				output.at(k) = pout[n]; k++;
			}
		}
		n = 0;
		for (i = 0; i < count * 16; i += 16)
		{
			for (n = 0; n < 16; n++)
				pin[n] = output.at(i + n);
			Decrypt(pin, pout);
			for (n = 0; n < 16; n++)
				output.at(i + n) = pout[n];
		}
	}
	return output;
}

//CString &CAES::DecryptString(CString &input)
//{
//	DecryptBuffer((BYTE *)input.GetBuffer(0),input.GetLength());
//	return input;
//}

//void CAES::DecryptFile(CString SourceFile,CString TagerFile)
//{
//	CFile sfile(SourceFile, CFile::modeRead);
//	CFile tfile(TagerFile, CFile::modeCreate | CFile::modeWrite);
//	int size = (int)sfile.GetLength();
//	int len = 0;
//	BYTE buffer[1024];
//	int curlen = 0;
//	while (curlen < size)
//	{
//		len = sfile.Read(buffer,1024);
//		DecryptBuffer(buffer,len);
//		tfile.Write(buffer,len);
//		curlen += len;
//	}
//	sfile.Close();
//	tfile.Close();
//}
//BOOL CAES::DecryptFileLoadingData(TCHAR* SourceFile,set<string> * pApiData)
//{
//	HANDLE m_File = CreateFile(SourceFile,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
//	if(m_File != INVALID_HANDLE_VALUE)
//	{
//		BOOL ret = TRUE;
//		DWORD m_Filesize = GetFileSize(m_File, NULL);
//		BYTE * Dbuffer = new BYTE[m_Filesize];		
//		DWORD readsize = 0;
//		ReadFile(m_File, Dbuffer,m_Filesize, &readsize, NULL);
//		DecryptBuffer(Dbuffer,m_Filesize);
//
//		char * str = new char[1024];
//		memset(str,'\0',1024);
//		int j = 0;
//		bool Istable = false;
//		for(int i = 0;i<(int)m_Filesize;i++)
//		{
//			if(j<1024)
//			{
//				if(Dbuffer[i] == 10)
//				{
//					str[j] = '\0';
//					if(!strcmp(str,"ApiTable"))
//						Istable = true;
//					else
//					{
//						if(Istable)
//						{
//							char m_ApiName[256];
//							memset(m_ApiName,'\0',256);
//							char* psc;
//							char* next_token = NULL;
//							int i = 0;
//							psc = strtok_s (str,"|",&next_token);
//							while (psc != NULL)
//							{
//								if(i==0)
//								{
//									strcpy_s(m_ApiName,256,psc);
//									break;
//								}
//								i++;
//								psc = strtok_s (NULL,"|",&next_token);
//							}
//							pApiData->insert(m_ApiName);
//						}
//						else
//						{
//							ret = FALSE;
//							break;
//						}
//					}
//					j=0;
//				}
//				else
//				{
//					str[j] = Dbuffer[i];
//					j++;
//				}
//			}
//		}
//		delete [] str;
//		delete [] Dbuffer;
//		CloseHandle(m_File);
//		return ret;
//	}
//	else
//		return FALSE;
//}
BYTE CAES::GfCalc(BYTE b, GfCalcMode Mode)
{
	switch (Mode)
	{
	case GfCalcMode::MODE01:
		return b;
		break;
	case GfCalcMode::MODE02:
		if (b < 0x80)
			return (BYTE)(int)(b << 1);
		else
			return (BYTE)((int)(b << 1) ^ (int)(0x1b));
		break;
	case GfCalcMode::MODE03://(b*2)+b*1
		return (BYTE)((int)GfCalc(b, GfCalcMode::MODE02) ^ (int)b);
		break;
	case GfCalcMode::MODE09://(b*2*2*2)+b*1
		return (BYTE)((int)GfCalc(GfCalc(GfCalc(b, GfCalcMode::MODE02), GfCalcMode::MODE02), GfCalcMode::MODE02) ^
			(int)b);
		break;
	case GfCalcMode::MODE0b://(b*2*2*2)+(b*2)+b*1
		return (BYTE)((int)GfCalc(GfCalc(GfCalc(b, GfCalcMode::MODE02), GfCalcMode::MODE02), GfCalcMode::MODE02) ^
			(int)GfCalc(b, GfCalcMode::MODE02) ^
			(int)b);
		break;
	case GfCalcMode::MODE0d://(b*2*2*2)+(b*2*2)+b*1
		return (BYTE)((int)GfCalc(GfCalc(GfCalc(b, GfCalcMode::MODE02), GfCalcMode::MODE02), GfCalcMode::MODE02) ^
			(int)GfCalc(GfCalc(b, GfCalcMode::MODE02), GfCalcMode::MODE02) ^
			(int)(b));
		break;
	case GfCalcMode::MODE0e://(b*2*2*2)+(b*2*2)+b*2
		return (BYTE)((int)GfCalc(GfCalc(GfCalc(b, GfCalcMode::MODE02), GfCalcMode::MODE02), GfCalcMode::MODE02) ^
			(int)GfCalc(GfCalc(b, GfCalcMode::MODE02), GfCalcMode::MODE02) ^
			(int)GfCalc(b, GfCalcMode::MODE02));
		break;
	default:
		return b;
	}
}

namespace py = pybind11;

PYBIND11_MODULE(PyAES, m) {
	// optional module docstring
	m.doc() = "pybind11 example plugin";

	// define add function
	//m.def("add", &add, "A function which adds two numbers");
	// bindings to Pet class
	py::class_<CAES>(m, "CAES")
		.def(py::init<>())
		.def("SetKeys", &CAES::SetKeys)
		.def("EncryptBuffer", &CAES::EncryptBuffer)
		.def("DecryptBuffer", &CAES::DecryptBuffer);
		
	py::enum_<KeySize>(m, "KeySize", py::arithmetic())
        .value("BIT128", KeySize::BIT128)
        .value("BIT192", KeySize::BIT192)
        .value("BIT256", KeySize::BIT256)
        .export_values();

}