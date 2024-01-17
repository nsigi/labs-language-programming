#include <iostream>
#include <fstream>
#include <set>
using namespace std;

struct Tree {
	int value;
	Tree* parent; //родитель
	Tree* left;	  //левый ребенок
	Tree* right;  //правый ребенок
};

void push(Tree*& root, int val);

//выделение памяти для элемента дерева и инициализация
void addEl(Tree*& t, int val) {
	if (t) push(t, val);
	else {
		t = new Tree;
		t->value = val;
		t->right = t->left = 0;
	}
}

//вставка элемента в дерево в соответствии с условием: влево - если меньше или равно, вправо - если больше
void push(Tree*& root, int val) {
	if (val > root->value) {
		addEl(root->right, val);
		root->right->parent = root;
	}
	else {
		addEl(root->left, val);
		root->left->parent = root;
	}
}

//поиск элемента с определенным значением с определенным корневым узлом какого-либо поддерева
Tree* findEl(Tree*& root, int val) {
	if (root->value > val && root->left) return findEl(root->left, val); 
	else if(root->value < val && root->right) return findEl(root->right, val); 
	else return root;
}

//удаление определенного элемента
void deleteEl(Tree*& t) {
	if (!t) return;

	if (t->left && t->right) {            //случай, когда у удаляемого элемента есть оба дочерних элемента (два поддерева)
		Tree* max = t;
		while (max->right)	max = max->right; //поиск макимального элемента (самого правого) относительно корневого узла
		t->value = max->value; //записываем значение максимального элемента вместо нашего удаляемого
		deleteEl(max);
		return;
	}
	else if (t->left) {                   //случай, когда у удаляемого элемента есть только левое поддерево
		if (t->parent->left == t) t->parent->left = t->left;
		else t->parent->right = t->left;
		t->left->parent = t->parent;
	}
	else if (t->right) {                  //случай, когда у удаляемого элемента есть только правое поддерево
		if (t->parent->right == t) t->parent->right = t->right;
		else t->parent->left = t->right;
		t->right->parent = t->parent;
	}
	else {                                //случай, когда у удаляемый элемент - лист
		if (t->parent->left == t) t->parent->left = 0;
		else t->parent->right = 0;
	}

	delete t;
}

void deleteReps(Tree*& root, multiset<int>& repeats) {
	if (!root) return;

	Tree* nRoot; //переменная, которая будет хранить корневые узлы текущих поддеревьев
	multiset <int> ::iterator it = repeats.begin();//создаю иттератор для своего мультимножества, чтобы обращаться к определенным элементам
	while (it != repeats.end()) {
		nRoot = findEl(findEl(root, *it)->left, *it); //нахожу первый элемент, который повторяется в дереве. Буду удалять его копию,
		deleteEl(nRoot);                              //которая находится в левом поддереве относительно него. 
		++it;
	}
}

//очищение дерева обратным обходом
void erase(Tree*& root) {
	if (root->left) erase(root->left);
	if (root->right) erase(root->right);
	delete root;
}

//чтения элементов дерева из файла
void input(Tree*& root, multiset <int>& repeats) {
	//открываем файловый поток ввода
	ifstream fIn("input.txt");

	if (fIn) {
		multiset <int> originals;     //мультимножество неповторяющихся элементов
		root = new Tree;              //создаем корень дерева
		root->left = root->right = 0;

		int a;
		fIn >> a;
		root->value = a;
		root->parent = 0;
		originals.insert(a);

		//считываем значения из файла и вставляем их в дерево поиска, одновременно проверяя, повторяется ли значение
		while (fIn >> a) {
			push(root, a);
			if (originals.find(a) == originals.end()) originals.insert(a);
			else repeats.insert(a);
		}

		//закрываем поток ввода
		fIn.close();
	}
	else cerr << "Ошибка чтения файла";
}

// запись дерева в файл с помощью обратного обхода
void output(ofstream& fOut, Tree*& root)
{
	//схема обхода ЛПК «левый – правый – корень»
	if (root->left) output(fOut, root->left); 
	if (root->right) output(fOut, root->right);
	fOut << root->value << " ";
}

int main() {
	setlocale(LC_ALL, "Rus");

	//мультимножество всех повторяющихся элементов
	multiset <int> repeats;

	Tree* root; //указатель на корень дерева
	input(root, repeats);
	
	//удаление повторов
	deleteReps(root, repeats); 

	//открываем файловый поток вывода
	ofstream fOut("output.txt", ios_base::trunc);

	output(fOut, root);

	//закрываем поток вывода
	fOut.close();

	erase(root);

	return 0;
}