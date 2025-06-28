#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BLOCK_SIZE 512


void create_fs(char* name, int numBlocks){

    FILE* fp;
    // Opening file in binary mode
    fp = fopen(name, "wb");
    // Checking if file opened successfully 
    if(fp != NULL){
        printf("Disk file opened successfully!\n");
    }
    else{
        printf("Unable to open disk file!\n");
    }

    char buffer[BLOCK_SIZE];
    // Writing binary data to file
    for(int i = 0; i < numBlocks; i++){
        size_t written = fwrite(buffer, sizeof(char), BLOCK_SIZE, fp);
    }
    fclose(fp);



}

