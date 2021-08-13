
#include<iostream>
#include<conio.h>
#include<Windows.h>
#include<string>
#include<math.h>
#include<fstream>
#include<cstdlib>
#include<cstring>

using namespace std;

struct Product
{
	string Naming;
	int Code;
	int Amount;
	int Price;
};
struct Client {
	string Name;
	string Phonenumber;
	string naming;
	int price, amount, change,code;
};
struct Data {
	Product product;
	Client client;
};

void ProductEntry(Data* (&data), int& n,string fileName);//ввод
void ProductAdd(Data* (&data), int& n);//дозаписывние продуктов
void Reading(Data* (&data), int& n, string fileName);//чтение данных из файла
void Print(Data* data, int n,string fileName);//вывод для админа с проверкой количества
void ProductChange(Data* (&data), int n, string fileName);//изменение
void Delete(Data* (&data), int& n);//удаление
void Copy(Data* (&newData), Data* (&oldData), int n);//копирование всего массива
void Copy(Data& newData, Data& oldData);//копирование только одного элемента массива для сортировки
void Sorting(Data* data, int n);//сортировка 
void Saving(Data* data, int n, string fileName);//сохранение со вписыванием файла
void Print2(Data* data, int n);//вывод для клиента
void Search(Data* data, int n);//поиск
void Purchase(Data* (&data), int n, string fileName);//покупка
void Clients(Data* data,string fileName);//клиентский чек
void BoughtProducts(Data* data, string fileName);//купленные продукты и их количество
void Save(Data* data, int n, string fileName);//сохранение автоматическое
void PrintByAmount(Data* data, int n);//отчет продуктов по количеству


void MainMenu()
{
	cout << "\n\t\t   SHOP SYSTEM\n";
	cout << "=============================================================";
	cout << "\n\n\t\t   (1) Admin Menu\n\n\t\t   (2) Customer Menu\n\n\t\t   (3) Exit a store";
	cout << "\n\n=============================================================\n";
	cout << "\n\nEnter Your Choice:";
}
void AdminMenu()
{
	cout << "***Admin menu***" << endl << "----------------------------------" << endl;
	cout << "(0) Exit to the main menu" << endl
		<< "(1) Publish a product" << endl
		<< "(2) Display all products" << endl
		<< "(3) Change a product" << endl
		<< "(4) Delete a product" << endl
		<< "(5) Save everything" << endl
		<< "(6) Display clients and their actions" << endl
		<< "(7) Display bought products list" << endl
		<< "(8) Display product by it's amount" << endl
		<< "(9) Add some product" << endl
		<< "----------------------------------" << endl;
	cout << "Enter Your Choice: ";
}
void ClientMenu()
{
	cout << "***Client menu***" << endl << "----------------------------------" << endl;
	cout << "(0) Exit to the main menu" << endl
		<< "(1) Display a list of products" << endl
		<< "(2) Sort products" << endl
		<< "(3) Search product" << endl
		<< "(4) Purchase a product" << endl
		<< "----------------------------------" << endl;
	cout << "Enter Your Choice: ";
}
void ChangingMenu()
{
	cout << "***Changing menu***" << endl << "----------------------------------" << endl;
	cout << "(0) Exit" << endl
		<< "(1) Change product's name" << endl
		<< "(2) Change product's price" << endl
		<< "(3) Change amount of this product" << endl
		<< "(4) Change everything" << endl;
}

