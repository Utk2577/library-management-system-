#include <iostream>
using namespace std;

const int MAX = 10;

class Book {
public:
    char name[21];
    char author[21];
    double price;
    bool isIssued;
    char issueDate[12];
    int holderCard;
    bool isActive;

    Book() {
        name[0] = '\0';
        author[0] = '\0';
        price = 0.0;
        isIssued = false;
        issueDate[0] = '\0';
        holderCard = -1;
        isActive = false;
    }
};

class Student {
public:
    char name[21];
    char schoolID[21];
    char mobile[16];
    bool isActive;

    Student() {
        name[0] = '\0';
        schoolID[0] = '\0';
        mobile[0] = '\0';
        isActive = false;
    }
};

class Library {
public:
    Book books[MAX];
    Student students[MAX];

    void clearInput() {
        cin.clear();
        cin.ignore(1000, '\n');
    }

    void addBook() {
        int acc;
        cout << "Enter Accession Number (1-10): ";
        cin >> acc;
        acc--;

        if (acc < 0 || acc >= MAX) { cout << "Invalid!\n"; return; }
        if (books[acc].isActive)   { cout << "Already exists!\n"; return; }

        cout << "Enter Book Name: ";
        cin >> ws; cin.getline(books[acc].name, 21);

        cout << "Enter Author: ";
        cin.getline(books[acc].author, 21);

        cout << "Enter Price: ";
        cin >> books[acc].price;

        books[acc].isActive = true;
        cout << "Book added!\n";
    }

    void deleteBook() {
        int acc;
        cout << "Enter Accession Number (1-10): ";
        cin >> acc;
        acc--;

        if (acc < 0 || acc >= MAX || !books[acc].isActive) { cout << "Book not found!\n"; return; }
        if (books[acc].isIssued) { cout << "Cannot delete! Book is issued.\n"; return; }

        books[acc].isActive = false;
        cout << "Book deleted!\n";
    }

    void listBooks() {
        cout << "\n===== BOOK LIST =====\n";
        for (int i = 0; i < MAX; i++) {
            if (books[i].isActive) {
                cout << "Acc: " << i + 1
                     << " | Name: "   << books[i].name
                     << " | Author: " << books[i].author
                     << " | Price: "  << books[i].price
                     << " | "         << (books[i].isIssued ? "Issued" : "Available")
                     << "\n";
            }
        }
    }

    void addStudent() {
        int card;
        cout << "Enter Card Number (1-10): ";
        cin >> card;
        card--;

        if (card < 0 || card >= MAX)  { cout << "Invalid!\n"; return; }
        if (students[card].isActive)  { cout << "Already exists!\n"; return; }

        cout << "Enter Student Name: ";
        cin >> ws; cin.getline(students[card].name, 21);

        cout << "Enter School ID: ";
        cin >> students[card].schoolID;

        cout << "Enter Mobile: ";
        cin >> students[card].mobile;

        students[card].isActive = true;
        cout << "Student added!\n";
    }

    void deleteStudent() {
        int card;
        cout << "Enter Card Number (1-10): ";
        cin >> card;
        card--;

        if (card < 0 || card >= MAX || !students[card].isActive) { cout << "Student not found!\n"; return; }

        for (int i = 0; i < MAX; i++) {
            if (books[i].isActive && books[i].isIssued && books[i].holderCard == card) {
                cout << "Cannot delete! Student has issued book.\n";
                return;
            }
        }

        students[card].isActive = false;
        cout << "Student deleted!\n";
    }

    void listStudents() {
        cout << "\n===== STUDENT LIST =====\n";
        for (int i = 0; i < MAX; i++) {
            if (students[i].isActive) {
                cout << "Card: " << i + 1
                     << " | Name: "      << students[i].name
                     << " | School ID: " << students[i].schoolID
                     << " | Mobile: "    << students[i].mobile
                     << "\n";
            }
        }
    }

    void issueBook() {
        int acc, card;
        cout << "Enter Accession Number (1-10): ";
        cin >> acc; acc--;

        if (acc < 0 || acc >= MAX || !books[acc].isActive) { cout << "Book not found!\n"; return; }
        if (books[acc].isIssued) { cout << "Book already issued!\n"; return; }

        cout << "Enter Card Number (1-10): ";
        cin >> card; card--;

        if (card < 0 || card >= MAX || !students[card].isActive) { cout << "Student not found!\n"; return; }

        cout << "Enter Issue Date (dd-mm-yyyy): ";
        cin >> books[acc].issueDate;

        books[acc].isIssued   = true;
        books[acc].holderCard = card;
        cout << "Book issued to " << students[card].name << "!\n";
    }

    void returnBook() {
        int acc;
        cout << "Enter Accession Number (1-10): ";
        cin >> acc; acc--;

        if (acc < 0 || acc >= MAX || !books[acc].isActive) { cout << "Book not found!\n"; return; }
        if (!books[acc].isIssued) { cout << "Book is not issued!\n"; return; }

        cout << "Returned by: " << students[books[acc].holderCard].name << "\n";

        books[acc].isIssued     = false;
        books[acc].holderCard   = -1;
        books[acc].issueDate[0] = '\0';
        cout << "Book returned!\n";
    }

    void run() {
        int choice;
        cout << "=== LIBRARY MANAGEMENT SYSTEM ===\n";

        do {
            cout << "\n--- MAIN MENU ---\n";
            cout << "1. Add Book\n";
            cout << "2. Delete Book\n";
            cout << "3. List Books\n";
            cout << "4. Add Student\n";
            cout << "5. Delete Student\n";
            cout << "6. List Students\n";
            cout << "7. Issue Book\n";
            cout << "8. Return Book\n";
            cout << "0. Exit\n";
            cout << "Choice: ";
            cin >> choice;

            if (!cin) { clearInput(); continue; }

            if      (choice == 1) addBook();
            else if (choice == 2) deleteBook();
            else if (choice == 3) listBooks();
            else if (choice == 4) addStudent();
            else if (choice == 5) deleteStudent();
            else if (choice == 6) listStudents();
            else if (choice == 7) issueBook();
            else if (choice == 8) returnBook();
            else if (choice == 0) cout << "Goodbye!\n";
            else                  cout << "Invalid choice!\n";

        } while (choice != 0);
    }
};

int main() {
    Library lib;
    lib.run();
    return 0;
}