#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <fstream>

class accountCT {
private:
	struct Accounts {
		std::string name;
		std::string password;
		double balance = 0.0;
	};

	std::vector<Accounts> table;
	int loggedIn = -1;
public:
	void createAccount(std::string username, std::string pass) {
		bool taken = false;

		for (int i = 0; i < table.size(); i++) {
			if (table[i].name == username) {
				taken = true;
				break;
			}
			else {
				taken = false;
			}
		}
		if (taken) {
			std::cout << "\nTheres already an account with this name.\n";
		}
		else if (taken == false) {
			table.push_back({ username, pass, 0.0 });
			loggedIn = static_cast<int>(table.size()) - 1;
		}
	}

	void saveData() {
		std::ofstream file("accounts.txt");

		if (!file) {
			std::cout << "\nCould not open file.\n";
			return;
		}

		for (const auto& acc : table) {
			file << acc.name << "\n";
			file << acc.password << "\n";
			file << acc.balance << "\n";
		}

		file.close();
	}

	void loadData() {
		std::ifstream file("accounts.txt");

		if (!file) {
			return;
		}

		table.clear();

		Accounts temp;

		while (
			std::getline(file, temp.name) &&
			std::getline(file, temp.password) &&
			file >> temp.balance
			) {

			file.ignore();

			table.push_back(temp);
		}

		file.close();
	}

	void logIn(std::string name1, std::string pass1) {
		if (loggedIn < 0) {
			bool found = false;
			for (int i = 0; i < table.size(); i++) {
				if (table[i].name == name1 && table[i].password == pass1) {
					loggedIn = i;
					found = true;
					break;
				}
			}
			if (found) {
				std::cout << "\nLogged in\n";
			}
			else {
				std::cout << "\nError, did not log in\n";
			}
		}
		else {
			std::cout << "\nAn account is already logged in\n";
		}
	}

	void logOut() {
		if (loggedIn < 0) {
			std::cout << "\nAlready logged out\n";
		}
		else {
			loggedIn = -1;
			std::cout << "\nLogged out\n";
		}
	}

	bool isLoggedIn() {
		if (loggedIn >= 0) {
			return true;
		}
		else {
			return false;
		}
	}

