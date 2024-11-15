#include<iostream>
#include<fstream>
#include<ctime>
#include<cstring>
#include <cctype>
#include<vector>
#include<algorithm>
#include <limits>
#include<stdio.h>

using namespace std;



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

bool checkBool(int x){
    if(x!=1&&x!=0){
        return false;
    }else return true;
}

bool discountCheck(int x){
    if(x<=99&&x>=0){
        return true;
    }else return false;
}

void polleria(){
	 cout << "______     _ _            ______             ______     _ _       " << endl;
    cout << "| ___ \\   | | |           |  _  \\            | ___ \\   | | |      " << endl;
    cout << "| |_/ /__ | | | ___  ___  | | | |___  _ __   | |_/ /__ | | | ___  " << endl;
    cout << "|  __/ _ \\| | |/ _ \\/ __| | | | / _ \\| '_ \\  |  __/ _ \\| | |/ _ \\ " << endl;
    cout << "| | | (_) | | | (_) \\__ \\ | |/ / (_) | | | | | | | (_) | | | (_) |" << endl;
    cout << "\\_|  \\___/|_|_|\\___/|___/ |___/ \\___/|_| |_| \\_|  \\___/|_|_|\\___/ " << endl;
    cout << "                                                                  " << endl;
}

bool isValidId(const char* id) {
    for (int i = 0; i < strlen(id); ++i) {
        if (!isalnum(id[i])) {  // Comprobar que el caracter sea alfanumérico
            return false;
        }
    }
    return true;
}

bool checkId(const char* id) {
    ifstream archivo("products.dat", ios::binary);
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return false;
    }
if (strlen(id) == 0 || !isValidId(id)){
    	cout << "ERROR: El ID no es válido. Debe ser alfanumerico y no estar vacío.\n";
        return false;	
		}

    Product product;
    while (archivo.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
        if (strcmp(product.id, id) == 0) {
            cerr<<"El ID ya esta registrado";
            return false;
        }
    }
    cout<<"\nSe registro con exito el id";
    archivo.close();
    return true;
}



bool checkBillId(const char* id) {
    ifstream archivo("bills.dat", ios::binary);
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return false;
    }

        if (strlen(id) == 0 || !isValidId(id)){
    	cout << "ERROR: El ID no es válido. Debe ser alfanumerico y no estar vacío.\n";
        return false;	
		}
    Bill bill;
    while (archivo.read(reinterpret_cast<char*>(&bill), sizeof(Bill))) {
    	
        if (strcmp(bill.id, id) == 0) {
            cerr<<"El ID ya esta registrado";
            return false;
        }
    }
    cout<<"\nSe registro con exito el id";
    archivo.close();
    return true;
}

bool checkExpenseId(const char* id) {
    ifstream archivo("expenses.dat", ios::binary);
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return false;
    }

    Expense expense;
    while (archivo.read(reinterpret_cast<char*>(&expense), sizeof(Expense))) {
        if (strcmp(expense.id, id) == 0) {
            cerr<<"El ID ya esta registrado";
            return false;
        }
    }
    cout<<"\nSe registro con exito el id";
    archivo.close();
    return true;
}

Product searchProductByID(const char* id) {
    Product product={};
     strcpy(product.id, "-1");
    ifstream archivo("products.dat", ios::binary);
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return product ;
    }

    while (archivo.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
        if (strcmp(product.id, id) == 0) {
            archivo.close();
            return product;
        }
    }
    archivo.close();
     strcpy(product.id, "-1");
    return product;
}

bool isAlphanumeric(const char* str) {
    for (int i = 0; i < strlen(str); i++) {
        if (!isalnum(str[i])) {  // Verifica si no es alfanumérico
            return false;         // Si encuentra un carácter no alfanumérico, retorna false
        }
    }
    return true;  // Retorna true si todos los caracteres son alfanuméricos
}

