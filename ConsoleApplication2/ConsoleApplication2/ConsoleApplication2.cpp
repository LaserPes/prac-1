// C2) Вывести на экран двоичное представление в памяти (все разряды) целого числа. При выводе необходимо визуально обозначить знаковый разряд и значащие разряды отступами или цветом.
//

#include <iostream>
#include <windows.h.>
#include <conio.h>
using namespace std;
HANDLE textColour = GetStdHandle(STD_OUTPUT_HANDLE);
string strochka;
union
{
	float f;
	int a;
} fu;
#undef min
#undef max
double getDouble() {
	cout << endl << "Введите число от " << numeric_limits<double>::min() << " до " << numeric_limits<double>::max() << ": ";
	while (true) {
		double userNumber;
		cin >> userNumber;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << endl << "Попробуйте ввести корректное число (от " << numeric_limits<double>::min() << " до " << numeric_limits<double>::max() << "): ";
		}
		else {
			cin.ignore(cin.rdbuf()->in_avail());
			return userNumber;
		}
	}
}
void output(char type, bool* A)
{
	cout << endl;
	for (int i = 0; i < 64; ++i)
	{
		if (i == 1) {
			cout << " ";
			SetConsoleTextAttribute(textColour, 5);
		}
		if (i == 12) {
			cout << " ";
			SetConsoleTextAttribute(textColour, 10);
		}
		if (i % 8 == 0 && i != 8 && i != 0)
			cout << " ";
		cout << A[i];
	}
	SetConsoleTextAttribute(textColour, 7);
	cout << endl << endl;
}
void doubleArray(double number, bool* A, int position)
{
	union newType
	{
		double firstPart;
		char secondPart[sizeof(firstPart)];
	} unionedDouble;
	unionedDouble.firstPart = number;
	unsigned char digit;
	for (int i = sizeof(unionedDouble) - 1; i >= 0; --i)
	{
		digit = unionedDouble.secondPart[i];
		for (int j = 0; j < 8; ++j)
		{
			digit& (128 >> j) ? A[position - 64] = 1 : A[position - 64] = 0;
			position++;
		}
	}
}
int main()
{

	
	char option = 'D';
	bool* digits = 0;
	int len;
	int znak;
s:
	system("cls");
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	int i;
	setlocale(0, "");
	int Type;
	std::cout << "Размеры " << "\n int: " << sizeof(int) << "\n short int: " << sizeof(short int)
		<< "\n long int: " << sizeof(long int) << "\n float: " << sizeof(float) << "\n double: " << sizeof(double) << "\n long double: " << sizeof(long double)
		<< "\n char: " << sizeof(char) << "\n bool: " << sizeof(bool) << "\n";
	cout << "введите цифру от 1 до 3(включительно),где:\n 1-int\n 2-float\n 3-double\n";
	cout << "ALT + F4-для выхода\n";
	cin >> Type;
	if (cin.fail())
	{
		cout << "введите число цифрами на NumPad\n";
		cout << "--------------------------------------------------------\n\n";
		cin.clear();
		cin.ignore(32767, '\n');
		system("pause"); goto s;
	}
	switch (Type)
	{
		double a;
	case 1: //int
		int a1;
		cout << "введите число:\n";
		cin >> a;
		if (cin.fail())
		{
			cout << "введите число цифрами на NumPad\n";
			cout << "--------------------------------------------------------\n\n";
			cin.clear();
			cin.ignore(32767, '\n');
			system("pause"); goto s;
		}
		else
		{
			if (a >= -signed(2147483648) && a <= 2147483647 && a == int(a))//проверка инта
			{
				a1 = int(a);
				i = 32;
				bool r1;
				r1 = a1 & (1U << --i);
				SetConsoleTextAttribute(h, 05);
				cout << r1 << " ";
				if (r1)
				{
					znak = 1;//отриц
				}
				else
				{
					znak = 0;//положит
				}
				for (--i; i >= 0; --i)
				{
					r1 = a1 & (1U << i);
					if (i % 4 == 0)
					{
						SetConsoleTextAttribute(h, 02);
						cout << r1 << " ";
					}
					else
					{
						SetConsoleTextAttribute(h, 02);
						cout << r1;
					}
				}
			}
			else
			{
				cout << "недопустимое значение для этого типа данных\n";
				system("pause"); goto s;
			}
			cout << " \n";
			break;
		}
	case 2: //float
		cout << "введите число:\n";
		cin >> fu.f;
		if (cin.fail())
		{
			cout << "введите число цифрами на NumPad\n";
			cout << "--------------------------------------------------------\n\n";
			cin.clear();
			cin.ignore(32767, '\n');
			system("pause"); goto s;
		}
		else
		{
			i = 32;
			bool r4;
			SetConsoleTextAttribute(h, 05);
			r4 = fu.a & (1U << --i);
			cout << r4 << " ";
			if (r4)
			{
				znak = 1;//отриц
			}
			else
			{
				znak = 0;//положит
			}
			SetConsoleTextAttribute(h, 04);
			for (--i; i >= 0; --i)
			{
				r4 = fu.a & (1U << i);
				cout << r4;
				if (i == 23)
				{
					SetConsoleTextAttribute(h, 02);
				}
			}
			len = 32;
			cout << " \n";
			break;
		}
	case 3: //double
		double numberD;
		numberD = getDouble();
		int count;
		count = 64;
		digits = new bool[count];
		cout << endl << "Двоичное представление числа " << numberD << ":" << endl;
		doubleArray(numberD, digits, 64);
		output(option, digits);
		cout << " \n";
		len = 64;
		break;
	default:
		cout << "не та цифирка\n";
		break;
	}
	SetConsoleTextAttribute(h, 07);
	system("pause"); goto s;
}