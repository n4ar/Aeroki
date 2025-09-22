#include "Aeroki.h"

#define MAX_VARIABLES 100

typedef struct {
    char name[32];
    int value;
} Variable;

Variable variables[MAX_VARIABLES];
int var_count = 0;

int get_variable(const char *name) {
    for (int i = 0; i < var_count; ++i) {
        if (strcmp(variables[i].name, name) == 0) {
            return variables[i].value;
        }
    }
    fprintf(stderr, "Variable not found: %s\n", name);
    exit(1);
}

void set_variable(const char *name, int value) {
    for (int i = 0; i < var_count; ++i) {
        if (strcmp(variables[i].name, name) == 0) {
            variables[i].value = value;
            return;
        }
    }

    if (var_count < MAX_VARIABLES) {
        strcpy(variables[var_count].name, name);
        variables[var_count].value = value;
        var_count++;
    } else {
        fprintf(stderr, "Too many variables.\n");
        exit(1);
    }
}

void handle_ha(char *line) {
    char left[32], right[32];
    char op;

    if (sscanf(line, "หา %[^+*/-]%c%[^\n]", left, &op, right) == 3) {
        int a = get_variable(left);
        int b = get_variable(right);
        int result = 0;

        switch (op) {
            case '+': result = a + b; break;
            case '-': result = a - b; break;
            case '*': result = a * b; break;
            case '/': result = (b != 0) ? a / b : 0; break;
            default: return;
        }

        printf("%d\n", result);
    } else if (sscanf(line, "หา %s", left) == 1) {
        int a = get_variable(left);
        printf("%d\n", a);
    }
}

void handle_hai(char *line) {
    char varname[32];
    int value;

    if (sscanf(line, "ให้ %s = %d", varname, &value) == 2) {
        set_variable(varname, value);
    }
}

void handle_rubkum(char *line) {
    char varname[32];
    if (sscanf(line, "รับค่า %s", varname) == 1) {
        int value;
        printf("กรอกค่า %s: ", varname);
        if (scanf("%d", &value) == 1) {
            set_variable(varname, value);
        } else {
            int c; while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}

static void ltrim(char *str) {
    int index = 0;
    while (str[index] == ' ' || str[index] == '\t') index++;
    if (index > 0) {
        int i = 0;
        while (str[index]) str[i++] = str[index++];
        str[i] = '\0';
    }
}

void __Ark_Interpreted(FILE *__src_file) {
    char line[256];
    while (fgets(line, sizeof(line), __src_file)) {
        line[strcspn(line, "\n")] = '\0';

        if (strncmp(line, "ให้ ", strlen("ให้ ")) == 0) {
            handle_hai(line);
        } else if (strncmp(line, "หา ", strlen("หา ")) == 0) {
            handle_ha(line);
        } else if (strncmp(line, "รับค่า ", strlen("รับค่า ")) == 0) {
            handle_rubkum(line);
        }
    }
}

void __Ark_Shell() {
    char line[256];

    printf("Aeroki Shell Mode (type 'ออก' to exit)\n");

    while (1) {
        printf(">>> ");
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL) break;

        line[strcspn(line, "\n")] = '\0';
        ltrim(line);

        if (strcmp(line, "ออก") == 0) break;

        if (strncmp(line, "ให้ ", strlen("ให้ ")) == 0) {
            handle_hai(line);
        } else if (strncmp(line, "หา ", strlen("หา ")) == 0) {
            handle_ha(line);
        } else if (strncmp(line, "รับค่า", strlen("รับค่า")) == 0) {
            handle_rubkum(line);
        } else if (line[0] != '\0') {
            printf("Unknown command: %s\n", line);
        }
    }

    printf("Exited shell mode.\n");
}
