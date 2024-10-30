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

// Current Time
time_t seconds = time(NULL);
struct tm timeFormat = *localtime(&seconds);

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
map<string, string> loginCredentials;
map<unique_ptr<string>, unique_ptr<string>> bookList;
map<unique_ptr<string>, unique_ptr<string>> borrowHistory;
map<unique_ptr<string>, unique_ptr<string>> returnHistory;

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
        cout << "\n| -Library-Management-System- |";
        cout << "\n-_-_-_-_-_-[ADD BOOK]-_-_-_-_-";

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

        cout << "\n| -Library-Management-System- |";
        cout << "\n-_-_-_-_-_-[READ BOOK]-_-_-_-_-";
        // Loop Iteration: Display
        size_t counter = 1;
        for (const auto& book : bookList) {
            cout << "\n" << counter << ". " << *book.first << " [" << *book.second << "]";
            counter++;
        }

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
        cout << "\n| -Library-Management-System- |";
        cout << "\n -_-_-[UPDATE BOOK INFO]-_-_-";

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
        cout << "\n| -Library-Management-System- |";
        cout << "\n-_-_-_-_-[DELETE BOOK]-_-_-_-_-";

        // Loop Iteration: Display
        size_t counter = 1;
        for (const auto& book : bookList) {
            cout << "\n" << counter << ". " << *book.first << " [" << *book.second << "]";
            counter++;
        }

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
        cout << "\n| -Library-Management-System- |";
        cout << "\n -_-_-_-_-[BOOK LIST]-_-_-_-_-";

        // Loop Iteration: Display
        size_t counter = 1;
        for (const auto& book : bookList) {
            cout << "\n" << counter << ". " << *book.first << " [" << *book.second << "]";
            counter++;
        }
    }

    // >> Borrow Book [6]
    void borrowBook() {
        string bookTitle;
        bool bookExists = false, bookAlreadyBorrowed = false;

        cout << "\n| -Library-Management-System- |";
        cout << "\n-_-_-_-_-[BORROW BOOK]-_-_-_-_-";
        // Loop Iteration: Display
        size_t counter = 1;
        for (const auto& book : bookList) {
            cout << "\n" << counter << ". " << *book.first << " [" << *book.second << "]";
            counter++;
        }

        do { // Error Loop
            // Prompt
            cout << "\nBook Title: ";
            getline(cin, bookTitle);

            if (bookTitle.empty()) {
                cerr << "\nERROR | blank_book_title";
            }

        } while (bookTitle.empty());

        // Loop Handling: bookExists
        for (const auto& book : bookList) {
            if (*book.first == bookTitle) {
                bookExists = true;
                break;
            }
        }

        if (!bookExists) {
            cerr << "\nERROR | book_does_not_exist";
            return;
        }

        // Loop Handling: isAlreadyBorrowed
        for (const auto& borrow : borrowHistory) {
            if (*(borrow.first) == bookTitle) {
                bookAlreadyBorrowed = true;
                break;
            }
        }

        if (bookAlreadyBorrowed) {
            cerr << "\nERROR | book_already_borrowed";
            return;
        }

        // Directories
        string currentPath = "C:\\CC202_LibraryManagementSystem\\txt_files\\" + bookTitle + ".txt";
        string borrowedBookFolder = "C:\\CC202_LibraryManagementSystem\\txt_files\\borrowed_books\\" + bookTitle + ".txt";

            // Error Handling: immovableFile
        if (rename(currentPath.c_str(), borrowedBookFolder.c_str()) != 0) {
            cerr << "\nERROR | could_not_move_file";
        }

        else {
            cout << "\nSuccessfully borrowed: " << bookTitle;
            borrowHistory[make_unique<string>(bookTitle)] = make_unique<string>("<borrowed>");
        }
    }

    // >> Return Book [7]
    void returnBook() {
        string bookTitle;
        bool bookExists, bookAlreadyReturned;

        cout << "\n| -Library-Management-System- |";
        cout << "\n-_-_-_-_-[RETURN BOOK]-_-_-_-_-";

        do { // Error Loop
            bookExists = false;
            bookAlreadyReturned = false;
            // Prompt
            cout << "\nBook Title: ";
            getline(cin, bookTitle);

            if (bookTitle.empty()) {
                cerr << "\nERROR | blank_book_title";
            }

        } while (bookTitle.empty());

        // Loop Handling: bookExists
        for (const auto& book : bookList) {
            if (*book.first == bookTitle) {
                bookExists = true;
                break;
            }
        }

        // Error Handling: fileDoesNotExist
        if (!bookExists) {
            cerr << "\nERROR | book_does_not_exist";
            return;
        }

        // Loop Handling: isAlreadReturned
        for (const auto& returned : returnHistory) {
            if (*(returned.first) == bookTitle) {
                bookAlreadyReturned = true;
                break;
            }
        }

        if (bookAlreadyReturned) {
            cerr << "\nERROR | book_already_returned";
            return;
        }

        // Directories
        string currentPath = "C:\\CC202_LibraryManagementSystem\\txt_files\\borrowed_books\\" + bookTitle + ".txt";
        string borrowedBookFolder = "C:\\CC202_LibraryManagementSystem\\txt_files\\" + bookTitle + ".txt";

        // Error Handling: immovableFile
        if (rename(currentPath.c_str(), borrowedBookFolder.c_str()) != 0) {
            cerr << "\nERROR | could_not_move_file";
        }

        else {
            cout << "\nSuccessfully returned: " << bookTitle;
            returnHistory[make_unique<string>(bookTitle)] = make_unique<string>("<returned>");
        }

        // Loop Iteration: Display
        size_t counter = 1;
        for (const auto& book : bookList) {
            cout << "\n" << counter << ". " << *book.first << " [" << *book.second << "]";
            counter++;
        }
    }

    // >> Search Book [8]
    void searchBook() {
        string bookTitle;
        bool bookExists;
        cout << "\n| -Library-Management-System- |";
        cout << "\n-_-_-_-_-[SEARCH BOOK]-_-_-_-_-";
        // Loop Iteration: Display
        size_t counter = 1;
        for (const auto& book : bookList) {
            cout << "\n" << counter << ". " << *book.first << " [" << *book.second << "]";
            counter++;
        }

        do {
            bookExists = false;
            // Prompt
            cout << "\nSearch Book | Book Title: ";
            getline(cin, bookTitle);

            // Error Handling: isEmpty
            if (bookTitle.empty() || bookTitle[0] == ' ') {
                cerr << "\nERROR | blank_book_title_input";
            }

        } while (bookTitle.empty() || bookTitle[0] == ' ');

        // Loop Handling: bookExists
        for (const auto& book : bookList) {
            if (*book.first == bookTitle) {
                bookExists = true;

                if (bookExists) {
                    int choice;
                    cout << "\nBook '" << bookTitle << "' found!" << " >> ISBN[" << *book.second << "]";

                    do {
                        cout << "\nShow Contents?: ";
                        cout << "\n[1] | Yes";
                        cout << "\n[2] | No";
                        cout << "\n---------";
                        cout << "\n>> ";
                        cin >> choice;

                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cerr << "\nERROR | invalid_input";
                        }
                    } while (cin.fail());

                    if (choice == 1) {
                        string line;
                        string filePath = getFilePath(bookTitle); // Getter
                        ifstream bookFileReader(filePath); // Create Book File

                        // Read File: Accessable File
                        if (bookFileReader) {
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

                    // Break Loop
                    else if (choice == 2) {
                        cout << "\nfinishing search...";
                        break;
                    }
                }
            }
        }
    }

    // >> Print Borrow History [9]
    void printBorrowHistory() {
        cout << "\n| -Library-Management-System- |";
        cout << "\n-_-_-_-[BORROW HISTORY]-_-_-_-";

        // Loop Handling: Print Borrow History
        for (const auto& bHistory : borrowHistory) {
            cout << "\n* " << *bHistory.first << "[" << *bHistory.second << "] borrowed | "
            << timeFormat.tm_mon + 1 << "/" << timeFormat.tm_mday << "/" << timeFormat.tm_year + 1900;
        }
    }

    /*time_t seconds = time(NULL);
    struct tm timeFormat = *localtime(&seconds);*/

    // >> Print Return History [9]
    void printReturnHistory() {
        cout << "\n| -Library-Management-System- |";
        cout << "\n-_-_-_-[RETURN HISTORY]-_-_-_-";

        // Loop Handling: Print Return History
        for (const auto& rHistory : returnHistory) {
            cout << "\n* " << *rHistory.first << "[" << *rHistory.second << "] returned | "
            << timeFormat.tm_mon + 1 << "/" << timeFormat.tm_mday << "/" << timeFormat.tm_year + 1900;
        }
    }
};

