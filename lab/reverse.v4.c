#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura para almacenar líneas
typedef struct {
    char **lines;
    size_t count;
    size_t capacity;
} LinesArray;

void init_lines_array(LinesArray *array, size_t initial_capacity) {
    array->lines = malloc(initial_capacity * sizeof(char *));
    if (!array->lines) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    array->count = 0;
    array->capacity = initial_capacity;
}

void add_line(LinesArray *array, char *line) {
    if (array->count >= array->capacity) {
        array->capacity *= 2;
        char **new_lines = realloc(array->lines, array->capacity * sizeof(char *));
        if (!new_lines) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
        array->lines = new_lines;
    }
    array->lines[array->count++] = line;
}

void free_lines_array(LinesArray *array) {
    for (size_t i = 0; i < array->count; i++) {
        free(array->lines[i]);
    }
    free(array->lines);
}

int main(int argc, char *argv[]) {
    // Verificar número de argumentos
	if (argc > 3) {
		fprintf(stderr, "usage: reverse <input> <output>\n");
		exit(1);
	}

    //Valido que los dos archivos sean diferentes
    if (strcmp(argv[1], argv[2]) == 0) {
        fprintf(stderr, "El archivo de entrada y salida deben diferir\n");
        exit(1);
    }

    // Abrir archivo de entrada
    FILE *input = fopen(argv[1], "r");
    if (!input) {
        fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
        exit(1);
    }
    //Abrir archivo de salida
    FILE *output = fopen(argv[2], "w");
    if (!output) {
        fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
        fclose(input);
        exit(1);
    }

    // Declaro los punteros y variable
    LinesArray lines;
    init_lines_array(&lines, 10);

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    //Leo todo el archivo de entrada
    while ((read = getline(&line, &len, input)) != -1) {
        char *line_copy = malloc((read + 1) * sizeof(char));
        if (!line_copy) {
            fprintf(stderr, "malloc failed\n");
            free(line);
            free_lines_array(&lines);
            fclose(input);
            fclose(output);
            exit(1);
        }
        strcpy(line_copy, line);
        add_line(&lines, line_copy);
    }
    free(line);

    //Escribimos en el archivo de salida
    for (size_t i = 0; i < lines.count; i++) {
        fprintf(output, "%s", lines.lines[i]);
    }

    free_lines_array(&lines);
    fclose(input);
    fclose(output);
    return 0;
}
