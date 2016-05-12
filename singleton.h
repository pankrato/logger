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
 
protected:
	Singleton();

private:
	Singleton(const Type&) = delete;
	Singleton& operator=(const Type&) = delete;
};

