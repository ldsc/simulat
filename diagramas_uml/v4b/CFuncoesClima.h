
/// -------------------  classe CTermodinamica ------------------------------------
/// Representa conceitos e funções básicas da termodinâmica.
class CTermodinamica
{
public: 
  /// Cálculo da concentração de vapor
  // pode ser acessada diretamente usando: CTermodinamica::FuncaoConcentracaoVapor()
  static inline double FuncaoConcentracaoVapor( double umidade, double temperatura );
private:
  /// Cálculo da pressão de vapor
  inline double FuncaoPressaoVapor( double temperatura );
};

/// -------------------  classe CFuncoesClima ------------------------------------
/// Classe CFuncoesClima: calcula funções como tempo, radoc, radol, e
/// umidadeExterna, umidadeInterna, rove, rovi...
/// *-*-*-*-*    /// redefinivel
class CFuncoesClima
{
protected:
   // Propriedades climáticas
   double text{25.0}; 						///< temperatura externa
   double tint{25.0}; 						///< temperatura interna
   double rove{0.017}; 						///< concentração vapor externo?
   double rovi{0.017}; 						///< concentração vapor interno?
   double radoc{0.0}; 						///< radiação onda curta
   double radol{0.0}; 						///< radiação onda longa
   double umidadeExterna{0.95}; 	    	///< umidade externa
   double umidadeInterna{0.75}; 		    ///< umidade interna

   // Propriedades climáticas - cálculo da temperatura interna
   // Para cálculo da temperatura interna, que é função da temperatura externa, usa um retardo e um amortecimento
   double retardo{0.0};						///< retardo térmico em função espessura parede
   double amortecimento{1.0}; 		    	///< amortecimento térmico em função espessura parede

   // Propriedades climáticas - cálculo da chuva
   double inicioChuva{0.0};  				///< hora início da chuva
   double fimChuva{0.0};  					///< hora fim da chuva
   double precipitacao{0.0};  				///< precipitacao em mm
   double olChuva{0.0}; 					///< conteúdo mássico de umidade relativo a chuva

   // Propriedades/atributos associados a interface em modo texto
   // O usuário pode definir a temperatura interna e umidades externa e interna
   // como constantes ou como função da temperatura externa
   char respTemperaturaInterna{'c'};		///< temperatura interna constante ou calculada
   char respHumidadeExterna{'c'};  			///< umidade externa constante ou calculada
   char respHumidadeInterna{'c'};			///< umidade interna constante ou calculada

//--------------------------------------------------------------------------------------Métodos
public:
  /// Construtor
  CFuncoesClima()	{
	 ExecutarFuncoesClima()
  }
  /// Destrutor
  ~CFuncoesClima();
  /// Dados default
  void DadosDefault();
  /// Entrada de dados
  void EntrarDadosObjeto();
  /// Executa funções clima
  void ExecutarFuncoesClima(double hora);
  /// Executa funções clima
  double operator()( double hora) { ExecutarFuncoesClima(); return hora; }

private:
   /// Cálculo da temperatura externa (função do tempo - hora)
   double FuncaoTemperaturaExterna( double hora );
   /// Cálculo da temperatura interna
   inline void FuncaoTemperaturaInterna( double hora );
   /// Cálculo da umidade externa (função da temperatura externa)
   inline void FuncaoUmidadeExterna();
   /// Cálculo da umidade interna (função da temperatura interna)
   inline void FuncaoUmidadeInterna();
   void FuncaoRadiacaoOndaCurta( double hora );
   /// Cálculo da radiação de onda longa
   inline void FuncaoRadiacaoOndaLonga( double hora );
   /// Cálculo da emissividade
   /// void CalculoEmissividade();
   /// Cálculo da radiação de onda curta
   /// Saída de dados do objeto para os (tela)
   friend std:ostream& operator<<(std::ostream& os, CFuncoesClima obj);
};
