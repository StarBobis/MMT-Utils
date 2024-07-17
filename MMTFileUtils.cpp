#include <Windows.h>
#include <unordered_map>

#include <boost/algorithm/string.hpp>

#include <istream>
#include <fstream>
#include <filesystem>
#include <iostream>

#include "MMTFormatUtils.h"

bool MMTFile_MoveFileToRecycleBin_Deprecated(const std::wstring& filePath)
{
    if (!std::filesystem::exists(filePath))
    {
        // �ļ�������
        return false;
    }

    SHFILEOPSTRUCT fileOp = { 0 };
    fileOp.wFunc = FO_DELETE;

    //fileOp.pFrom = filePath.c_str();   Unicode�ַ�������������ֽ��ַ���������ġ�
    fileOp.pFrom = reinterpret_cast<PCZZSTR>(filePath.c_str());
    fileOp.fFlags = FOF_ALLOWUNDO | FOF_NOCONFIRMATION;

    int result = SHFileOperation(&fileOp);
    if (result != 0)
    {
        // ��������
        return false;
    }

    // �ļ��ѷ��͵�����վ
    return true;
}

//����FrameAnalyse�ļ����������������ļ����б� searchStr, endStr
std::vector<std::wstring> MMTFile_FindFileNameListWithCondition(std::wstring SearchFolderPath, std::wstring searchStr, std::wstring endStr) {
    std::vector<std::wstring> findFileNameList;
    std::vector<std::wstring> FilteredFileNameList;
    //Ȼ��ֱ�ӳ�ʼ��FrameAnalyse�ļ��б�
    //LOG.Info(L"Initialize Filtered folder file list.");
    for (const auto& entry : std::filesystem::directory_iterator(SearchFolderPath)) {
        if (!(entry.is_regular_file())) {
            continue;
        }
        FilteredFileNameList.push_back(entry.path().filename().wstring());
    }

    for (std::wstring fileName : FilteredFileNameList) {

        if (fileName.find(searchStr) != std::string::npos && fileName.substr(fileName.length() - endStr.length()) == endStr) {
            findFileNameList.push_back(fileName);
        }
    }
    return findFileNameList;
}


std::vector<std::wstring> MMTFile_ReadIniFileLineList(std::wstring filePath)
{
    std::vector<std::wstring> lines;
    std::wifstream inFile(filePath);

    if (inFile.is_open())
    {
        std::wstring line;
        while (std::getline(inFile, line))
        {
            lines.push_back(line);
        }

        inFile.close();
    }

    return lines;
}


std::vector<std::wstring> MMTFile_GetFilePathListRecursive(std::wstring directory)
{
    std::vector<std::wstring> filePathList;

    for (const auto& entry : std::filesystem::directory_iterator(directory))
    {
        const auto& path = entry.path();
        if (std::filesystem::is_directory(path))
        {
            // �ݹ�����Ի�ȡ���ļ����е��ļ�
            std::vector<std::wstring> subFileNames = MMTFile_GetFilePathListRecursive(path);
            filePathList.insert(filePathList.end(), subFileNames.begin(), subFileNames.end());
        }
        else if (std::filesystem::is_regular_file(path))
        {
            filePathList.push_back(path.wstring());
        }
    }

    return filePathList;
}


std::vector<std::wstring> MMTFile_ReadAllLinesW(std::wstring filePath) {
    std::wifstream file(filePath); // ����ifstream���󲢴��ļ�
    std::vector<std::wstring> lines; // ����һ��string���͵�vector�������洢�ļ��е�ÿһ��
    //LOG.LogOutput(L"Start to read all lines.");
    if (file.is_open()) { // ����ļ��Ƿ�ɹ���
        std::wstring line;
        while (std::getline(file, line)) { // ��ȡÿһ�У�ֱ���ļ���β
            lines.push_back(line); // ����ȡ��������ӵ�vector��
        }
        file.close(); // �ر��ļ�
    }
    else {
        std::cout << "Can't open this file!" << std::endl;
    }
    return lines;
}


