#pragma once		
#include <cstdlib>
#include <Windows.h>
#include "LectorDB.h"
#include "ListaProducto.h"
#include <vector>
#include "Cliente.h"
#include "Platos.h"
#include "Pedido.h"
#include "Producto.h"
#include "Bebidas.h"
#include <iostream>
#include <conio.h>
using namespace System;
using namespace std;

class Menu {
public:
	void mostrarMenu();
	void registrarPedido(LectorDB& lector, ListaProducto& listaProducto, vector<Pedido>& pedidos);
	void gestionarPlatos(ListaProducto& listaProducto);
	void modificarPrecio(ListaProducto& listaProducto);
	void agregarPlato(ListaProducto& listaProducto);
	void eliminarPlato(ListaProducto& listaProducto);
	void generarInformes(vector<Pedido>& pedidos, LectorDB& lector);
	void verHistorialPedidos(vector<Pedido>& pedidos);
	void verPlatosDemandados();
	void verHistorialClientes(LectorDB lector);
	void verPlatosDemandadosRecursivo(vector<string>& platos, int index);
	void verHistorialPedidosRecursivo(vector<Pedido>& pedidos, int index);
	void verHistorialClientesRecursivo(vector<Cliente>& clientes, int index);
};


void Menu::mostrarMenu() {  // Definición completa de la función
	LectorDB lector;
	ListaProducto listaProducto;
	vector<Pedido> pedidos;

	vector<Cliente> clientes = lector.leerClientes("dbClientes.txt");
	vector<Platos<string>> platos = lector.leerPlatos("dbPlatos.txt");
	vector<Bebidas<string>> bebidas = lector.leerBebidas("dbBebidas.txt");

	//leer por data set
	/*vector<Cliente> clientes = {
		Cliente(1, "Erick Maycol",21),
		Cliente(2, "Antony Pablo",20),
		Cliente(3, "Pedro Marmol",18),
		Cliente(4, "Pablo Mora",19)
	};

	vector<Plato<string>> platos = {
		Plato<string>(1, "lomo saltado",21.20),
		Plato<string>(2, "ceviche",20.00),
		Plato<string>(3, "caldo de gallina",15.00),
		Plato<string>(4, "aji de gallina",15.00),
		Plato<string>(5, "escabeche de pollo",18.50),
		Plato<string>(6, "pachamanca",25.80),
	};*/

	// Lambda para agregar plato a la lista de productos
	auto agregarPlatoLista = [&listaProducto](Platos<string>& plato) {
		listaProducto.agregarPlatoInicial(plato.getId(), plato.getNombre(), plato.getPrecio(), "Comida");
		};

	// Agregar todos los platos a la lista
	for (Platos<string> plato : platos) {
		agregarPlatoLista(plato);
	}

	// Lambda para agregar Bebidas a la lista de productos
	auto agregarBebidaLista = [&listaProducto](Bebidas<string>& bebida) {
		listaProducto.agregarBebidaInicial(bebida.getId(), bebida.getNombre(), bebida.getPrecio(), "Bebida");
		};

	for (Bebidas<string> bebida : bebidas) {
		agregarBebidaLista(bebida);
	}

	int opcion;
	int direccion = 1;

	int filas = 25;
	int columnas = 23;
	int matriz[25][23] = {
		{0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0,0,0,0,0,0,1,2,2,2,2,2,2,2,1,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,1,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0},
		{0,0,0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0},
		{0,0,0,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0},
		{0,0,0,1,2,2,2,1,1,2,2,2,2,2,1,1,2,2,1,0,0,0,0},
		{0,0,1,2,2,2,2,1,1,2,2,2,2,2,1,1,2,2,1,0,0,0,0},
		{0,0,1,2,2,2,2,2,2,2,1,1,1,2,2,2,2,2,2,1,0,0,0},
		{0,0,1,2,2,2,2,2,2,1,5,5,5,1,2,2,2,2,2,1,0,0,0},
		{0,0,1,2,2,2,2,2,1,1,1,1,1,1,1,2,2,2,2,1,0,0,0},
		{0,0,1,2,2,2,2,2,1,5,5,5,5,5,1,2,2,2,2,1,1,0,0},
		{0,1,2,2,2,2,2,2,2,1,1,1,1,1,2,2,2,2,2,1,2,1,0},
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,1},
		{1,2,2,2,2,1,2,2,2,2,2,2,1,1,1,2,2,2,2,1,2,2,1},
		{1,2,2,2,1,2,2,2,1,1,1,1,3,3,1,2,2,2,2,1,1,2,1},
		{1,2,2,2,1,1,1,1,3,3,3,3,3,3,1,2,2,2,2,1,0,1,1},
		{1,2,2,2,1,4,4,3,3,3,3,3,3,1,2,2,2,2,2,1,0,0,0},
		{1,1,2,2,1,1,1,3,3,3,3,1,1,2,2,2,2,2,2,1,0,0,0},
		{0,1,1,2,2,2,2,1,1,1,1,2,2,2,2,2,2,2,2,1,0,0,0},
		{0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0},
		{0,0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,0,0,0},
		{0,0,0,1,1,1,2,2,2,2,2,2,2,2,2,2,2,1,5,1,0,0,0},
		{0,0,0,1,5,5,1,2,2,2,2,2,2,2,2,1,1,5,5,1,0,0,0},
		{0,0,0,1,1,5,5,1,1,1,1,1,1,1,1,5,5,5,1,1,0,0,0},
		{0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0},
	};

	while(1) {
		Console::ForegroundColor = ConsoleColor::White;

		if (_kbhit())
		{
			char tecla = _getch();
			if (tecla == 72)
			{
				if (direccion == 1)
					direccion = 1;
				else
					direccion--;
			}
			if (tecla == 80)
			{
				if (direccion == 4)
					direccion = 4;
				else
					direccion++;
			}
			if (tecla == 13)
			{
				int cont = 0;
				switch (direccion) {
				case 1:
					while(cont < 10) {
						cont++;
						Console::SetCursorPosition(6, 25);
						cout << "Cargando...";
						_sleep(100);
					}
					cont = 0;
					Console::Clear();
					registrarPedido(lector, listaProducto, pedidos);
					Console::Clear();
					break;
				case 2:
					while (cont < 10) {
						cont++;
						Console::SetCursorPosition(6, 25);
						cout << "Cargando...";
						_sleep(100);
					}
					cont = 0;
					Console::Clear();
					gestionarPlatos(listaProducto);
					
					Console::Clear();
					break;
				case 3:
					while (cont < 10) {
						cont++;
						Console::SetCursorPosition(6, 25);
						cout << "Cargando...";
						_sleep(100);
					}
					cont = 0;
					Console::Clear();
					generarInformes(pedidos, lector);
					Console::Clear();
					break;
				case 4:
					while (cont < 10) {
						cont++;
						Console::SetCursorPosition(6, 25);
						cout << "Saliendo del sistema...";
						_sleep(100);
					}
					cont = 0;
					Console::Clear();
					getch();
					break;
				default:
					cout << "Opcion no valida." << endl;
				}
			}
		}
		if (direccion == 1)
		{
			Console::SetCursorPosition(10, 6 + 0);
			Console::ForegroundColor = ConsoleColor::White;
			Console::BackgroundColor = ConsoleColor::Black;
			cout << "---- RESTAURANTE PEPITO ----" << endl;
			Console::SetCursorPosition(10, 6 + 2);
			Console::ForegroundColor = ConsoleColor::Black;
			Console::BackgroundColor = ConsoleColor::DarkYellow;
			cout << "1. Registrar Pedido" << endl;
			Console::SetCursorPosition(10, 6 + 4);
			Console::ForegroundColor = ConsoleColor::White;
			Console::BackgroundColor = ConsoleColor::Black;
			cout << "2. Lista de Platos" << endl;
			Console::SetCursorPosition(10, 6 + 6);
			Console::ForegroundColor = ConsoleColor::White;
			Console::BackgroundColor = ConsoleColor::Black;
			cout << "3. Generar Informes" << endl;
			Console::SetCursorPosition(10, 6 + 8);
			Console::ForegroundColor = ConsoleColor::White;
			Console::BackgroundColor = ConsoleColor::Black;
			cout << "4. Salir" << endl;
			Console::SetCursorPosition(10, 20);
			Console::ForegroundColor = ConsoleColor::White;
			Console::BackgroundColor = ConsoleColor::Black;
			cout << "\"Cualquiera puede cocinar\"";
			Console::SetCursorPosition(24, 21);
			Console::ForegroundColor = ConsoleColor::White;
			Console::BackgroundColor = ConsoleColor::Black;
			cout << "Ratatouille";

		}
		if (direccion == 2)
		{
			Console::SetCursorPosition(10, 6 + 0);
			Console::ForegroundColor = ConsoleColor::White;
			Console::BackgroundColor = ConsoleColor::Black;
			cout << "---- RESTAURANTE PEPITO ----" << endl;
			Console::SetCursorPosition(10, 6 + 2);
			Console::ForegroundColor = ConsoleColor::White;
			Console::BackgroundColor = ConsoleColor::Black;
			cout << "1. Registrar Pedido" << endl;
			Console::SetCursorPosition(10, 6 + 4);
			Console::ForegroundColor = ConsoleColor::Black;
			Console::BackgroundColor = ConsoleColor::DarkYellow;
			cout << "2. Lista de Platos" << endl;
			Console::SetCursorPosition(10, 6 + 6);
			Console::ForegroundColor = ConsoleColor::White;
			Console::BackgroundColor = ConsoleColor::Black;
			cout << "3. Generar Informes" << endl;
			Console::SetCursorPosition(10, 6 + 8);
			Console::ForegroundColor = ConsoleColor::White;
			Console::BackgroundColor = ConsoleColor::Black;
			cout << "4. Salir" << endl;
			Console::SetCursorPosition(10, 20);
			Console::ForegroundColor = ConsoleColor::White;
			Console::BackgroundColor = ConsoleColor::Black;
			cout << "\"Cualquiera puede cocinar\"";
			Console::SetCursorPosition(24, 21);
			Console::ForegroundColor = ConsoleColor::White;
			Console::BackgroundColor = ConsoleColor::Black;
			cout << "Ratatouille";

		}
		if (direccion == 3)
		{
			Console::SetCursorPosition(10, 6 + 0);
			Console::ForegroundColor = ConsoleColor::White;
			Console::BackgroundColor = ConsoleColor::Black;
			cout << "---- RESTAURANTE PEPITO ----" << endl;
			Console::SetCursorPosition(10, 6 + 2);
			Console::ForegroundColor = ConsoleColor::White;
			Console::BackgroundColor = ConsoleColor::Black;
			cout << "1. Registrar Pedido" << endl;
			Console::SetCursorPosition(10, 6 + 4);
			Console::ForegroundColor = ConsoleColor::White;
			Console::BackgroundColor = ConsoleColor::Black;
			cout << "2. Lista de Platos" << endl;
			Console::SetCursorPosition(10, 6 + 6);
			Console::ForegroundColor = ConsoleColor::Black;
			Console::BackgroundColor = ConsoleColor::DarkYellow;
			cout << "3. Generar Informes" << endl;
			Console::SetCursorPosition(10, 6 + 8);
			Console::ForegroundColor = ConsoleColor::White;
			Console::BackgroundColor = ConsoleColor::Black;
			cout << "4. Salir" << endl;
			Console::SetCursorPosition(10, 20);
			Console::ForegroundColor = ConsoleColor::White;
			Console::BackgroundColor = ConsoleColor::Black;
			cout << "\"Cualquiera puede cocinar\"";
			Console::SetCursorPosition(24, 21);
			Console::ForegroundColor = ConsoleColor::White;
			Console::BackgroundColor = ConsoleColor::Black;
			cout << "Ratatouille";

		}
		if (direccion == 4)
		{
			Console::SetCursorPosition(10, 6 + 0);
			Console::ForegroundColor = ConsoleColor::White;
			Console::BackgroundColor = ConsoleColor::Black;
			cout << "---- RESTAURANTE PEPITO ----" << endl;
			Console::SetCursorPosition(10, 6 + 2);
			Console::ForegroundColor = ConsoleColor::White;
			Console::BackgroundColor = ConsoleColor::Black;
			cout << "1. Registrar Pedido" << endl;
			Console::SetCursorPosition(10, 6 + 4);
			Console::ForegroundColor = ConsoleColor::White;
			Console::BackgroundColor = ConsoleColor::Black;
			cout << "2. Lista de Platos" << endl;
			Console::SetCursorPosition(10, 6 + 6);
			Console::ForegroundColor = ConsoleColor::White;
			Console::BackgroundColor = ConsoleColor::Black;
			cout << "3. Generar Informes" << endl;
			Console::SetCursorPosition(10, 6 + 8);
			Console::ForegroundColor = ConsoleColor::Black;
			Console::BackgroundColor = ConsoleColor::DarkYellow;
			cout << "4. Salir" << endl;
			Console::SetCursorPosition(10, 20);
			Console::ForegroundColor = ConsoleColor::White;
			Console::BackgroundColor = ConsoleColor::Black;
			cout << "\"Cualquiera puede cocinar\"";
			Console::SetCursorPosition(24, 21);
			Console::ForegroundColor = ConsoleColor::White;
			Console::BackgroundColor = ConsoleColor::Black;
			cout << "Ratatouille";

		}
		int d = 60;
		for (int i = 0; i < filas; i++) {
			for (int j = 0; j < columnas; j++) {
				switch (matriz[i][j])
				{
				case 0:
					Console::ForegroundColor = ConsoleColor::Black;
					break;
				case 1:
					Console::ForegroundColor = ConsoleColor::Black;
					break;
				case 2:
					Console::ForegroundColor = ConsoleColor::DarkYellow;
					break;
				case 3:
					Console::ForegroundColor = ConsoleColor::Gray;
					break;
				case 4:
					Console::ForegroundColor = ConsoleColor::Cyan;
					break;
				case 5:
					Console::ForegroundColor = ConsoleColor::DarkRed;
					break;

				}
				Console::SetCursorPosition(d + j, 3 + i);
				cout << char(219) << char(219);
				d++;

			}
			d = 60;
			cout << endl;
		}
	} 
}

