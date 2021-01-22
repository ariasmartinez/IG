//Nombre: Celia, Apellidos: Arias Martínez, DNI: 26510285w (DDGG IG curso 20-21)

#include "ig-aux.h"
#include "escena.h"

#include "objeto3d.h"
#include "malla-ind.h"
#include "malla-revol.h"
#include "practicas.h"
#include "camara.h"
#include "materiales-luces.h"
#include "seleccion.h"

//celia
#include "modelo-jer.h"
#include "latapeones.h"

// -----------------------------------------------------------------------------------------------

Escena::Escena()
{
   // COMPLETAR: Práctica 4: inicializar 'col_fuentes' y 'material_ini'
   // ...
   col_fuentes = new Col2Fuentes();
   material_ini = new Material(0.5,0.8,1.5,60); //DUDA


   // COMPLETAR: Práctica 5: hacer 'push_back' de varias camaras perspectiva u ortogonales,
   // (sustituir la cámara orbital simple ('CamaraOrbitalSimple') por varias cámaras de 3 modos ('Camara3Modos')
  // camaras.push_back( new CamaraOrbitalSimple() );
  
   camaras.push_back(new Camara3Modos(true, {0.0,2.0,7.0}, 1.0, {0.0,0.0,0.0}, 90.0)); //alzado  //perspectiva
   camaras.push_back( new Camara3Modos(false, {-5.0,2.0,0.0}, 1.0, {0.0,0.0,0.0},60.0) ); //perfil  //ortogonal
   camaras.push_back( new Camara3Modos(true, {0.0,7.0,1.0}, 4.0, {0.0,0.0,0.0},90.0) ); //planta  //perspectiva
 

   camaras.push_back( new Camara3Modos(true, {7.0,7.0,7.0}, 4.0, {0.0,0.0,0.0},90.0) ); //planta  //perspectiva

}
// -----------------------------------------------------------------------------------------------
// visualiza la escena en la ventana actual, usando la configuración especificada en 'cv'

void Escena::visualizarGL( ContextoVis & cv )
{
   using namespace std ;

   // recuperar el cauce actual de 'cv' en 'cauce', activarlo
   Cauce * cauce = cv.cauce_act ; assert( cauce != nullptr );
   cauce->activar() ;

   // recuperar la cámara actual de esta escena y  fijar las matrices 'modelview'
   // y 'projection' en el cauce gráfico (es decir: activar la cámara actual)
   CamaraInteractiva * camara = camaras[ind_camara_actual] ; assert( camara != nullptr );
   const float ratio_vp = float(cv.ventana_tam_y)/float(cv.ventana_tam_x) ;
   camara->fijarRatioViewport( ratio_vp );
   camara->activar( *cauce ) ;


   
   // dibujar los ejes, si procede
   if ( cv.dibujar_ejes  )
      DibujarEjesSolido( *cauce ) ;

   // fijar el color por defecto en el cauce para dibujar los objetos
   // if ( cv.fondo_blanco && ! cv.iluminacion )
   //    glColor3f( 0.0, 0.0, 0.0 );
   // else
   //    glColor3f( 1.0, 1.0, 1.0 );
   glColor3f( 1.0, 1.0, 1.0 );

   // COMPLETAR: Práctica 1: Configurar el cauce en función de:
   //    cv.sombr_plano (true/false)              --> usar fijarModoSombrPlano (método del 'cauce')
   //    cv.modo_visu   (puntos,lineas o relleno) --> usar glPolygonMode

   cauce->fijarModoSombrPlano(cv.sombr_plano);

   GLenum vis_pol;
   switch(cv.modo_visu){
      case (ModosVisu::relleno):
         vis_pol = GL_FILL;
      break;
      case (ModosVisu::lineas):
         vis_pol = GL_LINE;
      break;
      case (ModosVisu::puntos):
         vis_pol = GL_POINT;
      break;
      default:
         cout << "Modo relleno en escena desconocido" << endl;
   };


   glPolygonMode(GL_FRONT_AND_BACK, vis_pol);

  

   if ( cv.iluminacion )
   {
      // COMPLETAR: Práctica 4: activar evaluación del MIL (y desactivar texturas)
      // * habilitar evaluación del MIL en el cauce (fijarEvalMIL)
      // * activar la colección de fuentes de la escena
      // * activar el material inicial
      // ....
      cauce->fijarEvalMIL(true); //habilitar iluminacion en el cauce
      col_fuentes->activar(*cauce); //activar la coleccion de fuentes
    
      if(material_ini!=nullptr){
         cv.material_act = material_ini;  //DUDA
         material_ini->activar(*cauce);  //activar el material inicial
      }


   }
   else // si la iluminación no está activada, deshabilitar MIL y texturas
   {  cauce->fijarEvalMIL( false );
      cauce->fijarEvalText( false );
   }

   // recuperar el objeto actual de esta escena
   Objeto3D * objeto = objetos[ind_objeto_actual] ; assert( objeto != nullptr );

    //Visualizamos las normales si procede
   if ( cv.visualizar_normales && !cv.modo_seleccion )
      visualizarNormales( cv );

   // COMPLETAR: Práctica 1: visualizar el objeto actual ('objeto')

   objeto->visualizarGL(cv);

   
   // si hay un FBO, dibujarlo (opcional...)

}