void main()
{
	char password[10] = "admin";
	int amountOfData=0;
	Data* data = new Data[amountOfData];
	string mainEnter, adminEnter, clientEnter, productEnter, fileName;
mainmenu: system("cls");
	for (int i = 0;; i++)
	{
     	Reading(data, amountOfData, "Saving.txt");
		MainMenu();
		cin >> mainEnter;
		if (mainEnter == "1") {
			system("cls");

			system("cls");
			cout << "\n\n\n\n\n\n\n\t\t\t\tEnter the password: ";

			for (int j = 0; j < 5; j++)
			{
				password[j] = _getch();
				system("cls");
				cout << "\n\n\n\n\n\n\n\t\t\t\tEnter the password: ";
				for (i = 1; i <= (j + 1); i++)
				{
					cout << "*";
				}
			}
			if (strcmp(password, "admin") == 0)
			{
				system("cls");
			adminmenu:
				system("cls");
				for (i = 0;; i++)
				{
					AdminMenu();
					cin >> adminEnter;
					system("cls");
					if (adminEnter == "1") {
					input:
						cout << "Will you enter a product?[yes;no]: ";
						cin >> productEnter;
						if (productEnter == "yes" || productEnter == "Yes")
						{
							system("cls");
							ProductEntry(data, amountOfData,"Saving.txt");

						}
						else if (productEnter == "no" || productEnter == "No")
						{
							system("cls");
							goto adminmenu;
						}
						else {
							cout << "\n\n\nWrong input string, try again!!!\n";
							system("pause");
							goto input;
						}
						system("pause");
						system("cls");
						goto adminmenu;
					}
					else if (adminEnter == "2")
					{
						if (amountOfData > 0)
						{
							Print(data, amountOfData,"Saving.txt");
						}
						else { cout << "OOPS...We couldn't find any product!\n"; }
						system("pause");
						system("cls");
						goto adminmenu;
					}
					else if (adminEnter == "3")
					{
						if (amountOfData > 0)
						{
							ProductChange(data, amountOfData, "Changing.txt");
						}
						else {
							cout << "OOPS...We couldn't find any product!\n";
						}
						system("pause");
						system("cls");
						goto adminmenu;
					}
					else if (adminEnter == "4")
					{
						if (amountOfData >= 0)
						{
							Delete(data, amountOfData);
							Save(data, amountOfData, "Saving.txt");

						}
						else {
							cout << "OOPS...We couldn't find any product!\n";
						}
					}
					else if (adminEnter == "5") {
						cout << "Enter a name of file for save: ";
						cin >> fileName;
						if (amountOfData >= 0)
						{
							Saving(data, amountOfData, fileName);
						}
						else { cout << "Empty data for saving...Firstly you need to add product!\n"; system("pause"); goto adminmenu; }
					}
					else if (adminEnter == "6") { 
						system("cls");
						if (amountOfData >= 0)
						{
							Clients(data, "ClientInfo.txt");
							system("pause");
							system("cls");
						}
						else {
							cout << "Empty clients list!\n"; system("pause"); goto adminmenu;
						}
					}
					else if (adminEnter == "7") {
						system("cls");
						if (amountOfData >= 0)
						{
							BoughtProducts(data, "ProductInfo.txt");
							system("pause");
							system("cls");
						}
						else {
							cout << "Empty report list!\n"; system("pause"); goto adminmenu;
						}
					}
					else if (adminEnter == "8") {
						system("cls");
						if (amountOfData >= 0)
						{
							PrintByAmount(data, amountOfData);
							system("pause");
							system("cls");
						}
						else {
							cout << "Empty list of products!\n"; system("pause"); goto adminmenu;
						}
					}
					else if (adminEnter == "9")
					{
					if (amountOfData >= 0)
					{
						ProductAdd(data, amountOfData);
						Save(data, amountOfData, "Saving.txt");

					}
					else {
						cout << "OOPS...We couldn't find any product!\n";
					}
					}
					else if (adminEnter == "0") { goto mainmenu; }
					else {
						cout << "\n\n\nWrong input number, try again!!!\n";
						system("pause");
						goto adminmenu;
					}
				}
				break;
			}
			else {
				cout << "\n\n\nAccess denied, wrong password!!!\n\n";
				system("pause"); goto mainmenu;
			}
		}
		else if (mainEnter == "2") {
			system("cls");
		clientmenu:
			system("cls");
			for (i = 0;; i++) {
				ClientMenu();
				cin >> clientEnter;
				system("cls");
				if (clientEnter == "1") {
					if (amountOfData > 0)
					{
						Print2(data, amountOfData);
					}
					else { cout << "OOPS...We couldn't find any product!\n"; }
					system("pause");
					system("cls");
					goto clientmenu;
				}
				else if (clientEnter == "2") {
					if (amountOfData > 0)
					{
						Sorting(data, amountOfData);
					}
					else { cout << "OOPS...We couldn't find any product!\n"; }
					system("pause");
					system("cls");
					goto clientmenu;

				}
				else if (clientEnter == "3") {
					if (amountOfData > 0)
					{
						Search(data, amountOfData);
					}
					else { cout << "OOPS...We couldn't find any product!\n"; }
					system("pause");
					system("cls");
					goto clientmenu;

				}
				else if (clientEnter == "4")
				{
					if (amountOfData > 0) {
						cout << "***Purchase menu***\n\n";
						Print2(data, amountOfData);
						Purchase(data, amountOfData,"Saving.txt");
						Save(data, amountOfData, "Saving.txt");
					}
					else { cout << "OOPS...We couldn't find any product!\n"; }
					system("pause");
					system("cls");
					goto clientmenu;
				}
				else if (clientEnter == "0") { goto mainmenu; }
				else {
					cout << "\n\n\nWrong input number, try again!!!\n";
					system("pause");
					goto clientmenu;
				}
			}
		}
		else if (mainEnter == "3") {
			system("cls"); cout << "\n\n\n\t\t\t**********************************\n\t\t\tThank you for visiting our shop!!!\n\t\t\t**********************************\n\n\n\n\n\n"; break;
		}
		else {
			cout << "\n\n\nWrong input number, try again!!!\n";
			system("pause");
			goto mainmenu;
		}
	}


	system("pause");
}


