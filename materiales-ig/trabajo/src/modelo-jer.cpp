#include "modelo-jer.h"
#include "malla-revol.h"
#include <stdlib.h>



bb8::bb8(){

   unsigned ind0 = agregar(MAT_Traslacion(0,0,0));
   agregar (new Cuerpo(pm_alpha_rot_y, pm_alpha_rot_x, pm_alpha_rot_z));

   agregar( MAT_Traslacion(0,0,0.95));
   agregar( MAT_Escalado(0.57,0.57,0.57));
   agregar(new Cabeza(pm_beta_rot_cab, pm_mov_ojo, pm_mov_cab));


   pm_traslacion = leerPtrMatriz(ind0);

}

Cuerpo::Cuerpo(Matriz4f * &pm_alpha_rot_x,    Matriz4f * &pm_alpha_rot_y, Matriz4f * &pm_alpha_rot_z){
   unsigned ind1= agregar(MAT_Rotacion(0, {1,0,0}));
   unsigned ind2 = agregar(MAT_Rotacion(0, {0,1,0}));
   unsigned ind3 = agregar(MAT_Rotacion(0, {0,0,1}));

   Esfera * esf = new Esfera(100, 200);

   esf->colorearEsfera();
   agregar(esf);
  

   pm_alpha_rot_x = leerPtrMatriz(ind1);
   pm_alpha_rot_y = leerPtrMatriz(ind2);
   pm_alpha_rot_z = leerPtrMatriz(ind3);


}

Cabeza::Cabeza(Matriz4f * &pm_beta_rot_cab, Matriz4f * &pm_mov_ojo, Matriz4f * &pm_mov_cab){

   unsigned ind4 = agregar(MAT_Rotacion(0, {0,0,1}));
   unsigned ind6 = agregar(MAT_Rotacion(0, {1,0,0}));

   ponerColor({1,0.52,0});
   SemiEsfera * s_esf = new SemiEsfera(100, 200);
   s_esf->colorearSemiEsfera();
 
   agregar(MAT_Rotacion(270, {1,0,0}));
   
   agregar(s_esf);

   unsigned ind5 = agregar( MAT_Rotacion(0,{1,0,0}));
   agregar( MAT_Traslacion(0,-0.5,-0.6)); 
   
   agregar( MAT_Escalado(0.25,0.25,0.25));

   
   agregar(new Ojo(pm_mov_ojo));

   pm_beta_rot_cab = leerPtrMatriz(ind4);
   pm_mov_ojo  = leerPtrMatriz(ind5);
   pm_mov_cab = leerPtrMatriz(ind6);
   
}

Ojo::Ojo(Matriz4f *& pm_mov_ojo){ 
   Esfera* esf = new Esfera(100, 200);
   ponerColor({0.0,0.0,0.0});
   agregar(esf);
}



unsigned bb8::leerNumParametros() const{
   return 7; 
}

void bb8::actualizarEstadoParametro(const unsigned iParam, const float tSec){
   assert((iParam < leerNumParametros()) && (iParam >= 0));
   float nuevo_valor;
   switch(iParam){
      case 0:  //rotacion eje x
         nuevo_valor = 20*M_PI*tSec;
         fijarAlphaRotX(nuevo_valor);
      break;
      case 1: //rotacion eje y
         nuevo_valor = 2*M_PI*tSec;
         fijarAlphaRotY(nuevo_valor);
      break;

      case 2: //rotacion eje z
         nuevo_valor = 10*M_PI*tSec;
         fijarAlphaRotZ(nuevo_valor);
      break;
      case 3: //giro cabeza
         nuevo_valor =   60 * sin(0.5*M_PI*tSec);
         fijarBetaRotCab(nuevo_valor);
      break;
      case 4: //traslacion bb8 + rotacion eje x
         nuevo_valor = 0.5*M_PI*tSec;
         fijarTraslacion(nuevo_valor);
         fijarAlphaRotX(200*nuevo_valor);
             
      break;

      case 5: //movimiento ojo
       fijarMovimientoOjo(15 *sin(2.7*0.5*M_PI*tSec));
      break;

      case 6:   //inclinación cabeza
       fijarMovCabeza(10*sin(0.5*M_PI*tSec));
      break;
      
   }
}






void bb8::fijarAlphaRotX(const float nuevo_valor){
   * pm_alpha_rot_x = MAT_Rotacion(nuevo_valor, {1,0,0}); 
}

void bb8::fijarAlphaRotY(const float nuevo_valor){
   * pm_alpha_rot_y = MAT_Rotacion(nuevo_valor, {0,1,0}); 
}

void bb8::fijarAlphaRotZ(const float nuevo_valor){
   * pm_alpha_rot_z = MAT_Rotacion(nuevo_valor, {0,0,1}); 
}

void bb8::fijarBetaRotCab(const float nuevo_valor){
   * pm_beta_rot_cab = MAT_Rotacion(nuevo_valor, {0,0,1}); 
}


void bb8::fijarTraslacion(const float nuevo_valor){
   * pm_traslacion = MAT_Traslacion(2*sin(nuevo_valor), 2*cos(2*nuevo_valor),0);
}

void bb8::fijarMovimientoOjo(const float nuevo_valor){
   * pm_mov_ojo = MAT_Rotacion(nuevo_valor,0,1,0);
}

void bb8::fijarMovCabeza(const float nuevo_valor){

      *pm_mov_cab = MAT_Rotacion(nuevo_valor, 0,1,0);
      *pm_mov_cab = MAT_Rotacion(nuevo_valor, 1,0,0);
}