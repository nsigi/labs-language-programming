#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
using namespace std;

class VectorTD {
protected:
	int x, y, z; //координаты вектора
	double length; //длина вектора

	//модуль вектора (длина)
	double Length() {
		return sqrt(x * x + y * y + z * z);
	}

public:
	//конструктор инициализации 
	VectorTD(int cx, int cy, int cz) {
		x = cx;
		y = cy;
		z = cz;
		length = Length();
	}

	//конструктор по умолчанию
	VectorTD() {
		length = x = y = z = 0;
	}
	
	double getLen() {
		return length;
	}

	//деструктор
	~VectorTD() {
		length = x = y = z = 0;
	}
};

struct list {
	VectorTD vec;
	list* next;
	list* prev;
};

//перегруза операций сравнения

//операция < для двух векторов
bool operator < (VectorTD leftV, VectorTD rightV) {
	return leftV.getLen() < rightV.getLen();
}
//операция > для двух векторов
bool operator > (VectorTD leftV, VectorTD rightV) {
	return  rightV.getLen() < leftV.getLen();
}

//добавления элемента в конец списка
void pushBack(list*& head, VectorTD vect) {
	list* newEl = new list;
	newEl->vec = vect;
	if (!head) {
		newEl->next = newEl->prev = 0;
		head = newEl;
	}
	else {
		list* buf = head;
		while (buf->next) {
			buf = buf->next;
		}
		buf->next = newEl;
		newEl->next = 0;
		newEl->prev = buf;
	}
}

//создание вектора со случайными параметрами
VectorTD createVect() {
	return VectorTD(rand() % 100, rand() % 100, rand() % 100);
}

//обмен указателями элементов списка для сортировки
void swap(list*& head, list*& right) {
	list* curH = head;

	if (curH->prev) curH->prev->next = right;
	if (right->next) right->next->prev = curH;

	if (curH->next != right) {
		curH->next->prev = right;
		right->prev->next = curH;

		list* buf = curH->next;
		curH->next = right->next;
		right->next = buf;

		buf = curH->prev;
		curH->prev = right->prev;
		right->prev = buf;
	}
	else {
		list* buf = curH;
		curH->next = right->next;
		right->next = curH;

		right->prev = buf->prev;
		curH->prev = right;
	}
	head = right;
}

//сортировка выбором
void selectionSort(list*& head) {
	if (!head) {
		cerr << "Список пуст" << endl;
		return;
	}

	list* min, * buf;
	min = head;
	//цикл, в котором определяется текущее положение и вставляется на его место минимальный элемент(начинаем проход списка с начала)
	while (head->next) {
		buf = head->next;
		//нахождение минимального элемента из неотсортированной части списка
		while (buf) {
			if ((buf->vec) < (min->vec))
				min = buf;
			buf = buf->next;
		}

		//меняем местами минимальный элемент с текущим элементом, если текущий элемент не является минимальным
		if (min != head)
			swap(head, min);
		min = head = head->next;
	}

	//возвращаем голову обратно, чтобы она вновь указывала на первый элемент списка
	while (head->prev)
		head = head->prev;
}

//очищение памяти, выделенной для списка
void erase(list*& head) {
	if (!head) {
		cerr << "Список пуст для удаления" << endl;
		return;
	}

	do {
		list* buf = head;
		head = head->next;
		delete buf;
	} while (head);
}

//функция, которая проверяет факт упорядоченности структуры
bool checkSort(list* p) {
	if (p) {
		list* nextV = p->next;
		while (nextV) {
			if (p->vec > nextV->vec)
				return 0;
			p = p->next;
			nextV = nextV->next;
		}
		return 1;
	}
	else cerr << "Список пуст" << endl;

	return 0;
}

int main() {
	setlocale(LC_ALL, "Russian");

	srand(time(0)); //используем функцию, чтобы обновлять зерно псевдослучайных последовательностей

	//открываем файловый поток ввода
	ifstream fin("input.txt");
	int n, count;
	fin >> n;
	count = n;
	//закрываем поток ввода
	fin.close();

	list* pList = 0;
	//заполнение списка векторами
	while (n--) pushBack(pList, createVect());

	selectionSort(pList);

	checkSort(pList) ? cout << "Структура упорядочена правильно" : cout << "Структура упорядочена неправильно";
	
	erase(pList);

	//открываем файловый поток вывода	
	ofstream fout("output.txt", ios_base::trunc);
	fout << count;
	//закрываем файловый поток вывода	
	fout.close();

	return 0;
}
