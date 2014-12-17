
/// -------------------  Bibliotecas --------------------------------
//#include <cassert>
//#include <fstream>			/// por causa ifstream e ofstream ponteiros arquivos
#include <iostream>			/// por causa rotinas entrada saída
//#include <iomanip>			/// manipuladores, como setw()
//#include <cmath>			/// por causa funções matemáticas

#include "CSolver_TDMA.h"
using namespace std;


/// ---------------------------------------------------------------------------
/// Implementação função ResolverSistemaEquacoes_TDMA_piqi folpiqi
/// calcula coeficientes piqi do método implicito (Método de Thomas)
void CSolver_TDMA::ResolverSistemaEquacoes_TDMA_piqi() {
   double temp;
   p[1] = b[1] / a[1];		/// pode ser incluido dentro do for, porque c=0
   q[1] = d[1] / a[1];		/// e p[i-1] i=1 , p[0] e p[0] foi definido=0

   for( int i = 2; i <= nodos; i++ ) {
         temp = a[i] - c[i] * p[i - 1];
         p[i] = b[i] / ( temp );
         q[i] = ( c[i] * q[i - 1] + d[i] ) / ( temp );
      }
}

/// Saída de dados do objeto para os (tela)
std::ostream& operator<<(std::ostream& os, CSolver_TDMA& obj) {
  os 	<< "\n==> Objeto CSolver_TDMA:\n";
  for( int i=0; i<= nodos ; i++ )
	os 	<< "\ni=" << i 
		<< " a=" << obj.a[i]
		<< " b=" << obj.b[i]
		<< " c=" << obj.c[i]
		<< " d=" << obj.d[i]
		<< " p=" << obj.p[i]
		<< " q=" << obj.q[i];
}
