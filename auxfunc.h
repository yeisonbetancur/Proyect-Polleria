#ifndef AUXF

#define AUXF
#include <ctime>
#include <cstring>
#include <iostream>

struct Product{
	char id[20];
	char name[30];
	double price;
};
struct Bill{
	char id[20];
	tm date;
	char productId[20][20];
	int amountProduct[20];
	bool delivery;
	char direction[20];
	int discount;
	double totalPrice;
};
struct Expense{
	char id[20];
	char name[30];
	double price;
	tm date;
};

bool checkId(const char* id);
bool checkBillId(const char* id);
double calculateTotal(Bill bill);
bool discountCheck(int x);
bool checkBool(int x);

#endif
