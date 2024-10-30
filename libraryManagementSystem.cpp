/* Library Management System | Adrian Dominic L. Tan | BSCS 1-A */
// Standard Library Headers
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <string>
#include <vector>
using namespace std;

class User { // Base Class [User]
protected:
    unique_ptr<string> name, age, contactNumber;

public:
    User(unique_ptr<string> userName, unique_ptr<string> userAge, unique_ptr<string> userContactNumber)
        : name(move(userName)), age(move(userAge)), contactNumber(move(userContactNumber)) { /* User Constructor */ }
};

class Member : public User { // Derived Class [Member << User]
protected:
    unique_ptr<string> id;

public:
    Member(unique_ptr<string> memberName, unique_ptr<string> memberAge, unique_ptr<string> memberContactNumber, unique_ptr<string> memberId)
        : User(move(name), move(age), move(contactNumber)), id(move(memberId)) { /* Member Constructor */ }
};

// Standard Template Library[STL] Containers
map<unique_ptr<string>, unique_ptr<string>> bookList;
map<unique_ptr<string>, unique_ptr<Member>> borrowHistory;
vector<unique_ptr<string>> returnHistory;

class Book { // Book Class
protected:
    // Basic Information
    unique_ptr<string> title, ISBN, genre, author;

    // Publication Details
    unique_ptr<string> publicationDate, edition;

    // Physical Details
    unique_ptr<string> language, description;
    unsigned int pageCount;

    // Library Book Information
    unsigned int borrowCount = 0;
    bool availability = true;

public:
    enum class Language {
        English = 1, // Index starts at 1
        Filipino,
        Japanese,
        French,
        Italian,
        German,
        Arabic,
        Chinese
    };

    /* VALIDATORS */
    // VALIDATOR: Basic Information
    void validateBookTitle(string &fileName) { // File Search
        do { // Error Loop
            // Prompt
            cout << "\nBook Title: ";
            getline(cin, fileName);

            // Error Handling: isEmpty
            if (fileName.empty() || isspace(fileName[0])) {
                cerr << "\nERROR | blank_title_input\n";
            }

        } while (fileName.empty());
    }

    string validateBookAuthor() {
        string inputAuthor;
        do { // Error Loop
            // Prompt
            cout << "\nAuthor: ";
            getline(cin, inputAuthor);

            // Error Handling: isEmpty
            if (inputAuthor.empty() || isspace(inputAuthor[0])) {
                cerr << "\nERROR | blank_author_input\n";
            }

        } while (inputAuthor.empty() || isspace(inputAuthor[0]));
        return inputAuthor;
    }

    string validateBookGenre() {
        string inputGenre;
        do { // Error Loop
            // Prompt
            cout << "\nGenre: ";
            getline(cin, inputGenre);

            // Error Handling: isEmpty
            if (inputGenre.empty() || isspace(inputGenre[0])) {
                cerr << "\nERROR | blank_genre_input\n";
            }

        } while (inputGenre.empty() || isspace(inputGenre[0]));
        return inputGenre;
    }

    string validateBookISBN() {
        string inputISBN;
        bool ISBNIsDigit;
        do { // Error Loop
            ISBNIsDigit = true;
            // Prompt
            cout << "\nISBN(10-digits): ";
            getline(cin, inputISBN);

            // Error Handling: isEmpty
            if (inputISBN.empty() || isspace(inputISBN[0])) {
                cerr << "\nERROR | blank_ISBN_input\n";
                continue;
            }

            // Error Handling: validLength
            if (inputISBN.length() != 10) {
                cerr << "\nERROR | ISBN_must_be_10_digits\n";
                continue;
            }

            // Loop Checking: isDigit
            for (char &c : inputISBN) {
                if (!isdigit(c)) {
                    ISBNIsDigit = false;
                    break;
                }
            }

            // Error Handling: isDigit
            if (!ISBNIsDigit) {
                cerr << "\nERROR | non_digit_ISBN_input\n";
            }

        } while (inputISBN.empty() || isspace(inputISBN[0]) || inputISBN.length() != 10 || !ISBNIsDigit);
        return inputISBN;
    }

