#pragma once
#include <iostream>
#include <fstream>
#include <sstream>

#include "json.hpp"


//���ڶ�ȡJson�ļ�������
nlohmann::json MMTJson_ReadJsonFromFile(const std::wstring&);

//���浽json�ļ�,�����json�ļ�·����json����
void MMTJson_SaveToJsonFile(std::wstring, nlohmann::json);

