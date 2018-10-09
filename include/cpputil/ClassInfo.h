#pragma once

#include <string>
#include <functional>
#include <memory>

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

#define DECLARE_BASE_CLASS_INFO(type)                                          \
public:                                                                        \
	virtual const cpputil::ClassInfo<type>& GetClassInfo() const = 0;          \
	static void Register(cpputil::ClassInfo<type>* ci);

#define IMPLEMENT_BASE_CLASS_INFO(type, class, func)                           \
void type::Register(cpputil::ClassInfo<type>* ci)                              \
{                                                                              \
	class::Instance()->func(ci);                                               \
}

#define DECLARE_CHILD_CLASS_INFO(base)                                         \
public:                                                                        \
	virtual const cpputil::ClassInfo<base>& GetClassInfo() const {             \
		return m_s_classinfo;                                                  \
	}                                                                          \
                                                                               \
	static auto& GetClassName() { return m_s_classinfo.GetClassName(); }       \
                                                                               \
private:                                                                       \
	static cpputil::ClassInfo<base> m_s_classinfo;

#define IMPLEMENT_CHILD_CLASS_INFO(base, child, name)                          \
cpputil::ClassInfo<base> child::m_s_classinfo(                                 \
	(#name),                                                                   \
	[]()->std::shared_ptr<base> { return std::make_shared<child>(); },         \
	[](cpputil::ClassInfo<base>* ci) { base::Register(ci); }                   \
);