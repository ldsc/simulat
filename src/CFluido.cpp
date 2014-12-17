/// -------------------  Bibliotecas --------------------------------
//#include <cassert>
//#include <fstream>		/// por causa ifstream e ofstream ponteiros arquivos
#include <iostream>			/// por causa rotinas entrada saída
//#include <iomanip>		/// manipuladores, como setw()
//#include <cmath>			/// por causa funções matemáticas

#include "CInterface.h"
#include "CFluido.h"
using namespace std;

void CFluido::EntrarDadosObjeto() {
	CInterface::Carimbo();
	cout << *this;
	cout << "\nUsar densidade líquido(rol), calor especifico liquido (cl), calor latente vaporização(lv), default (d) ou novos (n): ";
	char resp;
	cin.get( resp );
	cin.get();
	if( resp == 'n' or resp == 'N' ) {
		cout << "\nEntre com os valores que serão solicitados.";
		cout << "\ndensidade do líquido (rol = "<< rol << "): ";
		cin >> rol;
		cout << "\ncalor específico da água (cl = " << cl << "): ";
		cin >> cl;
		cout << "\ncoeficiente de calor latente (lv = "<< lv << "): ";
		cin >> lv;
		cin.get();  /// pega o retorno de carro -> enter!
		}
}

/// Saída de dados do objeto para os (tela)
std::ostream& operator<<(std::ostream& os, CFluido& obj) {
  os 	<< "\n==> Objeto CFluido:"
		<< "\nrol = " 				<< obj.rol
		<< "\ncl = " 				<< obj.cl
		<< "\nlv = " 				<< obj.lv;
}
