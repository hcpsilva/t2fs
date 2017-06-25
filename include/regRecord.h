#include <stdio.h>
#include "../include/diskio.h"
#include "../include/auxlib2.h"
#include "../include/apidisk.h"

#define SIZERECORD 64


typedef struct {
	byte data[SECTOR_SIZE];
	int pointer=0;	 //qual dos 4 diretorios dentro do setor
	int dirPointer = 0;
	int blkPointer = 0;
}REGRECORD;


//carrega a primeira entrada de diretorio e seta o ponteiro para zero
//ass:Nicolas
void loadFirstRecord(REGRECORD *regR, REGMFT *regM);

//passa para a proxima entrada de diretorio se puder e retorna 0, 1 caso contrario
//ass:Nicolas
void nextRecord(REGRECORD *regR, REGMFT *regM);

//passa para a entrada de diretorio anterior se puder e retorna 0, 1 caso contrario
//ass:Nicolas
//int backRecord(REGRECORD *regR, REGMFT *regM);

//----------------------------------------------------------------------------------------------
/*Type
	 0: registro invalido (livre)
	 1: arquivo regular (file)
	 2:	arquivo de diretorio (dir)
*/
//retorna o tipo da entrada de diretorio. gg litle-endian
//ass:Nicolas
int getRecordType(REGRECORD *regR);

//retorna 1 se a entrada de diretorio indica registro livre, 0 caso contrario
//ass:Nicolas
int isRecordFree(REGRECORD *regR);

//retorna 1 se a entrada de diretorio indica um arquivo, 0 caso contrario
//ass:Nicolas
int isRecordFile(REGRECORD *regR);

//retorna 1 se a entrada de diretorio indica um diretorio, 0 caso contrario
//ass:Nicolas
int isRecordDir(REGRECORD *regR);

//----------------------------------------------------------------------------------------------

//retorna nome de reg
//ass:Nicolas
int getRecordName(REGRECORD *regR, char *buffer);

//retorna tamanho total em blocos de reg
//ass:Nicolas
int getBlocksFileSize(REGRECORD *regR);

//retorna tamanho total em bytes de reg
//ass:Nicolas
int getBytesFileSize(REGRECORD *regR);

//retorna numero de registro MFT de reg
//ass:Nicolas
int getMFTNumber(REGRECORD *regR);