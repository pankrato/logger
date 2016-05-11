#pragma once

template <class Type>
class Singleton
{
public:
	static Type& Instance()
	{
		static Type instance;
		return instance;
	}
 
private:
	Singleton();
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
};

