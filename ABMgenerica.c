#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "MetaData.h"

void pausa()
{
    printf("\n\nPresione una tecla para continuar...." );
    getchar();
}

void vaciar_buffer()
{
    char nada[200];
    fgets(nada, 200, stdin);
}

void limpiar_pantalla()
{
    printf("\033[2J\033[1;1H");
    return;
}

void menu()
{
    printf("\n");
    printf("  ============================================================================\n");
    printf(" |                                 ABM Generico                                |\n");
    printf("  ============================================================================\n");
    printf("\n");
    printf("  1   Dar de alta Estructura\n");
    printf("  2   Mostrar Estructura\n");
    printf("  3   Dar de alta\n");
    printf("  4   Dar de baja\n");
    printf("  5   Modificar\n");
    printf("\n");
    printf("  0   Salir\n");
    printf("\n");
    printf(" ------------------------------------------------------------------------------\n");
    printf("\n");
    printf("  Por favor seleccione una opción: ");
}

void alta_Estructura(){

    int cantidad;
    printf("Ingrese la cantidad de campos a cargar: ");

    scanf("%d",cantidad);

    for(int i =0;i<cantidad;i++){
        CargarMetaData();
    }

    return;
}

void main_mostrar_estructura(){

    FILE *campos = fopen("Campos.dat", "r+b");
    MetaData datos = (MetaData) malloc(sizeof(struct MetaDataRep));

    fseek(campos,0,SEEK_SET);
    while(fread(datos,sizeof(struct MetaDataRep),1,campos) == 1){
        printf("%s\n",datos->campo);
        printf("%s\n",datos->tipo);
        printf("%d\n",datos->longitud);
    
    }
    fclose(campos);
    free(datos);
    pausa();
    return;
}

void main_alta(){

    FILE *campo = fopen("Campos.dat", "r+b");
    
    MetaData datos = (MetaData) malloc(sizeof(struct MetaDataRep));
    fseek(campo,0,SEEK_SET);
    fread(datos,sizeof(struct MetaDataRep),1,campo);

    printf("cargar %s :",datos->campo);
    int i = datos->longitud;
    char x[i];
    fgets(x,i,stdin);


    fclose(campo);
    free(datos);
}

void main_abm()
{
    bool salir = false;
    int opcion;
    crear_archivo();
    
    while (!salir)
    {
        limpiar_pantalla();
        menu();
        int validador = scanf("%i", &opcion);
        vaciar_buffer();
        while (validador != 1 || opcion < 0 || opcion > 5)
        {
            printf("Opción incorrecta\n" );
            printf( "  Por favor seleccione una opción: " );
            validador = scanf("%i", &opcion);
            vaciar_buffer();
        }
        switch (opcion)
        {
        case 1:
            alta_Estructura();
            break;
        case 2:
            main_mostrar_estructura();
            break;
        case 3:
            //main_alta();
            break;
        case 4:
            //main_baja();
            break;
        case 5:
            //main_modificar();
            break;
        case 0:
            salir = true;
        }
    }
}