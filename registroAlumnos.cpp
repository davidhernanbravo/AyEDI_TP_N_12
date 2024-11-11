#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_ALUMNOS = 100;

typedef struct 
    {
        int id;
        string nombre;
        string domicilio;

    } tAlumno;

typedef struct 
    {
        tAlumno alumnos[MAX_ALUMNOS];
        int contador;
        
    } tListaAlumnos;

// Sobrecarga de operadores
bool operator>(const tAlumno &opIzq, const tAlumno &opDer) 
    {
        return opIzq.nombre > opDer.nombre;
    }

bool operator<(const tAlumno &opIzq, const tAlumno &opDer) 
    {
        return opIzq.nombre < opDer.nombre;
    }

void insertarAlumno(tListaAlumnos &lista, const tAlumno &alumno);
void eliminarAlumno(tListaAlumnos &lista, int id);
int buscarAlumno(const tListaAlumnos &lista, const string &nombre);
void mostrarAlumno(const tListaAlumnos &lista, int indice);
void mostrarListaAlumnos(const tListaAlumnos &lista);
void ordenarListaAlumnos(tListaAlumnos &lista, bool ascendente);
void cargarDesdeArchivo(tListaAlumnos &lista);
void guardarEnArchivo(const tListaAlumnos &lista);
void mostrarMenu(tListaAlumnos &lista);

int main() 
    {
        tListaAlumnos lista;
        lista.contador = 0;

        cargarDesdeArchivo(lista);
        mostrarMenu(lista);

        return 0;
    }

void mostrarMenu(tListaAlumnos &lista) 
    {
        int opcion;
        do {
            cout << endl << "REGISTRO DE ALUMNOS:" << endl << endl;

            cout << "1. Insertar Alumno" << endl;
            cout << "2. Eliminar Alumno" << endl;
            cout << "3. Buscar Alumno" << endl;
            cout << "4. Mostrar un Alumno" << endl;
            cout << "5. Mostrar Listado de Alumnos" << endl;
            cout << "6. Ordenar Listado" << endl;
            cout << "0. Salir" << endl << endl;
            cout << "Seleccione una opcion: ";
            cin >> opcion;
            cin.ignore();
            cout << endl;

            tAlumno alumno;
            int id, indice;
            string nombre;

            switch(opcion) 
            {
                case 1:
                    cout << endl << "Ingrese ID: ";
                    cin >> alumno.id;
                    cin.ignore();

                    cout << endl << "Ingrese Nombre: ";
                    getline(cin, alumno.nombre);

                    cout << endl << "Ingrese Domicilio: ";
                    getline(cin, alumno.domicilio);

                    insertarAlumno(lista, alumno);
                    guardarEnArchivo(lista);

                    break;

                case 2:
                    cout << endl << "Ingrese ID del alumno a eliminar: ";
                    cin >> id;

                    eliminarAlumno(lista, id);
                    guardarEnArchivo(lista);

                    break;

                case 3:
                    cout << endl << "Ingrese Nombre a buscar: ";
                    getline(cin, nombre);

                    indice = buscarAlumno(lista, nombre);

                    if (indice != -1) 
                        {
                            cout << endl << "Alumno encontrado" << endl;
                            mostrarAlumno(lista, indice);

                        } else 
                            {
                                cout << endl << "Alumno no encontrado." << endl;
                            }
                    break;

                case 4:
                    cout << endl << "Ingrese Nombre a mostrar: ";
                    getline(cin, nombre);

                    indice = buscarAlumno(lista, nombre);

                    if (indice != -1) 
                        {
                            mostrarAlumno(lista, indice);

                        } else 
                            {
                                cout << endl << "Alumno no encontrado." << endl;
                            }

                    break;

                case 5:
                    mostrarListaAlumnos(lista);

                    break;

                case 6:
                    bool ascendente;
                    cout << endl << "Ordenar Ascendente (1) o Descendente (0): ";
                    cin >> ascendente;

                    ordenarListaAlumnos(lista, ascendente);
                    mostrarListaAlumnos(lista);

                    break;
            }
        } while (opcion != 0);
    }

void insertarAlumno(tListaAlumnos &lista, const tAlumno &alumno) 
    {
        if (lista.contador < MAX_ALUMNOS) 
            {
                lista.alumnos[lista.contador++] = alumno;
            } else 
                {
                    cout << endl << "Lista llena. No se puede insertar más alumnos." << endl;
                }
    }

void eliminarAlumno(tListaAlumnos &lista, int id) 
    {
        bool encontrado = false;
        for (int i = 0; i < lista.contador; i++) 
            {
                if (lista.alumnos[i].id == id) 
                        {
                            for (int j = i; j < lista.contador - 1; j++) 
                                {
                                    lista.alumnos[j] = lista.alumnos[j + 1];
                                }
                            
                            lista.contador--;
                            encontrado = true;
                            break;
                        }
            }
        if (!encontrado) 
            {
                cout << endl << "Alumno con ID " << id << " no encontrado." << endl;
            }
    }

int buscarAlumno(const tListaAlumnos &lista, const string &nombre) 
    {
        for (int i = 0; i < lista.contador; i++) 
            {
                if (lista.alumnos[i].nombre == nombre) 
                    {
                        return i;
                    }

            }

        return -1;
    }

void mostrarAlumno(const tListaAlumnos &lista, int indice) 
    {
        cout << "ID: " << lista.alumnos[indice].id << endl;
        cout << "Nombre: " << lista.alumnos[indice].nombre << endl;
        cout << "Domicilio: " << lista.alumnos[indice].domicilio << endl << endl;
    }

void mostrarListaAlumnos(const tListaAlumnos &lista) 
    {
        for (int i = 0; i < lista.contador; i++) 
            {
                mostrarAlumno(lista, i);
            }
    }

void ordenarListaAlumnos(tListaAlumnos &lista, bool ascendente) 
    {
        for (int i = 0; i < lista.contador - 1; i++) 
            {
                for (int j = i + 1; j < lista.contador; j++) 
                    {
                        if ((ascendente && lista.alumnos[i] > lista.alumnos[j]) || (!ascendente && lista.alumnos[i] < lista.alumnos[j])) 
                            {
                                tAlumno temp = lista.alumnos[i];
                                lista.alumnos[i] = lista.alumnos[j];
                                lista.alumnos[j] = temp;
                            }
                    }
            }
    }

void cargarDesdeArchivo(tListaAlumnos &lista) 
    {
        ifstream archivo("Alumnos.txt");
        if (archivo.is_open()) 
            {
                lista.contador = 0;
                while (archivo >> lista.alumnos[lista.contador].id) 
                    {
                        archivo.ignore();
                        getline(archivo, lista.alumnos[lista.contador].nombre);
                        getline(archivo, lista.alumnos[lista.contador].domicilio);
                        lista.contador++;
                        if (lista.contador >= MAX_ALUMNOS) break;
                    }

                archivo.close();
            }
    }

void guardarEnArchivo(const tListaAlumnos &lista) 
    {
        ofstream archivo("Alumnos.txt");

        for (int i = 0; i < lista.contador; i++) 
            {
                archivo << lista.alumnos[i].id << endl;
                archivo << lista.alumnos[i].nombre << endl;
                archivo << lista.alumnos[i].domicilio << endl;
            }

        archivo.close();
    }