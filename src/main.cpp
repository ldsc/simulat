
/// -------------------  Bibliotecas --------------------------------
//#include <cassert>
//#include <fstream>			/// por causa ifstream e ofstream ponteiros arquivos
#include <iostream>			/// por causa rotinas entrada saída
//#include <iomanip>			/// manipuladores, como setw()
//#include <cmath>			/// por causa funções matemáticas
#include "CGnuplot.h"

#include "CInterface_SimuladorTelha.h"
using namespace std;

/// ---------------------------------------------------------------------------
/// FUNCAO PRINCIPAL MAIN()  ///  *-*-*-*-*
/// ---------------------------------------------------------------------------
int main() {
	CGnuplot::Terminal("wxt");	// define tipo de terminal do gnuplot
	char respreiniciarprograma = 'r';
	do {
        CInterface_SimuladorTelha simulat;		/// Cria objeto de simulação
        simulat.ExecutarSimulador();			/// Chama função de simulação
        cout << "\n\n\n\t\tDeseja Reiniciar o Programa..............(r)";
        cout << "\n\t\t       Abandonar Programa............... (a): ";
        cin.get( respreiniciarprograma );
        cin.get();
      }
	while( respreiniciarprograma == 'r' or respreiniciarprograma == 'R' );	
   return ( 0 );
}
