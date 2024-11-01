
#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "Node.h"
#include <string>
#include <vector>

class FileSystem {
public:
    FileSystem();

    void imprimirEstructura(const std::shared_ptr<Node>& nodo, const std::string& ruta) const;
    std::vector<std::string> buscarArchivosPorPalabraClave(const std::string& palabraClave) const;
    std::pair<int, int> contarArchivosYCarpetas() const;
    std::string obtenerArchivoNombreMasLargo() const;
    bool eliminarElementoPorNombre(const std::string& nombre);
    std::shared_ptr<Node> getRaiz() const;

private:
    std::shared_ptr<Node> raiz;
    std::pair<int, int> contarArchivosYCarpetasRecursivo(const std::shared_ptr<Node>& nodo) const;
    void imprimirArbol(const std::shared_ptr<Node>& nodo, const std::string& ruta = "") const;
    void buscarArchivos(const std::shared_ptr<Node>& nodo, const std::string& palabraClave, std::vector<std::string>& resultados, const std::string& ruta = "") const;
    void contarElementos(const std::shared_ptr<Node>& nodo, int& archivos, int& carpetas) const;
    void buscarArchivoLargo(const std::shared_ptr<Node>& nodo, std::string& rutaMasLarga, int& longitudMax, const std::string& ruta = "") const;
    bool eliminarRecursivo(const std::shared_ptr<Node>& nodo, const std::string& nombre);
    

};

#endif
