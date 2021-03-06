#ifndef CFluido_h
#define CFluido_h

/// -------------------  Bibliotecas --------------------------------
#include <iostream>			/// por causa rotinas entrada saída

/// ------------------- classe CFluido -------------------------------------
/// @brief Representa um fluido com atributos: rol, cl, lv.
class CFluido
{
protected:
   // Propriedades do líquido/gas
   double rol{1000.0}; 							///< densidade líquido (água)
   double cl{4187.0}; 							///< calor especifico liquido (água)
   double lv{2256685.0};						///< calor latente vaporização (água)

/// funções
public:
   /// Construtor
   CFluido() = default;
   /// Destrutor
   ~CFluido() = default;
   /// Dados default
   void DadosDefault() 					{ rol = 1000.0;   cl = 4187.0;  lv = 2256685.0; }
   /// Entrada de dados
   void EntrarDadosObjeto();

  /// Saída de dados do objeto para os (tela)
  friend std::ostream& operator<<(std::ostream& os, CFluido& obj);

  friend class CFuncaoConteudoMassicoWl;				/// CFuncao_wl poderá acessar rol
  friend class CSimulador_Telha;
  friend class CSimulador_Telha_GanhosEnergia;
};
#endif

