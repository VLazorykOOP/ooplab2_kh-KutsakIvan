// лб 2.2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <bitset>

using namespace std;

union bitField
{
    int nline, posline;
    unsigned short codletter;
};

void encryption(string* name, unsigned short Res[64])
{
    //зчитування інформації з файлу
    char l[8][9];
    ifstream fin;
    fin.open(*name);
    for (int i = 0; i < 8; i++)
    {
        fin.getline(l[i], 9);
        l[i][9] = '\0';
    }
    fin.close();
    for (int i = 0; i < 8; i++)//заповнення пробілами вільні місця в рядках
    {
        if (strlen(l[i]) != 8)
        {
            for (int j = strlen(l[i]); j < 8; j++)
            {
                l[i][j] = ' ';
                if (j + 1 == 8)l[i][j + 1] = '\0';
            }
        }
    }

    //шиврування
  
    bitField code;
    
    unsigned short  res = 0;
    unsigned char t = 1;
    int b = 0;



    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            res = 0;
            code.nline = i;
            res |= code.nline;

            // код букви 8 біт
            code.codletter = l[i][j];
            
            res |= code.codletter << 3;

            //біт парності перших двох полів 1 біт
            code.nline = i;
            for (int k = 0; k < 8; k++) // обчислення біта парності
            {
                if ( (code.nline & t) == t)
                {
                    b++;
                }
                t <<= 1;
            }
            code.codletter = l[i][j];
            for (int k = 0; k < 8; k++) // обчислення біта парності
            {
                if ( (code.codletter & t) == t)
                {
                    b++;
                }
                t <<= 1;
            }
            if (b % 2 == 0)res |= 1 << 11;

            //позиція символу в рядку 3 біти
            code.posline = j;
            res |= code.posline << 12;
            b = 0; t = 1;

            //біт парності позиції символу в рядку
            for (int k = 0; k < 3; k++) // обчислення біта парності
            {
                if ((code.posline & t) == t)b++;
                t <<= 1;
            }

            if (b % 2 == 0)res |= 1 << 15;
            if (res & 0x4000) res |= 0x8000;
            Res[8 * i + j] = res;
            b = 0; t = 1;



        }
    }
    for (int i = 0; i < 64; i++)cout << bitset<sizeof(unsigned short) * 8>(Res[i]) << endl;
    //запис результату в файл
    string name2;
    cout << "Введіть ім'я файлу в який буде записано зашифрований текст: "; cin >> name2;
    ofstream fout(name2, ios::binary | ios::out);
    fout.write((char*)Res, 64 * sizeof(unsigned short));
    fout.close();
}

void main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    unsigned short Res[64];
    int v, V;
    string name;
    cout << "Зашифрувати - 0" << endl << "Розшифрувати - 1" << endl;
    cout << "Виберіть дію: "; cin >> V;
    cout << "відкрити існуючий файл - 1" << endl << "створоти файл - 2" << endl; cin >> v;
    if (V == 0)
    {
        if (v == 1)
        {
            //відкриття файлу
            cout << "Введіть ім'я файлу: "; cin >> name;
            encryption(&name, Res);
            //for (int i = 0; i < 64; i++)cout << bitset<sizeof(unsigned short) * 8>(Res[i]) << endl;
        }
        else if (v == 2)
        {
            //створення файлу
            char line[9];
            cout << "Введіть ім'я файлу: "; cin >> name;
            ofstream fout;
            fout.open(name);
            cout << "Заповніть файл 8 рядками максимум по 8 символів" << endl;
            gets_s(line);
            for (int i = 0; i < 8; i++)
            {
                gets_s(line);
                fout << line << endl;
            }
            fout.close();
            encryption(&name, Res);
            //for (int i = 0; i < 64; i++)cout << bitset<sizeof(unsigned short) * 8>(Res[i]) << endl;
        }
    }
    else if (V == 1)
    {
        char res[8][9], letter;
        unsigned short l[64], codsymbol, encrypt, masksymbol, masknline = 7, maskposline;
        unsigned char codletter;
        short nline, posline;
        bitField code;
        string name;
        cout << "Введіть ім'я файлу який потрібно розшифрувати: "; cin >> name;
        ifstream fin(name, ios::binary | ios::in);
        fin.read((char*)l, 64 * sizeof(unsigned short));
        fin.close();
        maskposline = 7 << 12; //маска для виключення всіх бітів крім тих які відповідають за позицію символа в рядку
        masksymbol = 255 << 3; //маска для виключення всіх бітів крім тих які відповідають символ
        for (int i = 0; i < 64; i++)
        {
            encrypt = l[i];
            codletter = (encrypt & masksymbol) >> 3;
            letter = codletter;
            nline = encrypt & masknline;
            posline = (encrypt & maskposline) >> 12;
            res[nline][posline] = letter;
        }

        cout << "Введіть ім'я файлу в який буде записано результат: "; cin >> name;
        ofstream fout;
        fout.open(name);
        cout << "======Результат======" << endl;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                fout << res[i][j];
                cout << res[i][j];
            }
            fout << endl;
            cout << endl;
        }
        fout.close();
    }
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