#include <stdio.h>
#include <string.h>

// Function to print the content of a given file
void printFileContent(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Error opening file");
        return;
    }

    char ch;
    // Loop through each character in the file until EOF and print it
    while ((ch = fgetc(f)) != EOF) {
        putchar(ch);
    }
    printf("\n");

    // Close the file after reading its contents
    fclose(f);
}

// Function to concatenate the content of source File into destination File
void concatenateFiles(const char *destFile, const char *srcFile) {
    // Open destFile in append mode
    FILE *dest = fopen(destFile, "a");
    // Open srcFile in read mode
    FILE *src = fopen(srcFile, "r");

    if (dest == NULL || src == NULL) {
        printf("Error opening file");
        return;
    }

    char ch;
    // Read each character from source File and write it to destination File
    while ((ch = fgetc(src)) != EOF) {
        fputc(ch, dest);
    }

    // Close both files after operations
    fclose(src);
    fclose(dest);
}

int main(int argc, char *argv[]) {
    // Check if the user provides the command to display the content of "file"
    if (argc == 2 && strcmp(argv[1], "$") == 0) {
        printFileContent("file");
    }
    // Check if the user provides two filenames as arguments
    else if (argc == 3) {
        // Check if both filenames are identical
        if (strcmp(argv[1], argv[2]) == 0) {
            printf("Error: Both filenames are the same.\n");
            return 1;
        }

        // Concatenate the contents of the second file into the first
        concatenateFiles(argv[1], argv[2]);
    }
    // If the user provides incorrect number of arguments, display usage instructions
    else {
        printf("Usage: %s [destination file] [source file]\n", argv[0]);
        printf("Or: %s $\n", argv[0]);
        return 1;
    }

    return 0;
}
