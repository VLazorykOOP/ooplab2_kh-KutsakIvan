// лб 2.1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>

using namespace std;

void main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int a, b, c, d, res;
    cout << "Введіть число а: "; cin >> a; (unsigned char)a;
    cout << "Введіть число b: "; cin >> b; (unsigned char)b;
    cout << "Введіть число c: "; cin >> c; (unsigned char)c;
    cout << "Введіть число d: "; cin >> d; (unsigned char)d;
    
    res = ((b << 5) + b) + (((d << 4) - d) + (((a << 3) + (a << 2))) >> 9) - ((c << 6) + c) + ((d << 4) - (d << 1));
    cout << "res = " << res<< endl;
    system("pause");
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
