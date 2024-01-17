#include <iostream>
using namespace std;

struct list {
	int value;
	list* next;
};

void pushBack(list*& head, int value) {
	list* newEl = new list;
	if (!head) {
		newEl->next = 0;
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
		newEl->value = value;
	}
}

void pushFront(list*& head, int value) {
	list* newEl = new list;
	newEl->value = value;
	newEl->next = head;
	head = newEl;
}

void popBack(list*& head) {
	if (!head) {
		cerr << "Список пуст для удаления" << endl;
		return;
	}
	else {
		int v;
		if (!head->next) {
			v = head->value;
			delete head;
		}
		else {
			list* buf = head;
			while (buf->next->next) {
				buf = buf->next;
			}
			v = buf->next->value;
			buf->next = 0;
			delete buf->next;
		}

		cout << "Удален элемент со значением: " << v << endl;
	}
}

void popFront(list*& head) {
	if (!head) {
		cerr << "Список пуст для удаления" << endl;
		return;
	}

	list* buf = head;
	head = head->next;
	cout << "Удален элемент со значением: " << buf->value << endl;
	delete buf;
}

void erase(list*& head) {
	do {
		popFront(head);
	} while (head);
}

void print(list* head) {
	if (!head) {
		cerr << "Список пуст" << endl;
		return;
	}

	int i = 0;
	do {
		cout << ++i << " - " << head->value << endl;
	} while (head = head->next);
}

list* copy(list* head) {
	if (!head) return 0;
	else {
		list* cop = 0;
		while (head) {
			pushBack(cop, head->value);
			head = head->next;
		}
		return cop;
	}
}

int main() {
	setlocale(LC_ALL, "Rus");

	list* pList = 0;

	pushBack(pList, 12);
	pushFront(pList, 0);
	pushFront(pList, 1);
	pushBack(pList, 111);
	pushFront(pList, 34);

	list* pListCopy = copy(pList);

	print(pListCopy);

	erase(pList);
	erase(pListCopy);
	delete pList;
	delete pListCopy;

	return 0;
}