double calculateTotal(Bill bill){
    double total = 0;
    if (bill.discount < 0 || bill.discount > 100) {
        cerr << "ERROR: El descuento debe estar entre 0 y 100.\n";
        return total;
    }
    for (int i = 0; i < 20; i++) {
        if (bill.productId[i][0] == '\0'||!isAlphanumeric(bill.productId[i])) {
            break;
        }
        Product product = searchProductByID(bill.productId[i]);
        if (product.price > 0) {
            total += product.price * bill.amountProduct[i];
        } else {
            cerr << "Producto con ID " << bill.productId[i] << " no encontrado o precio inválido.\n";
        }
    }
    total -= total * (bill.discount / 100.0);
    return total;
}


  void readProductById(){
  	char id[20];
  	cout<<"Ingresa el ID ";
  	cin.ignore(numeric_limits<streamsize>::max(), '\n');
  	cin.getline(id,20);
  	Product product=searchProductByID(id);
  	if(product.id[0] != '\0'&& strcmp(product.id, id)==0){
    	cout <<"\nProducto encontrado:\n";
            cout <<"ID: "<<product.id<<"\n";
            cout <<"Nombre: "<<product.name<<"\n";
            cout <<"Precio: $"<<product.price<<"\n";
        }else{
        	cout<<"No se encontro el producto. con id; "<<id;
		}
	}
	
void addProduct(){
	Product product;
	ofstream file("products.dat",ios::binary | ios::app);
	if (!file){
		cerr<<"No se pudo abrir el archivo product.dat";
		return ;
	}
	cout << "Ingresa el ID (debe ser unico): ";
    cin >> product.id;
    
    if (!checkId(product.id)) {
        cerr << "El ID ya existe. Intenta con otro ID." << endl;
        return;
    }
	cout<<"Ingresa el nombre del producto (maximo 30 caracteres)";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.getline(product.name, 30);
	cout << "Ingresa el precio unitario del producto: ";
	while (!(cin >> product.price)) {
    	cin.clear();
    	cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    	cout << "Entrada invalida. Ingresa un nï¿½mero valido para el precio: ";
	}
	file.write(reinterpret_cast<const char*>(&product), sizeof(Product));
	file.close();
	cout<<"Producto ingresado correctamente\n";

}

void modifyProductByID() {
	char id[20];
  	cout<<"Ingresa el ID ";
  	cin.ignore(numeric_limits<streamsize>::max(), '\n');
  	cin.getline(id,20);
    fstream archivo("products.dat", ios::binary | ios::in | ios::out);
    
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    Product product;
    while (archivo.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
        if (strcmp(product.id, id) == 0) {
            cout << "\nProducto encontrado!";
            cout << "\nIngresa el nuevo nombre del producto: ";
            cin.getline(product.name, 30);
            cout << "Ingresa el nuevo precio del producto: ";
            cin >> product.price;
            archivo.seekp(-static_cast<int>(sizeof(Product)), ios::cur);
            archivo.write(reinterpret_cast<const char*>(&product), sizeof(Product));
            archivo.close();
            cout << "Producto modificado con ï¿½xito." << endl;

        }
    }

    archivo.close();
    cout << "No se encontrï¿½ el producto con el ID: " << id << endl;

}

bool loadProducts(Product products[], int& productCount) {
    ifstream file("products.dat", ios::binary);
    if (!file) {
        cerr << "Error al abrir el archivo products.dat" << endl;
        return false;
    }

    Product product;
    productCount = 0;
    while (file.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
        products[productCount++] = product;
    }

    file.close();
    return true;
}

void displayProducts(Product products[], int productCount){
    for (int i = 0; i < productCount; i++) {
        cout << "ID: " << products[i].id << ", Nombre: " << products[i].name << ", Precio: $" << products[i].price << endl;
    }
}
void sortProducts(Product products[], int productCount) {
    for (int i = 0; i < productCount - 1; i++) {
        for (int j = i + 1; j < productCount; j++) {
            if (strcmp(products[i].id, products[j].id) > 0) {
                Product temp = products[i];
                products[i] = products[j];
                products[j] = temp;
            }
        }
    }
}

void listProducts(){
	 const int MAX_PRODUCTS = 200;
    Product products[MAX_PRODUCTS];
    int productCount = 0;
    if (!loadProducts(products, productCount)) {
        return; 
    }

    sortProducts(products, productCount);

    cout << "Lista de productos ordenada por ID (de menor a mayor):" << endl;
    displayProducts(products, productCount);

    return ;
}



