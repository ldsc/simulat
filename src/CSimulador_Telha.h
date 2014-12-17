#ifndef CSimulador_Telha_h
#define CSimulador_Telha_h

/// -------------------  Bibliotecas --------------------------------
#include <iostream>			/// por causa rotinas entrada saída
#include <vector>
#include "CMeioPoroso_Telha_Discretizada_TDMA.h"
#include "CTransferenciaCalorMassa.h"
#include "CSolver_TDMA.h"
#include "CFuncoesClima.h"
#include "CFluido.h"
#include "CFuncaoConteudoMassicoWl.h"

#include "CGnuplot.h"

/// ------------------- Classe CSimulador_Telha -----------------------------------
/// @brief Representa um simulador de um meio poroso unidimensional discretizado (acrescenta conceitos simulação).
class CSimulador_Telha :
	public CMeioPoroso_Telha_Discretizada_TDMA,
	public CTransferenciaCalorMassa,
	public CSolver_TDMA
{
  // Objetos agregados
protected:
  CFuncoesClima					funcoesClima;
  CFluido						fluido;
  CFuncaoConteudoMassicoWl 		funcaoConteudoMassicoWl;

  // Atributos (valores médios)
  /// double errorecorrenciaol,errorecorrenciatp,errorecorrenciaola,errorecorrenciatpa;
  // Resultados, valores médios
   double wlm{0.0};                            ///< conteúdo mássico médio ?
   double hm{0.0};                             ///< coeficiente transferência massa médio ?
   double km{0.0};                             ///< condutividade média ?
   double olm{0.0};                            ///< conteúdo massa médio ?
   double tpm{0.0};                            ///< temperatura média telha permeável ?
   double tim{0.0};                            ///< temperatura média telha impermeável ?

protected:
   // Propriedades do Método Numérico - Controle avanço/recuo do intervalo de tempo - dt
   // o programa Simulat tem mecanismo que varia dt entre o intervalo dtmin <= dt <= dtmax.
   double dt{60.0}; 							///< intervalo de tempo da simulação
   double dta{60.0}; 							///< intervalo de tempo da simulação no instante anterior
   double dtmax{60.0};							///< intervalo de tempo máximo da simulação
   double dtmin{1.0};							///< intervalo de tempo mínimo da simulação
   double tempo{0.0};							///< tempo/hora atual da simulação (varia entre 0->24h)

   int recorrencia{2};							///< número de recorrências cálculo acoplamento conteúdos e temperaturas.

   // Propriedades da simulação
//    double tempoInicioSimulacao{0.0};         ///< hora inicial da simulação
   double tempoDecorrido{0.0};                  ///< tempo decorrido da simulação dias
//    double tempoFimSimulacao{96.0};        	///< hora de encerramento da simulação (ex: 24 1 dia, 48 2 dias, 72 3 
   /// double errorecorrenciaol,errorecorrenciatp,errorecorrenciaola,errorecorrenciatpa;

   /// Atributos associados a saída gráfica (CGnuplot)
   std::vector<double> vhora; 	// hora
   std::vector<double> ol0; 	// conteúdo massa volumétrico ponto 0
   std::vector<double> oln_1; 	// conteúdo massa volumétrico ponto n_1
   std::vector<double> tp0; 	// temperatura telha permeável ponto 0
   std::vector<double> tpn_1; 	// temperatura telha permeável ponto n_1
   std::vector<double> ti0; 	// temperatura telha permeável ponto 0
   std::vector<double> tin_1; 	// temperatura telha permeável ponto n_1
   CGnuplot grafico_ol;
   CGnuplot grafico_tp;
   CGnuplot grafico_ti;

public:
  /// Construtor
  CSimulador_Telha() ;
  /// Destrutor
  ~CSimulador_Telha();
   /// Dados default
   void DadosDefault();
   /// Entrada de dados
   void EntrarDadosObjeto();
   /// Chama funções: AvancarTempo() ExecutarFuncoesClima(); Calcular_wl_h_rov_dif_k()
   /// Calcular_ti(); Calcular_ol(); Calcular_tp();
   void Calcular_ti_ol_tp();
   /// Calcula valores médios tm, olm, km, wlm, hm
   void Calcular_olm_tm();		
   /// Próximo passo de tempo da simulação
   //void Next(double tempo, double dt) {};
   /// Mostra na tela resultados da simulação a cada passo.
   void SaidaTela();
   /// Armazena dados nos vetores para poder gerar gráfico no final.
   void SaidaGrafica();
   // Mostra gráficos ol, tp, ti usando 3 gráficos do CGnuplot.
   void SaidaGrafica_FimSaida() ;

private:
   /// Avança o passo de tempo.
   void AvancarTempo();
   // funcoesClima.ExecutarFuncoesClima();
   /// Cálculo dos valores médios de condutividade e difusividade
   void Calcular_wl_h_rov_dif_k();             //****
   /// Cálculo de ti
   inline void Calcular_ti();
   /// Cálculo de ol
   inline void Calcular_ol();
   /// Cálculo de tp
   inline void Calcular_tp();
private:   
   /// Cálculo de aibicidi necessários para cálculo ti
   void Calcular_aibicidi_ti();
   /// Cálculo dos coeficientes aibicidi necessários para cálculo ol.
   void Calcular_aibicidi_ol();
   /// Cálculo dos efeitos da chuva.
   void Calcular_efeitos_chuva_ol();
   /// Cálculo de aibicidi necessários para cálculo tp
   void Calcular_aibicidi_tp();

public:
  /// Saída de dados do objeto para os (tela)
  friend std::ostream& operator<<(std::ostream& os, CSimulador_Telha& obj);

  friend class CInterface_SimuladorTelha;
};

#endif
