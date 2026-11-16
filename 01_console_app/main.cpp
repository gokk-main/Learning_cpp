#include <iostream>
#include <string>
using namespace std;

int number_counter = 1;
int account_counter = 0;
int current_account = 0;

//структура банковского аккаунта
struct bank_account {
  int account_number;
  string owner;
  double balance;
};

//глобальные струткуры
bank_account account1{};
bank_account account2{};

//прототипы функций
bank_account create_account();
void print_account(bank_account&);
void deposit(bank_account&);
void withdraw(bank_account&);
void transfer(bank_account&);
void change_account();
void sub_change_account(char&);
bank_account& get_current_account();


int main() {
  char input ='0';


  while (input != 'q' && input != 'Q') {
    cout << endl;
    if (current_account == 1) cout << "Выбран счет №" << account1.account_number<<endl;
    else if (current_account == 2)  cout << "Выбран счет №" << account2.account_number<<endl;
    else if (account_counter == 0) cout <<"У вас нет счетов" << endl;
    cout << "----- МЕНЮ -----"<<endl;
    cout << "1. Создать счёт" <<endl;
    cout << "2. Пополнить счёт" << endl;
    cout << "3. Снять деньги" << endl;
    cout << "4. Перевести деньги" << endl;
    cout << "5. Информация о счёте" << endl;
    cout << "6. Выбрать счет"<<endl;
    cout << "q. Выход" << endl;
    cout << "> ";

    cin >> input;

    if (input == 'q' || input == 'Q' ) return 0;

    switch (input) {
      case '1': {
        if (account_counter == 0) {
          account1= create_account();
          break;
        }
        else if (account_counter == 1) {
          account2= create_account();
          break;
        }
        else {
          cout << "\nУ вас уже открыто максимальное количество счетов (2)"<<endl;
          break;
        }
      }
      case '2':
        if (current_account == 0) {
          cout << endl;
          cout << "У вас нет счета" << endl;
          break;
        }
        else deposit(get_current_account());
        break;
      case '3': {
        if (current_account == 0) {
          cout << endl;
          cout << "У вас нет счета" << endl;
          break;
        }
        else withdraw(get_current_account());
        break;
      }
      case '4': {
        if (current_account == 0) {
          cout << endl;
          cout << "У вас нет счета" << endl;
          break;
        }
        else transfer(get_current_account());
        break;
      }
      case '5': {
        if (current_account == 0) {
          cout << endl;
          cout << "У вас нет счета" << endl;
          break;
        }
        else print_account(get_current_account());
        break;
      }
      case '6': {
        change_account();
        break;
      }
      default:
        cout << endl;
        cout<<"\nНеизвестная команда"<<endl;
        break;
    }

  }

return 0;
}

bank_account create_account() {
  bank_account account;
  cout << "\nВведите ваше имя: ";
  getline(cin >> ws,account.owner);
  account.balance = 0;
  account.account_number = number_counter;
  number_counter++;
  cout << "\nСчёт №" <<account.account_number <<" успешно создан" <<endl;
  account_counter++;
  current_account = account.account_number;
  return account;
}

void print_account(bank_account& account) {

  cout <<endl;
  cout<<"Счёт №"<<account.account_number<<endl;
  cout<<"Владелец: " << account.owner<<endl;
  cout<<"Баланс: " <<account.balance << " ₽"<<endl;
}

void deposit(bank_account& account) {
  double deposit_amount;
    cout << "\nВаш текущий баланс: " << account.balance<<" ₽"<<endl;
    cout << "Введите сумму, которую хотите внести: ";
    cin >>deposit_amount;
    if (deposit_amount >0)account.balance += deposit_amount;
    else cout << "\nОтрицательная сумма"<<endl;


}

void withdraw(bank_account& account) {

  double withdraw_amount;
  cout << "\nВаш текущий баланс: " << account.balance<<" ₽"<<endl;
  cout << "Введите сумму для снятия: ";
  cin >> withdraw_amount;
  if (withdraw_amount > account.balance) {
    cout << "\nНедостаточно средств" << endl;
    return;
  }
  else if (withdraw_amount >0){
    account.balance -= withdraw_amount;
    cout << "Сумма " << withdraw_amount << " ₽ " <<"успешно снята" << endl;
  }
  else cout << "\nОтрицательная сумма"<<endl;

}

void transfer(bank_account& account) {

  int account_number;
  double transfer_amount;
  cout << "Введите номер счета, куда перевести деньги: ";
  cin >> account_number;
  cout << "Ваш текущий баланс : "<< account.balance<< " ₽";
  cout << "\nВведите сумму, которую хотите перевести: ";
  cin >> transfer_amount;
  if (transfer_amount > account.balance) {
    cout << "\nНедостаточно средств"<<endl;
  }
  else {
    if (account.account_number == account_number || transfer_amount<0 || account_counter<2) {
      cout << "\nПеревод невозможен"<<endl;
      return;
    }
    if (transfer_amount>0 && account_counter>1) {
      if (account_number == 2) {
        account2.balance += transfer_amount;
        account.balance -= transfer_amount;
        cout << "\nПеревод успешно совершён" <<endl;
      }
      else if (account_number == 1) {
        account.balance -= transfer_amount;
        account1.balance += transfer_amount;
        cout << "\nПеревод успешно совершён" <<endl;
      }
    }

  }
}

void change_account() {

  if (account_counter >= 1) {
    cout<<endl;
    cout <<"1. Счёт №"<<account1.account_number <<endl;
    if (account_counter == 2) cout <<"2. Счёт №"<<account2.account_number <<endl;
    cout<< "> ";
    char temp;
    cin >> temp;
    sub_change_account(temp);
  }
}

void sub_change_account(char& temp) {
  switch (temp) {
    case '1': {
      current_account = 1;
      break;
    }
    case '2':
      if (account_counter>1) {
        current_account = 2;
        break;
      }
      else{
        cout<<"\nНеизвестная команда"<<endl;
        break;
      }
    default: {
      cout<<"\nНеизвестная команда"<<endl;
      break;
    }
  }
}

bank_account& get_current_account() {
  if (current_account == 1) return account1;
  else if (current_account == 2) return account2;
}



