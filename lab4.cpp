#include <iostream>  
#include <cstring>      
#include <windows.h>

using namespace std;

// ---------- Собственные реализации строковых функций ----------

// 1. Три способа вычисления длины строки
size_t str_len1(const char* str) {
    size_t count = 0;
    while (str[count] != '\0') ++count;
    return count;
}

size_t str_len2(const char* str) {
    const char* p = str;
    while (*p != '\0') ++p;
    return p - str;
}

size_t str_len3(const char* str) {
    size_t count = 0;
    for (; *str != '\0'; ++str) ++count;
    return count;
}

// 2. Копирование строки
void my_strcpy(char* dest, const char* src) {
    while ((*dest++ = *src++) != '\0');
}

// 3. Сравнение строк
int my_strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        ++s1; ++s2;
    }
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}

// 4. Конкатенация
void my_strcat(char* dest, const char* src) {
    // идём в конец строки назначения
    while (*dest != '\0') ++dest;
    // копируем исходную строку в конец
    while ((*dest++ = *src++) != '\0');
}

// ---------- Главная функция ----------
int main() {

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    // Часть 1 и 2: работа со статическими строками
    char str1[] = "qwerty";
    char str2[] = "1234567890";
    
    cout << "===== Часть 1 и 2: Статические строки =====\n";
    
    // Стандартные библиотечные функции
    cout << "Стандартная strlen: длина str1 = " << strlen(str1) 
         << ", str2 = " << strlen(str2) << endl;
    
    char copy_lib[50];
    strcpy(copy_lib, str1);
    cout << "Стандартная strcpy: копия str1 = " << copy_lib << endl;
    
    cout << "Стандартная strcmp: сравнение str1 и str2 = " << strcmp(str1, str2) << endl;
    
    char cat_lib[50];
    strcpy(cat_lib, str1);
    strcat(cat_lib, str2);
    cout << "Стандартная strcat: сцепление = " << cat_lib << endl;
    
    cout << "\n--- Собственные функции ---\n";
    // Собственные функции длины строки
    cout << "str_len1: str1 = " << str_len1(str1) << ", str2 = " << str_len1(str2) << endl;
    cout << "str_len2: str1 = " << str_len2(str1) << ", str2 = " << str_len2(str2) << endl;
    cout << "str_len3: str1 = " << str_len3(str1) << ", str2 = " << str_len3(str2) << endl;
    
    // Собственное копирование
    char copy_my[50];
    my_strcpy(copy_my, str1);
    cout << "my_strcpy: копия str1 = " << copy_my << endl;
    
    // Собственное сравнение
    int cmp = my_strcmp(str1, str2);
    cout << "my_strcmp: str1 vs str2 = " << cmp << endl;
    
    // Собственная конкатенация
    char cat_my[50];
    my_strcpy(cat_my, str1);
    my_strcat(cat_my, str2);
    cout << "my_strcat: сцепление = " << cat_my << endl;
    
    // Часть 3: Динамическая память с malloc
    cout << "\n===== Часть 3: Динамическая память (malloc) =====\n";
    char *dyn1, *dyn2;
    dyn1 = (char*)malloc(100);
    dyn2 = (char*)malloc(100);
    
    if (!dyn1 || !dyn2) {
        cout << "Ошибка выделения памяти.\n";
        return 1;
    }
    
    // Инициализация строк
    my_strcpy(dyn1, "Привет");
    my_strcpy(dyn2, "Мир");
    cout << "До: dyn1 = " << dyn1 << ", dyn2 = " << dyn2 << endl;
    
    my_strcat(dyn1, dyn2);
    cout << "После my_strcat: dyn1 = " << dyn1 << endl;
    
    my_strcpy(dyn1, "Сравнение");
    cout << "my_strcmp: " << my_strcmp(dyn1, dyn2) << endl;
    
    free(dyn1);
    free(dyn2);
    
    // Часть 4: Использование calloc вместо malloc
    cout << "\n===== Часть 4: Динамическая память (calloc) =====\n";
    char *calloc1, *calloc2;
    // calloc выделяет память и обнуляет её
    calloc1 = (char*)calloc(100, sizeof(char));
    calloc2 = (char*)calloc(100, sizeof(char));
    
    if (!calloc1 || !calloc2) {
        cout << "Ошибка выделения памяти.\n";
        return 1;
    }
    
    my_strcpy(calloc1, "C++");
    my_strcpy(calloc2, "Лабораторная");
    cout << "Строки через calloc: " << calloc1 << " и " << calloc2 << endl;
    my_strcat(calloc1, calloc2);
    cout << "Сцепленные: " << calloc1 << endl;
    
    free(calloc1);
    free(calloc2);
    
    // Пояснение различий malloc и calloc
    cout << "\nПримечание: malloc выделяет неинициализированную память,"
         << " calloc выделяет и обнуляет память.\n";
    
    return 0;
}