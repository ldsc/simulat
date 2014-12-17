/// -------------------  Bibliotecas --------------------------------
//#include <cassert>
//#include <fstream>			/// por causa ifstream e ofstream ponteiros arquivos
#include <iostream>			/// por causa rotinas entrada saída
//#include <iomanip>			/// manipuladores, como setw()
//#include <cmath>			/// por causa funções matemáticas

#include "CInterface.h"
#include "CFuncaoCondutividade.h"
using namespace std;

/// ---------------------------------------------------------------------------
/// Entrada dos coeficientes das funções dos ensaios, de forma que pode ser utilizada por outros materiais
void CFuncaoCondutividade::EntrarDadosFuncao() {
	CInterface::Carimbo();
	cout << *this;
//    cout << "\nUsar coeficientes cálculo condutividade k = bk + ak * wl, (ak = " << ak 
// 		<< "), (bk = " << bk <<") default (d) ou novos valores (n): ";
   cout << "\nUsar coeficientes cálculo condutividade k = bk + ak * wl, default (d) ou novos valores (n): ";
   char resp;
   cin.get( resp );
   cin.get();
   if( resp == 'n' or resp == 'N' ) {
     cout << "\nak = ";
     cin >> ak;
     cout << "\nbk = ";
     cin >> bk;
     cin.get();
     }
}

/// Saída de dados do objeto para os (tela)
std::ostream& operator<<(std::ostream& os, CFuncaoCondutividade& obj) {
  os 	<< "\n==> Objeto CFuncaoCondutividade:"
		<< "\nak = "<< obj.ak
		<< "\nbk = "<< obj.bk;
}
