#ifndef NODO_H
#define NODO_H

#include <string>
#include <vector>
#include <memory>

class Node {
public:
    Node(const std::string& nombre, bool esArchivo);

    void agregarHijo(std::shared_ptr<Node> hijo);
    std::string getNombre() const;
    bool esArchivo() const;
    const std::vector<std::shared_ptr<Node>>& getHijos() const;
    bool eliminarHijoPorNombre(const std::string& nombre);
private:
    std::string nombre;
    bool archivo;
    std::vector<std::shared_ptr<Node>> hijos;
  
};

#endif 

