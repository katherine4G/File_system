#include "FileSystem.h"
#include <iostream>

FileSystem::FileSystem() {
    raiz = std::make_shared<Node>("", false);

    auto documents = std::make_shared<Node>("documents", false);
    auto report2023 = std::make_shared<Node>("report_2023.txt", true);
    auto notes = std::make_shared<Node>("notes.txt", true);
    auto reports = std::make_shared<Node>("reports", false);
    auto summary = std::make_shared<Node>("summary.docx", true);
    auto reportFinal = std::make_shared<Node>("report_final.docx", true);

    documents->agregarHijo(report2023);
    documents->agregarHijo(notes);
    documents->agregarHijo(reports);
    reports->agregarHijo(summary);
    reports->agregarHijo(reportFinal);


    auto images = std::make_shared<Node>("images", false);
    auto vacation = std::make_shared<Node>("vacation.jpg", true);
    auto family = std::make_shared<Node>("family.png", true);
    images->agregarHijo(vacation);
    images->agregarHijo(family);

    raiz->agregarHijo(documents);
    raiz->agregarHijo(images);
}

void FileSystem::imprimirEstructura(const std::shared_ptr<Node>& nodo, const std::string& ruta) const {
    if (!nodo) return; 

    std::string rutaActual = ruta.empty() ? "/" + nodo->getNombre() : ruta + "/" + nodo->getNombre();

    if (nodo->esArchivo()) {
        std::cout << rutaActual << std::endl;
    }
    else {
        for (const auto& hijo : nodo->getHijos()) {
            imprimirEstructura(hijo, rutaActual);
        }
    }
}

std::vector<std::string> FileSystem::buscarArchivosPorPalabraClave(const std::string& palabraClave) const {
    std::vector<std::string> resultados;
    buscarArchivos(raiz, palabraClave, resultados);
    return resultados;
}

std::pair<int, int> FileSystem::contarArchivosYCarpetas() const {
    if (!raiz) return { 0, 0 }; 

    std::pair<int, int> resultado = contarArchivosYCarpetasRecursivo(raiz);
    return { resultado.first, resultado.second - 1 }; // Resto 1 para no contar la raíz como carpeta
}

std::string FileSystem::obtenerArchivoNombreMasLargo() const {
    std::string rutaMasLarga;
    int longitudMax = 0;
    buscarArchivoLargo(raiz, rutaMasLarga, longitudMax);
    return rutaMasLarga;
}

bool FileSystem::eliminarElementoPorNombre(const std::string& nombre) {
    return eliminarRecursivo(raiz, nombre);
}

std::shared_ptr<Node> FileSystem::getRaiz() const {
    return raiz;
}

void FileSystem::imprimirArbol(const std::shared_ptr<Node>& nodo, const std::string& ruta) const {
    if (!nodo) return; 

    std::string rutaActual = ruta + "/" + nodo->getNombre();
    if (nodo->esArchivo()) {
        std::cout << rutaActual << std::endl;
    }
    else {
        for (const auto& hijo : nodo->getHijos()) {
            imprimirArbol(hijo, rutaActual);
        }
    }
}

void FileSystem::buscarArchivos(const std::shared_ptr<Node>& nodo, const std::string& palabraClave, std::vector<std::string>& resultados, const std::string& ruta) const {
    std::string rutaActual = ruta + "/" + nodo->getNombre();

    //  si el nodo es un archivo
    if (nodo->esArchivo()) {
        if (nodo->getNombre().find(palabraClave) != std::string::npos &&
            std::find(resultados.begin(), resultados.end(), rutaActual) == resultados.end()) {
            resultados.push_back(rutaActual);
        }
    }
    // Si el nodo es una carpeta
    else {
        // contiene la palabra clave?
        if (nodo->getNombre().find(palabraClave) != std::string::npos) {

            for (const auto& hijo : nodo->getHijos()) {
                if (hijo->esArchivo()) {
                    std::string rutaHijo = rutaActual + "/" + hijo->getNombre();
                    if (std::find(resultados.begin(), resultados.end(), rutaHijo) == resultados.end()) {
                        resultados.push_back(rutaHijo);
                    }
                }
            }
        }
    }

    // Recorrer a los hijos
    for (const auto& hijo : nodo->getHijos()) {
        buscarArchivos(hijo, palabraClave, resultados, rutaActual);
    }
}




void FileSystem::contarElementos(const std::shared_ptr<Node>& nodo, int& archivos, int& carpetas) const {
    if (!nodo) return; 

    if (nodo->esArchivo()) {
        archivos++;
    }
    else {
        carpetas++;
        for (const auto& hijo : nodo->getHijos()) {
            contarElementos(hijo, archivos, carpetas);
        }
    }
}

void FileSystem::buscarArchivoLargo(const std::shared_ptr<Node>& nodo, std::string& rutaMasLarga, int& longitudMax, const std::string& ruta) const {
    if (!nodo) return; 

    std::string rutaActual = ruta + "/" + nodo->getNombre();
    if (nodo->esArchivo() && nodo->getNombre().length() > longitudMax) {
        longitudMax = nodo->getNombre().length();
        rutaMasLarga = rutaActual;
    }
    else {
        for (const auto& hijo : nodo->getHijos()) {
            buscarArchivoLargo(hijo, rutaMasLarga, longitudMax, rutaActual);
        }
    }
}

std::pair<int, int> FileSystem::contarArchivosYCarpetasRecursivo(const std::shared_ptr<Node>& nodo) const {
    if (!nodo) return { 0, 0 };

    int contadorArchivos = 0;
    int contadorCarpetas = 0;

    if (nodo->esArchivo()) {
        contadorArchivos++;
    }
    else {
        contadorCarpetas++;
        for (const auto& hijo : nodo->getHijos()) {
            std::pair<int, int> resultado = contarArchivosYCarpetasRecursivo(hijo);
            contadorArchivos += resultado.first;
            contadorCarpetas += resultado.second;
        }
    }

    return { contadorArchivos, contadorCarpetas };
}

bool FileSystem::eliminarRecursivo(const std::shared_ptr<Node>& nodo, const std::string& nombre) {
    if (!nodo) return false;

    if (nodo->eliminarHijoPorNombre(nombre)) {
        return true;
    }

    for (const auto& hijo : nodo->getHijos()) {
        if (eliminarRecursivo(hijo, nombre)) {
            return true;
        }
    }
    return false;
}
