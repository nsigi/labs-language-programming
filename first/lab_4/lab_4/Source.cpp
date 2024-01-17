#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

class VectorTD {
protected:
	double x, y, z; //���������� �������
public:
	//����������� ������������� 
	VectorTD(double cx, double cy, double cz) : x(cx), y(cy), z(cz) {};

	//����������� �� ���������
	VectorTD() {
		x = y = z = 0;
	}

	//����������� �����������
	VectorTD(const VectorTD& vec) {
		x = vec.x;
		y = vec.y;
		z = vec.z;
	}

	//������ ������� (�����)
	double length() {
		return sqrt(x * x + y * y + z * z);
	}

	//������������� ��������� ����� � ������
	friend ofstream& operator<<(ofstream& fout, VectorTD vec);
	friend ifstream& operator>>(ifstream& fin, VectorTD& vec);

	//������������� �������������� ��������
	//��������
	const VectorTD operator + (VectorTD const& rightV) {
		return VectorTD(x + rightV.x, y + rightV.y, z + rightV.z);
	}
	//���������
	const VectorTD operator - (VectorTD const& rightV) {
		return VectorTD(x - rightV.x, y - rightV.y, z - rightV.z);
	}
	//��������� ������� �� �����
	VectorTD operator * (int a) {
		return VectorTD(x * a, y * a, z * a);
	}
	friend VectorTD operator * (int a, VectorTD rightV);

	//������� ������� �� ����� �������� �� ���� (����� ������ �� ����������)
	VectorTD operator / (double a) {
		if (!a)	cerr << "�� ���� ������ ������";
		else return VectorTD(x / a, y / a, z / a);
		return *this;
	}

	//������������� �������� ������������
	VectorTD operator = (const VectorTD& rightV);

	//���� ����� ���������
	double angVect(VectorTD rightV) {
		return acos((x * rightV.x + y * rightV.y + z * rightV.z) / (length() * rightV.length()));
	}

	//������������ ��������
	double gCosX() {
		return x / length();
	}
	double gCosY() {
		return y / length();
	}
	double gCosZ() {
		return z / length();
	}

	//����, ���������� � ����� ���������
	double angX() {
		return acos(gCosX());
	}
	double angY() {
		return acos(gCosY());
	}
	double angZ() {
		return acos(gCosZ());
	}

	double getX() {
		return x;
	}
	double getY() {
		return y;
	}
	double getZ() {
		return z;
	}

	//����������
	~VectorTD() {
		x = y = z = 0;
	}
};

class VectorAd : public VectorTD {
public:
	VectorAd(double cx, double cy, double cz) {
		x = cx;
		y = cy;
		z = cz;
	}

	VectorAd() {
		x = y = z = 0;
	}

	VectorAd(const VectorAd& vec) {
		x = vec.x;
		y = vec.y;
		z = vec.z;
	}

	//��������� ������������
	double operator * (VectorAd const&  rightV) {
		return (x * rightV.x + y * rightV.y + z * rightV.z);
	}
	
	//��������� ������������
	VectorAd cross(VectorAd const& rightV){
		return VectorAd(y * rightV.z - z * rightV.y, z * rightV.x - x * rightV.z, x * rightV.y - y * rightV.x);
	}
};

//��������� ���������� � ��������

ofstream& operator<<(ofstream& fout, VectorTD vec)
{
	fout << '(' << vec.x << ", " << vec.y << ", " << vec.z << ')';
	return fout;
}

ifstream& operator>>(ifstream& fin, VectorTD& vec)
{
	fin >> vec.x >> vec.y >> vec.z;
	return fin;
}

//�������� == ��� ���� ��������
bool operator == (VectorTD leftV, VectorTD rightV) {
	return (leftV.getX() == rightV.getX() && leftV.getY() == rightV.getY() && leftV.getZ() == rightV.getZ());
}

//�������� > ��� ���� ��������
bool operator > (VectorTD leftV, VectorTD rightV) {
	return leftV.length() - rightV.length() > 0 ? 1 : 0;
}

//�������� < ��� ���� ��������
bool operator < (VectorTD leftV, VectorTD rightV) {
	return leftV.length() - rightV.length() < 0 ? 1 : 0;
}

//�������� >= ��� ���� ��������
bool operator >= (VectorTD leftV, VectorTD rightV) {
	return leftV > rightV || leftV == rightV;
}

//�������� <= ��� ���� ��������
bool operator <= (VectorTD leftV, VectorTD rightV) {
	return leftV < rightV || leftV == rightV;
}

VectorTD operator * (int a, VectorTD rightV) {
	return rightV * a;
}

VectorTD VectorTD::operator = (const VectorTD& rightV) {
	if (*this == rightV) return *this; //��������� �� ����� �� ��� ������ �����������
	x = rightV.x;
	y = rightV.y;
	z = rightV.z;
	return *this;
}

void operationVec(VectorAd a, VectorAd b, int s) {
	//��������� �������� ����� ������	
	ofstream fout("output.txt", ios_base::trunc);

	//����������� �������� � ��������� � ����������� �� �����
	if (s % 2) {
		if (a > b) fout << "��������� ������ �� ������" << endl << "����� ������ > ������ ������";
		else if (a < b) fout << "��������� ������ �� ������" << endl << "����� ������ < ������ ������";
		else if (a == b) fout << "��������� ������ �� �����������" << endl << "����� ������ == ������ ������";
		else fout << "��������� ������ �� �����������" << endl << "����� ������ != ������ ������";
	}
	else {
		fout << "������ �����: ";
		fout << a + b;
	}

	//��������� ����� ������
	fout.close();
}

void operationVec(VectorTD a, VectorTD b, int s) {
	//��������� �������� ����� ������	
	ofstream fout("output.txt", ios_base::trunc);

	//����������� �������� � ��������� � ����������� �� �����
	if (s % 2) {
		if (a > b) fout << "��������� ������ �� ������" << endl << "����� ������ > ������ ������";
		else if (a < b) fout << "��������� ������ �� ������" << endl << "����� ������ < ������ ������";
		else if (a == b) fout << "��������� ������ �� �����������" << endl << "����� ������ == ������ ������";
		else fout << "��������� ������ �� �����������" << endl << "����� ������ != ������ ������";
	}
	else {
		fout << "������ �����: ";
		fout << a + b;
	}

	//��������� ����� ������
	fout.close();
}

int main() {
	setlocale(LC_ALL, "Russian");

	//��������� �������� ����� ����� 
	ifstream fin("input.txt");

	int s; //����
	fin >> s;

	//���������� � ��������� ������ ������ ����� ��������
	if (s < 2) {
		VectorTD a, b;
		fin >> a >> b;
		operationVec(a, b, s);
	}
	else {
		VectorAd a, b;
		fin >> a >> b;
		operationVec(a, b, s);
	}

	//��������� ����� �����
	fin.close();

	return 0;
}
