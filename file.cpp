#include <string>
#include <iostream>
using namespace std;
class Edition {
protected:
	string title;
	string author;
	int pages;
public:
	Edition (string t, string a, int p): title(t), author(a), pages(p) {}
	virtual ~Edition() {};
	virtual void showInfo() const = 0;
	virtual double cost() const = 0;
	virtual string type() const = 0;
};
class Book: public Edition {
private:
	string genre;
public:
	Book(string t, string a, int p, string g): Edition(t,a,p), genre(g) {}
	double cost() const override {
		return (200 + (2 * pages));
	}
	void showInfo() const override {
		cout << "Здесь инфа о книге";
	}
	string type() const override {
		return "Book type";
	}
};
class Magazine : public Edition {
private:
	int issueNumber;
public:
	Magazine(string t, string a, int p, int n): Edition(t,a,p), issueNumber(n) {}
	double cost() const override {
		return 150;
	}
	void showInfo() const override {
		cout << "Здесь инфа о журнале";
	}
	string type() const override {
		return "Magazine type";
	}
};
class Textbook: public Edition {
private:
	string subject;
public:
	Textbook(string t, string a, int p, string s): Edition(t,a,p), subject(s) {}
	double cost() const override {
		if (pages > 500) {
			return 300 - (300 * 0.15);
		}
		else return 300;
	}
	void showInfo() const override {
		cout << "Здесь инфа об учебнике";
	}
	string type() const override {
		return "Textbook type";
	}
};
int main()
{
	setlocale(LC_ALL, "Rus");
	int num, n, p;
	string t, a, ps, s;
	cin >> n;
	Edition** list = new Edition * [n];
	for (int i = 0; i < n; i++) {
		int choice;
		cin >> choice;
		cin.ignore();
		getline(cin, t);
		getline(cin, a);
		getline(cin, ps);
		p = stoi(ps);
		if (choice == 1) {
			getline(cin, s);
			list[i] = new Book(t, a, p, s);
		}
		else if (choice == 2) {
			string ns;
			getline(cin, ns);
			num = stoi(ns);
			list[i] = new Magazine(t, a, p, num);
		}
		else if (choice == 3) {
			getline(cin, s);
			list[i] = new Textbook(t, a, p, s);
		}
		else {
			cout << "Вы выбрали неверно. создадим Учебник" << endl;
			getline(cin, s);
			list[i] = new Textbook(t, a, p, s);

		}
	}
	cout << "Results:" << endl;
	for (int i=0; i < n; i++) {
		list[i]->showInfo();
		cout << list[i]->cost();
		cout << list[i]->type();
	}
	for (int i= 0; i < n; i++) {
		delete list[i];
	}
	delete[] list;
}
