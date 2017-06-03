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
		object.MemberName = new MemberType[Count]; \
		std::copy(array.begin(), array.end(), object.MemberName); \
	}

#define DefineArrayGetterSetter(ClassName, MemberType, MemberName, FuncName, Count) \
	DefineArrayGetter(ClassName, MemberType, MemberName, FuncName, Count) \
	DefineArraySetter(ClassName, MemberType, MemberName, FuncName, Count)


//#define DefineArraySetGetter(ClassName, MemberType, MemberName, FuncName, Count, Max) \
//	std::vector<MemberType> get##FuncName(const ClassName &object, unsigned int index) \
//	{ \
//		std::vector<MemberType> array(Count); \
//		if(index < Max) \
//		{ \
//			std::copy(object.MemberName[index], object.MemberName[index] + Count, array.begin()); \
//		} \
//		return array; \
//	}

//#define DefineArraySetSetter(ClassName, MemberType, MemberName, FuncName, Count, Max) \
//	void set##FuncName(ClassName &object, const std::vector<MemberType> &array, unsigned int index) \
//	{ \
//		if(index >= Max) \
//		{ \
//			return; \
//		} \
//		if(object.MemberName[index] != nullptr) \
//		{ \
//			delete[] object.MemberName[index]; \
//		} \
//		object.MemberName[index] = new MemberType[Count]; \
//		std::copy(array.begin(), array.end(), object.MemberName[index]); \
//	}

//#define DefineArraySetGetterSetter(ClassName, MemberType, MemberName, FuncName, Count, Max) \
//	DefineArraySetGetter(ClassName, MemberType, MemberName, FuncName, Count, Max) \
//	DefineArraySetSetter(ClassName, MemberType, MemberName, FuncName, Count, Max)

#define DefineArrayIndexGetter(ClassName, MemberType, MemberName, FuncName) \
	MemberType get##FuncName(const ClassName &object, unsigned int index) \
	{ \
		return object.MemberName[index]; \
	}

#define DefineArrayIndexSetter(ClassName, MemberType, MemberName, FuncName) \
	void set##FuncName(ClassName &object, unsigned int index, MemberType value) \
	{ \
		object.MemberName[index] = value; \
	}
#define DefineArrayIndexGetterSetter(ClassName, MemberType, MemberName, FuncName) \
	DefineArrayIndexGetter(ClassName, MemberType, MemberName, FuncName) \
	DefineArrayIndexSetter(ClassName, MemberType, MemberName, FuncName)

//????
#define DefineArrayIndexRefGetter(ClassName, MemberType, MemberName, FuncName) \
	const MemberType &get##FuncName(const ClassName &object, unsigned int index) \
	{ \
		return object.MemberName[index]; \
	}

#define DefineArrayIndexRefSetter(ClassName, MemberType, MemberName, FuncName) \
	void set##FuncName(ClassName &object, unsigned int index, const MemberType &value) \
	{ \
		object.MemberName[index] = value; \
	}
#define DefineArrayIndexRefGetterSetter(ClassName, MemberType, MemberName, FuncName) \
	DefineArrayIndexRefGetter(ClassName, MemberType, MemberName, FuncName) \
	DefineArrayIndexRefSetter(ClassName, MemberType, MemberName, FuncName)


template<class ArrayType>
inline void allocateArray(ArrayType **array, size_t count, size_t &defaultCount)
{
	if(array == nullptr)
	{
		return;
	}
	if(count == 0)
	{
		count = defaultCount;
	}
	else
	{
		defaultCount = count;
	}
	
	if(*array != nullptr)
	{
		delete[] *array;	
	}	
	*array = new ArrayType[count];
}
