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

typedef struct{
    int numFNT;
    int numDABPT;
    int fntstart;
    int dabptstart;
    int bptrstart;
}DiskMeta;

int numFNT;
int numDABPT;
int fntstart;
int dabptstart;
int bptrstart;


FILE* diskFile = NULL;
char currentuser[50] = "filler";

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
    diskFile = fp;

    char buffer[BLOCK_SIZE];
    memset(buffer, 0, BLOCK_SIZE);
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
        return;
    }
    fntstart = 1;


    // Calculating how many FNT entries fit in one block
    int fntentries = BLOCK_SIZE / sizeof(FNT);

    numFNT = (numOfFilenames + fntentries - 1) / fntentries;

    // Calculating how many DABPT entries per block
    int dabptentries = BLOCK_SIZE / sizeof(DABPT);

    numDABPT = (numOfDabpt + dabptentries - 1) / dabptentries;

    dabptstart = fntstart + numFNT;
    bptrstart = dabptstart + numDABPT;

    DiskMeta meta = {
    .numFNT = numFNT,
    .numDABPT = numDABPT,
    .fntstart = fntstart,
    .dabptstart = dabptstart,
    .bptrstart = bptrstart
    };

    fseek(fp, 0, SEEK_SET);
    fwrite(&meta, sizeof(DiskMeta), 1, fp);

    // Starting at beginning of FNT
    fseek(fp, fntstart * BLOCK_SIZE, SEEK_SET);

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
        printf("Writting data......");
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

        DiskMeta meta;
        fread(&meta, sizeof(DiskMeta), 1, fp);

        numFNT = meta.numFNT;
        numDABPT = meta.numDABPT;
        fntstart = meta.fntstart;
        dabptstart = meta.dabptstart;
        bptrstart = meta.bptrstart;



        // fseek sets pointer position
        fseek(fp, 0, SEEK_SET);

        int entriesPerBlock = BLOCK_SIZE / sizeof(FNT);
        int totalFNT = numFNT * entriesPerBlock;

        for(int i = 0; i < totalFNT; i++){
            FNT entry = {0};
            // fread advances position each time
            fseek(fp, fntstart * BLOCK_SIZE + i * sizeof(FNT), SEEK_SET);
            fread(&entry, sizeof(FNT), 1, fp);

            if(entry.inodeptr != -1){
                DABPT data;
                int offset = (dabptstart * BLOCK_SIZE) + (entry.inodeptr * sizeof(DABPT));
                fseek(fp, offset, SEEK_SET);
                fread(&data, sizeof(DABPT), 1, fp);
                //printf("entry.inodeptr = %d\n", entry.inodeptr);

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
void renamefs(char* oldname, char* newname, char* diskname, int fntstart){

    FILE* fp = fopen(diskname, "r+b");
    if (!fp) {
        printf("Unable to open disk file!\n");
        return;
    }

    DiskMeta meta;
    fseek(fp, 0, SEEK_SET);
    if (fread(&meta, sizeof(DiskMeta), 1, fp) != 1) {
        printf("Failed to read disk metadata\n");
        fclose(fp);
        return;
    }

    int entriesPerBlock = BLOCK_SIZE / sizeof(FNT);
    int totalFNT = meta.numFNT * entriesPerBlock;
    FNT entry;

    for (int i = 0; i < totalFNT; i++) {
        fseek(fp, meta.fntstart * BLOCK_SIZE + i * sizeof(FNT), SEEK_SET);
        fread(&entry, sizeof(FNT), 1, fp);

        if (entry.inodeptr != -1 && strcmp(entry.filename, oldname) == 0) {
            // Update filename
            strncpy(entry.filename, newname, sizeof(entry.filename));
            entry.filename[sizeof(entry.filename) - 1] = '\0';

            fseek(fp, meta.fntstart * BLOCK_SIZE + i * sizeof(FNT), SEEK_SET);
            fwrite(&entry, sizeof(FNT), 1, fp);

            printf("File: %s was renamed to %s!\n", oldname, newname);
            fclose(fp);
            return;
        }
    }
    printf("Unable to find file!\n");
    fclose(fp);
}

void putfs(char* diskname, char* name){

struct stat st;
    if (stat(name, &st) != 0) {
        printf("Unable to stat source file!\n");
        return;
    }
    int size = st.st_size;
    FILE* fp = fopen(name, "rb");
    if(fp == NULL){
        printf("Unable to open source file!\n");
        return;
    }
    FILE* disk = fopen(diskname, "r+b");
    if(disk == NULL) {
        printf("Unable to open disk file!\n");
        fclose(fp);
        return;
    }
    DiskMeta meta;
    fseek(disk, 0, SEEK_SET);
    if (fread(&meta, sizeof(DiskMeta), 1, disk) != 1) {
        printf("Failed to read disk metadata\n");
        fclose(fp);
        fclose(disk);
        return;
    }
    int entriesPerBlock = BLOCK_SIZE / sizeof(FNT);
    int totalFNT = meta.numFNT * entriesPerBlock;
    int dabptEntriesPerBlock = BLOCK_SIZE / sizeof(DABPT);
    int totalDABPT = meta.numDABPT * dabptEntriesPerBlock;
    int bptsEntriesPerBlock = BLOCK_SIZE / sizeof(BPTS);
    int totalBPTS = bptsEntriesPerBlock; // Only 1 block for BPTS for now
    // Find a free FNT entry
    FNT entry = {0};
    int fntIndex = -1;
    for(int i = 0; i < totalFNT; i++){
        fseek(disk, meta.fntstart * BLOCK_SIZE + i * sizeof(FNT), SEEK_SET);
        fread(&entry, sizeof(FNT), 1, disk);
        if(entry.inodeptr == -1){
            fntIndex = i;
            break;
        }
    }
    if(fntIndex == -1){
        printf("No free FNT entry available.\n");
        fclose(fp);
        fclose(disk);
        return;
    }
    // Find a free DABPT entry
    DABPT data = {0};
    int dabptIndex = -1;
    for(int i = 0; i < totalDABPT; i++){
        fseek(disk, meta.dabptstart * BLOCK_SIZE + i * sizeof(DABPT), SEEK_SET);
        fread(&data, sizeof(DABPT), 1, disk);
        if(data.blockptr == -1){
            dabptIndex = i;
            break;
        }
    }
    if(dabptIndex == -1){
        printf("No free DABPT entry available.\n");
        fclose(fp);
        fclose(disk);
        return;
    }
    // Find a free BPTS entry
    BPTS bpt = {0};
    int bptsIndex = -1;
    for(int i = 0; i < totalBPTS; i++){
        fseek(disk, meta.bptrstart * BLOCK_SIZE + i * sizeof(BPTS), SEEK_SET);
        fread(&bpt, sizeof(BPTS), 1, disk);
        int isFree = 1;
        for(int j = 0; j < 8; j++){
            if(bpt.blockptrs[j] != 0 && bpt.blockptrs[j] != -1){
                isFree = 0;
                break;
            }
        }
        if(isFree){
            bptsIndex = i;
            break;
        }
    }
    if(bptsIndex == -1){
        printf("No free BPTS entry available.\n");
        fclose(fp);
        fclose(disk);
        return;
    }
    // Allocate data blocks (naive: just use next available blocks after bptrstart)
    int blocks = (size + BLOCK_SIZE - 1) / BLOCK_SIZE;
    int datastart = meta.bptrstart + totalBPTS;
    int dataBlockIndices[8];
    for(int i = 0; i < blocks; i++){
        dataBlockIndices[i] = datastart + bptsIndex * 8 + i;
    }
    // Write file data to disk blocks
    char buffer[BLOCK_SIZE];
    for(int i = 0; i < blocks; i++){
        size_t bytesRead = fread(buffer, 1, BLOCK_SIZE, fp);
        fseek(disk, dataBlockIndices[i] * BLOCK_SIZE, SEEK_SET);
        fwrite(buffer, 1, bytesRead, disk);
    }
    // Write BPTS entry
    for(int i = 0; i < 8; i++){
        if(i < blocks)
            bpt.blockptrs[i] = dataBlockIndices[i];
        else
            bpt.blockptrs[i] = -1;
    }
    fseek(disk, meta.bptrstart * BLOCK_SIZE + bptsIndex * sizeof(BPTS), SEEK_SET);
    fwrite(&bpt, sizeof(BPTS), 1, disk);
    // Write DABPT entry
    data.fileSize = size;
    data.mod = time(NULL);
    data.blockptr = bptsIndex;
    strncpy(data.username, currentuser, sizeof(data.username));
    data.username[sizeof(data.username) - 1] = '\0';
    fseek(disk, meta.dabptstart * BLOCK_SIZE + dabptIndex * sizeof(DABPT), SEEK_SET);
    fwrite(&data, sizeof(DABPT), 1, disk);
    // Write FNT entry
    // Store only the base filename
    const char* base = strrchr(name, '/');
    if (!base) base = strrchr(name, '\\');
    if (!base) base = name; else base++;
    memset(&entry, 0, sizeof(FNT));
    strncpy(entry.filename, base, sizeof(entry.filename));
    entry.filename[sizeof(entry.filename) - 1] = '\0';
    entry.inodeptr = dabptIndex;
    fseek(disk, meta.fntstart * BLOCK_SIZE + fntIndex * sizeof(FNT), SEEK_SET);
    fwrite(&entry, sizeof(FNT), 1, disk);
    printf("File was successfully stored!\n");
    fclose(fp);
    fclose(disk);
}

void userfs(char* username){
    strncpy(currentuser, username, sizeof(currentuser));
    currentuser[sizeof(currentuser) - 1] ='\0';
    printf("The User is set to: %s\n", currentuser);
}





