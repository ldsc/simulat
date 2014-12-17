/// -------------------  Bibliotecas --------------------------------
//#include <cassert>
//#include <fstream>			/// por causa ifstream e ofstream ponteiros arquivos
#include <iostream>			/// por causa rotinas entrada saída
//#include <iomanip>			/// manipuladores, como setw()
#include <cmath>			/// por causa funções matemáticas

#include "CInterface.h"
#include "CFuncoesClima.h"
#include "CTermodinamica.h"
using namespace std;

/// ---------------------------------------------------------------------------
/// Implementação função Dados default
void CFuncoesClima::DadosDefault() {
  text = 25.0;
  tint = 25.0;
  hext = 0.95;
  hint = 0.75;
  //rove = 0.017;
  rove = CTermodinamica::ConcentracaoVapor( hext, text );
  //rovi = 0.017;
  rovi = CTermodinamica::ConcentracaoVapor( hint, tint );
  radoc = 0.0;
  radol = 0.0;
  retardo = 0.0;
  amortecimento = 1.0;
  horaInicioChuva = 0.0;
  horaFimChuva = 0.0;
  precipitacao = 0.0;
  respTemperaturaInterna = 'c';
  respHumidadeExterna = 'c';
  respHumidadeInterna = 'c';
  //ExecutarFuncoesClima(0.0);
}

/// ---------------------------------------------------------------------------
/// Implementação função EntrarDadosObjeto
/// permite a entrada dos dados das funções de forma que se possa utilizar funções diferentes para os cálculos.
void CFuncoesClima::EntrarDadosObjeto() {
// 	cout<< "\nCFuncoesClima -> Atributos :\n text = " << text << " tint = " << tint 
// 		<< " hext = "<< hext << " hint = " << hint 
// 		<< " radoc = " << radoc << " radol = " << radol
	CInterface::Carimbo();
	cout << *this;
	cout<< "\n\nOpções para os atributos climáticos:"
		<< "\nSerão constantes e usarei dados default acima apresentados..............d"
		<< "\nSerão constantes mas quero redefinir seus valores.......................c"
		<< "\nQuero definir quais serão constantes e quais irão variar (sem chuva)....n"
		<< "\nQuero definir quais serão constantes e quais irão variar (com chuva)....h: ";
   char resp;
   cin.get( resp );
   cin.get();
   if( resp == 'd' or resp == 'D' ) 
	   return;
   if( resp == 'c' or resp == 'C' ) {
		cout << "\nEntre com a temperatura externa constante (text = "<< text << "): ";
		cin >> text;
		cin.get();
		cout << "\nEntre com a temperatura interna constante (tint = "<< tint << "): ";
		cin >> tint;
		cin.get();
		cout << "\nEntre com a umidade externa constante = "<< hext << ": ";
		cin >> hext;
		cin.get();
		cout << "\nEntre com a umidade interna constante = "<< hint << ": ";
		cin >> hint;
		cin.get();
		cout << "\nEntre com a radiação de onda curta constante = "<< radoc << ": ";
		cin >> radoc;
		cin.get();
		cout << "\nEntre com a radiação de onda longa constante = "<< radol << ": ";
		cin >> radol;
		cin.get();
   }
   if( resp == 'n' or resp == 'N'  or resp == 'h' or resp == 'H' ) {
         cout << "\nTemperatura Interna constante (c) ou função temperatura externa (e):";
         cin.get( respTemperaturaInterna );
         cin.get();
         if( respTemperaturaInterna == 'e' or respTemperaturaInterna == 'E' ) {
               cout << "\namortecimento térmico para cálculo (tint) (amortecimento = " << amortecimento << "): ";
               cin >> amortecimento;
               cout << "retardo térmico para  cálculo (tint) (retardo = "<< retardo << "): ";
               cin >> retardo;
               cin.get();
            }
         else {
               cout << "\nEntre com a temperatura interna constante (tint = "<< tint << "): ";
               cin >> tint;
               cin.get();
            }

         cout << "\nUmidade externa constante (c) ou função temperatura externa (e):";
         cin.get( respHumidadeExterna );
         cin.get();
         if( respHumidadeExterna == 'c' or respHumidadeExterna == 'C' ) {
               cout << "\nUmidade Externa = "<< hext << ": ";
               cin >> hext;
               cin.get();
            }

         cout << "\nUmidade interna constante (c) ou função temperatura interna (i):";
         cin.get( respHumidadeInterna );
         cin.get();
         if( respHumidadeInterna == 'c' or respHumidadeInterna == 'C' ) {
               cout << "\nUmidade Interna = "<< hint << ": ";
               cin >> hint;
               cin.get();
            }
      }

   if( resp == 'h' or resp == 'H' ) {
         // Entra-se com a precipitacao media mensal e com o número de dias de chuva.
	     // Irá calcular  a precipitação média nos dias de chuva (mm/mes)*(mes/30dias).
         cout << "\n\nEntre com a precipitação mensal: ";
         cin >> precipitacao;
         cout << "\nConsidera-se que a chuva de todo o mês ocorreu em quantos dias: ";
         double diasChuva;
         cin >> diasChuva;
         precipitacao = precipitacao / diasChuva; /// 30mm/mes 1mm/dia
         cout << "\nEntre com a hora inicial da chuva (lembre-se que a simulação é ciclica - 24h):";
         cin >> horaInicioChuva;
         cout << "\nEntre com a hora final da chuva: ";
         cin >> horaFimChuva;
         cin.get();
      }
    // os atributos rove e rovi são função umidades e temperaturas, como foram modificados, preciso atualizar
	rove = CTermodinamica::ConcentracaoVapor( hext, text );
	rovi = CTermodinamica::ConcentracaoVapor( hint, tint );
}

