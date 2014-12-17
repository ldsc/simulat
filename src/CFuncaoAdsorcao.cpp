/// -------------------  Bibliotecas --------------------------------
//#include <cassert>
//#include <fstream>			/// por causa ifstream e ofstream ponteiros arquivos
#include <iostream>			/// por causa rotinas entrada saída
//#include <iomanip>			/// manipuladores, como setw()
#include <cmath>			/// por causa funções matemáticas

#include "CInterface.h"
#include "CFuncaoAdsorcao.h"
using namespace std;

/// Entrada de dados (associados aos ensaios)
void CFuncaoAdsorcao::EntrarDadosFuncao() {
	CInterface::Carimbo();
	cout << *this;
   cout << "\nUsar temperatura ensaio adsorcao default (d) ou novo (n): ";
   char resp;
   cin.get( resp );
   cin.get();
   if( resp == 'n' or resp == 'N' ) {
     cout << "\ntemperatura_ensaio_adsorcao = ";
     cin >> temperatura_ensaio_adsorcao;
     cin.get();
     }
}

/// ---------------------------------------------------------------------------
/// Implementação função cálculo da umidade em função conteúdo massa mássico wl  (resultado do ensaio de adsorção).
/// Uso cálculo umidade nos pontos h1 e hn para cálculo rov1 e rovn
/// As equações abaixo relacionam o conteúdo massa mássico wl com a umidade do ar (resultado do ensaio de adsorção).
// redefinivel
/// @param wl conteúdo massa mássico 
/// @param temperatura em que foi realizado ensaio adsorção
double CFuncaoAdsorcao::Umidade( double wl, double temperatura ) {
	// Resultados ensaio calcula nova valor de h
	ResultadosEnsaio( wl );
/*
Program received signal SIGSEGV, Segmentation fault.
0x000000000040beb7 in CFuncaoAdsorcao::Umidade (this=0x6290d0, wl=0.1791907514450867, 
    temperatura=24.274999999999999)
    at 
/home/bueno/Documentos/03-Pesquisa/4-Desenvolvimento/2-Programas-e-Bibliotecas-Releases/01a-SimulacaoTelhaMestrado/Simulat-SimuladorTelhaMestrado-v4b-GNULinux-2014-Documentado-
RedivisaoClasses-ArquivosSeparados-ComGnuplot/src/CFuncaoAdsorcao.cpp:34
34		ResultadosEnsaio( wl );
*/
	// Corrige considerando temperatura
	CorrecaoTemperatura( temperatura );
	return ( h );
}

/// Chamada por Umidade, inclui dados de ensaios específicos de adsorção.
void CFuncaoAdsorcao::ResultadosEnsaio( double& wl )
{
	if( wl <= 0.0163 )
		h = 3894.0 * wl;
	else if( wl > 0.0163 and wl <= 0.0182 )
		h = -72.8284 + 8362 * wl;
	else if( wl > 0.0182 and wl <= 0.07846 )
		h = 74.423 + 271 * wl;
	else if( wl > 0.07846 )	/// 0.176
		h = 92.2475 + 44.048 * wl;
}

/// Corrige umidade considerando temperatura da simulação e temperatura em que ensaio foi realizado
/// O ensaio de adsorção é feito, normalmente, a 25 graus Célsios, abaixo
/// correção da curva de adsorção para diferentes valores de temperatura
/// h2 = e^(ln h1*(sigma(t2)*temperatura_ensaio_adsorcao)/(sigma(temperatura_ensaio_adsorcao)*t2))
/// lembre-se em c++ log e' logaritimo natural
void CFuncaoAdsorcao::CorrecaoTemperatura( double& temperatura )
{
	/// Cálculo correção curva de adsorção função temperatura	
	if( h > 0.0 )
      h = exp( log( h ) * ( 0.0763 - 0.00016835 * temperatura ) * temperatura_ensaio_adsorcao
               /  ( (0.0763 - 0.00016835 * temperatura_ensaio_adsorcao ) * temperatura ) );

	/// Abaixo adicionados limites máximo e mínimo para h
	if( h >= 1.0 )
      h = 1.0;
	if( h <= 0.0 )
      h = 0.0;
}

/// Saída de dados do objeto para os (tela)
std::ostream& operator<<( std::ostream& os, CFuncaoAdsorcao& obj ) {
  os 	<< "\n==> Objeto CFuncaoAdsorcao:"
		<< "\nh (calculado)= "<< obj.h
		<< "\ntemperatura_ensaio_adsorcao = "<< obj.temperatura_ensaio_adsorcao;
}
