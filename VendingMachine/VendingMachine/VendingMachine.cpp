// VendingMachine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//My vending machine program, Ernesto Chan 5/6/2023


#include <iostream>
#include <fstream>
#include <vector>

#include <sstream>
#include <cstdlib>
#include <iomanip>
using namespace std;
//struct that represents the "item" variable that will be used to stock the vending machine
struct Item {
    string name;
    double price;
    int stock;
};

// function prototype for vendingMachineMenu
void vendingMachineMenu(vector<Item>& items, Item boughtItems[], int boughtItemsSize, double& balance);

// function prototype for listItems
void listItems(vector<Item>& items);

//function prototype for inventoryReport
void inventoryReport(vector<Item>& items);

// function prototype for quicksort
void quicksort(vector<Item>& items, int left, int right);
void sortItems(vector<Item>& items);



//In the main function vectors to represent the items in vending machine inventory and an array is used to store the purchased items 
//Input file is read and data is used for vector for vending machine
//Item class is formatted by commas seperating each value 
//Main menu is accessed with options for going to the vending machine,printing an inventory report, and exiting the program
//Vending machine and inventory report are handled by functions that are called
int main()
{
    vector<Item> items;
    Item boughtItems[100];
    ifstream file("items.txt");
    int input;
    string line;
    double balance = 20.00;
    while (getline(file, line)) {
        stringstream ss(line);
        string name;
        double price;
        int stock;
        getline(ss, name, ',');
        ss >> price;
        ss.ignore();
        ss >> stock;
        items.push_back({ name,price,stock });
        sortItems(items);

    }




    while (true) {

        cout << "Hello welcome to my program, your balance is " << balance << " here are your options\n";
        cout << "1.Vending machine menu\n";
        cout << "2.Print Inventory report\n";
        cout << "3.Exit the program\n";

        cin >> input;
        if (input <= 0 || input >= 4) {
            cout << "Invalid input, please input a valid input\n";
        }
        else if (input == 1) {
            vendingMachineMenu(items, boughtItems,100, balance);
            continue;
        }
        else if (input == 2) {
            inventoryReport(items);
            cout << "Report has been printed.\n\n";
            continue;
        }
        else if (input == 3) {
            cout << "Goodbye\n";
            break;
        }
    }
    return 0;
}


//function responsible for ui that handles input and output throught text prompts of vending machine
// menu will keep popping up through the use of loops enabling multiple uses of same option
// user is able control when to exit the program through this as well as access different menus
//items are purchased and put into an array
//items are listed by listItems function
// purchasing item causes decrements item stock as well as balance
//function can also return to main menu and exit program
void vendingMachineMenu(vector<Item>& items, Item boughtItems[], int boughtItemsSize, double& balance) {
    int exitProgramOption = items.size() + 2;
    int listPurchasesOption = items.size() + 1;
    int input = 0;
    int boughtItemCount = 0; // initialize count of bought items to zero
    cout << "Hello welcome to the vending machine, choose an item or go back to the main menu\n";

    while (true) {
        cout << "Pick an option:" << endl;
        listItems(items);
        cout << listPurchasesOption << "." << "See purchases" << endl;
        cout << exitProgramOption << "." << "Exit program" << endl;

        cin >> input;
        if (input<0 || input>exitProgramOption) {
            cout << "Invalid input please try again" << endl;
            continue;
        }
        if (input == listPurchasesOption) {
            cout << "You bought: " << endl;
            for (int i = 0; i < boughtItemCount; i++) {
                cout << boughtItems[i].name << endl;
            }
            cout << endl;
            continue;
        }
        if (input == items.size()) {
            return;
        }

        if (input == exitProgramOption) {
            cout << "Goodbye";
            exit(0);
        }
        if (input >= 0 && input < items.size()) {
            if (balance <= 0) {
                cout << "Not enough money :(" << endl;
                continue;
            }
            if (items[input].stock <= 0) {
                cout << "This item is out of stock" << endl;
                continue;
            }
            if (boughtItemCount >= boughtItemsSize) {
                cout << "You can't buy any more items. Please see purchases or exit." << endl;
                continue;
            }
            boughtItems[boughtItemCount] = items[input];
            boughtItemCount++;
            cout << "You bought " << items[input].name << endl;
            balance = balance - items[input].price;
            cout << "Your balance is " << balance << endl;
            items[input].stock--;
        }
    }
}
//function that iterates over items vector
// list information of each item in vector as well as additional option to go back to main menu
void listItems(vector<Item>& items) {
    for (int i = 0; i < items.size(); i++) {
        cout << i << "."<< items[i].name << " Price: $" << fixed << setprecision(2) << items[i].price << " Stock:" << items[i].stock << endl;
    }
    cout << items.size() << ". Go back to the main menu" << endl;
}
//Function responsible for creating inventory report file
// iterates through items vector and outputs it to file
void inventoryReport(vector<Item>& items) {
    ofstream file("inventory_report.txt");
    file << "Name\tPrice\tStock\n";
    for (Item item : items) {
        file << item.name << '\t' << item.price << '\t' << item.stock << endl;
    }
    file.close();

}
// function to call quicksort and sort the items vector
void sortItems(vector<Item>& items) {
    quicksort(items, 0, items.size() - 1);
}
// implementation of quicksort algorithm
void quicksort(vector<Item>& items, int left, int right) {
    if (left < right) {
        int pivotIndex = (left + right) / 2;
        string pivotValue = items[pivotIndex].name;
        int i = left, j = right;
        while (i <= j) {
            while (items[i].name < pivotValue) {
                i++;
            }
            while (items[j].name > pivotValue) {
                j--;
            }
            if (i <= j) {
                swap(items[i], items[j]);
                i++;
                j--;
            }
        }
        if (left < j) {
            quicksort(items, left, j);
        }
        if (i < right) {
            quicksort(items, i, right);
        }
    }
}


