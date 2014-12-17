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
   double inicioChuva;  					///< hora início da chuva
   double fimChuva;  						///< hora fim da chuva
   double precipitacao;  					///< precipitacao em mm
   double olChuva;  						///< conteúdo mássico de umidade relativo a chuva

   // Propriedades/atributos associados a interface em modo texto
   // O usuário pode definir a temperatura interna e umidades externa e interna
   // como constantes ou como função da temperatura externa
   char respTemperaturaInterna{'c'};		///< temperatura interna constante ou calculada
   char respHumidadeExterna{'c'};  			///< umidade externa constante ou calculada
   char respHumidadeInterna{'c'};			///< umidade interna constante ou calculada

//--------------------------------------------------------------------------------------Métodos
public:
   CFuncoesClima()							///< Construtor
   {
	 ExecutarFuncoesClima()
   }
   ~CFuncoesClima();						///< Destrutor
   /// Entrada de dados
   void EntrarDadosObjeto();
   /// Executa funções clima
   void ExecutarFuncoesClima(double hora);
   /// Executa funções clima
   double operator()( double hora) { ExecutarFuncoesClima(); return hora; }

// protected:
   /// Cálculo da temperatura externa (função do tempo - hora)
   double FuncaoTemperaturaExterna( double hora );
   /// Cálculo da temperatura interna
   inline void FuncaoTemperaturaInterna( double hora );
   /// Cálculo da umidade externa (função da temperatura externa)
   inline void FuncaoUmidadeExterna();
   /// Cálculo da umidade interna (função da temperatura interna)
   inline void FuncaoUmidadeInterna();
   /// Cálculo da concentração de vapor
   inline double FuncaoConcentracaoVapor( double umidade, double temperatura );
   /// Cálculo da pressão de vapor
   inline double FuncaoPressaoVapor( double temperatura );
   /// Cálculo da radiação de onda curta
   void FuncaoRadiacaoOndaCurta( double hora );
   /// Cálculo da radiação de onda longa
   inline void FuncaoRadiacaoOndaLonga( double hora );
   /// Cálculo da emissividade
   /// void CalculoEmissividade();
   
   aquiaqui incluir saída para cout/os, que será chamada pelo simulador
   std:ostream& operator<<(std::ostream& os, CFuncoesClima obj);
};

/// ------------------- Classe CFuncaoDifusividade -----------------------------------
/// Representa a função de difusidade ao vapor de um meio poroso; no caso específico, a telha de cerâmica.
/// A partir dos resultados do ensaio de difusividade, foi desenvolvida regressão estatistica
/// que correlaciona a difusividade e o conteúdo de massa volumétrico ol.
/// *-*-*-*-*    /// redefinivel
/// Para testar outros materiais, você deve incluir aqui a regressão para o material em estudo.
/// @todo: Para valer para outros ensaios, usar polinômios de grau n;
/// ler dados funcaoDifusividade.dat do disco, criando m polinômios!
class CFuncaoDifusividade
{
protected:
   double cdif{1.0}; 					    	///< multiplicador da difusividade

public:
   CFuncaoDifusividade() = default;				///< Construtor
   ~CFuncaoDifusividade()= default;				///< Destrutor
   /// Entrada de dados (associados aos ensaios)
   void EntrarDadosFuncao() {};
   /// Cálculo da difusividade a partir do conteúdo massa volumétrico ol (correlações obtidas a partir de ensaios)
   double FuncaoDifusividade( double ol );
   /// Cálculo da difusividade a partir do conteúdo massa volumétrico ol (correlações obtidas a partir de ensaios)
   double operator()( double ol ) { return FuncaoDifusividade(ol); };
   
   aquiaqui incluir saída para cout/os, que será chamada pelo simulador
   std:ostream& operator<<(std::ostream& os, CFuncaoDifusividade obj);
};


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
   void EntrarDadosFuncao() {};

   /// Cálculo da condutividade a partir da relação entre a condutividade térmica k e o conteúdo de
   /// massa mássico da telha wl.
   inline double FuncaoCondutividade( double wl )	{  /// double k = bk + ak * wl;
	  return ( bk + ak * wl );			/// return(k);
	}
   /// Cálculo da condutividade a partir da relação entre a condutividade térmica k e o conteúdo de
   /// massa mássico da telha wl.
   double operator()( double wl ) { return FuncaoCondutividade( wl ); };
   
   aquiaqui incluir saída para cout/os, que será chamada pelo simulador
   std:ostream& operator<<(std::ostream& os, CFuncaoCondutividade obj);
};