void Menu::registrarPedido(LectorDB& lector, ListaProducto& listaProducto, vector<Pedido>& pedidos) {
	cout << "\nRegistrar Pedido" << endl;

	string nombreCliente;
	cout << "Ingrese el nombre del cliente: ";
	cin.ignore();
	getline(cin, nombreCliente);

	// crear nuevo pedido
	Pedido nuevoPedido(pedidos.size() + 1, nombreCliente, new ListaProducto());

	// lambda para seleccionar producto
	auto seleccionarProductos = [&](const string& categoria) {
		char continuar;
		do {
			cout << "\n" << categoria << " disponibles:" << endl;
			listaProducto.mostrarProductosPorCategoria(categoria);

			int idProducto;
			cout << "Seleccionar " << categoria << " (ID): ";
			cin >> idProducto;


			nuevoPedido.agregarProductos(idProducto, &listaProducto, categoria);

			cout << "Desea agregar otro " << categoria << "? (s/n): ";
			cin >> continuar;
		} while (continuar == 's' || continuar == 'S');
		};

	// Selección de platos
	cout << "\n--- Selección de Platos ---" << endl;
	seleccionarProductos("Comida");

	// Selección de bebidas
	cout << "\n--- Selección de Bebidas ---" << endl;
	seleccionarProductos("Bebida");

	cout << "Fecha del pedido (dd/mm/aaaa): ";
	string fecha;
	cin >> fecha;
	nuevoPedido.fecha = fecha;

	// Calcular precio total
	float total = 0;

	// Recorremos la lista de productos en el pedido
	Producto* actual = nuevoPedido.productosPedidos->ini;

	while (actual != nullptr) {
		total += actual->precio; // Sumamos el precio de cada producto
		actual = actual->sig;    // Pasamos al siguiente producto
	}

	// Asignamos el total al pedido
	nuevoPedido.precioTotal = total;

	cout << "Total a Pagar: " << total << endl;
	cout << "Metodo de Pago (Efectivo/Tarjeta): ";
	string metodoPago;
	cin >> metodoPago;

	cout << "Pedido registrado correctamente!" << endl;
	pedidos.push_back(nuevoPedido);
}

