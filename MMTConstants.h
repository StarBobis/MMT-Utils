#pragma once
#include <string>

class MMTConstants {
public:
	bool Initialized = false;
	//把常量放在这里全局唯一一份，用的时候直接导入MMTStringUtils.h就能用
	std::string DXGI_FORMAT_R16_UINT_LowerCase = "dxgi_format_r16_uint";
	std::string DXGI_FORMAT_R32_UINT_LowerCase = "dxgi_format_r32_uint";

	std::string DXGI_FORMAT_R16_UINT_UpperCase = "DXGI_FORMAT_R16_UINT";
	std::string DXGI_FORMAT_R32_UINT_UpperCase = "DXGI_FORMAT_R32_UINT";

};
