#include <iostream>
#include <Windows.h>
using namespace std;

class Date {
    uint16_t day;
    uint16_t month;
    uint16_t year;
public:
    /*конструктор с параметрами*/
    Date(uint16_t day1, uint16_t month1, uint16_t year1) : day{ day1 }, month{ month1 }, year{ year1 } {}
    /*конструктор по умолчанию*/
    Date() : Date(0, 0, 0) { }

    /*вывод*/
    void printDate() const {
        cout << (day < 10 ? "0" : "") << day << "-" << (month < 10 ? "0" : "") << month << "-" << year;
    }
};
class People {
    int ID;
    char* surname;
    char* name;
    char* patronymic;
    Date data;
    static int count; /*статический счетчик людей*/
public:
    /*конструктор с параметрами*/
    People(int IDP, const char* surnameP, const char* nameP, const char* patronymicP, Date dataP) : ID{ IDP }, data{ dataP }
    {
        surname = new char[20];
        name = new char[20];
        patronymic = new char[20];

        strcpy_s(surname, 20, surnameP);
        strcpy_s(name, 20, nameP);
        strcpy_s(patronymic, 20, patronymicP);

        count++;
    }
    /*конструктор по умолчанию*/
    People() : People(0, " ", " ", " ", Date{ 0, 0, 0 }) { }
    /*конструктор копирования*/
    People(const People& object)
        : ID{ object.ID }, data{ object.data } {
        surname = new char[strlen(object.surname) + 1];
        strcpy_s(surname, strlen(object.surname) + 1, object.surname);

        name = new char[strlen(object.name) + 1];
        strcpy_s(name, strlen(object.name) + 1, object.name);

        patronymic = new char[strlen(object.patronymic) + 1];
        strcpy_s(patronymic, strlen(object.patronymic) + 1, object.patronymic);

        count++;
    }
    /*деструктор*/
    ~People() {
        delete[] surname;
        delete[] name;
        delete[] patronymic;

        count--;
    }

    /*сетеры и гетеры*/
    int getID() { return ID; }
    void setID(int IDp) { ID = IDp; }
    const char* getsurname() { return surname; }
    void setsurname(const char* surnameP) {
        delete[] surname;
        surname = new char[strlen(surnameP) + 1];
        strcpy_s(surname, strlen(surnameP) + 1, surnameP);
    }
    const char* getname() { return name; }
    void setname(const char* nameP) {
        delete[] name;
        name = new char[strlen(nameP) + 1];
        strcpy_s(name, strlen(nameP) + 1, nameP);
    }
    const char* getpatronymic() { return patronymic; }
    void setpatronymic(const char* patronymicP) {
        delete[] patronymic;
        patronymic = new char[strlen(patronymicP) + 1];
        strcpy_s(patronymic, strlen(patronymicP) + 1, patronymicP);
    }

    /*вывод информации о человеке*/
    void output() const {
        cout << endl << "ID: " << ID << "\nФамилия: " << (surname ? surname : " ") << "\nИмя: " << (name ? name : " ") << "\nОтчество: " << (patronymic ? patronymic : " ") << "\nДата рождения: ";
        data.printDate();
        cout << endl;
    }
    /*вывод количества проживающих*/
    static int getCount() { return count; }
};
int People::count = 0;

class Apartment {
    /* Сам класс несет в себе информацию о квартире, тоесть сколько в ней комнат, какая площадь, 
    сколько жильцов проживает, а так же какие именно. Нужно придумать еще подобную информацию и реализовать ее в виде переменных членов. 
    Какая-то информация будет являться неизменной, какая-то поддается изменениям. */
    /*  1. Должен содержать динамический массив обьектов класса People
        2. Должен содержать переменные члены
        3. Должен содержать функции члены которые нужны для класса
        4. Нужны конструторы, обязателельно 1 с параметром и делегирующий от него 1 по умолчанию,
        а так же 1 контруктор копирования. Если нужно больше - добавить больше    
        */

};

class House {
    /* Класс представляет собой информацию о всех квартирах дома. 
    Дом небольшой, но количество квартир должно быть приближено к реальной хрущевке.
    Нужно придумать переменные члены которые будут находиться в этом классе, для разнообразия*/
    /*  1. Должен содержать массив обьектов класса Apartment
        2. Должен содержать переменные члены
        3. Должен содержать функции члены которые нужны для класса
        4. Нужны конструторы, обязателельно 1 с параметром и делегирующий от него 1 по умолчанию,
        а так же 1 контруктор копирования. Если нужно больше - добавить больше
    */
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    /*Тут нужно реализовать меню с доступом ко всей информации по дому, начиная от количества квартир, заканчивая информацией об проживающих.*/
    People example1;
    Date data(9, 12, 2006);
    People example2(12345, "Легеза", "Виталина", "Андреевна", data);
    People example3 = example2;

    example1.output();
    example2.output();
    example3.output();

    cout << endl << "Количество People: " << People::getCount() << endl;

    return 0;
}