
#include"auxfunc.cpp"
#include"Products.cpp"
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
    bill.date=localtime (&rawtime);
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