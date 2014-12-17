
/// -------------------  Bibliotecas --------------------------------
//#include <cassert>
#include <fstream>			/// por causa ifstream e ofstream ponteiros arquivos
#include <iostream>			/// por causa rotinas entrada saída
#include <iomanip>			/// manipuladores, como setw()
//#include <cmath>			/// por causa funções matemáticas

#include "CInterface_SimuladorTelha.h"
using namespace std;

/// ---------------------------------------------------------------------------
/// ************  Implementação funções classe CInterface_SimuladorTelha     *********
/// ---------------------------------------------------------------------------
/// Dados default
void CInterface_SimuladorTelha::DadosDefault()
{
  simuladorTelha.DadosDefault();
  tempoInicioSimulacao = 0.0;       	/// hora inicial da simulação
  tempoFimSimulacao = 240.0;       		/// hora de encerramento da simulação (ex: 24=1 dia, 48240=10dias

  tipoSaida = 'g';
  nomeArquivoSaidaDisco = "simulat.saida";
  tempoInicioSaida =  0.0;
  intervaloSaidaResultados = 600.0;		/// corresponde a um pixel
  contadorPassoSaida = 7200000.0;		/// para garantir saída 1 passo
  // fout;								/// acesso arquivo saída
}

/// ---------------------------------------------------------------------------
/// função de controle principal  		/// função global de simulação
/// ---------------------------------------------------------------------------
///  *-*-*-*-*
void CInterface_SimuladorTelha::ExecutarSimulador() {
   cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
   FolhaRosto();		        		/// mostra folha de rosto nome programa, autor, laboratorio
   EntrarDadosObjeto();					/// executa funções de entrada de todas as classes
   InicioSaida();		        		/// executa parte inicial da saida (cabecalhos)
   do {									/// rotina cálculo ol,t,ti, considerando oscilações e variando dt
         simuladorTelha.Calcular_ti_ol_tp();
         if( ( tempoInicioSimulacao + simuladorTelha.tempoDecorrido ) >= tempoInicioSaida )
            Saida();		    		/// função saída resultados mode terminal e modo gráfico
      }

   while( ( tempoInicioSimulacao + simuladorTelha.tempoDecorrido ) <= tempoFimSimulacao );
   FimSaida();
}

/// ---------------------------------------------------------------------------
/// Implementação da folha de rosto
/// apresentacao inicial do programa ao usuario
/// com informações basicas, de onde procurar ajuda.
/// ---------------------------------------------------------------------------
/// Implementação função Carimbo
/// carimbo apresentado início programa, e para algumas saídas de tela.
// void CInterface_SimuladorTelha::Carimbo() {
//    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
//    cout << "\n\t.___________________________________________________________.";
//    cout << "\n\t|                                                           |";
//    cout << "\n\t| SIMULAÇÃO DA TRANSFÊRENCIA DE CALOR E UMIDADE EM TELHAS   |";
//    cout << "\n\t|     Mestrado Engenharia Civil - NCC - LMPT - SITERPA      |";
//    cout << "\n\t|                    André Duarte Bueno                     |";
//    cout << "\n\t.___________________________________________________________.";
// }

void CInterface_SimuladorTelha::FolhaRosto() {
   Carimbo();
   cout << "\n\t_____________________________________________________________";
   cout << "\n\t      Para   maiores  informações  leia  os   arquivos";
   cout << "\n\t      explica.doc..................como rodar programa";
   cout << "\n\t      balanco.doc............explica o fenomeno físico";
   cout << "\n\t      variavel.doc...........variáveis usadas programa";
   cout << "\n\t      readme.exe.........apresenta os documentos acima";
   cout << "\n\t_____________________________________________________________";
   cout << "\n\t		Pressione enter para continuar";
   cout << "\n\t_____________________________________________________________\a";
   cin.get();
}

