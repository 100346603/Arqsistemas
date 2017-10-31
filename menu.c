#include<stdio.h>


int main(){
  int opcion;
  do{
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
    printf("\t\t\t#INFO:     veces mostrado el menu principal\n\n");
    printf("Dame una opcion: \n");
    scanf("%i",&opcion);
  
    switch(opcion){
      case 1: printf("¿Está seguro de que desea salir del programa?[s/N]:");
      return 0;
      break;
      
      case 2:
	printf("Insertando Jedi\n");
	printf("\t\t\tDame el ID del Jedi:\n");
	printf("\t\t\tDame el nombre del Jedi:\n");
	printf("\t\t\tDame la vida:\n");
	printf("\t\t\tDame el ataque de aprendiz:\n");
	printf("\t\t\tDame la defensa de aprendiz:\n");
	printf("\t\t\tDame el ataque especial:\n");
	printf("\t\t\tDame la defensa especial:\n");
	printf("\t\t\tDame la velocidad: \n"); 
	printf("\t\t\tDame la velocidad especial:\n");
	printf("\t\t\tEs maestro (s/N):\n");
	break;
      
      default: printf("Opcion erronea");
    
  }
  }
  while (opcion!=1);
  return 0;
}