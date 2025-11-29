#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Book {
private:
    string title;
    string author;
    int year;
    bool isAvailable;

public:
    Book(string t, string a, int y)
        : title(t), author(a), year(y), isAvailable(true) {
    }

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool getIsAvailable() const { return isAvailable; }

    void setAvailable(bool available) { isAvailable = available; }

    void display() const {
        cout << title << " - " << author;
        if (isAvailable) {
            cout << " [Есть в библиотеке]";
        }
        else {
            cout << " [Нет в библиотеке]";
        }
    }
};

class Reader {
private:
    string name;
    int readerId;

public:
    Reader(string n, int id) : name(n), readerId(id) {}

    string getName() const { return name; }
    int getReaderId() const { return readerId; }

    void display() const {
        cout << name;
    }
};

void printBookInfo(Book book) {
    cout << "Книга: ";
    book.display();
    cout << endl;
}

void printReaderInfo(const Reader& reader) {
    cout << "Читатель: ";
    reader.display();
    cout << endl;
}

void borrowBook(Reader& reader, Book& book) {
    if (book.getIsAvailable()) {
        book.setAvailable(false);
        cout << "Книгу взял ";
        reader.display();
        cout << ": ";
        book.display();
        cout << endl;
    }
    else {
        cout << "Книгу уже кто-то взял" << endl;
    }
}

void checkBookStatus(const Book& book, const Reader& reader) {
    cout << "Книга '";
    book.display();
    cout << "' у ";
    reader.display();
    if (book.getIsAvailable()) {
        cout << " - в библиотеке" << endl;
    }
    else {
        cout << " - на руках" << endl;
    }
}

Book createBook(string title, string author, int year) {
    Book newBook(title, author, year);
    return newBook;
}

void displayAllBooks(const vector<Book>& books) {
    cout << "\nСписок всех книг:" << endl;
    for (const Book& book : books) {
        book.display();
        cout << endl;
    }
}

int main() {
    setlocale(LC_ALL, "ru");

    cout << "Работа с библиотекой" << endl;

    Book book1("Война и мир", "Лев Толстой", 1869);
    Book book2("Преступление и наказание", "Достоевский", 1866);

    Reader reader1("Иван", 101);
    Reader reader2("Мария", 102);

    cout << "\n1. Показ книги (копия):" << endl;
    printBookInfo(book1);

    cout << "\n2. Показ читателя:" << endl;
    printReaderInfo(reader1);

    cout << "\n3. Выдача книги:" << endl;
    borrowBook(reader1, book1);

    cout << "\n4. Проверка книг:" << endl;
    checkBookStatus(book1, reader1);
    checkBookStatus(book2, reader2);

    cout << "\n5. Добавление новой книги:" << endl;
    Book newBook = createBook("1984", "Оруэлл", 1949);
    cout << "Новая книга: ";
    newBook.display();
    cout << endl;

    cout << "\n6. Все книги:" << endl;
    vector<Book> library = { book1, book2, newBook };
    displayAllBooks(library);

    cout << "\n7. Итоговое состояние:" << endl;
    book1.display();
    cout << endl;
    book2.display();
    cout << endl;

    return 0;
}