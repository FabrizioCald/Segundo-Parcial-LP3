/*segundo_parcial_lp3.c*/
/*
	Nombre y Apellido: Fabrizio Calderoli
	Segundo parcial de LP3
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#include <semaphore.h>
/*pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;*/

sem_t sem1;

//--------------------------------------------------
struct Datos{
	int autosNum[99];
	int autosSent[99];
};

static void *funcion_hilo_1( void *datoR);
static void *funcion_hilo_2( void *datoL);
void imprimir_status(struct Datos * lista);
char *formatoAuto(int numero);
void imprimir_pasos_der(int paso4, int paso3, int paso2, int paso1);
void imprimir_pasos_izq(int paso4, int paso3, int paso2, int paso1);
//--------------------------------------------------

static void *funcion_hilo_1(void *datoR){
	/*----------------------------------------*/
	/*pthread_mutex_lock(&mutex);*/

	struct Datos * datosr = (struct Datos *)datoR;
	int pos = 0;
	/*int seguir = 0;*/
	int cambio = 0;
	int cont_auto = 0;
	int paso1 = 0;
	int paso2 = 0;
	int paso3 = 0;
	int paso4 = 0;

	/*pthread_mutex_unlock(&mutex);*/
	//--------------------------------------------------------------------------
	while(1){
		//---------------------------------------------------------------------
		sem_wait(&sem1);
		/*pthread_mutex_lock(&mutex);*/
		/*printf("desde el hilo 1 inicio\n");*/
		for (int i = 0; i < 99; ++i)
		{
			if (datosr->autosSent[i] == 2)
			{
				cambio = 1;
				break;
			}
		}

		while (pos < 99) {
            if ((datosr->autosNum[pos] != 0) && (datosr->autosSent[pos] == 1) && (cont_auto < 4)) {
                paso4 = 0;
                paso3 = paso2;
                paso2 = paso1;
                paso1 = datosr->autosNum[pos]; // Guardar el número del auto
                datosr->autosNum[pos] = 0;
                datosr->autosSent[pos] = 0;
                cont_auto++;
                /*pos++;*/
                imprimir_pasos_der(paso4, paso3, paso2, paso1);
				imprimir_status(datosr);
				sleep(1);
				system("clear");
            }else if (cont_auto == 4)
            {
            	paso4 = 0;
                paso3 = paso2;
                paso2 = paso1;
                paso1 = 0;
                imprimir_pasos_der(paso4, paso3, paso2, paso1);
				imprimir_status(datosr);
				sleep(1);
				system("clear");
				if ((paso4 == 0) && (paso3 == 0) && (paso2 == 0) && (paso1 == 0) && (cambio == 1))
				{
					break;
				}
            }else{
            	paso4 = 0;
                paso3 = paso2;
                paso2 = paso1;
                paso1 = 0;
                imprimir_pasos_der(paso4, paso3, paso2, paso1);
				imprimir_status(datosr);
				sleep(1);
				system("clear");
				if ((paso4 == 0) && (paso3 == 0) && (paso2 == 0) && (paso1 == 0) && (cambio == 1))
				{
					break;
				}
			}
            for (int sig = pos + 1; sig < 99; ++sig)
            {
            	if (cont_auto == 4)
            	{
            		break;
            	}
            	if ((datosr->autosNum[sig] != 0) && (datosr->autosSent[sig] == 1)){
            		pos = sig;
            		break;
            	}
            }
            /*pos++;*/
        }

        pos++;

        if (pos == 99)
        {
        	pos = 0;
        }
        cont_auto = 0;
        cambio = 0;

        /*printf("desde el hilo 1 final\n");*/
        sem_post(&sem1);
        /*pthread_mutex_unlock(&mutex);*/

		//--------------------------------------------------------------------------
	}
	//--------------------------------------------------------------------------
	
	return NULL;
}

