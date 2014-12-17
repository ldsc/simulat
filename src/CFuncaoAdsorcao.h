#ifndef CFuncaoAdsorcao_h
#define CFuncaoAdsorcao_h

/// -------------------  Bibliotecas --------------------------------
#include <iostream>			/// por causa rotinas entrada saída

/// ------------------- Classe CFuncaoAdsorcao -----------------------------------
/// @brief Calcula a umidade a partir das curvas de adsorção do material (correlações fornecidas pelo usuário).
/// Resultados ensaio adsorção telha permeável (André Bueno).
// redefinivel
class CFuncaoAdsorcao
{
protected:
  double h{0.0};
  double temperatura_ensaio_adsorcao{30.0};
public:
  /// Construtor
  CFuncaoAdsorcao() : h {0.0}, temperatura_ensaio_adsorcao { 30.0}	{}
  /// Destrutor
  ~CFuncaoAdsorcao()= default;
  /// Dados default
  void DadosDefault() 					{  h = 0.0; 	temperatura_ensaio_adsorcao = 30.0;	};
  /// Entrada de dados (associados aos ensaios)
  void EntrarDadosFuncao() ;
  /// Cálculo da umidade em função do conteúdo massa mássico wl (resultado do ensaio de adsorção).
  double Umidade( double wl, double temperatura);
  /// Cálculo da umidade em função do conteúdo massa mássico wl (resultado do ensaio de adsorção).
  double operator()( double wl, double temperatura) {
  return Umidade( wl, temperatura );
  }
  protected:
  /// Chamada por Umidade, inclui dados de ensaios específicos de adsorção.
  virtual void ResultadosEnsaio( double& wl );
  private:
  /// Corrige umidade considerando temperatura da simulação e temperatura em que ensaio foi realizado
  void CorrecaoTemperatura( double& temperatura );
  public:
  /// Saída de dados do objeto para os (tela)
  friend std::ostream& operator<<(std::ostream& os, CFuncaoAdsorcao& obj);
};
using CFuncaoAdsorcao_Bueno = CFuncaoAdsorcao;
#endif
