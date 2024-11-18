#pragma once
#include <vector>
#include "ListaProducto.h"


class Pedido {
public:
    int id;
    string cliente;
    ListaProducto* productosPedidos;
    string fecha;
    double precioTotal;
    Pedido* sig;

    Pedido(int id, string cliente, ListaProducto* productosPedidos = nullptr, string fecha = "", double precioTotal = 0, Pedido* sig = nullptr) : id(id), cliente(cliente), productosPedidos(productosPedidos), fecha(fecha), precioTotal(precioTotal), sig(sig) {};

    void mostrarPedido();
    void agregarProductos(int id, ListaProducto* productosLista, const string& categoriaEsperada);
    void ordenarPedidos(vector<Pedido>& pedido);
};


void Pedido::mostrarPedido() {
    cout << "ID: " << id << endl;
    cout << "Cliente: " << cliente << endl;
    if (productosPedidos != nullptr) {
        productosPedidos->mostrarProductoPlatos();
        productosPedidos->mostrarProductoBebidas();
    }
    cout << "Fecha: " << fecha << endl;
    cout << "Precio total: " << precioTotal << endl;
}

void Pedido::agregarProductos(int id, ListaProducto* productosLista, const string& categoria) {
    Producto* nuevo = nullptr;
    if (categoria == "Comida") {
        nuevo = productosLista->obtenerProductoComidas(id);
    }
    else if (categoria == "Bebida") {
        nuevo = productosLista->obtenerProductoBebidas(id);
    }

    if (nuevo != nullptr) {
        cout << "Producto encontrado: " << nuevo->nombre << " (Precio: " << nuevo->precio << ")" << endl;

        if (nuevo->categoria == "Comida") {
            productosPedidos->agregarPlatoInicial(nuevo->id, nuevo->nombre, nuevo->precio, nuevo->categoria);
        }
        else if (nuevo->categoria == "Bebida") {
            productosPedidos->agregarBebidaInicial(nuevo->id, nuevo->nombre, nuevo->precio, nuevo->categoria);
        }

        //sumamos el precio del nuevo producto al precio total del pedido
        precioTotal += nuevo->precio;
        cout << "Total acumulado: " << precioTotal << endl;
    }
    else {
        cout << "Producto con ID " << id << " no encontrado o no pertenece a la categor�a esperada." << endl;
    }
}


// Funci�n auxiliar para fusionar dos subarreglos
void merge(Pedido** arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Pedido** L = new Pedido * [n1];
    Pedido** R = new Pedido * [n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i]->fecha <= R[j]->fecha) { // Comparar por fecha
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}


// Funci�n de ordenamiento por Merge Sort
void mergeSort(Pedido** arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}


void Pedido::ordenarPedidos(vector<Pedido>& pedidos) {
    int n = pedidos.size();

    //si la lista de pedidos est� vacia o tiene un solo elemento, no hay que ordenar
    if (n <= 1) return;

    Pedido** arr = new Pedido * [n];
    for (int i = 0; i < n; i++) {
        arr[i] = &pedidos[i]; //Guardar la direcci�n de cada pedido
    }

    //Ordenar usando Merge Sort
    mergeSort(arr, 0, n - 1);

    //reconstruir el vector de pedidos en orden 
    for (int i = 0; i < n; i++) {
        pedidos[i] = *arr[i];
    }

    delete[]arr; //liberar memoria

};