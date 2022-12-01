// Crimson Bookstore Application
// Created by Sam Tombling: 31/10/2022


#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <fstream>

class Author;
class Publisher;
class Book;
class Order;
class Customer;

int publisherCount = 0;
int authorCount = 0;
int bookCount = 0;
int customerCount = 0;
int orderCount = 0;

enum bookGenre { CRIME, THRILLER, DRAMA, ROMANCE, SCIFI };

std::vector<Publisher*> publishers;
std::vector<Author*> authors;
std::vector<Customer*> customers;
std::vector<Book*> allBooks;
std::vector<Order*> allOrders;

std::ofstream bookFile("books.txt");

std::string getGenre(int choice) {
    switch (choice) {
    case 0:
        return "Crime";
    case 1:
        return "Thriller";
    case 2:
        return "Drama";
    case 3:
        return "Romance";
    case 4:
        return "SCIFI";
    }
}


class Publisher {
    int publisherId;
    std::string publisherName;
    std::string address[5];

public:

    Publisher(std::string publisherName, std::string address[]) {
        publisherId = publisherCount;
        publisherCount++;
        this->publisherName = publisherName;
        for (int i = 0; i < 5; i++) {
            this->address[i] = address[i];
        }
    }

    void printPublisher() {
        std::cout << "---- Publisher Details ----\n" << "ID: " << publisherId << "\nPublisher Name: " << publisherName << "\nAddress: " << address[0] << ", " << address[1] << ", " << address[2] << ", " << address[3] << ", " << address[4] << std::endl;
    }

    std::string getPublisherName() {
        return publisherName;
    }

    int getId() {
        return publisherId;
    }

    std::string getCity() {
        return address[1];
    }
};

class Author {
    int authorId;
    std::string fullName;
    std::string address[5];
    std::vector<Book*> booksReleased;

public:

    Author(std::string fullName, std::string address[]) {
        authorId = authorCount;
        authorCount++;
        this->fullName = fullName;
        for (int i = 0; i < 5; i++) {
            this->address[i] = address[i];
        }
    }

    void printAuthor() {
        std::cout << "---- Author Details ----\n" << "ID: " << authorId << "\nName: " << fullName << "\nAddress: " << address[0] << ", " << address[1] << ", " << address[2] << ", " << address[3] << ", " << address[4] << std::endl;
    }

    std::string getAuthorName() {
        return fullName;
    }

    int getId() {
        return authorId;
    }

    void releaseBook(Book* newBook) {
        booksReleased.push_back(newBook);
    }

    std::vector<Book*> getBooksReleased() {
        return booksReleased;
    }

    std::string getCity() {
        return address[1];
    }
};

class Book {
    int bookId;
    std::string bookName;
    Publisher* bookPublisher;
    Author* bookAuthor;
    bookGenre genre;
    static std::string storeSellerLabel;
    int price;
    int copiesSold = 0;

public:
    Book(std::string bookName, Publisher* bookPublisher, Author* bookAuthor, bookGenre genre, int price) {
        bookId = bookCount;
        bookCount++;
        this->bookName = bookName;
        this->bookPublisher = bookPublisher;
        this->bookAuthor = bookAuthor;
        this->genre = genre;
        this->price = price;
    }

    virtual void printBookSize() {};
    virtual std::string getBookType() {
        return "Error";
    }

    void printBookDetails() {
        std::cout << "---- Book Details ----" << "\nId: " << bookId << "\nBook Title: " << bookName << "\nAuthor: " << bookAuthor->getAuthorName() << "\nPublisher: " << bookPublisher->getPublisherName();
        std::cout << "\nGenre: " << getGenre(genre) << std::endl << std::endl;
    }

    int getId() {
        return bookId;
    }

    std::string getTitle() { return bookName; }

    int getPrice() {
        return price;
    }

    void addCopy() {
        copiesSold++;
    }

    int getCopiesSold() {
        return copiesSold;
    }

    static std::string getLabel() {
        return storeSellerLabel;
    }

    static void updateBrandLabel(std::string label) {
        storeSellerLabel = label;
    }

    void setBookDetails(std::string bookName, Publisher* bookPublisher, Author* bookAuthor, bookGenre genre, int price) {
        bookId = bookCount;
        bookCount++;
        this->bookName = bookName;
        this->bookPublisher = bookPublisher;
        this->bookAuthor = bookAuthor;
        this->genre = genre;
        this->price = price;
    }

