#ifndef CTransferenciaCalorMassa_h
#define CTransferenciaCalorMassa_h

/// -------------------  Bibliotecas --------------------------------
#include <iostream>			/// por causa rotinas entrada saída

/// ------------------- classe CTransferenciaCalorMassa -------------------------------------
/// @brief Inclui atributos associados a conceitos de transferência de calor e massa.
class CTransferenciaCalorMassa
{
protected:
   // Propriedades da transferência de calor e massa
   double hce{16.7}; 					///< coeficiente convecção externo
   double hci{9.1}; 					///< coeficiente convecção interno
   double hme{0.01386};					///< hme coeficiente troca massa externo
   double hmi{0.0076}; 					///< hmi coeficiente troca massa interno

   // Propriedades/constantes físicas
   double sigma{5.67e-8};				///< cte boltzman

/// funções
public:
   /// Construtor
   CTransferenciaCalorMassa()= default;
   /// Destrutor
   ~CTransferenciaCalorMassa()= default;

protected:
   /// Dados default
   void DadosDefault() 						{ hce = 16.7; hci = 9.1; hme = 0.01386; hmi = 0.0076; }
   /// Entrada de dados
   void EntrarDadosObjeto();

  /// Saída de dados do objeto para os (tela)
  friend std::ostream& operator<<(std::ostream& os, CTransferenciaCalorMassa& obj);
};

#endif
