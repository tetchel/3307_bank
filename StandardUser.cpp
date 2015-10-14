#include "StandardUser.h"

//in cents
#define MIN_BALANCE 100000
#define NUM_OPTIONS 8

void StandardUser::standardUserOperations(User* user, UserList* userlist) {
	std::vector<std::string> actions;
	actions.push_back("View balance(s)");
	actions.push_back("Withdraw cash");
	actions.push_back("Make a deposit");
	actions.push_back("Transfer funds between your accounts");
	actions.push_back("Transfer funds to another user's account");
	actions.push_back("Request a new account");
	actions.push_back("Close an account");

	int input = 0;
	while(input != NUM_OPTIONS) {
		if(user->getChequing() == -1 && user->getSavings() == -1) {
			std::cout << "You must open an account before you can do anything else." << std::endl;
			input = 6;
		}
		else {
			input = IOUtils::getUserAction(&actions);
		}

		int chq = user->getChequing();
		int sav = user->getSavings();

		switch(input) {
			//view balances
			case 1: {
				printBalances(user);
				break;
			}
			//withdraw
			case 2: {
				bool again = true;
				while(again) {
					//withdrawing from chequing = true, withdraw from savings = false
					bool chq_withdraw = selectAccount(chq, sav, "From which acccount would you like to withdraw?");

					int deduct = processDeduction(user, chq_withdraw);

					if(deduct != 0) {
						user->modifyBalance(chq_withdraw, -deduct);
						std::cout << "Withdrawal successful." << std::endl;
						printBalances(user);
					}
					else {
						std::cout << "Withdrawal cancelled." << std::endl;
					}

					again = IOUtils::getUserResponse("Perform another withdrawal? ", 'y', 'n');
				}
				break;
			}
			//deposit
			case 3: {
				bool again = true;
				while(again) {
					bool chq_dep = selectAccount(chq, sav, "To which acccount would you like to deposit?");

					int deposit = getDollarAmount();

					user->modifyBalance(chq_dep, deposit);
					printBalances(user);

					again = IOUtils::getUserResponse("Perform another deposit? ", 'y', 'n');
				}
				break;
			}
			//transfer between accounts
			case 4: {
				if(chq == -1 || sav == -1) {
					std::cout << "You only have one open account, so you can't make this kind of transfer.";
					break;
				}
				bool from_chq = IOUtils::getUserResponse("From which account would you like to transfer?", 'c', 's');

				int deduct = processDeduction(user, from_chq);
				if(deduct != 0) {
					user->modifyBalance(from_chq, -deduct);
					user->modifyBalance(!from_chq, deduct);
					std::cout << "Transfer successful." << std::endl;
					printBalances(user);
				}
				else
					std::cout << "Transfer cancelled." << std::endl;
			}
			//transfer between users
			case 5: {
				bool again = true;
				while(again) {
					bool chq_trans = selectAccount(chq, sav, "From which account would you like to make a transfer?");

					int deduct = processDeduction(user, chq_trans);

					if(deduct != 0) {
						bool enterUserAgain = true;
						while(enterUserAgain) {
							std::cout << "Enter the username to make the transfer to: ";
							std::string username;
							std::cin >> username;

							transform(username.begin(), username.end(), username.begin(), ::tolower);

							User* recipent = userlist->getUser(username);
							if(username.compare("manager") == 0 || username.compare("admin") == 0 || username.compare(user->getUsername()) == 0) {
                                std::cout << "You can't make a transfer to that person!" << std::endl;
                                //enterUserAgain stays true, try again
							}
							else if(recipent != NULL) {
								//transfers go into chequing because that makes sense
								recipent->modifyBalance(true, deduct);
								user->modifyBalance(chq_trans, -deduct);
								std::cout << "Transfer to " << username << " successful." << std::endl;
								enterUserAgain = false;
							}
							else {
								std::cout << "Recipent username was not found in the system." << std::endl;
								enterUserAgain = IOUtils::getUserResponse("Try a new username?", 'y', 'n');
							}
						}
					}
					again = IOUtils::getUserResponse("Would you like to make another transfer?", 'y', 'n');
				}
				break;
			}
			//request a new account
			case 6: {
				bool chq_open = IOUtils::getUserResponse("What type of account would you like to open?", 'c', 's');
				if(chq_open) {
					if(chq == -1) {
						user->modifyBalance(true, 1);
						std::cout << "Chequing account successfully opened!" << std::endl;
					}
					else
						std::cout << "You already have a chequing account!" << std::endl;
				}
				else {
					if(sav == -1) {
						user->modifyBalance(false, 1);
						std::cout << "Savings account successfully opened!" << std::endl;
					}
					else
						std::cout << "You already have a savings account!" << std::endl;
				}
				break;
			}
			//close an account
			case 7: {
				std::cout << "You must have $0.00 balance in an account in order to be able to close it." << std::endl;
				if(selectAccount(chq, sav, "Which account would you like to close?")) {
					if(chq == 0) {
						user->modifyBalance(true, -1);
						std::cout << "Your chequing account has been closed." << std::endl;
					}
					else {
						std::cout << "Chequing balance is not zero, account not closed." << std::endl;
					}
				}
				else {
					if(sav == 0) {
						user->modifyBalance(false, -1);
						std::cout << "Your savings account has been closed." << std::endl;
					}
					else {
						std::cout << "Savings balance is not zero, account not closed." << std::endl;
					}
				}
				break;
			}
		}
		std::cout << std::endl;
	}
}

