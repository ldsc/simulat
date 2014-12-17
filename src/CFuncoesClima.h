#ifndef CFuncoesClima_h
#define CFuncoesClima_h

/// -------------------  Bibliotecas --------------------------------
#include <iostream>			/// por causa rotinas entrada saída

/// -------------------  classe CFuncoesClima ------------------------------------
/// @brief  Armazena e calcula funções como temperatura externa/interna,
/// radiação onda curta/longa, umidade externa/interna, e chuva.
/// Estes atributos podem ser constantes ou função da hora do dia.
// redefinivel
class CFuncoesClima
{
protected:
   // Propriedades climáticas
   double text{25.0}; 						///< temperatura externa
   double tint{25.0}; 						///< temperatura interna
   double hext{0.95}; 						///< umidade externa
   double hint{0.75}; 						///< umidade interna
   double rove{0.017}; 						///< concentração vapor externo (calculado)
   double rovi{0.017}; 						///< concentração vapor interno (calculado)
   double radoc{0.0}; 						///< radiação onda curta
   double radol{0.0}; 						///< radiação onda longa

   // Para cálculo da temperatura interna, que pode ser função da temperatura externa, usa um retardo e um amortecimento
   double retardo{0.0};						///< retardo térmico em função espessura parede
   double amortecimento{1.0}; 		    	///< amortecimento térmico em função espessura parede

   // Propriedades climáticas associadas ao cálculo da chuva
   double horaInicioChuva{0.0};  			///< hora início da chuva
   double horaFimChuva{0.0};  				///< hora fim da chuva
   double precipitacao{0.0};  				///< precipitacao em mm

   // Propriedades/atributos associados a interface em modo texto
   // O usuário pode definir a temperatura interna e umidades externa e interna
   // como constantes ou como função da temperatura externa
   char respTemperaturaInterna{'c'};		///< temperatura interna constante ou calculada
   char respHumidadeExterna{'c'};  			///< umidade externa constante ou calculada
   char respHumidadeInterna{'c'};			///< umidade interna constante ou calculada
   /// @todo criar função para chuva e atributo respChuvainformando se é constante ou variável

//--------------------------------------------------------------------------------------Métodos
public:
  /// Construtor
  CFuncoesClima()					{	DadosDefault();  }
  /// Destrutor
  ~CFuncoesClima() = default;
  /// Dados default
  void DadosDefault();
  /// Entrada de dados
  void EntrarDadosObjeto();
  /// Atualiza os atributos de acordo com a hora do dia; 
  /// Se você deseja que os atributos sejam constantes, defina os mesmos chamando EntrarDadosObjeto() 
  /// e não chame ExecutarFuncoesClima().
  void ExecutarFuncoesClima(double hora);
  /// Executa funções clima
  double operator()( double hora) 	{ ExecutarFuncoesClima(hora); return hora; }

private:
   /// Cálculo da temperatura externa (função do tempo - hora)
   double TemperaturaExterna( double hora );
   /// Cálculo da temperatura interna
   inline void TemperaturaInterna( double hora );
   /// Cálculo da umidade externa (função da temperatura externa)
   inline void UmidadeExterna();
   /// Cálculo da umidade interna (função da temperatura interna)
   inline void UmidadeInterna();
   void RadiacaoOndaCurta( double hora );
   /// Cálculo da radiação de onda longa
   inline void RadiacaoOndaLonga( double hora );
   /// Cálculo da emissividade
   /// void CalculoEmissividade();
   /// Cálculo da radiação de onda curta
   /// Saída de dados do objeto para os (tela)
   friend std::ostream& operator<<(std::ostream& os, CFuncoesClima& obj);

   friend class CSimulador_Telha;
   friend class CSimulador_Telha_GanhosEnergia;
};

#endif
