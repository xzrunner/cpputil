#pragma once

#include <sstream>
#include <iomanip>

namespace cpputil
{

template<typename T>
static std::string StringHelper::ToString(const T& d, const int n)
{
	std::ostringstream out;
	out << std::setprecision(n) << d;
	return out.str();
}

}