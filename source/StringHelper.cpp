#include "cpputil/StringHelper.h"

#include <boost/locale/encoding.hpp>

#include <stdarg.h>

namespace cpputil
{

void StringHelper::Split(const std::string& src, const std::string& mid, std::vector<std::string>& dst)
{
	char* cstr = new char[src.length() + 1];
	std::strcpy(cstr, src.c_str());
	char* p = std::strtok(cstr, mid.c_str());
	while (p != 0)
	{
		dst.push_back(std::string(p));
		p = strtok(nullptr, mid.c_str());
	}
	delete[] cstr;
}

void StringHelper::ReplaceAll(std::string& str, const std::string& from, const std::string& to)
{
	if (from.empty()) {
		return;
	}
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
}

std::string StringHelper::UTF8ToGBK(const char* str)
{
	return boost::locale::conv::from_utf(str, "GBK");
}

std::string StringHelper::GBKToUTF8(const char* str)
{
	return boost::locale::conv::to_utf<char>(str, "GBK");
}

std::string StringHelper::Format(const std::string fmt, ...)
{
	int size = ((int)fmt.size()) * 2 + 50;   // Use a rubric appropriate for your code
	std::string str;
	va_list ap;
	while (1) {     // Maximum two passes on a POSIX system...
		str.resize(size);
		va_start(ap, fmt);
		int n = vsnprintf((char *)str.data(), size, fmt.c_str(), ap);
		va_end(ap);
		if (n > -1 && n < size) {  // Everything worked
			str.resize(n);
			return str;
		}
		if (n > -1)  // Needed size returned
			size = n + 1;   // For null char
		else
			size *= 2;      // Guess at a larger size (OS specific)
	}
	return str;
}

}