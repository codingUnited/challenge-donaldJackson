//NAME-RISHU RAJAN
//REG. N0-2019PGCACA82

#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<ctime>
#include<sstream>
#include<map>
#include<set>
#include<chrono>        // system_clock
#include<iomanip>       // has std::put_time
using namespace std;

////////////////////////// Utilities //////////////////////////
/*
ReadInt takes in an a low and a high value, then prompts the user for a value. if the value is in the range [low, high], it returns the value. 
Otherwise, it prints an error message and recursively calls itself to prompt the user again.
*/
int ReadInt(int low, int high) {
    cout << "\nEnter number in range " << low << " - " << high << ": ";
    int value;

    cin >> value;

    if (low <= value && value <= high)
        return value;

    cout << "ERROR: invalid number...Try again\n";
    return ReadInt(low, high);
}


/*
ShowReadMenu takes in a string vector of choices, then for each choice, it prints a numbered option to the console. 
It then calls ReadInt to prompt the user for a choice and returns the result.
*/
int ShowReadMenu(const vector<string> &choices) {
    cout << "\nMenu:\n";
    for (int ch = 0; ch < (int) choices.size(); ++ch) {
        cout << "\t" << ch + 1 << ": " << choices[ch] << "\n";
    }
    return ReadInt(1, choices.size());
}


/*
This gets the current date and time as a string in the format "YYYY-MM-DD HH:MM:SS".
*/
string GetCurrentTimeDate() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    return ss.str();
}


/*
Book class, represents a book using 3 strings (ISBN, TITLE, AUTHOR) and a vector of strings (PAGES). 
It has getters and setters for each data member, a Read method to read book details from the user, and a ToString method to return the book title.
*/
class Book {
private:
    string isbn;
    string title;
    string author;
    vector<string> pages;

public:
    /*
    Read() prompts the user for the book's ISBN, title, author name, and the number of pages.
    It then reads each page's content and stores it in the pages vector.
    */
    void Read() {
        string str;

        cout << "Enter ISBN: ";
        cin >> str;
        SetIsbn(str);

        cout << "Enter Title: ";
        cin >> str;
        SetTitle(str);

        cout << "Enter Author Name: ";
        cin >> str;
        SetAuthor(str);

        cout << "Enter How many pages: ";
        int pages_count;
        cin >> pages_count;

        for (int page = 0; page < pages_count; ++page) {
            cout << "Enter page # " << page + 1 << ": ";
            cin >> str;
            pages.push_back(str);
        }
    }

    /*
    GetAuthor() returns the author of the book.
    SetAuthor() sets the author of the book.
    GetIsbn() returns the ISBN of the book.
    SetIsbn() sets the ISBN of the book.
    GetPages() returns the pages of the book.
    SetPages() sets the pages of the book.
    GetTitle() returns the title of the book.
    SetTitle() sets the title of the book.
    ToString() returns the title of the book.   
    */
    const string& GetAuthor() const {
        return author;
    }

    void SetAuthor(const string& author) {
        this->author = author;
    }

    const string& GetIsbn() const {
        return isbn;
    }

    void SetIsbn(const string& isbn) {
        this->isbn = isbn;
    }

    const vector<string>& GetPages() const {
        return pages;
    }

    void SetPages(const vector<string>& pages) {
        this->pages = pages;
    }

    const string& GetTitle() const {
        return title;
    }

    void SetTitle(const string& title) {
        this->title = title;
    }

    string ToString() {
        return title;
    }
};



/*
BookReadingSession represents a reading session for a book.
It has a pointer to a Book object, the current page number, and the last access date.
**Design Flaw:** Using a raw Book pointer is a bad design choice. If the original book is deleted by an admin, this pointer becomes a "dangling pointer" and accessing it will cause a crash. A better design would use the book's ISBN to look it up when needed.
*/


