#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream> 
using namespace std;

const string INPUT_FILE = "file_in.dat";
const string OUTPUT_FILE = "file_out.dat";
const string ERROR_FILE = "file_err.dat";
const string LOG_FILE = "log_out.dat";

const double MIN_BALANCE = -50.00;

const int LIST_SIZE = 15;

class BankAccount {
public:

    BankAccount();
    BankAccount(const BankAccount& NewAccount);
    BankAccount(string SSN, string firstname, string lastname, string email);
    ~BankAccount();

    void setAccount(string newSSN, string newFirstName, string newLastName, string newEmail, int newID, double newAvailableBalance, double newPresentBalance);
    void setAccount(string newSSN, string newFirstName, string newLastName, string newEmail);

    double setPresentBalance(double newPresentBalance);
    double setAvailableBalance(double newAvailableBalance);
    void createCheckingAcc(string domain, int index);

    void setEmail(string newEmail);
    void setID(int newID);
    void setName(string newFirstName, string newLastName);

    const string getFirstName() { return firstName; }
    const string getLastName() { return lastName; }
    const string getSSN() { return SSN; }
    const string getEmail() { return emailAdress; }
    const double getAvailableBalance() { return availableBalance; }
    const double getPresentBalance() { return presentBalance; }
    const int getAccountID() { return accountID; }

    string toString();

private:

    int accountID = 0;
    double availableBalance = 0.00, presentBalance = 100.00;
    string firstName = "", lastName = "", emailAdress = "", SSN = "";

};

void processAccounts(BankAccount validList[], BankAccount invalidList[],BankAccount *pList[], int& validSize, int& invalidSize);
void printListToScreen(BankAccount list[], int size);
void printListToFile(BankAccount list[], int size, const string filename);

void sortMenuOption(BankAccount accountList[], int size);
void searchMenuOption(BankAccount accountList[], int size);
void defaultMenuOption();

void sortAccounts(BankAccount accountList[], const int listSize, int option);
void sortAccountsInner(BankAccount accountList[], const int listSize, int option);

void searchAccounts(BankAccount accountList[], const int listSize, int option);
void searchAccountsInner(BankAccount accountList[], const int listSize, int option);

int main()
{

    enum {

        SORT = 1,
        SEARCH,
        QUIT

    };

    BankAccount validAccounts[LIST_SIZE], invalidAccounts[LIST_SIZE], *pAccountList[LIST_SIZE];
    int validAccountSize = -1, invalidAccountSize = -1;
    processAccounts(validAccounts, invalidAccounts, pAccountList, validAccountSize, invalidAccountSize);    

    int input = 0;
    while (input != QUIT) {

        input = 0;
        cout << "\nMenu:\n1.Sort\n2.Search\n3.Quit\n\nInput: ";
        cin >> input;

        switch (input) {
        case SORT:
            sortMenuOption(*pAccountList, validAccountSize);
            break;
        case SEARCH:
            searchMenuOption(*pAccountList, validAccountSize);
            break;
        case QUIT:
            break;
        default:
            defaultMenuOption();
            break;

        }

    }


    return 0;
}

BankAccount::BankAccount() {
    //these will be the default paramiters, I wasnt able to find anything that mentioned what the specifics were for the default
    setAccount("0000000000", "FirstName", "LastName", "user_name@mailserver.domain", 0, 0, 0);

}
BankAccount::BankAccount(const BankAccount& copyFromAccount) {
    //I called it "copyFromAccount to remind myself that the 'BankAccount' you are copying from is the one being passed through the function.

    setAccount(copyFromAccount.SSN, copyFromAccount.firstName, copyFromAccount.lastName, copyFromAccount.emailAdress, copyFromAccount.accountID, copyFromAccount.availableBalance, copyFromAccount.presentBalance);

}
BankAccount::BankAccount(string SSN, string firstname, string lastname, string email) {

    setAccount(SSN, firstname, lastname, email, accountID, availableBalance, presentBalance);

}
BankAccount::~BankAccount() {

    setAccount("0000000000", "FirstName", "LastName", "user_name@mailserver.domain", 0, 0, 0);

}

