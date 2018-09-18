#pragma once

#include <string>
#include <functional>

namespace cpputil
{

template <typename T>
class ClassInfo
{
public:
	ClassInfo(const std::string& class_name,
		      std::function<std::shared_ptr<T>()> ctor,
		      std::function<void(cpputil::ClassInfo<T>*)> regist)
		: m_class_name(class_name)
		, m_ctor(ctor)
	{
		regist(this);
	}

	auto& GetClassName() const { return m_class_name; }
	auto& GetCtor() const { return m_ctor; }

private:
	std::string m_class_name;
	std::function<std::shared_ptr<T>()> m_ctor = nullptr;

}; // ClassInfo

}