class BookReadingSession {
private:
    Book* book; 
    int current_page;
    string last_access_date;

public:
    /*
    BookReadingSession() is a default constructor initializing the book pointer to nullptr.
    */
    BookReadingSession() :
            BookReadingSession(nullptr) {
    }

    /*
    BookReadingSession(Book* book) initializes the book pointer, sets the current page to 0, 
    and sets the last access date to the current date and time.
    */
    BookReadingSession(Book* book) :
            book(book), current_page(0), last_access_date(GetCurrentTimeDate()) {
    }

    /*
    ToString() returns an object (oss.str) containing the book title, current page index, and last access date. 
    */
    string ToString() {
        ostringstream oss;
        oss << GetBook()->GetTitle() << " Page: " << PageIdxStr() << " - " << GetLastAccessDate();
        return oss.str();
    }

    /*
    getCurrentPageContent() returns the content of the current page of the book.
    */
    string GetCurrentPageContent() {
        return book->GetPages()[current_page];
    }

    /*
    Get's the book pointer.
    */
    const Book* GetBook() const {
        return book;
    }

    /*
    GetLastAccessDate() Returns the last access date.
    */
    const string& GetLastAccessDate() const {
        return last_access_date;
    }

    /*
    sets the last access date to the current date and time.
    */
    void ResetLastAccessDate() {
        last_access_date = GetCurrentTimeDate();
    }

    /*
    Returns the current page index.
    */
    int GetCurrentPage() const {
        return current_page;
    }

    /*
    Returns a string representing the current page index and total number of pages in the format "current_page/total_pages".
    */
    string PageIdxStr() {
        ostringstream oss;
        oss << GetCurrentPage() + 1 << "/" << book->GetPages().size();
        return oss.str();
    }

    /*
    NextPage() increments the current page index if it is less than the total number of pages minus one. (i.e. flip page)
    */
    void NextPage() {
        if (current_page < (int) book->GetPages().size() - 1)
            current_page++;
    }

    /*
    PreviousPage() decrements the current page index if it is greater than zero. (i.e. turn back to previous page)
    */
    void PreviousPage() {
        if (current_page > 0)
            current_page--;
    }
};



/*
User class represents the user of the system. 
They have private data members for user name, password, name, email, a boolean indicating if they are a library admin,
and a vector of pointers to BookReadingSession objects.
It has methods to read user details, get and set each data member, add a reading session, and convert the user details to a string.
*/
class User {
private:
    string user_name;
    string password;
    string name;
    string email;
    bool is_library_admin;

    vector<BookReadingSession*> reading_sessions;

public:
    /*
    A good practice for a manager class like this is to prevent copying, as it's unclear who would own the pointers after a copy. 
    This C++11 feature deletes the copy constructor and assignment operator.
    */
    User(const User&) = delete;
    void operator=(const User&) = delete;

    /*
    initializes the is_library_admin boolean to false. (not an admin by default)
    */
    User() {
        is_library_admin = false;
    }

    /*
    The destructor correctly deletes all the BookReadingSession objects that were created with 'new', preventing memory leaks for the sessions.
    */
    ~User() {
        cout << "Destructor User\n";
        for (auto &session : reading_sessions)
            delete session;

        reading_sessions.clear();
    }

    /*
    ToString() returns a string representation of the user details, including name, email, user name, and admin status.
    */
    string ToString() const {
        ostringstream oss;
        oss << "Name: " << user_name;
        if (IsLibraryAdmin())
            oss << " | Admin";
        oss << "\n";
        oss << "Email: " << email << "\n";
        oss << "User name: " << user_name << "\n";
        return oss.str();
    }

    /*
    Read() prompts the user for their username, password, name, and email. setting them using the corresponding setter methods.
    */
    void Read(const string &user_name) {
        SetUserName(user_name);

        string str;

        cout << "Enter password: ";
        cin >> str;
        SetPassword(str);

        cout << "Enter name: ";
        cin >> str;
        SetName(str);

        cout << "Enter email: ";
        cin >> str;
        SetEmail(str);
    }

