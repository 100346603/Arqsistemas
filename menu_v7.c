*@authors
Pedro Agreda Jimenez
Jorge Agustin Aviles Mendez
Santiago Romero Romero
Sergio Herencias Redondo
Arquitectura de Sistemas GIST
Universidad Carlos III de Madrid
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu_v7.h"

//Funcion para iniciar lista
void iniciar(Lista* lista){
  lista->primero = NULL;
  lista->tamanio = 0;
}

//Funcion main
int main(){

  int opcion;
  int valor_escape = 0; //Valor para ejecutar infinitamente el bucle do while
  int contador = 0; //Contador para ver numero de veces impresas el menu

  Lista *nodo_jedi = malloc (sizeof(Nodo));
  iniciar(nodo_jedi);
  Nodo *primero = NULL;



//Sentencias para controlar el menu
  do{


    contador++;

    imprimir_menu();

    printf("\t\t#INFO: %d veces mostrado el menu principal\n\n", contador);
    printf("\nDame una opcion: \n");
    opcion = leer_entero();
    
    switch(opcion)
    {

      case 1: //Salir programa

        if(salir_programa() == 0){
          return 0;
        }else{
          break;
        }

      case 2: //Insertar jedi

        primero = insertar_jedi(primero);
        break;

      case 3: //Mostrar jedis almacenados

        mostrar_resumen(primero);
        break;

      case 4: //Mostrar info jedi completa

        mostrar_info(primero);
        break;

      case 5: //Modificar jedi

      	modificar_jedi(primero);
      	break;

      case 6: //Borrar jedi

        primero = borrar_jedi(primero);
        break;
      case 9 : //Simulador de combate
	combate_jedi(primero);
	break;
	  
      default: printf("Opcion erronea\n\n");

    }

  } while(valor_escape == 0);

  return 0;
}



