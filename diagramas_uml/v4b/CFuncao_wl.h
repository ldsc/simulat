/// ------------------- classe CFuncao_wl -------------------------------------
/// Classe CFuncao_wl: usada para cálculo do conteúdo de massa mássico wl, a partir ol, rol e rot.
/// Note que é uma classe de associação, que calcula uma informaçao com base nas informações de duas
/// classes associadas, a CFluido e a CMeioPoroso_Telha.
class CFuncao_wl
{
protected:
//    double& rol; 							///< densidade líquido (água)
//    double& rot; 							///< densidade (telha)
  CFluido* fluido;							///< fluido
  CMeioPoroso_Telha * telha;				///< telha

/// funções
public:
   /// Construtor
   //CFuncao_wl(CFluido fluido, CMeioPoroso_Telha telha): rol(fluido.rol), rot(telha.rot) ;
   CFuncao_wl(CFluido* _fluido = nullptr, CMeioPoroso_Telha* _telha = nullptr): fluido(_fluido), telha(_telha) {};
   /// Destrutor
   ~CFuncao_wl() = default;
   
   /// Calcula o conteúdo de massa mássico wl em função do conteúdo de massa volumétrico ol.
   /// @param ol conteúdo de massa volumétrico
   inline double Funcao_wl( double ol ){
	//return ( ol * rol / rot );
	return ( ol * fluido->rol / telha->rot );
	}
   /// Seta ponteiro para fluido
   void Fluido(CFluido* f) { fluido = f;}
   /// Seta ponteiro para telha
   void Telha(CMeioPoroso_Telha* t) { telha = t;}
   /// Calcula o conteúdo de massa mássico wl em função do conteúdo de massa volumétrico ol.
   /// @param ol conteúdo de massa volumétrico
   inline double operator()( double ol ) { return Funcao_wl(ol); }
   
  /// Saída de dados do objeto para os (tela)
  friend std:ostream& operator<<(std::ostream& os, CFuncao_wl obj);
};
