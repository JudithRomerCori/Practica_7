// Materia: Programación I, Paralelo 1

// Autor: Judith Marisol Romero Cori

// Fecha creación: 19/11/2023

// Fecha modificación: 22/11/2023

// Número de ejericio: 1

// Problema planteado:Escribe un programa que tenga un menú de tres opciones:

//·	Ingreso de datos de los equipo de la LPFB.
//·	Ingreso los resultados de los partidos.
//·	Reporte de la tabla de posiciones
//·	Salir
//La primera opción debe ingresar los datos de los nombres de los equipos de la ligade acuerdo con la siguiente estructura y estos sean almacenados en un archivo binario llamado “EquiposLPFB.bin”, se debe considerar en no duplicar los equipos de futbol por el Nombre del Equipo

//La segunda opción debe ingresar los resultados de los partidos, que debe almacenarse en el archivo “ResultadosLPFB.bin” de acuerdo a la siguiente estructura, se debe considerer que solo se debe colocar resultados de los equipos ingresados en el archive “EquiposLPFB.bin”:

//La tercera opción debe dar un reporte de la tabla de posiciones

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <algorithm>
using namespace std;

// Estructura para almacenar datos de los equipos
struct structEquiposLPFB
{
    char nombreEquipo[50];
    char colorCamiseta[50];
    char departamento[30];
    int anioCreacion;
};

// Estructura para almacenar resultados de partidos
struct structResultadosLPFB
{
    char nombreEquipoLocal[50];
    char nombreEquipoVisitante[50];
    int golesEquipoLocal;
    int golesEquipoVisitante;
    char fechaPartido[11];
};

// Función para ingresar datos de equipos
void ingresarEquipos()
{
    ofstream archivoEquipos("EquiposLPFB.bin", ios::binary | ios::app);

    if (!archivoEquipos.is_open())
    {
        cerr << "Error al abrir el archivo de equipos." << endl;
        return;
    }

    structEquiposLPFB equipo;
    char opcion;

    do
    {
        cout << "Ingrese el nombre del equipo: ";
        cin.ignore();
        cin.getline(equipo.nombreEquipo, sizeof(equipo.nombreEquipo));

        ifstream verificarEquipo("EquiposLPFB.bin", ios::binary);
        bool equipoExistente = false;

        while (verificarEquipo.read(reinterpret_cast<char *>(&equipo), sizeof(equipo)))
        {
            if (strcmp(equipo.nombreEquipo, equipo.nombreEquipo) == 0)
            {
                equipoExistente = true;
                break;
            }
        }

        verificarEquipo.close();

        if (equipoExistente)
        {
            cout << "El equipo ya existe. Ingrese otro nombre." << endl;
            continue;
        }

        cout << "Ingrese el color de la camiseta: ";
        cin.getline(equipo.colorCamiseta, sizeof(equipo.colorCamiseta));

        cout << "Ingrese el departamento: ";
        cin.getline(equipo.departamento, sizeof(equipo.departamento));

        cout << "Ingrese el año de creación: ";
        cin >> equipo.anioCreacion;

        archivoEquipos.write(reinterpret_cast<char *>(&equipo), sizeof(equipo));

        cout << "Equipo registrado correctamente." << endl;

        cout << "¿Desea ingresar otro equipo? (S/N): ";
        cin >> opcion;

    } while (opcion == 'S' || opcion == 's');

    archivoEquipos.close();
}

