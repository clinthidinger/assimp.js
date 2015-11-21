#pragma once


#define DefineGetter(ClassType, MemberType, MemberName, FuncName) 	MemberType get##FuncName(ClassType &object) { return object.MemberName; }
#define DefineSetter(ClassType, MemberType, MemberName, FuncName)	void set##FuncName(ClassType &object, MemberType value) { object.MemberName = value; }

#define DefineGetterSetter(ClassName, MemberType, MemberName, FuncName) \
	DefineGetter(ClassName, MemberType, MemberName, FuncName) \
	DefineSetter(ClassName, MemberType, MemberName, FuncName)

class YoMama
	{
	public:
		YoMama()
		{

		}
		int y;
	};