void Menu::gestionarPlatos(ListaProducto& listaProducto) {
	cout << "\nLista de Platos" << endl;
	cout << "1. Ver Carta" << endl;
	cout << "2. Modificar Precio" << endl;
	cout << "3. Agregar Plato" << endl;
	cout << "4. Eliminar Plato" << endl;

	int opcion;
	cin >> opcion;

	switch (opcion) {
	case 1:
		listaProducto.mostrarProductoPlatos();
		break;
	case 2:
		modificarPrecio(listaProducto);
		break;
	case 3:
		agregarPlato(listaProducto);
		break;
	case 4:
		eliminarPlato(listaProducto);
		break;
	default:
		cout << "Opcion no valida." << endl;
	}
}


void Menu::modificarPrecio(ListaProducto& listaProducto) {
	cout << "Modificar Precio" << endl;
	int id;
	float nuevoPrecio;
	cout << "ID del Plato: ";
	cin >> id;
	cout << "Nuevo Precio: ";
	cin >> nuevoPrecio;

	//lambda 2 
	auto modificarPrecioLambda = [&listaProducto](int id, float nuevoPrecio) {
		Producto* producto = listaProducto.obtenerProductoComidas(id);

		if (producto != nullptr) {
			producto->precio = nuevoPrecio;
			cout << "Precio modificado correctamente." << endl;
		}
		else {
			cout << "Plato no encontrado." << endl;
		}
		};
	modificarPrecioLambda(id, nuevoPrecio);
}

