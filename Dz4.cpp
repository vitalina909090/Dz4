#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>

using namespace std;

class Date {
    uint16_t day;
    uint16_t month;
    uint16_t year;
public:
    Date(uint16_t day1, uint16_t month1, uint16_t year1) : day(day1), month(month1), year(year1) {}
    Date() : Date(0, 0, 0) {}

    void printDate() const {
        cout << (day < 10 ? "0" : "") << day << "-" << (month < 10 ? "0" : "") << month << "-" << year;
    }
};

class People {
    int ID;
    string surname;
    string name;
    string patronymic;
    Date data;
    static int count;
public:
    People(int IDP, const string& surnameP, const string& nameP, const string& patronymicP, Date dataP)
        : ID(IDP), surname(surnameP), name(nameP), patronymic(patronymicP), data(dataP) {
        count++;
    }

    People() : People(0, "", "", "", Date(0, 0, 0)) {}

    People(const People& other)
        : ID(other.ID), surname(other.surname), name(other.name), patronymic(other.patronymic), data(other.data) {
        count++;
    }

    ~People() {
        count--;
    }

    void inputPerson() {
        cout << "Введіть ID: ";
        cin >> ID;

        cin.ignore();

        cout << "Введіть прізвище: ";
        getline(cin, surname);

        cout << "Введіть ім'я: ";
        getline(cin, name);

        cout << "Введіть по батькові: ";
        getline(cin, patronymic);

        int day, month, year;
        cout << "Введіть день народження (дд мм рррр): ";
        cin >> day >> month >> year;
        data = Date(day, month, year);
    }

    void output() const {
        cout << "ID: " << ID << "\nПрізвище: " << surname << "\nІм'я: " << name << "\nПо батькові: " << patronymic << "\nДата народження: ";
        data.printDate();
        cout << endl;
    }

    int getID() const { return ID; }
    static int getCount() { return count; }
};
int People::count = 0;

class Apartment {
    int rooms;
    double area;
    int floor;
    vector<People> humans;

public:
    Apartment() : rooms(0), area(0), floor(0) {}

    Apartment(int roomsP, double areaP, int floorP)
        : rooms(roomsP), area(areaP), floor(floorP) {}

    Apartment(const Apartment& other)
        : rooms(other.rooms), area(other.area), floor(other.floor), humans(other.humans) {}

    ~Apartment() {}

    void newPerson(const People& person) {
        humans.push_back(person);
    }

    void output() const {
        cout << "Квартира: " << rooms << " кімнати, площа: " << area << " кв.м, поверх: " << floor << ".\n";
        cout << "Кількість жильців: " << humans.size() << endl;
        for (int i = 0; i < humans.size(); i++) {
            humans[i].output();
        }
    }

    int getHumanCount() const { return humans.size(); }
    int getFloor() const { return floor; }

    bool findHumanByID(int ID, People& foundHuman) {
        for (int i = 0; i < humans.size(); i++) {
            if (humans[i].getID() == ID) {
                foundHuman = humans[i];
                return true;
            }
        }
        return false;
    }

    bool deleteHumanByID(int ID) {
        for (int i = 0; i < humans.size(); i++) {
            if (humans[i].getID() == ID) {
                humans[i] = humans.back();
                humans.pop_back();
                cout << "Жильця з ID " << ID << " видалено.\n";
                return true;
            }
        }
        cout << "Жильця з ID " << ID << " не знайдено.\n";
        return false;
    }
};

class House {
    int floors;
    Apartment apartments[6];
public:
    House() : floors(3) {
        apartments[0] = Apartment(2, 60.0, 1);
        apartments[1] = Apartment(3, 75.0, 1);
        apartments[2] = Apartment(2, 65.0, 2);
        apartments[3] = Apartment(3, 80.0, 2);
        apartments[4] = Apartment(4, 90.0, 3);
        apartments[5] = Apartment(2, 70.0, 3);
    }

    House(const House& other) : floors(other.floors) {
        for (int i = 0; i < 6; i++) {
            apartments[i] = other.apartments[i];
        }
    }

    ~House() {}

    void outputGeneralInfo() const {
        cout << "Поверхів в будинку: " << floors << "\nКвартир в будинку: 6" << endl;
        int totalHumans = 0;
        for (int i = 0; i < 6; i++) {
            totalHumans += apartments[i].getHumanCount();
        }
        cout << "Всього жильців в будинку: " << totalHumans << endl;
    }

    void outputApartmentInfo(int num) const {
        if (num >= 0 && num < 6) {
            apartments[num].output();
        }
        else {
            cout << "Некоректний номер квартири.\n";
        }
    }

    bool findHumanByID(int ID, People& foundHuman) {
        for (int i = 0; i < 6; i++) {
            if (apartments[i].findHumanByID(ID, foundHuman)) {
                cout << "Жильця з ID " << ID << " знайдено в квартирі на " << apartments[i].getFloor() << " поверсі.\n";
                return true;
            }
        }
        return false;
    }

    void deleteHumanByID(int ID) {
        bool found = false;
        for (int i = 0; i < 6; i++) {
            if (apartments[i].deleteHumanByID(ID)) {
                found = true;
            }
        }
        if (!found) {
            cout << "Жильця з ID " << ID << " не знайдено в будинку.\n";
        }
    }

    void newHumanToApartment(int num, const People& human) {
        if (num >= 0 && num < 6) {
            apartments[num].newPerson(human);
            cout << "Жильця успішно додано до квартири.\n";
        }
        else {
            cout << "Некоректний номер квартири.\n";
        }
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    House house;

    int choice = 1;
    do {
        cout << "\n--- Головне меню ---\n" <<
            "1. Показати інформацію про будинок\n" <<
            "2. Показати інформацію про квартиру\n" <<
            "3. Знайти жильця за ID\n" <<
            "4. Видалити жильця за ID\n" <<
            "5. Додати жильця в квартиру\n" <<
            "0. Вийти\n" <<
            "Оберіть дію: ";
        cin >> choice;

        switch (choice) {
        case 1:
            house.outputGeneralInfo();
            break;
        case 2: {
            int num;
            cout << "Введіть номер квартири (0-5): ";
            cin >> num;
            house.outputApartmentInfo(num);
            break;
        }
        case 3: {
            int ID;
            cout << "Введіть ID жильця: ";
            cin >> ID;
            People foundHuman;
            if (house.findHumanByID(ID, foundHuman)) {
                foundHuman.output();
            }
            else {
                cout << "Жильця з таким ID не знайдено\n";
            }
            break;
        }
        case 4: {
            int ID;
            cout << "Введіть ID жильця для видалення: ";
            cin >> ID;
            house.deleteHumanByID(ID);
            break;
        }
        case 5: {
            int apartmentNum;
            cout << "Введіть номер квартири (0-5): ";
            cin >> apartmentNum;
            People newHuman;
            newHuman.inputPerson();
            house.newHumanToApartment(apartmentNum, newHuman);
            break;
        }
        case 0:
            cout << "Вихід\n";
            break;
        default:
            cout << "Некоректний вибір\n";
        }
    } while (choice != 0);

    return 0;
}
