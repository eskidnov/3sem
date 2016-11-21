#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
//#include "stack.c"

//struct Stack paths;

void find(char *path, int depth, char *filename);

int main(int *argc, char *argv[]) {
    char *s = (char *)malloc(1000);
    strcpy(s, argv[1]);
    find(s, atoi(argv[2]), argv[3]);
    return 0;
}

void find(char *path, int depth, char *filename) {
    DIR *dir;
    struct dirent *dirp;
    struct stat sb;
    char *currentPath = (char*) malloc(1000);
            
    if (depth == 0) {
        return;
    }

    dir = opendir(path);

    if (dir == NULL) {
        printf("Error\n");
        exit(-1);
    }

    while ((dirp = readdir(dir)) != NULL) {

        if (!strcmp(dirp->d_name, ".") || !strcmp(dirp->d_name, ".."))
            continue;

        strcpy(currentPath, path);
        strcat(currentPath, "/");
        strcat(currentPath, dirp->d_name);

        stat(currentPath, &sb);
            
        if (S_ISDIR(sb.st_mode)) {
            strcat(path, "/");
            strcat(path, dirp->d_name);
            //push(paths, path);
            find(path, depth - 1, filename);
            path[strlen(path) - strlen(dirp->d_name) - 1] = '\0';
        }

        if (!strcmp(filename, dirp->d_name))
            printf("%s\n", path);
    
    }         

    (void) closedir(dir);

    free(currentPath); 
}
