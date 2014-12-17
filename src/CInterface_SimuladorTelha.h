#ifndef CInterface_SimuladorTelha_h
#define CInterface_SimuladorTelha_h

#include "CInterface.h"
#include "CSimulador_Telha_GanhosEnergia.h"

/// -------------------  Bibliotecas --------------------------------
#include <ios>
#include <iostream>			/// por causa rotinas entrada saída
#include <fstream>			/// por causa rotinas entrada saída disco

/// ------------------------- Classe CInterface_SimuladorTelha -------------------------------------
/// @brief Interface em modo texto para CSimulador_Telha_GanhosEnergia.
/// Contém as funções necessárias para gerar as saídas para tela, impressora, disco e gráficas.
/// Posteriormente deverá ser desmembrada (ex: tela/disco/impressora).
/// Nota: Quando gerou a versão para Unix eliminou saída gráfica pois usava drives e bibliotecas 
/// disponíveis apenas para DOS.
/// Quando gerou versão 4, com divisão das classes, eliminou saíuda para impressora,
/// o motivo, não se vende mais este tipo de impressora.
/// *-*-*-*-*
/// Todos os comandos gráficos estão formatados para o DOS e consideram que o seu monitor aceita o modo vga!!!
/// Na versão para UNIX e GNU-LINUX a parte gráfica do DOS foi desativada.
class CInterface_SimuladorTelha : public CInterface
{
protected:

/// Objetos agregados
//	CSimulador_Telha	simuladorTelha;
	CSimulador_Telha_GanhosEnergia	simuladorTelha;
	// 	CSolver_TDMA				solver_tdma;
	// 	CMeioPoroso_Telha 			telha;
	// 	CTransferenciaCalorMassa	transcal;
	//	CFuncao_wl 					funcao_wl;

protected:
   double tempoInicioSimulacao{0.0};            ///< hora inicial da simulação
   double tempoFimSimulacao{96.0};        		///< hora de encerramento da simulação (ex: 24 1 dia, 48 2 dias, 72 3 

   // Propriedades/atributos associados a interface em modo texto
   std::ofstream fout;							///< acesso arquivo saída
   char tipoSaida{'g'};                         ///< definição tipo saída
   std::string nomeArquivoSaidaDisco{"simulat.saida"};///< definição nome arquivo saída disco
   double tempoInicioSaida{0.0};                ///< hora em que a saída começa a ser apresentada na tela
   double intervaloSaidaResultados{600.0};      ///< intervalo de tempo em que a saída é apresentada
   double contadorPassoSaida{7200000.0};        ///< contador que controle passo de saída

//--------------------------------------------------------------------------------------Métodos
public:
   /// Construtor
//    CInterface_SimuladorTelha(CFuncoesClima& _fc, CFluido& _f )
//    : funcoesClima(_fc), fluido(_f) {
// 	  CSimulador_Telha(double& _dt, double& _dta, double& _dtmax, double& _dtmin, 
// 									  double& _tempo, CFuncoesClima _fc, CFluido _f)

   CInterface_SimuladorTelha( ) {
	std::cout.precision( 4 );  /// definição padrão para precisão da saída na tela
	fout.setf( std::ios::fixed | std::ios::left | std::ios::dec );
	DadosDefault();
   }
   /// Destrutor
   ~CInterface_SimuladorTelha() = default;

   /// Dados default
   void DadosDefault();
   /// Entrada de dados
   void EntrarDadosObjeto();

   /// Construtor sobrecarregado para entrada n
   /// CInterface_SimuladorTelha(unsigned int númeropontos);
   /// Executa a simulação
   void ExecutarSimulador();
   /// Função para encerramento do programa
   //int c_break( void );

	//static void Carimbo();				///< Carimbo titulo tese
protected:
   inline void LimparTela() {
	 std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
   }
   void Leiame();						///< Função de help/ajuda
   void FolhaRosto();					///< Tela inicial
   //void Carimbo();					///< Carimbo titulo tese
   //void EntrarDadosObjeto();			///< Entrada dados do objeto
   void InicioSaida();					///< Inicia apresentacao resultados
   void Saida();						///< Verifica se é para chamar SaidaTela
   void SaidaTela();					///< Apresenta saída dados parciais
   void FimSaida();						///< Finaliza apresentacao resultados

public:
  /// Saída de dados do objeto para os (tela)
  friend std::ostream& operator<<(std::ostream& os, CInterface_SimuladorTelha& obj);
};

#endif