static void *funcion_hilo_2(void *datoL){
	/*----------------------------------------*/
	/*pthread_mutex_lock(&mutex);*/

	struct Datos * datosl = (struct Datos *)datoL;
	int pos = 0;
	/*int seguir = 0;*/
	int cambio = 0;
	int cont_auto = 0;
	int paso1 = 0;
	int paso2 = 0;
	int paso3 = 0;
	int paso4 = 0;
	
	/*pthread_mutex_unlock(&mutex);*/
	/*----------------------------------------*/
	//--------------------------------------------------------------------------
	while(1){
		//---------------------------------------------------------------------
		sem_wait(&sem1);
		/*pthread_mutex_lock(&mutex);*/
		/*printf("Desde el hilo 2 inicio\n");*/
		for (int i = 0; i < 99; ++i)
		{
			if (datosl->autosSent[i] == 1)
			{
				cambio = 1;
				break;
			}
		}

		while (pos < 99) {
            if ((datosl->autosNum[pos] != 0) && (datosl->autosSent[pos] == 2) && (cont_auto < 4)) {
                paso4 = 0;
                paso3 = paso2;
                paso2 = paso1;
                paso1 = datosl->autosNum[pos]; // Guardar el número del auto
                datosl->autosNum[pos] = 0;
                datosl->autosSent[pos] = 0;
                cont_auto++;
                /*pos++;*/
                imprimir_pasos_izq(paso4, paso3, paso2, paso1);
				imprimir_status(datosl);
				sleep(1);
				system("clear");
            }else if (cont_auto == 4)
            {
            	paso4 = 0;
                paso3 = paso2;
                paso2 = paso1;
                paso1 = 0;
                imprimir_pasos_izq(paso4, paso3, paso2, paso1);
				imprimir_status(datosl);
				sleep(1);
				system("clear");
				if ((paso4 == 0) && (paso3 == 0) && (paso2 == 0) && (paso1 == 0) && (cambio == 1))
				{
					break;
				}
            }else{
            	paso4 = 0;
                paso3 = paso2;
                paso2 = paso1;
                paso1 = 0;
                imprimir_pasos_izq(paso4, paso3, paso2, paso1);
				imprimir_status(datosl);
				sleep(1);
				system("clear");
				if ((paso4 == 0) && (paso3 == 0) && (paso2 == 0) && (paso1 == 0) && (cambio == 1))
				{
					break;
				}
            }

            for (int sig = pos + 1; sig < 99; ++sig)
            {
            	if (cont_auto == 4)
            	{
            		break;
            	}
            	if ((datosl->autosNum[sig] != 0) && (datosl->autosSent[sig] == 2)){
            		pos = sig;
            		break;
            	}
            }
            /*pos++;*/
        }

        pos++;

        if (pos == 99)
        {
        	pos = 0;
        }
        cont_auto = 0;
        cambio = 0;

        /*printf("desde el hilo 2 final\n");*/
        sem_post(&sem1);
        /*pthread_mutex_unlock(&mutex);*/

		//--------------------------------------------------------------------------
	}
	//--------------------------------------------------------------------------
	
	return NULL;
}
//--------------------------------------------------