/// ---------------------------------------------------------------------------
/// Chama todas as funções da classe CFuncoesClima e calcula as variáveis da classe para o tempo atual
void CFuncoesClima::ExecutarFuncoesClima( double hora ) {
   /// Observe que uma função pode usar os valores calculados pela função anterior, a seguencia deve estar correta
   text = TemperaturaExterna( hora );			/// cte ou função tempo

   if( respTemperaturaInterna == 'e' or respTemperaturaInterna == 'E' )
      TemperaturaInterna( hora );	            /// cte ou função text,retardo,amortecimento

   if( respHumidadeExterna == 'e' or respHumidadeExterna == 'E' )
      UmidadeExterna();	                		/// cte ou função tempo

   if( respHumidadeInterna == 'i' or respHumidadeInterna == 'i' )
      UmidadeInterna();	                		/// cte ou função tempo

   rove = CTermodinamica::ConcentracaoVapor( hext, text );	/// função text(externa)  hext
   rovi = CTermodinamica::ConcentracaoVapor( hint, tint );	/// função tint(interna)  hint
   RadiacaoOndaCurta( hora );                	/// cte ou função tempo
   RadiacaoOndaLonga( hora );                	/// cte ou função tsuperficial fradol(t[0] ou ti[0])
   /// CalculoEmissividade();                   /// função tempo? incluir função emissividade
}

/// ---------------------------------------------------------------------------
/// A função da temperatura externa, é uma regressão baseada em dados de temperatura fornecidos pelo labsolar.
/// Dada a hora do dia, fornece a temperatura externa.
/// A regressão é uma senoide
/// redefinivel
double CFuncoesClima::TemperaturaExterna( double hora ) {
  ///  min=22 C max=32 C
  double temperatura = 5.0 * sin( 0.261799 * hora - 2.8274 ) + 27.0;
  return ( temperatura );
}

/// ---------------------------------------------------------------------------
/// Calcular temperaturaInterna, duas possibilidades, ti=cte, ou ti=função (te,amortecimento,retardo)
/// redefinivel
void CFuncoesClima::TemperaturaInterna( double hora ) {
   /// Caso 1: temperatura interna constante
   /// tint = tintcte;
   /// Caso 2: temperatura interna funÇão temperatura externa, amortecimento e retardo.
   tint = TemperaturaExterna( hora - retardo ) * amortecimento;
}