void BankAccount::setAccount(string newSSN, string newFirstName, string newLastName, string newEmail, int newID, double newAvailableBalance, double newPresentBalance) {

    firstName = newFirstName;
    lastName = newLastName;

    emailAdress = newEmail;
    accountID = newID;

    availableBalance = setAvailableBalance(newAvailableBalance);
    presentBalance = setPresentBalance(newPresentBalance);

    SSN = newSSN;
}
void BankAccount::setAccount(string newSSN, string newFirstName, string newLastName, string newEmail) {

    setAccount(newSSN, newFirstName, newLastName, newEmail, accountID, availableBalance, presentBalance);

}
void BankAccount::setName(string newFirstName, string newLastName) {

    setAccount(SSN, newFirstName, newLastName, emailAdress, accountID, availableBalance, presentBalance);

}

double BankAccount::setPresentBalance(double newPresentBalance) {
    //rather than call "SetAccount", these functions are called within "setAccount" to ensure that they are valid anytime they are changed, 
    // and the function can still be called to change only "presetBalance"

    if (newPresentBalance < MIN_BALANCE) {

        cout << "Present balance cannot be less than $50.00, cancelling request...\n";
        newPresentBalance = presentBalance;

    }

    return newPresentBalance;

}
double BankAccount::setAvailableBalance(double newAvailableBalance) {
    //rather than call "SetAccount", these functions are called within "setAccount" to ensure that they are valid anytime they are changed, 
    // and the function can still be called to change only "availableBalance, just like in "setPresentBalance"

    if (newAvailableBalance > presentBalance) {

        cout << "Available balance cannot be greater, cancelling request...\n";
        newAvailableBalance = availableBalance;

    }
    else if (newAvailableBalance < MIN_BALANCE) {

        cout << "Available balance cannot be less than $50.00, cancelling request...\n";
        newAvailableBalance = availableBalance;

    }
    return newAvailableBalance;

}
void BankAccount::createCheckingAcc(string domain, int index) {

    accountID = (((rand() % 1000) + 1) * 100) + (index + 1);

    if (domain == "edu") {

        presentBalance = setPresentBalance(150.00);

    }
    else {

        presentBalance = setPresentBalance(100.00);

    }


}

void BankAccount::setEmail(string newEmail) {

    setAccount(SSN, firstName, lastName, newEmail, accountID, availableBalance, presentBalance);

}
void BankAccount::setID(int newID) {

    setAccount(SSN, firstName, lastName, emailAdress, newID, availableBalance, presentBalance);

}

string BankAccount::toString() {

    stringstream accountString;
    accountString << left << setw(15) << SSN << setw(15) << firstName << setw(15) << lastName << setw(25) << emailAdress << right << setw(10) << accountID << setw(20) << availableBalance << setw(20) << presentBalance << "\n";
    return accountString.str();
}

