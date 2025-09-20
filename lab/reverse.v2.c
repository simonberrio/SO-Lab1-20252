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

    // Declaro los punteros y variable
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    //Leo todo el archivo de entrada
    while ((read = getline(&line, &len, input)) != -1) {
        //Imprimo en el archivo de salida y en pantalla
        fprintf(output, "%s", line);
        fprintf(stdout, "%s", line);
    }
    free(line);
    fclose(input);
    fclose(output);
    return 0;
}