/// ---------------------------------------------------------------------------
/// Implementação função UmidadeExterna
/// a umidade externa pode ser considerada constante, ou variável em função do tempo.
/// redefinivel
void CFuncoesClima::UmidadeExterna() {
   hext = 2.144 - text * 0.052;	/// 0.84+(27.0-text)*0.26/5.0;
   /// hmax=100 hmin=58 (27gc--0.84)conteúdo ar externo cte
   /// fixou-se o conteúdo e cálculou as umidades extremas
   /// if(hext>1.0)
   ///   hext=1.0;
}

/// ---------------------------------------------------------------------------
/// Implementação função UmidadeInterna, h = f(temperatura interna)
/// a umidade interna pode ser considerada constante, ou variável, em função do tempo, ou função da umidade externa.
// redefinivel
void CFuncoesClima::UmidadeInterna() {
   hint = 2.144 - tint * 0.052;	/// 0.84+(27.0-tint)*0.26/5.0;
///       if(hint>1.0)
///               hint=1.0;
}

/// ---------------------------------------------------------------------------
/// Cálculo da radiação de onda curta proveniente do sol.
/// Observação: o tempo que esta nestas formulas é tempo decimal, não é hora inteira.
/// A radiação se assemelha a uma função gaussiana (Normal).
/// Para cada dia típico temos uma curva de radiação diferente, as correlações usadas foram geradas
/// a partir de dados fornecidos pelo LABSOLAR da UFSC.
/// Maiores detalhes veja dissertação de mestrado.
// redefinivel
void CFuncoesClima::RadiacaoOndaCurta( double hora ) { 
   if(  hora < 4.0  or  hora > 18.86 )
    radoc = 0.0;
   else if( hora < 12.0 )
    radoc = 1648.2 - 870.7 * hora + 138.59 * hora * hora - 5.823 * hora * hora * hora ;
   else if( hora >= 12.0 )
    radoc = -17723.44 + 3842.2 * hora - 252.08 * hora * hora  + 5.206 * hora * hora * hora;
}

/// ---------------------------------------------------------------------------
/// Implementação função radiação onda longa, considerada constante ou função da tsuperficial.
/// No caso de considerar a temperatura superficial deve-se calcular
/// o balanço de radiação entre a radiação proveniente do céu e a emitida.
// redefinivel
void CFuncoesClima::RadiacaoOndaLonga( double /*hora*/ ) {
   radol = -100.0;
   /// radol = - sigma * pow ( tsuperficial , 4 ) ;   /// considerar balanço de radiação do ceu e da telha
}

/// Saída de dados do objeto para os (tela)
std::ostream& operator<<(std::ostream& os, CFuncoesClima& obj) {
  os 	<< "\n==> Objeto CFuncoesClima:"
		<< "\ntext = "		<< obj.text
		<< "\ntint = "		<< obj.tint
		<< "\nhext = "		<< obj.hext
		<< "\nhint = "		<< obj.hint
		<< "\nrove = "		<< obj.rove
		<< "\nrovi = "		<< obj.rovi
		<< "\nradoc = "		<< obj.radoc
		<< "\nradol = "		<< obj.radol
		<< "\nretardo = "	<< obj.retardo
		<< "\namortecimento = "			<< obj.amortecimento
		<< "\nhoraInicioChuva = "		<< obj.horaInicioChuva
		<< "\nhoraFimChuva = "			<< obj.horaFimChuva
		<< "\nprecipitacao = "			<< obj.precipitacao
		<< "\nrespTemperaturaInterna = "<< obj.respTemperaturaInterna
		<< "\nrespHhext = "				<< obj.respHumidadeExterna
		<< "\nrespHumidadeInterna = "	<< obj.respHumidadeInterna;
}
