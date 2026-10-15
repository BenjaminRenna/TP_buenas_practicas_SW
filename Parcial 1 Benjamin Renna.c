#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAM_CALLE 67
typedef struct {
	char Calle1[MAX_TAM_CALLE]; 
	char Calle2[MAX_TAM_CALLE];
	int Trafico;
} Vial;

Vial* agregarInterseccion(Vial *semaforo, int *cantidad);
void mostrarIntersecciones(Vial *semaforo,int cantidad);
void buscarCalles(Vial *semaforo,int cantidad);
void mostrarMenu();
void limpiarBuffer();

int main(int argc, char *argv[]) {
	Vial *semaforo= NULL;
	
	int cantidad = 0;
	int opcion;
	
	do{
		mostrarMenu();
		
		scanf("%d", &opcion);
		limpiarBuffer();
		switch (opcion) {
		case 1:
			semaforo = agregarInterseccion(semaforo,&cantidad);
			break;
		case 2:
			mostrarIntersecciones(semaforo,cantidad);
			break;
		case 3:
			buscarCalles(semaforo,cantidad);
			break;
		case 0:
			printf("Saliendo del programa.\n");
			break;
		default:
			printf("Opcion no valida. Intente de nuevo.\n");
		}
	} while(opcion != 0);
	return 0;
}
void mostrarMenu() {
	printf("\n--- MENU DE SEMAFORO---\n");
	printf("1. Agregar interseccion y Trafico\n");
	printf("2. Mostrar Intersecciones\n");
	printf("3. Buscar Calle");
	printf("\n");
	printf("0. Salir\n");
	printf("\n");
	printf("Seleccione una opcion: ");
	return;
}
Vial* agregarInterseccion(Vial *semaforo, int *cantidad){
	int cantidad_actual=0;
	int aux=0;
	char Ncalle1[41];
	char Ncalle2[41];
	int Ntrafico=0;
	cantidad_actual=*cantidad+1;
	
	Vial *temporal = (Vial *) realloc(semaforo, cantidad_actual * sizeof(Vial));
	if (temporal == NULL) {
		printf("Error: No se pudo asignar memoria para el nuevo jugador.\n");
		return semaforo; 	// Si falla, retornamos el valor viejo sin cambiar nada
	}
	semaforo = temporal;
	printf("Ingrese el nombre de la primer Calle\n");
	fgets(Ncalle1, 41, stdin);
	Ncalle1[strlen(Ncalle1)-1]='\0';
	strcpy(semaforo[*cantidad].Calle1, Ncalle1);
	printf("Ingrese el nombre de la segunda Calle\n");
	fgets(Ncalle2, 41, stdin);
	Ncalle2[strlen(Ncalle2)-1]='\0';
	strcpy(semaforo[*cantidad].Calle2, Ncalle2);
	printf("Ingrese la intensidad del trafico en la interseccion (Entre 0 y 100)\n");
	do{
		scanf("%d", &Ntrafico);
		if(Ntrafico <= 0 || Ntrafico>100){
			printf("El trafico debe estar entre 0 y 100\n");
		}
	} while(Ntrafico <= 0 || Ntrafico>100);
	limpiarBuffer();
	semaforo[*cantidad].Trafico=Ntrafico;
	(*cantidad)++;
	
	return semaforo;
}

void mostrarIntersecciones(Vial *semaforo,int cantidad){
	int i = 0;
	if (cantidad == 0 || semaforo == NULL) {
		printf("\nNo hay intersecciones.\n");
		return;
	}
	printf("\n=== INTERSECCIONES ACTUALES ===\n");
	printf("-----------------------------------------\n");
	for(i;i<cantidad;i++){
		printf("Interseccion %d entre %s y %s con una intensidad de trafico de %d \n",i,semaforo[i].Calle1,semaforo[i].Calle2,semaforo[i].Trafico);
	}
}
void buscarCalles(Vial *semaforo,int cantidad){
	int i = 0;
	char busca_calle[40];
	int encontro=0;
	memset(busca_calle, '\0', sizeof(busca_calle)); //rellena el arreglo de \0 para que este vacio
	
	if (cantidad == 0 || semaforo == NULL) {
		printf("\nNo hay intersecciones.\n");
		return;
	}
	printf("Ingrese el nombre de la calle a buscar\n");
	fgets(busca_calle, 51, stdin);
	//limpiarBuffer();
	busca_calle[strlen(busca_calle)-1] = '\0';
	printf("Buscando: %s\n", busca_calle);
	for(i;i<cantidad;i++){
		if (strcmp(semaforo[i].Calle1,busca_calle) == 0 || strcmp(semaforo[i].Calle2,busca_calle) == 0){
		printf("Interseccion entre Calle %s y Calle %s con un trafico de %d\n",semaforo[i].Calle1,semaforo[i].Calle2,semaforo[i].Trafico); 
		encontro=1;
		}
	}
	if (!encontro) { //si no lo encontre imprimo lo siguiente
		printf("\nNo se encontro ninguna interseccion con la calle: %s\n", busca_calle);
	}
}
void limpiarBuffer() {
	int c;
	while ((c = getchar()) != EOF && c != '\n');
}
