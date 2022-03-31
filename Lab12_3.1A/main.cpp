#include <iostream>
#include <string>
#include <Windows.h>
#include <iomanip>
using namespace std;

#pragma region "Прізвища студентів"
string surnames[] =
{
	"Бурачинський",
	"Кваша",
	"Попенко",
	"Жученко",
	"Пероганич",
	"Карпінський",
	"Дроб\'язко",
	"Боровий",
	"Приступа",
	"Костюк",

	"Гайдук",
	"Грицина",
	"Балога",
	"Величковська",
	"Марченко",
	"Бершеда",
	"Лимаренко",
	"Кравченко",
	"Ластівка",
	"Бельська",
};
#pragma endregion

enum class Spec { PZ, IT, KN , AT };
string strSpec[] = {"Програмне забезпечення", "Інформаційні технології", "Компютерні науки", "Автомобільний транспорт"};

struct Student
{
	string surname;
	int course;
	Spec spec;
	double mark_physic;
	double mark_math;
	double mark_informatic;
};

//void Create(Student* s, size_t cnt)
//{
//	for (size_t i = 0; i < cnt; i++)
//	{
//		cin.get();
//		cout << "Прізвище студента: ";
//		getline(cin, s[i].surname);
//		cout << "Курс(1-6): "; cin >> s[i].course;
//		int spec;
//		cout << "Спеціальність(0 - Програмне забезпечення, 1 - Інформаційні технології, 2 - Компютерні науки, 3 - Автомобільного транспорту): "; cin >> spec;
//		s[i].spec = (Spec)spec;
//		cout << "Оцінка з фізики: "; cin >> s[i].mark_physic;
//		cout << "Оцінка з математики: "; cin >> s[i].mark_math;
//		cout << "Оцінка з інформатики: "; cin >> s[i].mark_informatic;
//	}
//}

void Generete(Student* s, size_t cnt)
{
	for (size_t i = 0; i < cnt; i++)
	{
		s[i].surname = surnames[rand() % 20];
		s[i].course = 1 + rand() % 6;
		s[i].spec = Spec(rand() % 4);
		s[i].mark_informatic = (30 + rand() % 20)/10.0;
		s[i].mark_physic = (30 + rand() % 20) / 10.0;
		s[i].mark_math = (30 + rand() % 20) / 10.0;
	}
}

void Display(Student* s, size_t cnt)
{
	cout << "-----------------------------------------------------------------------------------------------" << endl;
	cout << "|  №  | курс |    прізвище    |       спеціальність     | фізика | математика | інформатика |" << endl;
	cout << "-----------------------------------------------------------------------------------------------" << endl;
	cout << left;
	for (size_t i = 0; i < cnt; i++)
	{
		cout << "|" << setw(5) << i << "|"
			<< setw(6) << s[i].course << "|"
			<< setw(16) << s[i].surname << "|"
			<< setw(25) << strSpec[int(s[i].spec)] << "|"
			<< setw(8) << s[i].mark_physic << "|"
			<< setw(12) << s[i].mark_informatic << "|"
			<< setw(13) << s[i].mark_informatic << "|" << endl;
	}
	cout << "-----------------------------------------------------------------------------------------------" << endl;

}

double avgMark(Student s)
{
	return (s.mark_informatic + s.mark_math + s.mark_physic) / 3.;
}

int CountStudent(Student* s, size_t cnt)
{
	int count = 0;
	for (size_t i = 0; i < cnt; i++)
	{
		if (avgMark(s[i]) > 4.5)
			count++;
	}
	return count;
}

enum class Mark { math, physic, informatic };
string strMark[] = { "math", "physic", "informatic" };
Mark BestSubject(Student* s, size_t cnt)
{
	double math = 0, physic = 0, informatic = 0;
	for (size_t i = 0; i < cnt; i++)
	{
		math += s[i].mark_math;
		physic += s[i].mark_physic;
		informatic += s[i].mark_informatic;
	}
	math /= cnt;
	physic /= cnt;
	informatic /= cnt;

	if (math > physic && math > informatic)
		return Mark::math;
	if (physic > math && physic > informatic)
		return Mark::physic;
	if (informatic > math && informatic > physic)
		return Mark::informatic;
}

int main()
{
	srand(time(0));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	size_t cnt;
	cout << "Введіть кількість студентів у масиві: "; cin >> cnt;
	Student* s = new Student[cnt]();

	Generete(s, cnt);
	Display(s, cnt);
	cout << "Кількість студентів, середній бал яких вищий за 4,5: " << CountStudent(s, cnt) << endl;
	cout << "Предмет, середній бал якого найбільший: " << strMark[(int)BestSubject(s, cnt)] << endl;

	delete[] s;

	return 0;
}