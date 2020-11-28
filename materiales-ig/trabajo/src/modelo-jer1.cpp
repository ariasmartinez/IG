#include "modelo-jer1.h"
#include "malla-revol.h"




PataSuperior::PataSuperior(int indice, int num_patas){
    ponerColor({0,0,1});
    
   // agregar(MAT_Rotacion(indice*360/num_patas, {0,1,0}));
    agregar(new Bola());
    agregar(MAT_Escalado(0.5,3,0.5));
    agregar(new Cilindro(100,200));
    agregar(MAT_Traslacion(0,3,0));


    
}

PataSuperiorBola::PataSuperiorBola(int indice, int num_patas, Matriz4f *&rot_sup){

    unsigned ind0 = agregar(MAT_Ident());
    
    agregar(new PataSuperior(indice, num_patas));

   
        agregar(MAT_Traslacion(0,3,0));
        agregar(new Bola());
   

   /// agregar(MAT_Rotacion(indice*360/num_patas, {0,1,0}));

    rot_sup = leerPtrMatriz(ind0);

}

PataInferior::PataInferior(int indice, int num_patas, Matriz4f * &rot_inf){
    ponerColor({0,0,1});
   // unsigned ind1 = agregar(MAT_Ident());
    
   // agregar(MAT_Rotacion(indice*360/num_patas, {0,1,0}));
    
    agregar(MAT_Escalado(0.5,3,0.5));
    agregar(new Cilindro(100,200));

    //rot_inf = leerPtrMatriz(ind1);
}


Bola::Bola(){
    Esfera * esf = new Esfera(100, 200);
    esf->colorearEsfera();
    agregar(MAT_Escalado(0.5,0.5,0.5));
    agregar(esf);
}


//ConjuntoPatas::ConjuntoPatas(){

//}

Pulpo::Pulpo(int num_patas){
    
    Conjunto * c = new Conjunto(rot_sup, rot_inf, num_patas);
     for (int i = 0; i< num_patas; i++){
        agregar(c);
        agregar(MAT_Rotacion(360/num_patas, {0,1,0}));
    }

   
   
}


Conjunto::Conjunto(Matriz4f * &rot_sup, Matriz4f * &rot_inf, int num_patas){
   

    Bola * bol = new Bola();

   
    agregar(bol);
     unsigned ind1 = agregar(MAT_Ident());
    agregar(MAT_Traslacion(0,0.25,0));
    
    PataInferior * pat_inf = new PataInferior(0, num_patas, rot_sup);
    
    for (int i = 0; i < num_patas; i++){
       // agregar(MAT_Rotacion(360/num_patas, {0,1,0}));
        agregar(pat_inf);
    }
    agregar(MAT_Traslacion(0,3,0));
   
    
    PataSuperiorBola * pat_sup = new PataSuperiorBola(0, num_patas, rot_sup);
    for (int i = 0; i < num_patas; i++){
       // agregar(MAT_Rotacion(360/num_patas, {0,1,0}));
        //agregar(new PataSuperiorBola(i, num_patas, rot_sup));
        agregar(pat_sup);
    }
   


   rot_inf = leerPtrMatriz(ind1);
}


unsigned Pulpo::leerNumParametros() const{
    return 1;
}

void Pulpo::actualizarEstadoParametro(const unsigned iParam, const float tSec){
   //assert((iParam < leerNumParametros()) && (iParam >= 0));
   float nuevo_valor;
   switch(iParam){
       case 0:
           fijarRot(tSec);
       break;
   }
}

void Pulpo::fijarRot(int nuevo_valor){
    *rot_inf = MAT_Rotacion(45-45*sin(nuevo_valor), {0,0,1});     
    *rot_sup = MAT_Rotacion(-2*(45-45*sin(nuevo_valor)), {0,0,1});
}

void Pulpo::fijarRotInf(int nuevo_valor){
    *rot_inf = MAT_Rotacion(45-45*sin(2*nuevo_valor), {0,0,1});
}