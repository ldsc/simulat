#ifndef CMeioPoroso_Telha_Discretizada_TDMA_h
#define CMeioPoroso_Telha_Discretizada_TDMA_h

/// -------------------  Bibliotecas --------------------------------
#include <iostream>			/// por causa rotinas entrada saída
#include "CInterface.h"    // nodos!
#include "CMeioPoroso_Telha.h"

/// ------------------- Classe CMeioPoroso_Telha_Discretizada_TDMA -----------------------------------
/// @brief Representa o conjunto de todos os nós de um meio poroso unidimensional discretizado (como uma telha).
class CMeioPoroso_Telha_Discretizada_TDMA :
	public CMeioPoroso_Telha
{
//   CFuncao_wl 			funcao_wl;
const double ti_inicial { 22.04 };	///< temperatura inicial telha impermeável
const double ol_inicial { 0.31  };	///< conteúdo de umidade inicio simulação
const double tp_inicial { 24.275};	///< temperatura inicial telha permeável
//const double ol_max = 0.31;		///< =porosidade

protected:
   // Propriedades do volume de controle (do nó da telha)
   double dif[nodos + 1]; 	    	///< vetor difusividade (de cada nó)
   double k[nodos + 1];  		    ///< vetor condutividade (de cada nó)
   double wl[nodos + 1]; 			///< vetor conteúdo massa mássico (de cada nó)
   double h[nodos + 1];    			///< vetor umidade relativa (de cada nó)
   double rov[nodos + 1];	    	///< vetor concentração vapor nos nodos (de cada nó)

   double esp;  					///< espessura filme líquido sobre a telha (instante atual)[mm?]
   double ol[nodos + 1];  			///< conteúdo massa  (instante atual)
   double tp[nodos + 1];	 		///< temperatura telha permeável (no instante atual)
   // Propriedades telha impermeável
   double ti[nodos + 1]; 			///< temperatura da telha impermeável (instante atual)

   double espa;  					///< espessura filme líquido sobre a telha (no instante anterior)
   double ola[nodos + 1];  			///< conteúdo de massa  (no instante anterior)
   double tpa[nodos + 1];	 		///< temperatura telha permeabel (no instante anterior)
   // Propriedades telha impermeável
   double tia[nodos + 1]; 			///< temperatura da telha impermeável (instante anterior)

   double espaa;  					///< espessura filme líquido sobre a telha (no instante anterior ao anterior)
   double olaa[nodos + 1];  		///< conteúdo massa  (no instante anterior ao anterior)
   double tpaa[nodos + 1];	 		///< temperatura telha permeabel (no instante anterior ao anterior)
   // Propriedades telha impermeável
   double tiaa[nodos + 1]; 			///< temperatura da telha impermeável (instante anterior ao anterior)

   double olChuva{0.0}; 			///< conteúdo mássico de umidade relativo a chuva

   double dx {1.0};					///< intervalo de espaço, função da largura da telha e do número de nós.

   //double m{0.0}; 				///< ???//m
   const int n { nodos };			///< Número de nós (volumes de controles)

   /// double errorecorrenciaol,errorecorrenciatp,errorecorrenciaola,errorecorrenciatpa;

public:
  /// Construtor
  CMeioPoroso_Telha_Discretizada_TDMA(){
	DadosDefault();
  }
  /// Destrutor
  ~CMeioPoroso_Telha_Discretizada_TDMA() = default;
   /// Dados default
   void DadosDefault();
   /// Entrada de dados
   void EntrarDadosObjeto();

public:
  /// Saída de dados do objeto para os (tela)
  friend std::ostream& operator<<(std::ostream& os, CMeioPoroso_Telha_Discretizada_TDMA& obj);

  friend class CInterfaceSimuladorTelha;
};

#endif
