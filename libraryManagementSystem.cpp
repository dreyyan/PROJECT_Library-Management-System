// Library Management System
#include <algorithm>
#include <cctype>
#include <ctime>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <string>
#include <vector>
using namespace std;

class Book {
protected:
    // Basic Information
    unique_ptr<string> title, ISBN, genre, author;

    // Publication Details
    unique_ptr<string> publicationDate;
    unsigned int edition;

    // Physical Details
    unique_ptr<string>language, description;
    unsigned int pageCount;

    // Library Book Information
    unsigned int borrowCount = 0;
    bool availability = true;

public:
    // CONSTRUCTOR: Initialization
    Book(unique_ptr<string> bookTitle,
        unique_ptr<string>bookAuthor,
        unique_ptr<string>bookGenre,
        unique_ptr<string>bookISBN,
        unique_ptr<string>bookPublicationDate,
        unsigned int bookEdition,
        unique_ptr<string>bookLanguage,
        unique_ptr<string>bookDescription,
        unsigned int bookPageCount,
        unsigned int bookBorrowCount,
        bool bookAvailability)
    : title(move(bookTitle)), author(move(bookAuthor)), genre(move(bookGenre)), ISBN(move(bookISBN)), publicationDate(move(bookPublicationDate)), edition(bookEdition), language(move(bookLanguage)), description(move(bookDescription)), pageCount(bookPageCount), borrowCount(bookBorrowCount), availability(bookAvailability) {}

    // ENUM: Languages
    enum class Language {
        English = 1, // Index Starts at 1
        Filipino,
        Japanese,
        French,
        Italian,
        German,
        Arabic,
        Chinese
    };

    // VALIDATION: Basic Information
    string validateBookAuthor() {
        string inputAuthor;

        do { // Error Loop
            // Prompt
            cout << "\nAuthor: ";
            getline(cin, inputAuthor);

            // Error Handling: isEmpty
            if (inputAuthor.empty()) {
                cerr << "\nERROR | blank_author_input\n";
            }

        } while (inputAuthor.empty());
        return inputAuthor;
    }

