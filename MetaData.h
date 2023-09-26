#ifndef METADATA_H
#define METADATA_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct MetaDataRep;
typedef struct MetaDataRep *MetaData;

struct MetaDataRep{
    
    char campo[32];
    char tipo;
    int longitud;

};



void crear_archivo();

void CargarMetaData();



#endif // metadata