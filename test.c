#include <stdio.h>

//TODO: tests should be performed on each options to create group of manipulators.
//file has only the tests that result should be "yes", other should result "no" for test to pass.
//for no tests are performed only on cases in the file.

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
        if (line[0] != '#') {
            sprintf(command, "./app 1 %s", line);
            printf("run: %s", command);
            pd = popen(command, "r");
            if (fgets(res_str, sizeof(res_str), pd) == NULL) {
                printf("error\n");
                return 1;
            }
            pclose(pd);
            if (!strcmp(res_str, "no")) {
                printf("failed, run with debug:\n");
                command[6] = '2';
                printf("run: %s\n", command);
                system(command);
                return 1;
                command[6] = '1';
            } else {
                printf("pass\n");
            }
        }
    }
    fclose(fd);
    return 0;
}
