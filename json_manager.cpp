#include "json_manager.h"
#include <fstream>
#include <sstream>
#include <iostream>

// util indent
static std::string indent(int n) { return std::string(n, ' '); }

// convertir nodo -> json manual
static void nodeToJson(std::ofstream& f, Node* n, int tab) {
    f << "{\n";
    f << indent(tab+2) << "\"id\": " << n->id << ",\n";
    f << indent(tab+2) << "\"nombre\": \"" << n->nombre << "\",\n";
    f << indent(tab+2) << "\"tipo\": \"" << (n->tipo == NodeType::CARPETA ? "carpeta" : "archivo") << "\",\n";
    f << indent(tab+2) << "\"contenido\": \"" << n->contenido << "\",\n";
    f << indent(tab+2) << "\"children\": [\n";
    for (size_t i = 0; i < n->children.size(); ++i) {
        nodeToJson(f, n->children[i], tab+4);
        if (i+1 < n->children.size()) f << ",\n";
        else f << "\n";
    }
    f << indent(tab+2) << "]\n";
    f << indent(tab) << "}";
}

// parser simple: lee desde stream ya posicionado en '{' y construye Node*
static Node* readNode(std::istream& in) {
    std::string token;
    // consume '{' (may be adjacent)
    char ch;
    in >> ch;
    if (ch != '{') return nullptr;

    int id = -1;
    std::string nombre, tipoStr, contenido;
    std::vector<Node*> children;

    std::string line;
    while (std::getline(in, line)) {
        // trim left spaces:
        size_t p = line.find_first_not_of(" \t\r\n");
        if (p == std::string::npos) continue;
        std::string s = line.substr(p);

        if (s.rfind("\"id\"",0) == 0) {
            size_t pos = s.find(':'); if (pos!=std::string::npos) {
                std::string val = s.substr(pos+1);
                id = std::stoi(val);
            }
        } else if (s.rfind("\"nombre\"",0) == 0) {
            size_t p1 = s.find('"', s.find(':'));
            size_t p2 = s.find('"', p1+1);
            nombre = s.substr(p1+1, p2-p1-1);
        } else if (s.rfind("\"tipo\"",0) == 0) {
            size_t p1 = s.find('"', s.find(':'));
            size_t p2 = s.find('"', p1+1);
            tipoStr = s.substr(p1+1, p2-p1-1);
        } else if (s.rfind("\"contenido\"",0) == 0) {
            size_t p1 = s.find('"', s.find(':'));
            size_t p2 = s.find('"', p1+1);
            contenido = s.substr(p1+1, p2-p1-1);
        } else if (s.rfind("\"children\"",0) == 0) {
            // next lines contain children array; read until ']'
            // read line until encountering '[' then parse children blocks
            while (std::getline(in, line)) {
                size_t q = line.find_first_not_of(" \t\r\n");
                if (q==std::string::npos) continue;
                std::string t = line.substr(q);
                if (t.size()>0 && t[0]=='[') {
                    // start children
                    break;
                }
            }
            // read children elements: look for '{' start and ']' end
            while (true) {
                // peek next non-space char
                char c;
                while (in.get(c)) {
                    if (!isspace((unsigned char)c)) { in.unget(); break; }
                }
                int next = in.peek();
                if (next == ']') { // end of children
                    std::getline(in, line); // consume ]
                    break;
                }
                if (next == '{') {
                    Node* child = readNode(in);
                    if (child) children.push_back(child);
                    // after readNode, there may be a comma or newline; consume until next non-space
                    char cc;
                    while (in.get(cc)) {
                        if (cc==',' ) break;
                        if (!isspace((unsigned char)cc)) { in.unget(); break; }
                    }
                } else {
                    // consume line and continue
                    if (!std::getline(in, line)) break;
                }
            }
        } else if (s.size()>0 && s[0]=='}') {
            // end of this node
            Node* n = new Node(id, nombre, (tipoStr=="carpeta"?NodeType::CARPETA:NodeType::ARCHIVO));
            n->contenido = contenido;
            for (Node* c : children) n->addChild(c);
            return n;
        }
    }
    return nullptr;
}

// ----------------- API -----------------
bool JSONManager::save(const std::string& filename, Tree& tree) {
    std::ofstream f(filename);
    if (!f.is_open()) return false;
    f << "{\n";
    f << "\"root\": ";
    nodeToJson(f, tree.getRoot(), 0);
    f << "\n}\n";
    f.close();
    return true;
}

bool JSONManager::load(const std::string& filename, Tree& tree) {
    std::ifstream f(filename);
    if (!f.is_open()) return false;
    // read entire file into stringstream for easier parsing with getline
    std::stringstream ss;
    ss << f.rdbuf();
    std::string content = ss.str();
    std::istringstream in(content);
    // find "root" and the first '{' after it
    size_t pos = content.find("\"root\"");
    if (pos == std::string::npos) return false;
    size_t brace = content.find('{', pos);
    if (brace == std::string::npos) return false;
    // create substring starting at brace and parse using istringstream advanced to that position
    std::istringstream in2(content.substr(brace));
    Node* newRoot = readNode(in2);
    if (!newRoot) return false;
    tree.setRoot(newRoot);
    return true;
}