//Ŀ¼����׺����ɾ��ָ��Ŀ¼��ָ����׺���������ļ�
void MMTFile_DeleteFilesWithSuffix(std::wstring directory, std::wstring suffix)
{
    for (const auto& entry : std::filesystem::directory_iterator(directory))
    {
        if (entry.is_regular_file() && entry.path().extension() == suffix)
        {
            std::filesystem::remove(entry.path());
            //MoveFileToRecycleBin(entry.path().wstring());
            //LOG.Info(L"Delete file:" + entry.path().wstring());
        }
    }
}


std::unordered_map<int, std::vector<std::byte>> MMTFile_ReadBufMapFromFile(std::wstring readPathW, int vertexNumber) {
    //LOG.Info(L"Read from " + readPathW);
    std::unordered_map<int, std::vector<std::byte>> BufMap;

    int stride = 0;
    std::ifstream BufFile(readPathW, std::ifstream::binary);
    BufFile.seekg(0, std::ios::end);
    //LOG.Info(L"Read Size: " + std::to_wstring(BufFile.tellg()));
    stride = int(BufFile.tellg() / vertexNumber);
    BufFile.seekg(0, std::ios::beg);
    //LOG.Info(L"Stride: " + std::to_wstring(stride));

    std::vector<std::byte> Buffer(vertexNumber * stride);
    BufFile.read(reinterpret_cast<char*>(Buffer.data()), vertexNumber * stride);
    BufFile.close();
    for (int i = 0; i < vertexNumber; i++) {
        BufMap[i] = MMTFormat_GetRange_Byte(Buffer, i * stride, i * stride + stride);
    }

    return BufMap;
}


int MMTFile_GetFileSize(std::wstring FileName) {
    std::ifstream BufFile(FileName, std::ifstream::binary);
    BufFile.seekg(0, std::ios::end);
    int fileSize = int(BufFile.tellg());
    BufFile.close();
    return fileSize;
}


uint64_t MMTFile_GetRealFileSize_NullTerminated(std::wstring FileName) {
    std::ifstream file(FileName, std::ios::binary);
    std::vector<char> data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    uint64_t end = data.size() - 1;
    while (end >= 0 && data[end] == 0) {
        end--;
    }
    uint64_t length = end + 1;
    file.close();
    return length;
}


//����ָ��directoryPathĿ¼����prefix��ͷ��Ŀ¼������һ���������Զ�ȷ��FrameAnalyseFolder.
std::wstring MMTFile_FindMaxPrefixedDirectory(const std::wstring& directoryPath, const std::wstring& prefix) {
    std::vector<std::wstring> matchingDirectories;

    for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
        if (entry.is_directory()) {
            std::wstring directoryName = entry.path().filename().wstring();
            if (directoryName.substr(0, prefix.size()) == prefix) {
                matchingDirectories.push_back(directoryName);
            }
        }
    }

    if (matchingDirectories.empty()) {
        return L"";
    }

    // ���ֵ�������Ŀ¼����
    std::sort(matchingDirectories.begin(), matchingDirectories.end());

    // ��������Ŀ¼����
    return matchingDirectories.back();
}


//���ļ��в���ָ�����ԣ��������topology,���ṩ����·�� ·������������
std::wstring MMTFile_FindMigotoIniAttributeInFile(const std::wstring& filePath, const std::wstring& attributeName) {
    std::wifstream file(filePath);
    std::wstring attributeValue;

    if (file.is_open()) {
        std::wstring line;
        while (std::getline(file, line)) {
            boost::algorithm::trim(line);
            if (line.find(attributeName + L":") != std::string::npos) {
                size_t pos = line.find(L":");
                std::wstring var = line.substr(pos + 1);
                boost::algorithm::trim(var);
                attributeValue = var;
                break;
            }
        }
        file.close();
    }

    return attributeValue;
}


bool MMTFile_IsValidFilename(std::string filename) {
    try {
        // ʹ�� std::filesystem::path ��������ļ����Ƿ���Ч
        std::filesystem::path p(filename);
        return p.filename() == filename;
    }
    catch (const std::exception&) {
        // ��������κ��쳣,˵���ļ�����Ч
        return false;
    }
}





