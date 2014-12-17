#ifndef CFuncaoAdsorcao_Pablo_h
#define CFuncaoAdsorcao_Pablo_h

/// -------------------  Bibliotecas --------------------------------
#include <cmath>
#include "CFuncaoAdsorcao.h"

/// @brief Representa ensaio adsorção telha argamassa (Pablo).
class CFuncaoAdsorcao_Pablo : public CFuncaoAdsorcao
{
public:
  /// Construtor
  CFuncaoAdsorcao_Pablo() 			{	temperatura_ensaio_adsorcao = 30.0; }
  /// Destrutor
  ~CFuncaoAdsorcao_Pablo()= default;
  /// Dados default
  void DadosDefault() 				{  h = 0.0; 	temperatura_ensaio_adsorcao = 25.0;	};
  /// Chamada por Umidade, inclui dados de ensaios específicos de adsorção (Pablo).
  virtual void ResultadosEnsaio(double& wl) override {
  if( wl <= 0.0014 )
      h = 5000.0 * wl;
  else if( wl > 0.0014 and wl <= 0.0073 )
      h = -9.9696 + 12358.0 * wl;
  else if( wl > 0.0073 and wl <= 0.0216 )
      h =38.05 + 7502.0 * wl - 249425.0 * wl * wl + 1217914.0 * wl * wl * wl;
  else if( wl > 0.0216 )	/// 0.1704
      h = 26.8817 * wl + 95.419;
  }
};
#endif
