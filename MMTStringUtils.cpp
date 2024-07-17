#include "MMTStringUtils.h"
#include <filesystem>
// uuid
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
// time
#include <boost/date_time/posix_time/posix_time.hpp>


std::wstring MMTString_GetFolderPathFromFilePath(std::wstring filePath) {
    std::size_t lastSlash = filePath.find_last_of(L"\\/");
    std::wstring path = filePath.substr(0, lastSlash);
    return path;
}

std::wstring MMTString_GetFileNameFromFilePath(std::wstring filePath) {
    std::filesystem::path pathObj(filePath);
    return pathObj.filename();
}

std::wstring MMTString_GetFileNameWithOutSuffix(std::wstring filePath) {
    // �������һ��'.'��λ��
    size_t dotPos = filePath.find_last_of(L'.');

    // ����ҵ���'.'
    if (dotPos != std::wstring::npos) {
        // �����ļ�������
        return filePath.substr(0, dotPos);
    }
    else {
        // ���û���ҵ�'.'��ֱ�ӷ��������ļ�·��
        return filePath;
    }
}


std::wstring MMTString_ToWideString(std::string input) {
    if (input.empty()) return L"";

    int size_needed = MultiByteToWideChar(CP_UTF8, 0, input.c_str(), -1, NULL, 0);
    if (size_needed == 0) {
        // Handle error appropriately
        throw std::runtime_error("Failed in MultiByteToWideChar conversion.");
    }

    std::wstring wstrTo(size_needed, L'\0');
    int chars_converted = MultiByteToWideChar(CP_UTF8, 0, input.c_str(), -1, &wstrTo[0], size_needed);
    if (chars_converted == 0) {
        // Handle error appropriately
        throw std::runtime_error("Failed in MultiByteToWideChar conversion.");
    }

    // Remove the null terminator as it is implicitly handled in std::wstring
    wstrTo.pop_back();

    return wstrTo;
}


std::string MMTString_ToByteString(std::wstring input) {
    if (input.empty()) return "";

    int size_needed = WideCharToMultiByte(CP_UTF8, 0, input.c_str(), -1, NULL, 0, NULL, NULL);
    if (size_needed == 0) {
        // Handle error appropriately
        throw std::runtime_error("Failed in WideCharToMultiByte conversion.");
    }

    std::string strTo(size_needed, '\0');
    int bytes_converted = WideCharToMultiByte(CP_UTF8, 0, input.c_str(), -1, &strTo[0], size_needed, NULL, NULL);
    if (bytes_converted == 0) {
        // Handle error appropriately
        throw std::runtime_error("Failed in WideCharToMultiByte conversion.");
    }

    // Remove the null terminator as it is implicitly handled in std::string
    strTo.pop_back();

    return strTo;
}


std::wstring MMTString_GenerateUUIDW() {
    boost::uuids::random_generator generator;
    boost::uuids::uuid uuid = generator();
    return MMTString_ToWideString(boost::uuids::to_string(uuid));
}


std::wstring MMTString_GetFormattedDateTimeForFilename()
{
    // ��ȡ�������ں�ʱ��
    boost::posix_time::ptime localTime =
        boost::posix_time::second_clock::local_time();

    // ��ʽ�����ں�ʱ��Ϊ�ַ���
    std::wstring dateTimeStr =
        boost::posix_time::to_iso_extended_wstring(localTime);

    // ���»����滻���ں�ʱ���еķ���ĸ�����ַ�
    boost::replace_all(dateTimeStr, "-", "_");
    boost::replace_all(dateTimeStr, ":", "_");

    return dateTimeStr;
}

//ԭʼ�ַ��������ڷָ���ַ���
//ע������Ҳ����ָ����᷵��һ������Ϊ1���б�װ��ԭʼ���ַ����������жϵ�ʱ��Ҫ��1������0
std::vector <std::wstring> MMTString_SplitString(std::wstring originalStr, std::wstring delimiter) {
    std::vector<std::wstring> result;
    std::wstring str = originalStr;
    size_t pos = 0;
    while ((pos = str.find(delimiter)) != std::wstring::npos) {
        std::wstring token = str.substr(0, pos);
        result.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    result.push_back(str);
    return result;
}


std::wstring MMTString_ToLowerCase(const std::wstring str)
{
    std::wstring result;
    std::locale loc;

    for (wchar_t c : str)
    {
        result += std::tolower(c, loc);
    }

    return result;
}


std::wstring MMTString_GetPSHashFromFileName(const std::wstring& input) {
    std::wstring result;
    size_t pos = input.find(L"-ps=");
    if (pos != std::wstring::npos && pos + 4 + 16 <= input.length()) {
        result = input.substr(pos + 4, 16);
    }
    return result;
}


std::wstring MMTString_GetVSHashFromFileName(const std::wstring& input) {
    std::wstring result;
    size_t pos = input.find(L"-vs=");
    if (pos != std::wstring::npos && pos + 4 + 16 <= input.length()) {
        result = input.substr(pos + 4, 16);
    }
    return result;
}

//��ȷ��������ַ�����[]��������
std::wstring MMTString_RemoveSquareBrackets(std::wstring inputStr) {
    if (inputStr.size() >= 2 && inputStr.front() == L'[' && inputStr.back() == L']') {
        inputStr = inputStr.substr(1, inputStr.size() - 2);
    }
    return inputStr;
}
