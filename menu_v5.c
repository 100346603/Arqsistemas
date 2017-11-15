#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "menu_v5.h"




int main(){

int opcion;
int comodin = 0;
int contador = 0;




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


        break;

      case 3:

      case 4:

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
  size_t numero_bytes=0;
  ssize_t bytes_leidos;
  char *cadena;

  numero_bytes=0;
  cadena=NULL;

  bytes_leidos = getline( &cadena, &numero_bytes, stdin);

  if(bytes_leidos==-1){
    return NULL;
    //if el caracter anterior es un espacio, entonces el caracter anterior es /0 = caracter nulo
  }else{
    return (cadena);
    free (cadena);
  }
}

double *convertir_entero(){
  char *convertir = intro_cadena();
  double valor = strtod(convertir,NULL);
  free(convertir);

  return &valor;
}

Nodo *insertar_yedi(Nodo *primero){

  Nodo *insertar=(Nodo*) malloc(sizeof(Nodo));

    if(primero==NULL){
      primero=insertar;
    }else{
      insertar->next=primero;
       primero=insertar;
     }

    printf("Insertando Jedi\n");
    printf("\tDame el ID del Jedi: ");
    insertar->jedi.ID=intro_cadena();
    printf("\tDame el nombre del Jedi: ");
    insertar->jedi.s_full_name=intro_cadena();
    printf("\tDame la vida: ");
    insertar->jedi.puntos.hit_points=convertir_entero();
    printf("\tDame el ataque de aprendiz: ");
    insertar->jedi.puntos.attack_array[0]=convertir_entero();
    printf("\tDame la defensa de aprendiz: ");
    insertar->jedi.puntos.defense_array[0]=convertir_entero();
    printf("\tDame el ataque especial: ");
    insertar->jedi.puntos.attack_array[1]=convertir_entero();
    printf("\tDame la defensa especial: ");
    insertar->jedi.puntos.defense_array[1]=convertir_entero();
    printf("\tDame la velocidad: ");
    insertar->jedi.puntos.speed_array[0]=convertir_entero();
    printf("\tDame la velocidad especial: ");
    insertar->jedi.puntos.speed_array[1]=convertir_entero();
    printf("\tEs maestro (s/N):");
    insertar->jedi.puntos.level=intro_cadena();



}







