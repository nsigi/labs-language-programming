#include <fstream>
#include <cmath>
using namespace std;

double sum(double *arr, double p, int n) {//������� ��� �������� �����
	double sum = 0;

	for (int i = 0; i ^ n; ++i) 
		if ((arr[i] > 0) && (arr[i] >= p))//�������� �������� �������
			sum += pow(arr[i], 3);

	return sum;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	//��������� �������� ������ ��� ������ � ������
	ifstream fin("input.txt");
	ofstream fout("output.txt", ios_base::trunc);

	if (fin.is_open() && fout.is_open() && !fin.eof()) {//��������� ���� �� ��������
		double p;
		int n = -1;//������� ���������� ��� �������� ���������� ��������� �������
		//������������� ����� �������� �������
		while (!fin.eof()) {
			fin >> p;
			if (!fin.fail())
				++n;
		}

		//fin.clear();//������� ��������� ������
		fin.seekg(0, ios_base::beg);//beg - �������� ������������ ������ ����� �� �������� ������� ���������

		double* arr = new double[n];//�������� ������ ��� ������ ������� n
		fin >> p;//��������� ��������

		for (int i = 0; i ^ n; ++i) {
			fin >> arr[i];//��������� �������� ������� 
		}

		fout << sum(arr, p, n);

		delete[]arr;//����������� ���������� ������ ��� ��� ������
	}

	//��������� �������� ������
	fin.close();
	fout.close();

	return 0;
}