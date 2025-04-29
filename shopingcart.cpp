#include<iostream>
#include<fstream>
#include<stdexcept>
#include<vector>
#include<conio.h>
#include<iomanip>
#include<windows.h>
#include "termcolor.hpp"

using namespace std; 

int const startingAccountNumber = 1000;
static int numberofuser = startingAccountNumber;
static int billNumber = 1000;

class Customer {
    string name;
    string phone_no;
    string email;
    string password;

public:
    Customer()  {}
    Customer(string name, string phone_no, string email, string password)
        : name(name), phone_no(phone_no), email(email), password(password) {}

    string get_name() const{ return name; }
    string get_password() const{ return password; }
    string get_email() const{ return email; }
    string get_phoneno() const{ return phone_no; }

    void update_phoneno(string phone_no) { this->phone_no = phone_no; }
    void update_email(string email) { this->email = email; }
    void update_password(string password) { this->password = password; }
    void update_name(string name) { this->name = name; }

    bool check_passwordclass(string password) {
        return password == this->password;
    }
    void view_profile() {
        cout << "\tname : " << name << endl;
        cout << "\tEmail : " << email << endl;
        cout << "\tphone_no : " << phone_no << endl;
    }
};
vector<Customer> customers;

class Product {
    string name;
    int price;
    int quantity;

public:
    Product() {}
    Product(string name, int price, int quantity) : name(name), price(price), quantity(quantity) {}

    string get_name() { return name; }
    int get_price() { return price; }
    int get_quantity() { return quantity; }

    void set_price(int price) { this->price = price; }
    void set_name(string name) { this->name = name; }
    void set_quantity(int quantity) { this->quantity = quantity; }
};

vector<Product> cart;

string setPassword() {
    string password;
    while (true) {
        password.clear();
        while (true) {
            char s = getch();
            if (!password.empty() && s == '\b') {
                cout << "\b \b";
                password.pop_back();
            } else if (s == '\r' || s == '\n') {
                if (password.empty()) {
                    cout << "\nPassword cannot be empty! Please enter a password." ;
                    break;
                } else {
                    return password;
                }
            } else {
                password += s;
                cout << "*";
            }
        }
    }
}

void saveCustomers() {

    try {
        ofstream file("customers.txt");
        if (!file.is_open()) {
            throw runtime_error("Unable to open customers.txt for writing");
        }
        for (const auto& customer : customers) {
            file << "name: " << customer.get_name() << endl;
            file << "phone_no: " << customer.get_phoneno() << endl;
            file << "email: " << customer.get_email() << endl;
            file << "password: " << customer.get_password() << endl;
            file << endl;
            // Check if write operation failed
            if (file.fail()) {
                throw runtime_error("Error writing to customers.txt");
            }
        }
        file.close();
        if (file.fail()) {
            throw runtime_error("Error closing customers.txt");
        }
    }
    catch (const std::runtime_error& e) {
        cout << "Error: " << e.what() << endl;
    }
    catch (const std::exception& e) {
        cout << "Unexpected error: " << e.what() << endl;
    }
    catch (...) {
        cout << "Unknown error occurred while saving customers" << endl;
    }
}

void loadCustomers() {
    ifstream file("customers.txt");
    if (!file.is_open()) {
        cout << "Error: Unable to open customers.txt for reading." << endl;
        return;
    }

    string line, name, phone_no, email, password;

    while (getline(file, line)) {
        if (line.find("name: ") == 0) {
            name = line.substr(6);
        } else if (line.find("phone_no: ") == 0) {
            phone_no = line.substr(10);
        } else if (line.find("email: ") == 0) {
            email = line.substr(7);
        } else if (line.find("password: ") == 0) {
            password = line.substr(10);
        } else if (line.empty()) {
            if (!name.empty() && !email.empty() && !password.empty()) {
                Customer customer(name, phone_no, email, password);
                customers.push_back(customer);
            }
            name.clear();
            phone_no.clear();
            email.clear();
            password.clear();
        }
    }

    if (!name.empty() && !email.empty() && !password.empty()) {
        Customer customer(name, phone_no, email, password);
        customers.push_back(customer);
    }

    file.close();
}


