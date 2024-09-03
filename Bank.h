using std::cout;
using std::cin;

class Bank {
private:
    std::string username, lastname, password;
    int age, year;
    char user_command;
    double balance;

    void clearScreen(){
        std::system("clear");
    }

    void wait(int seconds){
        sleep(seconds);
    }

    bool validateInput(){
        if (cin.fail()){
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input, please try again.\n";
            return false;
        }
        return true;
    }

    void Register() {
    cout << "\nEnter your username (first name): "; cin >> username;
    cout << "\nEnter your lastname: "; cin >> lastname;
    cout << "\nEnter your password: "; cin >> password;
    cout << "\nEnter your age: "; cin >> age;
    cout << "\nEnter your year of birth: "; cin >> year;
        if (year < 1950 || year > 2010) {
            cout << "Your age is invalid or you are too young\n";
        } 
        else {
            // General user information for Account info 
            std::ofstream user_info(username + "_info.txt", std::ofstream::out | std::ofstream::trunc);
            if (user_info.is_open()) {
                // user_info << username << std::endl << password;
                user_info << "Name: " << username << " " << lastname
                          << "\nAge: " << age << "\nYear: " << year 
                          << "\nPassword: " << password << "\n";
                user_info.close();

                // User's username and password
                std::ofstream user_name_password(username + ".txt", std::ofstream::out | std::ostream::trunc);
                if (user_name_password.is_open()){
                    user_name_password << username << "\n" << password;
                    user_name_password.close();
                }
                wait(1);
                cout << "\nRegistration completed successfully\n";
                wait(2);
                clearScreen();
                BankMenu();
            } 
            else {
                cout << "\nError: Unable to create user file.\n";
            }
        }
    }

    void LogIn() {
        cout << "\nEnter your username: "; cin >> username;
        cout << "\nEnter your password: "; cin >> password;
        std::ifstream read(username + ".txt");

        std::string check_username, check_password;

        if (read.is_open()) {
            getline(read, check_username); // Read the username
            getline(read, check_password); // Read the password
            if (username == check_username && password == check_password) {
                wait(1);
                cout << "\nWelcome back " << username << "\n";
                wait(2);
                clearScreen();
                BankMenu();
            } 
            else {
                cout << "\nInvalid username or password. Please try again.\n";
            }
        } 
        else {
            cout << "User not found. Please register first.\n";
        }
    }

        void AccountInfo(){
        cout << "Your personal information\n\n";
        wait(1);
        std::ifstream tiop(username + "_info.txt");
        char ch;
        if (!tiop.is_open()) {
            cout << "Unable to open account info file.\n";
            return;
        }
        while (tiop)
        {
            tiop.get(ch);
            cout << ch;
        }
        wait(1);
        cout <<"Enter [0] to go back\n"; cin >> user_command;
        wait(1);
        clearScreen();
        BankMenu();
    }

    void Deposit(){
        cout << "\tBank Deposit page\n\n";
        double amount;
        wait(1);
        cout << "Enter the amout of money -> "; cin >> amount;
        wait(1);
        cout << "\nLoading...\n\n";
        wait(2);
        if (!validateInput() || amount <= 0 || amount >= 1000){
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input or amount of money\n";
        }
        else {
            balance += amount;
            cout << "Deposit added successfully\n";
        }
        wait(2);
        clearScreen();
    }

    void CheckBalance(){
        cout << "Your balance information\n\n";
        cout << "Name: "<< username << " "<< lastname<<"\n";
        wait(2);
        cout << "\nYour current balance is "<< balance<<"£\n";
        wait(4);
        clearScreen();
    }

    void Withdrawal(){
        cout << "\tWithdrawal page\n";
        double amount;
        cout << "\nEnter the amount of money -> "; cin >> amount;
        wait(1);
        cout << "\nLoading...\n";
        if (!validateInput() || amount <= 0 || amount > balance) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "\nInvalid or insufficient funds. Please try again.\n";
        }
        else {
            balance -= amount;
            cout << "Withdrawal successful\n";
        }
        wait(4);
        clearScreen();
    }

public:

    Bank(){
        balance = 0.00;
    }

    bool PanelMenu() {
        std::string choice;
        while (true) {
            cout << "\tWelcome to the Central_Bank\n" << std::endl;
            cout << "Enter 'Log' to log in to your account" << std::endl;
            cout << "Enter 'Reg' for registration \n" << std::endl;
            cout << "Enter your choice -> ";
            cin >> choice;

            if (choice == "Log" || choice == "log") {
                LogIn();
                return false;
            } 
            else if (choice == "Reg" || choice == "reg") {
                Register();
                return false;
            } 
            else {
                wait(1);
                cout << "\nInvalid choice. Please try again.\n";
                wait(2);
                clearScreen();
                
            }
        }
    }

    void BankMenu() {

        while(user_command != '5'){
            cout << "\tWelcome to the Bank page " << username << "\n\n";
            cout << "==========================================";
            cout << "\n| " << "[1] --> Account info" << "                   | ";
            cout << "\n| " << "[2] --> Deposit" << "                        | ";
            cout << "\n| " << "[3] --> Check balance" << "                  | ";
            cout << "\n| " << "[4] --> Withdrawal" << "                     | ";
            cout << "\n| " << "[5] --> exit" << "                           | ";
            cout << "\n==========================================\n";

            cout << "\nEnter the command: "; cin >> user_command;
            
            switch (user_command){
            case '0':
                wait(1); clearScreen(); BankMenu();
                break;
            case '1':
                wait(1); clearScreen(); AccountInfo();
                break;
            case '2':
                wait(1); clearScreen(); Deposit();
                break;
            case '3':
                wait(1); clearScreen(); CheckBalance();
                break;
            case '4':
                wait(1); clearScreen(); Withdrawal();
                break;
            case '5':
                cout << "You exited from Bank, Thanks for using\n"; break;
                break;
            default: 
                cout << "Invalid option. Please try again.\n";
                break;
            }
        }
    }
};