    string validateBookGenre() {
        string inputGenre;
        do { // Error Loop
            // Prompt
            cout << "\nGenre: ";
            getline(cin, inputGenre);

            // Error Handling: isEmpty
            if (inputGenre.empty()) {
                cerr << "\nERROR | blank_genre_input\n";
            }

        } while (inputGenre.empty());
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
            if (inputISBN.empty()) {
                cerr << "\nERROR | blank_ISBN_input\n";
                continue;
            }

            // Error Handling: Length
            if (inputISBN.length() != 10) {
                cerr << "\nERROR | ISBN_must_be_10_digits\n";
                continue;
            }

            // Loop Checking: isDigit
            for (char& c : inputISBN) {
                if (!isdigit(c)) {
                    ISBNIsDigit = false;
                    break;
                }
            }

            // Error Handling: isDigit
            if (!ISBNIsDigit) {
                cerr << "\nERROR | non_digit_ISBN_input\n";
            }

        } while(inputISBN.empty() || inputISBN.length() != 10 || !ISBNIsDigit);
        return inputISBN;
    }

    // VALIDATION: Publication Details
    string validateBookPublicationDate() {
        string inputPublicationDate;
        bool isValidPublicationDate;
        do { // Error Loop
            isValidPublicationDate = true;

            // Prompt
            cout << "\nPublication Date(MM/DD/YYYY): ";
            getline(cin, inputPublicationDate);

            // Error Handling: isEmpty
            if (inputPublicationDate.empty()) {
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

        } while(inputPublicationDate.empty() || !isValidPublicationDate);
        return inputPublicationDate;
    }

    unsigned int validateBookEdition() {
        unsigned int inputBookEdition;
        do { // Error Loop
            // Prompt
            cout << "\nEdition: ";
            cin >> inputBookEdition;

            // Error Handling: isValid
            if (cin.fail()) {
                cin.clear(); // Remove Error Flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cerr << "\nERROR | non_digit_edition_input\n";
            }

            // Error Handling: isPositive
            else if (inputBookEdition < 1) {
                cerr << "\nERROR | non_positive_edition_input\n";
            }

        } while (cin.fail() || inputBookEdition < 1);
        return inputBookEdition;
    }

    string validateBookLanguage() {
        unsigned int languageIndex;
        string languageInput;
        bool isValidLanguage;
        // Display Common Book Languages
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
                switch(languageIndex) {
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

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cerr << "\n ERROR | blank_page_count\n";
            }
        } while (cin.fail());
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return inputPageCount;
    }

    string validateBookDescription() {
        string inputBookDescription;
        bool isValidDescription;
        do { // Error Loop
            isValidDescription = true;
            // Prompt
            cout << "\n|| 10 < Word Count < 20 ||";
            cout << "\nDescription:\n";
            getline(cin, inputBookDescription);

            // Error Handling: isEmpty
            if (inputBookDescription.empty()) {
                isValidDescription = false;
                cerr << "\nERROR | blank_book_description\n";
            }

            else {
                unsigned int wordCount = 0;
                bool isWord = false;
                // Loop Checking: Word Count
                for (size_t i = 0; i < inputBookDescription.length(); i++) {
                    // Word Checking: Space Handling
                    if (inputBookDescription[i] == ' ') {
                        if (isWord) {
                            isWord = false;
                        }

                        // Error Handling: Double Spaces
                        if (i + 1 < inputBookDescription.length() && inputBookDescription[i + 1] == ' ') {
                            isValidDescription = false;
                            cerr << "\nERROR | double_spaces\n";
                            break;
                        }
                    }

                    // Word Checking: Afterspace Handling | wordCount++ until next space
                    else {
                        if (!isWord) {
                            isWord = true;
                            wordCount++;
                        }
                    }
                }

                // Word Checking: Last Word
                if (isWord) {
                    wordCount++;
                }

                if (wordCount < 10 || wordCount > 20) {
                    isValidDescription = false;
                    cerr << "\nERROR | out_of_bounds_description_length\n";
                }
            }

        } while (!isValidDescription);
        return inputBookDescription;
    }

    // VALIDATION: File Search
    void validateBookTitle(string& fileName) {
        do { // Error Loop
            // Prompt
            cout << "\nBook Title: ";
            getline(cin, fileName);

            // Error Handling: isEmpty
            if (fileName.empty()) {
                cerr << "\nERROR | blank_title_input\n";
            }

        } while (fileName.empty());
    }

    // VALIDATION: Abstraction
    void validateBasicInformation(string& bookAuthor, string& bookGenre, string& bookISBN) {
        bookAuthor = validateBookAuthor();
        bookGenre = validateBookGenre();
        bookISBN = validateBookISBN();
    }

    void validatePublicationDetails(string& bookPublicationDate, unsigned int& bookEdition) {
        bookPublicationDate = validateBookPublicationDate();
        bookEdition = validateBookEdition();
    }

    void validatePhysicalDetails(string& bookLanguage, unsigned int& bookPageCount, string& bookDescription) {
        bookLanguage = validateBookLanguage();
        bookPageCount = validateBookPageCount();
        bookDescription = validateBookDescription();
    }

    void validateLibraryBookInformation() {
        //validateBookBorrowCount();
        //validateBookAvailability();
    }

    // [CREATE] CONSTRUCTOR: File Making
    Book(const string& textDirectory) {
        string fileName;
        cout << "\n~ adding book...";

        // Prompt Book Title as File Name
        validateBookTitle(fileName);
        ofstream openFile(textDirectory + "\\" + fileName + ".txt");

        // Validation Message
        if (openFile) {
            cout << "\n>> Book created successfully <<";
        } else {
            cerr << "\nERROR | book_not_created\n";
        }
    }

    // INPUT: Validation
    void inputValidatedInformation(const string& filePath, const string& bookTitle, const string& bookAuthor, const string& bookGenre, const string& bookISBN, const string& bookPublicationDate, const unsigned int& bookEdition, const string& bookLanguage, const string& bookDescription, const unsigned int& bookPageCount) {
        cout << "\n>> updating Basic Information to text...";

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
            enterText << "\nDescription:\n" << bookDescription << "\n";
        }
    }
};

