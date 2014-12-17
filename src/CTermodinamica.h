#ifndef CTermodinamica_h
#define CTermodinamica_h

#include <cmath>

/// -------------------  classe CTermodinamica ------------------------------------
/// @brief Representa conceitos e funções básicas da termodinâmica.
class CTermodinamica
{
public:
  /// Construtor
  CTermodinamica() = default;
  /// Destrutor
  ~CTermodinamica() = default;
  /// Cálculo da concentração de vapor.
  // pode ser acessada diretamente usando: CTermodinamica::ConcentracaoVapor()
  /// Calcula concentração de vapor em função umidade e temperatura
  /// @param: umidade entre 0 e 1
  /// @param: temperatura em Celsius
  static inline double ConcentracaoVapor( double umidade, double temperatura ) {
   return  PressaoVapor( temperatura ) * umidade * 18.0 / ( 8313.0 * ( 273.0 + temperatura ) );
  }
  
private:
  /// Cálculo da pressão de vapor.
  /// @param: temperatura em Celsius.
  static inline double PressaoVapor( double t ) {
   t = t + 273.16; 							// Converte temperatura para kelvin
   double pvs = 1000.0 * pow( 10, ( 30.5905 - 8.2 * log10( t ) + 2.4804e-3 * t - 3142.32 / t ) );
   return ( pvs );
  }
};
#endif