bool emailexistornot(string email) {
    for (const auto& customer : customers) {
        if (customer.get_email() == email)
            return true;
    }
    return false;
}

string validphonenumberchecker(string phoneNumber) {
    while (true) {
        bool isValid = true;
        if (phoneNumber.size() != 10 || phoneNumber.empty()) {
            isValid = false;
        } else {
            for (char c : phoneNumber) {
                if (c < '0' || c > '9') {
                    isValid = false;
                    break;
                }
            }
        }
        if (isValid) break;
        cout << termcolor::red;
        cout << "You entered an invalid number..." << endl;
        cout << termcolor::bright_cyan;
        cout << "\tEnter a valid number: ";
        cin >> phoneNumber;
        cout << termcolor::reset;
    }
    return phoneNumber;
}

string validemailchecker(string email) {
    while (true) {
        int es = email.size();
        int dot = 0, at = 0;
        bool valid = true;

        if (email == "0") {
            return "";
        }
        if (es < 5) {
            valid = false;
        } else {
            for (int i = 0; i < es; i++) {
                if (email[i] == '.') dot++;
                if (email[i] == '@') {
                    if (i == 0 || i == es - 1 || email[i + 1] == '.' || email[i - 1] == '.') {
                        valid = false;
                    } else {
                        at++;
                    }
                }
            }
            if (at != 1 || dot < 1 || email[es - 1] == '.' || email[es - 1] == '@') {
                valid = false;
            }
        }
        
        if (valid) {
            return email;
        } else {
            cout << termcolor::red;
            cout << "Invalid email format! (e.g., user@domain.com, or 0 to return): ";
            cout << termcolor::bright_cyan;
            cin >> email;
            cout << termcolor::reset;
        }
    }
}

bool checkforlogin() {
    system("CLS");
    cout << termcolor::magenta << termcolor::bold;
    cout << "\n\tWelcome To ShopSphere\n\n" << endl;
    cout << "\t1 : Login an account " << endl;
    cout << "\t2 : Create an account " << endl;
    cout << "\t3 : Exit" << "\n" << endl;
    cout << "\tSelect an Option : ";
    cout << termcolor::reset;
    while (true) {
        int choice;
        cin >> choice;
        system("CLS");
        if (choice == 1) return true;
        else if (choice == 2) return false;
        else if (choice == 3) exit(0);
        else cout << "\tSelect valid option : ";
    }
}

Customer& login(bool& loginflag) {
    system("CLS");
    cout << termcolor::bright_cyan << termcolor::bold;
    cout << "Login Section:\n\n";


    string email;
    int account_index = -1;

    while (true) {
        cout << termcolor::bright_cyan << termcolor::bold;

        cout << "Enter email address (or 0 to return to main menu): ";
        cin >> email;

        if (email == "0") {
            loginflag = false;
            return customers[numberofuser - startingAccountNumber];
        }
        if (email.empty()) {
            cout << termcolor::red;
            cout << "\nPlease enter an email address!" << endl;
            cout << termcolor::reset;
            continue;
        }

        email = validemailchecker(email);
        if (email.empty()) {
            loginflag = false;
            return customers[numberofuser - startingAccountNumber];
        }

        account_index = -1;
        for (int i = 0; i < customers.size(); i++) {
            if (email == customers[i].get_email()) {
                account_index = i;
                break;
            }
        }

        if (account_index == -1) {
            cout << termcolor::red;
            cout << "No account found with this email! Try again or enter 0 to return.\n" << endl;
            cout << termcolor::reset;
            continue;
        } else {
            break;
        }
    }

    string password;
    while (true) {
        cout << termcolor::bright_cyan << termcolor::bold;
        cout << "Enter password (or 0 to return to main menu): ";
        password = setPassword();
        cout << endl;

        if (password == "0") {
            loginflag = false;
            return customers[numberofuser - startingAccountNumber];
        }

        if (customers[account_index].check_passwordclass(password)) {
            system("CLS");
            cout << "\nLogged in successfully!" << endl;
            cout << "Press any key to continue...";
            getch();
            system("CLS");
            loginflag = true;
            return customers[account_index];
        } else {
            cout << termcolor::red;
            cout << "Incorrect password! Try again or enter 0 to return.\n" << endl;
            cout << termcolor::reset;
        }
    }
    cout << termcolor::reset;
    return customers[numberofuser - startingAccountNumber];
}