void Menu::agregarPlato(ListaProducto& listaProducto) {
	cout << "Agregar Plato" << endl;
	int id;
	string nombre;
	float precio;
	string categoria;

	cout << "ID del Plato: ";
	cin >> id;
	cout << "Nombre del Plato: ";
	cin.ignore();
	getline(cin, nombre);
	cout << "Precio: ";
	cin >> precio;
	cout << "Categoria: ";
	cin >> categoria;

	listaProducto.agregarPlatoInicial(id, nombre, precio, categoria);
	cout << "Plato agregado correctamente." << endl;
};

void Menu::eliminarPlato(ListaProducto& listaProducto) {
	cout << "Eliminar Plato" << endl;
	int id;
	cout << "ID del Plato: ";
	cin >> id;

	// Lambda 3
	auto eliminarPlatoLambda = [&listaProducto](int id) {
		Producto* producto = listaProducto.obtenerProductoComidas(id);
		if (producto != nullptr) {
			listaProducto.eliminarProducto(id);
			cout << "Plato eliminado correctamente." << endl;
		}
		else {
			cout << "Plato no encontrado." << endl;
		}
		};
	eliminarPlatoLambda(id);

};


void Menu::generarInformes(vector<Pedido>& pedidos, LectorDB& lector) {
	cout << "\nGenerar Informes" << endl;
	cout << "1. Historial de Pedidos" << endl;
	cout << "2. Platos mas Demandados" << endl;
	cout << "3. Historial de Clientes" << endl;

	int opcion;
	cin >> opcion;


	switch (opcion) {
	case 1:
		verHistorialPedidos(pedidos);
		getch();
		break;
	case 2:
		verPlatosDemandados();
		getch();
		break;
	case 3:
		verHistorialClientes(lector);
		getch();
		break;
	default:
		cout << "Opcion no valida." << endl;
	}
}


