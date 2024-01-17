#include <iostream>
#include <fstream>
#include <set>
using namespace std;

struct Tree {
	int value;
	Tree* parent; //��������
	Tree* left;	  //����� �������
	Tree* right;  //������ �������
};

void push(Tree*& root, int val);

//��������� ������ ��� �������� ������ � �������������
void addEl(Tree*& t, int val) {
	if (t) push(t, val);
	else {
		t = new Tree;
		t->value = val;
		t->right = t->left = 0;
	}
}

//������� �������� � ������ � ������������ � ��������: ����� - ���� ������ ��� �����, ������ - ���� ������
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

//����� �������� � ������������ ��������� � ������������ �������� ����� ������-���� ���������
Tree* findEl(Tree*& root, int val) {
	if (root->value > val && root->left) return findEl(root->left, val); 
	else if(root->value < val && root->right) return findEl(root->right, val); 
	else return root;
}

//�������� ������������� ��������
void deleteEl(Tree*& t) {
	if (!t) return;

	if (t->left && t->right) {            //������, ����� � ���������� �������� ���� ��� �������� �������� (��� ���������)
		Tree* max = t;
		while (max->right)	max = max->right; //����� ������������ �������� (������ �������) ������������ ��������� ����
		t->value = max->value; //���������� �������� ������������� �������� ������ ������ ����������
		deleteEl(max);
		return;
	}
	else if (t->left) {                   //������, ����� � ���������� �������� ���� ������ ����� ���������
		if (t->parent->left == t) t->parent->left = t->left;
		else t->parent->right = t->left;
		t->left->parent = t->parent;
	}
	else if (t->right) {                  //������, ����� � ���������� �������� ���� ������ ������ ���������
		if (t->parent->right == t) t->parent->right = t->right;
		else t->parent->left = t->right;
		t->right->parent = t->parent;
	}
	else {                                //������, ����� � ��������� ������� - ����
		if (t->parent->left == t) t->parent->left = 0;
		else t->parent->right = 0;
	}

	delete t;
}

void deleteReps(Tree*& root, multiset<int>& repeats) {
	if (!root) return;

	Tree* nRoot; //����������, ������� ����� ������� �������� ���� ������� �����������
	multiset <int> ::iterator it = repeats.begin();//������ ��������� ��� ������ ���������������, ����� ���������� � ������������ ���������
	while (it != repeats.end()) {
		nRoot = findEl(findEl(root, *it)->left, *it); //������ ������ �������, ������� ����������� � ������. ���� ������� ��� �����,
		deleteEl(nRoot);                              //������� ��������� � ����� ��������� ������������ ����. 
		++it;
	}
}

//�������� ������ �������� �������
void erase(Tree*& root) {
	if (root->left) erase(root->left);
	if (root->right) erase(root->right);
	delete root;
}

//������ ��������� ������ �� �����
void input(Tree*& root, multiset <int>& repeats) {
	//��������� �������� ����� �����
	ifstream fIn("input.txt");

	if (fIn) {
		multiset <int> originals;     //��������������� ��������������� ���������
		root = new Tree;              //������� ������ ������
		root->left = root->right = 0;

		int a;
		fIn >> a;
		root->value = a;
		root->parent = 0;
		originals.insert(a);

		//��������� �������� �� ����� � ��������� �� � ������ ������, ������������ ��������, ����������� �� ��������
		while (fIn >> a) {
			push(root, a);
			if (originals.find(a) == originals.end()) originals.insert(a);
			else repeats.insert(a);
		}

		//��������� ����� �����
		fIn.close();
	}
	else cerr << "������ ������ �����";
}

// ������ ������ � ���� � ������� ��������� ������
void output(ofstream& fOut, Tree*& root)
{
	//����� ������ ��� ������ � ������ � �������
	if (root->left) output(fOut, root->left); 
	if (root->right) output(fOut, root->right);
	fOut << root->value << " ";
}

int main() {
	setlocale(LC_ALL, "Rus");

	//��������������� ���� ������������� ���������
	multiset <int> repeats;

	Tree* root; //��������� �� ������ ������
	input(root, repeats);
	
	//�������� ��������
	deleteReps(root, repeats); 

	//��������� �������� ����� ������
	ofstream fOut("output.txt", ios_base::trunc);

	output(fOut, root);

	//��������� ����� ������
	fOut.close();

	erase(root);

	return 0;
}