    // Getter: ISBN
    string getISBN(const string &bookISBN) const {
        return bookISBN;
    }

    // VALIDATOR: Publication Details
    string validateBookPublicationDate() {
        string inputPublicationDate;
        bool isValidPublicationDate;
        do { // Error Loop
            isValidPublicationDate = true;
            // Prompt
            cout << "\nPublication Date(MM/DD/YYYY): ";
            getline(cin, inputPublicationDate);

            // Error Handling: isEmpty
            if (inputPublicationDate.empty() || isspace(inputPublicationDate[0])) {
                isValidPublicationDate = false;
                cerr << "\nERROR | blank_publication_date_input\n";
            }

            // Error Handling: validLength
            else if (inputPublicationDate.length() != 10) {
                isValidPublicationDate = false;
                cerr << "\nERROR | invalid_publication_date_length\n";
            }

            else {
                // Loop Checking: isValidDate
                for (size_t i = 0; i < inputPublicationDate.length(); i++) {
                    if (i == 2 || i == 5) {
                        // Error Handling: Date Separators(/)
                        if (inputPublicationDate[i] != '/') {
                            isValidPublicationDate = false;
                            cerr << "\nERROR | invalid_date_separators";
                            break;
                        }
                    }

                    // Error Handling: isDigit
                    else if (!isdigit(inputPublicationDate[i])) {
                        isValidPublicationDate = false;
                        cerr << "\nERROR | non_digit_publication_date_input\n";
                        break;
                    }
                }
            }

        } while (inputPublicationDate.empty() || isspace(inputPublicationDate[0]) || !isValidPublicationDate);
        return inputPublicationDate;
    }

    string validateBookEdition() {
        string inputBookEdition;
        bool isValidEdition;
        do { // Error Loop
            isValidEdition = true;
            // Prompt
            cout << "\nEdition(blank if not applicable): ";
            getline(cin, inputBookEdition);

            // Input Handling: isEmpty
            if (inputBookEdition.empty() || isspace(inputBookEdition[0])) {
                return "N/A";
            }

            // Error Handling: validLength
            if (inputBookEdition.length() > 2) {
                isValidEdition = false;
                cerr << "\nERROR | exceeded_edition_input_limit_of_two_digits";
            }

            // Loop Checking: isDigit
            for (char &c : inputBookEdition) {
                // Error Handling: isDigit
                if (!isdigit(c)) {
                    isValidEdition = false;
                    cerr << "\nERROR | non_digit_edition_input";
                    break;
                }
            }

        } while (!isValidEdition);
        return inputBookEdition;
    }

    // VALIDATOR: Physical Details
    string validateBookLanguage() {
        unsigned int languageIndex;
        string languageInput;
        bool isValidLanguage;
        // Display Book Languages[Common]
        cout << "\nEnglish[1] | Filipino[2] | Japanese[3] | French[4] | Italian[5] | German[6] | Arabic[7] | Chinese[8]";

        do { // Error Loop
            isValidLanguage = true;
            // Prompt
            cout << "\nLanguage: ";
            cin >> languageIndex;

            // Error Handling: isEmpty
            if (cin.fail()) {
                isValidLanguage = false;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cerr << "\nERROR | blank_language_input\n";
            }

            // Error Handling: outOfBoundsIndex
            else if (languageIndex < 1 || languageIndex > 8) {
                isValidLanguage = false;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cerr << "\nERROR | out_of_bounds_language_index\n";
            }

            // Conversion: indexToEnum
            if (isValidLanguage) {
                switch (languageIndex) {
                case 1:
                    languageInput = "English";
                    break;
                case 2:
                    languageInput = "Filipino";
                    break;
                case 3:
                    languageInput = "Japanese";
                    break;
                case 4:
                    languageInput = "French";
                    break;
                case 5:
                    languageInput = "Italian";
                    break;
                case 6:
                    languageInput = "German";
                    break;
                case 7:
                    languageInput = "Arabic";
                    break;
                case 8:
                    languageInput = "Chinese";
                    break;
                default:
                    // Error Handling: nonIndex
                    isValidLanguage = false;
                    cerr << "\nERROR | invalid_language_index\n";
                    break;
                }
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

        } while (!isValidLanguage);
        return languageInput;
    }

    unsigned int validateBookPageCount() {
        unsigned int inputPageCount;
        do { // Error Loop
            // Prompt
            cout << "\n# of Pages: ";
            cin >> inputPageCount;

            // Error Handling: isEmpty
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cerr << "\n ERROR | blank_page_count\n";
            }

        } while (cin.fail());
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return inputPageCount;
    }

