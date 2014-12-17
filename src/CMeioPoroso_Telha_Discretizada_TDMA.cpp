
/// -------------------  Bibliotecas --------------------------------
//#include <cassert>
//#include <fstream>			/// por causa ifstream e ofstream ponteiros arquivos
#include <iostream>			/// por causa rotinas entrada saída
//#include <iomanip>			/// manipuladores, como setw()
//#include <cmath>			/// por causa funções matemáticas

#include "CInterface.h"
#include "CMeioPoroso_Telha_Discretizada_TDMA.h"
using namespace std;

/// ---------------------------------------------------------------------------
/// ************  Implementação funções classe CMeioPoroso_Telha_Discretizada_TDMA   *********
/// ---------------------------------------------------------------------------
/// Implementação dados default classe CMeioPoroso_Telha_Discretizada_TDMA
void CMeioPoroso_Telha_Discretizada_TDMA::DadosDefault() {

   CMeioPoroso_Telha::DadosDefault();

   //n = nodos ;
   for( int i = 0; i <= n; i++ ) 							// aqui, trocar por < n
      dif[i] = k[i] = wl[i] = h[i] = rov[i] = 0.0;			/// pvs[i]=0;

   esp = espa = espaa = 0.0;
   /// perdaenergiachuva=0;

   for( int  i = 0; i <= n; i++ ) {
      ol[i] = ola[i] = olaa[i] = ol_inicial;				/// ol=wl*rot/rol
// 	  a[i] = b[i] = c[i] = d[i] = p[i] = q[i] = 0.00;
      /// aa[i]=bb[i]=cc[i]=dd[i]=pp[i]=qq[i]=0.00;
      tp[i] = tpa[i] = tpaa[i] = tp_inicial;				/// 24.75
	  ti[i] = tia[i] = tiaa[i] = ti_inicial;				/// 22.04
      }
   /// Telha impermeável
   for( int i = 0; i <= n; i++ )
      ti[i] = tia[i] = tiaa[i] = ti_inicial;

  dx = larg / ( double ) n;
  //m = 0.0; //?
  olChuva = 0.0;
}

/// ---------------------------------------------------------------------------
/// Implementação função fdadosti
/// entrada de dados para classe CTelhaImpermeaveli valores de ti[i] para tempo inicial
void CMeioPoroso_Telha_Discretizada_TDMA::EntrarDadosObjeto() {
  // Chamando EntrarDadosObjeto() dos objetos herdados!
  CMeioPoroso_Telha::EntrarDadosObjeto();

  CInterface::Carimbo();
  cout << *this;

  //------------------------
   cout << "\nEntrada dados associados a telha permeável (temperaturas)";
   cout << "\nUsar temperaturas default(" << tp_inicial << ") (d) ou novas temperaturas t[i] (n): ";
   char resp;
   cin.get( resp );
   cin.get();
   if( resp == 'n' or resp == 'N' )
      for( int i = 1; i <= n; i++ ) {
            cout << "\nEntre com o valor de tp[" << i << "] no instante inicial: ";
            cin >> tp[i];
            cin.get();
            tpaa[i] = tpa[i] = tp[i];
         }
  //------------------------
   cout << "\nEntrada dados associados a telha permeável (conteúdos mássicos)";
   cout << "\nUsar conteúdos volumétricos (ol = " << ol_inicial << ") e (espessura ="
		<< esp << " default(d) ou novos (n) ou saturados(s): ";
   cin.get( resp );
   cin.get();

   if( resp == 'n' or resp == 'N' ) {
         for( int i = 1; i <= n; i++ ) {
               cout << "\nEntre com o valor de ol[" << i << "] no instante inicial ("<< ol_inicial << "): ";
               cin >> ol[i];
               cin.get();
               olaa[i] = ola[i] = ol[i];
            }

         cout <<"\nEntre com o valor da espessura filme condensado instante inicial [m] (0): ";
         cin >> esp;
         cin.get();
         espaa = espa = esp;
      }
   else
      if( resp == 's' or resp == 'S' ) {
            for( int i = 1; i <= n; i++ )
               olaa[i] = ola[i] = ol[i] = porosidade;

            cout << "\nTodos os valores de ol[i] = " << porosidade;
            cout <<"\nEntre com o valor da espessura filme condensado instante inicial (0): ";
            cin >> esp;
            cin.get();
            espaa = espa = esp;
         }
  //------------------------
   cout << "\nEntrada dados associados a telha impermeável";
   cout << "\nUsar ti[i] inicial default (" << ti_inicial <<      ") (d) ou novos valores (n): ";
   cin.get( resp );
   cin.get();
   if( resp == 'n' or resp == 'N' )
      for( int i = 1; i <= n; i++ ) {
            cout << "\nEntre com o valor de ti[" << i << "] no instante inicial: ";
            cin >> ti[i];
            cin.get();
            tiaa[i] = tia[i] = ti[i];
         }
}

/// Saída de dados do objeto para os (tela)
std::ostream& operator<<(std::ostream& os, CMeioPoroso_Telha_Discretizada_TDMA& obj) {
	os 	<< "\n==> Objeto CMeioPoroso_Telha_Discretizada_TDMA:\n"
		<< "\n==> Objeto CMeioPoroso_Telha_Discretizada_TDMA -> Herdados:";
		//((CMeioPoroso_Telha*)this)->CMeioPoroso_Telha::funcaoAdsorcao
	CMeioPoroso_Telha mp = obj; // trocar
	os << mp;
//	os << const_cast<CMeioPoroso_Telha> (&obj);
//  os	<< static_cast<CMeioPoroso_Telha>(obj);
	os	<< "\n==> Objeto CMeioPoroso_Telha_Discretizada_TDMA -> Atributos:"
		<< "\nesp = " 		<< obj.esp
		<< "\nespa = " 		<< obj.espa
		<< "\nespaa = " 	<< obj.espaa
		<< "\ndx = " 		<< obj.dx
		<< "\nolChuva = " 	<< obj.olChuva
    	//<< "\nm = " 		<< obj.m //m
    	<< "\nn (nodos) = " << obj.n;
		
  for( int i = 0; i <= obj.n ; i++ )
	os	<< "\ni=" 		<< i
		<< " dif=" 		<< obj.dif[i]
		<< " k=" 		<< obj.k[i]
		<< " wl=" 		<< obj.wl[i]
		<< " h=" 		<< obj.h[i]
		<< " rov=" 		<< obj.rov[i]
		<< " ol=" 		<< obj.ol[i]
		<< " tp=" 		<< obj.tp[i]
	  // Propriedades telha impermeável
		<< " ti=" 		<< obj.ti[i];
// 		<< " ola=" 		<< obj.ola[i]
// 		<< " tpa=" 		<< obj.tpa[i]
// 		<< " tia=" 		<< obj.tia[i]
// 		<< " olaa=" 	<< obj.olaa[i]
// 		<< " tpaa=" 	<< obj.tpaa[i]
// 		<< " tiaa=" 	<< obj.tiaa[i];
}