void imprimir_pasos_der(int paso4, int paso3, int paso2, int paso1){
	if ((paso4 == 0) && (paso3 == 0) && (paso2 == 0) && (paso1 == 0))
	{
		printf("===============================================\n");
		printf("-----------------------------------------------\n");
		printf("-----------------------------------------------\n");
		printf("-----------------------------------------------\n");
		printf("===============================================\n");
	}

	if ((paso4 == 0) && (paso3 == 0) && (paso2 == 0) && (paso1 != 0))
	{
		char *resultadoUno = formatoAuto(paso1);
		printf("===============================================\n");
		printf("---->>>>>>>>>----------------------------------\n");
		printf("---->>%s>>-------------------------------------\n", resultadoUno);
		printf("---->>>>>>>>>----------------------------------\n");
		printf("===============================================\n");
		free(resultadoUno); // Liberamos la memoria reservada
	}

	if ((paso4 == 0) && (paso3 == 0) && (paso2 != 0) && (paso1 != 0))
	{
		char *resultadoUno = formatoAuto(paso1);
		char *resultadoDos = formatoAuto(paso2);
		printf("===============================================\n");
		printf("---->>>>>>>>>---->>>>>>>>>---------------------\n");
		printf("---->>%s>>---->>%s>>---------------------------\n", resultadoUno , resultadoDos);
		printf("---->>>>>>>>>---->>>>>>>>>---------------------\n");
		printf("===============================================\n");
		free(resultadoUno); // Liberamos la memoria reservada
		free(resultadoDos); // Liberamos la memoria reservada

	}else if ((paso4 == 0) && (paso3 == 0) && (paso2 != 0) && (paso1 == 0))
	{
		char *resultadoDos = formatoAuto(paso2);
		printf("===============================================\n");
		printf("----------------->>>>>>>>>---------------------\n");
		printf("----------------->>%s>>------------------------\n", resultadoDos);
		printf("----------------->>>>>>>>>---------------------\n");
		printf("===============================================\n");
		free(resultadoDos); // Liberamos la memoria reservada
	}

	if ((paso4 == 0) && (paso3 != 0) && (paso2 != 0) && (paso1 != 0))
	{
		char *resultadoUno = formatoAuto(paso1);
		char *resultadoDos = formatoAuto(paso2);
		char *resultadoTres = formatoAuto(paso3);
		printf("===============================================\n");
		printf("---->>>>>>>>>---->>>>>>>>>---->>>>>>>>>--------\n");
		printf("---->>%s>>---->>%s>>---->>%s>>-----------------\n", resultadoUno , resultadoDos, resultadoTres);
		printf("---->>>>>>>>>---->>>>>>>>>---->>>>>>>>>--------\n");
		printf("===============================================\n");
		free(resultadoUno); // Liberamos la memoria reservada
		free(resultadoDos); // Liberamos la memoria reservada
		free(resultadoTres); // Liberamos la memoria reservada

	}else if ((paso4 == 0) && (paso3 != 0) && (paso2 != 0) && (paso1 == 0))
	{
		char *resultadoDos = formatoAuto(paso2);
		char *resultadoTres = formatoAuto(paso3);
		printf("===============================================\n");
		printf("----------------->>>>>>>>>---->>>>>>>>>--------\n");
		printf("----------------->>%s>>---->>%s>>--------------\n", resultadoDos, resultadoTres);
		printf("----------------->>>>>>>>>---->>>>>>>>>--------\n");
		printf("===============================================\n");
		free(resultadoDos); // Liberamos la memoria reservada
		free(resultadoTres); // Liberamos la memoria reservada

	}else if ((paso4 == 0) && (paso3 != 0) && (paso2 == 0) && (paso1 == 0))
	{
		char *resultadoTres = formatoAuto(paso3);
		printf("===============================================\n");
		printf("------------------------------>>>>>>>>>--------\n");
		printf("------------------------------>>%s>>-----------\n", resultadoTres);
		printf("------------------------------>>>>>>>>>--------\n");
		printf("===============================================\n");
		free(resultadoTres); // Liberamos la memoria reservada

	}

	if ((paso4 == 0) && (paso3 != 0) && (paso2 == 0) && (paso1 != 0))
	{
		char *resultadoUno = formatoAuto(paso1);
		char *resultadoTres = formatoAuto(paso3);
		printf("===============================================\n");
		printf("---->>>>>>>>>----------------->>>>>>>>>--------\n");
		printf("---->>%s>>-------------->>%s>>-----------------\n", resultadoUno , resultadoTres);
		printf("---->>>>>>>>>----------------->>>>>>>>>--------\n");
		printf("===============================================\n");
		free(resultadoUno); // Liberamos la memoria reservada
		free(resultadoTres); // Liberamos la memoria reservada

	}

}

