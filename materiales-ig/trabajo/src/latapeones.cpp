#include "latapeones.h"
#include "malla-revol.h"

LataCocaCola::LataCocaCola(){
   

   agregar(new LataTapaSup());
   
   agregar(new LataTapaInf());
   
   Textura * text = new Textura("../recursos/imgs/lata-coke.jpg");
   agregar( new Material(text, 0.6,0.3,0.7,100) );
    
   agregar(new MallaRevolPLY("../recursos/plys/lata-pcue.ply", 20));
  
   ponerNombre("LataCocaCola");
   ponerIdentificador(1);
}



LataTapaSup::LataTapaSup(){
  
    agregar( new Material(0.6,0.6,1.0,30)  ); 
    agregar(new MallaRevolPLY("../recursos/plys/lata-psup.ply", 20));
    ponerNombre("Tapa superior de la lata");
    ponerIdentificador(-1);
}

LataTapaInf::LataTapaInf(){
    agregar( new Material(0.6,0.6,1.0,30) ); 
    agregar(new MallaRevolPLY("../recursos/plys/lata-pinf.ply", 20));
    ponerNombre("Tapa inferior de la lata");
    ponerIdentificador(-1);
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
    TexturaPeon * tex = new TexturaPeon("../recursos/imgs/text-madera.jpg");
    
    agregar( new Material(tex, 0.1, 0.7, 1.0, 100) ); 
    agregar(new MallaRevolPLY("../recursos/plys/peon", 20));
    ponerNombre("Peon Madera");
    ponerIdentificador(2);
}

PeonBlanco::PeonBlanco(){
     ponerColor({1.0,1.0,1.0});
  
    agregar( new Material(0.1, 0.8, 0.0, 100) );
    agregar(new MallaRevolPLY("../recursos/plys/peon", 20));
    ponerNombre("Peon Blanco");
    ponerIdentificador(3);
}

PeonNegro::PeonNegro(){
    ponerColor({0.0,0.0,0.0});
    
    agregar( new Material(0.8, 0.3, 1.0, 100) );
    agregar(new MallaRevolPLY("../recursos/plys/peon", 20));
    ponerNombre("Peon negro");
    ponerIdentificador(4);
}


LataPeones::LataPeones(){
    agregar(MAT_Traslacion(1.5, 0.0,0.0));
    agregar(new Peones());
    agregar(MAT_Escalado(3.0,3.0,3.0));
    agregar(MAT_Traslacion(-1.0, -0.5,-1.0));
    agregar(new LataCocaCola());
    ponerNombre("Lata y peones");
}

VariasLatasPeones::VariasLatasPeones(){
    agregar(new LataPeones());
     agregar(MAT_Escalado(3.0,3.0,3.0));
    agregar(MAT_Traslacion(-1.5, -0.5,-1.0));
    agregar(new LataUGR());
    agregar(MAT_Traslacion(2.0, 0.0,0.0));
    agregar(new LataPepsi());
  

}

LataUGR::LataUGR(){
    agregar(new LataTapaSup());
   
   agregar(new LataTapaInf());
 
  
   Textura * text = new Textura("../recursos/imgs/window-icon.jpg");
   agregar( new Material(text, 0.6,0.3,0.7,100) );
    
   agregar(new MallaRevolPLY("../recursos/plys/lata-pcue.ply", 20));

   ponerNombre("LataUgr");
   ponerIdentificador(5);
}

LataPepsi::LataPepsi(){
     agregar(new LataTapaSup());
   
   agregar(new LataTapaInf());

    Textura * text = new Textura("../recursos/imgs/lata-pepsi.jpg");
   agregar( new Material(text, 0.6,0.3,0.7,100) );
    
   agregar(new MallaRevolPLY("../recursos/plys/lata-pcue.ply", 20));
   
   ponerNombre("LataPepsi");
   ponerIdentificador(6);
}