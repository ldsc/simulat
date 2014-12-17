/// -------------------  Bibliotecas --------------------------------
// #include <cassert>
// #include <fstream>			/// por causa ifstream e ofstream ponteiros arquivos
#include <iostream>			/// por causa rotinas entrada saída
// #include <iomanip>			/// manipuladores, como setw()
// #include <cmath>			/// por causa funções matemáticas

#include "CFuncaoConteudoMassicoWl.h"
using namespace std;


/// Saída de dados do objeto para os (tela)
std::ostream& operator<<(std::ostream& os, CFuncaoConteudoMassicoWl&  obj) {
  os 	<< "\n==> Objeto CFuncaoConteudoMassicoWl :"
		<< "\n==> Objeto CFuncaoConteudoMassicoWl -> Agregados:"
		<< *obj.fluido
		<< *obj.telha;
}