// Función para agregar productos a la factura
Bill addProductBill(Bill bill) {
    int i = 0, bcheck;
    bool pending = true;
    
    while (pending && i < 20) { 
        cout << "\nEsta es la lista de los productos en el sistema: ";
        listProducts();  // Asumiendo que esta función muestra los productos disponibles.
        cout << "\nIngresa el id del producto a ingresar: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.getline(bill.productId[i], 20);
        
        Product product=searchProductByID(bill.productId[i]);
        cout << "ID encontrado en archivo: " << product.id << endl;
        if(product.id=="-1"){
        	cout<<"ERROR; El Id no es de ningun producto registrado";
        	continue;
		}
        
        // Verificar si el ID del producto es válido
        if (strlen(bill.productId[i]) == 0 || !isValidId(bill.productId[i])) {
            cout << "ERROR: El ID del producto no es válido. Debe ser alfanumerico y no estar vacío.\n";
            continue;
        }

        cout << "Ingresa la cantidad: ";
        cin >> bill.amountProduct[i];

        // Verificar que la cantidad ingresada sea válida y razonable
        if (bill.amountProduct[i] <= 0 || bill.amountProduct[i] > 100000) {  // Limitar la cantidad
            cout << "ERROR: La cantidad debe ser mayor que 0 y no excesivamente grande.\n";
            continue;
        }

        cout << "Deseas agregar otro producto? (0 para no, 1 para sí): ";
        bool cCheck = true;
        while (cCheck) {
            cin >> bcheck;
            if (checkBool(bcheck)) {
                if (bcheck == 0) {  // Si el usuario elige no agregar más productos
                    pending = false;  // Terminar el bucle principal
                }
                cCheck = false;  // Salir del bucle interno
            } else {
                cout << "ERROR: Ingresa 0 para NO o 1 para SI: ";
            }
        }
        i++;  // Incrementar el índice para el próximo producto
    }

    return bill;
}

void addBill() {
    Bill bill;
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    ofstream file("bills.dat", ios::binary | ios::app);
    if (!file) {
        cerr << "No se pudo abrir el archivo bills.dat" << endl;
        return;
    }

    cout << "Ingresa el ID (debe ser unico): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.getline(bill.id, 20);

    while (!checkBillId(bill.id)) {
        cerr << "\nEl ID ya existe. Intenta con otro ID: ";
        cin.getline(bill.id, 20); // Evitar que el buffer anterior contamine la nueva entrada
    }

    bill.date = *localtime(&rawtime);
    bill = addProductBill(bill);

    cout << "Tiene entrega a domicilio? (1 para si, 0 para no): ";
    while (!(cin >> bill.delivery) || !checkBool(bill.delivery)) { // Validar booleano
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nERROR: Ingresa 1 para Si o 0 para NO: ";
    }

    if (bill.delivery == 1) {
        cout << "\nCual es la dirección del domicilio? ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.getline(bill.direction, 20);
    }

    cout << "\nLa venta tiene descuento? Ingresa un valor entre 0 y 99: ";
    while (!(cin >> bill.discount) || !discountCheck(bill.discount)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "ERROR: Ingresa un descuento valido (0-99): ";
    }

    bill.totalPrice = calculateTotal(bill);
    file.write(reinterpret_cast<const char*>(&bill), sizeof(Bill));
    file.close();
    cout << "Factura realizada con exito\n";
}

Bill searchBillById(const char* id){
    Bill bill={};
    
    ifstream archivo("bills.dat", ios::binary);
    if (!archivo) {
        cerr << "\nError al abrir el archivo." << endl;
        return bill ;
    }

    while (archivo.read(reinterpret_cast<char*>(&bill), sizeof(Bill))) {
        if (strcmp(bill.id, id) == 0) {
            archivo.close();
            return bill;
        }
    }
    archivo.close();
    return bill={};
}

void readBillById(){
  	char id[20];
  	cout<<"Ingresa el ID ";
  	cin.ignore(numeric_limits<streamsize>::max(), '\n');
  	cin.getline(id,20);
  	Bill bill=searchBillById(id);
  	if(bill.id[0] != '\0'&& strcmp(bill.id, id)==0){
    	cout <<"\nProducto encontrado:\n";
            cout <<"ID: "<<bill.id<<"\n";
            cout <<"Fecha: "<<(1900+bill.date.tm_year)<<"/"<<bill.date.tm_mon+1<<"/"<<bill.date.tm_mday<<"\n";
            cout <<"Precio: $"<<bill.totalPrice<<"\n";
        }else{
        	cout<<"\nNo se encontro el producto. con id: "<<id;
		}
	}

