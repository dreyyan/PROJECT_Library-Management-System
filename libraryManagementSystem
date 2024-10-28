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
    void validateBookTitle(string& fileName) {
        do { // Error Loop
            // Prompt
            cout << "\nBook Title: ";
            getline(cin, fileName);

            // Error Handling: isEmpty
            if (fileName.empty()) {
                cout << "\nERROR | blank_title_input";
            }

        } while (fileName.empty());
    }

    void validateBookAuthor() {
        string inputAuthor;

        do { // Error Loop
            // Prompt
            cout << "\nAuthor: ";
            getline(cin, inputAuthor);

            // Error Handling: isEmpty
            if (inputAuthor.empty()) {
                cerr << "\nERROR | blank_author_input";
            }

        } while (inputAuthor.empty());
    }

    void validateBookGenre() {
        string inputGenre;
        do { // Error Loop
            // Prompt
            cout << "\nGenre: ";
            getline(cin, inputGenre);

            // Error Handling: isEmpty
            if (inputGenre.empty()) {
                cerr << "\nERROR | blank_genre_input";
            }

        } while (inputGenre.empty());
    }

    void validateBookISBN() {
        string inputISBN;
        bool ISBNIsDigit;
        do { // Error Loop
            ISBNIsDigit = true;

            // Prompt
            cout << "\nISBN(10-digits): ";
            getline(cin, inputISBN);

            // Error Handling: isEmpty
            if (inputISBN.empty()) {
                cerr << "\nERROR | blank_ISBN_input";
                continue;
            }

            // Error Handling: Length
            if (inputISBN.length() != 10) {
                cerr << "\nERROR | ISBN_must_be_10_digits";
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
                cerr << "\nERROR | non_digit_ISBN_input";
            }

        } while(inputISBN.empty() || inputISBN.length() != 10 || !ISBNIsDigit);
    }

    // VALIDATION: Publication Details
    void validateBookPublicationDate() {
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
                cerr << "\nERROR | blank_publication_date_input";
            }

            // Error Handling: validLength
            else if (inputPublicationDate.length() != 10) {
                isValidPublicationDate = false;
                cerr << "\nERROR | invalid_publication_date_length";
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
                        cerr << "\nERROR | non_digit_publication_date_input";
                        break;
                    }
                }
            }

        } while(inputPublicationDate.empty() || !isValidPublicationDate);
    }

    void validateBookEdition() {
        unsigned int inputBookEdition;
        do { // Error Loop
            // Prompt
            cout << "\nEdition: ";
            cin >> inputBookEdition;

            // Error Handling: isValid
            if (cin.fail()) {
                cin.clear(); // Remove Error Flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cerr << "\nERROR | non_digit_edition_input";
            }

            // Error Handling: isPositive
            else if (inputBookEdition < 1) {
                cerr << "\nERROR | non_positive_edition_input";
            }

        } while (cin.fail() || inputBookEdition < 1);
    }

    void validateBookLanguage() {
        string inputLanguage;
        // Display Common Book Languages
        cout << "\n|| English[1]|Filipino[2]|Japanese[3]|French[4]|Italian[5]|German[6]|Arabic[7]|Chinese[8] ||";

        do { // Error Loop
            // Prompt
            cout << "\nLanguage: ";
            getline(cin, inputLanguage);

            // Error Handling: isEmpty
            if (inputLanguage.empty()) {
                cerr << "\nERROR | blank_language_input";
            }

        } while (inputLanguage.empty());
    }

    // VALIDATION: Abstraction
    void validateBasicInformation() {
        string fileName;
        validateBookTitle(fileName);
        validateBookAuthor();
        validateBookGenre();
        validateBookISBN();
    }

    void validatePublicationDetails() {
        validateBookPublicationDate();
        validateBookEdition();
    }

    void validatePhysicalDetails() {
        validateBookLanguage();
        //validateBookDescription();
        //validateBookPageCount();
    }

    void validateLibraryBookInformation() {
        //validateBookBorrowCount();
        //validateBookAvailability();
    }

    // [CREATE] CONSTRUCTOR: File Making
    Book(const string& textDirectory) {
        string fileName;
        cout << "\n~ creating book...";

        // Prompt Book Title as File Name
        validateBookTitle(fileName);
        ofstream openFile(textDirectory + "\\" + fileName + ".txt");

        // Validation Message
        if (openFile) {
            cout << "\n>> Book created successfully <<";
        } else {
            cerr << "\nERROR | book_not_created";
        }
    }
};

class Library {
protected:
public:
    // [UPDATE] Update Book Information
    void updateBookInfo() {
        cout << "\n~ updating book info...";
        cout << "\nBASIC INFORMATION |";

        cout << "\nPUBLICATION INFORMATION |";

        cout << "\nPHYSICAL INFORMATION |";
        /*
        unique_ptr<string> bookTitle,
        unique_ptr<string>bookAuthor,
        unique_ptr<string>bookGenre,
        unique_ptr<string>bookISBN,
        unique_ptr<string>bookPublicationDate,
        unsigned int bookEdition,
        unique_ptr<string>bookLanguage,
        unique_ptr<string>bookDescription,
        unsigned int bookPageCount,
        unsigned int bookBorrowCount,
        bool bookAvailability
        */
    }
};

int main() {
    Book("C:\\CC202_LibraryManagementSystem\\txt_files");
    return 0;
}