void Escena::visualizarNormales( ContextoVis & cv )
{
   // recuperar el objeto raiz de esta escena y comprobar que está ok.
   bool ilum_ant = cv.iluminacion ;
   assert( cv.cauce_act != nullptr );
   Objeto3D * objeto = objetos[ind_objeto_actual] ; assert( objeto != nullptr );

   // configurar el cauce:
   cv.cauce_act->fijarEvalMIL( false );
   cv.cauce_act->fijarEvalText( false );
   cv.cauce_act->fijarModoSombrPlano( true ); // sombreado plano
   glLineWidth( 1.5 ); // ancho de líneas (se queda puesto así)
   glColor4f( 1.0, 0.7, 0.4, 1.0 ); // color de las normales

   // configurar el contexto de visualizacion
   cv.visualizando_normales = true ;   // hace que MallaInd::visualizarGL visualize las normales.
   cv.iluminacion           = false ;

   // visualizar objeto actual
   objetos[ind_objeto_actual]->visualizarGL( cv );

   // restaurar atributos cambiados en el contexto de visualización
   cv.visualizando_normales = false ;
   cv.iluminacion = ilum_ant ;
}




// -----------------------------------------------------------------------------------------------
// pasa la cámara actual a la siguiente

void Escena::siguienteCamara()
{
   assert( ind_camara_actual < camaras.size() );
   ind_camara_actual = (ind_camara_actual+1 ) % camaras.size();
   using namespace std ;
   cout << "Cámara actual cambiada a: " << (ind_camara_actual+1) << " (de " << camaras.size() << ")" << endl ;
}

// -----------------------------------------------------------------------------------------------
// pasa el objeto actual al siguiente

void Escena::siguienteObjeto()
{
   if ( objetos.size() == 0 )
      return ;
   assert( ind_objeto_actual < objetos.size() );
   ind_objeto_actual = (ind_objeto_actual+1 ) % objetos.size();
   using namespace std ;
   cout << "Objeto actual cambiado a: " << objetoActual()->leerNombre()
        << " (" << (ind_objeto_actual+1) << "/" << objetos.size() << ")." << endl  ;
}

// -----------------------------------------------------------------------------------------------
// devuelve puntero al objeto actual

Objeto3D * Escena::objetoActual()
{
   assert( ind_objeto_actual < objetos.size() );
   assert( objetos[ind_objeto_actual] != nullptr );
   return objetos[ind_objeto_actual] ;
}
// -----------------------------------------------------------------------------------------------
// devuelve un puntero a la cámara actual

CamaraInteractiva * Escena::camaraActual()
{
   assert( ind_camara_actual < camaras.size() );
   assert( camaras[ind_camara_actual] != nullptr );
   return camaras[ind_camara_actual] ;
}
// -----------------------------------------------------------------------------------------------
// devuelve un puntero a la colección de fuentes actual

ColFuentesLuz * Escena::colFuentes()
{
   assert( col_fuentes != nullptr );
   return col_fuentes ;
}
// -----------------------------------------------------------------------------------------------

Escena1::Escena1()
{
   using namespace std ;
   cout << "Creando objetos de escena 1 .... " << flush ;
 
   // añadir el objeto 'Cubo' a la lista de objetos de esta escena:
   objetos.push_back(new Invocacion2());
   objetos.push_back(new CilindroTextura());
   objetos.push_back( new Cubo() );
   objetos.push_back( new Tetraedro());
   objetos.push_back( new CuboColores() );
   // COMPLETAR: Práctica 1: creación del resto objetos de la práctica 1
   // Añadir objetos al vector 'objetos', con:
   //     objetos.push_back( new .... )
   // .........
   

   cout << "hecho." << endl << flush ;
}



// -------------------------------------------------------------------------
// COMPLETAR: Práctica 2
// Añadir la implementación del constructor de la clase Escena2 para construir
// los objetos que se indican en los guiones de las práctica 2
// .......


Escena2::Escena2(){
   using namespace std;
   cout << "Creando objetos de escena 2..." << flush;
  
   objetos.push_back(new MallaPLY("../recursos/plys/ant"));
   objetos.push_back(new MallaRevolPLY("../recursos/plys/peon", 10));
   objetos.push_back(new MallaRevolPLY("../recursos/plys/lata-pcue", 10));
   objetos.push_back(new MallaPLY("../recursos/plys/beethoven"));
   objetos.push_back(new MallaPLY("../recursos/plys/big_dodge.ply"));
  objetos.push_back(new MallaPLY("../recursos/plys/cow.ply"));

   objetos.push_back( new Cilindro(20,50));
   objetos.push_back( new Cono(20,50));
   objetos.push_back( new Esfera(20,50));
   objetos.push_back( new CilindroRelleno(20,50));

   cout << "hecho." << endl << flush ;
}

// -------------------------------------------------------------------------
// COMPLETAR: Práctica 3
// Añadir la implementación del constructor de la clase Escena3 para construir
// los objetos que se indican en los guiones de las práctica 3
// .......

Escena3::Escena3(){
   using namespace std;

   cout << "Creando objetos de escena 3..." << flush;
   
   objetos.push_back( new bb8());
   cout << "hecho." << endl << flush;
}

Escena4::Escena4(){
  using namespace std;
  cout << "Creando objetos de escena 4..." << flush;
  objetos.push_back( new NodoCubo24());
  objetos.push_back(new LataPeones());
  cout << "hecho" << endl << flush;
}
// ----------------------------------------------------------------------
// COMPLETAR: Práctica 4
// Añadir la implementación del constructor de la clase Escena4 para construir
// los objetos que se indican en los guiones de las práctica 4
// .......
Escena5::Escena5(){
   using namespace std;
   cout << "Creando objetos de escena 5..." << flush;
   objetos.push_back(new VariasLatasPeones());
   cout << "hecho" << endl << flush;
}


// ----------------------------------------------------------------------
// COMPLETAR: Práctica 5
// Añadir la implementación del constructor de la clase Escena5 para construir
// los objetos que se indican en los guiones de las práctica 5
// .......



