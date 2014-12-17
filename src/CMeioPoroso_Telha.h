#ifndef CMeioPoroso_Telha_h
#define CMeioPoroso_Telha_h

/// -------------------  Bibliotecas --------------------------------
#include <iostream>					/// por causa rotinas entrada saída
#include <memory>					/// shared_ptr
#include "CFuncaoDifusividade.h"
#include "CFuncaoCondutividade.h"
#include "CFuncaoAdsorcao.h"

/// ------------------- classe CMeioPoroso_Telha -------------------------------------
/// @brief Representa meio poroso agregando funções difusidade, condutividade e adsorção.
/// Representa ao mesmo tempo uma telha permeável e uma telha impermeável,
/// ou seja, vai calcular as informações para os dois casos, permitindo a comparação dos valores.
/// @todo: verificar vantagens de separar em duas classes, uma para impermeável e outra para permeável.
// redefinivel
class CMeioPoroso_Telha
{
const double wl_inicial = 0.0134;		///< conteúdo de massa inicial

/// Objetos agregados
public:
 	CFuncaoDifusividade 		funcaoDifusividade; ///< Função usada cálculo difusividade.
 	CFuncaoCondutividade		funcaoCondutividade;///< Função usada cálculo condutividade.
 	std::shared_ptr<CFuncaoAdsorcao>	funcaoAdsorcao;	///< Função usada cálculo adsorção.

protected:
   // Propriedades físicas da telha
   /// @todo: trocar por enum ETipoMaterial < uint8 > { argamassa_celso, argamassa_pablo, ceramica_bueno };
   char tipo_material{'c'}; 	///< tipo_material se refere ao tipo de material se argamassa, ou cerâmica, ou..

   double rot{1730}; 			///< densidade (telha)
   double ct{1000.0}; 			///< calor específico (telha)
   double porosidade{0.31}; 	///< porosidade (telha)
   double alfa{0.63}; 			///< coeficiente absorção a radiação (telha)
   double emis{1.0};  			///< coeficiente emissividade (telha)

   // Propriedades geométricas da telha
   double larg{0.03};			///< largura do objeto (telha)

   // Propriedades físicas da telha impermeável
   double wli;					///< conteúdo massa mássico wl  (fixo para telha impermeável)
   double ki;					///< condutividade (fixo para telha impermeável)

public:
   /// Construtor default/sobrecarregado, recebe o tipo de material.
   CMeioPoroso_Telha( char _tipo_material = 'c' ) :tipo_material(_tipo_material) {
     DadosDefault(  );
   }
   /// Destrutor
//   ~CMeioPoroso_Telha() 			{  if( funcaoAdsorcao ) delete funcaoAdsorcao;  }
   ~CMeioPoroso_Telha() 			{  if( funcaoAdsorcao ) funcaoAdsorcao.reset();  }
   /// Dados default
   void DadosDefault( );
   /// Entrada de dados
   void EntrarDadosObjeto();

  /// Saída de dados do objeto para os (tela)
  friend std::ostream& operator<<(std::ostream& os, CMeioPoroso_Telha& obj);
  friend class CFuncaoConteudoMassicoWl;	/// Poderá acessar rot
};
#endif
