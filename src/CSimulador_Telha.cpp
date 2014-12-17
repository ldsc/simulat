
/// -------------------  Bibliotecas --------------------------------
#include <cstdio>
#include <cassert>
#include <fstream>			/// por causa ifstream e ofstream ponteiros arquivos
#include <iostream>			/// por causa rotinas entrada saída
#include <iomanip>			/// manipuladores, como setw()
#include <cmath>			/// por causa funções matemáticas

#include "CInterface.h"
#include "CSimulador_Telha.h"
#include "CTermodinamica.h"
using namespace std;

/// ---------------------------------------------------------------------------
/// ************  Implementação funções classe CSimulador_Telha   *********
/// ---------------------------------------------------------------------------
/// Construtor
CSimulador_Telha::CSimulador_Telha() {
	DadosDefault();

	// A funcaoConteudoMassicoWl precisa acessar o fluido e a telha para cálculo wl.
	funcaoConteudoMassicoWl.Fluido( &fluido );
	funcaoConteudoMassicoWl.Telha( static_cast<CMeioPoroso_Telha*> (this) );

	/// Atributos associados a saída gráfica (CGnuplot)
	vhora.reserve(240);			// reserva espaço nos vetores
	ol0.reserve(240);
	oln_1.reserve(240);
	tp0.reserve(240);
	tpn_1.reserve(240);
	ti0.reserve(240);
	tin_1.reserve(240);
								// define estilo, titulos e intervalos dos gráficos.
	grafico_ol.Style("lines").XAutoscale().YAutoscale().Grid();
	//grafico_ol.Style("lines").XRange(0,200).YRange(0,0.35); //lines points linespoints
	grafico_ol.Title("Conteudo Massa Volumetrico").XLabel("hora").YLabel("ol");
	
	grafico_tp.Style("lines").XAutoscale().YAutoscale().Grid();
	//grafico_tp.Style("lines").XRange(0,200).YRange(15,50);
	grafico_tp.Title("Temperatura telha permeavel").XLabel("hora").YLabel("tp");
	
	grafico_ti.Style("lines").XAutoscale().YAutoscale().Grid();
	//grafico_ti.Style("lines").XRange(0,200).YRange(15,50);
	grafico_ti.Title("Temperatura telha impermeavel").XLabel("hora").YLabel("ti");
}

/// Destrutor
CSimulador_Telha::~CSimulador_Telha() {
	// Antes de destruir os gráficos o simulador salva os mesmos em disco.
	// 	grafico_ol.SaveTops("grafico_ol").replot();
	// 	grafico_tp.SaveTops("grafico_tp").replot();
	// 	grafico_ti.SaveTops("grafico_ti").replot();
	grafico_ol 	<< "set term png truecolor\n"
				<< "set output \"grafico_ol.png\"\n"
				<< "replot\n" ;
	grafico_tp 	<< "set term png truecolor\n" 
				<< "set output \"grafico_tp.png\"\n"
				<< "replot\n" ;
	grafico_ti 	<< "set term png truecolor\n"
				<< R"(set output "grafico_ti.png")"  // uso raw string
				<< "\nreplot\n" ;
	cout << "\nSalvando gráficos em disco... aguarde 2s\n";
    system("sleep 2"); // aguarda plotagem do grafico_ti
}

/// Destrutor
void CSimulador_Telha::SaidaGrafica_FimSaida() {
	grafico_ol.PlotVector( vhora, ol0 ," ol0" );
	grafico_ol.PlotVector( vhora, oln_1 ," oln_1");
	grafico_tp.PlotVector( vhora, tp0 ," tp0");
	grafico_tp.PlotVector( vhora, tpn_1 ," tpn_1");
	grafico_ti.PlotVector( vhora, ti0 ," ti0");
	grafico_ti.PlotVector( vhora, tin_1 ," tin_1");
}

