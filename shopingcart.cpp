#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#include<conio.h>
#include<iomanip>
#include<windows.h>

using namespace std; 

int const startingAccountNumber=1;
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


string setPassword(){
    string password;
    while(1){
        char s;
        s=getch();
        if (!password.empty() && s == '\b') {
            cout << "\b \b";
            password.pop_back();
        }

        
        if(s=='\r') 
            break;
        else    
            password+=s;
        cout<<"*";
    }
    return password;
}


bool emailexistornot(string email){
    for(int i=0;i<customers.size();i++){
        if(customers[i].get_email()==email)
            return true;
    }
    return false;
}

string validphonenumberchecker(string phoneNumber) {
    while (true) {
        bool isValid = true;
        // Check length
        if (phoneNumber.size() != 10||phoneNumber.empty()) {
            isValid = false;
        }
        else {
            // Check each character is a digit
            for (int i = 0; i < 10; i++) {
                if (phoneNumber[i] < '0' || phoneNumber[i] > '9') {
                    isValid = false;
                    break;
                }
            }
        }

        if (isValid) break;

        cout << "You entered an invalid number..."<<endl;
        cout << "\tEnter a valid number: ";
        cin >> phoneNumber;
    }
    return phoneNumber;
}

string validemailchecker(string email){
    int es = email.size();
    while(true)
    {
        int dot=0,atherate=0;
        for(int i=0;i<es;i++)
        {
            if(email[i]=='.')   dot++;
            if(email[i]=='@'&&email[i+1]!='.'&&email[i-1]!='.') atherate++;
        }
        if(atherate==1&&dot>=1 && email[es-1]!='.' && email[es-1]!='@' && email[0]!='@' && email[0]!='.') break;
        else{
            cout<<"You entered an invalid email addreess..."<<endl;
            cout<<"\tEnter an valid email address : ";
            cin>>email;
        }
    }
    return email;
}


bool checkforlogin()
{
    system("CLS");
    cout << "\n\tWelCome To Our App" << "\n\n" << endl;
    cout << "\t1 : Login an account " << endl ;
    cout << "\t2 : Create an account " << endl ;
    cout << "\t3 : Exit" << "\n" << endl ;

    cout << "\tSelect an Option : " ;
    while(true){

        int choice ;
        cin >> choice ;
        system("CLS");

        if(choice == 1)
            return true ;
        else if(choice == 2)
            return false ;
        else if(choice == 3)
            exit(0);
        else 
            cout << "\tSelect valid option : " ;
    }

}

Customer &login(bool &loginflag){
    system("CLS");
    cout << "Login Section:\n\n";

    string email;
    int account_index = -1;

    while (true) {
        cout << "Enter email address (or enter 0 to exit): ";
        cin>>email;
        // Allow user to exit at any time
        if (email == "0") {
            loginflag = false;
            break;
        }

        // If user presses Enter without typing an email, ask again
        if (email.empty()) {
            cout << "\nPlease enter an email address!" << endl;
            continue;  
        }

        // Check email format immediately
        email = validemailchecker(email);

        // Now, check if the email exists in the system
        account_index = -1;
        for (int i = 0; i < numberofuser - startingAccountNumber; i++) {
            if (email == customers[i].get_email()) {
                account_index = i;
                break;
            }
        }

        // If email does not exist, allow retries
        if (account_index == -1) {
            cout << "Account does not exist! Please create an account first." <<"\n"<< endl;
            continue;  
            
        } else     break;  
    }

    string password;

    if(loginflag==true){
        while (true) {
            cout << "Enter password (or enter 0 to exit): ";
            password = setPassword();
            
            // Allow user to exit at any time
            if (password == "0") {
                loginflag = false;
                break;
            }
            
            // Check if password matches
            if (customers[account_index].check_passwordclass(password)) {
                system("CLS");
                cout << "\nLogged in successfully!" << endl;
                cout << "Press any key to continue...";
                getch();
                system("CLS");
                loginflag = true;
                return customers[account_index];
            } else {
                cout << "\nIncorrect password! Please try again."<<endl;
            }
        }
    }
    return customers[numberofuser-startingAccountNumber];
}

void create_account()
{
    cin.ignore();
    cout << "\tCreate an account : \n" << endl ;  
    string name;
    string username;
    string email;
    string phone_no;
    string address;
    string password;
    string confirm_password;

    cout<<"\tEnter your name : ";
    getline(cin,name);
    cout<<"\tEnter email address : ";
    cin>>email;
    // Check if email already exists
    while (emailexistornot(email)) {
        cout << "\tEmail already exists! Please enter a different email: ";
        cin >> email;
    }
    email=validemailchecker(email);
    cout<<"\tEnter phone no : ";
    cin>>phone_no;
    phone_no=validphonenumberchecker(phone_no);

    while(true){
        cout<<"\tEnter password : ";
        password=setPassword();
        cout<<endl<<"\tConfirm password : ";
        confirm_password=setPassword();
        if(password!=confirm_password){
            system("CLS");
            cout<<endl<<"\tPassword does not match ! Please Try again... "<<endl; 
            continue;
        }
        else break;
    }

    system("CLS");
    customers.push_back(Customer(name, username, phone_no, email, address, password));
    numberofuser++;
    cout<<endl<<"\tAccount created successfully !"<<endl;
    cout<<"\tpress any key to continue...";
    getch();
    system("CLS");
    numberofuser++;   
}

vector<Product> cart;