class Menu {
// Menu Class: Recursive
protected:
    Library &libraryReference;
public:
    Menu(Library &libraryReference) : libraryReference(libraryReference) { /* Menu Constructor */ }

    void displayRegisterMenu() {
        string username, password;
        bool isRegisteredUsername, isValidUsername, isValidPassword, onRegisterMenu;
        bool hasLetter, hasNumber;
        cout << "\n| -Library-Management-System- |";
        cout << "\n-_-_-_-_-_-[REGISTER]-_-_-_-_-";
        do { // Error Loop
            isRegisteredUsername = false, isValidUsername = true, hasLetter = false, hasNumber = false, onRegisterMenu = true;
            // Prompt
            cout << "\n[ Character Length: min. 5 / max. 15 | a-z, 1-3 | No Spaces ]";
            cout << "\nUsername: ";
            getline(cin, username);

            // Error Handling: isEmpty
            if (username.empty() || username[0] == ' ') {
                isValidUsername = false;
                cerr << "\nERROR | blank_username_input";
            }

            // Error Handling: validLength
            if (username.length() < 5 || username.length() > 15) {
                isValidUsername = false;
                if (username.length() < 5) {
                    cerr << "\nERROR | under_minimum_username_length";
                }

                else {
                    cerr << "\nERROR | exceeded_maximum_username_length";
                }
            }

            // Error Handling: isSpace
            for (size_t i = 0; i < username.length(); i++) {
                if (isspace(username[i])) {
                    isValidUsername = false;
                    cerr << "\nERROR | username_must_not_contain_spaces";
                    break;
                }

                // Counter: isLetter
                if (isalpha(username[i])) {
                    hasLetter = true;
                }

                // Counter: isNumber
                if (isdigit(username[i])) {
                    hasNumber = true;
                }

                // Error Handling: isCharacter
                if (!isalnum(username[i])) {
                    isValidUsername = false;
                    cerr << "\nERROR | username_must_not_contain_characters";
                    break;
                }
            }

            // Error Handling: noLetters
            if (!hasLetter) {
                isValidUsername = false;
                cerr << "\nERROR | username_must_contain_a_letter";
            }

            // Error Handling: noNumbers
            if (!hasNumber) {
                isValidUsername = false;
                cerr << "\nERROR | username_must_contain_a_number";
            }

            // Error Handling: isNotExisting
            for (const auto& existingUsername : loginCredentials) {
                if (existingUsername.first == username) {
                    isRegisteredUsername = true;
                    cerr << "\nERROR | username_already_registered";
                    break;
                }
            }

        } while (!isValidUsername);

        do { // Error Loop
            isValidPassword = true, hasLetter = false, hasNumber = false;
            // Prompt
            cout << "\n[ Character Length: min. 5 / max. 15 | a-z, 1-3 | No Spaces ]";
            cout << "\nPassword: ";
            getline(cin, password);

            // Error Handling: isEmpty
            if (password.empty() || password[0] == ' ') {
                isValidPassword = false;
                cerr << "\nERROR | blank_password_input";
            }

            // Error Handling: validLength
            if (password.length() < 5 || password.length() > 15) {
                isValidPassword = false;
                if (password.length() < 5) {
                    cerr << "\nERROR | under_minimum_password_length";
                }

                else {
                    cerr << "\nERROR | exceeded_maximum_password_length";
                }
            }

            // Error Handling: isSpace
            for (size_t i = 0; i < password.length(); i++) {
                if (isspace(password[i])) {
                    isValidPassword = false;
                    cerr << "\nERROR | password_must_not_contain_spaces";
                    break;
                }

                // Counter: isLetter
                if (isalpha(password[i])) {
                    hasLetter = true;
                }

                // Counter: isNumber
                if (isdigit(password[i])) {
                    hasNumber = true;
                }

                // Error Handling: isCharacter
                if (!isalnum(password[i])) {
                    isValidPassword = false;
                    cerr << "\nERROR | password_must_not_contain_characters";
                    break;
                }
            }

            // Error Handling: noLetters
            if (!hasLetter) {
                isValidPassword = false;
                cerr << "\nERROR | password_must_contain_a_letter";
            }

            // Error Handling: noNumbers
            if (!hasNumber) {
                isValidPassword = false;
                cerr << "\nERROR | password_must_contain_a_number";
            }

        } while (!isValidPassword);

        // Register Using Login Credentials
        loginCredentials[username] = password;

        cout << "\nuser '" << username << "' registered successfully!";
        int registerMenuChoice;

        do {
            cout << "\n| -Library-Management-System- |";
            cout << "\n-_-_-_-_-_-[REGISTER]-_-_-_-_-";
            cout << "\n------------------------";
            cout << "\nProceed to Login Page?";
            cout << "\n[1] | Yes";
            cout << "\n[2] | No";
            cout << "\n------------------------";
            cout << "\n>> ";
            cin >> registerMenuChoice;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (registerMenuChoice == 1) {
                onRegisterMenu = false;
                displayLoginMenu();
            }

            else if (registerMenuChoice == 2) {
                onRegisterMenu = false;
                displayMenu();
            }

        } while (onRegisterMenu);
    }

