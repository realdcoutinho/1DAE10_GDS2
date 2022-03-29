#pragma once
#include <iostream>
class Blob
{
public:
	///*explicit*/ Blob(int size);
	explicit Blob(int size);

	Blob(const Blob& other); // copy constructor
	Blob& operator=(const Blob& rhs); // copy assignment

	Blob(Blob&& other) noexcept; // move constructor
	Blob& operator=(Blob&& rhs) noexcept; // move assignment

	~Blob();

	void Print() const;
	void Double();

	int& operator[](int index);

	friend std::ostream& operator<<(std::ostream& out, const Blob& rhs);
private:
	int m_Size;
	int* m_pData;
};


