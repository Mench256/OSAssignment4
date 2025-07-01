// Abraham Menchaca, 1002167812, CSE3320-002

// Sites used
// https://www.geeksforgeeks.org/command-line-arguments-in-c-cpp/
// https://www.youtube.com/watch?v=5bFBn_UpItA
// https://www.tutorialspoint.com/c_standard_library/c_function_fwrite.htm
// https://www.tutorialspoint.com/c_standard_library/c_function_fread.htm
// https://www.geeksforgeeks.org/fseek-in-c-with-example/
// https://www.geeksforgeeks.org/c/memset-c-example/
// https://stackoverflow.com/questions/238603/how-can-i-get-a-files-size-in-c
/*
To compile :
gcc -o fs driver.c fs.c

File system command syntax
-----------------------------

createfs <diskname> <numBlocks>
formatfs <diskname> <numFNT> <numDABPT>
openfs <diskname> <numBlocks>
savefs <diskname> <numBlocks>
list <diskname>
removefs <diskname> <filename> <numFNT>
renamefs <oldname> <newname> <diskname> 0
putfs <diskname> <host_filename>
getfs <diskname> <filename_in_disk>
userfs <username>
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// Function declarations
void create_fs(char* name, int numBlocks);
void list(char* name);
void savefs(char* name, int numBlocks);
void removefs(char* name, char* removeFile, int entries);
void formatfs(char* name, int numOfFilenames, int numOfDabpt);
void openfs(char* name, int numBlocks);
void renamefs(char* oldname, char* newname, char* diskname, int fntstart);
void putfs(char* diskname, char* name);
void userfs(char* username);
void getfs(char* name, char* filename);


int main(int argc, char *argv[]){


// Checking for correct number of arguments

// createfs command
if(strcmp(argv[1], "createfs") == 0){
    if(argc < 4){
        printf("Please provide the correct number of arguments!\n");
    }


    create_fs(argv[2], atoi(argv[3]));
}

// formatfs command
else if(strcmp(argv[1], "formatfs") == 0){
    if(argc < 4){
        printf("Please provide the correct number of arguments!\n");
    }
    formatfs(argv[2], atoi(argv[3]),atoi(argv[4]));
}

// savefs command
else if(strcmp(argv[1], "savefs") == 0){
    if(argc != 4){
        printf("Please provide the correct number of arguments!\n");
        return 1;
    }
    savefs(argv[2], atoi(argv[3]));
}

// openfs command
else if(strcmp(argv[1], "openfs") == 0){
    if(argc < 3){
        printf("Please provide the correct number of arguments!\n");
    }
    openfs(argv[2], atoi(argv[3]));
}

// list command
else if(strcmp(argv[1], "list") == 0){
    if(argc < 2){
        printf("Please provide the correct number of arguments!\n");
    }
    list(argv[2]);
}

// remove command
else if(strcmp(argv[1], "removefs") == 0){
    if(argc < 3){
        printf("Please provide the correct number of arguments!\n");
    }
   removefs(argv[2], argv[3], atoi(argv[3]));
}

// rename command
else if(strcmp(argv[1], "renamefs") == 0){
    if(argc < 4){
        printf("Please provide the correct number of arguments!\n");
    }
    renamefs(argv[2], argv[3], argv[4], 0);
}

// put command
else if(strcmp(argv[1], "putfs") == 0){
    if(argc != 4){
        printf("Please provide the correct number of arguments!\n");
        return 1;
    }

    putfs(argv[2], argv[3]);
}

// get command
else if(strcmp(argv[1], "getfs") == 0){
    if(argc < 3){
        printf("Please provide the correct number of arguments!\n");
        return 1;
    }
    getfs(argv[2], argv[3]);
}

// user command
else if(strcmp(argv[1], "userfs") == 0){
    if(argc < 3){
        printf("Please provide the correct number of arguments!\n");
        return 1;
    }
    userfs(argv[2]);
}

// link command
else if(strcmp(argv[1], "link") == 0){
    if(argc < 3){
        printf("Please provide the correct number of arguments!\n");
    }
}


// unlink command
else if(strcmp(argv[1], "unlink") == 0){
    if(argc < 3){
        printf("Please provide the correct number of arguments!\n");
    }
}

else{
    printf("Command not found!\n");
}

    return 0;
}