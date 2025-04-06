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
    void set_quantity(int quantity){
        this->quantity=quantity;
    }
    void set_price(int price){
        this->price=price;
    }
    void set_name(string name){
        this->name=name;
    }

};

// vector<string>pname;
// vector<int>pquantity;
// vector<int>price;
// static int TotalPrice = 0;

// void Product(string name,int q,int p){
//     int size = pname.size();
//     for(int i = 0 ; i<size ; i++){
//         if(name == pname[i]){
//             pquantity[i] += q;
//             price[i] += p;
//         }
//         else{
//             pname.push_back(name);
//             pquantity.push_back(q);
//             price.push_back(p);
//         }
//     }

//     size = pname.size();
//     for(int i =0 ; i<size ; i++)
//         TotalPrice += price[i];
// }


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

string validemailchecker(string email) {
    while (true) {
        int dot = 0, attherate = 0;

        for (char ch : email) {
            if (ch == '.') dot++;
            if (ch == '@') attherate++;
        }

        if (attherate == 1 && dot >= 1) {
            return email;  //  If format is correct, return email
        } else {
            cout << "Invalid email format! Please enter again: ";
            cin >> email;
        }
    }
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

void selectProduct(vector<Product>& products) {
    int choice, quantity;

    system("CLS");
        cout << left << setw(5) << "ID" << setw(15) << "Product" << setw(10) << "Price" << endl;
        cout << "---------------------------------" << endl;
        for (int i = 0; i < products.size(); i++) {
            cout << setw(5) << i + 1 << setw(15) << products[i].get_name() << setw(10) << products[i].get_price() << endl;
        }

        cout << "\nEnter 0 to go back." << endl;
        cout << "Enter your choice: ";

    while (true) {

        cout << "\nEnter your choice: ";
        while (!(cin >> choice) || (choice < 0 || choice > 3)) { 
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
            cout << "\nNot enough stock available! Please enter a valid quantity." << endl;
            cout << "Available quantity: " << products[choice - 1].get_quantity() << endl;
            cin.clear();
            cin.ignore(1000, '\n');  // Ignore invalid input  
        }

       
        // Update quantity and add product to cart
        if (quantity <= products[choice - 1].get_quantity()){
            // Update available quantity in inventory
            products[choice - 1].set_quantity(products[choice - 1].get_quantity() - quantity); 
            // Add product to cart with quantity
            cart.push_back(Product(products[choice - 1].get_name(), products[choice - 1].get_price(), quantity));
            cout << "Product added to cart Succesfully!\n" << endl;
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
        cout << "\npress 0 to return";
        cin >> n;
        if(n==0)
        return;
    }
    
}

// Define the products in each category
vector<Product> electronics = {
    Product("Laptop", 500, 10),
    Product("Smartphone", 300, 20),
    Product("Headphones", 100, 15)
};

vector<Product> footwear = {
    Product("Nike Shoes", 80, 30),
    Product("Adidas Sneakers", 70, 25),
    Product("Puma Sandals", 50, 40)
};

vector<Product> clothing = {
    Product("T-Shirt", 20, 50),
    Product("Jeans", 40, 30),
    Product("Jacket", 60, 20)
};

vector<Product> accessories = {
    Product("Watch", 150, 10),
    Product("Sunglasses", 50, 25),
    Product("Backpack", 30, 40)
};


void Inventory() {
    while (true) {
        system("CLS");
        cout << "Welcome to the Inventory!" << endl;
        cout << "Please select a category:\n";
        cout << "1 : Electronics" << endl;
        cout << "2 : Footwear" << endl;
        cout << "3 : Clothing" << endl;
        cout << "4 : Accessories" << endl;
        cout << "0 : Go Back" << endl;

        int choice;
        cout << "Enter your choice: ";

        while (!(cin >> choice) || (choice < 0 || choice > 4)) { 
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