/// Implementação dados default classe CSimulador_Telha
void CSimulador_Telha::DadosDefault() {
	// Herdado
	CMeioPoroso_Telha_Discretizada_TDMA::DadosDefault();
	CTransferenciaCalorMassa::DadosDefault();
	CSolver_TDMA::DadosDefault();

	// Agregados
	funcoesClima.DadosDefault();
	fluido.DadosDefault();
	//funcaoConteudoMassicoWl.DadosDefault();
	//Atributos valores médios
	wlm = 0.0;
	hm = 0.0;
	km = 0.0;
	olm = 0.0;
	tpm = 0.0;
	tim = 0.0;
	// Atributos simulação
	dt    = 60.0;           /// intervalo de tempo usado nos cálculos.
	dta   = 60.0;           /// intervalo de tempo usado nos cálculos (instante anterior).
	dtmax = 60.0;			/// intervalo de tempo máximo.
	dtmin = 1.0;			/// intervalo de tempo mínimo.
	tempo = 0.0;			/// tempo inicial.
	//m = 0.0;              /// ?.
	recorrencia = 2;		/// 1.
	tempoDecorrido = 0.0;
}

/// ---------------------------------------------------------------------------
/// Implementação função fdadosti
/// entrada de dados para classe CTelhaImpermeaveli valores de ti[i] para tempo inicial
void CSimulador_Telha::EntrarDadosObjeto() {
	CInterface::Carimbo();
  // Chamando EntrarDadosObjeto() dos objetos herdados
	CMeioPoroso_Telha_Discretizada_TDMA::EntrarDadosObjeto();
	CTransferenciaCalorMassa::EntrarDadosObjeto();
	CSolver_TDMA::EntrarDadosObjeto();
	
  // Chamando EntrarDadosObjeto() dos objetos agregados!
  funcoesClima.EntrarDadosObjeto();
  fluido.EntrarDadosObjeto();
  //funcaoConteudoMassicoWl.EntrarDadosFuncao();

  //------------------------
	CInterface::Carimbo();
	cout << "\nEntrada dados associados ao acoplamento entre balanço de massa e balanço energia.";
	cout << "\nO cálculo do conteúdo de umidade (ol) é realizado com a temperatura no instante anterior.";
	cout << "\nEntre com o número de recorrências " << recorrencia << " para acoplamento do balanço de massa e de temperatura : ";
	cin >> recorrencia;
  //------------------------
	cout << "\nEntrada dados associados ao controle do passo de tempo dt.";
	cout << "\nIntervalo de tempo em segundos (dt) " << dt << "s: ";
	cin >> dt;
	cout << "\nIntervalo de tempo máximo em segundos (dtmax) " << dtmax << "s: ";
	cin >> dtmax;
	cout << "\nIntervalo de tempo minimo em segundos (dtmin) " << dtmin << "s: ";
	cin >> dtmin;
}

/// ---------------------------------------------------------------------------
/// Implementação função ftempo
/// calcula tempo atual, baseado número do passo m, no dt e tempoInicioSimulacao .
void CSimulador_Telha::AvancarTempo() {
   /// tempo=m*dt/(60*60)+tempoInicioSimulacao;
   tempo = tempo + dt / ( 60.0 * 60.0 );

   while( tempo > 24.0 )
      tempo = tempo - 24.0;
}


