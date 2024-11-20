#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void CreateBIN(char* fname) {
    ofstream fout(fname, ios::binary); // ������� ���� ��� ������
    char ch; // ������� ����������� � �� ������������ ��������
    string s; // �������� ������������ �����
    do {
        cin.get(); // ������� ����� ��������� � ��� �� ���� �������
        cin.sync(); // "����� �����", ���� ��������� ���� ����� �����
        cout << "enter line: "; getline(cin, s); // ����� �����
        for (unsigned i = 0; i < s.length(); i++) // ������� �������� �����
            fout.write((char*)&s[i], sizeof(s[i])); // �������� ������ � ����
        cout << "continue? (y/n): "; cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    cout << endl;
}

void PrintBIN(char* fname) {
    ifstream fin(fname, ios::binary); // ������� ���� ��� ����������
    char c; // ���������� ������
    while (fin.read((char*)&c, sizeof(c))) // ���� ����� ��������� ������
    {
        cout << c << " "; // �������� ���� �� �����
    }
    cout << endl;
}
void ProcessBIN1(char* fname, char* gname) {
    ifstream f(fname, ios::binary); // ������� ���� ��� ����������
    ofstream g(gname, ios::binary); // ������� ���� ��� ������
    char c; // ���������� ������
    int min_even = -1; // ���������� �� ������� ��������
    int max_odd = -1; // ���������� �� ������� ��������

    while (f.read((char*)&c, sizeof(c))) {
        if (isdigit(c)) {
            int num = c - '0'; // ����������� ������ ����� � �����
            if (num % 2 == 0) { // ����� �����
                if (min_even == -1 || num < min_even) {
                    min_even = num;
                }
            }
            else { // ������� �����
                if (max_odd == -1 || num > max_odd) {
                    max_odd = num;
                }
            }
        }
    }

    // �������� ���������� � ����
    if (min_even != -1) {
        g.write((char*)&min_even, sizeof(min_even));
    }
    if (max_odd != -1) {
        g.write((char*)&max_odd, sizeof(max_odd));
    }
}

void PrintProcessedBIN(char* fname) {
    ifstream fin(fname, ios::binary); // ������� ���� ��� ����������
    int num;
    while (fin.read((char*)&num, sizeof(num))) { // ������ �����
        cout << num << " "; // �������� ��
    }
    cout << endl;
}

int main() {
    char fname[100]; // ��'� ������� �����
    cout << "enter file name 1: "; cin >> fname;
    CreateBIN(fname); // ����� ����� ����� � ���������
    PrintBIN(fname); // ������ ���� ������� ����� �� �����
    char gname[100]; // ��'� ������� �����
    cout << "enter file name 2: "; cin >> gname;
    ProcessBIN1(fname, gname);
    PrintProcessedBIN(gname); // ������ ���� ������� ����� �� �����
    return 0;
}
