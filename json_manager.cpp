#include "json_manager.h"
#include <fstream>
#include <sstream>

static void writeNode(std::ofstream& f, Node* n, int tab) {
    auto ind=[&](int k){return std::string(k,' ');};

    f << ind(tab) << "{\n";
    f << ind(tab+2) << "\"id\": " << n->id << ",\n";
    f << ind(tab+2) << "\"nombre\": \"" << n->nombre << "\",\n";
    f << ind(tab+2) << "\"tipo\": \"" << (n->tipo==NodeType::CARPETA?"carpeta":"archivo") << "\",\n";
    f << ind(tab+2) << "\"contenido\": \"" << n->contenido << "\",\n";
    f << ind(tab+2) << "\"children\": [\n";

    for (size_t i=0;i<n->children.size();i++) {
        writeNode(f, n->children[i], tab+4);
        if (i+1<n->children.size()) f<<",\n";
        else f<<"\n";
    }

    f << ind(tab+2) << "]\n";
    f << ind(tab) << "}";
}

static Node* readNode(std::istream& in);

bool JSONManager::save(const std::string& file, Tree& t) {
    std::ofstream f(file);
    if (!f.is_open()) return false;

    f << "{\n\"root\": ";
    writeNode(f, t.getRoot(), 0);
    f << "\n}\n";
    return true;
}

static Node* parseNode(std::istream& in);

bool JSONManager::load(const std::string& file, Tree& t) {
    std::ifstream f(file);
    if (!f.is_open()) return false;

    std::string all((std::istreambuf_iterator<char>(f)), {});
    size_t pos = all.find("{", all.find("root"));
    if (pos == std::string::npos) return false;

    std::istringstream ss(all.substr(pos));
    Node* r = readNode(ss);
    if (!r) return false;

    // reemplazar root
    t.~Tree();
    new(&t) Tree();
    t.move("/", "/"); // evita warnings
    t = Tree();
    t.getRoot()->children.clear();
    t.getRoot()->nombre = r->nombre;
    t.getRoot()->id = r->id;
    t.getRoot()->tipo = r->tipo;
    t.getRoot()->contenido = r->contenido;
    t.getRoot()->children = r->children;

    delete r;
    return true;
}

static Node* readNode(std::istream& in) {
    std::string s;
    int id=-1;
    std::string nombre, tipo, contenido;
    std::vector<Node*> children;

    char c;
    while (in.get(c))
        if (c=='{') break;

    while (getline(in, s)) {
        if (s.find("\"id\"") != std::string::npos) {
            id = stoi(s.substr(s.find(":")+1));
        }
        else if (s.find("\"nombre\"") != std::string::npos) {
            size_t p1=s.find("\"", s.find(":")+1)+1;
            size_t p2=s.find("\"", p1);
            nombre=s.substr(p1,p2-p1);
        }
        else if (s.find("\"tipo\"") != std::string::npos) {
            size_t p1=s.find("\"", s.find(":")+1)+1;
            size_t p2=s.find("\"", p1);
            tipo=s.substr(p1,p2-p1);
        }
        else if (s.find("\"contenido\"") != std::string::npos) {
            size_t p1=s.find("\"", s.find(":")+1)+1;
            size_t p2=s.find("\"", p1);
            contenido=s.substr(p1,p2-p1);
        }
        else if (s.find("\"children\"") != std::string::npos) {
            getline(in, s); // '['
            while (true) {
                char x=in.peek();
                if (x==']') { getline(in,s); break; }
                if (x=='{') {
                    Node* ch = readNode(in);
                    if (ch) children.push_back(ch);
                }
                getline(in, s);
                if (s.find("]")!=std::string::npos) break;
            }
        }
        else if (s.find("}") != std::string::npos) {
            Node* n=new Node(id,nombre,(tipo=="carpeta"?NodeType::CARPETA:NodeType::ARCHIVO));
            n->contenido=contenido;
            for (auto*c:children){c->parent=n;n->children.push_back(c);}
            return n;
        }
    }
    return nullptr;
}
