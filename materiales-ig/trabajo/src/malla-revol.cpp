//Nombre: Celia, Apellidos: Arias Martínez, DNI: 26510285w (DDGG IG curso 20-21)


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

   //calculamos normales


   std::vector<Tupla3f> normalesAristas;
   Tupla3f normal;
   for(unsigned i = 0; i<perfil.size()-1; i++){

      normal(0)= (perfil[i+1]-perfil[i])(1);
      normal(1)=-(perfil[i+1]-perfil[i])(0);
      normal(2)=0;
      if(normal.lengthSq()>0)
         normalesAristas.push_back(normal.normalized());
      else
         normalesAristas.push_back(normal);
      
   }
  

  // std::vector<Tupla3f> normalesVertices;
  /*
   nor_ver.push_back(normalesAristas[0]);

   Tupla3f normal_v;
   for (int i = 1; i < perfil.size()-1; i++){
      normal_v = normalesAristas[i]+normalesAristas[i-1];
      if(normal_v.lengthSq()>0)
         nor_ver.push_back(normal_v.normalized());
      else
         nor_ver.push_back(normal_v);
   }
   nor_ver.push_back(normalesAristas[normalesAristas.size()-2]);
*/

   nor_ver.insert(nor_ver.begin(), perfil.size(), {0.0, 0.0 , 0.0});
   if(normalesAristas[0].lengthSq()!=0)
      nor_ver[0]=normalesAristas[0].normalized();
   
   for(unsigned i=1; i<perfil.size()-1; i++){
      nor_ver[i]=normalesAristas[i]+normalesAristas[i-1];
      if(nor_ver[i].lengthSq()!=0)
         nor_ver[i]=nor_ver[i].normalized();
   }

   if(normalesAristas[perfil.size()-2].lengthSq()!=0)
      nor_ver[perfil.size()-1]=normalesAristas[perfil.size()-2];
   //DUDA

   std::vector<float> d, t;
   float d_total = 0;
   float  di, dj;
   for (unsigned int i = 0; i < perfil.size()-1; i++){
      di = sqrt((perfil[i+1]-perfil[i]).lengthSq());
      d.push_back(di);
      d_total+=di;
   }

   t.push_back(0);
    for(unsigned int i = 1; i<perfil.size(); i++)
      t.push_back(t[i-1]+d[i-1]/d_total);


   Tupla3f q;
   double angulo;
 //cambio perfil.size() por perfil -1
   for (unsigned  i = 0; i < num_copias; i++){
      for (unsigned j = 0; j < perfil.size(); j++){
         angulo = 2*i*180/(num_copias-1);
         q = MAT_Rotacion(angulo, {0,1,0})*perfil[j];
         vertices.push_back(q);
         if (i != 0)
            nor_ver.push_back(MAT_Rotacion(angulo, {0,1,0})*nor_ver[j]);
         cc_tt_ver.push_back({float(i)/float(perfil.size()-1),1.0-t[j]});
      }
   }

  


   double k;
   for (int i = 0; i < (num_copias-1); i++){
      for (int j = 0; j < (perfil.size()-1); j++){
         k = i*perfil.size()+j;
         triangulos.push_back({k, k+perfil.size(), k+perfil.size()+1});
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
   ponerNombre("Cilindro");
   
   
}

Cono::Cono(const int num_verts_per, const unsigned nperfiles) : MallaRevol()
{
   ponerNombre("Cono");
   vector<Tupla3f> perfil;
    for (int i = 0; i < num_verts_per; i++){
      Tupla3f a(1.0-i/(num_verts_per-1), i/(num_verts_per-1),0.0 );
      perfil.push_back(a);
   }
   inicializar(perfil, nperfiles);
   ponerNombre("Cono");
  
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
   ponerNombre("Esfera");
  
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
   ponerNombre("Cilindro Relleno");
  
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
   ponerNombre("SemiEsfera");
   
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