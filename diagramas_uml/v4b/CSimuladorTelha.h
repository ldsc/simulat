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
	//	CFuncao_wl 					funcao_wl;

protected:
   // Propriedades/atributos associados a interface em modo texto
   ofstream fout;								///< acesso arquivo saída
   char tipoSaida{'a'};                         ///< definição tipo saída
   char nomeArquivoSaidaDisco[40]{"simulat.saida"};///< definição nome arquivo saída disco
   double tempoInicioSaida{0.0};                ///< hora em que a saída começa a ser apresentada na tela
   double intervaloSaidaResultados{600.0};      ///< intervalo de tempo em que a saída é apresentada
   double contadorPassoSaida{7200000.0};        ///< contador que controle passo de saída

//--------------------------------------------------------------------------------------Métodos 
public:
   /// Construtor
   CSimuladorTelha(CFuncoesClima& _fc, CFluido& _f )
   : funcoes_clima(_fc), fluido(_f) {
	cout.precision( 4 );  /// definição padrão para precisão da saída na tela
	fout.setf( ios::fixed | ios::left | ios::dec );
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
   inline void LimparTela(){
	 cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
   }
   void Leiame();						///< Função de help/ajuda
   void FolhaRosto();					///< Tela inicial
   void Carimbo();						///< Carimbo titulo tese
   //void EntrarDadosObjeto();			///< Entrada dados do objeto
   void Inicio_Saida();					///< Inicia apresentacao resultados
   void Saida();						///< Verifica se é para chamar Saida_tela
   void Saida_tela();					///< Apresenta saída dados parciais
   void Fim_Saida();					///< Finaliza apresentacao resultados

   void Calcular_ol_tp_ti();			///< Chama funções ol, t, ti e analiza
   inline void CalcularGanhosEnergia_tp();	///< Cálculo ganhos e perdas massa e energia
   inline void CalcularGanhosEnergia_ti();	///< Cálculo ganhos e perdas massa e energia
   /// ocorrencia oscilações variando dt
   inline void Calcular_olm_tm();		///< Calcula valores médios tm, olm, km, wlm, hm

   /// Cálculo do tempo atual da simulação
   inline void AvancarTempo();
   
public:
  /// Saída de dados do objeto para os (tela)
  friend std:ostream& operator<<(std::ostream& os, CSimuladorTelha obj);
};

/// ---------------------------------------------------------------------------
/// ************  Implementação funções classe CSimuladorTelha     *********
/// ---------------------------------------------------------------------------
/// Dados default
void CSimuladorTelha::DadosDefault()
{
  funcoes_clima.DadosDefault();
  fluido.DadosDefault();
  no_telha.DadosDefault();

  tipoSaida = 'a';
  nomeArquivoSaidaDisco = "simulat.saida";
  tempoInicioSaida =  0.0;
  intervaloSaidaResultados = 600.0;	/// corresponde a um pixel
  contadorPassoSaida = 7200000.0;	/// para garantir saída 1 passo
}

/// ---------------------------------------------------------------------------
/// função de controle principal  /// função global de simulação
/// ---------------------------------------------------------------------------
///  *-*-*-*-*
void CSimuladorTelha::ExecutarSimulador(){
   cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";	/// ctrlbrk é função do dos.h
   FolhaRosto();		        		/// mostra folha de rosto nome programa, autor,laboratorio
   EntrarDadosObjeto();		/// executa funções de entrada de todas as classes
   /// mostra dados, repete até que tudo esteja correto
   Inicio_Saida();		        		/// desenha tabulacao inicial para tela e disco
   do {
         Calcular_ol_tp_ti();		/// rotina cálculo ol,t,ti, considerando oscilações e variando dt

         if( ( tempoInicioSimulacao + tempoDecorrido ) >= tempoInicioSaida )
            Saida();		    		/// função saída resultados tela,disco,prn
      }				                                		/// +dt

   while( ( tempoInicioSimulacao + tempoDecorrido ) <= tempoFimSimulacao ); /// +dt/60*60);

   Fim_Saida();
}
