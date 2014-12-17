#ifndef CSimulador_Telha_GanhosEnergia_h
#define CSimulador_Telha_GanhosEnergia_h

/// -------------------  Bibliotecas --------------------------------
#include <iostream>			/// por causa rotinas entrada saída
#include "CSimulador_Telha.h"

/// ------------------- Classe CSimulador_Telha_GanhosEnergia -----------------------------------
/// @brief Representa um simulador de meio poroso tridimensional discretizado com cálculos ganhos energia.
class CSimulador_Telha_GanhosEnergia :
	public CSimulador_Telha
{
protected:
   /// As linhas abaixo se referem as trocas de energia
   /// o arquivo variavel.doc descreve o significado de cada uma delas
   double gev{0.0};                                  ///< 
   double giv{0.0};                                  ///< 
   double gesp{0.0};                                 ///< 
   double gec{0.0};                                  ///< ganho externo convecção
   double gic{0.0};                                  ///< ganho interno convecção
   double gecl{0.0};                                 ///< ganho externo calor latente
   double gicl{0.0};                                 ///< ganho interno calor latente
   double geroc{0.0};                                ///< ganho externo radiação onda curta
   double gerol{0.0};                                ///< ganho externo radiação onda longa
   double gir{0.0};                                  ///< ganho interno radicao
   double bm{0.0};                                   ///< balanco massa
   double be{0.0};                                   ///< balanco energia
   double geci{0.0};                                 ///< ganho externo convecção
   double gici{0.0};                                 ///< ganho interno convecção
   double geroci{0.0};                               ///< ganho externo radiação onda curta
   double geroli{0.0};                               ///< ganho externo radiação onda longa
   double giri{0.0};                                 ///< ganho interno radicao

public:
  /// Construtor
  CSimulador_Telha_GanhosEnergia(){
	DadosDefault();
  }
  /// Destrutor
  ~CSimulador_Telha_GanhosEnergia() = default;
   /// Dados default
   void DadosDefault();
   /// Mostra na tela resultados da simulação a cada passo.
   //void SaidaTela();

//    /// Cálculo do tempo atual da simulação
//    inline void AvancarTempo();

private:
   /// Cálculo ganhos energia tp
   void CalcularGanhosEnergia_tp();
   /// Cálculo ganhos energia ti
   void CalcularGanhosEnergia_ti();

public:
  /// Saída de dados do objeto para os (tela)
  friend std::ostream& operator<<(std::ostream& os, CSimulador_Telha_GanhosEnergia& obj);

  friend class CInterface_SimuladorTelha;
};

#endif
