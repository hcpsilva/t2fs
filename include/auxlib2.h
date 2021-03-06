#ifndef _HAS_AUXLIB2_H
#define _HAS_AUXLIB2_H

#include <stdio.h>
//#include <string.h>

#include "lista.h"
//#include "regMFT.h"
#include "t2fs.h"
#include "regRecord.h"

#define IS_DIR 3
#define IS_FILE 5
#define MISSING_FILE -2
#define ERRO -3
#define OK 0
#define CARACTERES_VALIDOS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.0123456789"

typedef struct {
    DIR2 handle;
    int numMFT;
    char path[200];
    int currentPointer; // pode ficar maior ( ͡° ͜ʖ ͡°)
} ODIN;

typedef struct {
    FILE2 handle;
    int numMFT;
    char path[200];
    int currentPointer; // pode ficar maior ( ͡° ͜ʖ ͡°)²
    int estaAberto;
} OFILE;

struct t2fs_bootBlock bootBlock;

OFILE arquivosAbertos[20];
LISTA *diretoriosAbertos;

// int handleUltraMasterGenerator;

int openSpots();

int isValidPath(char caminho[]);

int fileExists(char caminho[], REGRECORD **regRout, REGMFT *regMout, REGRECORD **regRout2);

int findFreeMFT();

int loadBootBlock();

// ass:Gabriel
int writeNewRecord(char *name, int numMFT, REGRECORD *regR, REGMFT *regM, REGRECORD *regAvo, int tipo);

// ass:gabriel
int getHandle();

// ass:gabriel
void initLib();

// ass:gabriel
int readBlock(REGMFT regM, int VBN, char *buffer);

// ass: henrique
int writeBlock(REGMFT regM, int VBN, char *buffer);

//---------------------Funcs de lista-------------------------
// ass: gabriel o obstinado

ODIN *findDir(DIR2 handle);

int isOpenDir(char *pathname);

DIR2 insertDir(int numMFT, char *pathname);

int removeDirByHandle(DIR2 handle);

int removeDirByPath(char *pathname);
//-----------------------------------------------------------

#endif //_HAS_AUXLIB2_H
