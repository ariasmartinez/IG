

#include "grafo-escena.h"



class Cuerpo : public NodoGrafoEscena{
   public:
   Cuerpo(Matriz4f * &pm_alpha_rot_x,    Matriz4f * &pm_alpha_rot_y, Matriz4f * &pm_alpha_rot_z);
   //unsigned leerNumParametros();
   //void actualizarEstadoParametro(const unsigned iParam, const float tSec);
    //mirar
    //void leerNumParametros();
    //void actualizarEstadoParametros();
};

class Cabeza : public NodoGrafoEscena{
   public:
   Cabeza(Matriz4f * &pm_beta_rot_cab, Matriz4f * &pm_traslacion_ojo, Matriz4f *&pm_mov_cab);
   //unsigned leerNumParametros();
   //void actualizarEstadoParametro(const unsigned iParam, const float tSec);
};

class Ojo: public NodoGrafoEscena{
   public:
   Ojo(Matriz4f * & pm_traslacion_ojo);
};

class bb8: public NodoGrafoEscena{
   protected:
      Matriz4f * pm_alpha_rot_x = nullptr;
      Matriz4f * pm_alpha_rot_y = nullptr;
      Matriz4f * pm_alpha_rot_z = nullptr;
      Matriz4f * pm_beta_rot_cab = nullptr;
      Matriz4f * pm_traslacion = nullptr;
      Matriz4f * pm_traslacion_ojo = nullptr;
      Matriz4f * pm_mov_cab = nullptr;
      void actualizarEstadoParametro(const unsigned iParam, const float tSec);
   public:
      bb8();
      unsigned leerNumParametros() const;
      
      void fijarAlphaRotX(const float nuevo_valor);
      void fijarAlphaRotY(const float nuevo_valor);
      void fijarAlphaRotZ(const float nuevo_valor);
      void fijarBetaRotCab(const float nuevo_valor);
      void fijarTraslacion(const float nuevo_valor);
      void fijarTraslacionOjo(const float nuevo_valor);
      void fijarMovCabeza(const float nuevo_valor);

};

class Union: public NodoGrafoEscena{
   public:
   Union(Matriz4f * &pm_beta_rot_cab, Matriz4f * &pm_traslacion_ojo);
};