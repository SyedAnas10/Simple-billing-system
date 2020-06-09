#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <fstream>
#include <string>

using namespace std ;

// defining a structure for each house
struct billInfo {
	string address;
	int units;
};
billInfo houses[10]; // an array of 10 houses


// a function to generate bill
void billGenerator( billInfo house, int oldUnits )
{
	system("cls");
	cout << "Generating new bill..." << endl << endl << endl ;
	Sleep(4*1000);
	int bill;
	
	if( (house.units - oldUnits) >= 300 )
		bill = (house.units - oldUnits)*30 ;
	else
		bill = (house.units - oldUnits)*20 ;
	
	cout << "\t House No. :" << house.address << endl ;
	cout << "\t Previously consumed units : " << oldUnits <<  endl ;
	cout << "\t Units consumed this month : " << house.units << endl ;
	cout << "\t 	Amount Payable " <<  endl ;
	cout << "\t before due-date: Rs." << bill << "	after due-date: Rs." << bill+2000 << endl ;
	cout << endl ;
}


// a function to take readings from the input file
void areaInfo(ifstream& file)
{
	string temp;
	for( int i=0 ; i < 10 ; i++)
	{
		getline(file, houses[i].address);
		file >> houses[i].units;
		getline(file, temp);
	}
}

// a function to print the area information on screen
void printAreaInfo()
{
	for( int i=0 ; i < 10 ; i++)
	{
		cout << i << ") " << houses[i].address << " : units = " << houses[i].units << endl << endl ;
	}
}

// proceeds to generating bill for a specific house with new units reading
void newInput()
{
	int oldUnits, newUnits, houseNo;
	
	cout << "Enter the number of house indicated in the list to proceed : " ;
	cin >> houseNo;
	
	while(houseNo < 0 || houseNo > 9)
	{
		cout << "Please enter appropriate number from the list correspondingly : " ;
		cin >> houseNo;
	}
	
	oldUnits = houses[houseNo].units;
	
	cout << "\n\nEnter total units consumed : " ;
	cin >> newUnits;
	
	while( oldUnits > newUnits)
	{
		cout << "This month readings can not be smaller than the previous month" << endl ;
		cout << "Enter appropriate readings : " ;
		cin >> newUnits ;
	}
	
	houses[houseNo].units = newUnits ;
	
	billGenerator( houses[houseNo], oldUnits);
}

// update the file with new reading
void updateFile(ofstream& file)	
{
	for( int i = 0 ; i < 10 ; i++)
	{
		file << houses[i].address << endl ;
		file << houses[i].units << endl ;
	}
}

int main()
{
	char choice ;
	string houseNo;
	
	ifstream file;
	file.open("Area1.txt");
	areaInfo(file);
	printAreaInfo();
	file.close();
	
	cout << "Enter new units for a house?(y/n) : " ;
	cin >> choice ;
	
	if( choice == 'y' || choice == 'Y')
	{
		newInput();
		ofstream file;
		file.open("Area1.txt");
		updateFile(file);
		file.close();
	}	
	
	return 0;
}
