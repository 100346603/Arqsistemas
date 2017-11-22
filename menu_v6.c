#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "menu_v6.h"


void iniciar(Lista* lista){
  lista->primero=NULL;
  lista->tamanio=0;
}

int main(){

  int opcion;
  int comodin = 0;
  int contador = 0;

  Lista *nodo_jedi = malloc (sizeof(Nodo));
  iniciar(nodo_jedi);
  Nodo *primero = NULL;




  do{


    contador++;

    imprimir_menu();

    printf("\t\t#INFO: %d veces mostrado el menu principal\n\n", contador);
    printf("\nDame una opcion: \n");
    scanf("%i",&opcion);

    switch(opcion)
    {

      case 1:

        if(salir_programa() == 0){
          return 0;
        }else{
          break;
        }

      case 2:

        primero=insertar_jedi(primero);
        break;

      case 3:

        mostrar_resumen(primero);
        break;

      case 4:

        mostrar_info(primero);
        break;

      default: printf("Opcion erronea\n\n");

    }

  } while(comodin == 0);

  return 0;
}




void imprimir_menu(void){



    printf("=========================================\n");
    printf("[*][2017][SAUCEM APPS][JediManager]======\n");
    printf("=========================================\n");
    printf("[1] Salir\n");
    printf("[2] Insertar Jedi\n");
    printf("[3] Mostrar Jedis\n");
    printf("[4] Mostrar Jedi por ID\n");
    printf("[5] Modificar un Jedi\n");
    printf("[6] Borrar Jedi por ID\n");
    printf("[7] Exportar Jedis a fichero binario\n");
    printf("[8] Importar Jedis de fichero binario\n");
    printf("[9] Simulador de combate Jedi\n");
    printf("[10] Ordenar Jedis por puntos de vida\n");
    printf("[11] Autosalvado Jedi (5 segundos, si ha habido cambios)\n");

}


int salir_programa(void){

  char charsalida;

  printf("¿Está seguro de que desea salir del programa?[s/N]:\n");
  scanf("%s", &charsalida);

  return strcmp(&charsalida, "s");

}

char *intro_cadena(){
  char *cadena = NULL;
  size_t numero_bytes=0;
  ssize_t bytes_leidos;


  bytes_leidos = getline( &cadena, &numero_bytes, stdin);

  if(cadena[bytes_leidos-1]=='\n'){
     cadena[bytes_leidos-1]='\0';
    }
    if(bytes_leidos == -1){
      return NULL;
    }

    return cadena;
    free(cadena);
}


double leer_double(){
  char *convertir = intro_cadena();
  double valor = strtod(convertir, NULL);
  free(convertir);
  return valor;
}

int leer_entero(){
  char *convertir = intro_cadena();
  int valor = strtol(convertir, NULL, 0);
  free(convertir);
  return valor;
}





Nodo *insertar_jedi(Nodo *primero){

  Nodo *insertar=(Nodo*) malloc(sizeof(Nodo));

    printf("Insertando Jedi\n");
    printf("\tDame el ID del Jedi: ");
    insertar->jedi.ID=leer_entero();
    insertar->jedi.ID=leer_entero();
    printf("\tDame el nombre del Jedi: ");
    insertar->jedi.s_full_name=intro_cadena();
    printf("\tDame la vida: ");
    insertar->jedi.puntos.hit_points=leer_entero();
    printf("\tDame el ataque de aprendiz: ");
    insertar->jedi.puntos.attack_array[0]=leer_entero();
    printf("\tDame la defensa de aprendiz: ");
    insertar->jedi.puntos.defense_array[0]=leer_entero();
    printf("\tDame el ataque especial: ");
    insertar->jedi.puntos.attack_array[1]=leer_entero();
    printf("\tDame la defensa especial: ");
    insertar->jedi.puntos.defense_array[1]=leer_entero();
    printf("\tDame la velocidad: ");
    insertar->jedi.puntos.speed_array[0]=leer_double();
    printf("\tDame la velocidad especial: ");
    insertar->jedi.puntos.speed_array[1]=leer_double();
    printf("\tEs maestro (s/N):");
    char j = *intro_cadena();
    if(j=='s'){
      insertar->jedi.puntos.level = 1;
    }else if(j == 'n'){
      insertar->jedi.puntos.level = 0;
    }


     if(primero==NULL){
      primero=insertar;
     }else{
      insertar->next=primero;
       primero=insertar;
     }

  return primero;
}

void mostrar_resumen(Nodo *primero){
  if(primero==NULL){
    printf("\nLista vacía");
  }else{
    Nodo *j;

    printf("================================\n");
    printf("|  ID|    Nomb. |Vida|Ata.|Def.|\n");
    printf("================================\n");
    for(j=primero; j!=NULL; j= j->next){
      printf("| %d |   %s  | %d | %d | %d |\n", j->jedi.ID, j->jedi.s_full_name, j->jedi.puntos.hit_points,
             j->jedi.puntos.attack_array[0], j->jedi.puntos.defense_array[0]);
      printf("================================\n");
      }
  }
}

void mostrar_info(Nodo *primero){
  if(primero==NULL){
    printf("Lista vacía");
  }else{
    printf("Indique el ID: \n");
     int n_ID;
      n_ID = leer_entero();

     Nodo *j;

     for(j=primero; j =! NULL; j=j->next){
       if(j->jedi.ID == n_ID){
	  printf("= Información completa de Jedi");
		printf("\n= id: %d",j->jedi.ID);
		printf("\n= vida: %d",j->jedi.puntos.hit_points);
		printf("\n= nombre: %s, %d",j->jedi.s_full_name, j->jedi.puntos.level);
		printf("\n= ataque: %d",j->jedi.puntos.attack_array[0]);
		printf("\n= defensa: %d",j->jedi.puntos.defense_array[0]);
		printf("\n= s ataque: %d",j->jedi.puntos.attack_array[1]);
		printf("\n= s defensa: %d",j->jedi.puntos.defense_array[1]);
		printf("\n= velocidad: %lf\n",j->jedi.puntos.speed_array[1]);/////%d? no es para double
       }
     }
  }
}







