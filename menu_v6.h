#ifndef YEDI_H
#define YEDI_H

//Estructuras

typedef struct points{

    int hit_points;
    int attack_array[2];
    int defense_array[2];
    double speed_array[2];
    enum level_jedi{T_APPRENTICE,T_MASTER}

}Points;

typedef struct jedi{

    int ID;
    char* s_full_name;
    int size_name;
    Points puntos;
}Jedi;

typedef struct Nodo{
  Jedi jedi;
  struct Nodo* next;
}Nodo;

struct Lista_jedis{
  Nodo* primero;
  int tamanio;
}Lista;

//Funciones

void imprimir_menu();
int salir_programa();
double convertir_entero();
Nodo *insertar_jedi(Nodo *primero);

#endif /*YEDI_H*/
