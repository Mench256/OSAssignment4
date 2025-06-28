// Abraham Menchaca, 1002167812, CSE3320-002

// Sites used
// https://www.geeksforgeeks.org/command-line-arguments-in-c-cpp/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>





int main(int argc, char *argv[]){


// Checking for correct number of arguments

// createfs command
if(strcmp(argv[1], "createfs") == 0){
    if(argc != 4){
        printf("Please provide the correct number of arguments!\n");
    }
}

// formatfs command
if(strcmp(argv[1], "formatfs") == 0){
    if(argc != 4){
        printf("Please provide the correct number of arguments!\n");
    }
}

// savefs command
if(strcmp(argv[1], "savefs") == 0){
    if(argc != 3){
        printf("Please provide the correct number of arguments!\n");
    }
}

// openfs command
if(strcmp(argv[1], "openfs") == 0){
    if(argc != 3){
        printf("Please provide the correct number of arguments!\n");
    }
}

// list command
if(strcmp(argv[1], "list") == 0){
    if(argc != 2){
        printf("Please provide the correct number of arguments!\n");
    }
}

// remove command
if(strcmp(argv[1], "remove") == 0){
    if(argc != 3){
        printf("Please provide the correct number of arguments!\n");
    }
}

// rename command
if(strcmp(argv[1], "rename") == 0){
    if(argc != 4){
        printf("Please provide the correct number of arguments!\n");
    }
}

// put command
if(strcmp(argv[1], "put") == 0){
    if(argc != 3){
        printf("Please provide the correct number of arguments!\n");
    }
}

// get command
if(strcmp(argv[1], "get") == 0){
    if(argc != 3){
        printf("Please provide the correct number of arguments!\n");
    }
}

// user command
if(strcmp(argv[1], "user") == 0){
    if(argc != 3){
        printf("Please provide the correct number of arguments!\n");
    }
}

// link command
if(strcmp(argv[1], "link") == 0){
    if(argc != 3){
        printf("Please provide the correct number of arguments!\n");
    }
}


// unlink command
if(strcmp(argv[1], "unlink") == 0){
    if(argc != 3){
        printf("Please provide the correct number of arguments!\n");
    }
}


    return 0;
}