void ProductEntry(Data* (&data), int& n, string fileName)
{
	ofstream file(fileName,ios::app);
	int numbers;
	while (cout << "How many items do you want to publish :" &&
		!(cin >> n)) {
		system("cls");
		cin.clear();
		cin.ignore((numeric_limits < streamsize>::max)(), '\n');
		cout << "Wrong input; please try again!\n";
		system("pause");
		system("cls");
	}
	data = new Data[n];
	file << n << endl;
entering:
	for (int i = 0; i < n; i++)
	{
		cout << "Enter a name of the product: ";
		cin.get();
		getline(cin, data[i].product.Naming);
		while (cout << "Enter product code: " &&
			!(cin >> data[i].product.Code)) {
			system("cls");
			cin.clear();
			cin.ignore((numeric_limits < streamsize>::max)(), '\n');
			cout << "Wrong input; please try again!\n";
			system("pause");
			system("cls");
		}
		while (cout << "Enter product price: " &&
			!(cin >> data[i].product.Price)) {
			system("cls");
			cin.clear();
			cin.ignore((numeric_limits < streamsize>::max)(), '\n');
			cout << "Wrong input; please try again!\n";
			system("pause");
			system("cls");
		}		
		while (cout << "Enter product's amount: " &&
			!(cin >> data[i].product.Amount)) {
			system("cls");
			cin.clear();
			cin.ignore((numeric_limits < streamsize>::max)(), '\n');
			cout << "Wrong input; please try again!\n";
			system("pause");
			system("cls");
		}
        cout << "_____________________________________________\n\n";
		file << data[i].product.Naming<<endl;
		file << data[i].product.Code<<endl;
		file << data[i].product.Price<<endl;
		file << data[i].product.Amount<<endl;
     }
	file.close();
	cin.get();
}

