// Abraham Menchaca

// Sites used
// https://www.geeksforgeeks.org/command-line-arguments-in-c-cpp/
// https://www.youtube.com/watch?v=5bFBn_UpItA
// https://www.tutorialspoint.com/c_standard_library/c_function_fwrite.htm
// https://www.tutorialspoint.com/c_standard_library/c_function_fread.htm
// https://www.geeksforgeeks.org/fseek-in-c-with-example/
// https://www.geeksforgeeks.org/c/memset-c-example/
// https://stackoverflow.com/questions/238603/how-can-i-get-a-files-size-in-c

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// Function declarations
void create_fs(char* name, int numBlocks);
void list(char* name);
void savefs(char* name, int numBlocks);
void removefs(char* name, int entries, char* removeFile);
void formatfs(char* name, int numOfFilenames, int numOfDabpt);
void openfs(char* name, int numBlocks);
void renamefs(char* oldname, char* newname, int numBlocks, FILE* fp, int fntstart);
void putfs(char* name);


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
   // removefs(argv[2], atoi(argv[3]), argv[4], name, 0);
}

// rename command
else if(strcmp(argv[1], "renamefs") == 0){
    if(argc < 4){
        printf("Please provide the correct number of arguments!\n");
    }
    // setting this to zero for now but name sure to fix later
   // renamefs(argv[2], argv[3], globalNumBlocks, name, 0);
}

// put command
else if(strcmp(argv[1], "putfs") == 0){
    if(argc != 3){
        printf("Please provide the correct number of arguments!\n");
    }

    putfs(argv[2]);
}

// get command
else if(strcmp(argv[1], "get") == 0){
    if(argc < 3){
        printf("Please provide the correct number of arguments!\n");
    }
}

// user command
else if(strcmp(argv[1], "user") == 0){
    if(argc < 3){
        printf("Please provide the correct number of arguments!\n");
    }
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
    printf("Command now found!\n");
}

    return 0;
}
