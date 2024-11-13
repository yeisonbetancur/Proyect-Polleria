
#include"auxfunc.h"
#include"Products.cpp"
#include"Bills.h"
using namespace std;





int main();
void productMenu();

void productMenu(){
	int x;
	cout<<"Este es el menu de manejo de las productos, ingresa un valor del 0 al tin segun lo que desees hacer";
	cout<<"\n1.CrearProducto";
	cout<<"\n2.Editar el contenido de un producto";
	cout<<"\n3.Leer producto por id";
	cout<<"\n4.Mostrar lista de productos";
	cout<<"\n0.Volver al menu principal";
	cin>>x;
	switch(x){
		case 0: main();break;
		case 1: addProduct();productMenu();break;
		case 2: modifyProductByID();productMenu();break;
		case 3: readProductById();productMenu();break;
		case 4: listProducts();productMenu();break;
		default: cout<<"Ingresa un valor valido";productMenu();
	}
}


void billMenu(){
	int x;
	cout<<"Este es el menu de manejo de las facturas, ingresa un valor del 0 al tin segun lo que desees hacer";
	cout<<"\n1.CrearFactura";
	cout<<"\n2.Leer una factura especifica, segun su ID";
	cout<<"\n3.Editar el contenido de una factura";
	cout<<"\n4.Eliminar una factura (la borra del balance)";
	cout<<"\n0.Volver al menu principal";
	cin>>x;
	switch(x){
		case 1: addBill();break;
		case 2: readBillById();break;
		case 3: editBill();break;
		case 0: break;
	}
}

int main(){
	int x;
	cout<<"Sistema de Facturacion, Polleria Don Pollo";
	cout<<"Ingresa un numero (0-6) para seleccionar la funcion desees utilizar";
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
		case 1: billMenu();
		case 2: productMenu();break;
		default:cout<<"Ingresa un valor valido\n";main();
	}
}




