/// ------------------- Classe CFuncaoAdsorcao -----------------------------------
/// Calcula a umidade a partir das curvas de adsorção do material (correlações fornecidas pelo usuário).
/// *-*-*-*-*    /// redefinivel
class CFuncaoAdsorcao
{
public:
   CFuncaoAdsorcao();				///< Construtor
   ~CFuncaoAdsorcao();				///< Destrutor

protected:
   /// Entrada de dados (associados aos ensaios)
   void EntrarDadosFuncao();
   /// Cálculo da umidade em função do conteúdo massa mássico wl (resultado do ensaio de adsorção).
   double FuncaoUmidade( double wl, double temperatura, char tipo_material );
   /// Cálculo da umidade em função do conteúdo massa mássico wl (resultado do ensaio de adsorção).
   double operator()( double wl, double temperatura, char tipo_material ) {
     return FuncaoUmidade( wl, temperatura, tipo_material )};
	 
   aquiaqui incluir saída para cout/os, que será chamada pelo simulador
   std:ostream& operator<<(std::ostream& os, CFuncaoAdsorcao obj);
};
/// ------------------- classe CMeioPoroso_Telha -------------------------------------
/// Classe CMeioPoroso_Telha: para entrada de dados relativos ao meio poroso 
/// Representa ao mesmo tempo uma telha permeável e uma telha impermeável,
/// ou seja, vai calcular as informações para os dois casos, permitindo a comparação dos valores.
/// @todo: verificar vantagens de separar em duas classes, uma para impermeável e outra para permeável.
/// *-*-*-*-*    /// redefinivel
class CMeioPoroso_Telha
{
/// Objetos agregados
public:
 	CFuncaoDifusividade 		funcaoDifusividade; ///< Função usada cálculo difusividade.
 	CFuncaoCondutividade		funcaoCondutividade;///< Função usada cálculo condutividade.
 	CFuncaoAdsorcao				funcaoAdsorcao;		///< Função usada cálculo adsorção.

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
   CMeioPoroso_Telha( char tipo_material = 'c' ) {
     DadosDefault( tipo_material );
   }
   /// Destrutor
   ~CMeioPoroso_Telha() = default;
   /// Dados default
   void DadosDefault();
   /// Entrada de dados
   void EntrarDadosObjeto();
   
   friend class CFuncao_wl;		/// POderá acessar rot
   
   aquiaqui incluir saída para cout/os, que será chamada pelo simulador
   std:ostream& operator<<(std::ostream& os, CMeioPoroso_Telha obj);
};

/// ------------------- classe CFluido -------------------------------------
/// Classe CFluido: para entrada de dados relativos ao fluido *-*-*-*
/// propriedades do líquido e gás
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
   void DadosDefault(){
	    rol = 1000.0;   cl = 4187.0;  lv = 2256685.0;
   }
   /// Entrada de dados
   void EntrarDadosObjeto();

   friend class CFuncao_wl;		/// Poderá acessar rol
   
   aquiaqui incluir saída para cout/os, que será chamada pelo simulador
   std:ostream& operator<<(std::ostream& os, CFluido obj);
};

/// ------------------- classe CFuncao_wl -------------------------------------
/// Classe CFuncao_wl: usada para cálculo do conteúdo de massa mássico wl, a partir ol, rol e rot.
/// Note que é uma classe de associação, que calcula uma informaçao com base nas informações de duas
/// classes associadas, a CFluido e a CMeioPoroso_Telha.
class CFuncao_wl
{
protected:
//    double& rol; 							///< densidade líquido (água)
//    double& rot; 							///< densidade (telha)
  CFluido & fluido;							///< fluido
  CMeioPoroso_Telha & telha;				///< telha

/// funções
public:
   /// Construtor
   //CFuncao_wl(CFluido fluido, CMeioPoroso_Telha telha): rol(fluido.rol), rot(telha.rot) ;
   CFuncao_wl(CFluido _fluido, CMeioPoroso_Telha _telha): fluido(_fluido), telha(_telha) ;
   /// Destrutor
   ~CFuncao_wl() = default;
   
