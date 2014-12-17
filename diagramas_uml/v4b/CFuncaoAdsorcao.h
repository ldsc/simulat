
/// ------------------- Classe CFuncaoAdsorcao -----------------------------------
/// Calcula a umidade a partir das curvas de adsorção do material (correlações fornecidas pelo usuário).
/// *-*-*-*-*    /// redefinivel
class CFuncaoAdsorcao
{
public:
   CFuncaoAdsorcao();				///< Construtor
   ~CFuncaoAdsorcao();				///< Destrutor
  /// Dados default
  void DadosDefault() {};
protected:
   /// Entrada de dados (associados aos ensaios)
   void EntrarDadosFuncao(){};
   /// Cálculo da umidade em função do conteúdo massa mássico wl (resultado do ensaio de adsorção).
   double FuncaoUmidade( double wl, double temperatura, char tipo_material );
   /// Cálculo da umidade em função do conteúdo massa mássico wl (resultado do ensaio de adsorção).
   double operator()( double wl, double temperatura, char tipo_material ) {
     return FuncaoUmidade( wl, temperatura, tipo_material )};
   
  /// Saída de dados do objeto para os (tela)
  friend std:ostream& operator<<(std::ostream& os, CFuncaoAdsorcao obj);
};
