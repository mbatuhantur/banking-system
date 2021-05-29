#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;


class Account {
protected:
	int pin;
	int accNo;
	double balance;
	// double balancePending;
public:
	Account(int accNo, int pin) {
		this->accNo = accNo;
		this->pin = pin;
		this->balance = 1000.0;
	}
	Account() {}
	void deposit(double amount) {
		perhapsDeposit(amount);
		if (confirmDeposit()) {

			if (amount > 5.0) {
				balance += amount;
				cout << "Para yatirma basarili!" << endl;
				cout << endl << "Islem ozeti : " << endl;
				checkDetails();
			} 
			else {
				cout << "5 liradan daha az bir miktar yatirilamaz!";
			}
		}
		else {
			cout << "Para yatirma iptal edildi" << endl;
		}

		cout << "Baska bir islem yapmak icin herhangi bir tusa basiniz" << endl;
		cin.get();
		cin.get();
	}
	void perhapsDeposit(double amount) {
		cout << amount << " miktarindaki parayi yatirmak istediginize emin misiniz? (e/h)" << endl;
		cout << "Cevap : ";

	}
	bool confirmDeposit() {
		char cevap;
		cin >> cevap;

		if (cevap == 'e' || cevap == 'E')
			return true;
		else
			return false;
	}
	void checkDetails() {
		cout << "\n\t\t#---Hesap-------------------" << endl;
		cout << "\n\t\t#-Hesap No: " << accNo << endl;
		cout << "\n\t\t#-Butce : " << balance << endl;
		cout << "\n\t\t#---------------------------" << endl;
	}
	void withdraw(double amount) {
		if (balance < amount) {
			cout << "Yeterli bakiye bulunmamaktadir!" << endl;
			cout << "Toplam bakiye : " << balance << endl;
		}
		else {
			balance -= amount;
			cout << "Para cekme basarili!" << endl;
			cout << endl << "Islem ozeti : " << endl;
			checkDetails();
		}
		cout << "Baska bir islem yapmak icin herhangi bir tusa basiniz" << endl;
		cin.get();
		cin.get();
	}
	double checkFounds() {

	}
	int getAccNo() { return accNo; }
};

class ChequeAccount : public Account {
public:
	ChequeAccount(int accNo, int pin) : Account(accNo, pin) {}
	ChequeAccount() {}

	void chequeWithdraw(double amount) {
		withdraw(amount);
	}

	bool checkPin(int pin) {
		if (pin == this->pin)
			return true;
		else
			return false;
	}
};

class SavingAccount : Account {
public:
	double interest;
};
 
class EntryStation {
public:
	vector<ChequeAccount> accounts; // vector her türden veri ya da nesne tutar eleman eklendikçe otomatik olarak dizi boyutu büyür
	void AddAccount(int accNo) {
		ChequeAccount _new(accNo, 1234);
		accounts.push_back(_new);
	}
};
EntryStation es;

class ATM : public EntryStation {
private:
	int pin;
public: 
	ChequeAccount* currentAccount;
	ATM() {}

	void  getPin() {
		cout << "\n\t\tLutfen 4 haneli pininizi giriniz : "; cin >> pin;
	}
	bool readCard(int accNo) {
		for (int i = 0; i < es.accounts.size(); i++) {
			if (accNo == es.accounts[i].getAccNo()) {

				getPin();

				if (es.accounts[i].checkPin(pin))
					currentAccount = &es.accounts[i];
				return true;
			}
		}

		return false;
	}
	void withdraw(double amount) {
		(*currentAccount).chequeWithdraw(amount);
	}
};

class CounterTeller : public EntryStation {
public: 
	void deposit(int accNo, double amount) {
		for (int i = 0; i < es.accounts.size(); i++) {
			if (accNo == es.accounts[i].getAccNo()) {
				es.accounts[i].deposit(amount);
			}
		}
	}
};




class Client {
public:
	vector<Account> accounts;
};
int main() {
	CounterTeller ct;
	ATM atm;
	// Adding some predefined bank accounts to ATM
	es.AddAccount(1);
	es.AddAccount(2);
	es.AddAccount(3);
	es.AddAccount(4);


	int secim;
	int accNo;
	int pin;

	while (1) {
		system("cls");
		 cout            << "  __  __                     _____           _                 " << "\n"
                	<<    " |  \\/  |                   / ____|         | |                " << "\n"
                       << " | \\  / | ___ _ __  _   _  | (___  _   _ ___| |_ ___ _ __ ___" << "\n"
                     <<   " | |\\/| |/ _ \\ '_ \\| | | |  \\___ \\| | | / __| __/ _ \\ '_ ` _ \\" << "\n"
                       << " | |  | |  __/ | | | |_| |  ____) | |_| \\__ \\ ||  __/ | | | | |" << "\n"
                       << " |_|  |_|\\___|_| |_|\\__,_| |_____/ \\__, |___/\\__\\___|_| |_| |_|" << "\n"
                                     "                                    |___/             ";      cout<<" from MBT \n";
                                     cout<<"                   Thanks for using Bank Managemnt System";
		cout << "\n\t\t____________________________________________\n"  ; 
	   	cout << "\n\t\tHosgeldiniz" << endl;
		cout << "\n\t\tLutfen kullanmak istediginiz sistemi seciniz : " << endl;
		cout << "\n\t\t1. ATM " << endl;
		cout << "\n\t\t2. Counter Teller" << endl;
		cout << "\n\t\t3. Exit" << endl;
		cout << "\n\t\t Secim" <<endl;
		cout << "\n\t\t____________________________________________\n"  ; 
		cin >> secim;

		switch (secim) {
		case 1: {
			system("cls");
			
			cout << "\n\t\tATM kullanmayi sectiniz." << endl;
			cout << "\n\t\tLutfen hesap numarinizi giriniz." << endl;
			cout << "\n\t\tHesap Numarasi : "; cin >> accNo;
		

			int secenek;

			if (atm.readCard(accNo)) {
			    cout << "\n\t\t____________________________________________\n"  ;
				cout << "\n\t\tHosgeldiniz..." << endl;
				atm.currentAccount->checkDetails();
				cout << "\n\t\tYapmak istediginiz islemi seciniz:" << endl;
				cout << "\n\t\t1. Para Cekme" << endl;
				cout << "\n\t\t2. Cikis" << endl;
				cin >> secenek;
				

				if (secenek == 1) {
					double amount;
					cout << "\n\t\tLutfen cekmek istedihiniz miktari giriniz: ";
					cin >> amount;

					atm.withdraw(amount);
				}
				else {
					cout << "\n\t\tProgram sonlandiriliyor..." << endl;
					exit(1);
				}
			}
			break;
		}

		case 2: {
			int accNo;
			int amount;
			cout << "\n\t\t____________________________________________\n"  ;
			cout << "\n\t\tCounter Teller ile islem yapmayi sectiniz..." << endl;
			cout << "\n\t\tLutfen para yatirmak istediginiz hesap numarasini soyleyiniz : ";
			cin >> accNo;
			cout << "\n\t\tLutfen yatirmak istediginiz miktari giriniz : ";
			cin >> amount;
			cout << "\n\t\t____________________________________________\n"  ;

			ct.deposit(accNo, amount);

			break;
		}
		case 3: {
			cout << "\n\t\tHoscakalin!" << endl;
			exit(1);
		}
		default: {
			cout << "\n\t\tLutfen gecerli bir deger giriniz!" << endl;
			exit(1);
		}

		}
	}
}
