Cada versión esta dentro de la carpeta de versions.
Primera versión: Abrir archivo de entrada, leerlo con getline y escribirlo en consola
<img width="974" height="153" alt="image" src="https://github.com/user-attachments/assets/73924823-54ee-46d0-8321-3473580fb4a8" />
<img width="1107" height="285" alt="image" src="https://github.com/user-attachments/assets/33ad41ec-b094-40d4-a829-3a103efcf0d9" />

Segunda versión: Leer de un archivo de entrada y escribir en archivo de salida
<img width="1204" height="258" alt="image" src="https://github.com/user-attachments/assets/df65e3de-c509-44dc-8113-ef8428638ff4" />
<img width="571" height="132" alt="image" src="https://github.com/user-attachments/assets/b4742100-f0ae-4504-bdf0-619cb3d0c302" />

Tercera versión: Guardar en memoria lo leído en el archivo
<img width="1752" height="313" alt="image" src="https://github.com/user-attachments/assets/f7418e91-befe-4f51-aa5c-c11e1b102bae" />
<img width="525" height="184" alt="image" src="https://github.com/user-attachments/assets/c99ed653-70e9-4465-94b4-a3ed78dcabc0" />

Cuarte versión: Guardado en memoria dinamicamente
<img width="1741" height="167" alt="image" src="https://github.com/user-attachments/assets/f170a012-0152-4993-8f4f-68affa4fc926" />
<img width="492" height="200" alt="image" src="https://github.com/user-attachments/assets/ead6e8e0-5753-44c6-8dda-067b3e0ccc25" />

Versión final: Escribiendo en sentido contrario
<img width="1133" height="67" alt="image" src="https://github.com/user-attachments/assets/04b74957-b35f-4d71-a75d-b43853c29408" />

Ya ejecutando las pruebas:
<img width="1168" height="707" alt="image" src="https://github.com/user-attachments/assets/1c8576d0-d59f-424a-974b-58371ded6118" />
Nos dimos cuenta que la prueba 2 falló y buscamos el error y era por que no se estaba mandando el arg[2] y fallaba el programa en:
if (strcmp(argv[1], argv[2]) == 0) {
y se cambió para que quede así:
if (argc == 3 && strcmp(argv[1], argv[2]) == 0) {
Y se volvió a ejecutar el run-tests.sh y el resultado cambió al siguiente:
<img width="999" height="424" alt="image" src="https://github.com/user-attachments/assets/19e6f230-97ff-4beb-a6eb-ec34a26578fb" />
De nuevo se corrigió el mensaje de error cuando los dos archivos son iguales y se volvió a correr el test
<img width="1095" height="675" alt="image" src="https://github.com/user-attachments/assets/eded60e2-f9c5-4fcb-857e-63f2e36fdf6f" />
Para el error del test 5, en vez de solo comparar nombres de archivo, hay que comparar el inodo y dispositivo de ambos ficheros quedando la comparación así:
//Valido que los dos archivos sean diferentes
    if (argc == 3) {
        struct stat st_in, st_out;
        if (stat(argv[1], &st_in) == 0 && stat(argv[2], &st_out) == 0) {
            if (st_in.st_dev == st_out.st_dev && st_in.st_ino == st_out.st_ino) {
                fprintf(stderr, "reverse: input and output file must differ\n");
                exit(1);
            }
        }
    }

Para finalmente ejecutar el tester y lograr 
<img width="940" height="453" alt="image" src="https://github.com/user-attachments/assets/54d71580-8fa0-4e20-9f7f-341ead37fadc" />