void create_account() {
    cin.ignore();
    cout << termcolor::bright_cyan;
    cout << "\tCreate an account : \n" << endl;
    string name, username, email, phone_no, address, password, confirm_password;

    cout << "\tEnter your name : ";
    getline(cin, name);
    cout << "\tEnter email address (or 0 to return to main menu): ";
    cin >> email;

    if (email == "0") {
        system("CLS");
        return;
    }

    while (true) {
        email = validemailchecker(email);
        if (email.empty()) { // User entered "0" or invalid email and chose to return
            system("CLS");
            return;
        }

        if (emailexistornot(email)) {
            cout << termcolor::red;
            cout << "Email already exists! Please enter a different email (or 0 to return): ";
            cout << termcolor::bright_cyan;
            cin >> email;
            if (email == "0") {
                system("CLS");
                return;
            }
        } else {
            break; // Email is valid and does not exist
        }
    }

    cout << termcolor::bright_cyan;
    cout << "\tEnter phone no : ";
    cin >> phone_no;
    phone_no = validphonenumberchecker(phone_no);

    while (true) {
        cout << termcolor::bright_cyan;
        cout << "\tEnter password : ";
        password = setPassword();
        cout << endl << "\tConfirm password : ";
        confirm_password = setPassword();
        if (password != confirm_password) {
            system("CLS");
            cout << termcolor::red;
            cout << endl << "\tPassword does not match! Please try again..." << endl;
            continue;
        } else {
            break;
        }
    }

    customers.push_back(Customer(name, phone_no, email, password));
    numberofuser++;
    saveCustomers();

    system("CLS");
    cout << endl << "\tAccount created successfully!" << endl;
    cout << "\tPress any key to continue...";
    getch();
    system("CLS");
}

void UpdateProfile(Customer& customer) {
    system("CLS");
    cout << "\tUpdate Profile Section:\n" << endl;
    cout << "\t1 : Update Name" << endl;
    cout << "\t2 : Update Phone Number" << endl;
    cout << "\t3 : Update Email" << endl;
    cout << "\t4 : Update Password" << endl;
    cout << "\t5 : Go Back" << endl;

    int choice;
    cout << "\tSelect an option: ";
    cin >> choice;

    switch (choice) {
        case 1: {
            string name;
            cout << "\tEnter new name: ";
            cin.ignore();
            getline(cin, name);
            customer.update_name(name);
            break;
        }
        case 2: {
            string phone_no;
            cout << "\tEnter new phone number: ";
            cin >> phone_no;
            customer.update_phoneno(phone_no);
            break;
        }
        case 3: {
            string email;
            cout << "\tEnter new email address: ";
            cin >> email;
            customer.update_email(email);
            break;
        }
        case 4: {
            string password, confirm_password;
            while (true) {
                cout << "\tEnter new password: ";
                password = setPassword();
                cout << endl << "\tConfirm new password: ";
                confirm_password = setPassword();
                if (password != confirm_password) {
                    system("CLS");
                    cout << endl << "\tPasswords do not match! Please try again..." << endl;
                    continue;
                } else {
                    customer.update_password(password);
                    break;
                }
            }
            break;
        }
        case 5:
            return;
        default:
            cout << "Invalid choice! Please try again." << endl;
    }

    saveCustomers();
}

vector<Product> electronics = {
    Product("Laptop", 55990, 10),
    Product("Smartphone", 12990, 20),
    Product("Headphones", 999, 15),
    Product("Tablet", 23000, 12),
    Product("Smartwatch", 1400, 18),
    Product("Bluetooth Speaker", 1550, 25),
    Product("Gaming Console", 44990, 8),
    Product("Wireless Mouse", 600, 30),
    Product("Keyboard", 650, 22),
    Product("Power Bank", 1199, 35)
};

