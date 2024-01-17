#include <fstream>
using namespace std;

int sum(int a, int b) {
	return a + b;
}

int main()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt", ios_base::trunc);

	int a, b;

	fin >> a >> b;
	fout << a | b;

	fin.close();
	fout.close();

	return 0;
}

/*void init() {
	cin.clear();// убираем флаги ошибок и возвращаем cin в нормальный режим работы
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Incorrect input" << endl;
}

void setVals(int &a, int &b) {
	bool flag = true;
	int val = 0;
	while (flag)
	{
		cin >> a >> b;

		if (cin.fail())
		{
			init();
		}
		else
		{
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			if (cin.gcount() <= 1)
			{
				flag = false;
			}
			else
			{
				cout << "Extra characters" << endl;
			}
		}
	}
	return;
}*/