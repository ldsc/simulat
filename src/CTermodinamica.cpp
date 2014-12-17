/// -------------------  Bibliotecas --------------------------------
#include "CTermodinamica.h"

// /// ---------------------------------------------------------------------------
// /// Calcula concentração de vapor em função umidade e temperatura
// /// @param: umidade entre 0 e 1
// /// @param: temperatura em Celsius
// double CTermodinamica ::ConcentracaoVapor( double umidade, double temperatura ) {
// //    double pressaoVaporSaturacao = PressaoVapor( temperatura );
// //    double concentracaoVapor = pressaoVaporSaturacao * umidade * 18.0 / ( 8313.0 * ( 273.0 + temperatura ) );
// //    return  concentracaoVapor ;
//    return  PressaoVapor( temperatura ) * umidade * 18.0 / ( 8313.0 * ( 273.0 + temperatura ) );
// }
// 
// /// ---------------------------------------------------------------------------
// /// Cálculo da pressão de vapor.
// /// @param: temperatura em Celsius.
// double CTermodinamica ::PressaoVapor( double t ) {
//    t = t + 273.16; 							// Converte temperatura para kelvin
//    double pvs = 1000.0 * pow( 10, ( 30.5905 - 8.2 * log10( t ) + 2.4804e-3 * t - 3142.32 / t ) );
//    return ( pvs );
// }
