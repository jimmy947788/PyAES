// PyAES.h: 標準系統 include 檔案的 include 檔案，
// 或專案專屬的 Include 檔案。

#pragma once

// AES.h: interface for the CAES class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AES_H__787EA6CD_A461_497A_A0A3_3FE851B9F557__INCLUDED_)
#define AFX_AES_H__787EA6CD_A461_497A_A0A3_3FE851B9F557__INCLUDED_

#include <vector>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef unsigned char BYTE;

enum class KeySize
{
	BIT128 = 0,
	BIT192 = 1,
	BIT256 = 2
};

enum class GfCalcMode
{
	MODE01 = 0,
	MODE02,
	MODE03,
	MODE09,
	MODE0b,
	MODE0d,
	MODE0e
};

struct BYTE4
{
	BYTE w[4];
};

class CAES
{
private:
	int Nk, Nr;
	BYTE(*State)[4], * w[4], * key[4];

	void SubBytes();
	void ShiftRows();
	void MixColumns();
	void AddRoundKey(int round);
	void KeyExpansion();
	void InvShiftRows();
	void InvSubBytes();
	void InvMixColumns();
	BYTE GfCalc(BYTE b, GfCalcMode Mode);
	void Encrypt(BYTE* input, BYTE* output);
	void Decrypt(BYTE* input, BYTE* output);

public:
	CAES();
	virtual ~CAES();

	bool SetKeys(KeySize keySize, const char* sKey);
	std::vector<char> EncryptBuffer(const std::vector<char>& input);
	std::vector<char> DecryptBuffer(const std::vector<char>& input);
	//BOOL DecryptFileLoadingData(TCHAR* SourceFile,set<string> * pApiData);
	/*wchar_t* EncryptString(wchar_t* input);
	char* EncryptStringA(char* input);*/
	//CString &EncryptString(CString &input);
	//CString &DecryptString(CString &input);
	//void EncryptFile(CString SourceFile,CString TagerFile);
	//void DecryptFile(CString SourceFile,CString TagerFile);
};


#endif // !defined(AFX_AES_H__787EA6CD_A461_497A_A0A3_3FE851B9F557__INCLUDED_)
