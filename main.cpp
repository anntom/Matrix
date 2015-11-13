#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include "Matrix.h"
#include "time.h"

using namespace std;

bool read(const char * path, Matrix &mat)
{
	ifstream f(path);
	if (f.is_open())
	{
		try{
			f>>mat;
		}
		catch(const char* str){
			cout << str << endl;
			return false;
		}
		return true;
	}
	else
	{
		throw MyException("Can't open file");
		return false;
	}
}

int main(int argc, char * argv[])
{
	Matrix mat1, mat2;
	if (argc != 4)
	{
		cout << "Enter path to file" << endl;
		return -1;
	}
	else
	{
		string path1 = argv[1];
		string path2 = argv[2];
		string path_out = argv[3];
		bool read1, read2;
		try{
			read1 = read(path1.c_str(), mat1);
			read2 = read(path2.c_str(), mat2);
		}
		catch(const char* str){
			cout << str << endl; 
		}
		if (read1 && read2)
		{
			time_t start;
			time_t end;
			start = clock();
			Matrix res = mat1 * mat2;
			end = clock();
			cout << difftime(end, start) << endl;
			ofstream f(path_out);
			if (f.is_open())
			{
				f<<res;
			}
			else
			{
				cout << "Can't open file" << endl;
				return -1;
			}
		} 
		else
		{
			return -1;
		}
	}
	return 0;
}