    string validateBookContent() {
        string inputBookContent;
        bool isValidContent;
        do { // Error Loop
            isValidContent = true;
            // Prompt
            cout << "\nContent Must Be...: ";
            cout << "\n* 10 Words < Word Length < 300 Words";
            cout << "\n* Ending With '|': ";
            cout << "\nContent:\n";

            getline(cin, inputBookContent); // Input Content

            // Error Handling: isEmpty
            if (inputBookContent.empty() || isspace(inputBookContent[0])) {
                isValidContent = false;
                cerr << "\nERROR | blank_book_content\n";
                continue;
            }

            // Error Handling: No Sentinel
            if (inputBookContent.back() != '|') {
                isValidContent = false;
                cerr << "\nERROR | no_ending_'|'_symbol";
                continue;
            }

            inputBookContent.pop_back(); // Remove '|' Temporarily

            unsigned int wordCount = 0;
            bool isWord = false;

                // Loop Checking: Word Count
                for (size_t i = 0; i < inputBookContent.length(); i++) {
                    // Word Checking: Space Handling
                    if (inputBookContent[i] == ' ') {
                        if (isWord) {
                            isWord = false;
                        }

                        // Error Handling: Double Spaces
                        if (i + 1 < inputBookContent.length() && inputBookContent[i + 1] == ' ') {
                            isValidContent = false;
                            cerr << "\nERROR | double_spaces\n";
                            break;
                        }
                    }

                    // Word Checking: Afterspace Handling
                    else {
                        if (!isWord) {
                            isWord = true;
                            wordCount++; // Every After Whitespace
                        }
                    }
                }

                /*// Word Checking: Last Word
                if (isWord) {
                    wordCount++;
                }*/

                if (wordCount < 10 || wordCount > 301) { // Max Limit: 300 + 1 [Margin of Error]
                    isValidContent = false;

                    if (wordCount < 10) {
                        cerr << "\nERROR | under_description_length\n";
                    } else {
                        cerr << "\nERROR | exceeded_description_length\n";
                    }
                }

        } while (!isValidContent);
        return inputBookContent;
    }

    // VALIDATOR: Abstraction
    void validateBasicInformation(string &bookAuthor, string &bookGenre, string &bookISBN) {
        bookAuthor = validateBookAuthor();
        bookGenre = validateBookGenre();
        bookISBN = validateBookISBN();
    }

    void validatePublicationDetails(string &bookPublicationDate, string &bookEdition) {
        bookPublicationDate = validateBookPublicationDate();
        bookEdition = validateBookEdition();
    }

    void validatePhysicalDetails(string &bookLanguage, unsigned int &bookPageCount, string &bookContent) {
        bookLanguage = validateBookLanguage();
        bookPageCount = validateBookPageCount();
        bookContent = validateBookContent();
    }

    void validateLibraryBookInformation() {
        // validateBookBorrowCount();
        // validateBookAvailability();
    }

    // Error Handling: Book File Already Exists
    bool alreadyExists(const string &bookTitle) {
        for (const auto&  book : bookList) {
            if (*book.first == bookTitle) {
                return true;
            }
        }
        return false;
    }

    /* CONSTRUCTOR */
    // CONSTRUCTOR: Default
    Book()
        : title(make_unique<string>("")), author(make_unique<string>("")), genre(make_unique<string>("")), ISBN(make_unique<string>("")), publicationDate(make_unique<string>("")), edition(make_unique<string>("")), language(make_unique<string>("")), description(make_unique<string>("")), pageCount(0), borrowCount(0), availability(true) {}