/// ---------------------------------------------------------------------------
/// função classe CSimulador_Telha void Calcular_ti_ol_tp()
///  *-*-*-*-*
void CSimulador_Telha::Calcular_ti_ol_tp()	{
   /// Define variáveis nescessárias para verificar ocorrência de oscilações.
   double var_ol, var_tp, var_ti, var_esp, var_min;
   var_ol = var_tp = var_ti = var_esp = var_min = 10.0;

   /// Armazenamento variáveis anteriores:
   espaa = espa;										/// armazena espessuras
   espa = esp;

   /// Armazena valores anteriores de ol[i]
   for( int i = 1; i <= n; i++ ) {	
         olaa[i] = ola[i];								/// armazena ol
         ola[i] = ol[i];
         tpaa[i] = tpa[i];								/// armazena ti
         tpa[i] = tp[i];
         tiaa[i] = tia[i];								/// armazena ti
         tia[i] = ti[i];
      }

   /// sistema para verificar ocorrência de oscilação e cálculo dt
   do {
         dta = dt;										// armazena valor anterior dt
         AvancarTempo(); 								// veio de CFuncoesClima
         funcoesClima.ExecutarFuncoesClima( tempo );	// incrementa tempo e cálculo variáveis climaticas
         Calcular_wl_h_rov_dif_k();		// cálculo valores  wl[i],h[i],rov1,rovn,e valores intermediarios dif[i],k[i].
         Calcular_ti();     							// cálculo balanco energia ti[i] sem adsorçao
         /// objetivo recorrência é calcular ol e t com valores tempo atual
         int iii = 0; //?? não usa??
         for( int ii = 1; ii <= recorrencia; ii++ ) {
		  Calcular_ol();    							// armazena ola[i],cálculo balanco de massa ol[i]
          Calcular_tp();    							// armazena ta[i],cálculo balanco de energia  t[i]
               /*                  if(errorecorrenciaol<(ol[1]-ola[1]))/// armazena maior erro
                 {errorecorrenciaol=(ol[1]-ola[1]); math.h
                 iii=1;}
                 if(errorecorrenciatp<abs(tp[1]-tpa[1]))
                 {errorecorrenciatp=abs(tp[1]-tpa[1]);	// armazena maior erro
                 iii=1;}
               */
            }
	/// @todo: separar função de controle dt
         /*        if(iii==1)
         { errorecorrenciatpa=abs(tp[1]-tpa[1]);  		// armazena reducao erro
         errorecorrenciaola=abs(ol[1]-ola[1]);
         }
         */
         /// os if são nescessários para verificar se dividendos !=0 (diferentes de 0)
         if( ( ola[1] - olaa[1] ) != 0.0 )				// cálculo variacoes
            var_ol = ( ol[1] - ola[1] ) / ( ola[1] - olaa[1] );

         if( ( espa - espaa ) != 0.0 )
            var_esp = ( esp - espa ) / ( espa - espaa );

         if( ( tpa[1] - tpaa[1] ) != 0.0 )
            var_tp = ( tp[1] - tpa[1] ) / ( tpa[1] - tpaa[1] );

         if( ( tia[1] - tiaa[1] ) != 0.0 )
            var_ti = ( ti[1] - tia[1] ) / ( tia[1] - tiaa[1] );

         if( var_min > var_ol )								// var_min=menor variação
            var_min = var_ol;								// 5 3 2 1 0 -3 -6 var_min=-6

         if( var_min > var_esp )							// calcula menor valor de variação
            var_min = var_esp;

         if( var_min > var_tp )
            var_min = var_tp;

         if( var_min > var_ti )
            var_min = var_ti;

         if( var_min > 0.0 ) {								// não oscilou calcula novo dt e continua
															// no caso de var_min=+3 ou =+0.6
               dt = dt / var_min;							// dt cresce var_min<1 ou decresce var_min>1

               if( dt > 2.0 * dta )
                  dt = 2.0 * dta;							// limita o crescimento de dt a 2*dt anterior

               if( dt > dtmax )
                  dt = dtmax;								// limita valor dt ao valor max de dt
            }
         else {												// oscilou
               if( dt <= dtmin ) {							// oscilou ,mas dt=dtmin, logo continua
                     dt = dtmin;							// garante que dt não seja menor que dtmin.
                     var_min = 1;							// garante mesmo que tenha ocorrido oscilacao, que
                  }											// continue os cálculos se dt=dtmin.

               if( dt > dtmin ) {							// se dt>dtmin retorna tempo anterior e diminue dt
                     /// dta
                     tempo = tempo - dt / ( 60.0 * 60.0 );	// retorna tempo anterior

                     if( tempo < 0 )						// se justifica porque se ocorrer oscilações o dt atual
                        tempo = tempo + 24.0;				// vai ser menor que o anterior, e no caso de estarmos
															/// no limite de 24h o tempo poderiaficar negativo.
                     esp = espa;
                     espa = espaa;

                     for( int i = 1; i <= n; i++ ) {
															// reestabelecendo as variáveis
                           ol[i] = ola[i];	    			// ao tempo anterior
                           ola[i] = olaa[i];
                           ti[i] = tia[i];
                           tia[i] = tiaa[i];
                           tp[i] = tpa[i];
                           tpa[i] = tpaa[i];
                        }

                     /// e diminue valor de dt
                     if( var_min < 0.0 )
                        var_min = -var_min;

                     if( var_min > 1 )	        			// no caso de var_min =-3  alteracao tirei abs
                        dt = dt / -var_min;	    			// calcula novo dt menor que anterior
                     else
                        dt = dt * 0.5;	        			// no caso de var_min=-0.4

                     if( dt <= dtmin )
                        dt = dtmin;	            			// garante que dt não seja menor que dtmin.
                  }
            }			                        			// fim else oscilacao
      }
   while( var_min < 0.0 );		                			// retorna se ocorreu oscilacao var_min<0

  //m++;										// depois de corretos os cálculos incrementa m
												// que vai aparecer saída final tela e passo a passo
												// indicando o número de passos nescessários para cumprir temposaida
												// hora = hora + segundos*(1hora/60min*60seg)
   tempoDecorrido = tempoDecorrido + dta / ( 60.0 * 60.0 );
}

