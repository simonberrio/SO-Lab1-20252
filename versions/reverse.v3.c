#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    // Reservamos un array fijo para almacenar punteros a líneas
    const size_t MAX_LINES = 10;
    char *lines[MAX_LINES];
    size_t count = 0;

    // Declaro los punteros y variable
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    //Leo todo el archivo de entrada
    while ((read = getline(&line, &len, input)) != -1) {
        // Reservar memoria para cada línea
        char *line_copy = malloc((read + 1) * sizeof(char));
        if (!line_copy) {
            fprintf(stderr, "malloc failed\n");
            // liberar lo que ya tenemos
            for (size_t i = 0; i < count; i++) {
                free(lines[i]);
            }
            free(line);
            fclose(input);
            fclose(output);
            exit(1);
        }
        strcpy(line_copy, line);
        lines[count++] = line_copy;

        if (count >= MAX_LINES) {
            fprintf(stderr, "Se alcanzó el número máximo de líneas soportadas\n");
            break;
        }
    }
    free(line);
    //Escribir desde lo que se guardo en memoria y por ahí derecho liberarla
    for (size_t i = 0; i < count; i++) {
        fprintf(output, "%s", lines[i]);
        free(lines[i]);
    }

    fclose(input);
    fclose(output);
    return 0;
}
