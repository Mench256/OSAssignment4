#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define BLOCK_SIZE 512

typedef struct{
    int fileSize;
    time_t  mod;
    int blockptr;
    char username[50];
}DABPT;

typedef struct{
    char filename[54];
    int inodeptr;
}FNT;

typedef struct{
    int blockptrs[8];
}BPTS;

// creatfs 
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

// formatfs
/*void format_fs(char* name, int numOfFilenames, int numOfDabpt){

    FILE* fp;
    fp = fopen(name, "r+b");

    if(fp != NULL){
        printf("Disk file opened successfully!\n");
    }
    else{
        printf("Unable to open disk file!\n");
    }

    // Calculating how many FNT entries fit in one block
    int fntentries = BLOCK_SIZE / sizeof(FNT);

    int numFNT = (numOfFilenames + fntentries - 1) / fntentries;

    // Calculating how many DABPT entries per block
    int dabptentries = BLOCK_SIZE / sizeof(DABPT);

    int numDABPT = (numOfDabpt + dabptentries - 1) / dabptentries;

    int fntstart = 0;
    int dabptstart = fntstart + numFNT;
    int bptrstart = dabptstart + numDABPT;


}*/
// list
/*void list(char* name, int entries){

        FILE* fp;

        fp = fopen(name, "rb");
        
        if(fp != NULL){
            printf("Disfile opened successfully!\n");
        }
        else{
            printf("Unable to open diskfile!\n");
        }



        // fseek sets pointer position
        fseek(fp, 0, SEEK_SET);

        int entriesPerBlock = BLOCK_SIZE / sizeof(FNT);
        int numFNT = (entries + entriesPerBlock - 1) / entriesPerBlock;
        int fntstart = 0;
        int dabptstart = fntstart + numFNT;
    
        for(int i = 0; i < entries; i++){
            FNT entry;
            // fread advances position each time
            fread(&entry, sizeof(FNT), 1, fp);

            if(entry.inodeptr != -1){
                DABPT data;
                int offset = (dabptstart * BLOCK_SIZE) + (entry.inodeptr * sizeof(DABPT));
                fseek(fp, offset, SEEK_SET);
                fread(&data, sizeof(DABPT), 1, fp);

                printf("Filename: %s   Last Modified: %s   Username: %s\n", entry.filename, ctime(&data.mod), data.username);
            }
        }
        fclose(fp);


}*/
void savefs(char* name, int numBlocks){

FILE* fp;
FILE* des;

fp = fopen(name, "rb");

if(fp != NULL){
    printf("Disk file opened successfully!\n");
}
else{
    printf("Unable to open disk file!\n");
}

des = fopen("Destination_disk", "wb");

if(des != NULL){
    printf("Disk file opened successfully!\n");
}
else{
    printf("Unable to open disk file!\n");
}

char buffer[BLOCK_SIZE];

for(int i = 0; i < numBlocks; i++){

        fread(buffer,BLOCK_SIZE, 1,  fp);
        fwrite(buffer, BLOCK_SIZE, 1,  des);

    
}
fclose(fp);
fclose(des);



}