/// ---------------------------------------------------------------------------
/// impementacao função entrada dados classe saída
void CInterface_SimuladorTelha::EntrarDadosObjeto() {
  Carimbo();
   cout << "\n\nUsar dados de saída default (d) ou dados novos (n): ";
   char resp;
   cin.get( resp );
   cin.get();

  if( resp == 'd' or resp == 'D' )
	DadosDefault();
  else {
	cout << "\nEntre com os valores que serão solicitados.";
	cout << "\n==> Objeto CInterface_SimuladorTelha:"
 		 << "\n==> Objeto CInterface_SimuladorTelha -> Agregados:";
//cerr << "\nAntes de simuladorTelha.EntrarDadosObjeto();";
	simuladorTelha.EntrarDadosObjeto();
//cerr << "\nDepois de simuladorTelha.EntrarDadosObjeto();";
	
    cout << "\n==> Objeto CInterface_SimuladorTelha -> Atributos:";
	cout << "\nEntre com o tempo início simulação  (tempoInicioSimulacao = " << tempoInicioSimulacao << "): ";
	cin >> tempoInicioSimulacao;
	simuladorTelha.tempoDecorrido = simuladorTelha.tempo = tempoInicioSimulacao;
	cout << "\nEntre com o tempo final da simulação em horas (tempoFimSimulacao = " << tempoFimSimulacao << "): ";
	cout << "\n\t(1d=24, 2d=48, 3d=72, 4d=96, 5d=120h, 6=144h, 7=168, 8d=192h, 10=240): ";
	cin >> tempoFimSimulacao;

	int precisaosaida = 4;
	cout << "\nEntre com a precisão desejada na saída (" << precisaosaida << "): ";
	cin >> precisaosaida;
	cout.precision( precisaosaida );	/// precisao da saída casas decimais
	cout << "\nEntre com o tempo de início da saída dos resultados (tempoInicioSaida = " << tempoInicioSaida << ")h: ";
	cin >> tempoInicioSaida;
	cout << "\nEntre com o intervalo de saída dos resultados (intervaloSaidaResultados = "
		 << intervaloSaidaResultados << " ): ";
	cin >> intervaloSaidaResultados;
	cin.get();
	
	cout 	<< "\nEntre com o tipo de saída dos resultados, t=modoTexto, g=modoGráfico, a=ambos (default = "
			<< tipoSaida << " ): ";
	cin >> tipoSaida;
	cin.get();
  }
}

/// ---------------------------------------------------------------------------
/// Implementação inicio_saída
/// através de uma estrutura swith seleciona a tabela(início saída dados)
/// monta estrutura inicial de apresentacao dos dados da simulação
/// como nome das vari veis que são apresentadas ao usu rio,
/// estrutura da saída gráfica, como eixos,titulos,...
void CInterface_SimuladorTelha::InicioSaida() {
   LimparTela();
   Carimbo();
}

/// ---------------------------------------------------------------------------
/// Implementação Saida
/// tempo inicial de saída define hora decimal em que os resultados
/// comecam a ser apresentados.Os dados só serão apresentados depois de atingido o tempoInicioSaida.
/// Através de uma estrutura switch seleciona a saída de dados definida pelo usuário.
void CInterface_SimuladorTelha::Saida() {
   contadorPassoSaida = contadorPassoSaida + simuladorTelha.dta;

   if( contadorPassoSaida >= intervaloSaidaResultados ) {
         simuladorTelha.CalcularGanhosEnergia_tp();	/// ganho energia tp
         simuladorTelha.CalcularGanhosEnergia_ti();	/// ganho energia ti
         simuladorTelha.Calcular_olm_tm();			/// valores médios de olm, tm, km, wlm, hm, tmi
         contadorPassoSaida = 0.0;
		if( tipoSaida == 'g' or tipoSaida == 'G')
				simuladorTelha.SaidaGrafica();		/// Saída usando gráficos gnuplot
		else if ( tipoSaida == 't' or tipoSaida == 'T')
				simuladorTelha.SaidaTela();			/// Saída só na tela
		else	{
				simuladorTelha.SaidaGrafica();		/// Saída usando gráficos gnuplot
				simuladorTelha.SaidaTela();			/// Saída só na tela
		}
      }
}