/// ---------------------------------------------------------------------------
/// Implementação função Calcular_olm_tm calcula valores médios dos resultados de ol[i], t[i], ti[i]
void CSimulador_Telha::Calcular_olm_tm() {
   olm = tpm = tim = wlm = hm = km = 0.0;
   for( int i = 1; i <= n; i++ ) {
         olm += ol[i];
         tpm += tp[i];
         tim += ti[i];
      }
   olm = olm / n;
   tpm = tpm / n;
   tim = tim / n;

   wlm = funcaoConteudoMassicoWl.Wl( olm );
   hm = funcaoAdsorcao->Umidade( wlm, tpm );
   km = funcaoCondutividade.Condutividade( wlm );
}


/// ---------------------------------------------------------------------------
/// Calcula os valores médios de condutividade, difusividade, e os valores de conteúdo de massa mássico(wl),
/// h[1],h[n],rov[1],rov[n] para todos os pontos.
void CSimulador_Telha::Calcular_wl_h_rov_dif_k() {
  wl[1] = funcaoConteudoMassicoWl.Wl( ol[1] );
  h[1] = funcaoAdsorcao->Umidade( wl[1], tp[1] );					///  para cálculo rov1=f(h1,t1)
  rov[1] = CTermodinamica::ConcentracaoVapor( h[1], tp[1] );		///  paracálculo rov1

   for( int i = 2; i <= n; i++ ) {
        wl[i] = funcaoConteudoMassicoWl.Wl( ol[i] );
        dif[i] = funcaoDifusividade.Difusividade( ( ol[i] + ol[i - 1] ) / 2.0 );
        k[i] = funcaoCondutividade.Condutividade( ( wl[i] + wl[i - 1] ) / 2.0 );
      }
	// Linha abaixo não estava presente na versão unix; mas como foi corrigida na versão para DOS em 4/2000,
	// copiei para cá em 24/03/2014.
	//BUG 4/2000  abaixo calcula h[n] usando wl[n], mas faltava o cálculo de wl[n]
   wl[n] = funcaoConteudoMassicoWl.Wl( ol[n] ); //BUG 4/2000 linha incluida em 4/2000
   h[n] = funcaoAdsorcao->Umidade( wl[n], tp[n] );
   /// para cálculo rovn usa função rovn=f(hn,tn)
   rov[n] = CTermodinamica::ConcentracaoVapor( h[n], tp[n] );
   /// cálculo rovn h e t tempo anterior
}


/// ---------------------------------------------------------------------------
/// função classe CTelhaImpermeaveli, função cálculo fti
/// inicia vari veis da classe
void CSimulador_Telha::Calcular_ti() {
  Calcular_aibicidi_ti();					/// valores de a[i],b[i],c[i],d[i]
  ResolverSistemaEquacoes_TDMA_piqi();		/// valores de p[i],q[i]
  ti[n] = q[n];								/// calcula valores atuais ti

  for( int i = n; i > 1; i-- )
      ti[i - 1] = p[i - 1] * ti[i] + q[i - 1];
}