   /// Calcula o conteúdo de massa mássico wl em função do conteúdo de massa volumétrico ol.
   /// @param ol conteúdo de massa volumétrico
   inline double Funcao_wl( double ol ){
	//return ( ol * rol / rot );
	return ( ol * fluido.rol / telha.rot );
	}
   /// Calcula o conteúdo de massa mássico wl em função do conteúdo de massa volumétrico ol.
   /// @param ol conteúdo de massa volumétrico
   inline double operator()( double ol ) { return Funcao_wl(ol); }
   
   aquiaqui incluir saída para cout/os, que será chamada pelo simulador
   std:ostream& operator<<(std::ostream& os, CFuncao_wl obj);
};


/// ------------------- classe CTransferenciaCalorMassa -------------------------------------
/// Classe CTransferenciaCalorMassa: 
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
   CTransferenciaCalorMassa();
   /// Destrutor
   ~CTransferenciaCalorMassa();

protected:
   /// Dados default
   void DadosDefault(){
    hce = 16.7; hci = 9.1; hme = 0.01386;  hmi = 0.0076;
   }
   /// Entrada de dados
   void EntrarDadosObjeto();
   
   aquiaqui incluir saída para cout/os, que será chamada pelo simulador
   std:ostream& operator<<(std::ostream& os, CTransferenciaCalorMassa obj);
   
};

/// ------------------------- Classe CSolver_TDMA ---------------------------------------
/// Representa um solver TDMA - Tri-Diagonal  Matriz Algorithm.
class CSolver_TDMA
{
protected:
   // Propriedades do Método Numérico - Discretização
   // Propriedades do Método Numérico - TDMA
   double a[nodos + 1];				///< Vetor coeficiente a do método numérico TDMA
   double b[nodos + 1];				///< Vetor coeficiente b do método numérico TDMA
   double c[nodos + 1];				///< Vetor coeficiente c do método numérico TDMA
   double d[nodos + 1];				///< Vetor coeficiente d do método numérico TDMA
   double p[nodos + 1];				///< Vetor coeficiente p do método numérico TDMA
   double q[nodos + 1];				///< Vetor coeficiente q do método numérico TDMA

//--------------------------------------------------------------------------------------Métodos
public:
   /// Construtor
   CSolver_TDMA();
   /// Destrutor
   ~CSolver_TDMA();

protected:
   /// Cálculo dos coeficientes do método de Thomas
   void Calcular_piqi();

   aquiaqui incluir saída para cout/os, que será chamada pelo simulador
   std:ostream& operator<<(std::ostream& os, CSolver_TDMA obj);
};
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
  // Objetos agregados
  //   FuncaoDifusividade	funcao_difusividade;
  //   FuncaoCondutividade	funcao_condutividade;
  //   CFuncaoAdsorcao 		funcao_adsorcao;
  CFluido&				fluido;
  CFuncao_wl& 			funcao_wl;

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

/// funções da classe CMeioPoroso_Telha_Discretizada_TDMA
public:
  /// Construtor
  CMeioPoroso_Telha_Discretizada_TDMA(CFuncoesClima _fc, CFluido _f, CFuncao_wl _fwl)
  :funcoes_clima(_fc), fluido( _f ), funcao_wl( _fwl )  {};
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

protected:
   /// Cálculo dos coeficientes aibicidi necessários para cálculo ol.
   void Calcular_aibicidi_ol();
   /// Cálculo dos efeitos da chuva.
   void Calcular_efeitos_chuva_ol();
   /// Cálculo de aibicidi necessários para cálculo tp
   void Calcular_aibicidi_tp();
   /// Cálculo de aibicidi necessários para cálculo ti
   void Calcular_aibicidi_ti();
   
