#include<iostream>
#include<fstream>
#include<vector>
#include<cstring>
#include<conio.h>
#include<iomanip>
#include<windows.h>

using namespace std; 

int const startingAccountNumber=1000;
static int  numberofuser=startingAccountNumber;


class Customer{

    string name ;
    string username ;
    string phone_no ;
    string email ;
    string address ;
    string password ;

    public :

    Customer(){}

    Customer (string name ,string username ,string phone_no ,string email ,string address ,string password ){
        this->name = name ;
        this->username = username ;
        this->phone_no = phone_no ;
        this->email = email ;
        this->address = address ;
        this->password = password ;
    }

    string get_name(){
        return name ;
    }

    string get_username(){
        return username ;
    }

    string get_password(){
        return password ;
    }

    string get_email(){
        return email ;
    }

    string get_address(){
        return address ;
    }

    string get_phoneno(){
        return phone_no ;
    }

    void update_username(string username){
        this->username=username;
    }

    void update_phoneno(string phone_no){
        this->phone_no=phone_no;
    }

    void update_email(string email){
        this->email=email;
    }

    void update_address(string address){
        this->address=address;
    }
    
    void update_password(string password){
        this->password=password;
    }

    void update_name(string name){
        this->name=name;
    }

    bool check_passwordclass(string password) {
        if(password==this->password)
            return true;
        else    
            return false;
    }

    void view_profile(){
        cout << "\tname : " << name << endl ;
        cout << "\tEmail : " << email << endl ;
        cout << "\tphone_no : " << phone_no << endl ;
    }

};
vector<Customer> customers;

class Product{
    string name;
    int price;
    int quantity;
    public:
    Product(){}
    Product(string name,int price,int quantity){
        this->name=name;
        this->price=price;
        this->quantity=quantity;
    }
    string get_name(){
        return name;
    }
    int get_price(){
        return price;
    }
    int get_quantity(){
        return quantity;
    }

    void set_price(int price){
        this->price=price;
    }
    void set_name(string name){
        this->name=name;
    }
    void set_quantity(int quantity){
        this->quantity=quantity;
    }
};


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
                    cout << "\nPassword cannot be empty! Please enter a password.";
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

bool emailexistornot(string email) {
    for (int i = 0; i < customers.size(); i++) {
        if (customers[i].get_email() == email)
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
            for (int i = 0; i < 10; i++) {
                if (phoneNumber[i] < '0' || phoneNumber[i] > '9') {
                    isValid = false;
                    break;
                }
            }
        }
        if (isValid) break;
        cout << "You entered an invalid number..." << endl;
        cout << "\tEnter a valid number: ";
        cin >> phoneNumber;
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
            cout << "Invalid email format! (e.g., user@domain.com, or 0 to return): ";
            cin >> email;
        }
    }
}

bool checkforlogin() {
    system("CLS");
    cout << "\n\tWelCome To Our App" << "\n\n" << endl;
    cout << "\t1 : Login an account " << endl;
    cout << "\t2 : Create an account " << endl;
    cout << "\t3 : Exit" << "\n" << endl;
    cout << "\tSelect an Option : ";
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
    cout << "Login Section:\n\n";

    string email;
    int account_index = -1;

    while (true) {
        cout << "Enter email address (or 0 to return to main menu): ";
        cin >> email;

        if (email == "0") {
            loginflag = false;
            return customers[numberofuser - startingAccountNumber];
        }
        if (email.empty()) {
            cout << "\nPlease enter an email address!" << endl;
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
            cout << "No account found with this email! Try again or enter 0 to return.\n" << endl;
            continue;
        } else {
            break;
        }
    }

    string password;
    while (true) {
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
            cout << "Incorrect password! Try again or enter 0 to return." << endl;
        }
    }
    return customers[numberofuser - startingAccountNumber];
}