/// ---------------------------------------------------------------------------
/// Implementação função fTiiaibicidi
/// calcula vari veis aibicidi do método implicito
void CSimulador_Telha::Calcular_aibicidi_ti() {
   double temp, dx_dt;
   dx_dt = dx / dt;
   temp = ( rot * ( ct + fluido.cl * wli ) * dx_dt );
   b[1] = ki / dx;
   c[1] = 0.0;
   a[1] = hce + b[1] + temp / 2.0;				/// para telha sem adsorção
   d[1] = alfa * funcoesClima.radoc + emis * funcoesClima.radol + hce * funcoesClima.text + temp / 2.0 * ti[1];

   for( int i = 2; i < n; i++ ) {
         b[i] = c[i] = ki / dx;
         a[i] = b[i] + c[i] + temp;
         d[i] = temp * ti[i];
      }

   b[n] = 0.0;
   c[n] = ki / dx;
   a[n] = hci + c[n] + temp / ( 2.0 );
   d[n] = hci * funcoesClima.tint + temp * ti[n] / ( 2.0 );
}

/// ---------------------------------------------------------------------------
/// Implementação função cálculo oli
/// calcula os valores de ol[i], baseado nos valores de piqi
/// depois limita os valores de ol[i], em material seco ou saturado
void CSimulador_Telha::Calcular_ol() {
  Calcular_aibicidi_ol();						/// valores de a[i],b[i],c[i],d[i]
  ResolverSistemaEquacoes_TDMA_piqi();			/// valores de p[i],q[i]

  ol[n] = q[n];									/// calcula novos valores ol
  for( int i = n; i > 1; i-- )
    ol[i - 1] = p[i - 1] * ol[i] + q[i - 1];

  Calcular_efeitos_chuva_ol();
}

/// ---------------------------------------------------------------------------
/// Implementação função folaibicidi
/// calcula constantes aibicidi do método implicito
void CSimulador_Telha::Calcular_aibicidi_ol() {
   double dx_dt = dx / dt;
   b[1] = dif[1 + 1] / dx;
   a[1] = b[1] + dx_dt / ( 2.0 );
   c[1] = 0.0;
   d[1] = hme * ( funcoesClima.rove - rov[1] ) / fluido.rol + ol[1] * dx_dt / ( 2.0 ) - ( esp - espa ) / dt;
   /// +(esp-espa)/dt para -(esp-espa)/dt

   for( int i = 2; i < n; i++ ) {
         b[i] = dif[i + 1] / dx;
         c[i] = dif[i] / dx;
         a[i] = b[i] + c[i] + dx_dt;
         d[i] = ol[i] * dx_dt;
      }

   b[n] = 0.0;
   c[n] = dif[n] / dx;
   a[n] = c[n] + dx_dt / ( 2.0 );
   d[n] = +hmi * ( funcoesClima.rovi - rov[n] ) / fluido.rol + dx_dt * ol[n] / ( 2.0 );

   if( d[1] < 0.0 or d[n] < 0.0 ) {					/// alteracao
         cout << "\a";								/// gera um beep
         ///       outtextxy(40,470,"Mestrado Engenharia Civil - Laborat¢rio SITERPA - Andre D. Bueno (P)");///
         ///       cout<<"Coeficiente d[1]="<<d[1]<<"   Coeficiente d[n]="<<d[n];
         ///       double dtnovo;
         ///       dtnovo=(+ol[1]*dx/2.0-(esp-espa))/(d[1]-hme*(funcoesClima.rove-rov[1])/fluido.rol);
         ///       cout<<"  dtnovo="<<dtnovo;
         ///       positividade_coeficientes=1;
      }
}


