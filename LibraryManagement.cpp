#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib> // for atoi
using namespace std;

struct Book {
    int id;
    string title;
    string author;
    string section;
    int floor;
    string category;
    string status;
};

// ------------------- Helper Functions -------------------
// Trim spaces
void trimStr(string &s) {
    while (!s.empty() && (s[0] == ' ' || s[0] == '\t')) s.erase(0,1);
    while (!s.empty() && (s[s.size()-1]==' ' || s[s.size()-1]=='\t' || s[s.size()-1]=='\r' || s[s.size()-1]=='\n'))
        s.erase(s.size()-1);
}

// Parse line to Book
Book parseBook(string line) {
    Book b;
    size_t p1 = line.find('|');
    size_t p2 = (p1 == string::npos) ? string::npos : line.find('|', p1+1);
    size_t p3 = (p2 == string::npos) ? string::npos : line.find('|', p2+1);
    size_t p4 = (p3 == string::npos) ? string::npos : line.find('|', p3+1);
    size_t p5 = (p4 == string::npos) ? string::npos : line.find('|', p4+1);
    size_t p6 = (p5 == string::npos) ? string::npos : line.find('|', p5+1);

    if (p1==string::npos || p2==string::npos || p3==string::npos || p4==string::npos || p5==string::npos || p6==string::npos) {
        b.id = -1; return b; // invalid line
    }

    string idStr = line.substr(0,p1);
    b.title = line.substr(p1+1, p2-p1-1);
    b.author = line.substr(p2+1, p3-p2-1);
    b.section = line.substr(p3+1, p4-p3-1);
    string floorStr = line.substr(p4+1, p5-p4-1);
    b.floor = atoi(floorStr.c_str());
    b.category = line.substr(p5+1, p6-p5-1);
    b.status = line.substr(p6+1);

    trimStr(idStr); trimStr(b.title); trimStr(b.author); trimStr(b.section);
    trimStr(b.category); trimStr(b.status);

    b.id = atoi(idStr.c_str());
    return b;
}

// Save vector to file
void saveBooks(vector<Book> &books) {
    ofstream outFile("books.txt");
    for (size_t i=0;i<books.size();i++) {
        outFile << books[i].id << " | " << books[i].title << " | "
                << books[i].author << " | " << books[i].section << " | "
                << books[i].floor << " | " << books[i].category << " | "
                << books[i].status << "\n";
    }
    outFile.close();
}

// ------------------- Classes -------------------
class library {
public:
    void menu() {
        ifstream inFile("books.txt");
        string line;
        int count = 0;
        cout << "\n--- Library Books ---\n";
        while (getline(inFile,line)) {
            if (line.empty()) continue;
            Book b = parseBook(line);
            if (b.id != -1) {
                cout << b.id << " | " << b.title << " | " << b.author
                     << " | Section: " << b.section
                     << " | Floor: " << b.floor
                     << " | Category: " << b.category
                     << " | Status: " << b.status << endl;
                count++;
            }
        }
        inFile.close();
        cout << "\nTotal number of books: " << count << endl;
    }
};

class staff: public library {
public:
    void DataEntry() {
        ofstream outFile("books.txt", ios::app);
        Book b;
        cout << "Enter Book ID: "; cin >> b.id; cin.ignore();
        cout << "Enter Book Title: "; getline(cin,b.title);
        cout << "Enter Author: "; getline(cin,b.author);
        cout << "Enter Section: "; getline(cin,b.section);
        cout << "Enter Floor: "; cin >> b.floor; cin.ignore();
        cout << "Enter Category: "; getline(cin,b.category);
        b.status = "Available";

        outFile << b.id << " | " << b.title << " | " << b.author
                << " | " << b.section << " | " << b.floor
                << " | " << b.category << " | " << b.status << "\n";
        outFile.close();
        cout << "Book added successfully!\n";
    }

    void searchBookById() {
        int id; cout << "Enter Book ID: "; cin >> id;
        ifstream inFile("books.txt"); string line; bool found=false;
        while(getline(inFile,line)) {
            if(line.empty()) continue;
            Book b = parseBook(line);
            if(b.id==id) {
                cout << "\nBook Found:\n";
                cout << "ID: " << b.id << "\nTitle: " << b.title
                     << "\nAuthor: " << b.author
                     << "\nSection: " << b.section
                     << "\nFloor: " << b.floor
                     << "\nCategory: " << b.category
                     << "\nStatus: " << b.status << endl;
                found=true;
                break;
            }
        }
        inFile.close();
        if(!found) cout << "Book not found!\n";
    }

    void totalBooks() {
        ifstream inFile("books.txt"); string line; int count=0;
        while(getline(inFile,line)) if(!line.empty()) count++;
        inFile.close();
        cout << "Total books: " << count << endl;
    }
};

class student: public library {
public:
    void borrowBook() {
        int id; cout << "Enter Book ID: "; cin >> id;
        ifstream inFile("books.txt"); vector<Book> books; string line;
        while(getline(inFile,line)) if(!line.empty()) books.push_back(parseBook(line));
        inFile.close();

        bool found=false;
        for(size_t i=0;i<books.size();i++) {
            if(books[i].id==id) {
                found=true;
                if(books[i].status=="Available") {
                    books[i].status="Issued"; saveBooks(books);
                    cout << "Book borrowed successfully!\n";
                } else {
                    cout << "Book is already issued!\n";
                }
                break;
            }
        }
        if(!found) cout << "Book not found!\n";
    }

    void returnBook() {
        int id; cout << "Enter Book ID: "; cin >> id;
        ifstream inFile("books.txt"); vector<Book> books; string line;
        while(getline(inFile,line)) if(!line.empty()) books.push_back(parseBook(line));
        inFile.close();

        bool found=false;
        for(size_t i=0;i<books.size();i++) {
            if(books[i].id==id) {
                found=true;
                if(books[i].status=="Issued") {
                    books[i].status="Available"; saveBooks(books);
                    cout << "Book returned successfully!\n";
                } else {
                    cout << "Book was not issued!\n";
                }
                break;
            }
        }
        if(!found) cout << "Book not found!\n";
    }
};

// ------------------- Main -------------------
int main() {
    int role, choice; student s; staff st;
    cout << "Choose your role:\n1. Student\n2. Staff\n"; cin >> role;

    if(role==1) {
        do {
            cout << "\n1. Book Menu\n2. Return a Book\n3. Borrow a Book\n4. Exit\n"; cin >> choice;
            if(choice==1) s.menu();
            else if(choice==2) s.returnBook();
            else if(choice==3) s.borrowBook();
        } while(choice!=4);
    } else if(role==2) {
        do {
            cout << "\n1. Book Menu\n2. Add Book\n3. Total Books\n4. Search Book by ID\n5. Exit\n"; cin >> choice;
            if(choice==1) st.menu();
            else if(choice==2) st.DataEntry();
            else if(choice==3) st.totalBooks();
            else if(choice==4) st.searchBookById();
        } while(choice!=5);
    } else cout << "Invalid role selected.\n";

    return 0;
}