void create_account() {
    cin.ignore();
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

    while (emailexistornot(email)) {
        cout << "\tEmail already exists! Please enter a different email (or 0 to return): ";
        cin >> email;
        if (email == "0") {
            system("CLS");
            return;
        }
    }

    email = validemailchecker(email);
    if (email.empty()) {
        system("CLS");
        return;
    }

    cout << "\tEnter phone no : ";
    cin >> phone_no;
    phone_no = validphonenumberchecker(phone_no);

    while (true) {
        cout << "\tEnter password : ";
        password = setPassword();
        cout << endl << "\tConfirm password : ";
        confirm_password = setPassword();
        if (password != confirm_password) {
            system("CLS");
            cout << endl << "\tPassword does not match! Please try again..." << endl;
            continue;
        } else {
            break;
        }
    }

    // Add to vector
    customers.push_back(Customer(name, username, phone_no, email, address, password));
    numberofuser++;

    // Write to file
    ofstream file("customers.txt", ios::app); // Open in append mode
    if (file.is_open()) {
        file << "name: " << name << endl;
        file << "username: " << username << endl;
        file << "phone_no: " << phone_no << endl;
        file << "email: " << email << endl;
        file << "address: " << address << endl;
        file << "password: " << password << endl;
        file << endl; // Blank line to separate customers
        file.close();
    } else {
        cout << "Error: Could not save account to file!" << endl;
    }

    system("CLS");
    cout << endl << "\tAccount created successfully!" << endl;
    cout << "\tPress any key to continue...";
    getch();
    system("CLS");
}

vector<Product> cart;

// Define the products in each category
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

        cout << "\nEnter your choice: ";
        while (!(cin >> choice) || (choice < 0 || choice > size )) { 
            cout << "Invalid choice! Please enter a valid option: ";
            cin.clear();  // Clear error flag
            cin.ignore(1000, '\n');  // Ignore invalid input
        }
        if (choice == 0) {
            return;  // Exit product selection
        }
        cout << "Enter quantity: ";
        cin >> quantity;

        if (quantity <= 0 ) {
            cout << "\nInvalid quantity! Please enter a valid quantity." << endl;
            cin.clear();
            cin.ignore(1000, '\n');  // Ignore invalid input
        }

        if(quantity > products[choice - 1].get_quantity()) {
            cout << "\nSorry, We have Not enough stock available! Please enter a valid quantity." << endl;
            cout << "Available quantity: " << products[choice - 1].get_quantity() << endl;
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

void viewcart(){
    system("CLS");
    int n;
    while(true){
        
        cout << left << setw(5) << "ID" << setw(35) << "Product" << setw(35) << "Quantity"<< setw(30) << "Price" << endl;
        cout << "----------------------------------------------" << endl;
        for (int i = 0; i < cart.size(); i++) {
            cout << setw(5) << i + 1 << setw(35) << cart[i].get_name() << setw(35) << cart[i].get_quantity()<< setw(30) << cart[i].get_price() << endl;
        }
        cout << "\nPress 0 to go back : " ;
        while (!(cin >> n) == 0) { 
            cout << "Invalid choice! Please enter a valid option: ";
            cin.clear();  // Clear error flag
            cin.ignore(1000, '\n');  // Ignore invalid input
            if (n == 0) {
                return;  // Exit product selection
            }
        }
        if (n==0) {
            return;  // Exit product selection
        }
    }
    
}



void Inventory() {
    while (true) {
        system("CLS");
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
            cout << "Invalid choice! Please enter a valid option: ";
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
                return;  // Exit inventory and return to the main menu
        }
    }
}

// Helper function to restore inventory (add this to your code)
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


