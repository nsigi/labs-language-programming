#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
using namespace std;

class VectorTD {
protected:
	int x, y, z; //���������� �������
	double length; //����� �������

	//������ ������� (�����)
	double Length() {
		return sqrt(x * x + y * y + z * z);
	}

public:
	//����������� ������������� 
	VectorTD(int cx, int cy, int cz) {
		x = cx;
		y = cy;
		z = cz;
		length = Length();
	}

	//����������� �� ���������
	VectorTD() {
		length = x = y = z = 0;
	}
	
	double getLen() {
		return length;
	}

	//����������
	~VectorTD() {
		length = x = y = z = 0;
	}
};

struct list {
	VectorTD vec;
	list* next;
	list* prev;
};

//��������� �������� ���������

//�������� < ��� ���� ��������
bool operator < (VectorTD leftV, VectorTD rightV) {
	return leftV.getLen() < rightV.getLen();
}
//�������� > ��� ���� ��������
bool operator > (VectorTD leftV, VectorTD rightV) {
	return  rightV.getLen() < leftV.getLen();
}

//���������� �������� � ����� ������
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

//�������� ������� �� ���������� �����������
VectorTD createVect() {
	return VectorTD(rand() % 100, rand() % 100, rand() % 100);
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

//���������� �������
void selectionSort(list*& head) {
	if (!head) {
		cerr << "������ ����" << endl;
		return;
	}

	list* min, * buf;
	min = head;
	//����, � ������� ������������ ������� ��������� � ����������� �� ��� ����� ����������� �������(�������� ������ ������ � ������)
	while (head->next) {
		buf = head->next;
		//���������� ������������ �������� �� ����������������� ����� ������
		while (buf) {
			if ((buf->vec) < (min->vec))
				min = buf;
			buf = buf->next;
		}

		//������ ������� ����������� ������� � ������� ���������, ���� ������� ������� �� �������� �����������
		if (min != head)
			swap(head, min);
		min = head = head->next;
	}

	//���������� ������ �������, ����� ��� ����� ��������� �� ������ ������� ������
	while (head->prev)
		head = head->prev;
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

//�������, ������� ��������� ���� ��������������� ���������
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
	else cerr << "������ ����" << endl;

	return 0;
}

int main() {
	setlocale(LC_ALL, "Russian");

	srand(time(0)); //���������� �������, ����� ��������� ����� ��������������� �������������������

	//��������� �������� ����� �����
	ifstream fin("input.txt");
	int n, count;
	fin >> n;
	count = n;
	//��������� ����� �����
	fin.close();

	list* pList = 0;
	//���������� ������ ���������
	while (n--) pushBack(pList, createVect());

	selectionSort(pList);

	checkSort(pList) ? cout << "��������� ����������� ���������" : cout << "��������� ����������� �����������";
	
	erase(pList);

	//��������� �������� ����� ������	
	ofstream fout("output.txt", ios_base::trunc);
	fout << count;
	//��������� �������� ����� ������	
	fout.close();

	return 0;
}
