#pragma once
#include <vector>
#include <algorithm>


#define DefineGetter(ClassType, MemberType, MemberName, FuncName) 	MemberType get##FuncName(ClassType &object) { return object.MemberName; }
#define DefineConstGetter(ClassType, MemberType, MemberName, FuncName) 	MemberType get##FuncName(const ClassType &object) { return object.MemberName; }
#define DefineSetter(ClassType, MemberType, MemberName, FuncName)	void set##FuncName(ClassType &object, MemberType value) { object.MemberName = value; }

#define DefineGetterSetter(ClassName, MemberType, MemberName, FuncName) \
	DefineGetter(ClassName, MemberType, MemberName, FuncName) \
	DefineSetter(ClassName, MemberType, MemberName, FuncName)

#define DefineConstGetterSetter(ClassName, MemberType, MemberName, FuncName) \
	DefineConstGetter(ClassName, MemberType, MemberName, FuncName) \
	DefineSetter(ClassName, MemberType, MemberName, FuncName)


#define DefineArrayGetter(ClassName, MemberType, MemberName, FuncName, Count) \
	std::vector<MemberType> get##FuncName(const ClassName &object) \
	{ \
		std::vector<MemberType> array(Count); \
		std::copy(object.MemberName, object.MemberName + Count, array.begin()); \
		return array; \
	}

#define DefineArraySetter(ClassName, MemberType, MemberName, FuncName, Count) \
	void set##FuncName(ClassName &object, const std::vector<MemberType> &array) \
	{ \
		if(object.MemberName != nullptr) \
		{ \
			delete[] object.MemberName; \
		} \
		object.MemberName = new float[Count]; \
		std::copy(array.begin(), array.end(), object.MemberName); \
	}

#define DefineArrayGetterSetter(ClassName, MemberType, MemberName, FuncName, Count) \
	DefineArrayGetter(ClassName, MemberType, MemberName, FuncName, Count) \
	DefineArraySetter(ClassName, MemberType, MemberName, FuncName, Count)

