
/// ------------------------- Classe CSolver_TDMA ---------------------------------------
/// Representa um solver TDMA - Tri-Diagonal  Matriz Algorithm.
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
   CSolver_TDMA();
   /// Destrutor
   ~CSolver_TDMA();

protected:
   /// Cálculo dos coeficientes do método de Thomas
   void ResolverSistemaEquacoes_TDMA_piqi();
   
  /// Saída de dados do objeto para os (tela)
  friend std:ostream& operator<<(std::ostream& os, CSolver_TDMA obj);
};