void ProductAdd(Data* (&data), int& n)
{
	adding:
	int numbers;
	while (cout << "How many products do you want to add :" &&
		!(cin >> numbers)) {
		system("cls");
		cin.clear();
		cin.ignore((numeric_limits < streamsize>::max)(), '\n');
		cout << "Wrong input; please try again!\n";
		system("pause");
		system("cls");
	}
	if (numbers > 0)
	{
		Data* dataCopy = new Data[n];
		Copy(dataCopy, data, n);
		n += numbers;
		data = new Data[n];
		int counter = 0;
		for (int i = 0; i < numbers; i++)
		{
			++counter;
			data[counter] = dataCopy[i];
			cout << "Enter a name of the product: ";
			cin.get();
			getline(cin, data[i].product.Naming);
			while (cout << "Enter product code: " &&
				!(cin >> data[i].product.Code)) {
				system("cls");
				cin.clear();
				cin.ignore((numeric_limits < streamsize>::max)(), '\n');
				cout << "Wrong input; please try again!\n";
				system("pause");
				system("cls");
			}
			while (cout << "Enter product price: " &&
				!(cin >> data[i].product.Price)) {
				system("cls");
				cin.clear();
				cin.ignore((numeric_limits < streamsize>::max)(), '\n');
				cout << "Wrong input; please try again!\n";
				system("pause");
				system("cls");
			}
			while (cout << "Enter product's amount: " &&
				!(cin >> data[i].product.Amount)) {
				system("cls");
				cin.clear();
				cin.ignore((numeric_limits < streamsize>::max)(), '\n');
				cout << "Wrong input; please try again!\n";
				system("pause");
				system("cls");
			}
			cout << "_____________________________________________\n\n";
		}
		delete[]dataCopy;
		system("cls");
		cout << "A product was successfully added!\n";
		system("pause");
		system("cls");
	}
	else if (numbers == 0) { system("cls"); system("pause"); system("cls"); }
	else { cout << "Wrong input,try again!\n"; system("pause"); system("cls"); goto adding; }
	cin.get();
}

void Reading(Data* (&data), int& n, string fileName)
{
	ifstream file(fileName, ios::app);
	if (file) 
	{
		file >> n; 
		data = new Data[n];
		for (int i = 0; i < n; i++) 
		{
			file >> data[i].product.Naming;
			file >> data[i].product.Code;
			file >> data[i].product.Price;
			file >> data[i].product.Amount;
		}
		
	}
	else {
		cout << "OOPS...Failed to open a file!\n";
	}
	file.close();
}

void Print(Data* data, int n,string fileName)
{
	ofstream file(fileName);
	file << n << endl;
	for (int i = 0; i < n; i++)
	{
		if (data[i].product.Amount > 5) {
			file << data[i].product.Naming << endl;
			file << data[i].product.Code << endl;
			file << data[i].product.Price << endl;
			file << data[i].product.Amount << endl;
			cout << "Product #" << i + 1 << '\n';
			cout << "Name: " << data[i].product.Naming << endl;
			cout << "Code: " << data[i].product.Code << endl;
			cout << "Price: " << data[i].product.Price << " UAH" << endl;
			cout << "Amount: " << data[i].product.Amount << endl;
			cout << "___________________________________________________\n\n";
		}
		else {
			cout << "Warning! A little amount of a product items left!\n";
			cout << "Go for adding some more!!!\n\n\n";
			system("pause");
			file << data[i].product.Naming << endl;
			file << data[i].product.Code << endl;
			file << data[i].product.Price << endl;
			file << data[i].product.Amount << endl;
			cout << "Product #" << i + 1 << '\n';
			cout << "Name: " << data[i].product.Naming << endl;
			cout << "Code: " << data[i].product.Code << endl;
			cout << "Price: " << data[i].product.Price << " UAH" << endl;
			cout << "Amount: " << data[i].product.Amount << endl;
			cout << "___________________________________________________\n\n";
		}
	}
	file.close();
}

