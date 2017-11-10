#include<stdio.h>


void imprimir_menu(void);
void insertar_jedi(void);
int salir_programa(void);+

struct points* ptr_points{
   
    int hit_points;
    int attack_array[2];
    int defense_array[2];
    double speed_array [2];

}

struct Jedi{

    int ID;
    char* s_full_name;
    int size_name;
    enum level_jedi{T_APPRENTICE,T_MASTER};

}






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

        insertar_jedi();
        break;

      case 3:

      case 4:

      default: printf("Opcion erronea");

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

void insertar_jedi(void){


    printf("Insertando Jedi\n");

    printf("\tDame el ID del Jedi: ");
  	scanf("%i", &ID);
    printf("\tDame el nombre del Jedi: ");
    scanf("%s", &s_full_name);
    printf("\tDame la vida: ");
    scanf("%i", &hit_points);
  	printf("\tDame el ataque de aprendiz: ");
    scanf("%i", &attack_array[0]);
  	printf("\tDame la defensa de aprendiz: ");
    scanf("%i", &defense_array[0]);
  	printf("\tDame el ataque especial: ");
    scanf("%i", &attack_array[1]);
  	printf("\tDame la defensa especial: ");
    scanf("%i", &defense_array[1]);
  	printf("\tDame la velocidad: ");
    scanf("%i", &speed_array[0]);
  	printf("\tDame la velocidad especial: ");
    scanf("%i", &speed_array[1]);
  	printf("\tEs maestro (s/N):");
    scanf("%i", &level_jedi);

}

int salir_programa(void){

  char charsalida;

  printf("¿Está seguro de que desea salir del programa?[s/N]:\n");
  scanf("%s", &charsalida);

  return strcmp(&charsalida, "s");

}