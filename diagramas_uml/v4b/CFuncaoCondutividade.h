/// ------------------- Classe CFuncaoCondutividade -----------------------------------
/// Calcula a condutividade a partir de correlações fornecidas pelo usuário.
/// *-*-*-*-*    /// redefinivel
/// @todo: Para valer para outros ensaios, usar polinômios de grau n;
/// ler dados funcaoCondutividade.dat do disco, criando m polinômios!
class CFuncaoCondutividade 
{
protected:
   // Propriedades associadas ao cálculo da condutividade
   double ak{13.486};  					///< Coeficiente a para cálculo condutividade como função linear
   double bk{0.743}; 					///< Coeficiente b para cálculo condutividade como função linear

public:
   CFuncaoCondutividade();				///< Construtor
   ~CFuncaoCondutividade();				///< Destrutor

protected:
   /// Entrada de dados (associados aos ensaios)
   void EntrarDadosFuncao();
  /// Dados default
  void DadosDefault() { ak = 13.486; bk = 0.743; };
  /// Cálculo da condutividade a partir da relação entre a condutividade térmica k e o conteúdo de
  /// massa mássico da telha wl.
  inline double FuncaoCondutividade( double wl )	{  	/// double k = bk + ak * wl;
	return ( bk + ak * wl );							/// return(k);
  }
  /// Cálculo da condutividade a partir da relação entre a condutividade térmica k e o conteúdo de
  /// massa mássico da telha wl.
  double operator()( double wl ) { return FuncaoCondutividade( wl ); };

  /// Saída de dados do objeto para os (tela)
  friend std:ostream& operator<<(std::ostream& os, CFuncaoCondutividade obj);
};
