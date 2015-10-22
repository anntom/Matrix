#pragma once
#include <vector>

using namespace std;
typedef vector < vector< float > > MatrixType;
using namespace std;
class Matrix
{
public:
	Matrix(MatrixType &mat);
	Matrix operator*(Matrix const &mat) const;
	void print() const;

private:
	Matrix();
	MatrixType Mat;
};
