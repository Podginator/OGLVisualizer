#pragma once

template<int size, typename T> 
class Vector
{
protected:
	T *data;
	void Copy(const Vector<size, T>& copied);
public: 
	Vector()

};