#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

class Date {
    uint16_t day;
    uint16_t month;
    uint16_t year;
public:
    Date(uint16_t day1, uint16_t month1, uint16_t year1) : day{ day1 }, month{ month1 }, year{ year1 } {}
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
        : ID{ IDP }, surname{ surnameP }, name{ nameP }, patronymic{ patronymicP }, data{ dataP } {
        count++;
    }

    People() : People(0, "", "", "", Date{ 0, 0, 0 }) {}

    ~People() {
        count--;
    }

    People(const People& other)
        : ID{ other.ID }, surname{ other.surname }, name{ other.name }, patronymic{ other.patronymic }, data{ other.data } {
        count++;
    }

    People& operator=(const People& other) {
        if (this != &other) {
            ID = other.ID;
            surname = other.surname;
            name = other.name;
            patronymic = other.patronymic;
            data = other.data;
        }
        return *this;
    }

    void inputPerson() {
        cout << "Введите ID: ";
        cin >> ID;

        cin.ignore(); // Очистка буфера перед вводом строки

        cout << "Введите фамилию: ";
        getline(cin, surname);

        cout << "Введите имя: ";
        getline(cin, name);

        cout << "Введите отчество: ";
        getline(cin, patronymic);

        int day, month, year;
        cout << "Введите день рождения (дд мм гггг): ";
        cin >> day >> month >> year;
        data = Date(day, month, year);
    }

    void output() const {
        cout << "ID: " << ID << "\nФамилия: " << surname << "\nИмя: " << name << "\nОтчество: " << patronymic << "\nДата рождения: ";
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
    People* tenants;
    int tenantCount;
    int maxTenants;
public:
    Apartment() : rooms{ 0 }, area{ 0 }, floor{ 0 }, tenants{ nullptr }, tenantCount{ 0 }, maxTenants{ 0 } {}

    Apartment(int roomsP, double areaP, int floorP, int maxTenantsP)
        : rooms{ roomsP }, area{ areaP }, floor{ floorP }, maxTenants{ maxTenantsP }, tenantCount{ 0 } {
        tenants = new People[maxTenants];
    }

    ~Apartment() {
        delete[] tenants;
    }

    Apartment(const Apartment& other)
        : rooms{ other.rooms }, area{ other.area }, floor{ other.floor }, tenantCount{ other.tenantCount }, maxTenants{ other.maxTenants } {
        tenants = new People[maxTenants];
        for (int i = 0; i < tenantCount; ++i) {
            tenants[i] = other.tenants[i];
        }
    }

    Apartment& operator=(const Apartment& other) {
        if (this != &other) {
            delete[] tenants;
            rooms = other.rooms;
            area = other.area;
            floor = other.floor;
            tenantCount = other.tenantCount;
            maxTenants = other.maxTenants;
            tenants = new People[maxTenants];
            for (int i = 0; i < tenantCount; ++i) {
                tenants[i] = other.tenants[i];
            }
        }
        return *this;
    }

    void addTenant(const People& person) {
        if (tenantCount < maxTenants) {
            tenants[tenantCount++] = person;
        }
        else {
            cout << "Квартира полна, нельзя добавить больше жильцов.\n";
        }
    }

    void output() const {
        cout << "Квартира: " << rooms << " комнаты, площадь: " << area << " кв.м, этаж: " << floor << ".\n";
        cout << "Количество жильцов: " << tenantCount << endl;
        for (int i = 0; i < tenantCount; ++i) {
            tenants[i].output();
        }
    }

    int getTenantCount() const { return tenantCount; }
    int getFloor() const { return floor; }

    People* findTenantByID(int ID) const {
        for (int i = 0; i < tenantCount; ++i) {
            if (tenants[i].getID() == ID) {
                return &tenants[i];
            }
        }
        return nullptr;
    }

    void removeTenantByID(int ID) {
        for (int i = 0; i < tenantCount; ++i) {
            if (tenants[i].getID() == ID) {
                for (int j = i; j < tenantCount - 1; ++j) {
                    tenants[j] = tenants[j + 1];
                }
                tenantCount--;
                return;
            }
        }
        cout << "Жилец с ID " << ID << " не найден.\n";
    }
};

class House {
    int floors;
    Apartment apartments[6];
public:
    House() : floors{ 3 } {
        apartments[0] = Apartment(2, 60.0, 1, 3);
        apartments[1] = Apartment(3, 75.0, 1, 2);
        apartments[2] = Apartment(2, 65.0, 2, 2);
        apartments[3] = Apartment(3, 80.0, 2, 3);
        apartments[4] = Apartment(4, 90.0, 3, 4);
        apartments[5] = Apartment(2, 70.0, 3, 1);
    }

    House(const House& other) : floors{ other.floors } {
        for (int i = 0; i < 6; ++i) {
            apartments[i] = other.apartments[i];
        }
    }

