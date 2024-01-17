#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

class VectorTD {
protected:
	double x, y, z; //координаты вектора
public:
	//конструктор инициализации 
	VectorTD(double cx, double cy, double cz) : x(cx), y(cy), z(cz) {};

	//конструктор по умолчанию
	VectorTD() {
		x = y = z = 0;
	}

	//конструктор копирования
	VectorTD(const VectorTD& vec) {
		x = vec.x;
		y = vec.y;
		z = vec.z;
	}

	//модуль вектора (длина)
	double length() {
		return sqrt(x * x + y * y + z * z);
	}

	//перегруженные операторы ввода и вывода
	friend ofstream& operator<<(ofstream& fout, VectorTD vec);
	friend ifstream& operator>>(ifstream& fin, VectorTD& vec);

	//перегруженные арифметические операции
	//сложение
	const VectorTD operator + (VectorTD const& rightV) {
		return VectorTD(x + rightV.x, y + rightV.y, z + rightV.z);
	}
	//вычитание
	const VectorTD operator - (VectorTD const& rightV) {
		return VectorTD(x - rightV.x, y - rightV.y, z - rightV.z);
	}
	//умножение вектора на число
	VectorTD operator * (int a) {
		return VectorTD(x * a, y * a, z * a);
	}
	friend VectorTD operator * (int a, VectorTD rightV);

	//деление вектора на число отличное от нуля (иначе вектор не изменяется)
	VectorTD operator / (double a) {
		if (!a)	cerr << "На ноль делить нельзя";
		else return VectorTD(x / a, y / a, z / a);
		return *this;
	}

	//перегруженный оператор присваивания
	VectorTD operator = (const VectorTD& rightV);

	//угол между векторами
	double angVect(VectorTD rightV) {
		return acos((x * rightV.x + y * rightV.y + z * rightV.z) / (length() * rightV.length()));
	}

	//направляющие косинусы
	double gCosX() {
		return x / length();
	}
	double gCosY() {
		return y / length();
	}
	double gCosZ() {
		return z / length();
	}

	//углы, образуемые с осями координат
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

	//деструктор
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

	//скалярное произведение
	double operator * (VectorAd const&  rightV) {
		return (x * rightV.x + y * rightV.y + z * rightV.z);
	}
	
	//векторное произведение
	VectorAd cross(VectorAd const& rightV){
		return VectorAd(y * rightV.z - z * rightV.y, z * rightV.x - x * rightV.z, x * rightV.y - y * rightV.x);
	}
};

//перегруза операторов и операций

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

//операция == для двух векторов
bool operator == (VectorTD leftV, VectorTD rightV) {
	return (leftV.getX() == rightV.getX() && leftV.getY() == rightV.getY() && leftV.getZ() == rightV.getZ());
}

//операция > для двух векторов
bool operator > (VectorTD leftV, VectorTD rightV) {
	return leftV.length() - rightV.length() > 0 ? 1 : 0;
}

//операция < для двух векторов
bool operator < (VectorTD leftV, VectorTD rightV) {
	return leftV.length() - rightV.length() < 0 ? 1 : 0;
}

//операция >= для двух векторов
bool operator >= (VectorTD leftV, VectorTD rightV) {
	return leftV > rightV || leftV == rightV;
}

//операция <= для двух векторов
bool operator <= (VectorTD leftV, VectorTD rightV) {
	return leftV < rightV || leftV == rightV;
}

VectorTD operator * (int a, VectorTD rightV) {
	return rightV * a;
}

VectorTD VectorTD::operator = (const VectorTD& rightV) {
	if (*this == rightV) return *this; //проверяем не равен ли наш объект присваемому
	x = rightV.x;
	y = rightV.y;
	z = rightV.z;
	return *this;
}

void operationVec(VectorAd a, VectorAd b, int s) {
	//открываем файловый поток вывода	
	ofstream fout("output.txt", ios_base::trunc);

	//определение действий с векторами в зависимости от ключа
	if (s % 2) {
		if (a > b) fout << "Сравнение ведётся по модулю" << endl << "Левый вектор > правый вектор";
		else if (a < b) fout << "Сравнение ведётся по модулю" << endl << "Левый вектор < правый вектор";
		else if (a == b) fout << "Сравнение ведётся по координатам" << endl << "Левый вектор == правый вектор";
		else fout << "Сравнение ведётся по координатам" << endl << "Левый вектор != правый вектор";
	}
	else {
		fout << "Вектор суммы: ";
		fout << a + b;
	}

	//закрываем поток вывода
	fout.close();
}

void operationVec(VectorTD a, VectorTD b, int s) {
	//открываем файловый поток вывода	
	ofstream fout("output.txt", ios_base::trunc);

	//определение действий с векторами в зависимости от ключа
	if (s % 2) {
		if (a > b) fout << "Сравнение ведётся по модулю" << endl << "Левый вектор > правый вектор";
		else if (a < b) fout << "Сравнение ведётся по модулю" << endl << "Левый вектор < правый вектор";
		else if (a == b) fout << "Сравнение ведётся по координатам" << endl << "Левый вектор == правый вектор";
		else fout << "Сравнение ведётся по координатам" << endl << "Левый вектор != правый вектор";
	}
	else {
		fout << "Вектор суммы: ";
		fout << a + b;
	}

	//закрываем поток вывода
	fout.close();
}

int main() {
	setlocale(LC_ALL, "Russian");

	//открываем файловый поток ввода 
	ifstream fin("input.txt");

	int s; //ключ
	fin >> s;

	//определяем с объектами какого класса будем работать
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

	//закрываем поток ввода
	fin.close();

	return 0;
}
