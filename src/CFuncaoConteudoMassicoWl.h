#ifndef CFuncaoConteudoMassicoWl_h
#define CFuncaoConteudoMassicoWl_h

/// -------------------  Bibliotecas --------------------------------
#include <iostream>			/// por causa rotinas entrada saída
#include "CFluido.h"
#include "CMeioPoroso_Telha.h"

/// ------------------- classe CFuncaoConteudoMassicoWl -------------------------------------
/// @brief Classe de associação, usada para cálculo do conteúdo de massa mássico wl, a partir ol, rol e rot.
/// Note que é uma classe de associação, que calcula uma informaçao com base nas informações de duas
/// classes associadas, a CFluido e a CMeioPoroso_Telha.
class CFuncaoConteudoMassicoWl
{
protected:
//    double& rol; 							///< densidade líquido (água)
//    double& rot; 							///< densidade (telha)
  CFluido* fluido;							///< fluido
  CMeioPoroso_Telha * telha;				///< telha

/// funções
public:
   /// Construtor
   //CFuncaoConteudoMassicoWl(CFluido fluido, CMeioPoroso_Telha telha): rol(fluido.rol), rot(telha.rot) ;
   CFuncaoConteudoMassicoWl(CFluido* _fluido = nullptr, CMeioPoroso_Telha* _telha = nullptr): fluido(_fluido), telha(_telha) {};
   /// Destrutor
   ~CFuncaoConteudoMassicoWl() = default;
  /// Dados default
  void DadosDefault() {};
  /// Entrada de dados (associados aos ensaios)
  void EntrarDadosFuncao() {};
   /// Calcula o conteúdo de massa mássico wl em função do conteúdo de massa volumétrico ol.
   /// @param ol conteúdo de massa volumétrico
   inline double Wl( double ol ) {			//return ( ol * rol / rot );
	return ( ol * fluido->rol / telha->rot );
	}
   /// Seta ponteiro para fluido
   void Fluido(CFluido* f) { fluido = f;}
   /// Seta ponteiro para telha
   void Telha(CMeioPoroso_Telha* t) 		{ telha = t;}
   /// Calcula o conteúdo de massa mássico wl em função do conteúdo de massa volumétrico ol.
   /// @param ol conteúdo de massa volumétrico
   inline double operator()( double ol ) 	{ return Wl(ol); }

  /// Saída de dados do objeto para os (tela)
  friend std::ostream& operator<<(std::ostream& os, CFuncaoConteudoMassicoWl& obj);
};
#endif
