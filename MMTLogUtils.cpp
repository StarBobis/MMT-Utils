#include "MMTLogUtils.h"
#include "MMTStringUtils.h"
#include "MMTJsonUtils.h"


MMTLogger::MMTLogger() {

}


MMTLogger::MMTLogger(std::wstring ApplicationLocation) {
    this->RunResultJsonPath = ApplicationLocation + L"\\Configs\\RunResult.json";
}


void MMTLogger::Info(std::wstring str) {
    LOG(INFO) << MMTString_ToByteString(str);
}


void MMTLogger::Info(std::string str) {
    LOG(INFO) << str;
}


void MMTLogger::Warning(std::wstring str) {
    LOG(INFO) << MMTString_ToByteString(L"[Warning]:" + str);
}


void MMTLogger::Warning(std::string str) {
    LOG(INFO) << "[Warning]:" + str;
}


void MMTLogger::SaveResultJson(std::wstring str) {
    nlohmann::json runResultJson;
    runResultJson["result"] = MMTString_ToByteString(str);
    MMTJson_SaveToJsonFile(this->RunResultJsonPath, runResultJson);
}


void MMTLogger::SaveResultJson(std::string str) {
    nlohmann::json runResultJson;
    runResultJson["result"] = str;
    MMTJson_SaveToJsonFile(this->RunResultJsonPath, runResultJson);
}


void MMTLogger::Error(std::wstring str) {
    //把结果写到json文件里面
    SaveResultJson(str);
    std::wcout << L"[Error]:" << str << "\n";
    LOG(INFO) << MMTString_ToByteString(L"[Error]:" + str);
    exit(1);
}


void MMTLogger::Error(std::string str) {
    //把结果写到json文件里面
    SaveResultJson(str);
    LOG(INFO) << "[Error]:" + str;
    exit(1);
}


void MMTLogger::Success() {
    //把结果写到json文件里面
    SaveResultJson(L"success");
    LOG(INFO) << "Run complete! Success!";
}


void MMTLogger::NewLine() {
    Info("--------------------------------------------------------------------");
}
