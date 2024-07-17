#pragma once
#include <iostream>
#include "easylogging++.h"

class MMTLogger {
public:
	std::wstring RunResultJsonPath;

	//��־��¼����
	void Info(std::wstring);
	void Info(std::string);

	void Warning(std::wstring);
	void Warning(std::string);

	void Error(std::wstring);
	void Error(std::string);

	void NewLine();
	void Success();

	void SaveResultJson(std::wstring);
	void SaveResultJson(std::string);

	MMTLogger();
	MMTLogger(std::wstring ApplicationLocation);
};

//ȫ����־��
extern MMTLogger LOG;
