#include "grafo-escena.h"



class Pulpo: public NodoGrafoEscena{
    protected:
        Matriz4f * rot_sup = nullptr;
        Matriz4f * rot_inf = nullptr;
    public:
        Pulpo(int num_patas);
        unsigned leerNumParametros() const;
        void actualizarEstadoParametro(const unsigned iParam, const float tSec);
        void fijarRot(int nuevo_valor);
        void fijarRotInf(int nuevo_valor);
};

class Conjunto: public NodoGrafoEscena{
    public:
        Conjunto(Matriz4f * &rot_sup, Matriz4f * &rot_inf, int num_patas);
};

class PataSuperior: public NodoGrafoEscena{
    public:
        PataSuperior(int indice, int num_patas);
};

class PataSuperiorBola: public NodoGrafoEscena{
    public:
        PataSuperiorBola(int indice, int num_patas,Matriz4f * &rot);
};

class PataInferior: public NodoGrafoEscena{
    public:
        PataInferior(int indice, int num_patas,Matriz4f * &rot);
};

class Bola: public NodoGrafoEscena{
    private:
    int num_patas;
    public:
        Bola();
};

