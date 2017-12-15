/*@authors
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
    
    int guardar=0;
    pthread_mutex_init(&mutex,NULL);
    struct s_autosalvado *s_save;
    pthread_mutex_lock(&mutex);
    
   iniciar(nodo_jedi);
   Nodo *primero = NULL;
   pthread_t thread1 = NULL;
    

  
 



//Sentencias para controlar el menu
  do{
      
    int thr_rc=0; 
    pthread_mutex_unlock(&mutex);
    
    contador++;

    imprimir_menu();

    printf("\t\t#INFO: %d veces mostrado el menu principal\n\n", contador);
    printf("\nDame una opcion: \n");
    opcion = leer_entero();
    pthread_mutex_lock(&mutex);
    switch(opcion)
    {

      case 1: //Salir programa

        if(salir_programa() == 0){
	  borrar_lista(cabeza);
	  pthread_join(thread1,NULL);
	  pthread_mutex_unlock(&mutex);
	  pthread_mutex_destroy(&mutex);
	  free(nodo_jedi);
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

      case 7: //Exportar fichero

        exportar(primero);
        break;

      case 8: //Importar fichero

        importar(primero);
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

  printf("?Est? seguro de que desea salir del programa?[s/N]:\n");
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
    printf("\nLista vac?a\n");
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
    printf("\nLista vac?a\n");
  }else{
    printf("Indique el ID: \n");
     int id = leer_entero();
     Nodo *j;

     for(j = primero; j != NULL; j = j->next){
       if(j->jedi.ID == id){
	  printf("Informaci?n completa de Jedi");
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
        // Violacion del segmento cuando se introduce algo diferente a n?mero, o numero no encontrado
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



//Simulacion combate jedi
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
	  printf("El pokemonter no existe\n");
		  return NULL;
	 }
    }

    int danyo_1=(Jedi_1->jedi.puntos.speed_array[0]/Jedi_2->jedi.puntos.speed_array[0])*((86+rand()%15)*Jedi_1->jedi.puntos.attack_array[0])/(Jedi_2->jedi.puntos.defense_array[0])/10;
    printf("El Jedi_1 ataca con un da?o de: %d\n",danyo_1);
    int danyo_2=(Jedi_2->jedi.puntos.speed_array[0]/Jedi_1->jedi.puntos.speed_array[0])*((86+rand()%15)*Jedi_2->jedi.puntos.attack_array[0])/(Jedi_1->jedi.puntos.defense_array[0])/10;
    printf("El Jedi_2 ataca con un da?o de: %d\n",danyo_2);

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

//Importar Jedi de fichero binario

void importar(Nodo *primero){
  int tamanio;
  int numero_elementos = -1;
  int i_temp;
  char *c_temp;
  FILE *fichero2;
  printf("Introduce el nombre del fichero:\n");
  char *nombre_fichero = intro_cadena();
  fichero2 = fopen(nombre_fichero, "rb");
  if (fichero2 == NULL){
    perror("Error al abrir el fichero \n");
    return ;
  }

  while (!feof(fichero2) && numero_elementos<=0){
    Nodo *nuevoNodo= (Nodo*)malloc(sizeof(Nodo));

    numero_elementos = fread(&i_temp, sizeof(int), 1, fichero2);



    if (numero_elementos != 1){
      printf ("Error: Un dato no se ha podido leer %d\n",numero_elementos);

    }

    else{
      nuevoNodo->jedi.ID = i_temp;

    }

    numero_elementos = fread(&tamanio, sizeof(int), 1, fichero2);
    if (numero_elementos != 1){
      printf ("Error: Un dato no se ha podido leer \n");
    }
    numero_elementos = fread(&c_temp, sizeof(char), tamanio, fichero2);
    if (numero_elementos != tamanio){
      printf ("Error: Un dato no se ha podido leer \n");
    }
    else{
      nuevoNodo->jedi.s_full_name = c_temp;

    }

    numero_elementos = fread(&i_temp, sizeof(int), 1, fichero2);
    if (numero_elementos != 1){
      printf ("Error: Un dato no se ha podido leer \n");
    }
    else{
      nuevoNodo->jedi.size_name = i_temp;

    }

    numero_elementos = fread(&i_temp, sizeof(int), 1, fichero2);
    if (numero_elementos != 1){
      printf ("Error: Un dato no se ha podido leer \n");
    }
    else{
      nuevoNodo->jedi.puntos.hit_points = i_temp;

    }

    numero_elementos = fread(&i_temp, sizeof(int), 1, fichero2);
    if (numero_elementos != 1){
      printf ("Error: Un dato no se ha podido leer \n");
    }
    else{
      nuevoNodo->jedi.puntos.attack_array[2] = i_temp;

    }

    numero_elementos = fread(&i_temp, sizeof(int), 1, fichero2);
    if (numero_elementos != 1){
      printf ("Error: Un dato no se ha podido leer \n");
    }
    else{
      nuevoNodo->jedi.puntos.defense_array[2] = i_temp;

    }
    numero_elementos = fread(&i_temp, sizeof(int), 1, fichero2);
    if (numero_elementos != 1){
      printf ("Error: Un dato no se ha podido leer \n");
    }
    else{
      nuevoNodo->jedi.puntos.speed_array[2] = i_temp;

    }

    nuevoNodo->next = primero;
    primero = nuevoNodo;

  }
   if (ferror(fichero2) != 0){
    perror ("Error al leer el fichero \n");
  }
  else{
    printf ("El fichero se ha importado correctamente \n");
  }
  if (fclose(fichero2) != 0){
    perror ("Error al cerrar el fichero \n");
  }
}

//Exportar fichero
void exportar(Nodo *primero){
  int tamanio;
  int numero_elementos;
  FILE *fichero1;
  printf("Introduce el nombre del fichero: \n");
  char *nombre_fichero = intro_cadena();
  fichero1 = fopen(nombre_fichero, "wb");

  if (fichero1 == NULL){
    printf("El fichero no se ha podido abrir \n");
  }
  else if (primero == NULL){
    printf("La lista está vacia \n");
  }
  else{
    Nodo *j;
    for(j = primero; j != NULL; j = j->next){
      numero_elementos = fwrite (&(j->jedi.ID), sizeof(int), 1, fichero1);
      if (numero_elementos != 1){
	printf ("Error: El dato no se ha podido escribir \n");
      }

      tamanio = strlen(j->jedi.s_full_name) + 1;
      numero_elementos = fwrite(&tamanio, sizeof(int), 1, fichero1);
      if (numero_elementos != 1){
	printf ("Error: El dato no se ha podido escribir \n");
      }
      numero_elementos = fwrite(&(j->jedi.s_full_name), tamanio, 1, fichero1);
      if (numero_elementos != 1){
	printf ("Error: El dato no se ha podido escribir \n");
      }

      numero_elementos = fwrite (&(j->jedi.size_name), sizeof(int), 1, fichero1);
      if (numero_elementos != 1){
	printf ("Error: El dato no se ha podido escribir \n");
      }

      numero_elementos = fwrite (&(j->jedi.puntos.hit_points), sizeof(int), 1, fichero1);
      if (numero_elementos != 1){
	printf ("Error: El dato no se ha podido escribir \n");
      }

      numero_elementos = fwrite (&(j->jedi.puntos.attack_array[2]), sizeof(int), 1, fichero1);
      if (numero_elementos != 1){
	printf ("Error: El dato no se ha podido escribir \n");
      }

      numero_elementos = fwrite (&(j->jedi.puntos.defense_array[2]), sizeof(int), 1, fichero1);
      if (numero_elementos != 1){
	printf ("Error: El dato no se ha podido escribir \n");
      }

      numero_elementos = fwrite(&(j->jedi.puntos.speed_array[2]), sizeof(int), 1, fichero1);
      if (numero_elementos != 1){
	printf ("Error: El dato no se ha podido escribir \n");
      }

    }
    printf("El fichero se ha exportado correctamente \n");
  }
    if (fclose(fichero1) != 0){
      printf("Error al cerrar el fichero \n");
    }
}

int exportar_jedi(Lista *lista){
    FILE * f_out;
    f_out=fopen("data_demo.sbm","wb");

    size_t e_escritos;
    if (f_out== NULL){
       perror("El fichero no se ha podido abrir para lectura o no existe.\n");
        return -1;
    }

    else{
        Nodo *j;
        int i, n;

        for (j=lista->primero, i=0; i<lista->tamanio; i++, j=j->next){

            e_escritos=fwrite(&(j->jedi.ID), sizeof(int), 1, f_out);
            if(e_escritos!=1){
                 perror("Error: El dato no se ha escrito correctamente \n");
            }

            n=(int)strlen(j->jedi.s_full_name)+1;
            e_escritos=fwrite(&n,sizeof(int),1,f_out);
            if(e_escritos!=1){
                 perror("Error: El dato no se ha escrito correctamente \n");
            }
            e_escritos=fwrite(&(j->jedi.s_full_name), n, 1, f_out);
            if(e_escritos!=1){
                 perror("Error: El dato no se ha escrito correctamente \n");
            }

            e_escritos=fwrite(&(j->jedi.size_name), sizeof(int), 1, f_out);
            if(e_escritos!=1){
                 perror("Error: El dato no se ha escrito correctamente \n");
            }

            e_escritos=fwrite(&(j->jedi.puntos.hit_points), sizeof(int), 1, f_out);
            if(e_escritos!=1){
                 perror("Error: El dato no se ha escrito correctamente \n");
            }

            e_escritos=fwrite(&(j->jedi.puntos.attack_array[2]), sizeof(int), 1, f_out );
            if(e_escritos!=1){
                 perror("Error: El dato no se ha escrito correctamente \n");
            }

            e_escritos=fwrite(&(j->jedi.puntos.defense_array[2]), sizeof(int), 1, f_out);
            if(e_escritos!=1){
                 perror("Error: El dato no se ha escrito correctamente \n");
            }

            e_escritos=fwrite(&(j->jedi.puntos.speed_array[2]), sizeof(int), 1, f_out);
            if(e_escritos!=1){
                 perror("Error: El dato no se ha escrito correctamente \n");
            }
        }
        printf("El fichero se ha exportado correctamente \n");
    }

    if (fclose(f_out)!=0){
        perror("No se ha podido cerrar el fichero.\n");
        return -1;
    }
    return 0;
}
void* autosalvado(void* data){
   printf("Exportando...\n");
  pthread_mutex_lock(&mutex);
  struct Nodo* aux;
  struct s_autosalvado *info=(struct s_autosalvado*)data;
  while(info->opcion == 0){
        aux=info->lista;
	
        exportar_jedi(info->lista);
        pthread_mutex_unlock(&mutex);
	sleep(5);
	pthread_mutex_lock(&mutex);
    
    }
    
   pthread_mutex_unlock(&mutex);
   
    return 0;
  
}