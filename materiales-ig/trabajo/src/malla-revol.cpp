// *********************************************************************
// **
// ** Informática Gráfica, curso 2019-20
// ** Implementación de la clase 'MallaRevol'
// **
// *********************************************************************

#include "ig-aux.h"
#include "tuplasg.h"
#include "lector-ply.h"
#include "matrices-tr.h"
#include "malla-revol.h"
#include <stdlib.h>

using namespace std ;

// *****************************************************************************




// Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
// a partir de un perfil y el número de copias que queremos de dicho perfil.
void MallaRevol::inicializar
(
   const std::vector<Tupla3f> & perfil,     // tabla de vértices del perfil original
   const unsigned               num_copias  // número de copias del perfil
)
{
   // COMPLETAR: Práctica 2: completar: creación de la malla....

   //perfil.size(); -> num vertices? (m)?
   //num_copias -> n?
   
   //creación de tabla de vértices
   Tupla3f q;
   double angulo;
   //Matriz4f matriz_rotacion;
   
   for (double i = 0; i < num_copias; i++){
      for (double j = 0; j < perfil.size(); j++){
         //vertice obtenido tras rotar pj un angulo igual a 2ipi/(n-1) radianes
         angulo = 2*i*180/(num_copias-1);
         
         //matriz_rotacion = MAT_Rotacion(angulo, perfil[j](X), perfil[j](Y), perfil[j](Z));
         
         q = MAT_Rotacion(angulo, {0,1,0})*perfil[j];
         
         vertices.push_back(q);
      }
   }

  


   double k;
   for (int i = 0; i < (num_copias-1); i++){
      for (int j = 0; j < (perfil.size()-1); j++){
         k = i*perfil.size()+j;
         //triangulo formado por k, k+m, k+m+1
         //Tupla3i triangulo1(k, k+perfil.size(), k+perfil.size()+1);
         triangulos.push_back({k, k+perfil.size(), k+perfil.size()+1});
         //Tupla3i triangulo2(k, k+perfil.size()+1, k+1);
         triangulos.push_back({k, k+perfil.size()+1, k+1});

      }
   }
   

}

// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY

MallaRevolPLY::MallaRevolPLY
(
   const std::string & nombre_arch,
   const unsigned      nperfiles
)
{
   ponerNombre( std::string("malla por revolución del perfil en '"+ nombre_arch + "'" ));
   // COMPLETAR: práctica 2: crear la malla de revolución
   // Leer los vértice del perfil desde un PLY, después llamar a 'inicializar'
   // ...........................
   vector<Tupla3f> perfil;
   LeerVerticesPLY(nombre_arch, perfil);
   inicializar(perfil, nperfiles);

}


Cilindro::Cilindro(const int num_verts_per, const unsigned nperfiles) : MallaRevol()
{
   ponerNombre("Cilindro");
   vector<Tupla3f> perfil;
   double z = 0;
   for (double i = 0; i < num_verts_per; i++){
      z = i/(num_verts_per-1);
      perfil.push_back({1.0, z, 0.0});
   }
   
   inicializar(perfil, nperfiles);
   
}

Cono::Cono(const int num_verts_per, const unsigned nperfiles) : MallaRevol()
{
   ponerNombre("Cono");
   vector<Tupla3f> perfil;
    for (int i = 0; i < num_verts_per; i++){
      //double z = i/n;
      Tupla3f a(1.0-i/(num_verts_per-1), i/(num_verts_per-1),0.0 );
      perfil.push_back(a);
   }
   //cout << "cilindro fin"<<endl;
   inicializar(perfil, nperfiles);
}




Esfera::Esfera(const int num_verts_per, const unsigned nperfiles) : MallaRevol()
{
   ponerNombre("Esfera");
   vector<Tupla3f> perfil;
   double z;
    for (int i = 0; i < num_verts_per; i++){
      
      z = i*M_PI/(num_verts_per-1);
      Tupla3f a(sin(z), cos(z),0.0 );
      perfil.push_back(a);
   }
   
   inicializar(perfil, nperfiles);
}

CilindroRelleno::CilindroRelleno(const int num_verts_per, const unsigned nperfiles) : MallaRevol()
{
   ponerNombre("Cilindro");
   vector<Tupla3f> perfil;
   double z = 0;
   for (double i = 0; i < num_verts_per; i++){
      z = i/(num_verts_per-1);
      perfil.push_back({1.0, z, 0.0});
      perfil.push_back({0.0, z, 0.0});
   }
   
   inicializar(perfil, nperfiles);
   
}


SemiEsfera::SemiEsfera(const int num_verts_per, const unsigned nperfiles): MallaRevol()
{
   ponerNombre("SemiEsfera");
   vector<Tupla3f> perfil;
   double z;
    for (int i = 0; i < num_verts_per; i++){
      
      z = M_PI/2 + i*(M_PI/2)/(num_verts_per-1);
      Tupla3f a(sin(z), cos(z),0.0 );
      perfil.push_back(a);
      perfil.push_back({0.0,cos(z), 0.0});
   }
   
   inicializar(perfil, nperfiles);
}

void SemiEsfera::colorearSemiEsfera(){
      for (int i = 0; i < vertices.size(); i++){
      if (rand()% 5 < 4)
         col_ver.push_back({1,0.52,0});
      else
         col_ver.push_back({1,1,1});
   }
}
void Esfera::colorearEsfera(){
   for (int i = 0; i < vertices.size(); i++){
      if (rand()% 6 == 0)
         col_ver.push_back({1,0.52,0});
      else
         col_ver.push_back({1,1,1});
   }
}