	bool getAccounts() {
		if (table.size() > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	void viewBalance() {
		if (loggedIn >= 0) {
			std::cout << "\nYour balance is: " << table[loggedIn].balance << "$\n";
		}
		else {
			std::cout << "Error";
		}
	}

	void withdraw(double amount) {
		if (loggedIn >= 0) {
			if (amount <= table[loggedIn].balance && amount > 0.0) {
				table[loggedIn].balance -= amount;
				std::cout << "\nWithdrew " << amount << "$\n";
			}
			else {
				std::cout << "\nError(2)\n";
			}
		}
		else {
			std::cout << "\nError\n";
		}
	}

	void deposit(double amount) {
		if (loggedIn >= 0) {
			if (amount > 0.0) {
				table[loggedIn].balance += amount;
				std::cout << "\nDeposited " << amount << "$\n";
			}
			else {
				std::cout << "\nError(2)\n";
			}
		}
		else {
			std::cout << "\nError\n";
		}
	}

	void detail() {
		if (loggedIn >= 0) {
			double balance = table[loggedIn].balance;
			std::string name = table[loggedIn].name;
			std::string pass = table[loggedIn].password;

			std::cout << "\n Your balance is: " << balance << "$\n";
			std::cout << "\n Your account name is: " << name << "\n";
			std::cout << "\n Your account password is: " << pass << "\n";
		}
	}

	void transfer(double amount, std::string account) {
		if (loggedIn >= 0) {
			if (amount <= 0.0 || amount > table[loggedIn].balance) {
				std::cout << "\nError. Did not transfer.\n";
				return;
			}
			int targetAccount;
			bool found = false;

			for (int i = 0; i < table.size(); i++) {
				if (table[i].name == account) {
					targetAccount = i;
					found = true;
					break;
				}
				else {
					found = false;
				}
			}

			if (found) {
				if (targetAccount == loggedIn) {
					std::cout << "\nYou can not transfer money to yourself\n";
				}
				else if (targetAccount != loggedIn) {
					table[loggedIn].balance -= amount;
					std::cout << "\nRemoved " << amount << "$ from your account\n";
					table[targetAccount].balance += amount;
					std::cout << "\nAdded " << amount << "$ to " << table[targetAccount].name;
				}
			}
			else {
				std::cout << "\nError. Did not transfer.\n";
			}
		}
		else {
			std::cout << "\nError\n";
		}
	}

	void deleteAccount(const std::string pass) {
		if (loggedIn >= 0) {
			if (pass == table[loggedIn].password) {
				table.erase(table.begin() + loggedIn);
				loggedIn = -1;
				std::cout << "\nAccount deleted.\n";
			}
			else {
				std::cout << "\nIncorrect password.\n";
			}
		}
	}
};

int main() {
	std::cout << "Bank System Loading...\n";
	accountCT User;
	User.loadData();
	do {

		int option;
		std::cout << "\n=== MENU ===\n";
		std::cout << "1. Create account\n";
		std::cout << "2. Account options\n";
		std::cout << "3. Exit\n";
		std::cin >> option;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::cout << "Invalid input. Enter a number.\n";
			continue;
		}

		switch(option) {
		case 1: {
			std::cout << "\n...\n";

			bool loggedIn = User.isLoggedIn();

			if (loggedIn) {
				std::cout << "\nLog out first\n";
			}
			else if (loggedIn == false) {
				std::string name;
				std::string pass;

				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				std::cout << "\nEnter your name: ";
				std::getline(std::cin, name);

				std::cout << "\nCreate your password: ";
				std::getline(std::cin, pass);


				User.createAccount(name, pass);
				User.saveData();
				std::cout << "\nSuccessfully created account";
			}
			
			break;
		}
		case 2: {
			bool exitopt = true;
			do {
				int option;
				std::cout << "\n=== VAGGELIS BANK ===\n";
				std::cout << "1. View account details\n";
				std::cout << "2. View balance\n";
				std::cout << "3. Withdraw money\n";
				std::cout << "4. Deposit money\n";
				std::cout << "5. Log out\n";
				std::cout << "6. Log in\n";
				std::cout << "7. Transfer money\n";
				std::cout << "8. Delete account\n";
				std::cout << "9. Exit account options\n";
				std::cin >> option;

				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

					std::cout << "Invalid input. Enter a number.\n";
					continue;
				}

				if (option == 1) {
					char option;
					std::cout << "\nAre you sure? This will show your password.(Y/N)\n";
					std::cin >> option;

					if (option == 'Y' || option == 'y') {
						User.detail();
					}
					else {
						std::cout << "\nDid not detail account.\n";
						continue;
					}
				}
				else if (option == 2) {
					User.viewBalance();
				}
				else if (option == 3) {
					int amount = 0;
					std::cout << "\nEnter amount: ";
					std::cin >> amount;

					if (std::cin.fail()) {
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

						std::cout << "Invalid input. Enter a number.\n";
					}
					else {
						User.withdraw(amount);
						User.saveData();
					}
				}
				else if (option == 4) {
					int amount = 0;
					std::cout << "\nEnter amount: ";
					std::cin >> amount;

					if (std::cin.fail()) {
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

						std::cout << "Invalid input. Enter a number.\n";
					}
					else {
						User.deposit(amount);
						User.saveData();
					}
				}
				else if (option == 5) {
					std::cout << "\nLogging out...\n";
					User.saveData();
					User.logOut();
				}
				else if (option == 6) {
					std::string name;
					std::string pass;

					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

					std::cout << "\nEnter name: ";
					std::getline(std::cin, name);

					std::cout << "\nEnter password: ";
					std::getline(std::cin, pass);

					User.logIn(name, pass);
				}
				else if (option == 7) {
					int amount;
					std::string account;

					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

					std::cout << "\nEnter the account name you want to transfer the money to: ";
					std::getline(std::cin, account);
					std::cout << "\nEnter the amount of money you want to transfer to " << account << " :";
					std::cin >> amount;

					if (std::cin.fail()) {
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

						std::cout << "Invalid input. Enter a number.\n";
					}
					else {
						User.transfer(amount, account);
						User.saveData();
					}
				}
				else if (option == 8) {
					std::string password;

					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

					std::cout << "\nEnter your password to confirm the delete: ";
					std::getline(std::cin, password);

					User.deleteAccount(password);
					User.saveData();
				}
				else if (option == 9) {
					exitopt = false;
				}
				else {
					std::cout << "Invalid input.\n";
				}

			} while (exitopt);
			break;
		}
		case 3:
			std::cout << "Exiting..";
			return 0;
		default:
			std::cout << "Please enter a valid number.\n";
		}
	} while (true);

	return 0;
}
