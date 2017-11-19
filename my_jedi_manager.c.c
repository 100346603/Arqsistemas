/**CFile***********************************************************************

  Fichero     [obligatorio]

  Resumen     [obligatorio]

  Descripción [opcional]

  Ver también [opcional]

  Autor       [opcional]

  Copyright   [Copyright (c) 2012 Universidad Carlos III de Madrid

  Se concede, sin necesidad de acuerdo por escrito y sin ningún tipo de derechos
  de autor, permiso para utilizar, copiar, modificar y distribuir este programa
  y su documentación para cualquier propósito siempre y cuando esta advertencia
  y los siguientes dos párrafos aparezcan en las copias.

  EN NINGÚN CASO SE RECONOCERÁ A LA UNIVERSIDAD CARLOS III DE MADRID RESPONSABLE
  DIRECTA, INDIRECTA, ESPECIAL, O SUBSIDIARIA DE LOS POSIBLES DAÑOS Y PERJUICIOS
  QUE PUEDAN DERIVARSE DEL USO DE ESTE PROGRAMA Y DE SU DOCUMENTACIÓN, INCLUSO
  EN EL CASO DE QUE LA UNIVERSIDAD CARLOS III DE MADRID HAYA SIDO ADVERTIDA DE
  TALES DAÑOS Y PERJUICIOS.

  LA UNIVERSIDAD CARLOS III DE MADRID ESPECÍFICAMENTE SE DESENTIENDE DE TODO
  TIPO DE GARANTÍAS INCLUYENDO, PERO NO LIMITANDOLAS A, LAS GARANTIAS IMPLÍCITAS
  DE LA COMERCIALIZACIÓN Y ADECUACIÓN PARA CUALQUIER PROPÓSITO EN PARTICULAR. EL
  PROGRAMA SE PROVEE TAL CUAL Y LA UNIVERSIDAD CARLOS III DE MADRID NO TIENE
  OBLIGACIÓN ALGUNA DE OFRECER MANTENIMIENTO, SOPORTE, ACTUALIZACIONES, MEJORAS
  O MODIFICACIONES.]

******************************************************************************/

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
	
	primero = insertar_jedi(primero);
        break;

      case 3:
	
	mostrar_resumen(primero);
	break;

      case 4:
	
	mostrar_pokemon_ID(primero);
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

  printf("�Est� seguro de que desea salir del programa?[s/N]:\n");
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
  double valor = strtol(convertir,NULL,0);
  free(convertir);

  return &valor;
}
double *convertir_double(){
  char *convertir1 = intro_cadena();
  double valor1 = strtod(convertir1,NULL,);
  free(convertir1);

  return &valor1;
}


Nodo *insertar_jedi(Nodo *primero){

  Nodo *insertar=(Nodo*)malloc(sizeof(Nodo));

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
    insertar->jedi.puntos.speed_array[0]=convertir_double();
    printf("\tDame la velocidad especial: ");
    insertar->jedi.puntos.speed_array[1]=convertir_double();
    printf("\tEs maestro (s/N):");
    insertar->jedi.puntos.level_jedi=intro_cadena();



}
void mostrar_resumen(Nodo *primero){
  if(primero==NULL){
    printf("Lista vac�a");
  }else{
    Nodo *resumen;
    printf("================================\n");
    printf("|  ID|    Nomb. |Vida|Ata.|Def.|\n");
    printf("================================\n");
    for(resumen=primero; resumen=!NULL; resumen++){
      printf("| %d |   %s  | %d | %d | %d |"resumen->jedi.ID, resumen->jedi.s_full_name, resumen->jedi.puntos.hit_points, resumen->jedi.puntos.attack_array[0],resumen->jedi.puntos.puntos.defense_array[0]);
      printf("================================\n");
      }
  }
}

void mostrar_info(Nodo *primero){
  if(primero==NULL){
    printf("Lista vac�a");
  }else{
    printf("Indique el ID: \n");
     int n_ID= convertir_entero;
     Nodo *j;
     
     for(j=primero; j =! NULL; j->next){
       if(j->jedi.id== ID){
	 printf("= Informaci�n completa de Jedi");
		printf("\n= id: %d",j->jedi.ID);
		printf("\n= vida: %d",j->jedi.puntos.hit_points);
		printf("\n= nombre: %s",j->jedi.s_full_name, j->jedi.puntos.level_jedi);
		printf("\n= ataque: %d",j->jedi.puntos.attack_array[0]);
		printf("\n= defensa: %d",j->jedi.puntos.defense_array[0]);
		printf("\n= s ataque: %d",j->jedi.puntos.attack_array[1]);
		printf("\n= s defensa: %d",j->jedi.puntos.defense_array[1]);
		printf("\n= velocidad: %d\n",j->jedi.puntos.speed_array[1]);
       }
     }
  }
} 