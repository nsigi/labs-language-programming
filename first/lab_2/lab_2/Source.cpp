#include <iostream>
#include <fstream>
using namespace std;

struct list {
	int value;
	list* next;
	list* prev;
};

//���������� �������� � ����� ������
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

//�������� ������, ���������� ��� ������
void erase(list*& head) {
	if (!head) {
		cerr << "������ ���� ��� ��������" << endl;
		return;
	}

	do {
		list* buf = head;
		head = head->next;
		delete buf;
	} while (head);
}

//������ ������ �� �����
list* input(int& size, bool& m) {
	list* head = 0;
	size = 0;
	int n;
	//��������� �������� ����� �����
	ifstream fIn("input.txt");

	fIn >> m;

	while (fIn >> n) {
		pushBack(head, n);
		++size;
	}
	//��������� ����� �����
	fIn.close();

	return head;
}

//������ ���������������� ������ � ����
void output(list* head, int size) {
	if (!head) {
		cerr << "������ ����" << endl;
		return;
	}

	//��������� �������� ����� ������
	ofstream fOut("output.txt", ios_base::trunc);
	fOut << size;//������� ������ �������
	while (head) {
		fOut << ' ' << head->value;
		head = head->next;
	}

	//��������� ����� ������
	fOut.close();
}

//����� ����������� ��������� ������ ��� ����������
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
		cerr << "������ ����" << endl;
		return;
	}

	list* min, * buf;
	//����, � ������� ������������ ������� ��������� � ����������� �� ��� ����� ����������� (�������� ������ ������ � ������)
	for (int i = 0; i ^ (size - 1); ++i, head = head->next) {
		min = head;
		buf = head->next;
		//���������� ������������ �������� �� ����������������� ����� ������
		for (int j = i + 1; j ^ size; ++j, buf = buf->next)
			if ((buf->value) < (min->value))
				min = buf;
		//������ ������� ����������� ������� � ������� ���������, ���� ������� ������� �� �������� �����������
		if (min->value ^ head->value)
			swap(head, min);
	}

	//���������� ������ �������, ����� ��� ����� ��������� �� ������ ������� ������
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

//������� �������������� ������ (����������� ���������)
void heap(list**& a, int n, int i)
{
	//������� ������� ���� - ������������ ���������
	int max = i;
	int chLeft, chRight;

	while (1) {
		chLeft = 2 * i + 1; //����� �������� �������
		chRight = chLeft + 1; //������ �������� �������

		if (chLeft < n && a[chLeft]->value > a[max]->value)
			max = chLeft;

		if (chRight < n && a[chRight]->value > a[max]->value)
			max = chRight;

		//������ ���������� ������� �� ����� ����, ���� ���� �� ���������� �� 3-�
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
	//���������� ������ 
	for (i = size / 2; i > -1; --i)
		heap(a, size, i);

	//���������� ������ ��������� ���������� � �����
	for (i = size - 1; i ^ 0; --i)
	{
		// ���������� ������� ������ � ����� ������
		swap2(a[0], a[i]);
		//����������� ������ (��������� ��� �� ���� � ������ �� ����� ����� ������������ ��������� ����������)
		heap(a, i, 0);
	}
	//��������� ��������������� ������
	head = copy(a, size);
}

int main() {
	setlocale(LC_ALL, "Rus");

	int size = 0;
	bool m;

	list* pList = input(size, m);

	//�������� ���������� ��������������� ������� ������������
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