void editBillById(const char* id) {
    Bill bill = searchBillById(id);  
    if (bill.id[0] == '\0') {
        cerr << "\nNo se encontro ninguna factura con el ID: " << id << endl;
        return;
    }
    cout << "\nFactura encontrada:\n";
    cout << "ID: " << bill.id << "\n";
    cout << "Fecha: " << (1900 + bill.date.tm_year) << "/" 
         << bill.date.tm_mon << "/" << bill.date.tm_mday << "\n";
    cout << "Precio actual: $" << bill.totalPrice << "\n";
    cout << "\nDeseas cambiar la entrega a domicilio? (1 para sí, 0 para no): ";
    cin >> bill.delivery;
    if (bill.delivery) {
        cout << "\nIngresa la nueva dirección de entrega: ";
        cin.ignore();
        cin.getline(bill.direction, 20);
    } else {
        strcpy(bill.direction, "");  
    }
    cout << "\nIngresa el nuevo descuento (1-99): ";
    cin >> bill.discount;
    while (!discountCheck(bill.discount)) {
        cout << "Descuento inválido. Ingresa un valor entre 1 y 99: ";
        cin >> bill.discount;
    }
    bill.totalPrice = calculateTotal(bill);
    fstream file("bills.dat", ios::binary | ios::in | ios::out);
    if (!file) {
        cerr << "Error al abrir el archivo para la edición." << endl;
        return;
    }
    Bill tempBill;
    while (file.read(reinterpret_cast<char*>(&tempBill), sizeof(Bill))) {
        if (strcmp(tempBill.id, id) == 0) {
            file.seekp(-static_cast<streamoff>(sizeof(Bill)), ios::cur);
            file.write(reinterpret_cast<const char*>(&bill), sizeof(Bill));
            cout << "Factura actualizada con exito.\n";
            file.close();
            return;
        }
    }
    cerr << "Error: No se pudo encontrar la factura para actualizar." << endl;
    file.close();
}


void editBill(){
    char id[20];
    cout<<"\nIngresa el id de la factura a editar: ";
     cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.getline(id, 20);
    editBillById(id);
}


void deleteBillById(const char* id) {
    ifstream archivo("bills.dat", ios::binary);
    if (!archivo) {
        cerr << "Error al abrir el archivo de facturas." << endl;
        return;
    }
    ofstream archivoTemp("temp.dat", ios::binary);
    if (!archivoTemp) {
        cerr << "Error al crear el archivo temporal." << endl;
        archivo.close();
        return;
    }
    Bill bill;
    bool found = false;
    while (archivo.read(reinterpret_cast<char*>(&bill), sizeof(Bill))) {
        if (strcmp(bill.id, id) != 0) {
            archivoTemp.write(reinterpret_cast<const char*>(&bill), sizeof(Bill));
        } else {
            found = true;
        }
    }
    archivo.close();
    archivoTemp.close();
    if (found) {
        remove("bills.dat"); 
        rename("temp.dat", "bills.dat");   
        cout << "Factura eliminada con éxito." << endl;
    } else {
        remove("temp.dat");  
        cerr << "No se encontro ninguna factura con el ID: " << id << endl;
    }
}

void deleteBill(){
	char id[20];
	cout<<"\nIngresa el id de la factura a eliminar: ";
	 cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.getline(id,20);
	deleteBillById(id);
}


void printBill(const Bill& bill) {
    cout << "ID de la factura: " << bill.id << endl;
    cout << "Fecha: " << (bill.date.tm_mday) << "/" << (bill.date.tm_mon + 1) << "/" << (bill.date.tm_year + 1900) << endl;
    cout << "Direccion de entrega: " << bill.direction << endl;
    cout << "Entrega: " << (bill.delivery ? "Si" : "No") << endl;
    cout << "Descuento: " << bill.discount << "%" << endl;
    cout << "Total: $" << bill.totalPrice << endl;
    cout << "Productos:" << endl;
    for (int i = 0; i < 20; i++) {
        if (bill.productId[i][0] == '\0'||!isAlphanumeric(bill.productId[i])) {
            break;
        }
        Product product=searchProductByID(bill.productId[i]);
        cout << "\tID Producto: " << product.id << "Nombre del producto: "<<product.name<< ", Cantidad: " << bill.amountProduct[i] << ", Precio unidad: "<< product.price<< endl;
    }
    cout << "------------------------" << endl;
}