    House& operator=(const House& other) {
        if (this != &other) {
            floors = other.floors;
            for (int i = 0; i < 6; ++i) {
                apartments[i] = other.apartments[i];
            }
        }
        return *this;
    }

    void outputGeneralInfo() const {
        cout << "Этажей в доме: " << floors << endl;
        cout << "Квартир в доме: 6" << endl;
        int totalTenants = 0;
        for (const auto& apartment : apartments) {
            totalTenants += apartment.getTenantCount();
        }
        cout << "Всего жильцов в доме: " << totalTenants << endl;
    }

    void outputApartmentInfo(int index) const {
        if (index >= 0 && index < 6) {
            apartments[index].output();
        }
        else {
            cout << "Некорректный номер квартиры.\n";
        }
    }

    People* findTenantByID(int ID) {
        for (auto& apartment : apartments) {
            People* foundTenant = apartment.findTenantByID(ID);
            if (foundTenant != nullptr) {
                cout << "Жилец с ID " << ID << " найден в квартире на " << apartment.getFloor() << " этаже.\n";
                return foundTenant;
            }
        }
        return nullptr;
    }

    void removeTenantByID(int ID) {
        for (auto& apartment : apartments) {
            apartment.removeTenantByID(ID);
        }
    }

    Apartment* getApartments() {
        return apartments;
    }
};

void menu(House& house) {
    int choice = 0;
    do {
        cout << "\n--- Главное меню ---\n";
        cout << "1. Просмотреть информацию\n";
        cout << "2. Изменить информацию\n";
        cout << "3. Выйти\n";
        cout << "Введите ваш выбор: ";

        while (!(cin >> choice) || (choice < 1 || choice > 3)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Некорректный ввод. Пожалуйста, введите число от 1 до 3: ";
        }

        switch (choice) {
        case 1: {
            int subChoice;
            cout << "\n--- Просмотреть информацию ---\n";
            cout << "1.1 Общая информация о доме\n";
            cout << "1.2 Информация о квартире и жителях\n";
            cout << "1.3 Информация о жильце по ID\n";
            cout << "Введите ваш выбор: ";

            while (!(cin >> subChoice) || (subChoice < 1 || subChoice > 3)) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Некорректный ввод. Пожалуйста, введите число от 1 до 3: ";
            }

            switch (subChoice) {
            case 1:
                house.outputGeneralInfo();
                break;
            case 2: {
                int apartmentIndex;
                cout << "Введите номер квартиры (1 - 6): ";

                while (!(cin >> apartmentIndex) || (apartmentIndex < 1 || apartmentIndex > 6)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Некорректный ввод. Пожалуйста, введите номер квартиры от 1 до 6: ";
                }
                apartmentIndex--; // переводим в индекс массива

                house.outputApartmentInfo(apartmentIndex);
                break;
            }
            case 3: {
                int tenantID;
                cout << "Введите ID жильца: ";

                while (!(cin >> tenantID)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Некорректный ввод. Пожалуйста, введите ID жильца: ";
                }
                People* tenant = house.findTenantByID(tenantID);
                if (tenant) {
                    tenant->output();
                }
                else {
                    cout << "Жилец с ID " << tenantID << " не найден.\n";
                }
                break;
            }
            default:
                cout << "Некорректный выбор.\n";
                break;
            }
            break;
        }
        case 2: {
            int subChoice;
            cout << "\n--- Изменить информацию ---\n";
            cout << "2.1 Добавить нового жильца\n";
            cout << "2.2 Удалить жильца\n";
            cout << "Введите ваш выбор: ";

            while (!(cin >> subChoice) || (subChoice < 1 || subChoice > 2)) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Некорректный ввод. Пожалуйста, введите число 1 или 2: ";
            }

            switch (subChoice) {
            case 1: {
                int apartmentIndex;
                cout << "Введите номер квартиры (1 - 6): ";

                while (!(cin >> apartmentIndex) || (apartmentIndex < 1 || apartmentIndex > 6)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Некорректный ввод. Пожалуйста, введите номер квартиры от 1 до 6: ";
                }
                apartmentIndex--;

                People newPerson;
                newPerson.inputPerson(); // Ввод данных нового жильца

                cout << "Информация о новом жильце:\n";
                newPerson.output();

                house.getApartments()[apartmentIndex].addTenant(newPerson);
                break;
            }
            case 2: {
                int tenantID;
                cout << "Введите ID жильца для удаления: ";

                while (!(cin >> tenantID)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Некорректный ввод. Пожалуйста, введите ID жильца: ";
                }
                house.removeTenantByID(tenantID);
                break;
            }
            default:
                cout << "Некорректный выбор.\n";
                break;
            }
            break;
        }
        case 3:
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "Некорректный выбор.\n";
            break;
        }

        // Очистка состояния ввода для предотвращения застревания
        cin.clear();
        cin.ignore(10000, '\n');

    } while (choice != 3);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    House house;
    menu(house);
    return 0;
}
