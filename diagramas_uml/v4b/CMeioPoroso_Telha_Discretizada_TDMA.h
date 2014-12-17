
/// ------------------- Classe CMeioPoroso_Telha_Discretizada_TDMA -----------------------------------
/// Calcula a difusividade e a condutividade a partir de correlações fornecidas pelo usuário.
/// Deve-se incluir as correlações neste código cpp e recompilar o programa.   *-*-*-*-*
class CMeioPoroso_Telha_Discretizada_TDMA :
	public CMeioPoroso_Telha,
	public CTransferenciaCalorMassa,
	public CSolver_TDMA
{
  // Objetos associados
  CFuncoesClima&		funcoes_clima;
  CFluido&				fluido;
  // Objetos agregados
  //   FuncaoDifusividade	funcao_difusividade;
  //   FuncaoCondutividade	funcao_condutividade;
  //   CFuncaoAdsorcao 		funcao_adsorcao;
  CFuncao_wl 			funcao_wl;

protected:
   // Propriedades do volume de controle (do nó da telha)
   double dif[nodos + 1]; 	    	///< vetor difusividade (de cada nó)
   double k[nodos + 1];  		    ///< vetor condutividade (de cada nó)
   double wl[nodos + 1]; 			///< vetor conteúdo massa mássico (de cada nó)
   double h[nodos + 1];    			///< vetor umidade relativa (de cada nó)
   double rov[nodos + 1];	    	///< vetor concentração vapor nos nodos (de cada nó)

   double esp;  					///< espessura filme líquido sobre a telha (instante atual)[mm?]
   double ol[nodos + 1];  			///< conteúdo massa  (instante atual)
   double tp[nodos + 1];	 		///< temperatura telha permeável (no instante atual)
   // Propriedades telha impermeável
   double ti[nodos + 1]; 			///< temperatura da telha impermeável (instante atual)

   double espa;  					///< espessura filme líquido sobre a telha (no instante anterior)
   double ola[nodos + 1];  			///< conteúdo de massa  (no instante anterior)
   double tpa[nodos + 1];	 		///< temperatura telha permeabel (no instante anterior)
   // Propriedades telha impermeável
   double tia[nodos + 1]; 			///< temperatura da telha impermeável (instante anterior)

   double espaa;  					///< espessura filme líquido sobre a telha (no instante anterior ao anterior)
   double olaa[nodos + 1];  		///< conteúdo massa  (no instante anterior ao anterior)
   double tpaa[nodos + 1];	 		///< temperatura telha permeabel (no instante anterior ao anterior)
   // Propriedades telha impermeável
   double tiaa[nodos + 1]; 			///< temperatura da telha impermeável (instante anterior ao anterior)

   double dx {1.0};					///< intervalo de espaço, função da largura da telha e do número de nós.

   // Propriedades do Método Numérico - Controle avanço/recuo do intervalo de tempo - dt
   // o programa Simulat tem mecanismo que varia dt entre o intervalo dtmin <= dt <= dtmax.
   double dt{60.0}; 							///< intervalo de tempo da simulação
   double dta{60.0}; 							///< intervalo de tempo da simulação no instante anterior
   double dtmax{60.0};							///< intervalo de tempo máximo da simulação
   double dtmin{1.0};							///< intervalo de tempo mínimo da simulação
   double tempo{0.0};							///< tempo/hora atual da simulação (varia entre 0->24h)
   double m{0.0}; 								///< ???
   int n { nodos };								///< Número de nós (volumes de controles)

   int recorrencia{2};							///< número de recorrências cálculo acoplamento conteúdos e temperaturas.

   // Propriedades da simulação
   double tempoInicioSimulacao{0.0};            ///< hora inicial da simulação
   double tempoDecorrido{0.0};                  ///< tempo decorrido da simulação dias
   double tempoFimSimulacao{96.0};        		///< hora de encerramento da simulação (ex: 24 1 dia, 48 2 dias, 72 3 

   /// double errorecorrenciaol,errorecorrenciatp,errorecorrenciaola,errorecorrenciatpa;
   // Resultados, valores médios
   double wlm{0.0};                                  ///< conteúdo mássico médio ?
   double hm{0.0};                                   ///< coeficiente transferência massa médio ?
   double km{0.0};                                   ///< condutividade média ?
   double olm{0.0};                                  ///< conteúdo massa médio ?
   double tpm{0.0};                                  ///< temperatura média telha permeável ?
   double tim{0.0};                                  ///< temperatura média telha impermeável ?

   /// As linhas abaixo se referem as trocas de energia
   /// o arquivo variavel.doc descreve o significado de cada uma delas
   double gev{0.0};                                  ///< 
   double giv{0.0};                                  ///< 
   double gesp{0.0};                                 ///< 
   double gec{0.0};                                  ///< ganho externo convecção
   double gic{0.0};                                  ///< ganho interno convecção
   double gecl{0.0};                                 ///< ganho externo calor latente
   double gicl{0.0};                                 ///< ganho interno calor latente
   double geroc{0.0};                                ///< ganho externo radiação onda curta
   double gerol{0.0};                                ///< ganho externo radiação onda longa
   double gir{0.0};                                  ///< ganho interno radicao
   double bm{0.0};                                   ///< balanco massa
   double be{0.0};                                   ///< balanco energia
   double geci{0.0};                                 ///< ganho externo convecção
   double gici{0.0};                                 ///< ganho interno convecção
   double geroci{0.0};                               ///< ganho externo radiação onda curta
   double geroli{0.0};                               ///< ganho externo radiação onda longa
   double giri{0.0};                                 ///< ganho interno radicao

public:
  /// Construtor
  CMeioPoroso_Telha_Discretizada_TDMA(CFuncoesClima _fc, CFluido _f)
  :funcoes_clima(_fc), fluido( _f ) ,funcao_wl( _fwl )  {
	DadosDefault();
  }
  /// Destrutor
  ~CMeioPoroso_Telha_Discretizada_TDMA() = default;

   /// Dados default
   void DadosDefault();
   /// Entrada de dados
   void EntrarDadosObjeto();
   /// Próximo passo de tempo da simulação
   void Next(double tempo, double dt) = 0;
   
   /// Cálculo dos valores médios de condutividade e difusividade
   void CalcularValoresMedios_wl_h_rov_dif_k();             //****
   /// Cálculo de tp
   inline void Calcular_ti();
   /// Cálculo de ol.
   inline void Calcular_ol();
   /// Cálculo de tp
   inline void Calcular_tp();

private:
   /// Cálculo dos coeficientes aibicidi necessários para cálculo ol.
   void Calcular_aibicidi_ol();
   /// Cálculo dos efeitos da chuva.
   void Calcular_efeitos_chuva_ol();
   /// Cálculo de aibicidi necessários para cálculo tp
   void Calcular_aibicidi_tp();
   /// Cálculo de aibicidi necessários para cálculo ti
   void Calcular_aibicidi_ti();
   
public:
  /// Saída de dados do objeto para os (tela)
  friend std:ostream& operator<<(std::ostream& os, CMeioPoroso_Telha_Discretizada_TDMA obj);
};
