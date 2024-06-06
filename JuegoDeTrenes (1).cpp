#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <unordered_map>

using namespace std;

enum Color
{
    ROJO,
    AZUL,
    VERDE,
    MORADO,
    CAFE,
    NARANJA
};

const int NUM_CARTAS_POR_COLOR = 12;
const int NUM_JUGADORES = 4;
const int VAGONES_POR_JUGADOR = 18;

const int FILAS = 14;
const int COLUMNAS = 19;
const string RESET_COLOR = "\033[0m";
const string ROJO_COLOR = "\033[91m";
const string AZUL_COLOR = "\033[94m";
const string VERDE_COLOR = "\033[92m";
const string MORADO_COLOR = "\033[95m";
const string CAFE_COLOR = "\033[33m";
const string NARANJA_COLOR = "\033[33m";
const char TRAYECTO_A = 'A';
const char TRAYECTO_B = 'B';
const char TRAYECTO_C = 'C';
const char TRAYECTO_D = 'D';
const char TRAYECTO_E = 'E';
const char TRAYECTO_F = 'F';
const char TRAYECTO_G = 'G';
const char TRAYECTO_H = 'H';
const char TRAYECTO_I = 'I';
const char TRAYECTO_J = 'J';
const char TRAYECTO_K = 'K';
const char TRAYECTO_L = 'L';
const char TRAYECTO_M = 'M';
const char TRAYECTO_N = 'N';
const char TRAYECTO_O = 'O';
const char TRAYECTO_P = 'P';
const char TRAYECTO_Q = 'Q';
const char TRAYECTO_R = 'R';
const char TRAYECTO_S = 'S';

unordered_map<char, string> rutas = {
    {TRAYECTO_A, ROJO_COLOR},
    {TRAYECTO_B, ROJO_COLOR},
    {TRAYECTO_C, AZUL_COLOR},
    {TRAYECTO_D, VERDE_COLOR},
    {TRAYECTO_E, VERDE_COLOR},
    {TRAYECTO_F, MORADO_COLOR},
    {TRAYECTO_G, CAFE_COLOR},
    {TRAYECTO_H, CAFE_COLOR},
    {TRAYECTO_I, NARANJA_COLOR},
    {TRAYECTO_J, NARANJA_COLOR},
    {TRAYECTO_K, AZUL_COLOR},
    {TRAYECTO_L, ROJO_COLOR},
    {TRAYECTO_M, MORADO_COLOR},
    {TRAYECTO_N, MORADO_COLOR},
    {TRAYECTO_O, AZUL_COLOR},
    {TRAYECTO_P, VERDE_COLOR},
    {TRAYECTO_Q, MORADO_COLOR},
    {TRAYECTO_R, MORADO_COLOR},
    {TRAYECTO_S, CAFE_COLOR}};