vector<Product> footwear = {
    Product("Nike Shoes", 4950, 30),
    Product("Adidas Sneakers", 2199, 25),
    Product("Puma Sandals",1400 , 40),
    Product("Reebok Trainers", 2240, 20),
    Product("Vans Slip-ons", 3999, 25),
    Product("Formal Shoes", 850, 15),
    Product("Flip Flops", 300, 50),
    Product("Boots", 600, 10),
    Product("Loafers", 900, 18),
    Product("Crocs", 400, 35)
};

vector<Product> clothing = {
    Product("T-Shirt", 350, 50),
    Product("Jeans", 400, 30),
    Product("Jacket", 600, 20),
    Product("Sweater", 700, 25),
    Product("Hoodie", 500, 28),
    Product("Shorts", 250, 40),
    Product("Skirt", 300, 35),
    Product("Dress", 550, 22),
    Product("Tracksuit", 1000, 15),
    Product("Blazer", 800, 10)
};

vector<Product> accessories = {
    Product("Watch", 1500, 10),
    Product("Sunglasses", 250, 25),
    Product("Backpack", 600, 40),
    Product("Wallet", 250, 35),
    Product("Belt", 150, 30),
    Product("Cap", 130, 50),
    Product("Scarf", 110, 45),
    Product("Earrings", 50, 20),
    Product("Necklace", 300, 15),
    Product("Bracelet", 200, 18)
};

vector<Product> books = {
    Product("The Great Gatsby", 150, 100),
    Product("1984", 120, 80),
    Product("To Kill a Mockingbird", 340, 90),
    Product("The Alchemist", 260, 70),
    Product("Sapiens", 400, 50),
    Product("Atomic Habits", 260, 60),
    Product("Harry Potter", 375, 75),
    Product("The Hobbit", 400, 65),
    Product("Rich Dad Poor Dad", 500, 85),
    Product("The Psychology of Money", 390, 55)
};

vector<Product> sports = {
    Product("Football", 400, 40),
    Product("Basketball", 600, 35),
    Product("Yoga Mat", 300, 50),
    Product("Dumbbells (10kg)", 600, 15),
    Product("Tennis Racket", 1099, 20),
    Product("Skipping Rope", 325, 60),
    Product("Treadmill", 16000, 5),
    Product("Cycling Helmet", 1200, 25),
    Product("Resistance Bands", 300, 40),
    Product("Fitness Tracker", 400, 12)
};

vector<Product> health = {
    Product("Vitamins (60 tabs)", 300, 30),
    Product("First Aid Kit", 2000, 20),
    Product("Thermometer", 165, 25),
    Product("Blood Pressure Monitor", 1370, 10),
    Product("Hand Sanitizer", 35, 100),
    Product("Face Masks (50 pcs)", 250, 75),
    Product("Pain Relief Spray", 400, 40),
    Product("Cough Syrup", 120, 50),
    Product("Disinfectant Wipes", 50, 60),
    Product("Bandages", 5, 80)
};

vector<Product> groceries = {
    Product("Rice (5kg)", 350, 50),
    Product("Sugar (1kg)", 40, 100),
    Product("Flour (2kg)", 100, 80),
    Product("Cooking Oil (1L)", 100, 60),
    Product("Salt (1kg)", 10, 150),
    Product("Pasta (500g)", 70, 120),
    Product("Canned Beans", 175, 200),
    Product("Frozen Vegetables", 140, 90),
    Product("Spices Set", 400, 40),
    Product("Tea Bags (100 pcs)", 220, 70)
};

