#pragma once
#include <vector>
#include <fstream>

using namespace std;

class MyException : public exception
{
public:
	MyException(const char * exc_)
		:exc(exc_)
	{}
	virtual const char* what() const throw()
	{
		return exc.c_str();
	}
private:
	string exc;
};

class Matrix
{
typedef vector < vector< float > > MatrixType;
public:
	Matrix(){}
	Matrix operator*(Matrix const &mat) const;
	friend ifstream& operator>>(ifstream &in, Matrix &mat);
	friend ofstream& operator<<(ofstream &out, Matrix &mat);

private:
	MatrixType Mat;
};