    Author* getAuthor() {
        return bookAuthor;
    }

    Publisher* getPublisher() {
        return bookPublisher;
    }
};

class Order {
    int orderId;
    std::vector<Book*> books;
    int customerId;
    int cost;

public:

    Order(std::vector<Book*> books, int customerId) {
        orderId = orderCount;
        orderCount++;
        this->books = books;
        this->customerId = customerId;
        for (Book* book : books) {
            this->cost += book->getPrice();
        }
    }

    int getId() {
        return orderId;
    }

    double getCost() {
        double total = 0;
        for (Book* book : books) {
            total += book->getPrice();
        }

        return total;
    }

    std::vector<Book*> getBooks() {
        return books;
    }
};

class Customer {
    int customerId;
    std::string customerFirstName;
    std::string customerLastName;
    int age;
    std::string address[5];
    std::vector<Order*> orders;
    int totalSpending = 0;

public:

    Customer(std::string customerFirstName, std::string customerLastName, int age, std::string address[]) {
        customerId = customerCount;
        customerCount++;
        this->customerFirstName = customerFirstName;
        this->customerLastName = customerLastName;
        this->age = age;
        for (int i = 0; i < 5; i++) {
            this->address[i] = address[i];
        }
    }

    void printCustomer() {
        std::cout << "---- Customer Details ----\n" << "ID: " << customerId << "\nName: " << customerFirstName << " " << customerLastName << "\nAge: " << age << "\nAddress: " << address[0] << ", " << address[1] << ", " << address[2] << ", " << address[3] << ", " << address[4] << std::endl;
    }

    int getId() {
        return customerId;
    }

    void addOrder(Order* orders) {
        this->orders.push_back(orders);
        for (Order* order : this->orders) {
            for (Book* book : order->getBooks()) {
                totalSpending += book->getPrice();
            }
        }
    }

    int getTotalSpending() {
        return totalSpending;
    }

    std::string getFullname() {
        return customerFirstName + " " + customerLastName;
    }

    std::string getCity() {
        return address[1];
    }

    std::vector<Order*> getOrders() {
        return orders;
    }
};

class EBook : public Book {
    int size;

public:

    EBook(int size, std::string bookName, Publisher* bookPublisher, Author* bookAuthor, bookGenre genre, int price) : Book(bookName, bookPublisher, bookAuthor, genre, price){
        this->size = size;
    }
    void printBookSize() {
        std::cout << "Book size is: " << size << " GB";
    }
    std::string getBookType() {
        return "ebook";
    }
};

class PrintedBook : public Book {
    int noOfPages;

public:
    PrintedBook(int noOfPages, std::string bookName, Publisher* bookPublisher, Author* bookAuthor, bookGenre genre, int price) : Book(bookName, bookPublisher, bookAuthor, genre, price) {
        this->noOfPages = noOfPages;
    }
    void printBookSize() {
        std::cout << "Book size is: " << noOfPages << " pages";
    }
    std::string getBookType() {
        return "printed";
    }
};

std::string Book::storeSellerLabel = "Crimson BookStore";