void printAllBills() {
    ifstream archivo("bills.dat", ios::binary);
    if (!archivo) {
        cerr << "Error al abrir el archivo bills.dat." << endl;
        return;
    }

    Bill bill;
    while (archivo.read(reinterpret_cast<char*>(&bill), sizeof(Bill))) {
        printBill(bill);
    }

    archivo.close();
}



void inputExpenseData(Expense &expense){
    cout<<"\nIngrese el ID de la entrada: ";
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cin.getline(expense.id,20);
    while (checkExpenseId(expense.id)==false&&isAlphanumeric(expense.id)){
    	cout<<"\nEl id esta repetido o no es alfanumerico, ingresa otro: ";
    	cin.ignore(numeric_limits<streamsize>::max(),'\n');
    	cin.getline(expense.id,20);
	}
    cout<<"Ingrese el nombre: ";
    cin.getline(expense.name,30);

    cout<<"Ingrese el precio: ";
    cin>>expense.price;

    time_t rawtime;
    time(&rawtime);
    expense.date=*localtime(&rawtime);
}

void writeExpense(){
    Expense expense;
    inputExpenseData(expense);

    ofstream file("expenses.dat",ios::binary|ios::app);
    if(!file){
        cerr<<"No se pudo abrir el archivo expenses.dat para escribir."<<endl;
        return;
    }

    file.write(reinterpret_cast<const char*>(&expense),sizeof(Expense));
    file.close();
    cout<<"Gasto agregado con exito."<<endl;
}

void readAllExpenses(){
    ifstream file("expenses.dat",ios::binary);
    if(!file){
        cerr<<"No se pudo abrir el archivo expenses.dat para leer."<<endl;
        return;
    }

    Expense expense;
    while(file.read(reinterpret_cast<char*>(&expense),sizeof(Expense))){
        cout<<"ID: "<<expense.id<<", Nombre: "<<expense.name
            <<", Precio: $"<<expense.price
            <<", Fecha: "<<asctime(&expense.date);
    }

    file.close();
}

bool readExpenseById(const char* id){
    ifstream file("expenses.dat",ios::binary);
    if(!file){
        cerr<<"No se pudo abrir el archivo expenses.dat para leer."<<endl;
        return false;
    }

    Expense expense;
    while(file.read(reinterpret_cast<char*>(&expense),sizeof(Expense))){
        if(strcmp(expense.id,id)==0){
            cout<<"ID: "<<expense.id<<", Nombre: "<<expense.name
                <<", Precio: $"<<expense.price
                <<", Fecha: "<<asctime(&expense.date);
            file.close();
            return true;
        }
    }

    file.close();
    cerr<<"Gasto con ID "<<id<<" no encontrado."<<endl;
    return false;
}

void editExpense(const char* id){
    fstream file("expenses.dat",ios::binary|ios::in|ios::out);
    if(!file){
        cerr<<"No se pudo abrir el archivo expenses.dat para editar."<<endl;
        return;
    }

    Expense expense;
    while(file.read(reinterpret_cast<char*>(&expense),sizeof(Expense))){
        if(strcmp(expense.id,id)==0){
            cout<<"Editando el gasto con ID: "<<id<<endl;
            inputExpenseData(expense);

            file.seekp(-static_cast<int>(sizeof(Expense)),ios::cur);
            file.write(reinterpret_cast<const char*>(&expense),sizeof(Expense));
            cout<<"Gasto editado con exito."<<endl;
            file.close();
            return;
        }
    }

    cerr<<"Gasto con ID "<<id<<" no encontrado."<<endl;
    file.close();
}

