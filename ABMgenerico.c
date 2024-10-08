#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define MAX_CAMPOS 10
#define MAX_LONGITUD 34



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
    int longitud;

} Metadata;

struct RegistroGenerico
{
    char campos[MAX_CAMPOS][MAX_LONGITUD];
};

int cantidadDeCampos;

void CargarMetaData(){
    struct Metadata nuevaData;
    FILE *metadata = fopen("Campos.dat","ab+");

    if(metadata == NULL){
        printf("No se pudo abrir el archivo!");
        return;
    } else { 
        printf("Ingrese el nombre que recibirá el campo: ");
        scanf("%s",&nuevaData.campo);

        
    
        printf("ingrese la longitud del campo: ");
        scanf("%d",&nuevaData.longitud);
    
        fwrite(&nuevaData,sizeof(struct Metadata),1,metadata);
    }
    fclose(metadata);
    return;
}

void vaciar_metadata(){
    FILE *archivo = fopen("Campos.dat","w");
    fclose(archivo);
    cantidadDeCampos = 0;
}

void alta_Estructura(){
    limpiar_pantalla();
    FILE *metadata = fopen("Campos.dat","ab+");
    if(metadata == NULL){
        printf("No se pudo abrir el archivo!");
        return;
    }
    fseek(metadata, 0, SEEK_END);
    long tamanio = ftell(metadata);
    fclose(metadata);
    if (tamanio != 0){
        printf("La estructura ya fue generada");
    } else {
        int cantidad;
        printf("Ingrese la cantidad de campos a cargar: ");
        scanf("%d",&cantidad);
        for(int i =0;i<cantidad;i++){
            CargarMetaData();
        }
        cantidadDeCampos = cantidad;
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
    long tamanio = ftell(metadata);
    fclose(metadata);
    if (tamanio == 0){
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

//---------------------------------------------ALTAS------------------------------------------------------

void liberarRegistro(struct RegistroGenerico *registro){

    for(int i =0; i<cantidadDeCampos;i++){
        free(registro->campos[i]);
    }
}

void mostrar_archivo_datos(){
    limpiar_pantalla();
    FILE *archivo = fopen("Datos.dat", "r+b");
    struct RegistroGenerico registro;
    int i = 1;
    //inicializarRegistro(&registro);
    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo");
    } else {
        printf("Contenido del archivo de datos: \n");
        fseek(archivo,0,SEEK_SET);
        while(fread(&registro,sizeof(struct RegistroGenerico),1,archivo) == 1){
            printf("%i\n", i);
            for (int i = 0; i < cantidadDeCampos; i++){
                
                printf("%s", registro.campos[i]);
                printf("\n");
            }
            printf("\n----------------------------\n");
            i++;
        }
    }
    fclose(archivo);
    pausa();
    return;
}

void main_alta(){
    FILE *metadata = fopen("Campos.dat", "r+b");
    FILE *archivo = fopen("Datos.dat", "a+b");
    struct Metadata datos;
    struct RegistroGenerico registro;
    
    int i = 0;
    
    while (fread(&datos, sizeof(struct Metadata), 1, metadata) == 1)
    {
        printf("Ingrese %s: ",datos.campo);
        int longitud = datos.longitud;
        if (longitud > MAX_LONGITUD) {
            printf("La longitud del campo es demasiado grande.\n");
            continue;
        }

        fgets(registro.campos[i], longitud, stdin);
        // Elimina el carácter de nueva línea del final de la cadena
        registro.campos[i][strcspn(registro.campos[i], "\n")] = '\0';
        i++;
    }

    

    fseek(archivo, 0, SEEK_END);
    fwrite(&registro,sizeof(struct RegistroGenerico),1,archivo);
    
    fclose(archivo);
    mostrar_archivo_datos();
}

void main_baja(){
    int indice;
    printf("Indique numero de registro que quiere dar de baja: \n");
    scanf("%d",&indice);
    
    FILE *archivo = fopen("Datos.dat", "r+b");

    fseek(archivo,sizeof(struct RegistroGenerico)*(indice-1),SEEK_SET);

    struct RegistroGenerico registroEliminado;
    memset(&registroEliminado,0,sizeof(struct RegistroGenerico));
    fwrite(&registroEliminado,sizeof(struct RegistroGenerico),1,archivo);

    fseek(archivo,0,SEEK_END);
    fclose(archivo);
    pausa();
    printf("Se dio de baja el registro de la posicion %i", indice);
    pausa();
    return;
}

void main_modificar(){
    int indice;
    int nroCampo;
    FILE *archivo = fopen("Datos.dat","r+b");
    printf("Indique numero de registro a modificar: ");
    scanf("%d",&indice);

    struct RegistroGenerico nuevoRegistro;
    fseek(archivo,sizeof(struct RegistroGenerico)*(indice-1),SEEK_SET);
    fread(&nuevoRegistro,sizeof(struct RegistroGenerico),1,archivo);
    for(int i =0; i< cantidadDeCampos;i++){
        printf("Campo %d: %s\n",i+1,nuevoRegistro.campos[i]);
    }
    printf("\nIndique el numero de campo a modificar: ");
    scanf("%i",&nroCampo);
    vaciar_buffer();
    printf("\nIngrese el nuevo valor del campo %i: ", nroCampo);
    fgets(nuevoRegistro.campos[nroCampo-1],34, stdin);
    nuevoRegistro.campos[nroCampo-1][strcspn(nuevoRegistro.campos[nroCampo-1], "\n")] = '\0';

    fseek(archivo,sizeof(struct RegistroGenerico)*(indice-1),SEEK_SET);
    fwrite(&nuevoRegistro,sizeof(struct RegistroGenerico),1,archivo);
    fclose(archivo);
    printf("Se ha modificado el campo correctamente");
    pausa();
    return;
}
// -----------------------------------------MENU Y MAIN---------------------------------------------------
void menu()
{
    printf("\n");
    printf("  ============================================================================\n");
    printf(" |                                 ABM Generico                                |\n");
    printf("  ============================================================================\n");
    printf("\n");
    printf("  1   Establecer estructura\n");
    printf("  2   Mostrar Estructura\n");
    printf("  3   BORRAR ESTRUCTURA\n");
    printf("  4   Dar de alta\n");
    printf("  5   Dar de baja\n");
    printf("  6   Modificar\n");
    printf("  7   Ver archivo\n");
    printf("\n");
    printf("  0   Salir\n");
    printf("\n");
    printf(" ------------------------------------------------------------------------------\n");
    printf("\n");
    printf("  Por favor seleccione una opción: ");
}

void main()
{
    FILE *campos = fopen("Campos.dat", "r+b");
    struct Metadata datos;
    fseek(campos,0,SEEK_SET);
    int i = 0;
    while(fread(&datos,sizeof(struct Metadata),1,campos) == 1){
         i++;     
    }
    cantidadDeCampos = i;
    fclose(campos);
    bool salir = false;
    int opcion;
    bool generoEstructura = false;
    while (!salir)
    {
        limpiar_pantalla();
        menu();
        int validador = scanf("%i", &opcion);
        vaciar_buffer();
        while (validador != 1 || opcion < 0 || opcion > 7)
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
            vaciar_metadata();
            break;
        case 4:
            main_alta();
            break;
        case 5:
            main_baja();
            break;
        case 6:
            main_modificar();
            break;
        case 7:
            mostrar_archivo_datos();
            break;
        case 0:
            salir = true;
        }
    }
}