    void displayLoginMenu() {
        string username, password;
        bool usernameExists, correctPassword;
        cout << "\n| -Library-Management-System- |";
        cout << "\n-_-_-_-_-_-_-[LOGIN]-_-_-_-_-_-";
        do {
            // Error Loop
            usernameExists = false;
            // Prompt
            cout << "\nUsername: ";
            getline(cin, username);

            // Input Handling: usernameExists
            for (const auto& existingUsername : loginCredentials) {
                if (existingUsername.first == username) {
                    usernameExists = true;
                    break;
                }
            }

            // Error Handling: noExistingUsername
            if (!usernameExists) {
                cerr << "\nERROR | username_does_not_exist";
            }

        } while (!usernameExists);

        do { // Error Loop
            correctPassword = false;
            // Prompt
            cout << "\nPassword: ";
            getline(cin, password);

            // Input Handling: correctPassword
            if (loginCredentials[username] == password) {
                correctPassword = true;
            }

            // Error Handling: invalidPassword
            else {
                cerr << "\nERROR | invalid_password";
            }

        } while (!correctPassword);
        cout << "\nLogin Successful!";
        displayLibraryMenu();
    }

    void displayMenu() {
        int loginMenuChoice;
        do {
            cout << "\n| -Library-Management-System- |";
            cout << "\n-_-_-_-_-_-_-[MENU]-_-_-_-_-_-";
            cout << "\n---------------";
            cout << "\n[1] | Login";
            cout << "\n[2] | Register";
            cout << "\n[3] | Exit";
            cout << "\n---------------";
            cout << "\n>> ";
            cin >> loginMenuChoice;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch(loginMenuChoice) {
                case 1:
                    displayLoginMenu();
                break;
                case 2:
                    displayRegisterMenu();
                break;
                case 3:
                    cout << "\nexiting program...";
                    exit(0);
                break;
                default:
                    cerr << "Invalid Input. Please try again.";
                break;
            }

        } while(true);
    }

    /* MENU */
    // MENU: Display
    void displayLibraryMenu() {
        int choice;
        do {
            cout << "\n| -Library-Management-System- |";
            cout << "\n-_-_-_-_-_-[LIBRARY]-_-_-_-_-";
            cout << "\n---------------------------";
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
            cout << "\n[11] | Exit";
            cout << "\n---------------------------";
            cout << "\n>> ";
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
                libraryReference.returnBook();
                break;
            case 8:
                libraryReference.searchBook();
                break;
            case 9:
                libraryReference.printBorrowHistory();
                break;
            case 10:
                libraryReference.printReturnHistory();
                break;
            case 11:
                displayMenu();
                break;
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
    startProgram->displayMenu(); // Start Prgoram
    return 0;
}