//returns true for chq, false for sav
//assumes they have an account, which is valid.
bool StandardUser::selectAccount(int chq_bal, int sav_bal, std::string msg) {
	if(chq_bal != -1) {
		if(sav_bal != -1)
			return IOUtils::getUserResponse(msg, 'c', 's');
		else
			return true;
	}
	else
		return false;
}

void StandardUser::printBalances(User* user) {
	int chq = user->getChequing();
	int sav = user->getSavings();
	if(chq == -1 && sav == -1) {
		std::cout << "You don't have any open accounts!" << std::endl;
		return;
	}
	std::cout << "Your current balances:" << std::endl;

	if(chq != -1)
		std::cout << "Chequing Balance: " << IOUtils::centsToString(chq) << std::endl;
	if(sav != -1)
		std::cout << "Savings Balance:  " << IOUtils::centsToString(sav) << std::endl;
}

int StandardUser::getDollarAmount() {
	//require a dollar amount
	std::cout << "Enter the amount in dollars: ";
	std::cout.flush();
	//garbage variable is for modf call. value is not used
	double amount, garbage;
	while(!(std::cin >> amount) || amount <= 0 || modf(amount*100, &garbage) != 0) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Not a valid input. Enter a positive number only: ";
	}
	//convert dollars to cents
	return amount*100;
}

int StandardUser::processDeduction(User* user, bool chq) {
	int balance = chq ? user->getChequing() : user->getSavings();
	std::cout << IOUtils::centsToString(balance) << " is available." << std::endl;
	int amount = getDollarAmount();
	//MIN_BALANCE doesn't matter for savings accounts
	if(balance - amount > MIN_BALANCE || (balance - amount > 0 && !chq)) {
		return amount;
	}
	else if (balance - amount < 0) {
		std::cout 	<< "Insufficient funds!" << std::endl
					<< "Current balance is " << IOUtils::centsToString(balance) << " and you entered " << IOUtils::centsToString(amount) << std::endl
					<< "You are short " << IOUtils::centsToString(amount-balance) << "." << std::endl;
		bool again = IOUtils::getUserResponse("Enter a smaller amount?", 'y', 'n');
		if(again) {
			return processDeduction(user, chq);
		}
		else
			return 0;
	}
	else {
		if(IOUtils::getUserResponse(
				"Warning: Performing this transaction will result in your account falling below the minimum balance of $1000.00, resulting in a charge of $2.00 CA. Continue?",
				'y', 'n')) {
			if(balance - amount < 200) {
				std::cout << "Insufficient funds to pay the minimum balance fee after transaction." << std::endl;

				return 0;
			}
			else {
				//subtract the fee
				user->modifyBalance(chq, -200);
				return amount;
			}
		}
		else
			return 0;
	}
}