    /*
    Getter and Setter methods for each data member.
    */
    const string& GetEmail() const {
        return email;
    }

    void SetEmail(const string& email) {
        this->email = email;
    }

    const string& GetName() const {
        return name;
    }

    void SetName(const string& name) {
        this->name = name;
    }

    const string& GetPassword() const {
        return password;
    }

    void SetPassword(const string& password) {
        this->password = password;
    }

    const string& GetUserName() const {
        return user_name;
    }

    void SetUserName(const string& userName) {
        user_name = userName;
    }
    
    /*
    Returns true if the user is a library admin, false otherwise.
    */
    bool IsLibraryAdmin() const {
        return is_library_admin;
    }
    
    /*
    Sets the is_library_admin boolean to the given value. i.e. 0 or 1 for false or true respectively.
    */
    void SetIsLibraryAdmin(bool isLibraryAdmin) {
        is_library_admin = isLibraryAdmin;
    }

    /*
    Returns a const reference to the vector of BookReadingSession pointers. 
    */
    const vector<BookReadingSession*>& GetReadingSessions() const {
        return reading_sessions;
    }

    /*
    AddReadingSession() creates a new reading session for the given book, adds it to the reading_sessions vector 
    and returns a pointer to the new session. The User object now owns this session pointer.
    */
    BookReadingSession* AddReadingSession(Book* book) {
        BookReadingSession* session = new BookReadingSession(book);
        reading_sessions.push_back(session);
        return session;
    }
};



/*
UsersManager class manages user accounts and sessions.
It has private data members for the current user and a map of usernames to User objects.
It has methods to load user data, access the system (login/signup), and add reading sessions for the current user.
*/
class UsersManager {
private:
    User* current_user = nullptr;
    map<string, User*> userame_userobject_map;

    /*
    FreeLoadedData() deletes all user objects in the map and clears the map. It also sets the current user to nullptr. 
    This is critical for preventing memory leaks when reloading the database.
    */
    void FreeLoadedData() {
        for (auto pair : userame_userobject_map) {
            delete pair.second;
        }
        userame_userobject_map.clear();
        current_user = nullptr;
    }

public:
    /*
    Constructor that initializes the current user to nullptr.
    */
    UsersManager() {
    }

    /*
    The destructor calls FreeLoadedData() to ensure all dynamically allocated User objects are cleaned up when the UsersManager is destroyed.
    */
    ~UsersManager() {
        cout << "Destuctor: UsersManager\n";
        FreeLoadedData();
    }
    
    UsersManager(const UsersManager&) = delete;
    void operator=(const UsersManager&) = delete;


    /*
    LoadDatabase() clears any existing user data and then creates two dummy users. 
    Because it calls FreeLoadedData() at the beginning, it safely prevents memory leaks even if called multiple times.
    */
    void LoadDatabase() {
        cout << "UsersManager: LoadDatabase\n";

        FreeLoadedData();
        // Some "Dummy Data" for simplicity
        User* user1 = new User();
        user1->SetUserName("Rishu");
        user1->SetPassword("82");
        user1->SetEmail("rishurajan57@gmail.com");
        user1->SetIsLibraryAdmin(true);
        user1->SetName("Rishu Rajan");
        userame_userobject_map[user1->GetUserName()] = user1;

        User* user2 = new User();
        user2->SetUserName("Rajan");
        user2->SetPassword("1999");
        user2->SetEmail("rajan@gmail.com");
        user2->SetIsLibraryAdmin(false);
        user2->SetName("Titu Kumar");
        userame_userobject_map[user2->GetUserName()] = user2;
    }

    /*
    AccessSystem() prompts the user to either login or sign up.
    It calls ShowReadMenu to display the options and get the user's choice.
    If the user chooses to login, it calls DoLogin(). If the user chooses to sign up, it calls DoSignUp().
    */
    void AccessSystem() {
        int choice = ShowReadMenu( { "Login", "Sign Up" });
        if (choice == 1)
            DoLogin();
        else
            DoSignUp();
    }

