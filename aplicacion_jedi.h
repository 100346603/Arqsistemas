#ifndef YEDI_H
#define YEDI_H

//Estructuras

typedef enum {T_APPRENTICE, T_MASTER} level_jedi;

typedef struct points{ //? Puntero?//

    int hit_points;
    int attack_array[2];
    int defense_array[2];
    double speed_array[2];
    level_jedi level;

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

typedef struct lista_jedi{
  Nodo* primero;
  int tamanio;
} Lista;

typedef struct s_autosalvado{
  Lista *lista;
  int opcion;
}s_autosalvado;

//Funciones

extern void imprimir_menu();
extern int salir_programa();
extern double leer_double();
extern Nodo *insertar_jedi(Nodo *primero);
extern int leer_entero();
extern char *intro_cadena();
extern void mostrar_resumen(Nodo *primero);
extern void mostrar_info(Nodo *primero);
extern Nodo *modificar_jedi(Nodo* primero);
extern Nodo *borrar_jedi(Nodo *primero);
extern Nodo *combate_jedi(Nodo *primero);
extern void exportar(Nodo *primero);
extern void importar(Nodo *primero);
extern void* autosalvado(void* data);
extern void ordenar_jedi(Nodo *primero);
extern void swap(Nodo *a, Nodo *b);
extern void s_save;

#endif /*YEDI_H*/