class Library {
protected:
    Book& bookReference;
public:
    Library(Book& bookReference) : bookReference(bookReference) {}

    bool searchForFile(const string& bookTitle) {
        cout << "\nsearching for book...";
        string filePath = "C:\\CC202_LibraryManagementSystem\\txt_files\\" + bookTitle + ".txt";

        ifstream fileSearcher(filePath);

        // Error Handling: Accessable File
        if (!fileSearcher.is_open()) {
            return false;
        }

        cout << "\nBook File Found!\n";
        return true;
    }

    // [UPDATE] Update Book Information
    void updateBookInfo() {
        // Book Search Variables
        string bookTitle;
        bool fileFound;

        // Book File Variables
        string bookAuthor, bookGenre, bookISBN, bookPublicationDate, bookLanguage, bookDescription;
        unsigned int bookEdition, bookPageCount, bookBorrowCount = 0, bookAvailability = true;

        cout << "\n~ updating book info...";

        do { // Error Loop
            // Prompt
            cout << "\nSearch Book | Title: ";
            getline(cin, bookTitle);

            if (bookTitle.empty()) {
                cerr << "\nERROR | blank_book_title\n";
                continue;
            }

            // File Searching
            fileFound = searchForFile(bookTitle);

            if (fileFound) {
                string filePath = "C:\\CC202_LibraryManagementSystem\\txt_files\\" + bookTitle + ".txt"; // File Name
                cout << "\nBASIC INFORMATION |";
                bookReference.validateBasicInformation(bookAuthor, bookGenre, bookISBN);
                cout << "\nPUBLICATION INFORMATION |";
                bookReference.validatePublicationDetails(bookPublicationDate, bookEdition);
                cout << "\nPHYSICAL INFORMATION |";
                bookReference.validatePhysicalDetails(bookLanguage, bookPageCount, bookDescription);
                bookReference.inputValidatedInformation(filePath, bookTitle, bookAuthor, bookGenre, bookISBN, bookPublicationDate, bookEdition, bookLanguage, bookDescription, bookPageCount);
                //bookReference.readBookFile();
            }

            // Error Handling: Accessable File
            else {
                cerr << "\nERROR | file_does_not_exist\n";
            }

        } while (bookTitle.empty() || !fileFound);
    }
};

class Menu {
protected:
    Library& libraryReference;
public:
    Menu(Library& libraryReference) : libraryReference(libraryReference) {}

    void displayMenu() {
        int choice;
        do {
            cout << "\n| LIBRARY MANAGEMENT SYSTEM |";
            cout << "\n[1] | Add Book";
            cout << "\n[2] | Edit Book Info";
            cout << "\n[3] | Show Booklist";
            cout << "\n[4] | Borrow Book/s";
            cout << "\n[5] | Return Book/s";
            cout << "\n[6] | Search Book/s";
            cout << "\n[7] | Borrow History";
            cout << "\n[8] | Return History";
            cout << "\n[9] | Exit";
            cout << "\n-> ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch(choice) {
                case 1:
                    Book("C:\\CC202_LibraryManagementSystem\\txt_files");
                break;
                case 2:
                    libraryReference.updateBookInfo();
                break;
                case 3:
                    //displayBookList();
                break;
                case 4:
                    //borrowBook();
                break;
                case 5:
                    //returnBook();
                break;
                case 6:
                    //searchBook();
                break;
                case 7:
                    //printBorrowHistory();
                break;
                case 8:
                    //printReturnHistory();
                break;
                case 9:
                    cout << "\nProgram Exited.";
                    return;
                default:
                    cout << "\nInvalid Input. Please try again.";
                break;
            }
            backToMenu();
        } while(true);
    }

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
    Book book("C:\\CC202_LibraryManagementSystem\\txt_files");
    Library library(book);
    unique_ptr<Menu> startProgram = make_unique<Menu>(library);
    startProgram->displayMenu();
    return 0;
}