void init() {
    //Initial Declarations

    std::string a1Address[] = { "24 Road", "Test City", "Herts", "EN10 0PP", "UK" };
    Author* a1 = new Author("JRR Tolkien", a1Address);
    authors.push_back(a1);
    std::string a2Address[] = { "29 Road", "Los Santos", "California", "S10 0EP", "USA" };
    Author* a2 = new Author("John Steinbeck", a2Address);
    authors.push_back(a2);
    std::string a3Address[] = { "15 Drive", "Liverpool", "Merseyside", "M34 9KL", "UK" };
    Author* a3 = new Author("George Orwell", a3Address);
    authors.push_back(a3);

    std::string c1Address[] = { "46 Street", "Test City", "Herts", "EN10 4LK", "UK" };
    Customer* c1 = new Customer("Sam", "Tombling", 26, c1Address);
    customers.push_back(c1);
    std::string c2Address[] = { "234 Hill", "Test Town", "Norfolk", "NR20 5GH", "UK" };
    Customer* c2 = new Customer("Izzy", "Haslam", 26, c2Address);
    customers.push_back(c2);
    std::string p1Address[] = { "34 Bench", "Test City", "London", "SW1 9RT", "UK" };
    Publisher* p1 = new Publisher("Penguin", p1Address);
    publishers.push_back(p1);
    std::string p2Address[] = { "789 Test Avenue", "Philidelphia", "PA", "PA6", "USA" };
    Publisher* p2 = new Publisher("Collins", p2Address);
    publishers.push_back(p2);

    /* Book* b1 = new Book("Lord of the Rings", p1, a1, SCIFI, 10);
     allBooks.push_back(b1);
     a1->releaseBook(b1);
     Book* b2 = new Book("East of Eden", p2, a2, DRAMA, 15);
     allBooks.push_back(b2);
     a2->releaseBook(b2);
     Book* b3 = new Book("1984", p1, a3, SCIFI, 12);
     allBooks.push_back(b3);
     a3->releaseBook(b3);*/

    Book* b1 = new EBook(10, "Lord of the Rings", p1, a1, SCIFI, 10);
    allBooks.push_back(b1);
    a1->releaseBook(b1);

    Book* b2 = new PrintedBook(500, "East of Eden", p2, a2, DRAMA, 15);
    allBooks.push_back(b2);
    a2->releaseBook(b2);

    Book* b3 = new PrintedBook(600, "1984", p1, a3, SCIFI, 12);
    allBooks.push_back(b3);
    a3->releaseBook(b3);

    std::vector<Book*> orderOne;
    orderOne.push_back(b1);
    b1->addCopy();
    orderOne.push_back(b2);
    b2->addCopy();
    std::vector<Book*> orderTwo;
    orderTwo.push_back(b2);
    b2->addCopy();
    orderTwo.push_back(b3);
    b3->addCopy();

    Order* o1 = new Order(orderOne, 0);
    c1->addOrder(o1);
    Order* o2 = new Order(orderTwo, 1);
    c2->addOrder(o2);
    allOrders.push_back(o1);
    allOrders.push_back(o2);

} //included

void findCustomerById() {
    int id;
    std::cout << "\n\nPlease enter the ID of the customer you would like to find: ";
    std::cin >> id;
    for (Customer* customer : customers) {
        if (id == customer->getId()) {
            customer->printCustomer();
            return;
        }
    }
    id = -1;
    try
    {
        if (id == -1)
            throw id;
    }
    catch (int id)
    {
        std::cout << "Invalid ID entered!";
    }

    return;
}

void printAllCustomers() {
    for (Customer* customer : customers) {
        customer->printCustomer();
        std::cout << std::endl;
    }
}

void findPublisherById() {
    int id;
    std::cout << "\n\nPlease enter the ID of the publisher you would like to find: ";
    std::cin >> id;
    for (Publisher* publisher : publishers) {
        if (id == publisher->getId()) {
            publisher->printPublisher();
            return;
        }
    }

    std::cout << "Publisher not found!\n\n";
    return;
}

void printAllPublishers() {
    for (Publisher* publisher : publishers) {
        publisher->printPublisher();
        std::cout << std::endl;
    }
}

void printBookById() {
    int id;
    std::cout << "\n\nPlease enter the ID of the book you would like to find: ";
    std::cin >> id;
    for (Book* book : allBooks) {
        if (book->getId() == id)
        {
            book->printBookDetails();
            return;
        }
    }
    std::cout << "Book not found!\n\n";
    return;
}

void displayDetails() {
    for (Book* book : allBooks) {
        book->printBookDetails();
        std::cout << std::endl;
    }
}

void getTotalSales() {
    double total = 0;
    for (Order* order : allOrders) {
        total += order->getCost();
    }
    std::cout << "Total Sales: " << total << std::endl << std::endl;
}

void bestSellingAuthor() {
    int maxSold = 0;
    Author* bestSeller = NULL;
    for (Author* author : authors) {
        int temp = 0;
        for (Book* book : author->getBooksReleased()) {
            if (book->getCopiesSold() > maxSold) {
                maxSold = book->getCopiesSold();
                bestSeller = author;
            }
        }
    }
    std::cout << "Best selling author is " << bestSeller->getAuthorName() << std::endl;
}

void getMostValuedCustomer() {
    int maxSpend = 0;
    Customer* topBuyer = NULL;
    for (Customer* customer : customers) {
        if (customer->getTotalSpending() > maxSpend) {
            maxSpend = customer->getTotalSpending();
            topBuyer = customer;
        }
    }

    std::cout << "Top buyer is: " << topBuyer->getFullname();
}

