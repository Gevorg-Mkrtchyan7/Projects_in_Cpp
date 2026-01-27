#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Book{
    public:
        string title, author;

        Book(string t, string a) {
            title = t;
            author = a;
        }
};

class User{
    public:
        string username;
        string password;
        vector<Book> books;

        User(string u, string p) {
            username = u;
            password = p;
        }
};

void save(vector<User> &users) {
    ofstream userFile("Download.txt", ios::trunc);
    ofstream bookFile("Books.txt", ios::trunc);

    for (int i = 0; i < users.size(); i++) {
        userFile << users[i].username << endl;
        userFile << users[i].password << endl;

        for (int j = 0; j < users[i].books.size(); j++) {
            bookFile << users[i].username << endl;
            bookFile << users[i].books[j].title << endl;
            bookFile << users[i].books[j].author << endl;
        }
    }

    userFile.close();
    bookFile.close();
}

void load(vector<User> &users) {
    ifstream userFile("Download.txt");
    string name, password;

    while (getline(userFile, name) && getline(userFile, password)) {
        users.push_back(User(name, password));
    }
    userFile.close();

    ifstream bookFile("Books.txt");
    string username, bookName, bookAuthor;
    while (getline(bookFile, username) && getline(bookFile, bookName) && getline(bookFile, bookAuthor)) {
        for (int i = 0; i < users.size(); i++) {
            if (users[i].username == username) {
                users[i].books.push_back(Book(bookName, bookAuthor));
                break;
            }
        }
    }
    bookFile.close();
}

void allBooks(User &users){
    if(users.books.size() == 0){
        cout << "No books yet" << endl;
        return;
    }
    for(size_t i = 0; i < users.books.size(); i++){
        cout << users.books[i].title << " - " << users.books[i].author << endl;
    }
}

void getBook(User &users){
    string title, author;
    cout << "Enter the title of the book: ";
    getline(cin, title);
    bool t = true;
    for(size_t i = 0; i < users.books.size(); ++i){
        if(users.books[i].title == title){
            cout << users.books[i].title << " - " << users.books[i].author << endl;
            t = false;
            break;
        }
    }
    if(t){
        cout << "No books yet" << endl;
    }
}

void addBook(User &users){
    string title, author;
    cout << "Enter book's title: ";
    getline(cin, title);
    cout << "Enter Author's name: ";
    getline(cin, author);
    bool t = true;
    for(size_t i = 0; i < users.books.size(); ++i){
        if(users.books[i].title == title && users.books[i].author == author){
            cout << "The book already exists" << endl;
            t = false;
            break;
        }
    }
    if(t){
        Book b(title, author);
        users.books.push_back(b);
        cout << "The Book was added" << endl;
    }
}

void deleteBook(User &users){
    string title, author;
    cout << "Enter book's name: ";
    getline(cin, title);
    cout << "Enter book's author's name: ";
    getline(cin, author);
    for(size_t i = 0; i < users.books.size(); ++i){
        if(users.books[i].title == title && users.books[i].author == author){
            users.books.erase(users.books.begin() + i);
            cout << "Book has been deleted!" << endl;
            return;
        }
    }
    cout << "Incorrect name or author name entered!" << endl;
}

void deleteAccount(vector<User> &users, int n) {
    string str;
    cout << "Are you sure that you want to delete your account?(Enter <Yes> if you want or <No> if you don't want.): ";
    getline(cin, str);
    while(true){
        if (str == "Yes") {
            users.erase(users.begin() + n);
            cout << "Your account has been deleted!" << endl;
            break;
        }else if(str == "No"){
            break;
        }
    }
}

void func(vector<User> &users, int n){
    string command;
    while(1){
        do{
            cout << "Enter <All books> or <Get book> or <Add book> or <Delete book> or <Log out> or <Delete account>: ";
            getline(cin, command);
        }while(command != "All books" && command != "Get book" && command != "Add book" && command != "Log out" && command != "Delete book" && command != "Delete account");

        if(command == "All books"){
            allBooks(users[n]);
        }else if(command == "Get book"){
            getBook(users[n]);
        }else if(command == "Add book"){
            addBook(users[n]);
        }else if(command == "Delete book"){
            deleteBook(users[n]);
        }else if(command == "Delete account"){
            deleteAccount(users, n);
            break;
        }else{
            break;
        }
    }
}

bool isExist(vector<User> &users, string name, string password){
    for(size_t i = 0; i < users.size(); ++i){
        if(users[i].username == name){
            return false;
        }
    }
    return true;
}

int main(){
    vector<User> users;
    load(users);

    string command;
    while(1){
        do{
            cout << "Enter what you want(<Log in> or <Sign up> or <Exit>): ";
            getline(cin, command);
        }while(command != "Log in" && command != "Sign up" && command != "Exit");

        if(command == "Log in"){
            string name, password;
            cout << "Enter your username: ";
            getline(cin, name);
            cout << "Enter your password: ";
            getline(cin, password);
            bool t = true;
            for(int i = 0; i < users.size(); ++i){
                if(users[i].username == name && users[i].password == password){
                    func(users, i);
                    t = false;
                    break;
                }
            }
            if(t){
                cout << "Wrong name or password!" << endl;
            }
        }else if(command == "Sign up"){
            string name, password;
            cout << "Enter your username: ";
            getline(cin, name);
            cout << "Enter your password: ";
            getline(cin, password);
            if(isExist(users, name, password)){
                users.push_back(User(name, password));
                cout << "Registered!" << endl;
            }else{
                cout << "Already exist!" << endl;
            }
        }else{
            ofstream file("Library.txt");
            for(int i = 0; i < users.size(); ++i){
                file << "Username: " << users[i].username << "  " << "Password: " << users[i].password << endl;
                for(int j = 0; j < users[i].books.size(); ++j){
                    file << "Book: " << users[i].books[j].title << " - " << "Author: " << users[i].books[j].author << endl;
                }
                file << endl;
            }
            file.close();
            save(users);
            exit(0);
        }
    }
}
