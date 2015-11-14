
#include <memory>
#include <cassert>
#include "AnyValue.h"

typedef std::shared_ptr<struct MyData> MyDataRef;

struct MyData
{
	static MyDataRef create(int value) { return std::make_shared<MyData>(value); }

	MyData(int value)
		: data(value)
	{}

	int data;
};

static const char* KeysTable[] =
{
	"Float",
	"Double",
	"Int",
	"String",
	"MyData",
	"Invalid"
};

struct Keys
{
	enum EKeys
	{
		Float,
		Double,
		Int,
		String,
		MyData,
		Count,
		Invalid = Count
	};

	union
	{
		EKeys name;
		unsigned int value;
	};

	Keys(EKeys name) : name(name) {}
	Keys(unsigned int value) : value(value) {}
	Keys() : value(Invalid) {}
	operator EKeys() const { return name; }
	const char* ToString() const { return KeysTable[value]; }
};


int main (int argc, char* argv[])
{
	int i = 10;
	float f = 10.0f;
	double d = 10.0;
	std::string s = "ten";
	MyDataRef myData = MyData::create(i);

	AnyValue any;
	any.setValue(Keys::Float, f);
	any.setValue(Keys::Double, d);
	any.setValue(Keys::Int, i);
	any.setValue(Keys::String, s);
	any.setValue(Keys::MyData, myData);

	int intVal = any.getVal<int>(Keys::Int);
	double doubleVal = any.getVal<double>(Keys::Double);
	float floatVal = any.getVal<float>(Keys::Float);
	std::string strVal = any.getVal<std::string>(Keys::String);
	MyDataRef mine = any.getVal<MyDataRef>(Keys::MyData);

	assert(intVal == i);
	assert(doubleVal == d);
	assert(floatVal == f);
	assert(strVal == s);
	assert(mine);
	assert(intVal = mine->data);

    return 0;
}
