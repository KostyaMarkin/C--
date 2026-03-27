#include <iostream>
using namespace std;

static size_t my_strlen(const char* s) {
    size_t count = 0;
    while (s[count] != '\0') ++count;
    return count;
}

static void my_strcpy(char* dest, const char* src) {
    while ((*dest++ = *src++) != '\0');
}

static int my_strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        ++s1; ++s2;
    }
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}

static void my_strcat(char* dest, const char* src) {
    while (*dest != '\0') ++dest;
    while ((*dest++ = *src++) != '\0');
}

class Stroka {
    char str[80];          
public:
    Stroka();                    
    Stroka(const char* s);        
    Stroka(const Stroka& other); 


    // Перегруженные операторы
    Stroka& operator=(const Stroka& other);
    Stroka& operator+(const Stroka& other);   // сцепление (модифицирует текущий объект)
    int operator==(const Stroka& other);      // сравнение (1 – равны, 0 – нет)

    // Методы
    int length();          // длина строки
    void input();           // ввод с клавиатуры
    void output();          // вывод на экран
};


Stroka::Stroka() {
    str[0] = '\0';
}


Stroka::Stroka(const char* s) {
    my_strcpy(str, s);
}

Stroka::Stroka(const Stroka& other) {
    my_strcpy(str, other.str);
}


Stroka& Stroka::operator=(const Stroka& other) {
    if (this != &other) {               
        my_strcpy(str, other.str);
    }
    return *this;
}

// Оператор сцепления (конкатенация) – модифицирует текущий объект
Stroka& Stroka::operator+(const Stroka& other) {
    my_strcat(str, other.str);
    return *this;
}

// Оператор сравнения
int Stroka::operator==(const Stroka& other) {
    return my_strcmp(str, other.str) == 0 ? 1 : 0;
}


int Stroka::length() {
    return my_strlen(str);
}

// Ввод строки с клавиатуры (без пробелов)
void Stroka::input() {
    cin >> str;
}

// Вывод строки на экран
void Stroka::output() {
    cout << str;
}

// ---------- Главная функция ----------
int main() {
    Stroka s1("qwert"), s3, s4(s1), s5;

    cout << "Введите строку для s3: ";
    s3.input();

    s3.output();
    cout << endl;

    // Сцепление: s1 + s3 + s4
    s5 = s1 + s3 + s4;

    cout << "длина s5 = " << s5.length() << endl;
    cout << "s5 = ";
    s5.output();
    cout << endl;

    // Сравнение
    if (s1 == s5)
        cout << "строки s1 и s5 равны" << endl;
    else if (s1 == s4)
        cout << "строки s1 и s4 равны" << endl;
    else
        cout << "строки не равны" << endl;

    return 0;
}