//recursividad 1
void Menu::verHistorialPedidosRecursivo(vector<Pedido>& pedidos, int index) {
	if (index >= pedidos.size()) { //caso cuando llegamos al final de la lista
		return;
	}
	pedidos[index].mostrarPedido(); //mostramos el pedido actual
	verHistorialPedidosRecursivo(pedidos, index + 1); //llamamos a la recursiva para el siguiente pedido
};

void Menu::verHistorialPedidos(vector<Pedido>& pedidos) {
	cout << "\nHistorial de Pedidos" << endl;
	if (pedidos.empty()) {
		cout << "No hay pedidos registrados." << endl;
		return;
	}
	verHistorialPedidosRecursivo(pedidos, 0); //comenzamos con el primer pedido
};


//recursividad 2
void Menu::verPlatosDemandadosRecursivo(vector<string>& platos, int index) {
	if (index >= platos.size()) { //caso cuando llegamos al final de la lista
		return;
	}

	cout << index + 1 << ". " << platos[index] << endl; //mostrar el plato actual;
	verPlatosDemandadosRecursivo(platos, index + 1); //llamamos a la recursiva para el siguiente platoDemandado;
}

void Menu::verPlatosDemandados() {
	cout << "\nPlatos mas demandados: " << endl;
	vector<string> platos = { "Pollo a la braza", "Arroz con Pollo", "Broaster" };
	verPlatosDemandadosRecursivo(platos, 0);

}

void Menu::verHistorialClientesRecursivo(vector<Cliente>& clientes, int index) {
	if (index >= clientes.size()) { //caso cuando llegamos al final de la lista
		return;
	}
	cout << "ID: " << clientes[index].getId() << ", Nombre: " << clientes[index].getNombre() << ", Edad: " << clientes[index].getEdad() << endl; //obtenemos los datos del cliente
	verHistorialClientesRecursivo(clientes, index + 1); // llamada recursiva para el siguiente cliente;
}

void Menu::verHistorialClientes(LectorDB lector) {
	cout << "\nHistorial de Clientes" << endl;
	vector<Cliente> clientes = lector.leerClientes("dbClientes.txt");

	if (clientes.empty()) {
		cout << "No hay clientes registrados." << endl;
		return;
	}
	verHistorialClientesRecursivo(clientes, 0);  //comenzamos con el primer cliente
}