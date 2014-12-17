
/// -------------------  Bibliotecas --------------------------------
//#include <cassert>
//#include <fstream>			/// por causa ifstream e ofstream ponteiros arquivos
#include <iostream>			/// por causa rotinas entrada saída
//#include <iomanip>			/// manipuladores, como setw()
#include <cmath>			/// por causa funções matemáticas

#include "CInterface.h"
#include "CFuncaoDifusividade.h"
using namespace std;

void CFuncaoDifusividade::EntrarDadosFuncao() {
	CInterface::Carimbo();
	cout << *this;
	std::cout << "\nEntre com multiplicador da difusidade (cdif = "<< cdif << "): ";
	std::cin >> cdif;
	std::cin.get();
};

/// ---------------------------------------------------------------------------
/// Cálculo da difusividade a partir do conteúdo massa volumétrico ol (correlações obtidas a partir de ensaios)
// redefinivel
double CFuncaoDifusividade::Difusividade( double ol ) {
   double difusividade;
   if( ol < 0.0692 )
      difusividade = 9.25e-8 - 2.81e-6 * ol + 2.39e-5 * ol * ol;	/// 2 grau
   else if( ol >= 0.0692 and ol <= 0.173 )
      difusividade = 7.95e-9 + 6.21e-8 * ol;		/// 1 grau - reta
   else if( ol > 0.173 and ol <= 0.1903 )			/// item incluido em 25/03/92
      difusividade = -1.135e-7 + 7.734e-7 * ol;
   else if( ol > 0.1903 and ol <= 0.26815 )
      difusividade = 3.816766e-8 - 0.000054 * pow( ol, 4 ) + 1.048743 * pow( ol, 10 );	/// 10 grau
   else if( ol > 0.26815 )
      difusividade = 2e-6;							/// limite para ol>0.26815

   if( difusividade <= 1.0e-8 ) 					/// assegura valor mínimo de difusividade
      difusividade = 1.0e-8;						/// porque a regressão não é perfeita
   if( difusividade > 2.0e-6 )	    				/// assegura valor máximo difusividade
      difusividade = 2.0e-6;						/// alteração- melhor fixar ol?

   difusividade = difusividade * cdif;				/// multiplica por cdif
   return ( difusividade );
}

/// Saída de dados do objeto para os (tela)
std::ostream& operator<<(std::ostream& os, CFuncaoDifusividade& obj) {
  os 	<< "\n==> Objeto CFuncaoDifusividade:"
		<< "\ncdif = "<< obj.cdif;
}
