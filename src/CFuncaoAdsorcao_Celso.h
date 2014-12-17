#ifndef CFuncaoAdsorcao_Celso_h
#define CFuncaoAdsorcao_Celso_h

/// -------------------  Bibliotecas --------------------------------
#include <cmath>
#include "CFuncaoAdsorcao.h"

/// @brief Representa ensaio adsorção telha argamassa (Celso Perez Fernandes).
class CFuncaoAdsorcao_Celso : public CFuncaoAdsorcao
{
public:
  /// Construtor
  CFuncaoAdsorcao_Celso() 			{ temperatura_ensaio_adsorcao = 25.0; }
  /// Destrutor
  ~CFuncaoAdsorcao_Celso()= default;
  /// Dados default
  void DadosDefault() 				{  h = 0.0; 	temperatura_ensaio_adsorcao = 25.0;	};

  /// Chamada por Umidade, inclui dados de ensaios específicos de adsorção (Celso).
  virtual void ResultadosEnsaio(double& wl) override {
  if( wl > 0.0001 and wl <= 0.015671 )
	  h = 2.735972 + 0.300513 * log( wl / 10.0 );
  else if( wl > 0.015671 and wl <= 0.056975 )
	  h = 2.7164 - 57.6623 * wl / 10.0 + 2.2017 * pow( wl / 10,3 ) +0.094077 * log( pow( wl / 10.0, 3.0 ) );
  else if( wl > 0.056975 )	/// 0.1812)
	  h = 0.95623 + 0.2415 * wl;
  }
};
#endif
