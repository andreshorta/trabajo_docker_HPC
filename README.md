# trabajo_docker_HPC
# Cálculo Paralelo de π con MPI

## Introducción
Este proyecto se enfoca en calcular el valor aproximado de π utilizando el método de la serie de Leibniz para sumar una serie infinita. La implementación se realiza de manera eficiente mediante el uso de procesamiento en paralelo con MPI (Message Passing Interface). MPI es una biblioteca estándar de comunicación para programas paralelos en clústeres de computadoras.

## Estructura del Proyecto
El proyecto se estructura en torno a un contenedor Docker, que encapsula la aplicación y sus dependencias. A continuación, se describen los componentes principales del proyecto:

### Dockerfile
El Dockerfile especifica los pasos necesarios para construir la imagen del contenedor. Se utiliza una imagen base de Ubuntu y se instalan MPI y el compilador de C. Luego, se copia el código fuente del programa y se compila.

### docker-compose.yml
El archivo docker-compose.yml define los servicios necesarios para ejecutar el programa en paralelo con MPI. En este caso, se define un servicio para el proceso maestro. El número de procesadores utilizados para la ejecución se puede modificar fácilmente cambiando el valor después del parámetro -n en el comando mpirun. Por ejemplo, para utilizar más procesadores, se puede aumentar este valor a -n1, -n2, -n3 etc.

### Código Fuente (calcular_pi.c)
El programa en C implementa la lógica para calcular el valor aproximado de π en paralelo utilizando MPI. Se divide el trabajo entre varios procesos, cada uno de los cuales calcula una parte de la suma total. El proceso principal (proceso 0) recolecta los resultados parciales de todos los procesos, realiza la suma final y calcula el valor aproximado de π.

## Ejecución del Proyecto
Para ejecutar el proyecto, sigue estos pasos:

1. Asegúrate de tener Docker instalado en tu sistema.
2. Abre una terminal y navega hasta el directorio que contiene los archivos del proyecto.
3. Ejecuta el siguiente comando `docker-compose up --build` para construir la imagen del contenedor.
4. 
#### Modificación del Archivo docker-compose.yml
Para ejecutar el programa con diferentes números de procesadores, se deben realizar las siguientes modificaciones en el archivo `docker-compose.yml`:

```yaml
version: "3"
services:
  proceso_maestro:
    build: .
    command: mpirun -n 1 ./calcular_pi

### Ejecución con un procesador:
mpirun -n 1 ./calcular_pi
### Ejecución con un procesador:
mpirun -n 2 ./calcular_pi
### Ejecución con un procesador:
mpirun -n 3 ./calcular_pi
