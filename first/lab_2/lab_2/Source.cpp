#include <iostream>
#include <fstream>
using namespace std;

struct list {
	int value;
	list* next;
	list* prev;
};

//добавления элемента в конец списка
void pushBack(list*& head, int value) {
	list* newEl = new list;
	if (!head) {
		newEl->next = newEl->prev = 0;
		newEl->value = value;
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
		newEl->value = value;
	}
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

//чтения списка из файла
list* input(int& size, bool& m) {
	list* head = 0;
	size = 0;
	int n;
	//открываем файловый поток ввода
	ifstream fIn("input.txt");

	fIn >> m;

	while (fIn >> n) {
		pushBack(head, n);
		++size;
	}
	//закрываем поток ввода
	fIn.close();

	return head;
}

//запись отсортированного списка в файл
void output(list* head, int size) {
	if (!head) {
		cerr << "Список пуст" << endl;
		return;
	}

	//открываем файловый поток вывода
	ofstream fOut("output.txt", ios_base::trunc);
	fOut << size;//выводим размер массива
	while (head) {
		fOut << ' ' << head->value;
		head = head->next;
	}

	//закрываем поток вывода
	fOut.close();
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

void selectionSort(list*& head, int size) {
	if (!head) {
		cerr << "Список пуст" << endl;
		return;
	}

	list* min, * buf;
	//цикл, в котором определяется текущее положение и вставляется на его место минимальный (начинаем проход списка с начала)
	for (int i = 0; i ^ (size - 1); ++i, head = head->next) {
		min = head;
		buf = head->next;
		//нахождение минимального элемента из неотсортированной части списка
		for (int j = i + 1; j ^ size; ++j, buf = buf->next)
			if ((buf->value) < (min->value))
				min = buf;
		//меняем местами минимальный элемент с текущим элементом, если текущий элемент не является минимальным
		if (min->value ^ head->value)
			swap(head, min);
	}

	//возвращаем голову обратно, чтобы она вновь указывала на первый элемент списка
	while (head->prev)
		head = head->prev;
}

list* copy(list** a, int size) {
	a[0]->prev = 0;
	a[0]->next = a[1];
	for (int i = 1; i ^ (size - 1); ++i) {
		a[i]->prev = a[i - 1];
		a[i]->next = a[i + 1];
	}
	a[size - 1]->prev = a[size - 2];
	a[size - 1]->next = 0;

	return a[0];
}

void swap2(list*& l, list*& r) {
	list* p = l;
	l = r;
	r = p;
}

//функция редактирование дерева (просеивание элементов)
void heap(list**& a, int n, int i)
{
	//считаем текущий узел - максимальным элементом
	int max = i;
	int chLeft, chRight;

	while (1) {
		chLeft = 2 * i + 1; //левый дочерний элемент
		chRight = chLeft + 1; //правый дочерний элемент

		if (chLeft < n && a[chLeft]->value > a[max]->value)
			max = chLeft;

		if (chRight < n && a[chRight]->value > a[max]->value)
			max = chRight;

		//ставим наибольший элемент на место ущла, если узел не наибольший из 3-х
		if (max != i) {

			swap2(a[i], a[max]);

			i = max;
		}
		else break;
	}
}

void heapSort(list**& a, list*& head, int size) {
	list* buf = head;
	int i;

	for (i = 0; i ^ size; buf = buf->next, ++i)	a[i] = buf;
	//построение дерева 
	for (i = size / 2; i > -1; --i)
		heap(a, size, i);

	//сортироуем массив перемещая наибольший в конец
	for (i = size - 1; i ^ 0; --i)
	{
		// перемещаем текущий корень в конец дерева
		swap2(a[0], a[i]);
		//редактируем дерево (уменьшаем его на один и ставим на место корня максимальный элементиз оставшихся)
		heap(a, i, 0);
	}
	//сохраняем отсортированный список
	head = copy(a, size);
}

int main() {
	setlocale(LC_ALL, "Rus");

	int size = 0;
	bool m;

	list* pList = input(size, m);

	//выбираем сортировку соответствующую запросу пользователя
	if (m)	selectionSort(pList, size);
	else {
		list** a = new list * [size];
		heapSort(a, pList, size);
		delete[] a;
	}

	output(pList, size);

	erase(pList);

	return 0;
}