void beginTransaction() {
    std::vector<Book*> booksToBuy;
    std::cout << "---- Transaction Manager ----";
    printAllCustomers();
    std::cout << "Enter the purchaser's customer ID: ";
    int id;
    std::cin >> id;
    std::cout << "How many books would they like to buy?: ";
    int count;
    std::cin >> count;
    while (count > 0) {
        displayDetails();
        std::cout << "Enter the ID of the book they would like to buy: ";
        int bookId;
        std::cin >> bookId;
        for (Book* book : allBooks) {
            if (bookId == book->getId()) {
                booksToBuy.push_back(book);
            }
        }
        count--;
    }
    Order* newOrder = new Order(booksToBuy, id);
    for (Customer* customer : customers) {
        if (id == customer->getId()) {
            customer->addOrder(newOrder);
        }
    }
}

void analyseBookTrends() {
    int ebookCount = 0;
    int printedBookCount = 0;

    for (Book* book : allBooks) {
        if (book->getBookType() == "ebook") {
            ebookCount += book->getCopiesSold();
        }
        else {
            printedBookCount += book->getCopiesSold();
        }
    }

    if (ebookCount > printedBookCount) {
        std::cout << "Ebooks outsold printed books by " << ebookCount - printedBookCount << std::endl;
    }
    else if (printedBookCount > ebookCount) {
        std::cout << "Printed books outsold ebooks by " << printedBookCount - ebookCount << std::endl;
    }
    else {
        std::cout << "Printed books and eBooks sold equally" << std::endl;
    }
}

void identifyLocalSale() {
    std::string customerCity;
    std::string authorCity;
    std::string publisherCity;
    int noOfLocalSales = 0;

    for (Customer* customer : customers) {
        customerCity = customer->getCity();
        for (Order* order : customer->getOrders()) {
            for (Book* book : order->getBooks()) {
                Author* a = book->getAuthor();
                Publisher* p = book->getPublisher();
                authorCity = a->getCity();
                publisherCity = p->getCity();
                if ((customerCity == authorCity) && (customerCity == publisherCity)) {
                    noOfLocalSales++;
                }

            }
        }
    }

    std::cout << "Number of local sales = " << noOfLocalSales;
}

void addBook() {
    std::string name;
    int price;
    int authorId;
    int publisherId;
    Author* a = NULL;
    Publisher* p = NULL;
    int genreChoice;
    int bookType;
    bookGenre g;
    std::cout << "Enter the name of the book you would like to add: ";
    std::cin >> name;
    std::cout << "Enter the price of the book you would like to add: ";
    std::cin >> price;
    printAllPublishers();
    std::cout << "Enter the ID of the publisher of the book: ";
    std::cin >> publisherId;
    for (Publisher* publisher : publishers) {
        if (publisherId == publisher->getId())
            p = publisher;
    }
    std::cout << "Enter the ID of the author of the book: ";
    std::cin >> authorId;
    for (Author* author : authors) {
        if (authorId == author->getId())
            a = author;
    }
    std::cout << "Enter the genre of the book by number - 0(Crime), 1(THRILLER), 2(ROMANCE), 3(DRAMA), 4(SCIFI): ";
    std::cin >> genreChoice;
    switch (genreChoice) {
    case 0:
        g = CRIME;
        break;
    case 1:
        g = THRILLER;
        break;
    case 2:
        g = ROMANCE;
        break;
    case 3:
        g = DRAMA;
        break;
    case 4:
        g = SCIFI;
        break;
    default:
        std::cout << "Incorrect choice!";
        return;
    }
    std::cout << "Enter 1 for EBook, or 2 for paperback: ";
    std::cin >> bookType;

    if (bookType == 1) {
        int size;
        std::cout << "Enter the size of the book: ";
        std::cin >> size;
        Book* book = new EBook(size, name, p, a, g, price);
        a->releaseBook(book);
        allBooks.push_back(book);
    }
    else {
        int size;
        std::cout << "Enter the number of pages: ";
        std::cin >> size;
        Book* book = new PrintedBook(size, name, p, a, g, price);
        a->releaseBook(book);
        allBooks.push_back(book);
    }
    std::cout << "Book added successfully\n\n";
}

