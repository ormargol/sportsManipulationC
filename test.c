#include <stdio.h>

int main(int argc, char** argv) {
    ssize_t read;
    char *line = NULL;
    size_t len = 0;
    char command[100];
    char res_str[3];
    if (argc <= 1) {
        printf("Error\n");
        return 1;
    }
    FILE *fd = fopen(argv[1], "r");
    if (fd == NULL) {
        printf("error\n");
        return 1;
    }
    FILE *pd;
    while ((read = getline(&line, &len, fd)) != -1) {
        if (line == NULL) {
            printf("line=NULL\n");
        }
        printf("line: %s", line);
        if (line[0] != '#') {
            sprintf(command, "./app T %s", line);
            printf("run: %s\n", command);
            pd = popen(command, "r");
            if (fgets(res_str, sizeof(res_str), pd) == NULL) {
                printf("error\n");
                return 1;
            }
            pclose(pd);
            if (!strcmp(res_str, "no!")) {
                command[6] = 'D';
                printf("run: %s\n", command);
                system(command);
                command[6] = 'T';
            }
        }
    }
    fclose(fd);
    return 0;
}
