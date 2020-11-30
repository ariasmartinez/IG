// *********************************************************************
// **
// ** Informática Gráfica, curso 2020-21
// ** Declaraciones de la clase Objeto3D.hpp
// **
// *********************************************************************

//#include <set>   // std::set
#include "ig-aux.h"
#include "tuplasg.h"
#include "malla-ind.h"   // declaración de 'ContextoVis'
#include "lector-ply.h"


// *****************************************************************************
// funciones auxiliares

// *****************************************************************************
// métodos de la clase MallaInd.

MallaInd::MallaInd()
{
   // nombre por defecto
   ponerNombre("malla indexada, anónima");
}
// -----------------------------------------------------------------------------

MallaInd::MallaInd( const std::string & nombreIni )
{
   // 'identificador' puesto a 0 por defecto, 'centro_oc' puesto a (0,0,0)
   ponerNombre(nombreIni) ;
}

//-----------------------------------------------------------------------------
// calcula la tabla de normales de triángulos una sola vez, si no estaba calculada

void MallaInd::calcularNormalesTriangulos()
{

   // si ya está creada la tabla de normales de triángulos, no es necesario volver a crearla
   const unsigned nt = triangulos.size() ;
   assert( 1 <= nt );
   if ( 0 < nor_tri.size() )
   {
      assert( nt == nor_tri.size() );
      return ;
   }

   // COMPLETAR: Práctica 4: creación de la tabla de normales de triángulos
   // ....

}


// -----------------------------------------------------------------------------
// calcula las dos tablas de normales

void MallaInd::calcularNormales()
{
   // COMPLETAR: en la práctica 4: calculo de las normales de la malla
   // se debe invocar en primer lugar 'calcularNormalesTriangulos'
   // .......


}




// ----------------------------------------------------------------------------


void MallaInd::visualizarGL( ContextoVis & cv )
{

   using namespace std ;
   assert( cv.cauce_act != nullptr );

   if ( triangulos.size() == 0 || vertices.size() == 0 )
   {  cout << "advertencia: intentando dibujar malla vacía '" << leerNombre() << "'" << endl << flush ;
      return ;
   }

   // guardar el color previamente fijado
   const Tupla4f color_previo = leerFijarColVertsCauce( cv );

   // COMPLETAR: práctica 1: si el puntero 'array_verts' es nulo, crear el objeto ArrayVerts
   //   * en el constructor se dan los datos de la tabla de coordenadas de vértices (tabla 'vertices')
   //   * después hay que invocar a 'fijarIndices', usando el formato y datos de la tabla de triángulos ('triangulos')
   //   * si las tablas 'col_ver', 'cc_tt_ver' o 'nor_ver' no están vacías, hay que invocar los métodos 
   //     'fijarColores', 'fijarCoordText' y 'fijarNormales', como corresponda.

  
   if (array_verts == nullptr)
      array_verts = new ArrayVertices( GL_FLOAT, 3, vertices.size(), vertices.data());
   
   


   
   array_verts->fijarIndices( GL_UNSIGNED_INT, 3*triangulos.size(), triangulos.data());

   
   if (!col_ver.empty())
      array_verts->fijarColores( GL_FLOAT, 3, col_ver.data());
   if (!cc_tt_ver.empty())
      array_verts->fijarCoordText( GL_FLOAT, 2, cc_tt_ver.data());
   if (!nor_ver.empty())
      array_verts->fijarNormales(GL_FLOAT, nor_ver.data());

   
   // COMPLETAR: práctica 1: visualizar según el modo (en 'cv.modo_envio')
   //   ** inmediato begin/end       : usar método 'visualizarGL_MI_BVE' de 'ArrayVerts'
   //   ** inmediato con una llamada : usar método 'visualizarGL_MI_DAE' de 'ArrayVerts'
   //   ** diferido (con un VAO)     : usar método 'visualizarGL_MD_VAO' de 'ArrayVerts'
   // (en cualquier caso hay que pasar como parámetro el tipo de primitiva adecuada a una malla de triángulos).
   // .....

     
   ArrayVertices * array_verts2;
   ArrayVertices * array_verts3;
   ArrayVertices * array_verts4;
    
  
  if (cv.calcular_envolvente){
   if (array_verts2 == nullptr)
   {
      calcularEnvolvente();
      array_verts2 = new ArrayVertices(GL_FLOAT, 3, esferaXZ.size(), esferaXZ.data());
      array_verts3 = new ArrayVertices(GL_FLOAT, 3, esferaYZ.size(), esferaYZ.data());
      array_verts4 = new ArrayVertices(GL_FLOAT, 3, esferaXY.size(), esferaXY.data());
   }

      glColor3f(1,1,0);
     glLineWidth(0.4); 
   
   array_verts2->visualizarGL_MI_DAE(GL_LINES);
   
   array_verts3->visualizarGL_MI_DAE(GL_LINES);
  
   array_verts4->visualizarGL_MI_DAE(GL_LINES);
  }   
   GLenum vis_pol = GL_TRIANGLES;

   switch(cv.modo_envio){
      case (ModosEnvio::inmediato_begin_end):
         array_verts->visualizarGL_MI_BVE(vis_pol);
      break;
      case (ModosEnvio::inmediato_drawelements):
         array_verts->visualizarGL_MI_DAE(vis_pol);
      break;
      case (ModosEnvio::diferido_vao):
         array_verts->visualizarGL_MD_VAO(vis_pol);
      break;
      default:
         cout << "malla-ind.cpp::visualizarGL:: cv.modo_envio extraño" << endl;
   }
 
   // restaurar el color previamente fijado
   glColor4fv( color_previo );
}