void processAccounts(BankAccount validList[], BankAccount invalidList[], BankAccount* pList[], int& validSize, int& invalidSize) {

    ifstream infile;

    infile.open(INPUT_FILE);

    if (!infile) {
        cout << "Cannot open file" << endl;
        exit(EXIT_FAILURE);
    }

    string tempFirstName = "", tempLastName = "", tempEmailAdress = "", tempSSN = "";
    BankAccount tempAccount;
    int usernameSize = 0, mailserverSize = 0, firstNameSize = 0, lastNameSize = 0, ssnSize = 0, index = 0, requestCount = 0;
    string domain = "";


    infile >> tempSSN >> tempFirstName >> tempLastName >> tempEmailAdress;

    while (infile) {

        
        index = 0, usernameSize = 0, mailserverSize = 0, firstNameSize = 0, lastNameSize = 0, ssnSize = 0, index = 0;
        domain = "";
        tempAccount.setAccount(tempSSN, tempFirstName, tempLastName, tempEmailAdress);

        while (tempEmailAdress[index] != '@') {

            if ((tempEmailAdress[index] >= '0' && tempEmailAdress[index] <= '9') || (tempEmailAdress[index] >= 'A' && tempEmailAdress[index] <= 'Z') || (tempEmailAdress[index] >= 'a' && tempEmailAdress[index] <= 'z')) {

                usernameSize++;

            }
            index++;
        }
        while (tempEmailAdress[index] != '.') {

            if ((tempEmailAdress[index] >= 'A' && tempEmailAdress[index] <= 'Z') || (tempEmailAdress[index] >= 'a' && tempEmailAdress[index] <= 'z')) {

                mailserverSize++;

            }
            index++;
        }

        for (int i = tempEmailAdress.length() - 3; i < tempEmailAdress.length(); i++) {

            if (tempEmailAdress[i] >= 'a' && tempEmailAdress[i] <= 'z') {

                domain = domain + tempEmailAdress[i];

            }

        }

        for (int i = 0; i < tempFirstName.length(); i++) {

            if ((tempFirstName[i] >= 'A' && tempFirstName[i] <= 'Z') || (tempFirstName[i] >= 'a' && tempFirstName[i] <= 'z')) {

                firstNameSize++;

            }

        }
        for (int i = 0; i < tempLastName.length(); i++) {

            if ((tempLastName[i] >= 'A' && tempLastName[i] <= 'Z') || (tempLastName[i] >= 'a' && tempLastName[i] <= 'z')) {

                lastNameSize++;

            }

        }

        for (int i = 0; i < tempSSN.length(); i++) {

            if (tempSSN[i] >= '0' && tempSSN[i] <= '9') {

                ssnSize++;

            }

        }

        if ((ssnSize > 9) && (usernameSize > 3) && (firstNameSize > 1) && (lastNameSize > 1) && (mailserverSize > 3) && ((domain == "edu") || (domain == "com"))) {

            if (validSize < 14) {

                validSize++;
                validList[validSize] = tempAccount;
                validList[validSize].createCheckingAcc(domain, validSize);
                pList[validSize] = &validList[validSize];

            }

        }
        else if ((ssnSize < 9) || (usernameSize < 3) || (firstNameSize < 1) || (lastNameSize < 1) || (mailserverSize < 3) || ((domain != "edu") || (domain != "com"))) {

            if (invalidSize < 14) {

                invalidSize++;
                invalidList[invalidSize] = tempAccount;

            }

        }

        requestCount++;

        infile >> tempSSN >> tempFirstName >> tempLastName >> tempEmailAdress;

    }

    if (validSize >= 15) {

        cout << "Warning: Max file sized reached, some valid accounts may not be recorded\n";
        validSize = 14;

    }

    if (invalidSize >= 15) {

        cout << "Warning: Max file sized reached, some invalid accounts may not be recorded\n";
        invalidSize = 14;

    }
    validSize++;
    invalidSize++;

    cout << "\nRequests Processed: " << requestCount << "\nSuccsesfull Accounts: " << validSize << "\nUnsuccesfull Accounts: " << invalidSize << "\nAccounts not stored: " << requestCount - (validSize + invalidSize) << endl;

    infile.close();

}
void printListToScreen(BankAccount list[], int size) {

    if (size <= 0) {
        cout << "There are none available at the moment, make you you've processed all checking account requests\n";
    }
    else {

        for (int i = 0; i < size; i++) {

            cout << list[i].toString();

        }

    }

}
void printListToFile(BankAccount list[], int size, const string filename) {

    ofstream outfile;
    outfile.open(filename);

    if (size <= 0) {
        cout << "There are none available at the moment, make you you've processed all checking account requests\n";
    }
    else {

        for (int i = 0; i < size; i++) {

            outfile << list[i].toString();

        }

    }

    outfile.close();

}

void sortMenuOption(BankAccount accountList[], int size) {

    enum {

        FIRST_NAME = 1, 
        LAST_NAME, 
        ACCOUNT_ID, 
        AVAILABLE_BAL, 
        PRESENT_BAL, 
        SSN, 
        EMAIL,
        BACK_TO_MENU

    };
    int sortOption = 0;
    while (sortOption != BACK_TO_MENU) {

        sortOption = 0;
        cout << "\nSort by:\n1.First name\n2.Last name\n3.Account ID\n4.Available balance\n5.present balance\n6.SSN\n7.email\n8.Back to Menu\n\nInput: ";
        cin >> sortOption;

        switch (sortOption) {
        case FIRST_NAME:
            sortAccounts(accountList, size, sortOption);
            break;
        case LAST_NAME:
            sortAccounts(accountList, size, sortOption);
            break;
        case ACCOUNT_ID:
            sortAccounts(accountList, size, sortOption);
            break;
        case AVAILABLE_BAL:
            sortAccounts(accountList, size, sortOption);
            break;
        case PRESENT_BAL:
            sortAccounts(accountList, size, sortOption);
            break;
        case SSN:
            sortAccounts(accountList, size, sortOption);
            break;
        case EMAIL:
            sortAccounts(accountList, size, sortOption);
            break;
        case BACK_TO_MENU:
            cout << "Going back to the main menu...\n";
            break;
        default:
            defaultMenuOption();;
            break;

        }

    }

}
void searchMenuOption(BankAccount accountList[], int size) {

    enum {

        ID = 1,
        FIRST_NAME,
        LAST_NAME,
        EMAIL,
        BACK_TO_MENU

    };
    int searchOption = 0;
    while (searchOption != BACK_TO_MENU) {

        searchOption = 0;
        cout << "\nSearch by:\n1.ID\n2.First name\n3.Last name\n4.Email\n5.Back to Menu\n\nInput: ";
        cin >> searchOption;

        switch (searchOption) {
        case ID:
            searchAccounts(accountList, size, searchOption);
            break;
        case FIRST_NAME:
            searchAccounts(accountList, size, searchOption);
            break;
        case LAST_NAME:
            searchAccounts(accountList, size, searchOption);
            break;
        case EMAIL:
            searchAccounts(accountList, size, searchOption);
            break;
        case BACK_TO_MENU:
            cout << "Going back to the main menu...\n";
            break;
        default:
            defaultMenuOption();
            break;

        }

    }

}
void defaultMenuOption() {

    cout << "Invalid choice, try again\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

}

