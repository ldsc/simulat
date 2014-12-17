
/// -------------------  Bibliotecas --------------------------------
//#include <cassert>
//#include <fstream>			/// por causa ifstream e ofstream ponteiros arquivos
#include <iostream>			/// por causa rotinas entrada saída
//#include <iomanip>			/// manipuladores, como setw()
//#include <cmath>			/// por causa funções matemáticas

#include "CInterface.h"
#include "CTransferenciaCalorMassa.h"
using namespace std;

/// Entrada de dados
void CTransferenciaCalorMassa::EntrarDadosObjeto() {
	CInterface::Carimbo();
	cout << *this;
   cout << "\nUsar coeficientes Transferência Calor por convecção (hce, hci) e "
		<<	"Transferência de Massa  (hme, hmi) default (d) ou novos (n): ";
   char resp;
   cin.get( resp );
   cin.get();
   if( resp == 'n' or resp == 'N' ) {
         cout << "\nEntre com os valores que serão solicitados.";
         cout << "\ncoeficiente de convecção externa (hce = " << hce << "): ";
         cin >> hce;
         cout << "\ncoeficiente de convecção interna (hci = " << hci << "): ";
         cin >> hci;
         cout << "\ncoeficiente de troca de vapor externo (hme = "<< hme << "): ";
         cin >> hme;
         cout << "\ncoeficiente de troca de vapor interno (hmi = "<< hmi << "): ";
         cin >> hmi;
         cin.get();  /// pega o retorno de carro -> enter!
      }
}

/// Saída de dados do objeto para os (tela)
std::ostream& operator<<(std::ostream& os, CTransferenciaCalorMassa&  obj) {
  os 	<< "\n==> Objeto CTransferenciaCalorMassa:\n"
        << "\nhce = " << obj.hce
        << "\nhci = " << obj.hci
        << "\nhme = " << obj.hme
        << "\nhmi = " << obj.hmi;
}
