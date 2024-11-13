#ifndef BILL_H

#define BILL_H

#include <ctime>
#include"auxfunc.h"


Bill addProductBill(Bill);
void addBill();
Bill searchBillById(const char*);
void readBillById();
void editBillById(const char*);
void editBill();
#endif