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
    agregar( new Material(text, 0.5,0.1,0.3,20) ); //DUDA
    agregar(new MallaRevolPLY("../recursos/plys/lata-pcue.ply", 50));
    ponerNombre("Cuerpo de la lata");
}

LataTapaSup::LataTapaSup(){
    //Textura * tex = new Textura("../recursos/imgs/text-lata-1.jpg");
    agregar( new Material(0.1,0.6,0.3,20)  ); //DUDA
    agregar(new MallaRevolPLY("../recursos/plys/lata-psup.ply", 10));
    ponerNombre("Tapa superior de la lata");
}

LataTapaInf::LataTapaInf(){
    agregar( new Material(0.1,0.6,0.3,20) ); //DUDA
    agregar(new MallaRevolPLY("../recursos/plys/lata-pinf.ply", 10));
    ponerNombre("Tapa inferior de la lata");
}

Peon::Peon(){
    agregar(new MallaRevolPLY("../recursos/plys/peon", 10));
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
    agregar( new Material(tex, 0.2, 0.4, 0.4, 20) ); //DUDA
    agregar(new MallaRevolPLY("../recursos/plys/peon", 50));
}

PeonBlanco::PeonBlanco(){
     ponerColor({1.0,1.0,1.0});
    //Textura * tex = new Textura("../recursos/imgs/text-madera.jpg");
    agregar( new Material(0.1, 0.8, 0.1, 15) ); //DUDA
    agregar(new MallaRevolPLY("../recursos/plys/peon", 50));
}

PeonNegro::PeonNegro(){
    ponerColor({0.0,0.0,0.0});
    //Textura * tex = new Textura("../recursos/imgs/text-madera.jpg");
    agregar( new Material(0.1, 0.1, 0.8, 20) ); //DUDA
    agregar(new MallaRevolPLY("../recursos/plys/peon", 15));
}


LataPeones::LataPeones(){
    agregar(new Peones());
    
    agregar(MAT_Traslacion(0,4,0));
    agregar(new Lata());
    ponerNombre("Lata y peones");
}