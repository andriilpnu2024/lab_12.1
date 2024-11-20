#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void CreateBIN(char* fname) {
    ofstream fout(fname, ios::binary); // відкрили файл для запису
    char ch; // відповідь користувача – чи продовжувати введення
    string s; // введений користувачем рядок
    do {
        cin.get(); // очищуємо буфер клавіатури – щоб не було символу
        cin.sync(); // "кінець рядка", який залишився після вводу числа
        cout << "enter line: "; getline(cin, s); // ввели рядок
        for (unsigned i = 0; i < s.length(); i++) // скануємо введений рядок
            fout.write((char*)&s[i], sizeof(s[i])); // записали символ у файл
        cout << "continue? (y/n): "; cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    cout << endl;
}

void PrintBIN(char* fname) {
    ifstream fin(fname, ios::binary); // відкрили файл для зчитування
    char c; // прочитаний символ
    while (fin.read((char*)&c, sizeof(c))) // поки можна прочитати символ
    {
        cout << c << " "; // виводимо його на екран
    }
    cout << endl;
}
void ProcessBIN1(char* fname, char* gname) {
    ifstream f(fname, ios::binary); // відкрили файл для зчитування
    ofstream g(gname, ios::binary); // відкрили файл для запису
    char c; // прочитаний символ
    int min_even = -1; // Ініціалізуємо як недійсне значення
    int max_odd = -1; // Ініціалізуємо як недійсне значення

    while (f.read((char*)&c, sizeof(c))) {
        if (isdigit(c)) {
            int num = c - '0'; // Перетворимо символ цифри у число
            if (num % 2 == 0) { // Парне число
                if (min_even == -1 || num < min_even) {
                    min_even = num;
                }
            }
            else { // Непарне число
                if (max_odd == -1 || num > max_odd) {
                    max_odd = num;
                }
            }
        }
    }

    // Записуємо результати у файл
    if (min_even != -1) {
        g.write((char*)&min_even, sizeof(min_even));
    }
    if (max_odd != -1) {
        g.write((char*)&max_odd, sizeof(max_odd));
    }
}

void PrintProcessedBIN(char* fname) {
    ifstream fin(fname, ios::binary); // відкрили файл для зчитування
    int num;
    while (fin.read((char*)&num, sizeof(num))) { // читаємо числа
        cout << num << " "; // виводимо їх
    }
    cout << endl;
}

int main() {
    char fname[100]; // ім'я першого файлу
    cout << "enter file name 1: "; cin >> fname;
    CreateBIN(fname); // ввели рядки файлу з клавіатури
    PrintBIN(fname); // вивели вміст першого файлу на екран
    char gname[100]; // ім'я другого файлу
    cout << "enter file name 2: "; cin >> gname;
    ProcessBIN1(fname, gname);
    PrintProcessedBIN(gname); // вивели вміст другого файлу на екран
    return 0;
}
