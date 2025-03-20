#include<iostream>
#include<string>
#include<conio.h>
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
        this->username = name ;
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
        return phone_no ;
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

}customers[10];


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



string setPassword(){
    string password;
    while(1){
        char s;
        s=getch();
        if (s == '\b') {
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

string validphonenumberchecker(string phoneNumber) {
    while (true) {
        bool isValid = true;

        // Check length
        if (phoneNumber.size() != 10||phoneNumber.empty()) {
            isValid = false;
        } else {
            // Check each character is a digit
            for (int i = 0; i < 10; i++) {
                if (phoneNumber[i] < '0' || phoneNumber[i] > '9') {
                    isValid = false;
                    break;
                }
            }
        }

        if (isValid) break;

        cout <<endl<< "You entered an invalid number..."<<endl<<endl;
        cout << "Enter a valid number: ";
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
                cout << "\nIncorrect password! Please try again.\n"<<endl;
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
    customers[numberofuser-startingAccountNumber]=Customer(name,username,phone_no,email,address,password);
    cout<<endl<<"\tAccount created successfully !"<<endl;
    cout<<"\tpress any key to continue...";
    getch();
    system("CLS");
    numberofuser++;   
}

void electronic(){
    system("CLS");
    cout << "1 : Mobile    20000 " << endl;
    cout << "2 : Laptop     60000" << endl ;
    cout << "3 : Camera     15000" << endl ;
    cout << "4 : Television    60000" << endl ;
    cout << "back to main menu (enter 0) :" << endl;
    cout << "enter your choice : " ;
    int choice;
    cin >> choice;
    cout << "\nenter quantity : " ;
    int quantity;
    cin >> quantity;

    switch (choice)
    {
    case 1:
        /* code */
        Product ("Mobile" ,20000 , quantity);
        break;
    case 2 :
        Product ("Laptop" ,60000 , quantity);
        break;
    case 3 :
        Product ("Camera" ,15000 , quantity);
        break;
    case 4 :
        Product ("Television" , 60000 , quantity);
        break ;
    case 0 :
        break ;
    default:
        break;
    }
}

void footware(){
    system("CLS");
    cout << "1 : Shoes    2000 " << endl;
    cout << "2 : Sandals     1000" << endl ;
    cout << "3 : Slippers     500" << endl ;
    cout << "4 : Boots    3000" << endl ;
    cout << "back to main menu (enter 0) :" << endl;
    cout << "enter your choice : " ;
    int choice;
    cin >> choice;
    cout << "\nenter quantity : " ;
    int quantity;
    cin >> quantity;

    switch (choice)
    {
    case 1:
        /* code */
        Product ("Shoes" ,2000 , quantity);
        break;
    case 2 :
        Product ("Sandals" ,1000 , quantity);
        break;
    case 3 :
        Product ("Slippers" ,500 , quantity);
        break;
    case 4 :
        Product ("Boots" , 3000 , quantity);
        break ;
    case 0 :
        break ;
    default:
        break;
    }
}

void clothing(){
    system("CLS");
    cout << "1 : T-shirt    500 " << endl;
    cout << "2 : Shirt     1000" << endl ;
    cout << "3 : Jeans     1500" << endl ;
    cout << "4 : Trousers    2000" << endl ;
    cout << "back to main menu (enter 0) :" << endl;
    cout << "enter your choice : " ;
    int choice;
    cin >> choice;
    cout << "\nenter quantity : " ;
    int quantity;
    cin >> quantity;

    switch (choice)
    {
    case 1:
        /* code */
        Product ("T-shirt" ,500 , quantity);
        break;
    case 2 :
        Product ("Shirt" ,1000 , quantity);
        break;
    case 3 :
        Product ("Jeans" ,1500 , quantity);
        break;
    case 4 :
        Product ("Trousers" , 2000 , quantity);
        break ;
    case 0 :
        break ;
    default:
        break;
    }
}

void accesesories(){
    system("CLS");
    cout << "1 : Watch    5000 " << endl;
    cout << "2 : Bracelet     2000" << endl ;
    cout << "3 : Ring     1000" << endl ;
    cout << "4 : Chain    3000" << endl ;
    cout << "back to main menu (enter 0) :" << endl;
    cout << "enter your choice : " ;
    int choice;
    cin >> choice;
    cout << "\nenter quantity : " ;
    int quantity;
    cin >> quantity;

    switch (choice)
    {
    case 1:
        /* code */
        Product ("Watch" ,5000 , quantity);
        break;
    case 2 :
        Product ("Bracelet" ,2000 , quantity);
        break;
    case 3 :
        Product ("Ring" ,1000 , quantity);
        break;
    case 4 :
        Product ("Chain" , 3000 , quantity);
        break ;
    case 0 :
        break ;
    default:
        break;
    }
}



void Inventory (){
    system("CLS");
    cout << "1 : Electronic" << endl;
    cout << "2 : footware" << endl ;
    cout << "3 : clothing" << endl ;
    cout << "4 : accesesories" << endl ;
    cout << "back to main menu (enter 0) :" << endl;
    cout << "enter your choice : " ;
    int n;
    cin >> n;
    switch (n)
    {
    case 1:
        electronic();
        break;
    case 2 :
        footware();
        break ;
    case 3 :
        clothing();
        break;
    case 4 :
        accesesories();
        break;
    case 0 :
        break ;
    default:
        break;
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
            cout << "5 : Add to cart" << endl;
            cout << "6 : Remove from cart" << endl;
            cout << "7 : Checkout" << endl;
            cout << "8 : Logout" << endl;          
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


                case 8: {
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