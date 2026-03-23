#include <iostream>
#include <windows.h>
using namespace std;

// Задание 1. Возведение в степень
void power2() {
    int k;
    cout << "Введите  число k: ";
    cin >> k;

    int p = 1;
    for (int i = 0; i < k; i++) {
        p *= 2;
        cout << "2^" << i + 1 << " = " << p << endl;
    }
}

// Задание 2. Операции с указателями
void pointerDemo() {
    int mas[3] = {100, 200, 300};
    int *ptr1, *ptr2;

    ptr1 = mas;
    ptr2 = &mas[2];

    cout << "\nРабота с указателями:\n";
    cout << "*ptr1 = " << *ptr1 << endl;
    cout << "ptr1[1] = " << ptr1[1] << endl;
    cout << "*(ptr1 + 2) = " << *(ptr1 + 2) << endl;
    cout << "*ptr2 = " << *ptr2 << endl;
    cout << "ptr2 - ptr1 = " << ptr2 - ptr1 << endl;
}

double volume(double a) {
    return a * a * a;
}

double volume(double a, double b, double c) {
    return a * b * c;
}



void swap(int a, int b) {
    int temp = a;
    a = b;
    b = temp ;
}

void swapValues(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swapLink(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp ;
}

void swap(double a, double b) {
    double temp = a;
    a = b;
    b = temp;
}

void swapValues(double *a, double *b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}

void swapLink(double &a, double &b) {
    double temp = a;
    a = b;
    b = temp; 
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    power2();
    pointerDemo();

    double side, x, y, z;
    cout << "\nВведите сторону куба: ";
    cin >> side;
    cout << "Объем куба = " << volume(side) << endl;

    cout << "Введите длину, ширину и высоту параллелепипеда: ";
    cin >> x >> y >> z;
    cout << "Объем параллелепипеда = " << volume(x, y, z) << endl;

    int i1 = 10, i2 = 20;
    double d1 = 1.5, d2 = 2.5;
    
    //Обмен по значению
    cout << "\nДо обмена int: " << i1 << " " << i2 << endl;
    swap(i1, i2);
    cout << "После обмена int: " << i1 << " " << i2 << endl;

    i1 = 10;
    i2 = 20;
    //Обмен по указателю
    cout << "\nДо обмена int: " << i1 << " " << i2 << endl;
    swapValues(&i1, &i2);
    cout << "После обмена int: " << i1 << " " << i2 << endl;

    i1 = 10;
    i2 = 20;
    //Обмен по ссылке
    cout << "\nДо обмена int: " << i1 << " " << i2 << endl;
    swapLink(i1, i2);
    cout << "После обмена int: " << i1 << " " << i2 << endl;

     //Обмен по значению
    cout << "\nДо обмена double: " << i1 << " " << i2 << endl;
    swap(d1, d2);
    cout << "После обмена double: " << i1 << " " << i2 << endl;

    d1 = 1.5;
    d2 = 2.5;
    //Обмен по указателю
    cout << "\nДо обмена double: " << i1 << " " << i2 << endl;
    swapValues(&d1, &d2);
    cout << "После обмена double: " << i1 << " " << i2 << endl;

    d1 = 1.5;
    d2 = 2.5;
    //Обмен по ссылке
    cout << "\nДо обмена double: " << i1 << " " << i2 << endl;
    swapLink(d1, d2);
    cout << "После обмена double: " << i1 << " " << i2 << endl;
    
   
    return 0;
}