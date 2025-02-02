#include "Owner.h"
#include "Organization.h"
#include "Helper.h"
#include"OpeningUI.h"

Owner::Owner(string _id, string _userName, string _password, int _totalMoney, vector<Car*> _cars, vector<Notification*> _inbox)
	:User(_id, _userName, _password, _totalMoney)
{
	this->cars = _cars;
	this->inbox = _inbox;
}

Owner::Owner(string _id, string _userName, string _password, int _totalMoney) :User(_id, _userName, _password, _totalMoney)
{


}


void Owner::displayInfo()
{
	// we are displaying  the openning UI of the Owner
	int i = 0;
	while (true) {
		system("cls");
		if (i)
			cout << "unvalid input please try again" << endl;
		i++;
		cout << "\t\t\tHELLO " << username << '\n';
		cout << "total money: " << totalMoney << '\n';
		cout << "1-Add New Cars\n";
		cout << "2-See My Cars\n";
		cout << "3-inbox: ";
		if (inbox.size() > 0)
			cout << inbox.size();
		else cout << "0";
		cout << '\n';
		cout << "4-go back\n";

		string input = "0";
		cin >> input;
		if (input == "1") {
			addNewCar();
			i = 0;
		}
		else if (input == "2") {
			showMyCars();
			i = 0;
		}	
		else if (input == "3") {
			if (inbox.size() == 0) {
				cout << "You don't have any Notifications\n";
				system("pause");
				

			}
			else {
				showInbox();
			}
			i = 0;
		}
		else if (input == "4") {
			openingUI();
		}
	}

}

string Owner::toBeWrittenInFile()
{
	string s = User::toBeWrittenInFile();

	/// we are preparing the string that will be written for the owner


	s += "{";

	for (int i = 0; i < cars.size(); i++) {
		if (i)
			s += ",";

		s += cars[i]->ID;

	}

	s += "}";

	int counter = 0;
	s += " ";
	s += "{";
	for (auto i : inbox) {
		if (counter)
			s += ',';
		s += i->getID();
		counter++;
	}

	s += '}';
	//
	return s;

}

void Owner::addNewCar() {

	system("cls");
	Organization* org = Organization::getInstance();

	// adding NewCar to be verified by the Admin

	Car c;
	c.getCarInput(org->allCars.size(), stoi(id));
	org->allCars.push_back(c);
	cars.push_back(&(org->allCars[org->allCars.size() - 1]));

	org->writeFiles();

}

void Owner::showMyCars()
{
	
	// show the only operting(verifiedCars) of the owner and onClick on an ID we show the rentingProcesses of the Car
	int key[100] = { 0 };
	int j = 1;
	int i = 0;
	for (; i < cars.size(); i++) {
		if (cars[i]->getVerification()) {
			if(j==1)
				system("cls");
			cout << i+1 << " ";
			cars[i]->displayInfo();
			cout << '\n';
			key[j] = i;
			j++;
		}
	}
	if (j == 1) {

		cout << "You Don't have any operating Cars\n";
		
		system("pause");
		displayInfo();

	}

	bool flag = false;
	string s = "0";
	int n = 0;
	while (!flag) {
		cout << "Choose car no to show its history  or enter \"a\" to go back : ";
		cin >> s;
		if (s == "a")
			displayInfo();
		else if ((Helper::checkDigit(s[0]))) {
			flag = true;
			if (s.size() > 1) {
				if ((Helper::checkDigit(s[1]))) {
				}
				else flag = false;
			}
		}
		if (flag)
			n = stoi(s);
		else {

			cout << "unvalid input please try again" << endl;
		}
	}
	if (n >= j||j<=0) {
		cout << "unavailabe car id \n";
		system("pause");
		showMyCars();
		
	}
	else {
		n = key[n];
		Car* choosen = cars[n];
		if (choosen->getRentingProcesses().size() == 0) {
			cout << " This Car has no rentingProcesses\n";
			system("pause");
			showMyCars();
		}
		else {
			system("cls");
			for (int i = 0; i < choosen->getRentingProcesses().size(); i++) {

				cout << i + 1 << " ";
				choosen->getRentingProcesses()[i]->displayInfo(choosen->getModel());
				cout << '\n';
			}
			system("pause");
			showMyCars();
			
		}
	}

	
}

void Owner::showInbox()
{

	// we are displaying the inbox of the owenr and make it empty after it like normal notifications in any app
	cout << '\n';
	for (int i = 0; i < inbox.size(); i++) {

		cout << i + 1 << ": ";
		inbox[i]->displayInfo();

	}

	inbox.clear();
	
	system("pause");
	displayInfo();


}

void Owner::changeMoney(float money)
{
	Organization* org = Organization::getInstance();

	totalMoney += money;
	inbox.push_back(&org->allNotifications[org->allNotifications.size() - 1]);


}

void Owner::displayData()
{
	User::displayData();
	cout << "Number Of cars:" << cars.size() << '\n';

}

void Owner::displayTheUniqueHistory()
{

	// we are display the Cars of the Owner 
	if (cars.size() == 0) {

		cout << "This user has no cars yet\n";

	}
	else {

		for (int i = 0; i < cars.size(); i++) {
			cout << i + 1 << ": ";
			cars[i]->displayInfo();
			cout << "\n";

		}
	}
	
}


