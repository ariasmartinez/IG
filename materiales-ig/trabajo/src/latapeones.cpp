#include "latapeones.h"
#include "malla-revol.h"

Lata::Lata(){
   

   agregar(new LataTapaSup());
   
   agregar(new LataTapaInf());
   agregar(new LataCentral());
   ponerNombre("Lata");
}

LataCentral::LataCentral(){
    Textura * text = new Textura("../recursos/imgs/lata-pepsi.jpg");
    agregar( new Material(text, 0.6,0.3,0.7,100) ); //DUDA
    
    agregar(new MallaRevolPLY("../recursos/plys/lata-pcue.ply", 20));
    ponerNombre("Cuerpo de la lata");
}

LataTapaSup::LataTapaSup(){
    //Textura * tex = new Textura("../recursos/imgs/text-lata-1.jpg");
    agregar( new Material(0.6,0.6,1.0,100)  ); //DUDA
    agregar(new MallaRevolPLY("../recursos/plys/lata-psup.ply", 20));
    ponerNombre("Tapa superior de la lata");
}

LataTapaInf::LataTapaInf(){
    agregar( new Material(0.6,0.6,1.0,100) ); //DUDA
    agregar(new MallaRevolPLY("../recursos/plys/lata-pinf.ply", 20));
    ponerNombre("Tapa inferior de la lata");
}

Peon::Peon(){
    agregar(new MallaRevolPLY("../recursos/plys/peon", 20));
}


Peones::Peones(){
    agregar(new PeonMadera());
    agregar(MAT_Traslacion(-4,0,0));
    agregar(new PeonBlanco());
    agregar(MAT_Traslacion(2,0,0));
    agregar(new PeonNegro());
}

PeonMadera::PeonMadera(){
    Textura * tex = new Textura("../recursos/imgs/text-madera.jpg");
    agregar( new Material(tex, 0.8, 1.0, 1.0, 100) ); //DUDA
    agregar(new MallaRevolPLY("../recursos/plys/peon", 20));
}

PeonBlanco::PeonBlanco(){
     ponerColor({1.0,1.0,1.0});
    //Textura * tex = new Textura("../recursos/imgs/text-madera.jpg");
    agregar( new Material(0.8, 1.0, 0.3, 100) ); //DUDA
    agregar(new MallaRevolPLY("../recursos/plys/peon", 20));
}

PeonNegro::PeonNegro(){
    ponerColor({0.0,0.0,0.0});
    //Textura * tex = new Textura("../recursos/imgs/text-madera.jpg");
    agregar( new Material(0.8, 0.3, 1.0, 100) ); //DUDA
    agregar(new MallaRevolPLY("../recursos/plys/peon", 20));
}


LataPeones::LataPeones(){
    agregar(new Peones());
    agregar(MAT_Escalado(3.0,3.0,3.0));
    agregar(MAT_Traslacion(1.0, -0.5,0));
    agregar(new Lata());
    ponerNombre("Lata y peones");
}