void addPublisher() {
    std::string name;
    std::string unit;
    std::string city;
    std::string region;
    std::string postcode;
    std::string country;

    std::cout << "Enter the publisher name: ";
    std::cin >> name;
    std::cout << "Enter the publisher's address - Unit: ";
    std::cin >> unit;
    std::cout << "Enter the publisher's address - city: ";
    std::cin >> city;
    std::cout << "Enter the publisher's address - region: ";
    std::cin >> region;
    std::cout << "Enter the publisher's address - postcode: ";
    std::cin >> postcode;
    std::cout << "Enter the publisher's address - country: ";
    std::cin >> country;

    std::string address[5] = { unit, city, region, postcode, country };
    Publisher* p = new Publisher(name, address);

    std::cout << "Publisher added!\n\n";
}

void addAuthor() {
    std::string fullName;
    std::string unit;
    std::string city;
    std::string region;
    std::string postcode;
    std::string country;

    std::cout << "Enter the author's full name: ";
    std::getline(std::cin, fullName);
    std::cout << "Enter the author's address - Unit: ";
    std::cin >> unit;
    std::cout << "Enter the author's address - city: ";
    std::cin >> city;
    std::cout << "Enter the author's address - region: ";
    std::cin >> region;
    std::cout << "Enter the author's address - postcode: ";
    std::cin >> postcode;
    std::cout << "Enter the author's address - country: ";
    std::cin >> country;

    std::string address[5] = { unit, city, region, postcode, country };
    Author* a = new Author(fullName, address);

    std::cout << "Author added!\n\n";
}

void addCustomer() {
    std::string firstName;
    std::string lastName;
    int age;
    std::string unit;
    std::string city;
    std::string region;
    std::string postcode;
    std::string country;

    std::cout << "Enter the customer's first name: ";
    std::cin >> firstName;
    std::cout << "Enter the customer's last name: ";
    std::cin >> lastName;
    std::cout << "Enter the customer's age: ";
    std::cin >> age;
    std::cout << "Enter the customer's address - Unit: ";
    std::cin >> unit;
    std::cout << "Enter the customer's address - city: ";
    std::cin >> city;
    std::cout << "Enter the customer's address - region: ";
    std::cin >> region;
    std::cout << "Enter the customer's address - postcode: ";
    std::cin >> postcode;
    std::cout << "Enter the customer's address - country: ";
    std::cin >> country;

    std::string address[5] = { unit, city, region, postcode, country };
    Customer* c = new Customer(firstName, lastName, age, address);

    std::cout << "Customer added!\n\n";
}

int main()
{
    init();
    std::cout << "---- BookStore App ----\n" << "Hello, and welcome to the bookstore app!\n";
    bool repeat = true;
    while (repeat) {
        std::cout << "\n\n\n\n---------------\n";
        std::cout << "Would you like to: \n";
        std::cout << "1. Create an Order\n2. Find a customer by id\n3. Print all customers\n4. Find a publisher by id\n5. Print all publishers\n6. Find a book by ID\n";
        std::cout << "7. Display all books\n8. Create an order\n9. Add a book\n10. Add a Publisher\n11. Add an author\n12. Add a customer\n13. Get total sales\n14. Display the best selling author";
        std::cout << "\n15. Find the most valued customer\n16. Analyse book trends\n17. Identify total number of local sales\n18. Exit";
        std::cout << "\nEnter choice: ";
        int choice;
        std::cin >> choice;
        switch (choice) {
        case 1:
            beginTransaction();
            break;
        case 2:
            findCustomerById();
            break;
        case 3:
            printAllCustomers();
            break;
        case 4:
            findPublisherById();
            break;
        case 5:
            printAllPublishers();
            break;
        case 6:
            printBookById();
            break;
        case 7:
            displayDetails();
            break;
        case 8:
            beginTransaction();
            break;
        case 9:
            addBook();
            break;
        case 10:
            addPublisher();
            break;
        case 11:
            addAuthor();
            break;
        case 12:
            addCustomer();
            break;
        case 13:
            getTotalSales();
            break;
        case 14:
            bestSellingAuthor();
            break;
        case 15:
            getMostValuedCustomer();
            break;
        case 16:
            analyseBookTrends();
            break;
        case 17:
            identifyLocalSale();
            break;
        case 18:
            repeat = false;
            break;
        default:
            std::cout << "Invalid option, please try again!\n";
        }
    }

    // Shows polymorphic printBookSize method
    /*for (Book* book : allBooks) {
        book->printBookSize();
    }*/

    // Changes static variable to something new
    /*std::cout << Book::getLabel();
    Book::updateBrandLabel("NewBookName");*/

    for (Book* book : allBooks) {
        bookFile << book->getId() << ": " << book->getTitle() << std::endl;
    }

    bookFile.close();
}