    // CONSTRUCTOR: Initialization
    Book(unique_ptr<string> bookTitle,
         unique_ptr<string> bookAuthor,
         unique_ptr<string> bookGenre,
         unique_ptr<string> bookISBN,
         unique_ptr<string> bookPublicationDate,
         unique_ptr<string> bookEdition,
         unique_ptr<string> bookLanguage,
         unique_ptr<string> bookContent,
         unsigned int bookPageCount,
         unsigned int bookBorrowCount,
         bool bookAvailability)
        : title(move(bookTitle)), author(move(bookAuthor)), genre(move(bookGenre)), ISBN(move(bookISBN)), publicationDate(move(bookPublicationDate)), edition(move(bookEdition)), language(move(bookLanguage)), description(move(bookContent)), pageCount(bookPageCount), borrowCount(bookBorrowCount), availability(bookAvailability) {}

    // CONSTRUCTOR: Book File <- addBook();
    Book(const string &textDirectory) {
        string bookTitle;
        bool bookAlreadyExists;
        cout << "\n~ adding book...";

        // Prompt Book Title as File Name
        do {
            validateBookTitle(bookTitle);
            bookAlreadyExists = alreadyExists(bookTitle);

            if (!bookAlreadyExists) {
                ofstream openFile(textDirectory + "\\" + bookTitle + ".txt"); // Create File Path

                // Create Book: Book File is Accessable && Book File Doesn't Exist
                if (openFile) {
                    cout << "\n>> Book created successfully <<";
                    break;
                }

                // Error Message: Book File is Not Accessable
                else  {
                    cerr << "\nERROR | cannot_open_file\n";
                    break;
                }
            }

            // Error Message: Book File Already Exists
            else {
                cerr << "\nERROR | book_already_exists\n";
            }

        } while (bookAlreadyExists);
    }
};

class Library { // Library Class
protected:
    Book &bookReference; // Reference to Book

public:
    Library(Book &bookReference) : bookReference(bookReference) { /* Library Constructor */ }

    //  Getter: File Path
    string getFilePath(const string &bookTitle) const {
        return "C:\\CC202_LibraryManagementSystem\\txt_files\\" + bookTitle + ".txt";
    }

    /* FILE */
    // FILE: Locate
    void locateBookFile(bool &fileFound, const string &bookTitle) {
        cout << "\n>> locating book file...";
        string filePath = getFilePath(bookTitle);

        ifstream fileSearcher(filePath);

        // Error Handling: Accessable File
        if (!fileSearcher.is_open()) {
            fileFound = false;
            return;
        }

        fileFound = true;
        cout << "\nBook File Found!\n";
    }

    // FILE: Input
    void inputValidatedInformation(const string &filePath, const string &bookTitle, const string &bookAuthor, const string &bookGenre, const string &bookISBN, const string &bookPublicationDate, const string &bookEdition, const string &bookLanguage, const string &bookContent, const unsigned int &bookPageCount) {
        cout << "\n>> updating basic information in book file...";
        // Open File
        ofstream enterText(filePath);
        // Validation Message
        if (enterText.is_open()) {
            enterText << "BASIC INFORMATION |\n";
            enterText << "Title: " << bookTitle << "\n";
            enterText << "Author: " << bookAuthor << "\n";
            enterText << "Genre: " << bookGenre << "\n";
            enterText << "ISBN: " << bookISBN << "\n";
            enterText << "\nPUBLICATION INFORMATION |\n";
            enterText << "Publication Date: " << bookPublicationDate << "\n";
            enterText << "Edition: " << bookEdition << "\n";
            enterText << "\nPHYSICAL INFORMATION |\n";
            enterText << "Language: " << bookLanguage << "\n";
            enterText << "# of Pages: " << bookPageCount << "\n";
            enterText << "\nContent:\n" << bookContent << "\n";
        }
    }

    // FILE: Read
    void readBookFile(const string &bookTitle) {
        cout << "\n>> reading book file...";
        string line, filePath = getFilePath(bookTitle); // Getter
        ifstream bookFileReader(filePath); // Create Book File


        // Read Text File: Accessable File
        if (bookFileReader) {
            cout << "\nBook File Found!\n";
            while (getline(bookFileReader, line)) {
                cout << line << "\n";
            }
            bookFileReader.close();
        }

        // Error Handling: Inaccessable File
        else {
            cerr << "\nERROR | inaccessible_book_file";
        }
    }

