# cpp-bank-system
Learning project written in C++ for practicing OOP, file handling and basic system design.

## Features
- Create accounts with username and password
- Login / Logout system
- Deposit and withdraw money
- Transfer money between accounts
- View balance and account details
- Delete account (password protected)
- Persistent storage using a text file

## How it works
- Accounts are stored in a vector memory
- Data is saved to "accounts.txt" when changes happen
- Each account stores username, password, balance
- The program loads saved accounts on startup
  
## File System
- "accounts.txt" is used for saving/loading accounts
- Each account is stored as name, password, balance
   
## Menu System
The program has two menus:
- Main menu: create account, account options, exit
- Account menu: login required actions (deposit, withdraw, etc.)

## Important Notes
- Passwords are stored in plain text so they are not secure
- This is just a learning project
- No encryption or database system is used
- Input validation is basic but not perfect

## What I learned
- Classes and structs
- File handling
- Vectors and data storage
- Menu driven programs
- Basic state management

## Future Improvements
- Encrypt passwords
- Replace text file with database
- Imrove error handling
- Add transaction history
- Improve code structure
