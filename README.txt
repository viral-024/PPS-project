README.txt — ShopSphere E-Commerce System

Overview:
ShopSphere is a console-based e-commerce system written in C++. 
It provides a complete shopping experience with user accounts, product inventory, cart management, and billing.

------------

How to Use the Program

1. Starting the Program:
    -Compile and run the program.
    -The system will load existing customer data automatically.

2. Main Menu Options:
    -Login to an existing account
    -Create a new account
    -Exit the program

------------

Account Management

1. Creating an Account:
    -Enter your full name
    -Provide a valid email address (format: user@domain.com)
    -Enter a 10-digit phone number
    -Set and confirm your password

2. Logging In:
    -Enter your registered email address
    -Input your password (shown as * for privacy)

------------

Shopping Features
    
After successful login, you can:

1. View Profile:
    -See your account details (name, email, phone)

2. Update Profile:
    -Change your name, phone number, email, or password

3. View Inventory:
    -Browse products from 8 categories:
        -Electronics (Laptops, Phones, etc.)
        -Footwear (Shoes, Sandals, etc.)
        -Clothing (T-Shirts, Jeans, etc.)
        -Accessories (Watches, Sunglasses, etc.)
        -Books (Fiction, Non-fiction)
        -Sports (Equipment, Gear)
        -Health (Medicines, Supplements)
        -Groceries (Food items)

4. Add to Cart:
    -Select products by ID
    -Choose quantity (cannot exceed available stock)
    -Products are automatically added to your cart

-----------

Cart Management

1. View Cart:
    -See all items with details:
        -Product name
        -Quantity
        -Unit price
        -Total price per item

2. Remove from Cart:
    -Select items by ID to remove
    -Specify quantity to remove
    -Removed items return to inventory

3. Checkout: 
    -View complete bill with:
        -Bill number and timestamp
        -Customer details
        -Itemized purchase list
        -Subtotal and discounts (if applicable)
        -Grand total
    -Confirm purchase to complete transaction

------------

System Features

1. Data Persistence:
    -All customer accounts are saved in customers.txt
    -Inventory quantities update in real-time
    -Bill numbers increment sequentially

2. Input Validation:
    -Email format verification
    -Phone number validation (must be 10 digits)
    -Password confirmation
    -Quantity checks against available stock

3. Security:
    -Password entry masked with *
    -Email verification before account creation

Notes:
    -The system maintains separate inventories for each category
    -Discounts are automatically applied:
        -10% for purchases over ₹20,000
        -7.5% for purchases over ₹12,000
    -All prices are in Indian Rupees (₹)
    -Press '0' at any time to return to the previous menu

To exit the program, choose the logout option from the main menu or close the console window.