/// ---------------------------------------------------------------------------
/// Implementação Calcular_efeitos_chuva_ol
void CSimulador_Telha::Calcular_efeitos_chuva_ol() {
   olChuva = 0.0;
   /// for (i=1;i<=n;i++)/// sistema de freio baseado na media
   ///   ol[i]=(ol[i]+ola[i])/2;

	/// ---------------------------------------------------------------------------
	/// sistema que considera chuva constante durante um periodo
	/// horaInicioChuva, horaFimChuva, precipitacao=funçãochuva
	/// if(tempoDecorrido>horaInicioChuva and tempoDecorrido<horaFimChuva)
	/// {
	///   olChuva=+precipitacao*dta/(2592000*1000*larg);
	///   ol[1]=ol[1]+olChuva;      /// 30*24*60*60=2592000
	/// }
	/// converte precipitacao mm/mes para conteúdo

   /// início rotina considera espessura
}

/// ---------------------------------------------------------------------------
/// função classe CTelhaImpermeavel, função cálculo fti
/// baseado nos valores piqi do metodo implicito calcula t[i]
void CSimulador_Telha::Calcular_tp() {
  Calcular_aibicidi_tp();	/// valores de a[i],b[i],c[i],d[i]
  ResolverSistemaEquacoes_TDMA_piqi();			/// valores de p[i],q[i]
  
  tp[n] = q[n];			/// calcula valores atuais t
  for( int i = n; i > 1; i-- )
    tp[i - 1] = p[i - 1] * tp[i] + q[i - 1];

   /// ol[1] não representa só o conteúdo de umidade ponto 1
   /// mas também a espessura do filme de liquido

   if( ( ol[1] - ola[1] ) > 0.0 ) {			/// ganho umidade meio externo relacao tempo anterior
											/// ou aumentou ol[1] ou aumentou espessura
         if( ol[1] > porosidade ) {			/// aumentou espessura
               esp = esp + ( +ol[1] - porosidade ) * dx / 2.0;
               ol[1] = porosidade;

               if( esp > 0.0001 )			/// alteracao limite para filme de líquido
                  esp = 0.0001;
            }
      }
   else {									/// perda umidade para meio externo
         /// ou diminuiu ol[1] ou diminuiu espessura
         /// e se a espessura ficou <0 não temos mais filme de liquido
         /// e temos reducao ol[1]
         if( esp > 0.0 ) {
											/// se espa <0 apenas diminuiu ol[1]
											/// abaixo considera diminuicao espessura
               esp = esp + ( +ol[1] - ola[1] ) * dx / 2.0;
               ol[1] = porosidade;

               /// existe a nescessidade ainda de considerar que a perda de
               /// vapor eliminou o filme de liquido e diminuiu ol[1]
               if( esp < 0.0 ) {			/// se espessura calculada acima <0
                     ol[1] = ola[1] + esp * 2.0 / dx;	/// ola[1]=porosidade pois estava saturado
                     esp = 0.0;
                  }
            }
      }

   /// fim rotina cálculo espessura
   for( int i = 1; i <= n; i++ ) {
         if( ol[i] > porosidade )				/// limitacao ol[i] maior porosidade
            ol[i] = porosidade;

         if( ol[i] < 0.0 )
            ol[i] = 0.0;						/// limitacao ol[i] não negativo
      }
}

/*
/// ---------------------------------------------------------------------------
/// função classe CTelhaImpermeavel, função cálculo fti
/// baseado nos valores piqi do metodo implicito calcula t[i]
void CSimulador_Telha::Calcular_tp() {
  Calcular_aibicidi_tp();	/// valores de a[i],b[i],c[i],d[i]
  ResolverSistemaEquacoes_TDMA_piqi();			/// valores de p[i],q[i]
  
  tp[n] = q[n];			/// calcula valores atuais t
  for( int i = n; i > 1; i-- )
    tp[i - 1] = p[i - 1] * tp[i] + q[i - 1];
}*/

