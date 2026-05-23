#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

struct Cancion {
    string nombre;
    string artista;
    string duracion;
};

struct Nodo {
    Cancion cancion;
    Nodo* siguiente;
    Nodo* anterior;
};

Nodo* primero = nullptr;

void agregarCancion() {
    Nodo* nuevo = new Nodo;

    cin.ignore();

    cout << "\nIngrese el nombre de la cancion: ";
    getline(cin, nuevo->cancion.nombre);

    cout << "Ingrese el artista: ";
    getline(cin, nuevo->cancion.artista);

    cout << "Ingrese la duracion: ";
    getline(cin, nuevo->cancion.duracion);

    if (primero == nullptr) {
        primero = nuevo;
        nuevo->siguiente = primero;
        nuevo->anterior = primero;
    } else {
        Nodo* ultimo = primero->anterior;

        ultimo->siguiente = nuevo;
        nuevo->anterior = ultimo;
        nuevo->siguiente = primero;
        primero->anterior = nuevo;
    }

    cout << "\nCancion agregada correctamente.\n";
}

void mostrarLista() {
    if (primero == nullptr) {
        cout << "\nNo hay canciones registradas.\n";
        return;
    }

    Nodo* actual = primero;
    int contador = 1;

    cout << "\n===== LISTA COMPLETA DE CANCIONES =====\n";

    do {
        cout << "\nCancion #" << contador << endl;
        cout << "Nombre: " << actual->cancion.nombre << endl;
        cout << "Artista: " << actual->cancion.artista << endl;
        cout << "Duracion: " << actual->cancion.duracion << endl;

        actual = actual->siguiente;
        contador++;
    } while (actual != primero);
}

void mostrarCancionActual(Nodo* actual) {
    system("cls");

    cout << "===== REPRODUCTOR DE MUSICA =====\n";
    cout << "\nReproduciendo:\n";
    cout << "Cancion: " << actual->cancion.nombre << endl;
    cout << "Artista: " << actual->cancion.artista << endl;
    cout << "Duracion: " << actual->cancion.duracion << endl;

    cout << "\nControles:\n";
    cout << "Flecha derecha  -> Siguiente cancion\n";
    cout << "Flecha izquierda -> Cancion anterior\n";
    cout << "ESC              -> Regresar al menu\n";
}

void reproducirPlaylist() {
    if (primero == nullptr) {
        cout << "\nNo hay canciones para reproducir.\n";
        return;
    }

    Nodo* actual = primero;
    mostrarCancionActual(actual);

    int tecla;

    do {
        tecla = getch();

        if (tecla == 224) {
            tecla = getch();

            if (tecla == 77) {
                actual = actual->siguiente;
                mostrarCancionActual(actual);
            } else if (tecla == 75) {
                actual = actual->anterior;
                mostrarCancionActual(actual);
            }
        }

    } while (tecla != 27);
}

void liberarMemoria() {
    if (primero == nullptr) {
        return;
    }

    Nodo* actual = primero->siguiente;

    while (actual != primero) {
        Nodo* temp = actual;
        actual = actual->siguiente;
        delete temp;
    }

    delete primero;
    primero = nullptr;
}

int main() {
    int opcion;

    do {
        cout << "\n===== MENU PRINCIPAL =====\n";
        cout << "1. Agregar cancion\n";
        cout << "2. Mostrar lista completa\n";
        cout << "3. Reproducir playlist\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                agregarCancion();
                break;

            case 2:
                mostrarLista();
                break;

            case 3:
                reproducirPlaylist();
                system("cls");
                break;

            case 4:
                liberarMemoria();
                cout << "\nSaliendo del programa...\n";
                break;

            default:
                cout << "\nOpcion invalida. Intente nuevamente.\n";
        }

    } while (opcion != 4);

    return 0;
}