//Funcion para imprimmir el menu por pantalla
void imprimir_menu(){



    printf("\n=========================================\n");
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

//Funcion para salir del programa con redundancia [case 1]
int salir_programa(){

  char charsalida;

  printf("¿Está seguro de que desea salir del programa?[s/N]:\n");
  charsalida = *intro_cadena();

  return strcmp(&charsalida, "s");

}

//Funcion para leer texto por teclado
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

//Funcion para convertir la entrada de teclado a double
double leer_double(){
  char *convertir = intro_cadena();
  double valor = strtod(convertir, NULL);
  free(convertir);
  return valor;
}

//Funcion para convertir la entrada de teclado a int
int leer_entero(){
  char *convertir = intro_cadena();
  int valor = strtol(convertir, NULL, 0);
  free(convertir);
  return valor;
}




//Insertar Jedi
Nodo *insertar_jedi(Nodo *primero){

  Nodo *insertar=(Nodo*) malloc(sizeof(Nodo));

    printf("Insertando Jedi\n");
    printf("\tDame el ID del Jedi: ");
    insertar->jedi.ID=leer_entero();
    printf("\tDame el nombre del Jedi: ");
    insertar->jedi.s_full_name=intro_cadena();
    printf("\tDame la vida: ");
    insertar->jedi.puntos.hit_points=leer_entero();
    printf("\tDame el ataque de aprendiz: ");
    insertar->jedi.puntos.attack_array[0]=leer_entero();
    printf("\tDame la defensa de aprendiz: ");
    insertar->jedi.puntos.defense_array[0]=leer_entero();
    printf("\tDame la velocidad de aprendiz: ");
    insertar->jedi.puntos.speed_array[0]=leer_double();
    printf("\tDame el ataque de maestro: ");
    insertar->jedi.puntos.attack_array[1]=leer_entero();
    printf("\tDame la defensa de maestro: ");
    insertar->jedi.puntos.defense_array[1]=leer_entero();
    printf("\tDame la velocidad de maestro: ");
    insertar->jedi.puntos.speed_array[1]=leer_double();
    printf("\tEs maestro (s/N):");
    char j = *intro_cadena();
    if(j=='s'){
      insertar->jedi.puntos.level = 1;
    }else if(j == 'n'){
      insertar->jedi.puntos.level = 0;
    }


     if(primero==NULL){
      primero = insertar;
     }else{
      insertar->next = primero;
       primero = insertar;
     }

  return primero;
}

//Mostrar stats de Jedi de forma resumida
void mostrar_resumen(Nodo *primero){
  if(primero==NULL){
    printf("\nLista vacía\n");
  }else{
    Nodo *j;

    printf("================================\n");
    printf("|  ID|    Nomb. |Vida|Ata.|Def.|\n");
    printf("================================\n");
    for(j=primero; j != NULL; j = j->next){
      printf("| %d |   %s  | %d | %d | %d |\n", j->jedi.ID, j->jedi.s_full_name, j->jedi.puntos.hit_points,
             j->jedi.puntos.attack_array[0], j->jedi.puntos.defense_array[0]);
      printf("================================\n");
      }
  }
}

//Mostrar informacion de un jedi, de forma completa pidiendo su ID por teclado
void mostrar_info(Nodo *primero){
  if(primero==NULL){
    printf("\nLista vacía\n");
  }else{
    printf("Indique el ID: \n");
     int id = leer_entero();
     Nodo *j;

     for(j = primero; j != NULL; j = j->next){
       if(j->jedi.ID == id){
	  printf("Información completa de Jedi");
		printf("\n= id: %d",j->jedi.ID);
		printf("\n= vida: %d",j->jedi.puntos.hit_points);
		if(j->jedi.puntos.level == 0){
			printf("\n= nombre: %s, Aprendiz ",j->jedi.s_full_name);
		}
		if(j->jedi.puntos.level == 1){
			printf("\n= nombre: %s, Maestro ",j->jedi.s_full_name);
		}
		printf("\n= ataque aprendiz: %d",j->jedi.puntos.attack_array[0]);
		printf("\n= defensa aprendiz: %d",j->jedi.puntos.defense_array[0]);
	  printf("\n= velocidad aprendiz: %lf",j->jedi.puntos.speed_array[0]);
    printf("\n= ataque maestro: %d",j->jedi.puntos.attack_array[1]);
		printf("\n= defensa maestro: %d",j->jedi.puntos.defense_array[1]);
		printf("\n= velocidad maestro: %lf\n",j->jedi.puntos.speed_array[1]);
       }
     }
  }
}

//Modificar un jedi introduciendo por teclado el ID
Nodo *modificar_jedi(Nodo* primero){
  if (primero == NULL){
        printf("\nLista vacia \n");
    }else{
        printf("Indique el ID: ");
        int id = leer_entero();
        Nodo *j;

       for (j = primero; j != NULL; j = j->next){
            if (j->jedi.ID == id)
            {
                printf("\n\tID: ");
                j->jedi.ID = leer_entero();
		printf("\n\tNombre: ");
                j->jedi.s_full_name = intro_cadena();
		printf("\n\tEs maestro (s/N):");
    char h = *intro_cadena();
    if(h=='s'){
      j->jedi.puntos.level = 1;
    }else if(h == 'n'){
      j->jedi.puntos.level = 0;
    }
                printf("\n\tVida: ");
                j->jedi.puntos.hit_points = leer_entero();
		printf("\n\tAtaque de aprendiz: ");
                j->jedi.puntos.attack_array[0] = leer_entero();
		printf("\n\tDefensa de aprendiz: ");
                j->jedi.puntos.defense_array[0] = leer_entero();
    printf("\n\tVelocidad de aprendiz: ");
                j->jedi.puntos.speed_array[0] =leer_double();
		printf("\n\tAtaque de maestro: ");
                j->jedi.puntos.attack_array[1] = leer_entero();
		printf("\n\tDefensa de maestro: ");
                j->jedi.puntos.defense_array[1] = leer_entero();
		printf("\n\tVelocidad de maestro: ");
                j->jedi.puntos.speed_array[1] =leer_double();

            }
        }
    }
    return primero;
}

//Borrar un Jedi por ID captado mediante teclado
Nodo *borrar_jedi(Nodo *primero){
    if (primero == NULL){
        printf("\nLista vacia \n");
    }else{
        printf("\n Indique ID: ");
        int id = leer_entero();
        // Violacion del segmento cuando se introduce algo diferente a número, o numero no encontrado
	      Nodo *j;
        Nodo *borrar;

        if(primero->jedi.ID == id){
            borrar = primero;
	    if(primero->next == NULL){
	      return 0;
	    }else{
            primero = primero->next;
	    }
            free(borrar->jedi.s_full_name);
	    free(borrar);
        }else{
	  for (j = primero; j != NULL; j = j->next){
            if (j->next->jedi.ID == id){
                borrar = j->next;
                j->next = j->next->next;
                free(borrar->jedi.s_full_name);
		free(borrar);

            }
	  }
        }
    }
    return primero;
}
void ordenar_jedi(Nodo *primero){
    double vida;
    Nodo *j;
      if(primero==NULL){
	printf(“\nLista vacía \n”);
      }else{
        for(j=primero; j!=NULL ; j= j->next){
	  for(
           if(j->jedi.puntos.hit_points[0]>vida){
              vida=j->jedi.puntos.hit_points[0];
           }
         }
      }
Nodo *j; /////????????????????????????????????????????????????????????????????
 for(j=primero; j!=NULL ; j= j->next){
      if(j->jedi.puntos.hit_points[0]==vida){
       printf (“\n Jedis ordenados de mayor a menor:) ;
       printf
       
       
       
 }
}
}







Nodo *combate_jedi(Nodo *primero){
  Nodo *i;
  Nodo *j;
  Nodo *Jedi_1=NULL;
  Nodo *Jedi_2=NULL;
 
  if (primero == NULL){
        printf("\n La lista esta vacia \n");
    }else{
        printf("\n Indique el ID: ");
        int id_1 = leer_entero();
	
 
    for (i = primero; i != NULL; i = i->next){
            if (i->jedi.ID == id_1 && i->jedi.puntos.hit_points > 0){
	      printf("\nEl Jedi_1 puede combatir\n");
	      Jedi_1=i;
		}else if(i->jedi.ID == id_1 && i->jedi.puntos.hit_points < 0){
		  printf("\nEl Jedi_1 NO puede combatir\n");
		}
	}
	if(Jedi_1 == NULL){
	  printf("El Jedi_1 no existe\n");
		  return NULL;
	 }
  }//se puede borrar esto?
  if (primero == NULL){
        printf("\n La lista esta vacia \n");
   //hasta aqui
    }else{
        printf("\n Indique el ID: ");
        int id_2 = leer_entero();
      
        for (j = primero; j != NULL; j = j->next){
            if (j->jedi.ID == id_2 && j->jedi.puntos.hit_points > 0){
	      printf("\nEl Jedi_2 puede combatir\n");
	      Jedi_2=j;
		}else if(j->jedi.ID == id_2 && j->jedi.puntos.hit_points < 0){
		  printf("\nEl Jedi_2 no puede combatir\n");
		}
	}
	if(Jedi_2 == NULL){
	  printf("El pokemon no existe\n");
		  return NULL;
	 }
    }
  
    int danyo_1=(Jedi_1->jedi.puntos.speed_array[0]/Jedi_2->jedi.puntos.speed_array[0])*((86+rand()%15)*Jedi_1->jedi.puntos.attack_array[0])/(Jedi_2->jedi.puntos.defense_array[0])/10
    printf("El Jedi_1 ataca con un daño de: %d\n",danyo_1);
    int danyo_2=(Jedi_2->jedi.puntos.speed_array[0]/Jedi_1->jedi.puntos.speed_array[0])*((86+rand()%15)*Jedi_2->jedi.puntos.attack_array[0])/(Jedi_1->jedi.puntos.defense_array[0])/10
    printf("El Jedi_2 ataca con un daño de: %d\n",danyo_2);
    
    int vida_1 = Jedi_1->jedi.puntos.hit_points = (Jedi_1->jedi.puntos.hit_points)-danyo_2;
    printf("vida actualizada del Jedi_1 es: %d\n", vida_1);
    int vida_2 = Jedi_2->jedi.puntos.hit_points = (Jedi_2->jedi.puntos.hit_points)-danyo_1;
    printf("vida actualizada del Jedi_2 es: %d\n", vida_2);
    
    
    if(vida_1 > 0){
      printf("El Jedi_1 sigue vivo\n");
    }else{
      printf("El Jedi_1 no tiene vida\n");
    }
    
    if(vida_2 > 0){
      printf("El Jedi_2 sigue vivo\n");
    }else{
      printf("El Jedi_2 no tiene vida\n");
    }
    
    return (primero);
}