void deleteExpense(const char* id){
    ifstream file("expenses.dat",ios::binary);
    if(!file){
        cerr<<"No se pudo abrir el archivo expenses.dat para borrar."<<endl;
        return;
    }

    ofstream tempFile("temp.dat",ios::binary);
    Expense expense;
    bool deleted=false;

    while(file.read(reinterpret_cast<char*>(&expense),sizeof(Expense))){
        if(strcmp(expense.id,id)!=0){
            tempFile.write(reinterpret_cast<const char*>(&expense),sizeof(Expense));
        }else{
            deleted=true;
        }
    }

    file.close();
    tempFile.close();
    remove("expenses.dat");
    rename("temp.dat","expenses.dat");

    if(deleted){
        cout<<"Gasto con ID "<<id<<" eliminado con exito."<<endl;
    }else{
        cerr<<"Gasto con ID "<<id<<" no encontrado."<<endl;
    }
}

void sortExpenses(){
    const int MAX_EXPENSES=100;
    Expense expenses[MAX_EXPENSES];
    int count=0;

    ifstream file("expenses.dat",ios::binary);
    if(!file){
        cerr<<"No se pudo abrir el archivo expenses.dat para ordenar."<<endl;
        return;
    }

    while(file.read(reinterpret_cast<char*>(&expenses[count]),sizeof(Expense))&&count<MAX_EXPENSES){
        count++;
    }
    file.close();

    for(int i=0;i<count-1;i++){
        for(int j=0;j<count-i-1;j++){
            if(strcmp(expenses[j].id,expenses[j+1].id)>0){
                Expense temp=expenses[j];
                expenses[j]=expenses[j+1];
                expenses[j+1]=temp;
            }
        }
    }

    ofstream sortedFile("expenses.dat",ios::binary|ios::trunc);
    if(!sortedFile){
        cerr<<"No se pudo abrir el archivo expenses.dat para escribir los datos ordenados."<<endl;
        return;
    }

    for(int i=0;i<count;i++){
        sortedFile.write(reinterpret_cast<const char*>(&expenses[i]),sizeof(Expense));
    }

    sortedFile.close();
    cout<<"Gastos ordenados por ID exitosamente."<<endl;
}

bool sameDay(const tm& date1,const tm& date2){
    return date1.tm_year==date2.tm_year&&date1.tm_mon==date2.tm_mon&&date1.tm_mday==date2.tm_mday;
}

void loadBills(Bill bills[],int& billCount){
    ifstream file("bills.dat",ios::binary);
    if(!file){
        cerr<<"Error al abrir el archivo bills.dat"<<endl;
        return;
    }
    billCount=0;
    while(file.read(reinterpret_cast<char*>(&bills[billCount]),sizeof(Bill))){
        billCount++;
    }
    file.close();
}

void sortBillsByTime(Bill bills[],int billCount){
    for(int i=0;i<billCount-1;i++){
        for(int j=i+1;j<billCount;j++){
            if(difftime(mktime(&bills[i].date),mktime(&bills[j].date))>0){
                Bill temp=bills[i];
                bills[i]=bills[j];
                bills[j]=temp;
            }
        }
    }
}

void printBillsByDay(const Bill bills[],int billCount,const tm& date){
    for(int i=0;i<billCount;i++){
        if(sameDay(bills[i].date,date)){
            cout<<"ID: "<<bills[i].id<<", Hora: "<<bills[i].date.tm_hour<<":"<<bills[i].date.tm_min<<", Total: $"<<bills[i].totalPrice<<endl;
        }
    }
}

void checkAndPrintBillsOnDate(){
    Bill bills[100];
    int billCount=0;
    loadBills(bills,billCount);
    int year,month,day;
    cout<<"Ingresa el año: ";
    cin>>year;
    cout<<"Ingresa el mes: ";
    cin>>month;
    cout<<"Ingresa el dia: ";
    cin>>day;
    tm date={};
    date.tm_year=year-1900;
    date.tm_mon=month-1;
    date.tm_mday=day;
    sortBillsByTime(bills,billCount);
    cout<<"Facturas para la fecha "<<day<<"/"<<month<<"/"<<year<<":"<<endl;
    printBillsByDay(bills,billCount,date);
}

int loadExpenses(Expense expenses[], int maxExpenses) {
    ifstream file("expenses.dat", ios::binary);
    if (!file) {
        cerr << "Error al abrir el archivo expenses.dat" << endl;
        return 0;
    }
    int count = 0;
    while (count < maxExpenses && file.read(reinterpret_cast<char*>(&expenses[count]), sizeof(Expense))) {
        count++;
    }
    file.close();
    return count;
}