// Función para ingresar resultados de partidos
void ingresarResultados()
{
    ifstream archivoEquipos("EquiposLPFB.bin", ios::binary);

    if (!archivoEquipos.is_open())
    {
        cerr << "Error al abrir el archivo de equipos." << endl;
        return;
    }

    ofstream archivoResultados("ResultadosLPFB.bin", ios::binary | ios::app);

    if (!archivoResultados.is_open())
    {
        cerr << "Error al abrir el archivo de resultados." << endl;
        archivoEquipos.close();
        return;
    }

    structEquiposLPFB equipo;
    structResultadosLPFB resultado;
    char opcion;

    cout << "Equipos disponibles:" << endl;
    while (archivoEquipos.read(reinterpret_cast<char *>(&equipo), sizeof(equipo)))
    {
        cout << "- " << equipo.nombreEquipo << endl;
    }

    do
    {
        cout << "Ingrese el nombre del equipo local: ";
        cin.ignore();
        cin.getline(resultado.nombreEquipoLocal, sizeof(resultado.nombreEquipoLocal));

        ifstream verificarEquipo("EquiposLPFB.bin", ios::binary);
        bool equipoLocalExistente = false;

        while (verificarEquipo.read(reinterpret_cast<char *>(&equipo), sizeof(equipo)))
        {
            if (strcmp(equipo.nombreEquipo, resultado.nombreEquipoLocal) == 0)
            {
                equipoLocalExistente = true;
                break;
            }
        }

        verificarEquipo.close();

        if (!equipoLocalExistente)
        {
            cout << "El equipo local no existe. Ingrese un equipo válido." << endl;
            continue;
        }

        cout << "Ingrese el nombre del equipo visitante: ";
        cin.getline(resultado.nombreEquipoVisitante, sizeof(resultado.nombreEquipoVisitante));

        ifstream verificarEquipoVisitante("EquiposLPFB.bin", ios::binary);
        bool equipoVisitanteExistente = false;

        while (verificarEquipoVisitante.read(reinterpret_cast<char *>(&equipo), sizeof(equipo)))
        {
            if (strcmp(equipo.nombreEquipo, resultado.nombreEquipoVisitante) == 0)
            {
                equipoVisitanteExistente = true;
                break;
            }
        }

        verificarEquipoVisitante.close();

        if (!equipoVisitanteExistente)
        {
            cout << "El equipo visitante no existe. Ingrese un equipo válido." << endl;
            continue;
        }

        cout << "Ingrese la cantidad de goles del equipo local: ";
        cin >> resultado.golesEquipoLocal;

        cout << "Ingrese la cantidad de goles del equipo visitante: ";
        cin >> resultado.golesEquipoVisitante;

        cout << "Ingrese la fecha del partido (formato dd/mm/aaaa): ";
        cin.ignore();
        cin.getline(resultado.fechaPartido, sizeof(resultado.fechaPartido));

        archivoResultados.write(reinterpret_cast<char *>(&resultado), sizeof(resultado));

        cout << "Resultado registrado correctamente." << endl;

        cout << "¿Desea ingresar otro resultado? (S/N): ";
        cin >> opcion;

    } while (opcion == 'S' || opcion == 's');

    archivoEquipos.close();
    archivoResultados.close();
}

// Estructura para la tabla de posiciones
struct TablaPosiciones
{
    char nombreEquipo[50];
    int PJ;
    int G;
    int E;
    int P;
    int GF;
    int GC;
    int DG;
    int Pts;
};

// Función para comparar equipos por puntos
bool compararPorPuntos(const TablaPosiciones &a, const TablaPosiciones &b)
{
    return a.Pts > b.Pts;
}