    /*
    DoLogin() prompts for username and password, finds the user in the map, and sets the current_user if successful.
    */
    void DoLogin() {
        LoadDatabase(); // This is safe to call here.

        while (true) {
            string user_name, pass;
            cout << "Enter user user_name & password: ";
            cin >> user_name >> pass;

            if (!userame_userobject_map.count(user_name)) {
                cout << "\nInvalid user user_name or password. Try again\n\n";
                continue;
            }
            User* user_exist = userame_userobject_map.find(user_name)->second;

            if (pass != user_exist->GetPassword()) {
                cout << "\nInvalid user user_name or password. Try again\n\n";
                continue;
            }
            current_user = user_exist;
            break;
        }
    }

    /*
    DoSignUp() prompts the user for a new username.
    **Bug:** The function attempts to call `current_user->Read(user_name)`, but `current_user` is a nullptr at this point. This will cause the program to crash due to a null pointer dereference. The function also fails to allocate a `new User()` for the sign-up process.
    */
    void DoSignUp() {
        string user_name;
        while (true) {
            cout << "Enter user name. (No spaces): ";
            cin >> user_name;

            if (userame_userobject_map.count(user_name))
                cout << "Already used. Try again\n";
            else
                break;
        }
        // CRASH HAPPENS HERE: current_user is nullptr.
        current_user->Read(user_name);
        userame_userobject_map[current_user->GetUserName()] = current_user;
    }

    /*
    AddReadingSession() creates a new reading session for the given book by calling the AddReadingSession() method of the current_user.
    It returns a pointer to the new BookReadingSession.
    */
    BookReadingSession* AddReadingSession(Book* book) {
        return current_user->AddReadingSession(book);
    }

    /*
    GetCurrentUser() returns a pointer to the current_user.
    */
    const User* GetCurrentUser() const {
        return current_user;
    }
};


/*
BooksManager class manages the collection of books. 
It has a private data member for a map of ISBNs to Book objects.
It has methods to load book data, add, update, delete, and get books by ISBN
*/
class BooksManager {
private:
    map<string, Book*> isbn_to_book_map;

    /*
    FreeLoadedData() deletes all book objects in the map and clears the map.
    */
    void FreeLoadedData() {
        for (auto pair : isbn_to_book_map) {
            delete pair.second;
        }
        isbn_to_book_map.clear();
    }

public:
    BooksManager() {
    }

    /*
    LoadDatabase() clears any existing book data and creates three dummy books.
    Because it calls FreeLoadedData() at the beginning, it safely prevents memory leaks.
    */
    void LoadDatabase() {
        cout << "BooksManager: LoadDatabase\n";
        FreeLoadedData();

        Book* book1 = new Book();
        book1->SetIsbn("00001");
        book1->SetAuthor("Rishu");
        book1->SetTitle("CPP By Rema Thareja");
        vector<string> pages1 = { "A C++", "B C++", "C C++", "D C++", "E C++" };
        book1->SetPages(pages1);
        AddBook(book1);

        Book* book2 = new Book();
        book2->SetIsbn("00002");
        book2->SetAuthor("Rajan");
        book2->SetTitle("Intro to Algorithm");
        vector<string> pages2 = { "A Algo", "B Algo", "C Algo", "D Algo", "E " };
        book2->SetPages(pages2);
        AddBook(book2);

        Book* book3 = new Book();
        book3->SetIsbn("00003");
        book3->SetAuthor("Rishu");
        book3->SetTitle("Data Structures in C++");
        vector<string> pages3 = { "A Data", "B Data", "C Data", "D Data", "E Data" };
        book3->SetPages(pages3);
        AddBook(book3);
    }