// Función para comparar fechas (día, mes y año) y retornar verdadero si coinciden

// Función para ordenar por hora (hora y minutos)
void sortByTime(Expense expenses[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (expenses[i].date.tm_hour > expenses[j].date.tm_hour ||
               (expenses[i].date.tm_hour == expenses[j].date.tm_hour && expenses[i].date.tm_min > expenses[j].date.tm_min)) {
                Expense temp = expenses[i];
                expenses[i] = expenses[j];
                expenses[j] = temp;
            }
        }
    }
}

// Función para imprimir los gastos del mismo día ordenados por hora
void printSameDayExpenses(const Expense expenses[], int count, const tm& targetDate) {
    cout << "Gastos del mismo dia (ordenados por hora):\n";
    for (int i = 0; i < count; i++) {
        if (sameDay(expenses[i].date, targetDate)) {
            cout << "ID: " << expenses[i].id << ", Nombre: " << expenses[i].name
                 << ", Precio: $" << expenses[i].price << ", Hora: "
                 << expenses[i].date.tm_hour << ":" << expenses[i].date.tm_min << endl;
        }
    }
}

// Función principal que organiza todo
void processExpenses() {
    const int MAX_EXPENSES = 100;
    Expense expenses[MAX_EXPENSES];
    int count = loadExpenses(expenses, MAX_EXPENSES);
    if (count == 0) {
        cout << "No se encontraron gastos en el archivo.\n";
        return;
    }

    // Fecha objetivo (ejemplo: se pueden usar valores actuales o solicitados al usuario)
    tm targetDate;
    cout << "Ingrese la fecha para buscar (formato: YYYY MM DD): ";
    cin >> targetDate.tm_year >> targetDate.tm_mon >> targetDate.tm_mday;
    targetDate.tm_year -= 1900;
    targetDate.tm_mon -= 1;

    // Filtra y ordena los gastos del día especificado
    sortByTime(expenses, count);
    printSameDayExpenses(expenses, count, targetDate);
}

int loadBills(Bill bills[], int maxBills) {
    ifstream file("bills.dat", ios::binary);
    if (!file) {
        cerr << "Error al abrir el archivo bills.dat" << endl;
        return 0;
    }
    int count = 0;
    while (count < maxBills && file.read(reinterpret_cast<char*>(&bills[count]), sizeof(Bill))) {
        count++;
    }
    file.close();
    return count;
}



// Calcular el total de las facturas del mismo día
double calculateTotalBills(Bill bills[], int count, const tm& targetDate) {
    double totalBills = 0.0;
    for (int i = 0; i < count; i++) {
        if (sameDay(bills[i].date, targetDate)) {
            totalBills += bills[i].totalPrice;
        }
    }
    return totalBills;
}

// Calcular el total de los gastos del mismo día
double calculateTotalExpenses(Expense expenses[], int count, const tm& targetDate) {
    double totalExpenses = 0.0;
    for (int i = 0; i < count; i++) {
        if (sameDay(expenses[i].date, targetDate)) {
            totalExpenses += expenses[i].price;
        }
    }
    return totalExpenses;
}

// Función que procesa el balance del día
void processDailyBalance() {
    const int MAX_BILLS = 100;
    const int MAX_EXPENSES = 100;

    Bill bills[MAX_BILLS];
    Expense expenses[MAX_EXPENSES];

    int billCount = loadBills(bills, MAX_BILLS);
    int expenseCount = loadExpenses(expenses, MAX_EXPENSES);

    if (billCount == 0 || expenseCount == 0) {
        cout << "No se encontraron facturas o gastos en los archivos.\n";
        return;
    }

    // Fecha objetivo (se puede usar la fecha actual o proporcionarla)
    tm targetDate;
    cout << "Ingrese la fecha para el balance (formato: YYYY MM DD): ";
    cin >> targetDate.tm_year >> targetDate.tm_mon >> targetDate.tm_mday;
    targetDate.tm_year -= 1900;
    targetDate.tm_mon -= 1;

    // Calcular el total de facturas y gastos del día
    double totalBills = calculateTotalBills(bills, billCount, targetDate);
    double totalExpenses = calculateTotalExpenses(expenses, expenseCount, targetDate);

    // Mostrar el balance
    double balance = totalBills - totalExpenses;
    cout << "\nBalance del dia: \n";
    cout << "Total de facturas: $" << totalBills << endl;
    cout << "Total de gastos: $" << totalExpenses << endl;
    cout << "Balance final (facturas - gastos): $" << balance << endl;
}