public:
   aquiaqui incluir saída para cout/os, que será chamada pelo simulador
   std:ostream& operator<<(std::ostream& os, CMeioPoroso_Telha_Discretizada_TDMA obj);
};

/// ------------------------- Classe CSimuladorTelha -------------------------------------
/// Contém todas as funções necessárias para gerar as saídas para tela, impressora, disco e gráficas.
/// Posteriormente deverá ser desmembrada (ex: tela/disco/impressora).
/// Nota: Quando gerou a versão para Unix eliminou saída gráfica pois usava drives e bibliotecas 
/// disponíveis apenas para DOS.
/// Quando gerou versão 4, com divisão das classes, eliminou saíuda para impressora,
/// o motivo, não se vende mais este tipo de impressora.
/// *-*-*-*-*
/// Todos os comandos gráficos estão formatados para o DOS e consideram que o seu monitor aceita o modo vga!!!
/// Na versão para UNIX e GNU-LINUX a parte gráfica do DOS foi desativada.
class CSimuladorTelha 
{  
/// Objetos agregados
protected:
	CFuncoesClima 					funcoes_clima;
	CFluido 						fluido;
	CMeioPoroso_Telha_Discretizada_TDMA	no_telha;
	// 	CSolver_TDMA				solver_tdma;
	// 	CMeioPoroso_Telha 			telha;
	// 	CTransferenciaCalorMassa	transcal;
	CFuncao_wl 						funcao_wl;

protected:
   // Propriedades do Método Numérico - Discretização
   // Propriedades do Método Numérico - Controle avanço/recuo do intervalo de tempo - dt
   // o programa Simulat tem mecanismo que varia dt entre o intervalo dtmin <= dt <= dtmax.
   double dt; 								///< intervalo de tempo da simulação
   double dta; 								///< intervalo de tempo da simulação no instante anterior
   double dtmax;							///< intervalo de tempo máximo da simulação
   double dtmin;							///< intervalo de tempo mínimo da simulação
   double tempo;							///< tempo/hora atual da simulação (varia entre 0->24h)
   double m; 								///< ???
   int n { nodos };							///< Número de nós (volumes de controles)

   int recorrencia;							///< número de recorrências cálculo acoplamento conteúdos e temperaturas.

   // Propriedades da simulação
   // Propriedades climáticas
   double tempoInicioSimulacao;                 ///< hora inicial da simulação
   double tempoDecorrido;                       ///< tempo decorrido da simulação
   double tempoFimSimulacao;               		///< hora de encerramento da simulação (ex: 24 1 dia, 48 2 dias, 72 3 dias)
   double contadorPassoSaida;                   ///< contador que controle passo de saída
   /// double errorecorrenciaol,errorecorrenciatp,errorecorrenciaola,errorecorrenciatpa;

   // Propriedades/atributos associados a interface em modo texto
   ofstream fout;								///< acesso arquivo saída
   char tipoSaida;                              ///< definição tipo saída
   char nomeArquivoSaidaDisco[40];              ///< definição nome arquivo saída disco
   double tempoInicioSaida;                     ///< hora em que a saída começa a ser apresentada na tela
   double intervaloSaidaResultados;             ///< intervalo de tempo em que a saída é apresentada

   // Propriedades/atributos associados a interface em modo gráfico
   /// int sinal,dec;             				///< atributos numéricos usados na saída gráfica
   /// tempo, ol, tp e ti na saida gráfica.
   /// int xol, yolm, xt, ytpm, ytim; 			///< pontos gráficos atuais
   /// int xola,yolma,xta,ytpma,ytima;			///< pontos gráficos anteriores
   /// int yol[nodos+1],yesp,ytp[nodos+1],yti[nodos+1];
   /// int yola[nodos+1],yespa,ytpa[nodos+1],ytia[nodos+1];

   // Resultados, valores médios
   double wlm;                                  ///< conteúdo mássico médio ?
   double hm;                                   ///< coeficiente transferência massa médio ?
   double km;                                   ///< condutividade média ?
   double olm;                                  ///< conteúdo massa médio ?
   double tpm;                                  ///< temperatura média telha permeável ?
   double tim;                                  ///< temperatura média telha impermeável ?

