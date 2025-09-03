#include <stdio.h>  
#include <fcntl.h>  
#include <unistd.h> 
#include <string.h> 
#include <errno.h>  

int main() {
    const char *nombre_archivo = "mi_texto_usuario.txt";
    int fd; 
    char buffer_input[256]; 

    
    printf("Escribe el texto que quieres guardar en el archivo: ");
    
    
    
    if (fgets(buffer_input, sizeof(buffer_input), stdin) == NULL) {
        perror("Error al leer la entrada");
        return 1;
    }

    buffer_input[strcspn(buffer_input, "\n")] = 0;

    
    fd = open(nombre_archivo, O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if (fd == -1) {
        perror("Error al crear/abrir el archivo para escritura");
        return 1; 
    }
    
    
    ssize_t bytes_escritos = write(fd, buffer_input, strlen(buffer_input));

    if (bytes_escritos == -1) {
        perror("Error al escribir en el archivo");
        close(fd);
        return 1;
    }

    printf("\n✅ Se guardó tu texto en '%s'.\n", nombre_archivo);
    
    close(fd); 

    printf("--------------------------------------\n");

    
    fd = open(nombre_archivo, O_RDONLY);
    
    if (fd == -1) {
        perror("Error al abrir el archivo para lectura");
        return 1;
    }

    char buffer_lectura[256]; 
    ssize_t bytes_leidos = read(fd, buffer_lectura, sizeof(buffer_lectura) - 1);

    if (bytes_leidos == -1) {
        perror("Error al leer el archivo");
        close(fd);
        return 1;
    }
    
    buffer_lectura[bytes_leidos] = '\0'; 
    
    close(fd); 

    
    printf("📄 Contenido leído del archivo:\n");
    printf("'%s'\n", buffer_lectura);

    return 0;
}