void expenseMenu(){
    int option;
    char id[20];

        cout<<"\n--- Menu de Gestion de Gastos ---\n";
        cout<<"1. Agregar gasto\n";
        cout<<"2. Ver todos los gastos\n";
        cout<<"3. Buscar gasto por ID\n";
        cout<<"4. Editar gasto por ID\n";
        cout<<"5. Eliminar gasto por ID\n";
        cout<<"6. Ordenar gastos por ID\n";
        cout<<"0. Salir\n";
        cout<<"Seleccione una opcion: ";
        cin>>option;

        switch(option){
            case 1:writeExpense();break;
            case 2:readAllExpenses();break;
            case 3:cout<<"Ingrese el ID a buscar: ";cin>>id;readExpenseById(id);expenseMenu();break;
            case 4:cout<<"Ingrese el ID a editar: ";cin>>id;editExpense(id);expenseMenu();break;
            case 5:cout<<"Ingrese el ID a eliminar: ";cin>>id;deleteExpense(id);expenseMenu();break;
            case 6:sortExpenses();break;
            case 0: return;
                break;
            default:
                cout<<"Opcion invalida. Intente de nuevo."<<endl;
        }
}

void productMenu(){
	int x;
	cout<<"\nEste es el menu de manejo de las productos, ingresa un valor del 0 al tin segun lo que desees hacer";
	cout<<"\n1.CrearProducto";
	cout<<"\n2.Editar el contenido de un producto";
	cout<<"\n3.Leer producto por id";
	cout<<"\n4.Mostrar lista de productos";
	cout<<"\n0.Volver al menu principal\n";
	cin>>x;
	switch(x){
		case 0: return;break;
		case 1: addProduct();productMenu();break;
		case 2: modifyProductByID();productMenu();break;
		case 3: readProductById();productMenu();break;
		case 4: listProducts();productMenu();break;
		default: cout<<"Ingresa un valor valido";productMenu();
	}
}


void billMenu(){
	int x;
	cout<<"\nEste es el menu de manejo de las facturas, ingresa un valor del 0 al tin segun lo que desees hacer";
	cout<<"\n1.CrearFactura";
	cout<<"\n2.Leer una factura especifica, segun su ID";
	cout<<"\n3.Mostrar la lista de todas las facturas en pantalla";
	cout<<"\n4.Editar el contenido de una factura";
	cout<<"\n5.Eliminar una factura (la borra del balance)";
	cout<<"\n0.Volver al menu principal\n";
	cin>>x;
	switch(x){
		case 1: addBill();billMenu();break;
		case 2: readBillById();billMenu();break;
		case 3: printAllBills();billMenu();break;
		case 4: editBill();billMenu();break;
		case 5: deleteBill();billMenu();break;
		case 0: return;break;
		default:cout<<"Ingresa un valor valido: ";billMenu;
	}
}

int main(){
	int x;
	polleria();
	cout<<"\nSistema de Facturacion, Polleria Don Pollo";
	cout<<"\nIngresa un numero (0-6) para seleccionar la funcion desees utilizar";
	cout<<"\n1.Menu de Facturas";
	cout<<"\n2.Menu de Productos";
	cout<<"\n3.Menu de Gastos";
	cout<<"\n4.Leer Facturas del dia";
	cout<<"\n5.Leer Gastos del dia";
	cout<<"\n6.Generar balance del dia";
	cout<<"\n0.Cerrar el programa\n";
	cin>>x;
	switch(x){
		case 0: cout<<"Se ha cerrado con exito";return 0;
		case 1: billMenu();main();break;
		case 2: productMenu();main();break;
		case 3: expenseMenu();main();break;
		case 4: checkAndPrintBillsOnDate();main();break;
		case 5: processExpenses();main();break;
		case 6: processDailyBalance();main();break;
		default:cout<<"Ingresa un valor valido\n";main();
	}
}











