#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <filesystem>
#include <istream>
#include <fstream>


//�ƶ��ļ�������վ������ֱ��ɾ������ֹ���ݶ�ʧ
//ʵ�ʲ��Է�����BUG���е�ʱ���޷��ƶ��ļ�������վ�����Բ��Ƽ�ʹ��
bool MMTFile_MoveFileToRecycleBin_Deprecated(const std::wstring& filePath);

std::vector<std::wstring> MMTFile_FindFileNameListWithCondition(std::wstring SearchFolderPath, std::wstring searchStr, std::wstring endStr);


std::vector<std::wstring> MMTFile_ReadIniFileLineList(std::wstring filePath);

std::vector<std::wstring> MMTFile_GetFilePathListRecursive(std::wstring directory);

//��ȡ�ļ��������У�һ������ini��ȡ�����
std::vector<std::wstring> MMTFile_ReadAllLinesW(std::wstring filePath);

//ɾ��ָ��Ŀ¼��ָ����׺���ļ�������������һ�����ɵ�Mod�ļ���
void MMTFile_DeleteFilesWithSuffix(std::wstring directory, std::wstring suffix);

std::unordered_map<int, std::vector<std::byte>> MMTFile_ReadBufMapFromFile(std::wstring readPathW, int vertexNumber);

//��ȡ�ļ���С
int MMTFile_GetFileSize(std::wstring FileName);

//��ȡ����Ľ�β������ر��0���ļ�����ʵ�Ĳ�Ϊ0���ֵ��ļ���С
uint64_t MMTFile_GetRealFileSize_NullTerminated(std::wstring FileName);

std::wstring MMTFile_FindMaxPrefixedDirectory(const std::wstring& directoryPath, const std::wstring& prefix);

//���ļ��в���ָ��3Dmigoto��ini�������ԣ��������format,���ṩ����·������ֱ�ӷ��������ļ���������������
std::wstring MMTFile_FindMigotoIniAttributeInFile(const std::wstring& filePath, const std::wstring& attributeName);

bool MMTFile_IsValidFilename(std::string filename);