    // >> [C]REATE Book [1]
    void createBook() {
        Book("C:\\CC202_LibraryManagementSystem\\txt_files");
    }

    // >> [R]EAD Book [2]
    void readBook() {
        string bookTitle, line;
        bool fileFound = true;
        cout << "\n~ reading book...";

        do { // Error Loop
            // Prompt
            cout << "\nBook Title: ";
            getline(cin, bookTitle);

            // Error Handling: isEmpty
            if (bookTitle.empty() || isspace(bookTitle[0])) {
                cerr << "\nERROR | blank_book_title_input";
            }

        } while (bookTitle.empty() || isspace(bookTitle[0]));

        string filePath = getFilePath(bookTitle); // Getter
        ifstream bookFileReader(filePath); // Create Book File

        // Read File: Accessable File
        if (bookFileReader) {
            cout << "\nBook File Found!\n\n";
            cout << "\nFile Name: " << bookTitle << ".txt";
            cout << "\n-------------------------CONTENT-------------------------|\n";

            while (getline(bookFileReader, line)) {
                cout << line << "\n";
            }

            cout << "---------------------------------------------------------|\n";
            bookFileReader.close();
        }

        // Error Handling: Accessable File
        else {
            cerr << "\nERROR | inaccessible_book_file";
        }
    }

    // >> [U]PDATE Book [3]
    void updateBook() {
        // Book Search Variables
        string bookTitle;
        bool fileFound;

        // Book File Variables
        string bookAuthor, bookGenre, bookISBN, bookPublicationDate, bookLanguage, bookContent, bookEdition;
        unsigned int bookPageCount, bookBorrowCount = 0, bookAvailability = true;

        cout << "\n~ updating book info...";
        do { // Error Loop
            // Prompt
            cout << "\nSearch Book | Title: ";
            getline(cin, bookTitle);

            if (bookTitle.empty() || isspace(bookTitle[0])) {
                cerr << "\nERROR | blank_book_title\n";
                continue;
            }

            locateBookFile(fileFound, bookTitle); // Search for File

            // Validate Information: Accessable File
            if (fileFound) {
                string filePath = getFilePath(bookTitle);
                cout << "\nBASIC INFORMATION |";
                bookReference.validateBasicInformation(bookAuthor, bookGenre, bookISBN);
                cout << "\nPUBLICATION INFORMATION |";
                bookReference.validatePublicationDetails(bookPublicationDate, bookEdition);
                cout << "\nPHYSICAL INFORMATION |";
                bookReference.validatePhysicalDetails(bookLanguage, bookPageCount, bookContent);
                // Input Validated Information to Book File
                inputValidatedInformation(filePath, bookTitle, bookAuthor, bookGenre, bookISBN, bookPublicationDate, bookEdition, bookLanguage, bookContent, bookPageCount);
                readBookFile(bookTitle);
                bookList[make_unique<string>(bookTitle)] = make_unique<string>(bookISBN);
            }

            // Error Handling: Accessable File
            else {
                cerr << "\nERROR | file_does_not_exist\n";
            }

        } while (bookTitle.empty() || isspace(bookTitle[0]) || !fileFound);
    }

    // >> [D]ELETE Book [4]
    void deleteBook() {
        string bookTitle;
        string filePath = getFilePath(bookTitle);
        cout << "\n~ deleting book...";

        do { // Error Loop
            // Prompt
            cout << "\nBook Title: ";
            getline(cin, bookTitle);

            // Error Handling: isEmpty
            if (bookTitle.empty() || isspace(bookTitle[0])) {
                cerr << "\nERROR | blank_book_title_input";
            }

        } while (bookTitle.empty() || isspace(bookTitle[0]));

        filePath = getFilePath(bookTitle); // Getter
        if (remove(filePath.c_str()) == 0) { // Converts File Path to C-Style String, Removes File Using File Path, Returns 0 or 1
            cout << "\nBook File Deleted!\n\n";

            for (const auto& book : bookList) {
                if (*book.first == bookTitle) {
                    bookList.erase(book.first);
                    break;
                }
            }
        }

        else {
            cerr << "\nERROR | file_does_not_exist";
        }
    }