void sortAccounts(BankAccount accountList[], const int listSize, int option) {

    sortAccountsInner(accountList, listSize, option);
    cout << "\nSSN            First Name     Last Name      Email                    Account ID     Present Balance   Available Balance\n========================================================================================================================\n";
    printListToScreen(accountList, listSize);

}
void sortAccountsInner(BankAccount accountList[], const int listSize, int option) {

    BankAccount tempAcc;

    for (int i = 0; i < listSize; i++) {

        for (int g = 0; g < listSize; g++) {

            if ((accountList[i].getFirstName() < accountList[g].getFirstName()) && option == 1) {

                tempAcc = accountList[i];
                accountList[i] = accountList[g];
                accountList[g] = tempAcc;
                
            }else if ((accountList[i].getLastName() < accountList[g].getLastName()) && option == 2) {

                tempAcc = accountList[i];
                accountList[i] = accountList[g];
                accountList[g] = tempAcc;

            }else if ((accountList[i].getAccountID() < accountList[g].getAccountID()) && option == 3) {

                tempAcc = accountList[i];
                accountList[i] = accountList[g];
                accountList[g] = tempAcc;

            }else if ((accountList[i].getAvailableBalance() > accountList[g].getAvailableBalance()) && option == 4) {

                tempAcc = accountList[i];
                accountList[i] = accountList[g];
                accountList[g] = tempAcc;

            }else if ((accountList[i].getPresentBalance() > accountList[g].getPresentBalance()) && option == 5) {

                tempAcc = accountList[i];
                accountList[i] = accountList[g];
                accountList[g] = tempAcc;

            }else if ((accountList[i].getSSN() < accountList[g].getSSN()) && option == 6) {

                tempAcc = accountList[i];
                accountList[i] = accountList[g];
                accountList[g] = tempAcc;

            }else if ((accountList[i].getEmail() < accountList[g].getEmail()) && option == 7) {

                tempAcc = accountList[i];
                accountList[i] = accountList[g];
                accountList[g] = tempAcc;

            }

        }

    }

}

void searchAccounts(BankAccount accountList[], const int listSize, int option) {

    searchAccountsInner(accountList, listSize, option);

}
void searchAccountsInner(BankAccount accountList[], const int listSize, int option) {

    string input = "";
    int tempSize = 0;

    if (option == 1) {

        cout << "\nSearch by ID: ";
        cin >> input;
        cout << "\nSSN            First Name     Last Name      Email                    Account ID     Present Balance   Available Balance\n========================================================================================================================\n";

        for (int i = 0; i < listSize; i++) {

            size_t found_pos = (to_string(accountList[i].getAccountID())).find(input);

            if (found_pos != string::npos) {
                cout << accountList[i].toString();
                tempSize++;
            }

        }
        if (tempSize == 0) {

            cout << "none found\n";

        }


    } else if (option == 2) {

        cout << "\nSearch by First Name: ";
        cin >> input;
        cout << "\nSSN            First Name     Last Name      Email                    Account ID     Present Balance   Available Balance\n========================================================================================================================\n";

        for (int i = 0; i < listSize; i++) {

            size_t found_pos = (accountList[i].getFirstName()).find(input);

            if (found_pos != string::npos) {
                cout << accountList[i].toString();
                tempSize++;
            }

        }
        if (tempSize == 0) {

            cout << "none found\n";

        }


    } else if (option == 3) {

        cout << "\nSearch by Last Name: ";
        cin >> input;
        cout << "\nSSN            First Name     Last Name      Email                    Account ID     Present Balance   Available Balance\n========================================================================================================================\n";

        for (int i = 0; i < listSize; i++) {

            size_t found_pos = (accountList[i].getLastName()).find(input);

            if (found_pos != string::npos) {
                cout << accountList[i].toString();
                tempSize++;
            }

        }
        if (tempSize == 0) {

            cout << "none found\n";

        }


    } else if (option == 4) {

        cout << "\nSearch by Email: ";
        cin >> input;
        cout << "\nSSN            First Name     Last Name      Email                    Account ID     Present Balance   Available Balance\n========================================================================================================================\n";

        for (int i = 0; i < listSize; i++) {

            size_t found_pos = (accountList[i].getEmail()).find(input);

            if (found_pos != string::npos) {
                cout << accountList[i].toString();
                tempSize++;
            }

        }
        if (tempSize == 0) {

            cout << "none found\n";

        }


    }

}

