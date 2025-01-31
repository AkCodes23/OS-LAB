#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <ctype.h>
#include <time.h>
#include <sys/wait.h>

void ls_l();
void cp(char *source, char *destination);
void wc(char *filename);
void print_file_info(struct stat *file_stat);

int main() {
    int choice;
    char source[100], destination[100], filename[100];

    while(1) {
        printf("\n--- Menu ---\n");
        printf("1. ls -l\n");
        printf("2. cp\n");
        printf("3. wc\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                ls_l();
                break;
            case 2:
                printf("Enter source file: ");
                scanf("%s", source);
                printf("Enter destination file: ");
                scanf("%s", destination);
                cp(source, destination);
                break;
            case 3:
                printf("Enter filename: ");
                scanf("%s", filename);
                wc(filename);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

void ls_l() {
    struct dirent *de;
    struct stat file_stat;
    DIR *dr = opendir(".");

    if (dr == NULL) {
        printf("Could not open current directory");
        return;
    }

    while ((de = readdir(dr)) != NULL) {
        if (stat(de->d_name, &file_stat) == -1) {
            perror("stat");
            continue;
        }
        print_file_info(&file_stat);
        printf(" %s\n", de->d_name);
    }

    closedir(dr);
}

void print_file_info(struct stat *file_stat) {
    printf((S_ISDIR(file_stat->st_mode)) ? "d" : "-");
    printf((file_stat->st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stat->st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stat->st_mode & S_IXUSR) ? "x" : "-");
    printf((file_stat->st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stat->st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stat->st_mode & S_IXGRP) ? "x" : "-");
    printf((file_stat->st_mode & S_IROTH) ? "r" : "-");
    printf((file_stat->st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stat->st_mode & S_IXOTH) ? "x" : "-");
    printf(" %ld", file_stat->st_nlink);
    printf(" %s", getpwuid(file_stat->st_uid)->pw_name);
    printf(" %s", getgrgid(file_stat->st_gid)->gr_name);
    printf(" %ld", file_stat->st_size);
    printf(" %s", ctime(&file_stat->st_mtime));
}

void cp(char *source, char *destination) {
    FILE *src, *dst;
    char ch;

    src = fopen(source, "r");
    if (src == NULL) {
        perror("Error opening source file");
        return;
    }

    dst = fopen(destination, "w");
    if (dst == NULL) {
        perror("Error opening destination file");
        fclose(src);
        return;
    }

    while ((ch = fgetc(src)) != EOF) {
        fputc(ch, dst);
    }

    fclose(src);
    fclose(dst);
    printf("File copied successfully.\n");
}

void wc(char *filename) {
    FILE *fp;
    char ch;
    int lines = 0, words = 0, chars = 0;
    int in_word = 0;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    while ((ch = fgetc(fp)) != EOF) {
        chars++;
        if (ch == '\n') {
            lines++;
        }
        if (isspace(ch)) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            words++;
        }
    }

    fclose(fp);
    printf("Lines: %d Words: %d Characters: %d\n", lines, words, chars);
}
