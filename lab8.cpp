#include <iostream>
#include <fstream>
#include <stdexcept>
#include <windows.h>
using namespace std;

// ============== Класс Stroka из ЛР6 с перегрузкой << и >> ==============
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
    Stroka& operator+(const Stroka& other);
    int operator==(const Stroka& other);

    // Методы
    int length();
    void input();
    void output();

    // Пункт 1: перегрузка операторов помещения и извлечения
    friend ostream& operator<<(ostream& os, const Stroka& s);
    friend istream& operator>>(istream& is, Stroka& s);
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

Stroka& Stroka::operator+(const Stroka& other) {
    my_strcat(str, other.str);
    return *this;
}

int Stroka::operator==(const Stroka& other) {
    return my_strcmp(str, other.str) == 0 ? 1 : 0;
}

int Stroka::length() {
    return my_strlen(str);
}

void Stroka::input() {
    cin >> str;
}

void Stroka::output() {
    cout << str;
}

// Реализация перегруженных операторов потокового ввода/вывода (пункт 1)
ostream& operator<<(ostream& os, const Stroka& s) {
    os << s.str;
    return os;
}

istream& operator>>(istream& is, Stroka& s) {
    is >> s.str;
    return is;
}

// ============== Исключение для файловых ошибок ==============
class FileException : public exception {
private:
    string message;
public:
    FileException(const string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// ============== Пункт 3: Цифратор с использованием классов потоков ==============
class Digitator {
private:
    string inputFile;
    string outputFile;

public:
    Digitator(string in, string out) : inputFile(in), outputFile(out) {}

    void digitate() {
        ifstream fin(inputFile);
        if (!fin) throw FileException("Не удалось открыть входной файл для цифратора.");

        ofstream fout(outputFile);
        if (!fout) throw FileException("Не удалось открыть выходной файл для цифратора.");

        char ch;
        while (fin.get(ch)) {
            if (isalpha(ch)) {
                // Преобразуем букву в число: a=1, b=2, ..., z=26
                int digit = tolower(ch) - 'a' + 1;
                fout << digit;
                // Добавляем пробел между числами для читаемости
                fout << ' ';
            } else if (isdigit(ch)) {
                // Цифры оставляем как есть
                fout << ch;
            } else {
                // Остальные символы (пробелы, знаки препинания)
                fout << ch;
            }
        }

        fin.close();
        fout.close();
    }

    // Демонстрация методов изменения состояния потока (пункт 4)
    void showFileInfo() {
        ifstream fin(inputFile);
        if (!fin) throw FileException("Не удалось открыть файл для демонстрации.");

        cout << "\n=== Демонстрация методов изменения состояния потока ===" << endl;
        
        // tellg() - получение текущей позиции
        streampos begin = fin.tellg();
        cout << "Начальная позиция: " << begin << endl;
        
        // seekg() - перемещение в конец файла
        fin.seekg(0, ios::end);
        streampos end = fin.tellg();
        cout << "Конечная позиция (размер файла): " << end << " байт" << endl;
        
        // seekg() - перемещение в начало
        fin.seekg(0, ios::beg);
        
        // peek() - просмотр следующего символа без извлечения
        cout << "Первый символ файла (peek): " << (char)fin.peek() << endl;
        
        // ignore() - пропуск первых 5 символов
        cout << "Пропускаем 5 символов..." << endl;
        fin.ignore(5);
        cout << "Символ после пропуска: " << (char)fin.peek() << endl;
        
        // rdstate() - проверка состояния потока
        cout << "Состояние потока (rdstate): " << fin.rdstate() << endl;
        if (fin.good()) cout << "Поток в хорошем состоянии" << endl;
        
        // clear() - сброс флагов состояния
        fin.clear();
        
        // getline() - чтение строки
        fin.seekg(0, ios::beg);
        string line;
        getline(fin, line);
        cout << "Первая строка файла (getline): " << line << endl;
        
        fin.close();
    }
};

// ============== Пункт 4: Дополнительная программа для демонстрации методов состояния потоков ==============
void demonstrateStreamMethods() {
    cout << "\n========== Демонстрация методов изменения состояния потоков ==========" << endl;
    
    // Создаем тестовый файл
    ofstream testFile("test.txt");
    testFile << "Hello, World!\nThis is a test file.\nLine 3: Demonstration of stream methods.\n";
    testFile.close();
    
    ifstream file("test.txt");
    if (!file) {
        cout << "Ошибка открытия файла" << endl;
        return;
    }
    
    // 1. tellg() - получение текущей позиции
    cout << "\n1. tellg() - текущая позиция в потоке:" << endl;
    cout << "   Позиция до чтения: " << file.tellg() << endl;
    
    // 2. getline() - чтение строки
    string line;
    getline(file, line);
    cout << "   Прочитана строка: " << line << endl;
    cout << "   Позиция после чтения: " << file.tellg() << endl;
    
    // 3. seekg() - перемещение позиции
    cout << "\n2. seekg() - перемещение позиции в потоке:" << endl;
    file.seekg(0, ios::beg);  // в начало
    cout << "   После seekg(0, ios::beg): " << file.tellg() << endl;
    
    file.seekg(10, ios::beg); // на 10 байт от начала
    cout << "   После seekg(10, ios::beg): " << file.tellg() << endl;
    cout << "   Символ на позиции 10: " << (char)file.peek() << endl;
    
    // 4. peek() - просмотр следующего символа
    cout << "\n3. peek() - просмотр символа без извлечения:" << endl;
    cout << "   peek(): " << (char)file.peek() << endl;
    cout << "   После peek позиция не изменилась: " << file.tellg() << endl;
    
    // 5. ignore() - пропуск символов
    cout << "\n4. ignore() - пропуск символов:" << endl;
    file.seekg(0, ios::beg);
    cout << "   Позиция до ignore: " << file.tellg() << endl;
    file.ignore(7); // пропускаем "Hello, "
    cout << "   После ignore(7): " << file.tellg() << endl;
    cout << "   Следующий символ: " << (char)file.peek() << endl;
    
    // 6. rdstate() и good() - проверка состояния
    cout << "\n5. rdstate() и good() - проверка состояния потока:" << endl;
    cout << "   rdstate(): " << file.rdstate() << endl;
    cout << "   good(): " << (file.good() ? "true" : "false") << endl;
    cout << "   eof(): " << (file.eof() ? "true" : "false") << endl;
    cout << "   fail(): " << (file.fail() ? "true" : "false") << endl;
    cout << "   bad(): " << (file.bad() ? "true" : "false") << endl;
    
    // 7. clear() - сброс состояния
    cout << "\n6. clear() - сброс состояния потока:" << endl;
    file.clear();
    cout << "   После clear() - rdstate(): " << file.rdstate() << endl;
    
    // 8. eof() - проверка конца файла
    cout << "\n7. eof() - проверка конца файла:" << endl;
    file.seekg(0, ios::end);
    cout << "   После seekg(0, ios::end): " << file.tellg() << endl;
    file.peek(); // попытка чтения за концом
    cout << "   eof(): " << (file.eof() ? "true" : "false") << endl;
    
    file.close();
    
    // Удаляем тестовый файл
    remove("test.txt");
}

// ============== Демонстрация работы класса Stroka с операторами << и >> ==============
void demonstrateStroka() {
    cout << "\n========== Демонстрация работы класса Stroka с операторами << и >> ==========" << endl;
    
    Stroka s1("Hello");
    Stroka s2, s3;
    
    cout << "s1 = " << s1 << endl;  // использование оператора <<
    
    cout << "Введите строку для s2: ";
    cin >> s2;  // использование оператора >>
    
    cout << "Введите строку для s3: ";
    cin >> s3;
    
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    
    // Демонстрация конкатенации
    Stroka s4 = s1;
    s4 = s4 + s2;
    cout << "s1 + s2 = " << s4 << endl;
    
    // Демонстрация сравнения
    if (s2 == s3) {
        cout << "s2 и s3 равны" << endl;
    } else {
        cout << "s2 и s3 не равны" << endl;
    }
}

// ============== Главная функция ==============
int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    
    cout << "========== ЛАБОРАТОРНАЯ РАБОТА №8 ==========" << endl;
    
    // Пункт 1 и 2: демонстрация класса Stroka с перегруженными операторами
    demonstrateStroka();
    
    // Пункт 3: цифратор с использованием классов потоков
    cout << "\n========== Пункт 3: Цифратор ==========" << endl;
    
    // Создаем тестовый файл для цифратора
    ofstream testInput("input.txt");
    testInput << "Hello World! 123 ABC def" << endl;
    testInput.close();
    
    try {
        Digitator digitator("input.txt", "digitator_output.txt");
        digitator.digitate();
        cout << "Цифратор успешно выполнен. Результат в файле 'digitator_output.txt'" << endl;
        
        // Вывод результата цифратора
        ifstream result("digitator_output.txt");
        cout << "Результат цифратора: ";
        char ch;
        while (result.get(ch)) {
            cout << ch;
        }
        cout << endl;
        result.close();
        
        // Демонстрация методов изменения состояния потока на примере цифратора
        digitator.showFileInfo();
        
    } catch (const FileException& e) {
        cout << "Ошибка файла: " << e.what() << endl;
    } catch (const exception& e) {
        cout << "Общая ошибка: " << e.what() << endl;
    }
    
    // Пункт 4: собственная программа для демонстрации методов изменения состояния потоков
    demonstrateStreamMethods();
    
    return 0;
}