void imprimir_pasos_izq(int paso4, int paso3, int paso2, int paso1){
	if ((paso4 == 0) && (paso3 == 0) && (paso2 == 0) && (paso1 == 0))
	{
		printf("===============================================\n");
		printf("-----------------------------------------------\n");
		printf("-----------------------------------------------\n");
		printf("-----------------------------------------------\n");
		printf("===============================================\n");
	}

	if ((paso4 == 0) && (paso3 != 0) && (paso2 == 0) && (paso1 == 0))
	{
		char *resultadoTres = formatoAuto(paso3);
		printf("===============================================\n");
		printf("----<<<<<<<<<----------------------------------\n");
		printf("----<<%s<<-------------------------------------\n", resultadoTres);
		printf("----<<<<<<<<<----------------------------------\n");
		printf("===============================================\n");
		free(resultadoTres); // Liberamos la memoria reservada
	}

	if ((paso4 == 0) && (paso3 != 0) && (paso2 != 0) && (paso1 == 0))
	{
		char *resultadoTres = formatoAuto(paso3);
		char *resultadoDos = formatoAuto(paso2);
		printf("===============================================\n");
		printf("----<<<<<<<<<----<<<<<<<<<---------------------\n");
		printf("----<<%s<<----<<%s<<---------------------------\n", resultadoTres , resultadoDos);
		printf("----<<<<<<<<<----<<<<<<<<<---------------------\n");
		printf("===============================================\n");
		free(resultadoTres); // Liberamos la memoria reservada
		free(resultadoDos); // Liberamos la memoria reservada

	}else if ((paso4 == 0) && (paso3 == 0) && (paso2 != 0) && (paso1 == 0))
	{
		char *resultadoDos = formatoAuto(paso2);
		printf("===============================================\n");
		printf("-----------------<<<<<<<<<---------------------\n");
		printf("-----------------<<%s<<------------------------\n", resultadoDos);
		printf("-----------------<<<<<<<<<---------------------\n");
		printf("===============================================\n");
		free(resultadoDos); // Liberamos la memoria reservada
	}

	if ((paso4 == 0) && (paso3 != 0) && (paso2 != 0) && (paso1 != 0))
	{
		char *resultadoTres = formatoAuto(paso3);
		char *resultadoDos = formatoAuto(paso2);
		char *resultadoUno = formatoAuto(paso1);
		printf("===============================================\n");
		printf("----<<<<<<<<<----<<<<<<<<<----<<<<<<<<<--------\n");
		printf("----<<%s<<----<<%s<<----<<%s<<-----------------\n", resultadoTres , resultadoDos, resultadoUno);
		printf("----<<<<<<<<<----<<<<<<<<<----<<<<<<<<<--------\n");
		printf("===============================================\n");
		free(resultadoTres); // Liberamos la memoria reservada
		free(resultadoDos); // Liberamos la memoria reservada
		free(resultadoUno); // Liberamos la memoria reservada

	}else if ((paso4 == 0) && (paso3 == 0) && (paso2 != 0) && (paso1 != 0))
	{
		char *resultadoDos = formatoAuto(paso2);
		char *resultadoUno = formatoAuto(paso1);
		printf("===============================================\n");
		printf("-----------------<<<<<<<<<----<<<<<<<<<--------\n");
		printf("-----------------<<%s<<----<<%s<<--------------\n", resultadoDos, resultadoUno);
		printf("-----------------<<<<<<<<<----<<<<<<<<<--------\n");
		printf("===============================================\n");
		free(resultadoDos); // Liberamos la memoria reservada
		free(resultadoUno); // Liberamos la memoria reservada

	}else if ((paso4 == 0) && (paso3 == 0) && (paso2 == 0) && (paso1 != 0))
	{
		char *resultadoUno = formatoAuto(paso1);
		printf("===============================================\n");
		printf("------------------------------<<<<<<<<<--------\n");
		printf("------------------------------<<%s<<-----------\n", resultadoUno);
		printf("------------------------------<<<<<<<<<<-------\n");
		printf("===============================================\n");
		free(resultadoUno); // Liberamos la memoria reservada

	}

	if ((paso4 == 0) && (paso3 != 0) && (paso2 == 0) && (paso1 != 0))
	{
		char *resultadoTres = formatoAuto(paso3);
		char *resultadoUno = formatoAuto(paso1);
		printf("===============================================\n");
		printf("----<<<<<<<<<-----------------<<<<<<<<<--------\n");
		printf("----<<%s<<--------------<<%s<<-----------------\n", resultadoTres , resultadoUno);
		printf("----<<<<<<<<<-----------------<<<<<<<<<--------\n");
		printf("===============================================\n");
		free(resultadoTres); // Liberamos la memoria reservada
		free(resultadoUno); // Liberamos la memoria reservada

	}

}