// Define the products in each category
vector<Product> electronics = {
    Product("Laptop", 500, 10),
    Product("Smartphone", 300, 20),
    Product("Headphones", 100, 15),
    Product("Tablet", 250, 12),
    Product("Smartwatch", 200, 18),
    Product("Bluetooth Speaker", 80, 25),
    Product("Gaming Console", 400, 8),
    Product("Wireless Mouse", 25, 30),
    Product("Keyboard", 40, 22),
    Product("Power Bank", 35, 35)
};

vector<Product> footwear = {
    Product("Nike Shoes", 80, 30),
    Product("Adidas Sneakers", 70, 25),
    Product("Puma Sandals", 50, 40),
    Product("Reebok Trainers", 75, 20),
    Product("Vans Slip-ons", 60, 25),
    Product("Formal Shoes", 90, 15),
    Product("Flip Flops", 20, 50),
    Product("Boots", 100, 10),
    Product("Loafers", 65, 18),
    Product("Crocs", 40, 35)
};

vector<Product> clothing = {
    Product("T-Shirt", 20, 50),
    Product("Jeans", 40, 30),
    Product("Jacket", 60, 20),
    Product("Sweater", 45, 25),
    Product("Hoodie", 50, 28),
    Product("Shorts", 25, 40),
    Product("Skirt", 30, 35),
    Product("Dress", 55, 22),
    Product("Tracksuit", 70, 15),
    Product("Blazer", 80, 10)
};

vector<Product> accessories = {
    Product("Watch", 150, 10),
    Product("Sunglasses", 50, 25),
    Product("Backpack", 30, 40),
    Product("Wallet", 25, 35),
    Product("Belt", 20, 30),
    Product("Cap", 15, 50),
    Product("Scarf", 18, 45),
    Product("Earrings", 35, 20),
    Product("Necklace", 60, 15),
    Product("Bracelet", 40, 18)
};

vector<Product> books = {
    Product("The Great Gatsby", 15, 100),
    Product("1984", 12, 80),
    Product("To Kill a Mockingbird", 14, 90),
    Product("The Alchemist", 13, 70),
    Product("Sapiens", 20, 50),
    Product("Atomic Habits", 18, 60),
    Product("Harry Potter", 25, 75),
    Product("The Hobbit", 16, 65),
    Product("Rich Dad Poor Dad", 17, 85),
    Product("The Psychology of Money", 19, 55)
};

vector<Product> sports = {
    Product("Football", 25, 40),
    Product("Basketball", 30, 35),
    Product("Yoga Mat", 20, 50),
    Product("Dumbbells (10kg)", 45, 15),
    Product("Tennis Racket", 60, 20),
    Product("Skipping Rope", 10, 60),
    Product("Treadmill", 500, 5),
    Product("Cycling Helmet", 35, 25),
    Product("Resistance Bands", 15, 40),
    Product("Fitness Tracker", 70, 12)
};

vector<Product> health = {
    Product("Vitamins (60 tabs)", 20, 30),
    Product("First Aid Kit", 25, 20),
    Product("Thermometer", 15, 25),
    Product("Blood Pressure Monitor", 50, 10),
    Product("Hand Sanitizer", 5, 100),
    Product("Face Masks (50 pcs)", 10, 75),
    Product("Pain Relief Spray", 8, 40),
    Product("Cough Syrup", 6, 50),
    Product("Disinfectant Wipes", 7, 60),
    Product("Bandages", 3, 80)
};

vector<Product> groceries = {
    Product("Rice (5kg)", 20, 50),
    Product("Sugar (1kg)", 2, 100),
    Product("Flour (2kg)", 3, 80),
    Product("Cooking Oil (1L)", 5, 60),
    Product("Salt (1kg)", 1, 150),
    Product("Pasta (500g)", 2, 120),
    Product("Canned Beans", 1, 200),
    Product("Frozen Vegetables", 3, 90),
    Product("Spices Set", 10, 40),
    Product("Tea Bags (100 pcs)", 5, 70)
};

void selectProduct(vector<Product>& products) {
    int choice, quantity;
    int size = products.size();
    cout << size << endl;
    system("CLS");
        cout << left << setw(5) << "ID" << setw(35) << "Product" << setw(30) << "Price" << endl;
        cout << "---------------------------------" << endl;
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
                if(quantity <= products[choice - 1].get_quantity()){
                    // Item already exists in cart: update quantity and price
                    item.set_quantity(item.get_quantity() + quantity);
                    item.set_price(item.get_price() + products[choice - 1].get_price() * quantity);
                }
                found = true;
                break;
            }
        }

        if (!found) {
            // Item does not exist in cart: add new item
            if(quantity <= products[choice - 1].get_quantity()){
                cart.push_back(Product(products[choice - 1].get_name(), products[choice - 1].get_price() * quantity, quantity));
            }
        }
        continue;  
    }
}

void viewcart(){
    system("CLS");
    int n;
    while(true){
        
        cout << left << setw(5) << "ID" << setw(15) << "Product" << setw(15) << "Quantity"<< setw(10) << "Price" << endl;
        cout << "---------------------------------" << endl;
        for (int i = 0; i < cart.size(); i++) {
            cout << setw(5) << i + 1 << setw(15) << cart[i].get_name() << setw(15) << cart[i].get_quantity()<< setw(10) << cart[i].get_price() << endl;
        }
        cout << "\nPress 0 to go back : " ;
        cin >> n;
        if(n==0)
        return;
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
            cout << "6 : Checkout" << endl;
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