/*TEST RUN


Requests Processed: 15
Succsesfull Accounts: 15
Unsuccesfull Accounts: 0
Accounts not stored: 0

Menu:
1.Sort
2.Search
3.Quit

Input: 1

Sort by:
1.First name
2.Last name
3.Account ID
4.Available balance
5.present balance
6.SSN
7.email
8.Back to Menu

Input: 1

SSN            First Name     Last Name      Email                    Account ID     Present Balance   Available Balance
========================================================================================================================
9999341862     Alberto        pollem         bug22Bug@lapc.com             28213                   0                 100
0001896545     Alert          gru            despicableMe@lapc.com         14612                   0                 100
3841968436     Dan            Phantom        ghost@lapc.com                35908                   0                 100
7445848988     Dimmy          Iron           Iron_goleM2@lapc.com          82814                   0                 100
5468789875     Jenny          wakeman        Im_arobot@lapc.edu            46510                   0                 150
1111425224     Lou            Who            lee35@lapc.edu                96215                   0                 150
1927730227     Mary           Stan           mary_lee5@lapc.com             4201                   0                 100
9105758202     Pope           Percy          Perc33@lapc.com               46802                   0                 100
1144869521     Spongebob      Squarepants    bullbeSpong@lapc.com          96309                   0                 100
3697415649     Stacy          droo           doppry@lapc.edu               70611                   0                 150
5465462189     Vaons          Cheese         Milkman@lapc.edu              17005                   0                 150
1561652163     Vins           Venus          ilove_space@lapc.com          72506                   0                 100
0012857302     larry          Stallion       Horses@lapc.com               33503                   0                 100
3812684284     paul           Leron          Backetb4ll@lapc.edu           47907                   0                 150
8174489654     vaons          McLame         So_Cool@lapc.edu              50104                   0                 150

Sort by:
1.First name
2.Last name
3.Account ID
4.Available balance
5.present balance
6.SSN
7.email
8.Back to Menu

Input: 2

SSN            First Name     Last Name      Email                    Account ID     Present Balance   Available Balance
========================================================================================================================
5465462189     Vaons          Cheese         Milkman@lapc.edu              17005                   0                 150
7445848988     Dimmy          Iron           Iron_goleM2@lapc.com          82814                   0                 100
3812684284     paul           Leron          Backetb4ll@lapc.edu           47907                   0                 150
8174489654     vaons          McLame         So_Cool@lapc.edu              50104                   0                 150
9105758202     Pope           Percy          Perc33@lapc.com               46802                   0                 100
3841968436     Dan            Phantom        ghost@lapc.com                35908                   0                 100
1144869521     Spongebob      Squarepants    bullbeSpong@lapc.com          96309                   0                 100
0012857302     larry          Stallion       Horses@lapc.com               33503                   0                 100
1927730227     Mary           Stan           mary_lee5@lapc.com             4201                   0                 100
1561652163     Vins           Venus          ilove_space@lapc.com          72506                   0                 100
1111425224     Lou            Who            lee35@lapc.edu                96215                   0                 150
3697415649     Stacy          droo           doppry@lapc.edu               70611                   0                 150
0001896545     Alert          gru            despicableMe@lapc.com         14612                   0                 100
9999341862     Alberto        pollem         bug22Bug@lapc.com             28213                   0                 100
5468789875     Jenny          wakeman        Im_arobot@lapc.edu            46510                   0                 150

Sort by:
1.First name
2.Last name
3.Account ID
4.Available balance
5.present balance
6.SSN
7.email
8.Back to Menu

Input: 3

SSN            First Name     Last Name      Email                    Account ID     Present Balance   Available Balance
========================================================================================================================
1927730227     Mary           Stan           mary_lee5@lapc.com             4201                   0                 100
0001896545     Alert          gru            despicableMe@lapc.com         14612                   0                 100
5465462189     Vaons          Cheese         Milkman@lapc.edu              17005                   0                 150
9999341862     Alberto        pollem         bug22Bug@lapc.com             28213                   0                 100
0012857302     larry          Stallion       Horses@lapc.com               33503                   0                 100
3841968436     Dan            Phantom        ghost@lapc.com                35908                   0                 100
5468789875     Jenny          wakeman        Im_arobot@lapc.edu            46510                   0                 150
9105758202     Pope           Percy          Perc33@lapc.com               46802                   0                 100
3812684284     paul           Leron          Backetb4ll@lapc.edu           47907                   0                 150
8174489654     vaons          McLame         So_Cool@lapc.edu              50104                   0                 150
3697415649     Stacy          droo           doppry@lapc.edu               70611                   0                 150
1561652163     Vins           Venus          ilove_space@lapc.com          72506                   0                 100
7445848988     Dimmy          Iron           Iron_goleM2@lapc.com          82814                   0                 100
1111425224     Lou            Who            lee35@lapc.edu                96215                   0                 150
1144869521     Spongebob      Squarepants    bullbeSpong@lapc.com          96309                   0                 100

Sort by:
1.First name
2.Last name
3.Account ID
4.Available balance
5.present balance
6.SSN
7.email
8.Back to Menu

Input: 4

SSN            First Name     Last Name      Email                    Account ID     Present Balance   Available Balance
========================================================================================================================
1927730227     Mary           Stan           mary_lee5@lapc.com             4201                   0                 100
0001896545     Alert          gru            despicableMe@lapc.com         14612                   0                 100
5465462189     Vaons          Cheese         Milkman@lapc.edu              17005                   0                 150
9999341862     Alberto        pollem         bug22Bug@lapc.com             28213                   0                 100
0012857302     larry          Stallion       Horses@lapc.com               33503                   0                 100
3841968436     Dan            Phantom        ghost@lapc.com                35908                   0                 100
5468789875     Jenny          wakeman        Im_arobot@lapc.edu            46510                   0                 150
9105758202     Pope           Percy          Perc33@lapc.com               46802                   0                 100
3812684284     paul           Leron          Backetb4ll@lapc.edu           47907                   0                 150
8174489654     vaons          McLame         So_Cool@lapc.edu              50104                   0                 150
3697415649     Stacy          droo           doppry@lapc.edu               70611                   0                 150
1561652163     Vins           Venus          ilove_space@lapc.com          72506                   0                 100
7445848988     Dimmy          Iron           Iron_goleM2@lapc.com          82814                   0                 100
1111425224     Lou            Who            lee35@lapc.edu                96215                   0                 150
1144869521     Spongebob      Squarepants    bullbeSpong@lapc.com          96309                   0                 100

Sort by:
1.First name
2.Last name
3.Account ID
4.Available balance
5.present balance
6.SSN
7.email
8.Back to Menu

Input: 5

SSN            First Name     Last Name      Email                    Account ID     Present Balance   Available Balance
========================================================================================================================
5465462189     Vaons          Cheese         Milkman@lapc.edu              17005                   0                 150
5468789875     Jenny          wakeman        Im_arobot@lapc.edu            46510                   0                 150
3812684284     paul           Leron          Backetb4ll@lapc.edu           47907                   0                 150
8174489654     vaons          McLame         So_Cool@lapc.edu              50104                   0                 150
3697415649     Stacy          droo           doppry@lapc.edu               70611                   0                 150
1111425224     Lou            Who            lee35@lapc.edu                96215                   0                 150
0001896545     Alert          gru            despicableMe@lapc.com         14612                   0                 100
9105758202     Pope           Percy          Perc33@lapc.com               46802                   0                 100
1927730227     Mary           Stan           mary_lee5@lapc.com             4201                   0                 100
9999341862     Alberto        pollem         bug22Bug@lapc.com             28213                   0                 100
0012857302     larry          Stallion       Horses@lapc.com               33503                   0                 100
1561652163     Vins           Venus          ilove_space@lapc.com          72506                   0                 100
7445848988     Dimmy          Iron           Iron_goleM2@lapc.com          82814                   0                 100
3841968436     Dan            Phantom        ghost@lapc.com                35908                   0                 100
1144869521     Spongebob      Squarepants    bullbeSpong@lapc.com          96309                   0                 100

Sort by:
1.First name
2.Last name
3.Account ID
4.Available balance
5.present balance
6.SSN
7.email
8.Back to Menu

Input: 6

SSN            First Name     Last Name      Email                    Account ID     Present Balance   Available Balance
========================================================================================================================
0001896545     Alert          gru            despicableMe@lapc.com         14612                   0                 100
0012857302     larry          Stallion       Horses@lapc.com               33503                   0                 100
1111425224     Lou            Who            lee35@lapc.edu                96215                   0                 150
1144869521     Spongebob      Squarepants    bullbeSpong@lapc.com          96309                   0                 100
1561652163     Vins           Venus          ilove_space@lapc.com          72506                   0                 100
1927730227     Mary           Stan           mary_lee5@lapc.com             4201                   0                 100
3697415649     Stacy          droo           doppry@lapc.edu               70611                   0                 150
3812684284     paul           Leron          Backetb4ll@lapc.edu           47907                   0                 150
3841968436     Dan            Phantom        ghost@lapc.com                35908                   0                 100
5465462189     Vaons          Cheese         Milkman@lapc.edu              17005                   0                 150
5468789875     Jenny          wakeman        Im_arobot@lapc.edu            46510                   0                 150
7445848988     Dimmy          Iron           Iron_goleM2@lapc.com          82814                   0                 100
8174489654     vaons          McLame         So_Cool@lapc.edu              50104                   0                 150
9105758202     Pope           Percy          Perc33@lapc.com               46802                   0                 100
9999341862     Alberto        pollem         bug22Bug@lapc.com             28213                   0                 100

Sort by:
1.First name
2.Last name
3.Account ID
4.Available balance
5.present balance
6.SSN
7.email
8.Back to Menu

Input: 7

SSN            First Name     Last Name      Email                    Account ID     Present Balance   Available Balance
========================================================================================================================
3812684284     paul           Leron          Backetb4ll@lapc.edu           47907                   0                 150
0012857302     larry          Stallion       Horses@lapc.com               33503                   0                 100
5468789875     Jenny          wakeman        Im_arobot@lapc.edu            46510                   0                 150
7445848988     Dimmy          Iron           Iron_goleM2@lapc.com          82814                   0                 100
5465462189     Vaons          Cheese         Milkman@lapc.edu              17005                   0                 150
9105758202     Pope           Percy          Perc33@lapc.com               46802                   0                 100
8174489654     vaons          McLame         So_Cool@lapc.edu              50104                   0                 150
9999341862     Alberto        pollem         bug22Bug@lapc.com             28213                   0                 100
1144869521     Spongebob      Squarepants    bullbeSpong@lapc.com          96309                   0                 100
0001896545     Alert          gru            despicableMe@lapc.com         14612                   0                 100
3697415649     Stacy          droo           doppry@lapc.edu               70611                   0                 150
3841968436     Dan            Phantom        ghost@lapc.com                35908                   0                 100
1561652163     Vins           Venus          ilove_space@lapc.com          72506                   0                 100
1111425224     Lou            Who            lee35@lapc.edu                96215                   0                 150
1927730227     Mary           Stan           mary_lee5@lapc.com             4201                   0                 100

Sort by:
1.First name
2.Last name
3.Account ID
4.Available balance
5.present balance
6.SSN
7.email
8.Back to Menu

Input: 8
Going back to the main menu...

Menu:
1.Sort
2.Search
3.Quit

Input: 2

Search by:
1.ID
2.First name
3.Last name
4.Email
5.Back to Menu

Input: 5
Going back to the main menu...

Menu:
1.Sort
2.Search
3.Quit

Input: 2

Search by:
1.ID
2.First name
3.Last name
4.Email
5.Back to Menu

Input: 1

Search by ID: 87

SSN            First Name     Last Name      Email                    Account ID     Present Balance   Available Balance
========================================================================================================================
none found

Search by:
1.ID
2.First name
3.Last name
4.Email
5.Back to Menu

Input: 1

Search by ID: 10

SSN            First Name     Last Name      Email                    Account ID     Present Balance   Available Balance
========================================================================================================================
5468789875     Jenny          wakeman        Im_arobot@lapc.edu            46510                   0                 150
8174489654     vaons          McLame         So_Cool@lapc.edu              50104                   0                 150

Search by:
1.ID
2.First name
3.Last name
4.Email
5.Back to Menu

Input: 2

Search by First Name: je

SSN            First Name     Last Name      Email                    Account ID     Present Balance   Available Balance
========================================================================================================================
none found

Search by:
1.ID
2.First name
3.Last name
4.Email
5.Back to Menu

Input: 2

Search by First Name: E

SSN            First Name     Last Name      Email                    Account ID     Present Balance   Available Balance
========================================================================================================================
none found

Search by:
1.ID
2.First name
3.Last name
4.Email
5.Back to Menu

Input: 2

Search by First Name: e

SSN            First Name     Last Name      Email                    Account ID     Present Balance   Available Balance
========================================================================================================================
5468789875     Jenny          wakeman        Im_arobot@lapc.edu            46510                   0                 150
9105758202     Pope           Percy          Perc33@lapc.com               46802                   0                 100
9999341862     Alberto        pollem         bug22Bug@lapc.com             28213                   0                 100
1144869521     Spongebob      Squarepants    bullbeSpong@lapc.com          96309                   0                 100
0001896545     Alert          gru            despicableMe@lapc.com         14612                   0                 100

Search by:
1.ID
2.First name
3.Last name
4.Email
5.Back to Menu

Input: 3

Search by Last Name: an

SSN            First Name     Last Name      Email                    Account ID     Present Balance   Available Balance
========================================================================================================================
5468789875     Jenny          wakeman        Im_arobot@lapc.edu            46510                   0                 150
1144869521     Spongebob      Squarepants    bullbeSpong@lapc.com          96309                   0                 100
3841968436     Dan            Phantom        ghost@lapc.com                35908                   0                 100
1927730227     Mary           Stan           mary_lee5@lapc.com             4201                   0                 100

Search by:
1.ID
2.First name
3.Last name
4.Email
5.Back to Menu

Input: 4

Search by Email: .com

SSN            First Name     Last Name      Email                    Account ID     Present Balance   Available Balance
========================================================================================================================
0012857302     larry          Stallion       Horses@lapc.com               33503                   0                 100
7445848988     Dimmy          Iron           Iron_goleM2@lapc.com          82814                   0                 100
9105758202     Pope           Percy          Perc33@lapc.com               46802                   0                 100
9999341862     Alberto        pollem         bug22Bug@lapc.com             28213                   0                 100
1144869521     Spongebob      Squarepants    bullbeSpong@lapc.com          96309                   0                 100
0001896545     Alert          gru            despicableMe@lapc.com         14612                   0                 100
3841968436     Dan            Phantom        ghost@lapc.com                35908                   0                 100
1561652163     Vins           Venus          ilove_space@lapc.com          72506                   0                 100
1927730227     Mary           Stan           mary_lee5@lapc.com             4201                   0                 100

Search by:
1.ID
2.First name
3.Last name
4.Email
5.Back to Menu

Input: 4

Search by Email: .edu

SSN            First Name     Last Name      Email                    Account ID     Present Balance   Available Balance
========================================================================================================================
3812684284     paul           Leron          Backetb4ll@lapc.edu           47907                   0                 150
5468789875     Jenny          wakeman        Im_arobot@lapc.edu            46510                   0                 150
5465462189     Vaons          Cheese         Milkman@lapc.edu              17005                   0                 150
8174489654     vaons          McLame         So_Cool@lapc.edu              50104                   0                 150
3697415649     Stacy          droo           doppry@lapc.edu               70611                   0                 150
1111425224     Lou            Who            lee35@lapc.edu                96215                   0                 150

Search by:
1.ID
2.First name
3.Last name
4.Email
5.Back to Menu

Input: 5
Going back to the main menu...

Menu:
1.Sort
2.Search
3.Quit

Input: 3

C:\Users\Matteo\source\repos\Lab #3 Pointers Sort & Search F25\x64\Debug\Lab #3 Pointers Sort & Search F25.exe (process 26996) exited with code 0.
Press any key to close this window . . .

*/