#include <string>
#include <iostream>
#include <fstream> // Для работы с файлами

using namespace std;

// Классы Edition, Book, Magazine, Textbook остаются без изменений
class Edition {
protected:
    string title;
    string author;
    int pages;
public:
    Edition(string t, string a, int p) : title(t), author(a), pages(p) {}
    virtual ~Edition() {};
    virtual void showInfo() const = 0;
    virtual double cost() const = 0;
    virtual string type() const = 0;
};

class Book : public Edition {
    string genre;
public:
    Book(string t, string a, int p, string g) : Edition(t, a, p), genre(g) {}
    double cost() const override { return (200 + (2 * pages)); }
    void showInfo() const override { cout << "Книга: " << title << " | "; }
    string type() const override { return "Book type"; }
};

class Magazine : public Edition {
    int issueNumber;
public:
    Magazine(string t, string a, int p, int n) : Edition(t, a, p), issueNumber(n) {}
    double cost() const override { return 150; }
    void showInfo() const override { cout << "Журнал: " << title << " | "; }
    string type() const override { return "Magazine type"; }
};

class Textbook : public Edition {
    string subject;
public:
    Textbook(string t, string a, int p, string s) : Edition(t, a, p), subject(s) {}
    double cost() const override {
        return (pages > 500) ? 300 * 0.85 : 300;
    }
    void showInfo() const override { cout << "Учебник: " << title << " | "; }
    string type() const override { return "Textbook type"; }
};

int main() {
    setlocale(LC_ALL, "Rus");
    
    int n;
    cout << "Введите количество изданий: ";
    cin >> n;

    // --- ЗАПИСЬ В ФАЙЛ ---
    ofstream outFile("data.txt");
    if (!outFile) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        return 1;
    }

    outFile << n << endl; // Записываем количество в начало файла

    for (int i = 0; i < n; i++) {
        int choice, pages;
        string t, a, extra;
        
        cout << "Тип (1-Книга, 2-Журнал, 3-Учебник): ";
        cin >> choice;
        cin.ignore();
        cout << "Название: "; getline(cin, t);
        cout << "Автор: "; getline(cin, a);
        cout << "Стр: "; cin >> pages;
        cin.ignore();
        cout << "Доп. инфо (жанр/номер/предмет): "; getline(cin, extra);

        // Пишем в файл в строгом порядке
        outFile << choice << endl << t << endl << a << endl << pages << endl << extra << endl;
    }
    outFile.close();

    // --- ЧТЕНИЕ ИЗ ФАЙЛА ---
    ifstream inFile("data.txt");
    if (!inFile) {
        cerr << "Ошибка открытия файла для чтения!" << endl;
        return 1;
    }

    int countFromFile;
    inFile >> countFromFile;

    Edition** list = new Edition*[countFromFile];

    for (int i = 0; i < countFromFile; i++) {
        int choice, p;
        string t, a, extra;

        inFile >> choice;
        inFile >> ws; // Пропускаем пробелы/переносы перед getline
        getline(inFile, t);
        getline(inFile, a);
        inFile >> p;
        inFile >> ws;
        getline(inFile, extra);

        if (choice == 1) list[i] = new Book(t, a, p, extra);
        else if (choice == 2) list[i] = new Magazine(t, a, p, stoi(extra));
        else list[i] = new Textbook(t, a, p, extra);
    }
    inFile.close();

    // --- ВЫВОД РЕЗУЛЬТАТОВ ---
    cout << "\n--- Результаты из файла ---" << endl;
    for (int i = 0; i < countFromFile; i++) {
        list[i]->showInfo();
        cout << " Цена: " << list[i]->cost() << " | " << list[i]->type() << endl;
    }

    // Очистка памяти
    for (int i = 0; i < countFromFile; i++) delete list[i];
    delete[] list;

    return 0;
}
