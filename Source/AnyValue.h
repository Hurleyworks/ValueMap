// This header file was auto-generated by ClassMate++
// Created: 13 Apr 2015 4:53:35 pm
// Copyright (c) 2015, HurleyWorks

#pragma once

#include "Any.h"
#include <unordered_map>

template <class PROPERTY>
class AnyValue
{
	typedef std::unordered_map<int, Poco::Any> ValueMap;

 public:
	 AnyValue() = default;
	~AnyValue() = default;
		
	void addDefault(const PROPERTY & key, const Poco::Any & value) { map_.insert(std::make_pair(key, value)); }
	void setValue(const PROPERTY & key, const Poco::Any & value)
	{
		auto it = map_.find(key);
		if (it == map_.end())
			map_.insert(std::make_pair(key, value));
		else
			it->second = value;
	}

	template <typename T>
	T & getRef(const PROPERTY & key) { return Poco::AnyCast<T>(getValue(key)); }

	template <typename T>
	T getVal(const PROPERTY & key) { return Poco::AnyCast<T>(getValue(key)); }

	template <typename T>
	T* getPtr(const PROPERTY & key) { return Poco::AnyCast<T>(&getValue(key)); }

 private:
	ValueMap map_;
	Poco::Any empty_;

	Poco::Any & getValue(const PROPERTY & key)
	{
		auto it = map_.find(key);
		if (it != map_.end())
			return it->second;

		return empty_;
	}
	
}; // end class AnyValue