void ProductChange(Data* (&data), int n, string fileName)
{
changing:
	ifstream file(fileName);
	int numbers; string choice;
	while (cout << "Enter a number of a specific product for change (from 1 up to " << n << " ): " &&
		!(cin >> numbers)) {
		system("cls");
		cin.clear();
		cin.ignore((numeric_limits < streamsize>::max)(), '\n');
		cout << "Wrong input, please try again!\n";
		system("pause");
		system("cls");
	}
	numbers--; 
	if (numbers >= 0 && numbers < n)
	{
	choosing:
		system("cls");
		ChangingMenu();
		cin >> choice;
		if (choice == "0")
		{
			system("cls");
			AdminMenu();
		}
		else if (choice == "1")
		{
			cout << "Enter product name: ";
			cin.get();
			getline(cin,data[numbers].product.Naming);
			file >> data[numbers].product.Naming;
			file >> data[numbers].product.Code;
			file >> data[numbers].product.Price;
			file >> data[numbers].product.Amount;
		}
		else if (choice == "2")
		{
			while (cout << "Enter product price: " &&
				!(cin >> data[numbers].product.Price)) {
				system("cls");
				cin.clear();
				cin.ignore((numeric_limits < streamsize>::max)(), '\n');
				cout << "Wrong input, please try again!\n";
				system("pause");
				system("cls");
			}
			file >> data[numbers].product.Naming;
			file >> data[numbers].product.Code;
			file >> data[numbers].product.Price;
			file >> data[numbers].product.Amount;
		}
		else if (choice == "3")
		{
			while (cout << "Enter product's amount: " &&
				!(cin >> data[numbers].product.Amount)) {
				system("cls");
				cin.clear();
				cin.ignore((numeric_limits < streamsize>::max)(), '\n');
				cout << "Wrong input, please try again!\n";
				system("pause");
				system("cls");
			}
			file >> data[numbers].product.Naming;
			file >> data[numbers].product.Code;
			file >> data[numbers].product.Price;
			file >> data[numbers].product.Amount;
		}
		else if (choice == "4")
		{
			cout << "Enter product name: ";
			cin.get();
			getline(cin,data[numbers].product.Naming);
			while (cout << "Enter product price: " &&
				!(cin >> data[numbers].product.Price)) {
				system("cls");
				cin.clear();
				cin.ignore((numeric_limits < streamsize>::max)(), '\n');
				cout << "Wrong input, please try again!\n";
				system("pause");
				system("cls");
			}
			while (cout << "Enter product's amount: " &&
				!(cin >> data[numbers].product.Amount)) {
				system("cls");
				cin.clear();
				cin.ignore((numeric_limits < streamsize>::max)(), '\n');
				cout << "Wrong input, please try again!\n";
				system("pause");
				system("cls");
			}
			file >> data[numbers].product.Naming;
			file >> data[numbers].product.Code;
			file >> data[numbers].product.Price;
			file >> data[numbers].product.Amount;
		}
		else { cout << "Wrong input string,try again!\n"; goto choosing; }
		system("cls");
		cout << "New changes were successfully updated!\n";
		system("pause");
		system("cls");
	}
	else { cout << "Wrong number of a product,try again!\n"; system("pause"); goto changing; }
	file.close();
	cin.get();
}

void Delete(Data* (&data), int& n)
{
deleting:
	int numbers;
	while (cout << "Enter a number of a specific product for delete (from 1 up to " << n << " ): " &&
		!(cin >> numbers)) {
		system("cls");
		cin.clear();
		cin.ignore((numeric_limits < streamsize>::max)(), '\n');
		cout << "Wrong input, please try again!\n";
		system("pause");
		system("cls");
	}
	numbers--;
	if (numbers >= 0 && numbers < n)
	{
		Data* dataCopy = new Data[n];
		Copy(dataCopy, data, n);
		--n;
		data = new Data[n];
		int counter = 0;
		for (int i = 0; i <= n; i++)
		{
			if (i != numbers)
			{
				data[counter] = dataCopy[i];
				++counter;
			}
		}
		delete[]dataCopy;
		system("cls");
		cout << "A product was successfully deleted!\n";
		system("pause");
		system("cls");

	}
	else { cout << "Wrong number of a product,try again!\n"; system("pause"); system("cls"); goto deleting; }
}

