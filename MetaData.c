#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "MetaData.h"




void crear_archivo(){
    FILE *archivo = fopen("Campos.dat","w");

    fclose(archivo);
}

void CargarMetaData(){

    MetaData NuevaData = (MetaData)malloc(sizeof(struct MetaDataRep));
    FILE *metadata = fopen("Campos.dat","r+b");

    if(metadata == NULL){
        printf("No se pudo abrir el archivo!");
        return;
    }

    printf("Ingrese el nombre que recibirá el campo: ");
    fgets(NuevaData->campo,32,stdin);
    printf("ingrese de que tipo sera el campo (int - char - float, etc.) solo con un caracter: ");
    scanf("%c",NuevaData->tipo);
    
    printf("ingrese la longitud que tendra el campo (cantidad de chars o cantidad de numeros): ");
    scanf("%d",&NuevaData->longitud);
    
    fwrite(NuevaData,sizeof(struct MetaDataRep),1,metadata);

    fclose(metadata);

    return;
}


