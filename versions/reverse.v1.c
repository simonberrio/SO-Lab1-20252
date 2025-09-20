#include <stdio.h>
#include <stdlib.h>

// Función principal
int main(int argc, char *argv[]) {
    FILE *input = stdin;

    // Verificar número de argumentos
	if (argc > 3) {
		fprintf(stderr, "usage: reverse <input> <output>\n");
		exit(1);
	}

    // Abrir archivo de entrada
    input = fopen(argv[1], "r");
    if (!input) {
        fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
        exit(1);
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, input)) != -1) {
        //Imprimo en pantalla
        fprintf(stdout, "%s", line);
    }
    free(line);
    fclose(input);
    return 0;
}
