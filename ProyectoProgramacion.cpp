#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

// Declarar matrices
vector<vector<string>> matrizOriginal;
vector<vector<string>> matrizPrestamistas;


// Función para leer el archivo CSV y cargar los datos en la matriz
void leerCSV() {
    ifstream archivo("biblioteca.csv");
    if (archivo.is_open()) {
        string linea;
        getline(archivo, linea); // Leer y descartar la primera línea (cabecera)
        while (getline(archivo, linea)) {
            stringstream sstream(linea);
            vector<string> obra;
            string dato;
            while (getline(sstream, dato, ',')) {
                obra.push_back(dato);
            }
            matrizOriginal.push_back(obra);
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo CSV. Se creará uno nuevo cuando se exporten los datos.\n";
    }
}

// Función para agregar obra a matriz original
void agregarObraOriginal() {
    setlocale(LC_ALL,"spanish");
    cout << "\n";
    cout << "__________________________________________\n";
    string titulo, autor, editorial, tipoObra, tipoAutor, fechaPublicacion, genero, estado, link, Orcid;
    cout << "Ingrese el titulo de la obra: ";
    getline(cin, titulo);
    cout << "Ingrese el nombre del autor: ";
    getline(cin, autor);
    cout << "Ingrese el nombre de la editorial: ";
    getline(cin, editorial);
    cout << "Especifique el tipo de obra (Revista,Libro,Publicacion,etc): ";
    getline(cin, tipoObra);
    cout << "Ingrese tipo de autor (Estudiante o Profesor): ";
    getline(cin, tipoAutor);
    cout << "Ingrese fecha de publicacion (dd/mm/aaaa):";
    getline(cin, fechaPublicacion);
    cout << "Ingrese el genero o campo de la obra: ";
    getline(cin, genero);
    cout << "Estado de la Obra (default = Stock)\n";
    if (estado.empty()) {
        estado = "Stock";
    }
    cout << "Ingrese el codigo ORCID (xxxx-xxxx): ";
    getline(cin, Orcid);
    if (!link.empty()) {
        link = "https://orcid.org/0000-0001/";
    } else {
        link = "https://orcid.org/0000-0001/" + Orcid;
    }
    matrizOriginal.push_back({titulo, autor, editorial, tipoObra, tipoAutor, fechaPublicacion, genero, estado, link});
    cout << "Obra agregada con exito.\n";
    cout << "__________________________________________\n";
    cout << "\n";
}

// Función para editar obra de matriz original
void editarObraOriginal() {
    setlocale(LC_ALL, "spanish");
    cout << "\n";
    cout << "__________________________________________\n";
    string titulo;
    cout << "Ingrese el titulo de la obra a editar: ";
    getline(cin, titulo);
    cout << "En caso de que el campo no requiera edicion presione enter (se quedara guardado el campo ingresado anteriormente)\n";

    // Buscar la obra en la matriz
    for (auto& obra : matrizOriginal) {
        if (obra[0] == titulo) {
            cout << "Obra encontrada. Edite los campos que desee:\n";
            string autor, editorial, tipoObra, tipoAutor, fechaPublicacion, genero, estado, link, Orcid;
            
            cout << "Ingrese el titulo de la obra (actual: " << obra[0] << "): ";
            getline(cin, titulo);
            if (!titulo.empty()) {
                obra[0] = titulo;
            }

            cout << "Ingrese el nombre del autor (actual: " << obra[1] << "): ";
            getline(cin, autor);
            if (!autor.empty()) {
                obra[1] = autor;
            }

            cout << "Ingrese el nombre de la editorial (actual: " << obra[2] << "): ";
            getline(cin, editorial);
            if (!editorial.empty()) {
                obra[2] = editorial;
            }

            cout << "Especifique el tipo de obra (actual: " << obra[3] << "): ";
            getline(cin, tipoObra);
            if (!tipoObra.empty()) {
                obra[3] = tipoObra;
            }

            cout << "Ingrese tipo de autor (actual: " << obra[4] << "): ";
            getline(cin, tipoAutor);
            if (!tipoAutor.empty()) {
                obra[4] = tipoAutor;
            }

            cout << "Ingrese fecha de publicacion (actual: " << obra[5] << "): ";
            getline(cin, fechaPublicacion);
            if (!fechaPublicacion.empty()) {
                obra[5] = fechaPublicacion;
            }

            cout << "Ingrese el genero o campo de la obra (actual: " << obra[6] << "): ";
            getline(cin, genero);
            if (!genero.empty()) {
                obra[6] = genero;
            }

            cout << "Ingrese el codigo ORCID (actual: " << obra[8] << "): https://orcid.org/0000-0001/";
            getline(cin, Orcid);
            if (!link.empty()) {
                obra[8] = link;
            } else {
			    obra[8] =link = "https://orcid.org/0000-0001/" + Orcid;
		    }

            cout << "Obra editada con exito.\n";
            return;
        }
    }
    cout << "No se encontro la obra con el titulo ingresado.\n";
    cout << "__________________________________________\n";
    cout << "\n";
}

// Función para realizar un préstamo
void realizarPrestamo() {
    setlocale(LC_ALL, "spanish");
    string nombreUsuario, identificacion, titulo;
    cout << "Ingrese el nombre del usuario: ";
    getline(cin, nombreUsuario);
    cout << "Ingrese su identificacion: ";
    getline(cin, identificacion);
    cout << "Ingrese el titulo del libro que desea solicitar: ";
    getline(cin, titulo);

    // Buscar la obra en la matriz y cambiar su estado a "Prestada"
    for (auto& obra : matrizOriginal) {
        if (obra[0] == titulo) {
            if (obra[7] == "Stock") {
                obra[7] = "Prestada";
                matrizPrestamistas.push_back({titulo, nombreUsuario, identificacion});
                cout << "Préstamo realizado con éxito. El estado del libro ha cambiado a 'Prestada'.\n";
            } else {
                cout << "El libro ya está prestado.\n";
            }
            return;
        }
    }
    cout << "No se encontró el libro con el título ingresado.\n";
}

// Función para devolver un préstamo
void devolverPrestamo() {
    setlocale(LC_ALL, "spanish");
    string nombreUsuario, identificacion, titulo;
    cout << "Ingrese el nombre del usuario: ";
    getline(cin, nombreUsuario);
    cout << "Ingrese su identificacion: ";
    getline(cin, identificacion);
    cout << "Ingrese el titulo del libro que desea devolver: ";
    getline(cin, titulo);

    // Buscar la obra en la matriz y cambiar su estado a "Stock"
    for (auto& obra : matrizOriginal) {
        if (obra[0] == titulo && obra[7] == "Prestada") {
            auto it = find_if(matrizPrestamistas.begin(), matrizPrestamistas.end(),
                              [&](const vector<string>& prestamista) {
                                  return prestamista[0] == titulo && prestamista[1] == nombreUsuario && prestamista[2] == identificacion;
                              });
            if (it != matrizPrestamistas.end()) {
                matrizPrestamistas.erase(it); // Eliminar registro de prestamista
                obra[7] = "Stock";
                cout << "Devolución realizada con éxito. El estado del libro ha cambiado a 'Stock'.\n";
            } else {
                cout << "No se encontró un préstamo que coincida con los datos proporcionados.\n";
            }
            return;
        }
    }
    cout << "No se encontró el libro con el título ingresado o el libro no está prestado.\n";
}

// Función para visualizar los prestamistas
void visualizarPrestamistas() {
    setlocale(LC_ALL, "spanish");
    cout << "\n" <<endl;
    cout << "==============================================================================================\n";
    cout << "| " << left << setw(28) << "Titulo"
         << "| " << setw(28) << "Nombre del Usuario"
         << "| " << setw(28) << "Identificacion del Usuario" << "|\n";
    cout << "==============================================================================================\n";

    // Imprimir cada fila de la matriz
    for (const auto& prestamista : matrizPrestamistas) {
        cout << "| " << left << setw(28) << prestamista[0]
             << "| " << setw(28) << prestamista[1]
             << "| " << setw(28) << prestamista[2] << "|\n";
    }

    cout << "==============================================================================================\n";
    cout << "\n";
}


// Función para gestionar préstamos
void gestionarPrestamos() {
    setlocale(LC_ALL, "spanish");
    cout << "\n===========================================";
    cout << "\n";
    cout << "\tBiblioteca de Obras\n";
    cout << "===========================================\n";
    char opcion;
    
    // Solicitar una opción válida
    do {
        cout << "1. Realizar prestamo\n";
        cout << "2. Devolver prestamo\n";
        cout << "3. Visualizar prestamistas\n";
        cout << "Ingrese su opcion (1, 2 o 3): ";
        cin >> opcion;
        cin.ignore();

        if (opcion != '1' && opcion != '2' && opcion != '3') {
            cout << "\nOpcion invalida. Intente nuevamente.";
            cout << "\n===========================================";
    		cout << "\n";
        }
    } while (opcion != '1' && opcion != '2' && opcion != '3');

    switch (opcion) {
        case '1':
            realizarPrestamo();deley 
            break;
        case '2':
            devolverPrestamo();
            break;
        case '3':
            visualizarPrestamistas();
            break;
    }

    cout << "__________________________________________\n";
    cout << "\n";
}



// Función para mostrar matriz original
void mostrarMatrizOriginal() {
    setlocale(LC_ALL, "spanish");
	
    cout << "\n" << endl;

    // Imprimir encabezados
    cout << "====================================================================================================================================================\n";
    cout << "| " << left << setw(15) << "Titulo"
         << "| " << setw(13) << "Autor"
         << "| " << setw(13) << "Editorial"
         << "| " << setw(13) << "Tipo de Obra"
         << "| " << setw(13) << "Tipo de Autor"
         << "| " << setw(21) << "Fecha de Publicacion"
         << "| " << setw(13) << "Genero - Campo"
         << "| " << setw(13) << "Estado"
         << "| " << setw(13) << "CODIGO ORCID" << "|\n";
    cout << "====================================================================================================================================================\n";

    // Imprimir cada fila de la matriz
    for (const auto& obra : matrizOriginal) {
        string link = obra[8];
        if (link.find("https://orcid.org/0000-0001/") == 0) {
            link.replace(0, 24, ""); // Eliminar el prefijo "https://orcid.org/0000-0001/"
        }
        cout << "| " << left << setw(15) << obra[0]
             << "| " << setw(13) << obra[1]
             << "| " << setw(13) << obra[2]
             << "| " << setw(13) << obra[3]
             << "| " << setw(13) << obra[4]
             << "| " << setw(21) << obra[5]
             << "| " << setw(13) << obra[6]
             << "| " << setw(13) << obra[7]
             << "| " << setw(13) << obra[8] << "|\n";
    }

    cout << "====================================================================================================================================================\n";
    cout << "\n";
}

// Función para buscar obra
void buscarObra() {
    setlocale(LC_ALL,"spanish");
    cout << "\n";
    cout << "__________________________________________\n";
    string titulo;
    cout << "Ingrese titulo de la obra a buscar: ";
    getline(cin, titulo);
    bool encontrado = false;
    for (const auto& obra : matrizOriginal) {
        if (obra[0] == titulo) {
            cout << "Obra encontrada en la matriz original:\n";
            cout << "Titulo: " << obra[0] << "\n";
            cout << "Autor: " << obra[1] << "\n";
            cout << "Editorial: " << obra[2] << "\n";
            cout << "Tipo de obra: " << obra[3] << "\n";
            cout << "Tipo de autor: " << obra[4] << "\n";
            cout << "Fecha de publicacion: " << obra[5] << "\n";
            cout << "Genero - Campo: " << obra[6] << "\n";
            cout << "Estado: " << obra[7] << "\n";
            string link = obra[8];
            if (link.find("https://orcid.org/0000-0001/") == 0) {
                link.replace(0, 24, ""); // Eliminar el prefijo "https://orcid.org/0000-0001/"
            }
            cout << "Link: https://orcid.org/0000-0001/" << link << "\n\n";
            cout << "__________________________________________\n";
            cout << "\n";
            encontrado = true;
            break;
        }
    }
    if (!encontrado) {
    	cout << "\n";
    	cout << "__________________________________________\n";
        cout << "Obra no encontrada.\n";
        cout << "__________________________________________\n";
        cout << "\n";
    }
}

// Función para eliminar obra de matrices
void eliminarObra() {
    setlocale(LC_ALL,"spanish");
    cout << "\n";
    cout << "__________________________________________\n";
    string titulo;
    cout << "Ingrese titulo de la obra a eliminar: ";
    getline(cin, titulo);
    bool eliminado = false;
    for (auto it = matrizOriginal.begin(); it != matrizOriginal.end(); ++it) {
        if (it->at(0) == titulo) {
            string link = it->at(8);
            if (link.find("https://orcid.org/0000-0001/") == 0) {
                link.replace(0, 24, ""); // Eliminar el prefijo "https://orcid.org/0000-0001/"
            }
            cout << "\n";
            cout << "__________________________________________\n";
            cout << "Obra eliminada de la matriz original:\n";
            cout << "Titulo: " << it->at(0) << "\n";
            cout << "Autor: " << it->at(1) << "\n";
            cout << "Editorial: " << it->at(2) << "\n";
            cout << "Tipo de obra: " << it->at(3) << "\n";
            cout << "Tipo de autor: " << it->at(4) << "\n";
            cout << "Fecha de publicacion: " << it->at(5) << "\n";
            cout << "Genero: " << it->at(6) << "\n";
            cout << "Estado: " << it->at(7) << "\n";
            cout << "Link: https://orcid.org/0000-0001/" << link << "\n\n";
            cout << "__________________________________________\n";
            cout << "\n";
            matrizOriginal.erase(it);
            eliminado = true;
            break;
        }
    }
    if (!eliminado) {
    	cout << "\n";
    	cout << "__________________________________________\n";
        cout << "Obra no encontrada.\n";
        cout << "__________________________________________\n";
        cout << "\n";
    }
    cout << "__________________________________________\n";
    cout << "\n";
}

// Función para exportar matrices a CSV
void exportarCSV() {
    setlocale(LC_ALL,"spanish");
    ofstream archivo("biblioteca.csv");
    if (archivo.is_open()) {
        archivo << "Titulo,Autor,Editorial,Tipo de Obra,Tipo de Autor,Fecha de Publicacion,Genero,Estado,Link\n";
        for (const auto& obra : matrizOriginal) {
            archivo << obra[0] << "," << obra[1] << "," << obra[2] << "," << obra[3] << "," << obra[4] << "," << obra[5] << "," << obra[6] << "," << obra[7] << "," << obra[8] << "\n";
        }
        archivo.close();
        cout << "\n";
        cout << "__________________________________________\n";
        cout << "Archivo CSV generado con exito.\n";
        cout << "__________________________________________\n";
        cout << "\n";
    } else {
    	cout << "\n";
    	cout << "__________________________________________\n";
        cout << "Error al generar archivo CSV.\n";
        cout << "__________________________________________\n";
        cout << "\n";
    }
}

int main() {
	setlocale(LC_ALL, "es_ES.UTF-8");
	
	 // Leer el archivo CSV al iniciar
    leerCSV();
    
    int opcion;
    do {
    	cout << "\n===========================================";
    	cout << "\n";
        cout << "\tBiblioteca de Obras\n";
        cout << "===========================================\n";
        cout << "1. Agregar Obra \n";
        cout << "2. Editar Obra \n";
        cout << "3. Gestionar Prestamos \n";
        cout << "4. Mostrar Obras \n";
        cout << "5. Buscar Obra \n";
        cout << "6. Eliminar Obra \n";
        cout << "7. Exportar matrices a CSV \n";
        cout << "8. Salir \n";
        cout << "Ingrese opcion: ";

        // Verificación de entrada válida
        while (!(cin >> opcion)) {
            cout << "Entrada invalida. \nPor favor ingrese un numero: ";
            cin.clear(); // Limpia el estado de error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descarta la entrada no válida
        }

        cout << "===========================================\n";
        cin.ignore(); // Ignorar el salto de línea
        switch (opcion) {
            case 1:
                agregarObraOriginal();
                break;
            case 2:
                editarObraOriginal();
                break;
            case 3:
                gestionarPrestamos();
                break;
            case 4:
                mostrarMatrizOriginal();
                break;
            case 5:
                buscarObra();
                break;
            case 6:
                eliminarObra();
                break;
            case 7:
                exportarCSV();
                break;
            case 8:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opción inválida. Intente nuevamente.\n";
        }
    } while (opcion != 8);

    return 0;
}