    BooksManager(const BooksManager&) = delete;
    void operator=(const BooksManager&) = delete;

    /*
    The destructor for BooksManager ensures all dynamically allocated Book objects are freed.
    */
    ~BooksManager() {
        cout << "Destuctor: BooksManager\n";
        FreeLoadedData();
    }

    /*
    AddBook() maps a book pointer to an ISBN.
    **Memory Leak Bug:** If a book with the same ISBN is added, the map overwrites the old pointer. The memory for the original Book object is never freed, causing a memory leak.
    */
    void AddBook(Book* book) {
        isbn_to_book_map[book->GetIsbn()] = book;
    }

    // These functions are not implemented.
    void UpdateBook(string isbn, Book* book) {
    }
    void DeleteBook(string isbn) {
    }
    Book* GetBook(string isbn) {
        return nullptr;
    }

    const map<string, Book*>& GetIsbnToBookMap() const {
        return isbn_to_book_map;
    }
    
    void SetIsbnToBookMap(const map<string, Book*>& isbnToBookMap) {
        isbn_to_book_map = isbnToBookMap;
    }

};

class UserView {
private:
    UsersManager &users_manager;
    BooksManager &books_manager;
public:
    /*
    Constructor that initializes the references to the UsersManager and BooksManager objects.
    */
    UserView(UsersManager & users_manager, BooksManager &books_manager) :
            users_manager(users_manager), books_manager(books_manager) {
    }

    /*
    Display() displays the user view menu and handles user input.
    It shows options to view profile, list reading history, list available books, and logout.
    */
    void Display() {
        const User* user = users_manager.GetCurrentUser();
        cout << "\n\nHello " << user->GetName() << " | User View\n";

        vector<string> menu;
        menu.push_back("View Profile");
        menu.push_back("List & Select from My Reading History");
        menu.push_back("List & Select from Available Books");
        menu.push_back("Logout");

        while (true) {
            int choice = ShowReadMenu(menu);
            if (choice == 1)
                ViewProfile();
            else if (choice == 2)
                ListReadingHistory();
            else if (choice == 3)
                ListAvailableBooks();
            else
                break;
        }
    }

    /*
    Displays the current user's profile information.
    */
    void ViewProfile() {
        const User* user = users_manager.GetCurrentUser();
        cout << "\n" << user->ToString() << "\n";
    }

    /*
    Displays the reading session for a given BookReadingSession.
    **Risk:** The function doesn't check if the 'session' pointer or the book within it are null before using them. If a book was deleted, this could cause a crash.
    */
    void DisplaySession(BookReadingSession* session) {
        vector<string> menu;
        menu.push_back("Next Page");
        menu.push_back("Previous Page");
        menu.push_back("Stop Reading");

        while (true) {
            cout << "Current Page: " << session->PageIdxStr() << "\n";
            cout << session->GetCurrentPageContent() << "\n";

            int choice = ShowReadMenu(menu);
            if (choice == 1)
                session->NextPage();
            else if (choice == 2)
                session->PreviousPage();
            else
                break;
        }
        session->ResetLastAccessDate();
    }

    /*
    ListReadingHistory() lists the current user's reading sessions and allows them to select one to view.
    */
    void ListReadingHistory() {
        int idx = 0;
        const auto& sessions = users_manager.GetCurrentUser()->GetReadingSessions();
        for (auto& session : sessions) {
            cout << ++idx << ": " << session->ToString() << "\n";
        }

        if (idx == 0)
            cout << "\nNo history. List books and start having fun\n";
        else {
            cout << "\nWhich session to open?: ";
            int choice = ReadInt(1, idx);
            DisplaySession(sessions[choice - 1]);
        }
    }