   /// As linhas abaixo se referem as trocas de energia
   /// o arquivo variavel.doc descreve o significado de cada uma delas
   double gev;                                  ///< 
   double giv;                                  ///< 
   double gesp;                                 ///< 
   double gec;                                  ///< ganho externo convecção
   double gic;                                  ///< ganho interno convecção
   double gecl;                                 ///< ganho externo calor latente
   double gicl;                                 ///< ganho interno calor latente
   double geroc;                                ///< ganho externo radiação onda curta
   double gerol;                                ///< ganho externo radiação onda longa
   double gir;                                  ///< ganho interno radicao
   double bm;                                   ///< balanco massa
   double be;                                   ///< balanco energia
   double geci;                                 ///< ganho externo convecção
   double gici;                                 ///< ganho interno convecção
   double geroci;                               ///< ganho externo radiação onda curta
   double geroli;                               ///< ganho externo radiação onda longa
   double giri;                                 ///< ganho interno radicao

//--------------------------------------------------------------------------------------Métodos 
public:
   /// Construtor
   CSimuladorTelha(){
	  cout.precision( 4 );  /// definição padrão para precisão da saída na tela
	  DadosDefault();
   }
   /// Destrutor
   ~CSimuladorTelha() = default;

   /// Dados default
   void DadosDefault();
   /// Entrada de dados
   void EntrarDadosObjeto();

   /// Construtor sobrecarregado para entrada n
   /// CSimuladorTelha(unsigned int númeropontos);
   /// Executa a simulação
   void ExecutarSimulador();
   /// Função para encerramento do programa
   int c_break( void );

protected: 
   void Leiame();						///< Função de help/ajuda
   void FolhaRosto();					///< Tela inicial
   void SelecionarTiposSaidas();		///< Seleciona tipos saídas desejadas
   void ExecutarFuncoesEntrada();		///< Executa todas as procedures de entradas

   void Calcular_ol_tp_ti();			///< Chama funções ol, t, ti e analiza
   inline void CalcularGanhosEnergia_tp();	///< Cálculo ganhos e perdas massa e energia
   inline void CalcularGanhosEnergia_ti();	///< Cálculo ganhos e perdas massa e energia
   /// ocorrencia oscilações variando dt
   inline void Calcular_olm_tm();		///< Calcula valores médios tm, olm, km, wlm, hm

   /// ------cabecalho inicial para tela ou disco------
   void Cabecalho_tela();				///< Tabela com vari veis de saida
   void Cabecalho_disco();				///< Tabela com vari veis saida para disco
   /// -------inicio_saida--------------------------
   void Inicio_Saida();					///< Inicia apresentacao resultados
   void Inicio_Saida_tela();			///< Switch para selecionar tabela de saída
   /// void Inicio_Saida_gráfica();     ///< Desenha tela gr fica inicial
   void Inicio_Saida_so_disco();		///< Cria tela para percentagem concluida
   void Inicio_Saida_passo_a_passo();   ///< Tabela para procedimento passo a passo
   void Inicio_Saida_disco();			///< Tabela para procedimento passo a passo (disco)
   /// ------saida-----------------------------------
   void Saida();						///< Switch seleciona saída correta
   void Carimbo();						///< Carimbo titulo tese
   void Saida_tela();					///< Saída para tela
   void Saida_disco();					///< Saída disco passo a passo
   /// void Saida_gráfica_Initialize();   ///< Inicializa saída gr fica
   /// void Saida_gráfica_intermediaria();///< Saída gráfica comum
   /// void Saida_gráfica();             ///< Saída para gr fico
   /// void Saida_gráfica_passo_a_passo();///< Saída para grafico paraa/p
   void Saida_passo_a_passo();			///< Saída tela passo a passo
   /// void Saida_disco();
   /// ------Fim_Saida----------------------------------
   void Fim_Saida();					///< Finaliza apresentacao resultados
   void Final_Saida_disco();			///< Dados finais para disco

   /// Cálculo do tempo atual da simulação
   inline void AvancarTempo();
   

   /// Entrada de dados (que normalmente são modificados)
   void EntrarVariaveis();	    ///< Entrada dtmax dtmin
   
};