    // >> Show Booklist [5]
    void showBookList() {
        cout << "\n~ showing book list...";

        // Loop Iteration: Display
        size_t counter = 1;
        for (const auto& book : bookList) {
            cout << "\n" << counter << ". " << *book.first << " [" << *book.second << "]";
            counter++;
        }
    }

    // >> Borrow Book [6]
    void borrowBook() {
        cout << "\n~ borrowing book...";
        string bookTitle;
        bool bookAlreadyExists = false;
        do { // Error Loop
            // Prompt
            cout << "\nBook Title: ";
            getline(cin, bookTitle);

            if (bookTitle.empty()) {
                cerr << "\nERROR | blank_book_title";
            }

        } while (bookTitle.empty());

        if (bookAlreadyExists) {
            string currentPath = "C:\\CC202_LibraryManagementSystem\\txt_files\\" + bookTitle + ".txt";
            string borrowedBookFolder = "C:\\CC202_LibraryManagementSystem\\txt_files\\borrowed_books\\" + bookTitle + ".txt";

            /*for (const auto& borrow : borrowHistory) {
                if (*borrow.first == bookTitle) {
                    bookAlreadyExists = true;
                    break;
                }
            }
            //map<unique_ptr<string>, unique_ptr<Member>> borrowHistory;*/

            // Error Handling:
            if (rename(currentPath.c_str(), borrowedBookFolder.c_str()) != 0) {
                cerr << "\nERROR | could_not_move_file";
            }

            else {
                cout << "\nSuccessfully borrowed: " << bookTitle;
            }
        }

        // Erorr Handling: bookExists
        else {
            cerr << "\nERROR | book_does_not_exist";
        }
    }
};

class Menu { // Menu Class: Recursive
protected:
    Library &libraryReference;

public:
    Menu(Library &libraryReference) : libraryReference(libraryReference) { /* Menu Constructor */ }

    /* MENU */
    // MENU: Display
    void displayMenu() {
        int choice;
        do {
            cout << "\n| LIBRARY MANAGEMENT SYSTEM |";
            cout << "\n[1] | Create Book";
            cout << "\n[2] | Update Book Information";
            cout << "\n[3] | Read Book";
            cout << "\n[4] | Delete Book";
            cout << "\n[5] | Show Booklist";
            cout << "\n[6] | Borrow Book";
            cout << "\n[7] | Return Book";
            cout << "\n[8] | Search Book";
            cout << "\n[9] | Borrow History";
            cout << "\n[10] | Return History";
            cout << "\n[11] | Register User";
            cout << "\n[12] | Exit";
            cout << "\n-> ";
            cin >> choice;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (choice) {
            case 1:
                libraryReference.createBook();
                break;
            case 2:
                libraryReference.updateBook();
                break;
            case 3:
                libraryReference.readBook();
                break;
            case 4:
                libraryReference.deleteBook();
                break;
            case 5:
                libraryReference.showBookList();
                break;
            case 6:
                libraryReference.borrowBook();
                break;
            case 7:
                // returnBook();//printBorrowHistory();
                break;
            case 8:
                // searchBook();//printReturnHistory();
                break;
            case 9:
                // searchBook();//printReturnHistory();
                break;
            case 10:
                // searchBook();//printReturnHistory();
                break;
            case 11:
                // searchBook();//printReturnHistory();
                break;
            case 12:
                cout << "\nProgram Exited.";
                return;
            default:
                cout << "\nInvalid Input. Please try again.";
                break;
            }
            backToMenu();
        } while (true);
    }

    // MENU: Return
    void backToMenu() {
        char choice;
        cout << "\nReturn to menu[y/n]?: ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            return;
        }

        else if (choice == 'n' || choice == 'N') {
            cout << "\nProgram Exited.";
            exit(0);
        }
        else {
            cout << "\nInvalid Input.\n";
            cin >> choice;
        }
    }
};

int main() {
    Book book; // Default Book Constructor for Library
    Library library(book); // Library Constructor for Menu
    unique_ptr<Menu> startProgram = make_unique<Menu>(library); // Function Wrapper: Smart Pointer -> Function
    startProgram->displayMenu(); // Start the Prgoram
    return 0;
}
