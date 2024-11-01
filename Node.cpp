#include "Node.h"

Node::Node(const std::string& nombre, bool esArchivo) : nombre(nombre), archivo(esArchivo) {}

void Node::agregarHijo(std::shared_ptr<Node> hijo) {
    hijos.push_back(hijo);
}

std::string Node::getNombre() const {
    return nombre;
}

bool Node::esArchivo() const {
    return archivo;
}

const std::vector<std::shared_ptr<Node>>& Node::getHijos() const {
    return hijos;
}

bool Node::eliminarHijoPorNombre(const std::string& nombre) {
    for (auto it = hijos.begin(); it != hijos.end(); ++it) {
        if ((*it)->getNombre() == nombre) {
            hijos.erase(it);
            return true;
        }
    }
    return false;
}

