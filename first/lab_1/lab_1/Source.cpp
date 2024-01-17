#include <fstream>
#include <cmath>
using namespace std;

double sum(double *arr, double p, int n) {//функция для подсчета суммы
	double sum = 0;

	for (int i = 0; i ^ n; ++i) 
		if ((arr[i] > 0) && (arr[i] >= p))//проверка элемента массива
			sum += pow(arr[i], 3);

	return sum;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	//открываем файловые потоки для чтения и записи
	ifstream fin("input.txt");
	ofstream fout("output.txt", ios_base::trunc);

	if (fin.is_open() && fout.is_open() && !fin.eof()) {//проверяем файл на открытие
		double p;
		int n = -1;//заводим переменную для подсчёта количества элементов массива
		//устанавливаем длину входного массива
		while (!fin.eof()) {
			fin >> p;
			if (!fin.fail())
				++n;
		}

		//fin.clear();//очищаем состояние потока
		fin.seekg(0, ios_base::beg);//beg - смещение относительно начала файла на величину первого параметра

		double* arr = new double[n];//выделяем память под массив размера n
		fin >> p;//считываем параметр

		for (int i = 0; i ^ n; ++i) {
			fin >> arr[i];//считываем элементы массива 
		}

		fout << sum(arr, p, n);

		delete[]arr;//освобождаем выделенную память под наш массив
	}

	//закрываем файловые потоки
	fin.close();
	fout.close();

	return 0;
}