//Nombre: Celia, Apellidos: Arias Martínez, DNI: 26510285w (DDGG IG curso 20-21)


// *********************************************************************
// **
// ** Informática Gráfica - curso 2020-21
// ** Declaración de la clase 'Escena' y derivadas (una por cada práctica)
// **
// **  + Escena: clase con una colección de objetos para visualizar y una cámara.
// **    En cada momento se visualiza uno de los objetos (se conmuta con 'o')
// **    Las clases derivadas incluyen cada una un constructor específico que crea el objeto,
// **    son estas:
// **
// **       + Escena1 : práctica 1
// **       + Escena2 : práctica 2
// **       + Escena3 : práctica 3
// **       + Escena4 : práctica 4
// **       + Escena5 : práctica 5
// **
// *********************************************************************

#ifndef ESCENA_H
#define ESCENA_H


#include <vector>
#include "practicas.h"

// *************************************************************************
// Clase Escena
// -----------------
// Clase para objetos visualizables de tipo escena: incluye objetos, cámaras,
// un material inicial, una colección de fuentes de luz, etc...


class Escena
{
   public:

   // crea una escena con una cámara orbital simple, materiales y luces por defecto.
   Escena() ;

   // visualiza el objeto actual de la escena
   void visualizarGL( ContextoVis & cv ) ;

   // pasa la cámara actual a la siguiente
   void siguienteCamara() ;

   // devuelve un puntero a la cámara actual
   CamaraInteractiva * camaraActual() ;

   // pasa el objeto actual al siguiente
   void siguienteObjeto() ;

   // devuelve puntero al objeto actual
   Objeto3D * objetoActual();

   // devuelve un puntero a la colección de fuentes actual
   ColFuentesLuz * colFuentes();



   protected:
   // vector de objetos (alternativos: se visualiza uno de ellos nada más)
   std::vector<Objeto3D *> objetos ;

   // vector de cámaras (se usa una en cada momento)
   std::vector<CamaraInteractiva *> camaras ;

   // material por defecto que se activa antes de dibujar (con iluminación activada)
   Material * material_ini = nullptr ;

   // colección de fuentes de luz que se usarán para dibujar, (con iluminación activada)
   ColFuentesLuz * col_fuentes = nullptr ;

   // índice de la cámara activa (en el vector 'camaras')
   unsigned ind_camara_actual = 0 ;

   // índice del objeto activo (en el vector 'objetos')
   unsigned ind_objeto_actual = 0 ;

   private:
   void visualizarNormales(ContextoVis & cv );
} ;


// -------------------------------------------------------------------------
// clase derivada de 'Escena', define un constructor que permite añadir
// al array de objetos de la escena los objetos que se indican en la práctica 1

class Escena1 : public Escena
{
   public:
      Escena1() ;
} ;


class Escena2: public Escena
{
   public:
      Escena2();
};
// -------------------------------------------------------------------------
// COMPLETAR: Práctica 2, 3, 4 y 5.
// Añadir la declaración de las clases Escena2, Escena3, etc ..... para definir
// los objetos que se indican en los guiones de las prácticas 2,3,4 y 5.

class Escena3: public Escena{
   public:
      Escena3();
};


class Escena4: public Escena{
   public:
      Escena4();
};

class Escena5 : public Escena{
   public:
   Escena5();
};

#endif // ESCENA_H