/// ---------------------------------------------------------------------------
///  impplementacao função FimSaida
///  em função tipo de saída seleciona uma finalizacao para a apresentacao
///  dos dados.
void CInterface_SimuladorTelha::FimSaida() {
	// se for saida gráfica não mostrou dados na tela, aqui mostra resultados finais
	if( tipoSaida == 'g' or tipoSaida == 'G' or tipoSaida == 'a' or tipoSaida == 'A') {
		simuladorTelha.SaidaTela();					/// Saída só na tela.
		simuladorTelha.SaidaGrafica_FimSaida();		/// Mostra gráfico após final da simulação.
	}

	cout << "\a\a";
	cout <<"\n________________________________________________________________________FIM____\n";
	Carimbo();
}

/// ---------------------------------------------------------------------------
/// Implementação função readme, leitura de arquivos de informaçao
///  *-*-*-*-*
void CInterface_SimuladorTelha::Leiame()
{
   ///  toupper
   char resposta, ch;

   do				/// este do while permite o acesso ao Help, se não foi selecionado
      /// o Help continua o processamento.
      {
         Carimbo();
         cout <<   "\t___________________________________________________________";
         cout << "\n\t\t\tSelecione a opção que deseja  ";
         cout << "\n\t___________________________________________________________";
         cout << "\n\t   -->Arquivos de informações do programa SIMULAT.EXE<--";
         cout << "\n\n\t\texplica.doc.......................(a)";
         cout << "\n\t\tbalanco.doc.......................(b)";
         cout << "\n\t\tvariavel.doc......................(c)";
         cout << "\n\t\tRetornar ao Programa Simulat......(d)";
         cout << "\n\t\tAbandonar o Programa (Quit).......(e)";
         cout << "\n\t___________________________________________________________: ";
         cin.get( resposta );	/// =getche();
         cin.get();
         Carimbo();

         if( resposta == 'a' or resposta == 'A' ) {
               ifstream explica( "explica.doc" );			/// ponteiro para arquivo explica
               while( explica.get( ch ) ) {					/// pega caracter de explica, armazena
                     cout << ch;							/// mostra caracter na tela
                     if( ch == '|' ) {
                           cin.get();	
                           cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
                        }
                  }
            }
         if( resposta == 'c' or resposta == 'C' ) {
               ifstream variavel( "variavel.doc" );			/// abre ponteiro para arquivo variavel
               while( variavel.get( ch ) ) {				/// enquanto não chegar ao fim
															/// le caracter e armazena em ch
                     cout << ch;							/// mostra caracter na tela
                     if( ch == '|' ) {
                           cin.get();						/// pausa
                           cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
                        }
                  }
            }
         if( resposta == 'b' or resposta == 'B' ) {
               ifstream balanco( "balanco.doc" );			/// abre arquivo para arquivo balanco
               while( balanco.get( ch ) ) {					/// enquanto não chegar ao fim
                     cout << ch;							/// mostra caracter na tela
                     if( ch == '|' ) {
                           cin.get();						/// pausa
                           cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
                        }
                  }
            }
      }
   while( resposta == 'a' or resposta == 'A' or resposta == 'b'
          or resposta == 'B' or resposta == 'c' or resposta == 'C' );
}


std::ostream& operator<<(std::ostream& os, CInterface_SimuladorTelha& obj)
{
     os	<< "\ntempoInicioSimulacao = " 		<< obj.tempoInicioSimulacao
    	<< "\ntempoFimSimulacao = " 		<< obj.tempoFimSimulacao
    	<< "\ntipoSaida = " 				<< obj.tipoSaida
		<< "\nnomeArquivoSaidaDisco = " 	<< obj.nomeArquivoSaidaDisco
		<< "\ntempoInicioSaida = " 			<< obj.tempoInicioSaida
		<< "\nintervaloSaidaResultados = " 	<< obj.intervaloSaidaResultados;
}

