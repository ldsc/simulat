#ifndef CSolver_TDMA_h
#define CSolver_TDMA_h

/// -------------------  Bibliotecas --------------------------------
#include <iostream>			/// por causa rotinas entrada saída

#include "CInterface.h"  // nodos!

/// ------------------------- Classe CSolver_TDMA ---------------------------------------
/// @brief representa um solver TDMA - Tri-Diagonal  Matriz Algorithm (unidimensional).
class CSolver_TDMA
{
protected:
   // Propriedades do Método Numérico - Discretização
   // Propriedades do Método Numérico - TDMA
   double a[nodos + 1];				///< Vetor coeficiente a do método numérico TDMA
   double b[nodos + 1];				///< Vetor coeficiente b do método numérico TDMA
   double c[nodos + 1];				///< Vetor coeficiente c do método numérico TDMA
   double d[nodos + 1];				///< Vetor coeficiente d do método numérico TDMA
   double p[nodos + 1];				///< Vetor coeficiente p do método numérico TDMA
   double q[nodos + 1];				///< Vetor coeficiente q do método numérico TDMA

//--------------------------------------------------------------------------------------Métodos
public:
   /// Construtor
   CSolver_TDMA() = default;
   /// Destrutor
   ~CSolver_TDMA() = default;
   /// Dados default
   void DadosDefault() {
   for( int  i = 0; i <= nodos; i++ )
	  a[i] = b[i] = c[i] = d[i] = p[i] = q[i] = 0.00;
	}
  /// Entrada de dados
  void EntrarDadosObjeto() {};

protected:
   /// Cálculo dos coeficientes do método de Thomas
   void ResolverSistemaEquacoes_TDMA_piqi();

  /// Saída de dados do objeto para os (tela)
  friend std::ostream& operator<<(std::ostream& os, CSolver_TDMA& obj);
};

#endif
