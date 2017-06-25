#include "../include/regRecord.h"
#include "../include/regMFT.h"

//carrega a primeira entrada de diretorio e seta o ponteiro para zero
//ass:Nicolas
void loadFirstRecord(REGRECORD *regR, REGMFT *regM){
	read_sector(bootBlock.blocksize * getLBN(regM) , regR->data);
	regR->pointer = 0;	// qual dos 4 diretorios dentro do setor
	regR->sectPointer = 0; // qual dos 4 setores dentro do bloco
	regR->blkPointer = getLBN(regM); 
}

//passa para a proxima entrada de diretorio se puder e retorna 0, 1 caso contrario
//ass:Nicolas
void nextRecord(REGRECORD *regR, REGMFT *regM){
	int i;

	if(regR->pointer < 3){		// pode pegar 4 diretorios dentro de 1 setor
		regR->pointer++;
	}
	else{
		if(regR->sectPointer < bootBlock.blocksize-1){	// pode pegar 4 setores dentro de 1 bloco (geralmente, depende do blocksize)
			regR->pointer = 0;
			regR->sectPointer++;
			read_sector(bootBlock.blocksize * regR.blkPointer + regR.sectPointer , regR->data);
		}
		else{
			if(regR.blkPointer - getLBN(regM) < getCont(regM) - 1){		// temos que pegar o proximo bloco, neste caso ele é contiguo na memoria (está na mesma tupla)
				regR->blkPointer++;
				regR->pointer = 0;
				regR->sectPointer = 0;
			}
			else{			// temos que pegar o proximo bloco mas ele NAO está contiguo, entao pegar a proxima tupla
				if(nextTupla(regM)== OK){
					if(isTuplaChain == OK){
						read_sector(bootBlock.blocksize * getLBN(regM) , regR->data);
						regR->pointer = 0;	
						regR->sectPointer = 0; 
						regR->blkPointer = getLBN(regM);
					}
				}
			}

		}	
	
	}
}

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
int getRecordType(REGRECORD *regR){
	int out=0;
	for(int i=0;i<4;i++){
		out+=regR->data[SIZERECORD*regR->pointer];
	}
	return out;
}

//retorna 1 se a entrada de diretorio indica registro livre, 0 caso contrario
//ass:Nicolas
int isRecordFree(REGRECORD *regR){
	if(getRecordType(regR)==0)
		return OK;
	else return ERRO;
}

//retorna 1 se a entrada de diretorio indica um arquivo, 0 caso contrario
//ass:Nicolas
int isRecordFile(REGRECORD *regR){
	if(getRecordType(regR)==1)
		return OK;
	else return ERRO;
}

//retorna 1 se a entrada de diretorio indica um diretorio, 0 caso contrario
//ass:Nicolas
int isRecordDir(REGRECORD *regR){
	if(getRecordType(regR)==2)
		return OK;
	else return ERRO;
}

//----------------------------------------------------------------------------------------------

//carrega nome de reg, retorna 0 se conseguiu, 1 caso contrario
//ass:Nicolas
int getRecordName(REGRECORD *regR, char *buffer){
	if(strcpy(buffer, regR->data[SIZERECORD*regR->pointer+1]))
		return OK;
	else
		return ERRO;
}

//retorna tamanho total em blocos de reg
//ass:Nicolas
int getBlocksFileSize(REGRECORD *regR){
	int out=0;
	for(int i=0;i<4;i++){
		out+=regR->data[SIZERECORD*regR->pointer+52+i]*256^i;
	}
	return out;
}

//retorna tamanho total em bytes de reg
//ass:Nicolas
int getBytesFileSize(REGRECORD *regR){
	int out=0;
	for(int i=0;i<4;i++){
		out+=regR->data[SIZERECORD*regR->pointer+56+i]*256^i;
	}
	return out;
}

//retorna numero de registro MFT de reg
//ass:Nicolas
int getMFTNumber(REGRECORD *regR){
	int out=0;
	for(int i=0;i<4;i++){
		out+=regR->data[SIZERECORD*regR->pointer+60+i]*256^i;
	}
	return out;
}