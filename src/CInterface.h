#ifndef CInterface_h
#define CInterface_h

/// --------------- Valores padrão alterar e recompilar -----------------------
/// O número de nodos representa o número de pontos em que a telha é dividida
/// para o desenvolvimento do método numérico adotado.
/// O número de nodos deve ser um múltiplo de 3; multiplicar por 3 e somar 1
/// exemplos: 3*1+1=4 3*3+1=10 3*6+1=19 3*33+1=100
/// para que só apareça os resultados de 4 pontos o passo dos laços for foi definido por nodos/3.
/// desta forma a saída padrão apresenta quatro pontos, que são:
/// ponto 1 superfície externa, ponto 4 e 7 internos e ponto 10 superfície interna.
constexpr int nodos {10} ;		// #define nodos 10

/// -------------------  Bibliotecas --------------------------------
#include <iostream>			/// por causa rotinas entrada saída

class CInterface
{
public:  
  /// ---------------------------------------------------------------------------
  /// Implementação função Carimbo
  /// carimbo apresentado início programa, e para algumas saídas de tela.
  static void Carimbo() {
	 std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	 std::cout << "\n\t.___________________________________________________________.";
	 std::cout << "\n\t|                                                           |";
	 std::cout << "\n\t| SIMULAÇÃO DA TRANSFÊRENCIA DE CALOR E UMIDADE EM TELHAS   |";
	 std::cout << "\n\t|     Mestrado Engenharia Civil - NCC - LMPT - SITERPA      |";
	 std::cout << "\n\t|                    André Duarte Bueno                     |";
	 std::cout << "\n\t.___________________________________________________________.";
  }
};
#endif