// Función para generar y mostrar el reporte de la tabla de posiciones
void reporteTablaPosiciones()
{
    ifstream archivoEquipos("EquiposLPFB.bin", ios::binary);

    if (!archivoEquipos.is_open())
    {
        cerr << "Error al abrir el archivo de equipos." << endl;
        return;
    }

    ifstream archivoResultados("ResultadosLPFB.bin", ios::binary);

    if (!archivoResultados.is_open())
    {
        cerr << "Error al abrir el archivo de resultados." << endl;
        archivoEquipos.close();
        return;
    }

    structEquiposLPFB equipo;
    structResultadosLPFB resultado;

    const int MAX_EQUIPOS = 8;
    TablaPosiciones tabla[MAX_EQUIPOS];

    int numEquipos = 0;

    // Leer hasta MAX_EQUIPOS equipos o hasta el final del archivo
    while (archivoEquipos.read(reinterpret_cast<char *>(&equipo), sizeof(equipo)))
    {
        strcpy(tabla[numEquipos].nombreEquipo, equipo.nombreEquipo);
        tabla[numEquipos].PJ = 0;
        tabla[numEquipos].G = 0;
        tabla[numEquipos].E = 0;
        tabla[numEquipos].P = 0;
        tabla[numEquipos].GF = 0;
        tabla[numEquipos].GC = 0;
        tabla[numEquipos].DG = 0;
        tabla[numEquipos].Pts = 0;

        numEquipos++;

        if (numEquipos == MAX_EQUIPOS)
            break;
    }

    // Calcular la tabla de posiciones
    while (archivoResultados.read(reinterpret_cast<char *>(&resultado), sizeof(resultado)))
    {
        for (int i = 0; i < numEquipos; i++)
        {
            if (strcmp(tabla[i].nombreEquipo, resultado.nombreEquipoLocal) == 0)
            {
                tabla[i].PJ++;
                tabla[i].GF += resultado.golesEquipoLocal;
                tabla[i].GC += resultado.golesEquipoVisitante;

                if (resultado.golesEquipoLocal > resultado.golesEquipoVisitante)
                {
                    tabla[i].G++;
                    tabla[i].Pts += 3;
                }
                else if (resultado.golesEquipoLocal < resultado.golesEquipoVisitante)
                {
                    tabla[i].P++;
                }
                else
                {
                    tabla[i].E++;
                    tabla[i].Pts += 1;
                }
            }

            if (strcmp(tabla[i].nombreEquipo, resultado.nombreEquipoVisitante) == 0)
            {
                tabla[i].PJ++;
                tabla[i].GF += resultado.golesEquipoVisitante;
                tabla[i].GC += resultado.golesEquipoLocal;

                if (resultado.golesEquipoVisitante > resultado.golesEquipoLocal)
                {
                    tabla[i].G++;
                    tabla[i].Pts += 3;
                }
                else if (resultado.golesEquipoVisitante < resultado.golesEquipoLocal)
                {
                    tabla[i].P++;
                }
                else
                {
                    tabla[i].E++;
                    tabla[i].Pts += 1;
                }
            }
        }
    }

    // Ordenar la tabla de posiciones por puntos de mayor a menor
    sort(tabla, tabla + numEquipos, compararPorPuntos);

    // Mostrar la tabla de posiciones formateada
    cout << "\nTabla de Posiciones:" << endl;
    cout << "  No.    Equipo              PJ   G   E   P   GF   GC   DG   Pts" << endl;

    for (int i = 0; i < numEquipos; i++)
    {
        cout << "  " << i + 1 << "      " << setw(20) << left << tabla[i].nombreEquipo
             << setw(4) << tabla[i].PJ << setw(4) << tabla[i].G << setw(4) << tabla[i].E << setw(4) << tabla[i].P
             << setw(5) << tabla[i].GF << setw(5) << tabla[i].GC << setw(5) << tabla[i].DG << setw(5) << tabla[i].Pts << endl;
    }

    archivoEquipos.close();
    archivoResultados.close();
}

// Función principal
int main()
{
    int opcion;

    do
    {
        cout << "\nMenú de Opciones:" << endl;
        cout << "1. Ingreso de datos de los equipos de la LPFB." << endl;
        cout << "2. Ingreso de los resultados de los partidos." << endl;
        cout << "3. Reporte de la tabla de posiciones." << endl;
        cout << "4. Salir." << endl;
        cout << "Ingrese su opción: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            ingresarEquipos();
            break;

        case 2:
            ingresarResultados();
            break;

        case 3:
            reporteTablaPosiciones();
            break;

        case 4:
            cout << "Saliendo del programa. ¡Hasta luego!" << endl;
            break;

        default:
            cout << "Opción no válida. Por favor, ingrese una opción válida." << endl;
            break;
        }

    } while (opcion != 4);

    return 0;
}