    /*
    Lists all available books from the BooksManager and allows the user to select one to read.
    **Bug:** If there are no books available, `idx` will be 0. The call to `ReadInt(1, 0)` creates an invalid range, causing an infinite loop because no input can satisfy the condition.
    */
    void ListAvailableBooks() {
        const map<string, Book*>& mp = books_manager.GetIsbnToBookMap();

        cout << "\nOur current book collection:\n";
        int idx = 0;
        for (const auto &pair : mp) {
            cout << "\t" << ++idx << " " << pair.second->ToString() << "\n";
        }

        cout << "\nWhich book to read?: ";
        int choice = ReadInt(1, idx);

        idx = 0;
        for (const auto &pair : mp) {
            if (++idx == choice) {
                BookReadingSession* session = users_manager.AddReadingSession(pair.second);
                DisplaySession(session);
                break;
            }
        }
    }
};

class AdminView {
private:
    UsersManager &users_manager;
    BooksManager &books_manager;
public:

    /*
    Constructor that initializes the references to the UsersManager and BooksManager objects.
    */
    AdminView(UsersManager &users_manager, BooksManager &books_manager) :
            users_manager(users_manager), books_manager(books_manager) {
    }

    /*
    Display() displays the admin view menu and handles user input.
    It shows options to view profile, add a book, and logout.
    */
    void Display() {
        const User* user = users_manager.GetCurrentUser();

        cout << "\n\nHello " << user->GetName() << " | Admin View\n";
        vector<string> menu;
        menu.push_back("View Profile");
        menu.push_back("Add Book");
        menu.push_back("Logout");

        while (true) {
            int choice = ShowReadMenu(menu);
            if (choice == 1)
                ViewProfile();
            else if (choice == 2)
                AddBook();
            else
                break;
        }
    }

    /*
    Displays the current user's profile information.
    */
    void ViewProfile() {
        const User* user = users_manager.GetCurrentUser();
        cout << "\n" << user->ToString() << "\n";
    }

    /*
    Prompts the admin for book details and adds a new book to the BooksManager.
    **Bug:** This function is the source of the memory leak in the `BooksManager`. It creates a new book but doesn't check for a duplicate ISBN before adding it. 
	Prepare for millions of the same book in memory if the admin keeps adding books with the same ISBN. LOL 
    */
    void AddBook() {
        Book *book = new Book();
        book->Read();
        books_manager.AddBook(book);
    }
};

class OnlineReaderSystem {
private:
    BooksManager *books_manager;
    UsersManager *users_manager;
    
    /*
    Loads the databases for users and books by calling their respective LoadDatabase() methods.
    */
    void LoadDatabase() {
        users_manager->LoadDatabase();
        books_manager->LoadDatabase();
    }

public:

    /*
    Constructor that initializes the BooksManager and UsersManager objects using 'new'.
    */
    OnlineReaderSystem() :
            books_manager(new BooksManager()), users_manager(new UsersManager()) {
    }

    /*
    The destructor correctly deletes the manager objects to prevent memory leaks.
    */
    ~OnlineReaderSystem() {
        cout << "Destuctor: OnlineReaderSystem\n";

        if (books_manager != nullptr) {
            delete books_manager;
            books_manager = nullptr;
        }
        if (users_manager != nullptr) {
            delete users_manager;
            users_manager = nullptr;
        }
    }

    /*
    Run() is the main loop of the system.
    It loads the databases, handles login/signup, and displays the correct view (Admin or User) based on the user's status.
    */
    void Run() {
        LoadDatabase();

        while (true) {
            users_manager->AccessSystem();

            // The views are created on the stack, so they are automatically
            // destroyed when this if/else block finishes. No memory leak here.
            if (users_manager->GetCurrentUser()->IsLibraryAdmin()) {
                AdminView view(*users_manager, *books_manager);
                view.Display();
            } else {
                UserView view(*users_manager, *books_manager);
                view.Display();
            }
        }
    }
};


/*
main() is the entry point of the program.
It creates an OnlineReaderSystem object and calls its Run() method to start the system.
*/
int main() {
    OnlineReaderSystem site;
    site.Run();

    return 0;
}