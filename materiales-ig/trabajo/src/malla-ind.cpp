//Nombre: Celia, Apellidos: Arias Martínez, DNI: 26510285w (DDGG IG curso 20-21)


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
         cout << "El modo de envío de malla-ind no está definido" << endl;
   }
 
   ArrayVertices * tetr_env;
   std::vector<Tupla3f> envolvente;
   if (envolvente.size()  == 0){
      calcularEnvolvente();
      
      envolvente.push_back(minXminYminZ);
      envolvente.push_back(minXminYmaxZ);
      envolvente.push_back(minXmaxYminZ);
      envolvente.push_back(minXmaxYmaxZ);
      envolvente.push_back(maxXminYminZ);
      envolvente.push_back(maxXminYmaxZ);
      envolvente.push_back(maxXmaxYminZ);
      envolvente.push_back(maxXmaxYmaxZ);
      
      tetr_env =new ArrayVertices( GL_FLOAT, 3, envolvente.size(), envolvente.data());
   }
    
   tetr_env->visualizarGL_MD_VAO(GL_LINES);


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
Programar un método dentro de la clase mallaInd que calcule los vértices del tetraedro paralelo a los ejes más pequeño que contenga a la malla, para ello:
1. Añadir los siguientes atributos de tipo Tupla3f en la clase mallaInd:

- minXminYminZ
- minXminYmaxZ
- minXmaxYminZ
- minXmaxYmaxZ
- maxXminYminZ
- maxXminYmaxZ
- maxXmaxYminZ
- maxXmaxYmaxZ

(Perdonad pero es que de este ni siquiera leí el enunciado porque no hice este examen pero por lo que me dijeron entendí esto)
2. Calcular la máxima y mínima coordenada x de entre todas las coordenadas x de los vértices de la malla. Análogamente con las máximas y mínimas coordenadas y y z.
3. Con estas medidas, almacenar en cada atributo el vértice correspondiente al tetraedro envolvente. Por ejemplo, en minXmaxYminZ se almacenaria un punto cuyas coordenadas sean la mínima coordenada x, la máxima coordenada y y la mínima coordenada z de las anteriormente calculadas.

*/


void MallaInd::calcularEnvolvente(){
   float min_x = vertices[0](0);
   float max_x = vertices[0](0);
   float min_y = vertices[0](1);
   float max_y = vertices[0](1);
   float min_z = vertices[0](2);
   float max_z = vertices[0](2);
   
   for (int i = 0; i < vertices.size(); i++){
      min_x = std::min(vertices[i](0), min_x);
      max_x = std::max(vertices[i](0), max_x);
      min_y = std::min(vertices[i](1), min_y);
      max_y = std::max(vertices[i](1), max_y);
      min_z = std::min(vertices[i](2), min_z);
      max_z = std::max(vertices[i](2), max_z);

   }

    minXminYminZ = Tupla3f({min_x,min_y,min_z});
    minXminYmaxZ = Tupla3f({min_x,min_y,max_z});
    minXmaxYminZ = Tupla3f({min_x,max_y,min_z});
    minXmaxYmaxZ = Tupla3f({min_x, max_y, max_z});
    maxXminYminZ = Tupla3f({max_x,min_y,min_z});
    maxXminYmaxZ = Tupla3f({max_x, min_y, max_z});
    maxXmaxYminZ = Tupla3f({max_x,max_y, min_z});
    maxXmaxYmaxZ = Tupla3f({max_x,max_y,max_z});



}