void selectProduct(vector<Product>& products) {
    cout << termcolor::bright_blue << termcolor::bold;
    int choice, quantity;
    int size = products.size();
    cout << size << endl;
    system("CLS");
        cout << left << setw(5) << "ID" << setw(35) << "Product" << setw(30) << "Price" << endl;
        cout << "-------------------------------------------" << endl;
        for (int i = 0; i < size ; i++) {
            cout << setw(5) << i + 1 << setw(35) << products[i].get_name() << setw(30) << products[i].get_price() << endl;
        }

        cout << "\nEnter 0 to go back : " << endl;
    while (true) {
        cout << termcolor::bright_blue << termcolor::bold;
        cout << "\nEnter your choice: ";
        while (!(cin >> choice) || (choice < 0 || choice > size )) { 
            cout << termcolor::red;
            cout << "Invalid choice! Please enter a valid option: ";
            cout << termcolor::reset;
            cin.clear();  // Clear error flag
            cin.ignore(1000, '\n');  // Ignore invalid input
        }
        if (choice == 0) {
            cout << termcolor::reset;
            return;  // Exit product selection
        }
        cout << termcolor::bright_blue << termcolor::bold;
        cout << "Enter quantity: ";
        cin >> quantity;

        if (quantity <= 0 ) {
            cout << termcolor::red;
            cout << "\nInvalid quantity! Please enter a valid quantity." << endl;
            cout << termcolor::reset;
            cin.clear();
            cin.ignore(1000, '\n');  // Ignore invalid input
        }
        cout << termcolor::bright_blue << termcolor::bold;
        if(quantity > products[choice - 1].get_quantity()) {
            cout << termcolor::red;
            cout << "Sorry, We have Not enough stock available! Please enter a valid quantity." << endl;
            cout << termcolor::reset;
            cout << termcolor::bright_grey;
            cout << "Available quantity: " << products[choice - 1].get_quantity() << endl;
            cout << termcolor::reset;
            cin.clear();
            cin.ignore(1000, '\n');  // Ignore invalid input  
        }

        bool found = false;

        for (auto &item : cart) {
            if (item.get_name() == products[choice - 1].get_name())
            {
                if(quantity <= products[choice - 1].get_quantity() && quantity != 0){
                    // Item already exists in cart: update quantity and price
                    item.set_quantity(item.get_quantity() + quantity);
                    item.set_price(item.get_price() + products[choice - 1].get_price() * quantity);
                    products[choice - 1].set_quantity(products[choice - 1].get_quantity() - quantity);
                }
                found = true;
                break;
            }
        }

        if (!found) {
            // Item does not exist in cart: add new item
            if(quantity <= products[choice - 1].get_quantity() && quantity != 0){
                cart.push_back(Product(products[choice - 1].get_name(), products[choice - 1].get_price() * quantity, quantity));
                products[choice - 1].set_quantity(products[choice - 1].get_quantity() - quantity);
            }
        }
        continue;  
    }
}

void Inventory() {
    while (true) {
        system("CLS");
        cout << termcolor::bright_yellow << termcolor::bold;  
        cout << "Welcome to the Inventory!" << endl;
        cout << "Please select a category:\n";
        cout << "1 : Electronics" << endl;
        cout << "2 : Footwear" << endl;
        cout << "3 : Clothing" << endl;
        cout << "4 : Accessories" << endl;
        cout << "5 : Books" << endl;
        cout << "6 : Sports" << endl;
        cout << "7 : Health" << endl;
        cout << "8 : Groceries" << endl;
        cout << "0 : Go Back" << endl;

        int choice;
        cout << "Enter your choice: ";

        while (!(cin >> choice) || (choice < 0 || choice > 8)) { 
            cout << termcolor::red;
            cout << "Invalid choice! Please enter a valid option: ";
            cout << termcolor::reset;
            cin.clear();  // Clear error flag
            cin.ignore(1000, '\n');  // Ignore invalid input
        }

        switch (choice) {
            case 1: 
                selectProduct(electronics); 
                break;
            case 2: 
                selectProduct(footwear); 
                break;
            case 3: 
                selectProduct(clothing); 
                break;
            case 4: 
                selectProduct(accessories); 
                break;
            case 5:
                selectProduct(books); 
                break;
            case 6:
                selectProduct(sports); 
                break;
            case 7:
                selectProduct(health); 
                break;
            case 8:
                selectProduct(groceries); 
                break;    
            case 0: 
                return;  
        }
    }
}

void restoreInventory(string productName, int quantity) {
    vector<vector<Product>*> catagories = {&electronics, &footwear, &clothing, &accessories, &books, &sports, &health, &groceries};
    for (auto inventory : catagories) {
        for (auto &product : *inventory) {
            if (product.get_name() == productName) {
                product.set_quantity(product.get_quantity() + quantity);
                return;
            }
        }
    }
}