void Copy(Data* (&newData), Data* (&oldData), int n)
{
	for (int i = 0; i < n; i++)
	{
		newData[i] = oldData[i];
	}  
}

void Sorting(Data* data, int n)
{
	Data copyData;

	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (data[i].product.Naming > data[j].product.Naming)
			{
				Copy(copyData, data[j]);
				Copy(data[j], data[i]);
				Copy(data[i], copyData);
			} 
		}
	}
	system("cls");
	cout << "All products were successfully sorted!\n";
	system("pause");
	system("cls");
}

void Copy(Data& newData, Data& oldData)
{      
	newData.product.Naming = oldData.product.Naming;
	newData.product.Code = oldData.product.Code;
	newData.product.Price = oldData.product.Price;
	newData.product.Amount = oldData.product.Amount;
}

void Saving(Data* data, int n, string fileName)
{
	ofstream file(fileName, ios::out);
	if (file)
	{
		file << n << endl;
		for (int i = 0; i < n; i++)
		{
			file << data[i].product.Naming << endl;
			file << data[i].product.Code << endl;
			file << data[i].product.Price << endl;
			file << data[i].product.Amount << endl;
		}

		system("cls");
		cout << "Everything was successfully saved into a file " << fileName << endl;
		system("pause");
		system("cls");
	}
	else {
		cout << "OOPS...Couldn't open the file!\n";
	}
	file.close();
}

void Print2(Data* data, int n)
{
	cout << "***List of available products***\n\n";
	cout << "___________________________________________________\n\n";
	for (int i = 0; i < n; i++)
	{
		cout << "Product #" << i + 1 << '\n';
		cout << "Name: " << data[i].product.Naming << endl;
		cout << "Code: " << data[i].product.Code << endl;
		cout << "Price: " << data[i].product.Price << " UAH" << endl;
		cout << "Amount: " << data[i].product.Amount << endl;
		cout << "___________________________________________________\n\n";
	}
}

void Search(Data* data, int n)
{
searching:
	int code;
	cout << "***Searching Menu***\n\n";
	while (cout << "Enter a code of a product for search: " &&
		!(cin >> code)) {
		system("cls");
		cin.clear();
		cin.ignore((numeric_limits < streamsize>::max)(), '\n');
		cout << "Wrong input; please try again!\n";
		system("pause");
		system("cls");
	}
	system("cls");
	for (int i = 0; i < n; ++i) {
		if (code == data[i].product.Code)
		{
			cout << "Product #" << i + 1 << '\n';
			cout << "Name: " << data[i].product.Naming << endl;
			cout << "Code: " << data[i].product.Code << endl;
			cout << "Price: " << data[i].product.Price << " UAH" << endl;
			cout << "Amount: " << data[i].product.Amount << endl;
			cout << "___________________________________________________\n\n";
		}
	}
}