/// ---------------------------------------------------------------------------
/// Implementação função ftianbncndn
/// calcula os valores aibicidi do método implicito
void CSimulador_Telha::Calcular_aibicidi_tp() {
   double dx_dt;
   dx_dt = dx / dt;
   double temp;									/// pressãovapor1;usada para considerar a chuva.
   temp = ( rot * ( ct + fluido.cl * wl[1] ) * dx / 2.0 + espa * fluido.cl * fluido.rol ) / dt;
   b[1] = k[1 + 1] / dx;
   c[1] = 0.0;
   a[1] = +hce + b[1] + temp;
   d[1] = +alfa * funcoesClima.radoc + emis * funcoesClima.radol + hce * funcoesClima.text 
			 + fluido.lv * hme * ( funcoesClima.rove - rov[1] ) 
			 + fluido.lv * ( esp - espa ) + temp * tp[1];
///    pressãovapor1=CTermodinamica::ConcentracaoVapor( Umidade_telha(Wl(ol[1]-olChuva),t[1]) ,t[1]);
///    d[1]=+alfa*funcoesClima.radoc+emis*funcoesClima.radol+hce*funcoesClima.text+fluido.lv*hme*(funcoesClima.rove-pressãovapor1)+temp*t[1];
   /// nas trocas de calor latente para o ponto exterior deve-se considerar
   /// somente olvapor diminuindo olChuva de ol[1].
   /// por enquanto a temperatura da chuva 'e considerada igual a da telha
   /// de forma que o conteúdo de liquido ganho com a chuva entra diretamente
   /// como conteúdo de umidade no cálculo da capacidade térmica global.

   /// a agua ganha com a chuva  entrou como ganho de energia latente
   /// devemos diminuir de d[1] a troca de calor latente somada com a chuva
///  if(tempoDecorrido>horaInicioChuva and tempoDecorrido<horaFimChuva)
///    d[1]=d[1]-fluido.lv*hme*(funcoesClima.rove-CTermodinamica::ConcentracaoVapor( Umidade_telha(Wl(olChuva),t[1]) ,t[1]) );
   ///   wlchuva=Wl(olChuva);
   ///   hchuva=Umidade_telha(wlchuva,t[1]);         todos embutidos acima
   ///   rovchuva=CTermodinamica::ConcentracaoVapor(hchuva,t[1]);

   for( int i = 2; i < n; i++ ) {
         temp = ( ct + fluido.cl * wl[i] ) * rot * dx_dt;	/// alteração
         b[i] = k[i + 1] / dx;
         c[i] = k[i] / dx;
         a[i] = c[i] + b[i] + temp;
         d[i] = temp * tp[i];
      }

   b[n] = 0.0;
   c[n] = k[n] / dx;
   temp = ( ct + fluido.cl * wl[n] ) * rot * dx_dt;
   a[n] = +hci + c[n] + temp / ( 2.0 );
   d[n] = +fluido.lv * hmi * ( funcoesClima.rovi - rov[n] ) + hci * funcoesClima.tint + temp * tp[n] / ( 2.0 );
}				/// fim da função

/// Mostra na tela resultados da simulação a cada passo.
void CSimulador_Telha::SaidaTela() {
   cout.precision(3);
   cout << "\n_______________________________________________________________________________\n";
   cout << "   |hora=" 	<< setw(6)	<< tempo;	/// tempo hora decimal  alteracao
// cout<<" "<<tint;             				/// temperatura interna
   cout << " |text=" 	<< setw(6)	<< funcoesClima.text;	/// temperatura externa
   cout << " |radoc=" 	<< setw(6)	<< funcoesClima.radoc;	/// radiação onda curta
   cout << " |tint=" 	<< setw(6)	<< funcoesClima.tint;	/// temperatura interna
// cout<<" "<<rove;          					/// concentração vapor externo
// cout<<" "<<rovi;          					/// concentração vapor interno
// cout<<" "<<hm;               				/// umidade média
// cout<<" "<<esp;/// tmi;   /// <<km;			/// condutividade térmica média
   for( int i = 1; i <= n; i++ ) {
      cout 	<< "\n" 	<< setw(3) 	<< i 		<< "|ti= " << setw(8) << ti[i]
			<< "|ol= " 	<< setw(8) << ol[i] 	<< "|tp= " << setw(8) << tp[i];
      }
   cout << "\n   |tim=" << setw(8) << tim;		/// temperatura média telha impermeável
   cout << "|olm=" 		<< setw(8) << olm;				/// conteúdo volumetrico medio
   cout << "|tpm=" 	<< setw(8) << tpm;			/// temperatura média telha permeável

}

