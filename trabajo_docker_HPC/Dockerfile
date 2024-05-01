# Usa una imagen base de Ubuntu
FROM ubuntu:latest

# Instala MPI y el compilador de C
RUN apt-get update && \
    apt-get install -y mpich gcc && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

# Copia el código fuente del programa
COPY calcular_pi.c /app/

# Compila el programa
WORKDIR /app
RUN mpicc calcular_pi.c -o calcular_pi

# Comando por defecto para ejecutar el programa
CMD ["./calcular_pi"]
