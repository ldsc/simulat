#ifndef CFuncaoDifusividade_h
#define CFuncaoDifusividade_h

/// -------------------  Bibliotecas -------------------------------------------------
#include <iostream>								/// por causa rotinas entrada saída

/// ------------------- Classe CFuncaoDifusividade -----------------------------------
///  @brief Representa a função de difusidade ao vapor de um meio poroso; no caso específico, a telha de cerâmica.
/// A partir dos resultados do ensaio de difusividade, foi desenvolvida regressão estatistica
/// que correlaciona a difusividade e o conteúdo de massa volumétrico ol.
// redefinivel
/// Para testar outros materiais, você deve incluir aqui a regressão para o material em estudo.
/// @todo: Para valer para outros ensaios, usar polinômios de grau n;
/// ler dados funcaoDifusividade.dat do disco, criando m polinômios!
class CFuncaoDifusividade
{
protected:
   double cdif{1.0}; 					    	///< multiplicador da difusividade

public:
   CFuncaoDifusividade() = default;				///< Construtor
   ~CFuncaoDifusividade()= default;				///< Destrutor
  /// Dados default
  void DadosDefault() { cdif = 1.0; };
   /// Entrada de dados (associados aos ensaios)
   void EntrarDadosFuncao() ;
   /// Cálculo da difusividade a partir do conteúdo massa volumétrico ol (correlações obtidas a partir de ensaios)
   double Difusividade( double ol );
   /// Cálculo da difusividade a partir do conteúdo massa volumétrico ol (correlações obtidas a partir de ensaios)
   double operator()( double ol ) 		{ return Difusividade(ol); };

  /// Saída de dados do objeto para os (tela)
  friend std::ostream& operator<<(std::ostream& os, CFuncaoDifusividade& obj);
};
#endif
