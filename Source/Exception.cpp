//
// Exception.cpp
//
// $Id: //poco/1.4/Foundation/src/Exception.cpp#1 $
//
// Library: Foundation
// Package: Core
// Module:  Exception
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


//#include "Poco/Exception.h"
//#include <typeinfo>
//
#include "Exception.h"

namespace Poco {


Exception::Exception(int code): _pNested(0), _code(code)
{
}


Exception::Exception(const std::string& msg, int code): _msg(msg), _pNested(0), _code(code)
{
}


Exception::Exception(const std::string& msg, const std::string& arg, int code): _msg(msg), _pNested(0), _code(code)
{
	if (!arg.empty())
	{
		_msg.append(": ");
		_msg.append(arg);
	}
}


Exception::Exception(const std::string& msg, const Exception& nested, int code): _msg(msg), _pNested(nested.clone()), _code(code)
{
}


Exception::Exception(const Exception& exc):
	std::exception(exc),
	_msg(exc._msg),
	_code(exc._code)
{
	_pNested = exc._pNested ? exc._pNested->clone() : 0;
}

	
Exception::~Exception() throw()
{
	delete _pNested;
}


Exception& Exception::operator = (const Exception& exc)
{
	if (&exc != this)
	{
		delete _pNested;
		_msg     = exc._msg;
		_pNested = exc._pNested ? exc._pNested->clone() : 0;
		_code    = exc._code;
	}
	return *this;
}


const char* Exception::name() const throw()
{
	return "Exception";
}


const char* Exception::className() const throw()
{
	return typeid(*this).name();
}

	
const char* Exception::what() const throw()
{
	return name();
}

	
std::string Exception::displayText() const
{
	std::string txt = name();
	if (!_msg.empty())
	{
		txt.append(": ");
		txt.append(_msg);
	}
	return txt;
}


void Exception::extendedMessage(const std::string& arg)
{
	if (!arg.empty())
	{
		if (!_msg.empty()) _msg.append(": ");
		_msg.append(arg);
	}
}


Exception* Exception::clone() const
{
	return new Exception(*this);
}


void Exception::rethrow() const
{
	throw *this;
}


POCO_IMPLEMENT_EXCEPTION(LogicException, Exception, "Logic exception")
POCO_IMPLEMENT_EXCEPTION(AssertionViolationException, LogicException, "Assertion violation")
POCO_IMPLEMENT_EXCEPTION(NullPointerException, LogicException, "Null pointer")
POCO_IMPLEMENT_EXCEPTION(NullValueException, LogicException, "Null value")
POCO_IMPLEMENT_EXCEPTION(BugcheckException, LogicException, "Bugcheck")
POCO_IMPLEMENT_EXCEPTION(InvalidArgumentException, LogicException, "Invalid argument")
POCO_IMPLEMENT_EXCEPTION(NotImplementedException, LogicException, "Not implemented")
POCO_IMPLEMENT_EXCEPTION(RangeException, LogicException, "Out of range")
POCO_IMPLEMENT_EXCEPTION(IllegalStateException, LogicException, "Illegal state")
POCO_IMPLEMENT_EXCEPTION(InvalidAccessException, LogicException, "Invalid access")
POCO_IMPLEMENT_EXCEPTION(SignalException, LogicException, "Signal received")
POCO_IMPLEMENT_EXCEPTION(UnhandledException, LogicException, "Unhandled exception")

POCO_IMPLEMENT_EXCEPTION(RuntimeException, Exception, "Runtime exception")
POCO_IMPLEMENT_EXCEPTION(NotFoundException, RuntimeException, "Not found")
POCO_IMPLEMENT_EXCEPTION(ExistsException, RuntimeException, "Exists")
POCO_IMPLEMENT_EXCEPTION(TimeoutException, RuntimeException, "Timeout")
POCO_IMPLEMENT_EXCEPTION(SystemException, RuntimeException, "System exception")
POCO_IMPLEMENT_EXCEPTION(RegularExpressionException, RuntimeException, "Error in regular expression")
POCO_IMPLEMENT_EXCEPTION(LibraryLoadException, RuntimeException, "Cannot load library")
POCO_IMPLEMENT_EXCEPTION(LibraryAlreadyLoadedException, RuntimeException, "Library already loaded")
POCO_IMPLEMENT_EXCEPTION(NoThreadAvailableException, RuntimeException, "No thread available")
POCO_IMPLEMENT_EXCEPTION(PropertyNotSupportedException, RuntimeException, "Property not supported")
POCO_IMPLEMENT_EXCEPTION(PoolOverflowException, RuntimeException, "Pool overflow")
POCO_IMPLEMENT_EXCEPTION(NoPermissionException, RuntimeException, "No permission")
POCO_IMPLEMENT_EXCEPTION(OutOfMemoryException, RuntimeException, "Out of memory")
POCO_IMPLEMENT_EXCEPTION(DataException, RuntimeException, "Data error")

POCO_IMPLEMENT_EXCEPTION(DataFormatException, DataException, "Bad data format")
POCO_IMPLEMENT_EXCEPTION(SyntaxException, DataException, "Syntax error")
POCO_IMPLEMENT_EXCEPTION(CircularReferenceException, DataException, "Circular reference")
POCO_IMPLEMENT_EXCEPTION(PathSyntaxException, SyntaxException, "Bad path syntax")
POCO_IMPLEMENT_EXCEPTION(IOException, RuntimeException, "I/O error")
POCO_IMPLEMENT_EXCEPTION(ProtocolException, IOException, "Protocol error")
POCO_IMPLEMENT_EXCEPTION(FileException, IOException, "File access error")
POCO_IMPLEMENT_EXCEPTION(FileExistsException, FileException, "File exists")
POCO_IMPLEMENT_EXCEPTION(FileNotFoundException, FileException, "File not found")
POCO_IMPLEMENT_EXCEPTION(PathNotFoundException, FileException, "Path not found")
POCO_IMPLEMENT_EXCEPTION(FileReadOnlyException, FileException, "File is read-only")
POCO_IMPLEMENT_EXCEPTION(FileAccessDeniedException, FileException, "Access to file denied")
POCO_IMPLEMENT_EXCEPTION(CreateFileException, FileException, "Cannot create file")
POCO_IMPLEMENT_EXCEPTION(OpenFileException, FileException, "Cannot open file")
POCO_IMPLEMENT_EXCEPTION(WriteFileException, FileException, "Cannot write file")
POCO_IMPLEMENT_EXCEPTION(ReadFileException, FileException, "Cannot read file")
POCO_IMPLEMENT_EXCEPTION(UnknownURISchemeException, RuntimeException, "Unknown URI scheme")


POCO_IMPLEMENT_EXCEPTION(ApplicationException, Exception, "Application exception")
POCO_IMPLEMENT_EXCEPTION(BadCastException, RuntimeException, "Bad cast exception")

} // namespace Poco
