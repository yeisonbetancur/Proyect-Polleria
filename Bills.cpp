#include"auxfunc.h"


using namespace std;


Bill addProductBill(Bill bill){
	int i = 0, bcheck;
    bool pending = true;
    while (pending && i < 20) { 
        cout << "Ingresa el id del producto a ingresar: ";
        cin >> bill.productId[i];
        cout << "Ingresa la cantidad: ";
        cin >> bill.amountProduct[i];
        cout << "¿Deseas agregar otro producto? (0 para no, 1 para sí): ";
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

void addBill(){
	Bill bill;
	time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
	ofstream file("bills.dat",ios::binary | ios::app);
	if (!file){
		cerr<<"No se pudo abrir el archivo product.dat";
		return ;
	}
	cout << "Ingresa el ID (debe ser unico): ";
    cin >> bill.id;//want to change this
    
    while (checkBillId(bill.id)==false) {
        cerr << "El ID ya existe. Intenta con otro ID." << endl;
        cin >> bill.id;
    }
    bill.date=*localtime (&rawtime);
    bill = addProductBill(bill);
    cout<<"Tiene entrega a domicilio?(1 para si, 0 para no) ";
    cin>>bill.delivery;
	
    if(bill.delivery==1){
        cout<<"\nCual es la direccion del domicilio? ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.getline(bill.direction,20);
    }
	cout<<"\nLa venta tiene descuento? ";
	cin>>bill.discount;
	while(discountCheck(bill.discount)==false){
		cout<<"Ingresa un valor entre 1 y 99";
		cin>>bill.discount;
	}
	bill.totalPrice=calculateTotal(bill);

	file.write(reinterpret_cast<const char*>(&bill), sizeof(Bill));
	file.close();
	cout<<"Factura Realizada con Exito\n";

}

Bill searchBillById(const char* id){
    Bill bill={};
    ifstream archivo("bills.dat", ios::binary);
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return bill ;
    }

    while (archivo.read(reinterpret_cast<char*>(&bill), sizeof(Bill))) {
        if (strcmp(bill.id, id) == 0) {
            archivo.close();
            return bill;
        }
    }
    archivo.close();
    return bill;
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
            cout <<"Fecha: "<<(1900+bill.date.tm_year)<<"/"<<bill.date.tm_mon+1<<"/"<<bill.date.tm_mday<<"/"<<bill.date.tm_hour<<"/"<<bill.date.tm_min<<"/"<<bill.date.tm_sec<<"\n";
            cout <<"Precio: $"<<bill.totalPrice<<"\n";
        }else{
        	cout<<"No se encontro el producto. con id; "<<id;
		}
	}

void editBillById(const char* id) {
    Bill bill = searchBillById(id);  
    
    if (bill.id[0] == '\0') {
        cerr << "No se encontró ninguna factura con el ID: " << id << endl;
        return;
    }

    cout << "\nFactura encontrada:\n";
    cout << "ID: " << bill.id << "\n";
    cout << "Fecha: " << (1900 + bill.date.tm_year) << "/" 
         << bill.date.tm_mon << "/" << bill.date.tm_mday << "\n";
    cout << "Precio actual: $" << bill.totalPrice << "\n";
    cout << "¿Deseas cambiar la entrega a domicilio? (1 para sí, 0 para no): ";
    cin >> bill.delivery;

    if (bill.delivery) {
        cout << "Ingresa la nueva dirección de entrega: ";
        cin.ignore();
        cin.getline(bill.direction, 20);
    } else {
        strcpy(bill.direction, "");  
    }


    cout << "Ingresa el nuevo descuento (1-99): ";
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

    // Busca la posición de la factura en el archivo para sobrescribirla
    Bill tempBill;
    while (file.read(reinterpret_cast<char*>(&tempBill), sizeof(Bill))) {
        if (strcmp(tempBill.id, id) == 0) {
            file.seekp(-static_cast<streamoff>(sizeof(Bill)), ios::cur);
            file.write(reinterpret_cast<const char*>(&bill), sizeof(Bill));
            cout << "Factura actualizada con éxito.\n";
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
    cin.getline(id,20);
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

    // Leer y copiar facturas que no coincidan con el ID al archivo temporal
    while (archivo.read(reinterpret_cast<char*>(&bill), sizeof(Bill))) {
        if (strcmp(bill.id, id) != 0) {
            archivoTemp.write(reinterpret_cast<const char*>(&bill), sizeof(Bill));
        } else {
            found = true;
        }
    }

    archivo.close();
    archivoTemp.close();

    // Reemplazar el archivo original solo si la factura se encontró y eliminó
    if (found) {
        remove("bills.dat");                // Eliminar archivo original
        rename("temp.dat", "bills.dat");     // Renombrar archivo temporal
        cout << "Factura eliminada con éxito." << endl;
    } else {
        remove("temp.dat");  // Eliminar el archivo temporal si no se encontró el ID
        cerr << "No se encontró ninguna factura con el ID: " << id << endl;
    }
}

void deleteBill(){
char id[20];
cout<<"\nIngresa el id de la factura a eliminar: ";
cin.getline(id,20);
deleteBillById(id);
}
