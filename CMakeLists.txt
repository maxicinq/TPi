# Mínima versión de CMake requerida.
cmake_minimum_required(VERSION 3.6)
# Nombre del proyecto. En general va a ser el mismo que el nombre 
# del directorio en donde está el CMakeLists.txt. 
project(solucion)

# Versión de C++ a utilizar. En Algoritmos 1 usamos C++11.
set(CMAKE_CXX_STANDARD 11)

# Agrega como parte del proyecto al subdirectorio de googletest,
# e incluye los archivos de headers de googletest al proyecto.
# Para hacer esto, primero se debería extraer el archivo
# lib/googletest-master.rar en la carpeta lib.
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)

# Dice cuáles son los archivos que van a tener el código
# de nuestro proyecto. Acá solo hace falta poner los .cpp.
# OJO: Hay que poner los .cpp con el directorio en el que están
# adentro del proyecto.
set(SOURCE_FILES main.cpp ejercicios.cpp auxiliares.cpp
        definiciones.h
        tests/ej1TEST.cpp
        tests/ej2TEST.cpp
        tests/ej3TEST.cpp
        tests/ej4TEST.cpp
        tests/ej5TEST.cpp
        tests/ej6TEST.cpp
)

# Dice cuál va a ser el nombre del archivo ejecutable,
# y qué .cpp va a tener. Acá le decimos que se va a llamar solucion,
# y que va a tener los archivos .cpp
# que estén en la variable SOURCE_FILES, que seteamos en la línea anterior. 
add_executable(solucion ${SOURCE_FILES})

# Agrega más opciones a la compilación.
# -g: Hace que podamos debuggear el programa.
# --coverage: Hace que se pueda calcular el cubrimiento de los casos de test.
set(CMAKE_CXX_FLAGS "-g --coverage")
# Un temita de gcov que no se lleva tan bien con CMake,
# y entonces hay que poner esta línea.
# Para más información, ver https://texus.me/2015/09/06/cmake-and-gcov/.
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

# Acá le decimos que ponga nuestro ejecutable en la misma
# carpeta en la que está el CMakeLists.txt.
# Esto es para que no lo ponga en la carpeta CMakeFiles.
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

# Acá le decimos que use las bibliotecas de gtest.
# Necesario si estamos usando gtest.
target_link_libraries(solucion gtest gtest_main)

