#ifndef BILL

#define BILL

#include <ctime>
#include"auxfunc.h"


Bill addProductBill(Bill bill);
void addBill();
Bill searchBillById(const char* id);
void readBillById();
void editBillById(const char* id);
void editBill();
#endif