/// Mostra gráficos do CGnuplot
void CSimulador_Telha::SaidaGrafica(){
   // Saída gráfica, adicionando dados nos vetores.
   vhora.push_back( tempoDecorrido );
   ol0.push_back( ol[1] );
   oln_1.push_back( ol[nodos] );
   tp0.push_back( tp[1] );
   tpn_1.push_back( tp[nodos] );
   ti0.push_back( ti[1] );
   tin_1.push_back( ti[nodos] );
/*
   static vector<double> vx(2);
   static vector<double> vy(2);
   vx[0] = tempoDecorrido - dt;
   vx[1] = tempoDecorrido;
   vy[0] = ola[1];
   vy[1] = ol[1];
   grafico_ol.PlotVector( vx, vy ," ol0" );
   vy[0] = ola[nodos];
   vy[1] = ol[nodos];
   grafico_ol.PlotVector( vhora, oln_1 ," oln_1");
   vy[0] = tpa[1];
   vy[1] = tp[1];
   grafico_tp.PlotVector( vhora, tp0 ," tp0");
   vy[0] = tpa[nodos];
   vy[1] = tp[nodos];
   grafico_tp.PlotVector( vhora, tpn_1 ," tpn_1");
   vy[0] = tia[1];
   vy[1] = ti[1];
   grafico_ti.PlotVector( vhora, ti0 ," ti0");
   vy[0] = tia[nodos];
   vy[1] = ti[nodos];
   grafico_ti.PlotVector( vhora, tin_1 ," tin_1");
*/
//    if( ol0.size() == 20 ) {
// 	grafico_ol.PlotVector( vhora, ol0 ," ol0" );
// 	grafico_ol.PlotVector( vhora, oln_1 ," oln_1");
// 	grafico_tp.PlotVector( vhora, tp0 ," tp0");
// 	grafico_tp.PlotVector( vhora, tpn_1 ," tpn_1");
// 	grafico_ti.PlotVector( vhora, ti0 ," ti0");
// 	grafico_ti.PlotVector( vhora, tin_1 ," tin_1");
//    }
//    else if( ol0.size() > 20 ) {
// 	system ("sleep 0.02");
// 	grafico_ol.Replot();
// 	grafico_tp.Replot();
// 	grafico_ti.Replot();
//    }
	
}

std::ostream& operator<<(std::ostream& os, CSimulador_Telha& obj) {
	os 	<< "\n==> Objeto CSimulador_Telha:"
		<< "\n==> Objeto CSimulador_Telha -> Herdados";
		//	os	<< static_cast<CMeioPoroso_Telha_Discretizada_TDMA> (obj);
	CMeioPoroso_Telha_Discretizada_TDMA meioPoroso = obj;
	os << meioPoroso;
		// 	os	<< static_cast<CTransferenciaCalorMassa> (obj);
	CTransferenciaCalorMassa tc = obj;
	os << tc;
		// 	os	<< static_cast<CSolver_TDMA> (obj);
	os	<< "\n==> Objeto CSimulador_Telha -> Agregados:"
		<< obj.funcoesClima
		<< obj.fluido;
	  //<< obj.funcaoConteudoMassicoWl
	os	<< "\ndt = " 		<< obj.dt
    	<< "\ndta = " 		<< obj.dta
    	<< "\ndtmax = " 	<< obj.dtmax
    	<< "\ndtmin = " 	<< obj.dtmin
    	<< "\ntempo = " 	<< obj.tempo
    	<< "\nrecorrencia = " 	<< obj.recorrencia
//     	<< "\ntempoInicioSimulacao = " 	<< obj.tempoInicioSimulacao
    	<< "\ntempoDecorrido = " 	<< obj.tempoDecorrido;
//     	<< "\ntempoFimSimulacao = " 	<< obj.tempoFimSimulacao
}