char *formatoAuto(int numero) {
    // Determinamos el tamaño necesario para el string
    int numDigitos = 0;
    int temp = numero;
    while (temp != 0) {
        temp /= 10;
        numDigitos++;
    }
    
    // Almacenamos el tamaño del string, incluyendo el caracter nulo '\0'
    int tamanoString = numDigitos + 6; // "auto" + NN + '\0'
    
    // Reservamos memoria para el string
    char *cadena = (char *)malloc(tamanoString * sizeof(char));
    if (cadena == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria.\n");
        exit(EXIT_FAILURE);
    }
    
    // Construimos el string "autoNN"
    snprintf(cadena, tamanoString, "auto%02d", numero);
    
    return cadena;
}

void imprimir_status(struct Datos * lista){
	printf("--Autos en espera para atravesar el puente--\n");
	for (int i = 0; i < 99; ++i)
	{
		if (lista->autosNum[i] != 0)
		{
			if (lista->autosSent[i] == 1)
			{
				// autos que van a la derecha
				char *resultado = formatoAuto(lista->autosNum[i]);
    			printf("=> %s\n", resultado);
    
    			free(resultado); // Liberamos la memoria reservada
				
			}else if (lista->autosSent[i] == 2)
			{
				// autos que van a la izquierda
				char *resultado = formatoAuto(lista->autosNum[i]);
    			printf("<= %s\n", resultado);
    
    			free(resultado); // Liberamos la memoria reservada
			}
		}
	}
	/*printf("Se termino de imprimir status\n");*/
}

int main(int argc, char const *argv[])
{
	/*-----------------*/
	struct Datos arreglos;
	pthread_t hilo_uno;
	pthread_t hilo_dos;
	sem_init(&sem1, 0, 1);
	int contador = 0;

	for (int a = 0; a < 99; ++a)
	{
		arreglos.autosNum[a] = 0;
		arreglos.autosSent[a] = 0;
	}

	/*----------------*/
	char comando[8];
	char op_ab[] = "car";
	char op_a[] = "der";
	char op_b[] = "izq";
	char op_c[] = "status";
	char op_d[] = "start";
	/*----------------*/
	while(1){
		printf("Ingrese un comando: ");
		scanf("%s", comando);
		if (contador == 99)
		{
			contador = 0;
		}
		//---------------------------------------------------
		/*fflush(stdout);*/ // Descarga el búfer
		/*fgets(comando, sizeof(comando), stdin);*/
		// Elimina el carácter de nueva línea (si existe)
    	/*comando[strcspn(comando, "\r\n")] = '\0';*/
    	/*printf("\n");*/
		//---------------------------------------------------
		if (strcmp(comando, op_ab) == 0)
		{
			scanf("%s", comando);
			if (strcmp(comando, op_a) == 0)
			{
				/*printf("opcion car der\n");*/
				arreglos.autosNum[contador] = contador + 1;
				arreglos.autosSent[contador] = 1; // autos que van a la derecha tienen sentido 1
				contador++;
			}

			if (strcmp(comando, op_b) == 0)
			{
				/*printf("opcion car izq\n");*/
				arreglos.autosNum[contador] = contador + 1;
				arreglos.autosSent[contador] = 2; // autos que van a la izquierda tienen sentido 2
				 contador++;
			}
		}
		//----------------------------------------------------
		/*if (strcmp(comando, op_a) == 0)
		{
			printf("opcion car der\n");
		}

		if (strcmp(comando, op_b) == 0)
		{
			printf("opcion car izq\n");
		}*/
		//----------------------------------------------------
		if (strcmp(comando, op_c) == 0)
		{
			/*printf("opcion status\n");*/
			imprimir_status(&arreglos);
		}

		if (strcmp(comando, op_d) == 0)
		{
			printf("opcion start\n");
			/*break;*/
			pthread_create(&hilo_uno, NULL, *funcion_hilo_1, &arreglos);
			pthread_create(&hilo_dos, NULL, *funcion_hilo_2, &arreglos);
		}
	}

	/*pthread_create(&hilo_uno, NULL, *funcion_hilo_1, &arreglos);
	pthread_create(&hilo_dos, NULL, *funcion_hilo_2, &arreglos);*/

	pthread_join(hilo_uno, NULL);
	pthread_join(hilo_dos, NULL);

	return 0;
}