void removefromcart() {
    system("CLS");
    if (cart.empty()) {
        cout << "Your cart is empty!" << endl;
        cout << "Press any key to continue...";
        getch();
        return;
    }

    while (true) {
        
        cout << left << setw(5) << "ID" << setw(35) << "Product" << setw(35) << "Quantity" << setw(30) << "Price" << endl;
        cout << "----------------------------------------------" << endl;
        for (int i = 0; i < cart.size(); i++) {
            cout << setw(5) << i + 1 << setw(35) << cart[i].get_name() << setw(35) << cart[i].get_quantity() << setw(30) << cart[i].get_price() << endl;
        }

        int n;
        cout << "\nEnter the ID of the item you want to remove from cart (or enter 0 to go back): ";
        cin >> n;

        if (n == 0) {
            return;
        }

        // Validate ID
        if (n < 1 || n > cart.size()) {
            cout << "Invalid choice! Please enter a valid ID." << endl;
            cout << "Press any key to continue...";
            getch();
            system("CLS");
            continue;
        }

        int quantity;
        cout << "Enter the quantity to remove: ";
        cin >> quantity;

        // Validate quantity
        if (quantity <= 0 || quantity > cart[n - 1].get_quantity()) {
            cout << "Invalid quantity! Please enter a valid quantity (1-" << cart[n - 1].get_quantity() << "): ";
            cin >> quantity;
        }

        // Calculate unit price
        int unitPrice = cart[n - 1].get_price() / cart[n - 1].get_quantity();
        int newQuantity = cart[n - 1].get_quantity() - quantity;
        int newPrice = unitPrice * newQuantity;

        // Update or remove item from cart
        if (newQuantity > 0) {
            cart[n - 1].set_quantity(newQuantity);
            cart[n - 1].set_price(newPrice);
        } else {
            cart.erase(cart.begin() + (n - 1));
        }

        restoreInventory(cart[n - 1].get_name(), quantity);

        cout << "Item removed from cart successfully!" << endl;
        cout << "Press any key to continue...";
        getch();
        system("CLS");

        // If cart is empty, exit
        if (cart.empty()) {
            cout << "Your cart is now empty!" << endl;
            cout << "Press any key to continue...";
            getch();
            return;
        }
    }
}






int main() {
    while (true) {
        bool loginflag = true;
        while (!checkforlogin()) {
            create_account();
        }

        Customer &client = login(loginflag);
        if (!loginflag) {
            continue;
        }
        bool flag = true; 

        while (flag) {
            system("CLS");
            cout << "\nWelcome, " << client.get_name() << "!" << endl;
            cout << "\nSelect an option:" << endl;
            cout << "1 : View Profile" << endl;
            cout << "2 : Update Profile" << endl;
            cout << "3 : view inventory" << endl;
            cout << "4 : view cart" << endl;
            cout << "5 : Remove from cart" << endl;
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
                    system("CLS");
                    cout << "\nWhich field would you like to update?" << endl;
                    cout << "1 : Update Email" << endl;
                    cout << "2 : Update Phone Number" << endl;
                    cout << "3 : Update Password" << endl;
                    cout << "Enter your choice: ";
                    int updateChoice;
                    cin >> updateChoice;
                    cin.ignore(); 

                    switch (updateChoice) {
                        case 1: {
                            string newValue;
                            cout << "Enter new email: ";
                            cin >> newValue;
                            client.update_email(newValue);
                            cout << "\nEmail updated successfully!" << endl;
                            break;
                        }
                        case 2: {
                            string newValue;
                            cout << "Enter new phone number: ";
                            cin >> newValue;
                            client.update_phoneno(newValue);
                            cout << "\nPhone number updated successfully!" << endl;
                            break;
                        }
                        case 3: {
                            string newValue;
                            cout << "Enter new password: ";
                            newValue = setPassword(); 
                            client.update_password(newValue);
                            cout << "\nPassword updated successfully!" << endl;
                            break;
                        }
                        default:
                            cout << "Invalid option!" << endl;
                    }
                    cout << "Press any key to continue...";
                    getch();
                    break;
                }
                case 3 : {
                    Inventory();
                    break ;
                }

                case 4 : {
                    viewcart();
                    break;
                }
                
                case 5 : {
                    removefromcart();
                    break;
                }
                

                case 7: {
                    system("CLS");
                    cout << "Logging out..." << endl;
                    cout << "Press any key to continue...";
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