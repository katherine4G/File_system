#include "FileSystem.h"
#include <iostream>
#include <locale>

int main() {

    std::locale::global(std::locale("es_ES.UTF-8")); 

    std::cout.imbue(std::locale()); 


    FileSystem sistema;

    // Tosos los archivos existentes
    std::cout << "Estructura inicial del sistema de archivos:" << std::endl;
    sistema.imprimirEstructura(sistema.getRaiz(), ""); 

    // 1. Explorar el sistema de archivos para encontrar archivos por palabra clave 
    std::string palabraClave = "report";

    std::cout << "\nArchivos que contienen '" << palabraClave << "':" << std::endl;
    auto resultadosBusqueda = sistema.buscarArchivosPorPalabraClave(palabraClave);
    for (const auto& ruta : resultadosBusqueda) {
        std::cout << ruta << std::endl;
    }

    // 2. Contar la cantidad de archivos y carpetas en el sistema 
    std::pair<int, int> resultado = sistema.contarArchivosYCarpetas();
    std::cout << "\nConteo de archivos y carpetas:" << std::endl;
    std::cout << "Archivos: " << resultado.first << std::endl;
    std::cout << "Carpetas: " << resultado.second << std::endl;

    // 3. Obtener el archivo con el nombre más largo 
    auto archivoLargo = sistema.obtenerArchivoNombreMasLargo();
    std::cout << "\nArchivo con el nombre más largo: " << archivoLargo << std::endl;

    // 4. Eliminar un archivo o carpeta específico 
    std::string nombreEliminar = "notes.txt";
    if (sistema.eliminarElementoPorNombre(nombreEliminar)) {
        std::cout << "\nEliminado: " << nombreEliminar << std::endl;
    }
    else {
        std::cout << "\nNo se encontró: " << nombreEliminar << std::endl;
    }

 
    std::cout << "\nSistema de archivos recargado después de la eliminación:" << std::endl;
    sistema.imprimirEstructura(sistema.getRaiz(), ""); // Llama a la función con los parámetros necesarios

    return 0;
}
