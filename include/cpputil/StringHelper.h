#pragma once

#include <string>
#include <vector>

namespace cpputil
{

class StringHelper
{
public:
	static void Split(const std::string& src, const std::string& mid,
		std::vector<std::string>& dst);
	static void ReplaceAll(std::string& str, const std::string& from,
		const std::string& to);

	template<typename T>
	static std::string ToString(const T& d, const int n = 6);

	static std::string UTF8ToGBK(const char* str);
	static std::string GBKToUTF8(const char* str);

	static std::string Format(const std::string str, ...);

	static std::string Trim(const std::string& str);

}; // StringHelper

}

#include "StringHelper.inl"