// *****************************************************************************


// ****************************************************************************
// Clase 'MallaPLY'

MallaPLY::MallaPLY( const std::string & nombre_arch )
{
   ponerNombre( std::string("malla leída del archivo '") + nombre_arch + "'" );

   // COMPLETAR: práctica 2: leer archivo PLY e inicializar la malla
   // ..........................

  
   
   LeerPLY(nombre_arch,vertices,triangulos);
   

   //hecho

   // COMPLETAR: práctica 4: invocar  a 'calcularNormales' para el cálculo de normales
   // .................



}

// ****************************************************************************
// Clase 'Cubo

Cubo::Cubo()
:  MallaInd( "cubo 8 vértices" )
{

   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
      } ;

  

   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,5,1}, {0,4,5}, // Y-
         {2,3,7}, {2,7,6}, // Y+ (+2)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

   ponerColor({0.0, 0.0, 1.0});
}

Tetraedro::Tetraedro() : MallaInd("tetraedro"){
   
   vertices =
      {
        {0, 0, 0}, //0
        {0, 1, 0}, //1
        {1, 0, 0}, //2
        {0,0,1} //3
      

      };
   
   triangulos = 
   {
      {0,1,2}, {1,2,3}, {2,3,0},
     
   };

   ponerColor({0.0, 0.0, 1.0});
}



CuboColores::CuboColores() : MallaInd("cubo colores"){
   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
      } ;

  

   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,5,1}, {0,4,5}, // Y-
         {2,3,7}, {2,7,6}, // Y+ (+2)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

   col_ver =
   {
      { -1.0, -1.0, -1.0 }, // 0
      { -1.0, -1.0, +1.0 }, // 1
      { -1.0, +1.0, -1.0 }, // 2
      { -1.0, +1.0, +1.0 }, // 3
      { +1.0, -1.0, -1.0 }, // 4
      { +1.0, -1.0, +1.0 }, // 5
      { +1.0, +1.0, -1.0 }, // 6
      { +1.0, +1.0, +1.0 }, // 7
   };
   
}
// -----------------------------------------------------------------------------------------------




/*

Programar un método dentro de la clase mallaInd que calcule la esfera envolvente de la malla, para ello:
1. Añadir tres atributos privados a la clase: 
- vector<Tupla3f> esferaXZ
- vector<Tupla3f> esferaYZ
- vector<Tupla3f> esferaXY
que contendrán las coordenadas de los puntos que compongan, respectivamente, el ecuador, el meridiano paralelo al plano x=0 y el meridiano paralelo al plano z=0
2. Hallar el centro geométrico de la malla, para ello, calcular la media aritmética de todos los vértices que la componen (caso de haber al menos uno, en otro caso se supone el (0,0,0) )
3. Hallar la máxima de las distancias del centro geométrico calculado anteriormente a un vértice de la malla.
El punto calculado en 2 será el centro de la esfera envolvente y la distancia máxima calculada en 3 será el radio de dicha esfera.
4. Calcular una cantidad representativa de puntos que pertenezcan al plano paralelo a y=0 que pasa por el centro geométrico y que están a una distancia igual al radio calculado en 3 y almacenarlos en esferaXZ, análogamente con puntos paralelos a x=0 en esferaYZ y con puntos paralelos a z=0 en esferaXY. 
Programar el método de forma que una vez estos vértices estén calculados no se vuelvan a calcular a no ser que la malla haya cambiado.

*/
double MallaInd::dist(Tupla3f v, Tupla3f v2){
   return sqrt(pow(v(0)-v2(0),2)+pow(v(1)-v2(1),2)+pow(v(2)-v2(2),2));
}


void MallaInd::calcularEnvolvente(){
   double media_x = 0 ; double media_y = 0; double media_z = 0;
   double max_x = vertices[0](0); double max_y = vertices[0](1); double max_z = vertices[0](2);
   Tupla3f centro(0,0,0);
   int num_prec = 100;
   if (vertices.size()>0){
      for (int i = 0; i < vertices.size();i++){
         media_x += vertices[i](0);
         media_y += vertices[i](1);
         media_z += vertices[i](2);
      }
      Tupla3f centro(media_x/float(vertices.size()), media_y/float(vertices.size()), media_z/float(vertices.size()));
   }

   double radio = 0;
   for (int i = 0; i < vertices.size(); i++)
      radio = std::max(dist(vertices[i], centro), radio);
   
   
   for (int i = 0; i < num_prec; i++){
      esferaXZ.push_back({float(centro(0)+radio*(cos(2*M_PI*i/num_prec))),centro(1), float(centro(2)+radio*(sin(2*M_PI*i/num_prec)))});
      esferaYZ.push_back({centro(0),centro(1)+radio*(cos(2*M_PI*i/num_prec)), centro(2)+radio*(sin(2*M_PI*i/num_prec))});
      esferaXY.push_back({centro(0)+radio*(sin(2*M_PI*i/num_prec)),centro(1)+radio*(cos(2*M_PI*i/num_prec)), centro(2)});
   }



  
}