vector<vector<char>> tablero = {
    {' ', ' ', ' ', TRAYECTO_D, 'X', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', ' ', ' ', TRAYECTO_J,'X','X',TRAYECTO_N, 'X', 'X', ' ', ' ',' '},
    {' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', TRAYECTO_E, ' ', ' ', ' ', 'X', 'X', 'X', 'X', 'X', 'X', TRAYECTO_O, 'X', 'X', 'X'},
    {'X', 'X', TRAYECTO_B, ' ', ' ', 'X', ' ', ' ', ' ', TRAYECTO_I, ' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', ' ', 'X', ' ', ' ', ' ', 'X', 'X', 'X', ' ', ' ', ' ', 'X', ' ', ' ', TRAYECTO_R},
    {'X', ' ', ' ', ' ', ' ', 'X', ' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', ' ', 'X', ' ', ' ', ' ',},
    {TRAYECTO_A, 'X', 'X', 'X', 'X', TRAYECTO_F, 'X', 'X', TRAYECTO_H, 'X', 'X', TRAYECTO_K, 'X', 'X', 'X', TRAYECTO_P, ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', 'X', ' ', ' ', 'X', ' ', ' ', ' ', 'X', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', 'X', ' ', ' ', 'X', ' ', ' ', ' ', 'X', ' ', ' ', TRAYECTO_S},
    {' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', 'X', ' ', ' ', 'X', ' ', ' ', ' ', 'X', ' ', ' ', 'X'},
    {' ', ' ', 'X', 'X', 'X', TRAYECTO_G, ' ', ' ', 'X', 'X', 'X', TRAYECTO_L, ' ', ' ', ' ', TRAYECTO_Q, 'X', 'X', 'X'},
    {' ', ' ', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', ' '},
    {' ', ' ', TRAYECTO_C, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', TRAYECTO_M, 'X', 'X', 'X', ' ', ' ', ' '}};

vector<string> cartas = {"Rojo", "Azul", "Verde", "Morado", "Cafe", "Naranja"};

struct Jugador
{
    vector<Color> cartas;
    int vagones;
    int puntos;
};

void barajar(vector<Color> &mazo)
{
    srand(static_cast<unsigned int>(time(0)));
    random_shuffle(mazo.begin(), mazo.end());
}

void robarCartas(vector<Color> &mazo, vector<Color> &cartasJugador, int numCartas, vector<Color> &descarte)
{
    for (int i = 0; i < numCartas; ++i)
    {
        if (mazo.empty())
        {
            if (descarte.empty())
            {
                cout << "No hay cartas para robar." << endl;
                return;
            }
            else
            {
                cout << "La baraja se ha agotado. Barajando descarte para crear nueva baraja.\n";
                barajar(descarte); // Barajar antes de vaciar el descarte
                mazo = descarte;
                descarte.clear();
            }
        }
        cartasJugador.push_back(mazo.back());
        mazo.pop_back();
    }
}

void mostrarCartas(const vector<Color> &cartas)
{
    for (Color carta : cartas)
    {
        switch (carta)
        {
        case ROJO:
            cout << ROJO_COLOR << "R" << RESET_COLOR << " ";
            break;
        case AZUL:
            cout << AZUL_COLOR << "A" << RESET_COLOR << " ";
            break;
        case VERDE:
            cout << VERDE_COLOR << "V" << RESET_COLOR << " ";
            break;
        case MORADO:
            cout << MORADO_COLOR << "M" << RESET_COLOR << " ";
            break;
        case CAFE:
            cout << CAFE_COLOR << "C" << RESET_COLOR << " ";
            break;
        case NARANJA:
            cout << NARANJA_COLOR << "N" << RESET_COLOR << " ";
            break;
        }
    }
    cout << endl;
}

int calcularPuntos(int numCartasTrayecto)
{
    switch (numCartasTrayecto)
    {
    case 2:
        return 1;
    case 3:
        return 2;
    case 4:
        return 4;
    case 5:
        return 6;
    case 6:
        return 9;
    default:
        return 0;
    }
}

bool esColorValido(int color)
{
    return color >= ROJO && color <= NARANJA;
}

void inicializarMazo(vector<Color> &mazo)
{
    for (int i = 0; i < NUM_CARTAS_POR_COLOR; ++i)
    {
        mazo.push_back(ROJO);
        mazo.push_back(AZUL);
        mazo.push_back(VERDE);
        mazo.push_back(MORADO);
        mazo.push_back(CAFE);
        mazo.push_back(NARANJA);
    }
    barajar(mazo);
}

void inicializarJugadores(vector<Jugador> &jugadores)
{
    for (int i = 0; i < NUM_JUGADORES; ++i)
    {
        jugadores[i].vagones = VAGONES_POR_JUGADOR;
        jugadores[i].puntos = 0;
    }
}

void imprimirTablero()
{
    for (int i = 0; i < FILAS; ++i)
    {
        for (int j = 0; j < COLUMNAS; ++j)
        {
            char celda = tablero[i][j];
            if (rutas.find(celda) != rutas.end())
            {
                cout << rutas[celda] << "[" << celda << "]" << RESET_COLOR;
            }
            else
            {
                cout << "[" << celda << "]";
            }
        }
        cout << endl;
    }
}
int main()
{
    // Inicializar jugadores y mazo
    vector<Jugador> jugadores(NUM_JUGADORES);
    vector<Color> mazo;
    vector<Color> descarte;
    inicializarJugadores(jugadores);
    inicializarMazo(mazo);

    // Iniciar el juego
    bool juegoEnCurso = true;
    int turno = 0;

    while (juegoEnCurso)
    {
        Jugador &jugadorActual = jugadores[turno % NUM_JUGADORES];
        cout << "Turno del jugador " << (turno % NUM_JUGADORES + 1) << endl;

        // Mostrar el tablero
        imprimirTablero();

        // Mostrar vagones disponibles para el jugador
        cout << "Vagones disponibles: " << jugadorActual.vagones << endl;

        // Mostrar las cartas del jugador
        cout << "Cartas del jugador: ";
        mostrarCartas(jugadorActual.cartas);

        cout << "Elija una acción: 1) Robar dos cartas 2) Realizar un trayecto\n";
        int accion;
        cin >> accion;

        if (accion == 1)
        {
            robarCartas(mazo, jugadorActual.cartas, 2, descarte);
            cout << "Cartas del jugador: ";
            mostrarCartas(jugadorActual.cartas);
        }
        else if (accion == 2)
        {
            cout << "Ingrese fila y columna del trayecto: ";
            int fila, columna;
            cin >> fila >> columna;
            fila--;    // Ajustamos el índice a partir de 0
            columna--; // Ajustamos el índice a partir de 0

            // Verificar si la fila y la columna están dentro del rango válido del tablero
            if (fila >= 0 && fila < FILAS && columna >= 0 && columna < COLUMNAS)
            {
                if (tablero[fila][columna] == 'X')
                {
                    cout << "Ingrese el número de cartas necesarias para el trayecto:\n";
                    int numCartasTrayecto;
                    cin >> numCartasTrayecto;

                    cout << "Ingrese el color de las cartas necesarias (0=Rojo, 1=Azul, 2=Verde, 3=Morado, 4=Cafe, 5=Naranja):\n";
                    int color;
                    cin >> color;

                    if (esColorValido(color))
                    {
                        Color colorCarta = static_cast<Color>(color);
                        int numCartasDelColor = count(jugadorActual.cartas.begin(), jugadorActual.cartas.end(), colorCarta);
                        if (numCartasDelColor >= numCartasTrayecto)
                        {
                            for (int i = 0; i < numCartasTrayecto; ++i)
                            {
                                auto it = find(jugadorActual.cartas.begin(), jugadorActual.cartas.end(), colorCarta);
                                if (it != jugadorActual.cartas.end())
                                {
                                    descarte.push_back(*it);
                                    jugadorActual.cartas.erase(it);
                                }
                            }
                            jugadorActual.vagones -= numCartasTrayecto;

                            // Cambiar la letra 'X' por otra letra cuando se complete la ruta
                            char nuevaLetra = ' ';
                            switch (tablero[fila][columna])
                            {
                            case 'A':
                                nuevaLetra = 'a';
                                break;
                            case 'B':
                                nuevaLetra = 'b';
                                break;
                            case 'C':
                                nuevaLetra = 'c';
                                break;
                            case 'D':
                                nuevaLetra = 'd';
                                break;
                            case 'E':
                                nuevaLetra = 'e';
                                break;
                            case 'F':
                                nuevaLetra = 'f';
                                break;
                            default:
                                break;
                            }
                            tablero[fila][columna] = nuevaLetra;

                            int puntosGanados = calcularPuntos(numCartasTrayecto);
                            jugadorActual.puntos += puntosGanados;
                            cout << "Trayecto realizado. Puntos ganados: " << puntosGanados << endl;
                        }
                        else
                        {
                            cout << "No tienes suficientes cartas de ese color.\n";
                        }
                    }
                    else
                    {
                        cout << "Color inválido.\n";
                    }
                }
                else
                {
                    cout << "No hay trayecto en esa posición.\n";
                }
            }
            else
            {
                // La posición del trayecto está fuera de los límites del tablero
                cout << "Posición inválida." << endl;
            }
        }

        // Incrementar el turno
        turno++;
    }

    return 0;
}
