#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>

//�ַ�������boost����
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/cxx11/any_of.hpp>

// �����ļ�����·����ȡ�ļ�����Ŀ¼·��,��β�����Զ�����/
std::wstring MMTString_GetFolderPathFromFilePath(std::wstring filePath);

//stringת��Ϊwstring
std::wstring MMTString_ToWideString(std::string input);

//wstringת��Ϊstring
std::string MMTString_ToByteString(std::wstring input);

//����UUID
std::wstring MMTString_GenerateUUIDW();

//���������ַ���
std::wstring MMTString_GetFormattedDateTimeForFilename();

//��C++ʵ�ַָ��ַ�������ΪBoost���޷�������L"=="��Ϊ�ָ���
//ԭʼ�ַ��������ڷָ���ַ���
std::vector<std::wstring> MMTString_SplitString(std::wstring originalStr,std::wstring delimiter);

//ͨ���ļ�·����ȡ�ļ���
std::wstring MMTString_GetFileNameFromFilePath(std::wstring filePath);

std::wstring MMTString_GetFileNameWithOutSuffix(std::wstring filePath);

std::wstring MMTString_ToLowerCase(const std::wstring str);
std::wstring MMTString_GetPSHashFromFileName(const std::wstring& input);
std::wstring MMTString_GetVSHashFromFileName(const std::wstring& input);
std::wstring MMTString_RemoveSquareBrackets(std::wstring inputStr);



