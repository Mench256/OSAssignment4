#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
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

// global variables
int numFNT = 0;
int numDABPT = 0;
int fntstart = 0;
int dabptstart = 0;
int bptrstart = 0;
FILE* diskFile = NULL;

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
void formatfs(char* name, int numOfFilenames, int numOfDabpt){

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

    numFNT = (numOfFilenames + fntentries - 1) / fntentries;

    // Calculating how many DABPT entries per block
    int dabptentries = BLOCK_SIZE / sizeof(DABPT);

    numDABPT = (numOfDabpt + dabptentries - 1) / dabptentries;

    dabptstart = fntstart + numFNT;
    bptrstart = dabptstart + numDABPT;

    // Starting at beginning of FNT
    fseek(fp, 0, SEEK_SET);

    // Zeroing out FNT
    for(int i = 0; i < numOfFilenames; i++){
        FNT entry;

        memset(entry.filename, 0, sizeof(entry.filename));
        entry.inodeptr = -1;

        fwrite(&entry, sizeof(FNT), 1, fp);
    }

    // Starting at begining of DABPT
    fseek(fp, dabptstart * BLOCK_SIZE, SEEK_SET);
    // Zeroing out DABPT 
    for(int i = 0; i < numOfDabpt; i++){
        DABPT data;

        data.fileSize = 0;
        data.mod = 0;
        data.blockptr = -1;
        memset(data.username, 0, sizeof(data.username));
        fwrite(&data, sizeof(DABPT), 1, fp);
    }

    fclose(fp);
}
// list
void list(char* name){

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
        int totalFNT = numFNT * entriesPerBlock;

        printf("%d", totalFNT);
        for(int i = 0; i < totalFNT; i++){
            printf("Hello from the for loop!\n");
            FNT entry;
            // fread advances position each time
            fseek(fp, fntstart * BLOCK_SIZE + i * sizeof(FNT), SEEK_SET);
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


}
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

void removefs(char* name, int entries, char* removeFile){

FILE* fp;

fp = fopen(name, "r+b");

if(fp != NULL){
    printf("Disk file opened successfully!\n");
}
else{
    printf("Unable to open disk file!\n");
}

for(int i = 0; i < entries; i++){
    FNT entry;

    fread(&entry, sizeof(FNT), 1, fp);

    if(strcmp(entry.filename, removeFile) == 0 && entry.inodeptr != -1){

        entry.inodeptr = -1;
        
        int offset = i * sizeof(FNT);
        fseek(fp, offset, SEEK_SET);
        fwrite(&entry, sizeof(FNT), 1, fp);
        break;
        

    }
}
}
// Openfs
void openfs(char* name, int numBlocks){


diskFile = fopen(name, "rb");

if(diskFile != NULL){
    printf("Disk file opend successfully!\n");
}
else{
    printf("Unable to open disk file!\n");
}

}

// rename 
/*void renamefs(char* oldname, char* newname, int numBlocks, FILE* fp, int fntstart){

    FNT entry;

    int fntentries = numBlocks * (BLOCK_SIZE / sizeof(FNT));

    for(int i = 0; i < fntentries; i++){

        fseek(fp, fntstart * BLOCK_SIZE + i, sizeof(FNT), SEEK_SET);
        fread(&entry, sizeof(FNT), 1, fp);

        if(strcmp(entry.filename, oldname) == 0){
            strncpy(entry.filename, newname, sizeof(entry.filename));
            fseek(fp, fntstart * BLOCK_SIZE * i sizeof(FNT), SEEK_SET);
            fwrite(&entry, sizeof(FNT), 1, fp);
            printf("File: %s was renamed to %s!\n", oldname, newname);
            return;
        }
    }
    printf("Unable to find file!\n");
}*/

void putfs(char* name){


    struct stat st;

    stat(name, &st);
    int size = st.st_size;

    FILE* fp;

    fp = fopen(name, "rb");

    if(fp != NULL){
        printf("Disk file opend successfully!\n");
    }
    else{
        printf("Unable to open disk file!\n");
    }
    char* buffer = malloc(size);
    fread(buffer, 1, size, fp);
    fclose(fp);

    FILE* disk = fopen("disk1", "r+b");
    int blocks = (size + BLOCK_SIZE - 1) / BLOCK_SIZE;
    int datastart = fntstart + numFNT + numDABPT + 2;

    for(int i= 0; i < blocks; i++){
        fseek(disk, (datastart + i) * BLOCK_SIZE, SEEK_SET);
        fwrite(buffer + i * BLOCK_SIZE, 1, BLOCK_SIZE, disk);
    }


    BPTS bpt;

    for(int i = 0; i < blocks; i++){
        bpt.blockptrs[i] = datastart + i;
    }
    for(int i = blocks; i < 8; i++){
        bpt.blockptrs[i] = -1;
    }
    fseek(disk, bptrstart * BLOCK_SIZE, SEEK_SET);
    fwrite(&bpt, sizeof(BPTS), 1, disk);

    DABPT data;
    data.fileSize = size;
    data.mod = time(NULL);
    data.blockptr = 0;

    // Make sure to change to username later
    strncpy(data.username, "filler", sizeof("filler"));

    fseek(disk, dabptstart * BLOCK_SIZE, SEEK_SET);
    fwrite(&data, sizeof(DABPT), 1, disk);

    FNT entry;

    strncpy(entry.filename, name, sizeof(entry.filename));
    entry.inodeptr = 0;
    fseek(disk, fntstart * BLOCK_SIZE, SEEK_SET);
    fwrite(&entry, sizeof(FNT), 1, disk);

}