void Purchase(Data* (&data), int n, string fileName)
{
 ifstream file(fileName);
 ofstream file2("ClientInfo.txt",ios::app);
 ofstream file4("ProductInfo.txt", ios::app);

buying:
 int numbers; string choice;
	while (cout << "Enter a number of a specific product for buying (from 1 up to " << n << " ): " &&
		!(cin >> numbers)) {
		system("cls");
		cin.clear();
		cin.ignore((numeric_limits < streamsize>::max)(), '\n');
		cout << "Wrong input; please try again!\n";
		system("pause");
		system("cls");
	}
	numbers--;
	if (numbers >= 0 && numbers < n) {
		system("cls");
		cout << "***Order processing***\n\n";
		cin.get();
			cout << "Enter your name,please: ";
			getline(cin, data[numbers].client.Name);
			cout << "Enter your phone number: ";
			getline(cin, data[numbers].client.Phonenumber);
			while (cout << "Enter amount of items you want to buy: " &&
				!(cin >> data[numbers].client.amount)) {
				system("cls");
				cin.clear();
				cin.ignore((numeric_limits < streamsize>::max)(), '\n');
				cout << "Wrong input; please try again!\n";
				system("pause");
				system("cls");
			}
			if (data[numbers].client.amount <= data[numbers].product.Amount) {
				data[numbers].product.Price *= data[numbers].client.amount;
				cout << "\n\n" << "Total price to pay: " << data[numbers].product.Price << " UAH\n\n";
			moneyinsert:
				while (cout << "Insert money to pay: " &&
					!(cin >> data[numbers].client.price)) {
					system("cls");
					cin.clear();
					cin.ignore((numeric_limits < streamsize>::max)(), '\n');
					cout << "Wrong input; please try again!\n";
					system("pause");
					system("cls");
				}
				if (data[numbers].client.price == data[numbers].product.Price)
				{
					data[numbers].client.naming = data[numbers].product.Naming;
					data[numbers].client.code = data[numbers].product.Code;
					data[numbers].client.change = data[numbers].client.price - data[numbers].product.Price;
					data[numbers].product.Amount -= data[numbers].client.amount;
					data[numbers].product.Price /= data[numbers].client.amount;
					cout << "\n\n" << "The product " << data[numbers].product.Naming << " was successfully bought!\n";
					cout << "Your change: " << data[numbers].client.change << " UAH\n\n";
					system("pause");
					system("cls");
					file2 << "-------------------------------------" << endl;
					file2 << "Client's name: "<< data[numbers].client.Name << endl;
					file2 <<"Client's phonenumber: "<< data[numbers].client.Phonenumber << endl;
					file2 <<"Product name: "<< data[numbers].client.naming << endl;
					file2 <<"Product code: "<< data[numbers].client.code << endl;
					file2 <<"Amount purchased:"<< data[numbers].client.amount << endl;
					file2 <<"Total price: "<< data[numbers].client.price << endl;
					file2 <<"Change: "<< data[numbers].client.change << endl;
					file2 << "-------------------------------------" << endl;
					file4 << "-------------------------------------" << endl;
					file4 << "Product name: " << data[numbers].client.naming << endl;
					file4 << "Product code: " << data[numbers].client.code << endl;
					file4 << "Amount purchased:" << data[numbers].client.amount << endl;
					file4 << "Money earned: " << data[numbers].client.price - data[numbers].client.change << endl;
					file4 << "-------------------------------------" << endl;
				}
				else if (data[numbers].client.price > data[numbers].product.Price)
				{
					data[numbers].client.naming = data[numbers].product.Naming;
					data[numbers].client.code = data[numbers].product.Code;
					data[numbers].client.change = data[numbers].client.price - data[numbers].product.Price;
					data[numbers].product.Amount -= data[numbers].client.amount;
					data[numbers].product.Price /= data[numbers].client.amount;
					cout << "\n\n" << "The product " << data[numbers].product.Naming << " was successfully bought!\n\n";
					cout << "Your change: " << data[numbers].client.change << " UAH\n\n";
					file2 << "-------------------------------------" << endl;
					file2 << "Client's name: " << data[numbers].client.Name << endl;
					file2 << "Client's phonenumber: " << data[numbers].client.Phonenumber << endl;
					file2 << "Product name: " << data[numbers].client.naming << endl;
					file2 << "Product code: " << data[numbers].client.code << endl;
					file2 << "Amount purchased:" << data[numbers].client.amount << endl;
					file2 << "Total price: " << data[numbers].client.price << endl;
					file2 << "Change: " << data[numbers].client.change << endl;
					file2 << "-------------------------------------" << endl;
					file4 << "-------------------------------------" << endl;
					file4 << "Product name: " << data[numbers].client.naming << endl;
					file4 << "Product code: " << data[numbers].client.code << endl;
					file4 << "Amount purchased:" << data[numbers].client.amount << endl;
					file4 << "Money earned: " << data[numbers].client.price - data[numbers].client.change << endl;
					file4 << "-------------------------------------" << endl;
				}
				if (data[numbers].client.price < data[numbers].product.Price)
				{
					cout << "Sorry, you transaction was declined! Your sum is lower, than price of a product!\n";
					system("pause");
					system("cls"); goto moneyinsert;
				}
			}
			else if (data[numbers].client.amount > data[numbers].product.Amount)
			{
				cout << "Sorry, but we don't have this amount of a product!\n\n";
				system("pause");
				system("cls"); goto buying;
			}
			else if (data[numbers].client.amount == 0)
			{
				cout << "\n\n"; system("pause"); system("cls");
			}
		     if(data[numbers].product.Amount == 0)
			{
				 cout << "You can't buy a product with zero amount!\n\n";
				 system("pause");
				 system("cls"); goto buying;
			}
	}
	else { cout << "Wrong number of a product,try again!\n"; system("pause"); goto buying; }
	cin.get();
	file.close();
	file2.close();
	file4.close();
}

