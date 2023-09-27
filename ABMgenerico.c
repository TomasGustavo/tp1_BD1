#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>


// -------------------------------- FUNCIONES UTILES --------------------------------------
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


//----------------------------------FUNCIONES PARA OBTENER METADATA--------------------------------------
struct Metadata{
    
    char campo[32];
    //char tipo;
    int longitud;

} Metadata;


void CargarMetaData(){
    struct Metadata nuevaData;
    FILE *metadata = fopen("Campos.dat","ab+");

    if(metadata == NULL){
        printf("No se pudo abrir el archivo!");
        return;
    } else { 
        printf("Ingrese el nombre que recibirá el campo: ");
        scanf("%s",&nuevaData.campo);

        // printf("ingrese de que tipo sera el campo (int - char - float, etc.) solo con un caracter: ");
        //scanf("%c",&nuevaData.tipo);
    
        printf("ingrese la longitud del campo: ");
        scanf("%d",&nuevaData.longitud);
    
        fwrite(&nuevaData,sizeof(struct Metadata),1,metadata);
    }
    fclose(metadata);
    return;
}




void menu()
{
    printf("\n");
    printf("  ============================================================================\n");
    printf(" |                                 ABM Generico                                |\n");
    printf("  ============================================================================\n");
    printf("\n");
    printf("  1   Establecer estructura\n");
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
    limpiar_pantalla();
    FILE *metadata = fopen("Campos.dat","ab+");
    if(metadata == NULL){
        printf("No se pudo abrir el archivo!");
        return;
    }
    fseek(metadata, 0, SEEK_END);
    long tamaño = ftell(metadata);
    fclose(metadata);
    if (tamaño != 0){
        printf("La estructura ya fue generada");
    } else {
        int cantidad;
        printf("Ingrese la cantidad de campos a cargar: ");
        scanf("%d",&cantidad);
        for(int i =0;i<cantidad;i++){
            CargarMetaData();
        }
    }
    pausa();
    return;
}

void main_mostrar_estructura(){
    limpiar_pantalla();
    FILE *metadata = fopen("Campos.dat","ab+");
    if(metadata == NULL){
        printf("No se pudo abrir el archivo!");
        return;
    }
    fseek(metadata, 0, SEEK_END);
    long tamaño = ftell(metadata);
    fclose(metadata);
    if (tamaño == 0){
        printf("La estructura aun no fue generada");
    } else {
        FILE *campos = fopen("Campos.dat", "r+b");
        struct Metadata datos;
        if (campos == NULL)
        {
            printf("No se pudo abrir el archivo");
        } else {
            printf("ESTRUCTURA DE DATOS: \n");
            fseek(campos,0,SEEK_SET);
            while(fread(&datos,sizeof(struct Metadata),1,campos) == 1){
                printf("%s[%d]\n",datos.campo,datos.longitud);
        // printf("%s\n",datos.tipo);
            }
        }
        fclose(campos);
    }
    pausa();
    return;
}

void main_alta(){

    FILE *metadata = fopen("Campos.dat", "r+b");
    struct Metadata datos;
    //Deberia recorrer todo el archivo y por cada campo pedir que ingresen los datos
    while (fread(&datos, sizeof(struct Metadata), 1, metadata) == 1)
    {
        printf("Ingrese %s :",datos.campo);
        int i = datos.longitud;
        char valorDelCampo[i];
        fgets(valorDelCampo,i,stdin);
        //Aca es donde necesito ayuda
    }
    fclose(metadata);
}

void main()
{
    bool salir = false;
    int opcion;
    bool generoEstructura = false;
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
            main_alta();
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