ostream& tableHeader(ostream& ob) {
    ob << left << setw(5) << "ID" 
       << setw(35) << "Product" 
       << setw(15) << "Quantity" 
       << setw(15) << "Unit Price" 
       << setw(15) << "Total Price" << endl;
    return ob;
}
ostream& tableSeparator(ostream& ob) {
    ob << "------------------------------------------------------------------------------------" << endl;
    return ob;
}

void viewcart() {
    system("CLS");
    if (cart.empty()) {
        cout << "Your cart is empty!" << endl;
        cout << "Press any key to continue...";
        getch();
        return;
    }

    cout << "========== Your Cart ==========" << endl << endl;
    cout << tableHeader << tableSeparator;
    for (int i = 0; i < cart.size(); i++) {
        int unitPrice = cart[i].get_price() / cart[i].get_quantity();
        int totalPrice = cart[i].get_price();
        cout << left << setw(5) << (i + 1) 
             << setw(35) << cart[i].get_name() 
             << setw(15) << cart[i].get_quantity() 
             << setw(15) << unitPrice 
             << setw(15) << totalPrice << endl;
    }
    cout << tableSeparator;

    cout << "\nPress 0 to go back: ";
    int input;
    while (!(cin >> input) || input != 0) {
        cout << termcolor::red;
        cout << "Invalid input! Please press 0 to go back: ";
        cout << termcolor::reset;
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

void removefromcart() {
    system("CLS");
    if (cart.empty()) {
        cout << "Your cart is empty!" << endl;
        cout << "Press any key to continue...";
        getch();
        return;
    }

    while (true) {
        cout << termcolor::yellow;
        cout << "========== Remove from Cart ==========" << endl << endl;
        cout << tableHeader << tableSeparator;
        for (int i = 0; i < cart.size(); i++) {
            int unitPrice = cart[i].get_price() / cart[i].get_quantity();
            int totalPrice = cart[i].get_price();
            cout << left << setw(5) << (i + 1) 
                 << setw(35) << cart[i].get_name() 
                 << setw(15) << cart[i].get_quantity() 
                 << setw(15) << unitPrice 
                 << setw(15) << totalPrice << endl;
        }
        cout << tableSeparator;
        cout << termcolor::bright_white;
        cout << "\nEnter the ID of the item to remove (or 0 to go back): ";
        cout << termcolor::reset;
        int n;
        cin >> n;

        if (n == 0) {
            system("CLS");
            return;
        }

        if (n < 1 || n > cart.size()) {
            cout << termcolor::red;
            cout << "Invalid ID! Please enter a valid ID." << endl;
            cout << "Press any key to continue...";
            cout << termcolor::reset;
            getch();
            system("CLS");
            continue;
        }

        cout << "Enter the quantity to remove: ";
        int quantity;
        while (!(cin >> quantity) || quantity <= 0 || quantity > cart[n - 1].get_quantity()) {
            cout << termcolor::red;
            cout << "Invalid quantity! Please enter a value between 1 and " 
                 << cart[n - 1].get_quantity() << ": ";
            cout << termcolor::reset;
            cin.clear();
            cin.ignore(1000, '\n');
        }

        int unitPrice = cart[n - 1].get_price() / cart[n - 1].get_quantity();
        int newQuantity = cart[n - 1].get_quantity() - quantity;
        int newPrice = unitPrice * newQuantity;

        if (newQuantity > 0) {
            cart[n - 1].set_quantity(newQuantity);
            cart[n - 1].set_price(newPrice);
        } else {
            cart.erase(cart.begin() + (n - 1));
        }

        restoreInventory(cart[n - 1].get_name(), quantity);
        cout << termcolor::green;
        cout << "Item removed successfully!" << endl;
        cout << "Press any key to continue...";
        cout << termcolor::reset;
        getch();
        system("CLS");

        if (cart.empty()) {
            cout << "Your cart is now empty!" << endl;
            cout << "Press any key to continue...";
            getch();
            return;
        }
    }
}

void bill(Customer& customer) {
    system("CLS");
    if (cart.empty()) {
        cout << "Your cart is empty!" << endl;
        cout << "Press any key to continue...";
        getch();
        return;
    }

    int billNum = billNumber;
    time_t now = time(0);
    string timestamp = ctime(&now);
    timestamp.pop_back();

    cout << "===================== ShopSphere =====================" << endl;
    cout << "Bill Number: " << billNum << endl;
    cout << "Date: " << timestamp << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "Customer Details:" << endl;
    cout << "Name: " << customer.get_name() << endl;
    cout << "Email: " << customer.get_email() << endl;
    cout << "Phone: " << (customer.get_phoneno().empty() ? "Not provided" : customer.get_phoneno()) << endl;
    cout << "===========================================================" << endl << endl;

    cout << tableHeader << tableSeparator;
    int subtotal = 0;
    int totalItems = 0;
    for (int i = 0; i < cart.size(); i++) {
        int unitPrice = cart[i].get_price() / cart[i].get_quantity();
        int totalPrice = cart[i].get_price();
        subtotal += totalPrice;
        totalItems += cart[i].get_quantity();
        cout << left << setw(5) << (i + 1) 
             << setw(35) << cart[i].get_name() 
             << setw(15) << cart[i].get_quantity() 
             << setw(15) << unitPrice 
             << setw(15) << totalPrice << endl;
    }
    cout << tableSeparator;

    int discount = 0;
    if (subtotal > 20000) {
        discount = static_cast<int>(subtotal * 0.10);
    } else if (subtotal > 12000) {
        discount = static_cast<int>(subtotal * 0.75);
    }
    int grandTotal = subtotal - discount;

    cout << left << setw(50) << "Total Items: " << totalItems << endl;
    cout << setw(50) << "Subtotal: " << subtotal << endl;
    if (discount > 0) {
        cout << setw(50) << "Discount: " << discount << endl;
    }
    cout << setw(50) << "Grand Total: " << grandTotal << endl;
    cout << setw(50) << "Payment Method: Paid via Cash" << endl;
    cout << "===========================================================" << endl << endl;

    cout << "Options:" << endl;
    cout << "1 : Confirm Purchase" << endl;
    cout << "2 : Return to Main Menu" << endl;
    cout << "Enter your choice: ";

    int choice;
    while (!(cin >> choice) || (choice < 1 || choice > 2)) {
        cout << "Invalid choice! Please enter 1 or 2: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    if (choice == 1) {
        billNumber++;
        cart.clear();
        saveCustomers();
        cout << termcolor::green;
        cout << "\nPurchase confirmed! Thank you for shopping with ShopSphere!" << endl;
        cout << "Press any key to continue...";
        cout << termcolor::reset;
        getch();
    }
}

int main() {
    loadCustomers();
    while (true) {
        bool loginflag = true;
        while (!checkforlogin()) {
            create_account();
        }

        Customer& client = login(loginflag);
        if (!loginflag) {
            continue;
        }
        bool flag = true;

        while (flag) {
            system("CLS");
            cout << termcolor::bright_yellow << termcolor::bold;
            cout << "\nWelcome, " << client.get_name() << "!" << endl;
            cout << "\nSelect an option:" << endl;
            cout << "1 : View Profile" << endl;
            cout << "2 : Update Profile" << endl;
            cout << "3 : View Inventory" << endl;
            cout << "4 : View Cart" << endl;
            cout << "5 : Remove from Cart" << endl;
            cout << "6 : Bill" << endl;
            cout << "7 : Logout" << endl;
            cout << "Enter your choice: ";

            int choice;
            cin >> choice;
            cin.ignore();

            switch (choice) {
                case 1: {
                    system("CLS");
                    client.view_profile();
                    cout << "\tPress any key to continue...";
                    getch();
                    break;
                }
                case 2: {
                    UpdateProfile(client);
                    break;
                }
                case 3: {
                    Inventory();
                    break;
                }
                case 4: {
                    viewcart();
                    break;
                }
                case 5: {
                    removefromcart();
                    break;
                }
                case 6: {
                    bill(client);
                    break;
                }
                case 7: {
                    system("CLS");
                    cout << termcolor::green;
                    cout << "Logging out..." << endl;
                    cout << "Press any key to continue...";
                    cout << termcolor::reset;
                    getch();
                    flag = false;
                    break;
                }
                default:
                    cout << "Invalid choice, please try again." << endl;
                    break;
            }
        }
    }
    return 0;
}