void Save(Data* data,int n, string fileName)
{
	ofstream file(fileName, ios::out);
	
	if (file)
	{
		file << n << endl;
		for (int i = 0; i < n; i++)
		{
			file << data[i].product.Naming << endl;
			file << data[i].product.Code << endl;
			file << data[i].product.Price << endl;
			file << data[i].product.Amount << endl;
		}
	}
	file.close();
}

void Clients(Data* data, string fileName)
{
	ifstream file(fileName);
    string temp;	
	while (!file.eof())
	{
		temp = " ";
		getline(file, temp);
		cout << temp << endl;
	}
	file.close();
}

void BoughtProducts(Data* data, string fileName)
{
	ifstream file(fileName);
	string temp;
	while (!file.eof())
	{
		temp = " ";
		getline(file, temp);
		cout << temp << endl;
	}
	file.close();
}

void PrintByAmount(Data* data, int n)
{
	int amount; string choice;
	while (cout << "Enter amount to find specific product: " &&
		!(cin >> amount)) {
		system("cls");
		cin.clear();
		cin.ignore((numeric_limits < streamsize>::max)(), '\n');
		cout << "Wrong input; please try again!\n";
		system("pause");
		system("cls");
	}
	system("cls");
	choosing:
	cout << "Do you want to find products with more amount,less or equal?[1;2;3]: ";
	cin >> choice;
	system("cls");
	if (choice == "1")
	{
        for (int i = 0; i < n; ++i)
		{
			if (data[i].product.Amount > amount)
			{
				cout << "Product #" << i + 1 << '\n';
				cout << "Name: " << data[i].product.Naming << endl;
				cout << "Code: " << data[i].product.Code << endl;
				cout << "Price: " << data[i].product.Price << " UAH" << endl;
				cout << "Amount: " << data[i].product.Amount << endl;
				cout << "___________________________________________________\n\n";
			}
		}
	}
	if (choice == "2")
	{
		for (int i = 0; i < n; ++i)
		{
			if (data[i].product.Amount < amount)
			{
				cout << "Product #" << i + 1 << '\n';
				cout << "Name: " << data[i].product.Naming << endl;
				cout << "Code: " << data[i].product.Code << endl;
				cout << "Price: " << data[i].product.Price << " UAH" << endl;
				cout << "Amount: " << data[i].product.Amount << endl;
				cout << "___________________________________________________\n\n";
			}
		}
	}
	if (choice == "3")
	{
		for (int i = 0; i < n; ++i)
		{
			if (data[i].product.Amount == amount)
			{
				cout << "Product #" << i + 1 << '\n';
				cout << "Name: " << data[i].product.Naming << endl;
				cout << "Code: " << data[i].product.Code << endl;
				cout << "Price: " << data[i].product.Price << " UAH" << endl;
				cout << "Amount: " << data[i].product.Amount << endl;
				cout << "___________________________________________________\n\n";
			}
		}
	}
}