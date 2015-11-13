
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

typedef AnyValue<Keys> Properties;


int main (int argc, char* argv[])
{
	int i = 10;
	float f = 10.0f;
	double d = 10.0;
	std::string s = "ten";
	MyDataRef myData = MyData::create(i);

	Properties props;
	props.setValue(Keys::Float, f);
	props.setValue(Keys::Double, d);
	props.setValue(Keys::Int, i);
	props.setValue(Keys::String, s);
	props.setValue(Keys::MyData, myData);

	int intVal = props.getVal<int>(Keys::Int);
	double doubleVal = props.getVal<double>(Keys::Double);
	float floatVal = props.getVal<float>(Keys::Float);
	std::string strVal = props.getVal<std::string>(Keys::String);
	MyDataRef mine = props.getVal<MyDataRef>(Keys::MyData);

	assert(intVal == i);
	assert(doubleVal == d);
	assert(floatVal == f);
	assert(strVal == s);
	assert(mine);
	assert(intVal = mine->data);

    return 0;
}
