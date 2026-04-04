#include <iostream>
#include <string>
using namespace std;

// ------------------------- Базовый класс "Автомобиль" -------------------------
class Car {
protected:
    string brand;       // марка автомобиля
    string country;     // страна производитель
public:
    // Конструктор
    Car(const string& b, const string& c) : brand(b), country(c) {}

    // Виртуальный метод для вывода информации (полиморфизм)
    virtual void showInfo() const {
        cout << "Марка: " << brand << ", Страна: " << country << endl;
    }

    // Деструктор (виртуальный для корректного удаления через указатель на базовый класс)
    virtual ~Car() {}
};

// ------------------------- Класс "Модель", наследник Car -------------------------
class Model : public Car {
protected:
    string bodyType;    // тип кузова (седан, хэтчбек и т.д.)
public:
    // Конструктор вызывает конструктор базового класса
    Model(const string& b, const string& c, const string& bt)
        : Car(b, c), bodyType(bt) {}

    // Переопределяем метод вывода
    virtual void showInfo() const override {
        Car::showInfo();               // выводим марку и страну
        cout << "Тип кузова: " << bodyType << endl;
    }
};

// ------------------------- Класс "Машина", наследник Model -------------------------
class Vehicle : public Model {
private:
    int year;           // год выпуска
    string license;     // номерной знак
public:
    // Конструктор
    Vehicle(const string& b, const string& c, const string& bt, int y, const string& l)
        : Model(b, c, bt), year(y), license(l) {}

    // Переопределяем метод вывода
    virtual void showInfo() const override {
        Model::showInfo();            // выводим марку, страну, тип кузова
        cout << "Год выпуска: " << year << ", Номер: " << license << endl;
    }
};

// ------------------------- Главная функция -------------------------
int main() {
    // Создаём объекты разных классов
    Car car("Toyota", "Japan");
    Model model("BMW", "Germany", "sedan");
    Vehicle vehicle("Lada", "Russia", "hatchback", 2020, "A123BC");

    cout << "=== Информация об автомобиле (базовый класс) ===" << endl;
    car.showInfo();
    cout << endl;

    cout << "=== Информация о модели (наследник Car) ===" << endl;
    model.showInfo();
    cout << endl;

    cout << "=== Информация о машине (наследник Model) ===" << endl;
    vehicle.showInfo();
    cout << endl;



    return 0;
}