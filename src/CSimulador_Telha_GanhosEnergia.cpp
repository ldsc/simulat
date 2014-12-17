
/// -------------------  Bibliotecas --------------------------------
#include <cassert>
#include <fstream>			/// por causa ifstream e ofstream ponteiros arquivos
#include <iostream>			/// por causa rotinas entrada saída
#include <iomanip>			/// manipuladores, como setw()
#include <cmath>			/// por causa funções matemáticas

#include "CSimulador_Telha_GanhosEnergia.h"
using namespace std;


/// Dados default
void CSimulador_Telha_GanhosEnergia::DadosDefault() {
	CSimulador_Telha::DadosDefault();
	gev = giv = gesp = gec = gic = gecl = gicl = geroc = gerol = gir = bm = be = 0.00;
	geci = gici = geroci = geroli = giri = 0.0;
}

/// ---------------------------------------------------------------------------
/// Implementação função fganhos();
/// função que calcula os ganhos de massa e energia para os pontos extremos.
void CSimulador_Telha_GanhosEnergia::CalcularGanhosEnergia_tp() {
   /// gesp=;    /// ganho com variação espessura
   gecl = fluido.lv * hme * ( funcoesClima.rove - rov[1] ) + fluido.lv * ( esp - espa );	/// ganho externo calor latente
   gicl = fluido.lv * hmi * ( funcoesClima.rovi - rov[n] );		/// ganho interno calor latente
   gec = hce * ( funcoesClima.text - tp[1] );					/// ganho externo convecção
   gic = hci * ( funcoesClima.tint - tp[n] );					/// ganho interno convecção
   geroc = alfa * funcoesClima.radoc;							/// ganho externo radiação onda curta
   gerol = emis * funcoesClima.radol;							/// ganho externo radiação onda longa
   gir = 0;														/// ganho interno radicao
   /// bm=   ;  												/// balanco massa
   /// be=   ;   												/// balanco energia
}

/// ---------------------------------------------------------------------------
/// cálculo energia  para telha sem adsorção
void CSimulador_Telha_GanhosEnergia::CalcularGanhosEnergia_ti() {
   geci = hce * ( funcoesClima.text - ti[1] );				/// ganho externo convecção
   gici = hci * ( funcoesClima.tint - ti[n] );				/// ganho interno convecção
   geroci = alfa * funcoesClima.radoc;						/// ganho externo radiação onda curta
   geroli = emis * funcoesClima.radol;						/// ganho externo radiação onda longa
   giri = 0;												/// ganho interno radicao
}

// /// Mostra na tela resultados da simulação a cada passo.
// void CSimulador_Telha_GanhosEnergia::SaidaTela() {
//    cout << "\n";
//    cout << "|t=" 		<< tempo;				/// tempo hora decimal  alteracao
// // cout<<" "<<tint;             				/// temperatura interna
//    cout << "\ttext=" 	<< funcoesClima.text;	/// temperatura externa
//    cout << "\tradoc=" 	<< funcoesClima.radoc;	/// radiação onda curta
// //  cout<<" "<<rove;          		/// concentração vapor externo
// //  cout<<" "<<rovi;          		/// concentração vapor interno
// //  cout<<" "<<hm;               	/// umidade média
// // cout<<" "<<esp;/// tmi;   /// <<km;/// condutividade térmica média
// //    for( int i = 1; i <= n; i++ ) {
// //       cout << "\nti["<< i <<"]="<< ti[i];
// //       cout << "\nol["<< i <<"]="<< ol[i];
// //       cout << "\ntp["<< i <<"]="<< tp[i];
// //       }
//    cout << "\tolm=" << olm;			/// conteúdo volumetrico medio
//    cout << "\ttpm=" << tpm;			/// temperatura média telha permeável
//    cout << "\ttim=" << tim;			/// temperatura média telha impermeável
// // cout<<"|";
// }

std::ostream& operator<<(std::ostream& os, CSimulador_Telha_GanhosEnergia&  obj) {
  os 	<< "\n==> Objeto CSimulador_Telha_GanhosEnergia:"
		<< "\n==> Objeto CSimulador_Telha_GanhosEnergia-> Herdados";
//   os	<< static_cast<CSimulador_Telha > (obj);
	CSimulador_Telha st = obj;
	os << st;

  os  	<< "\nwlm = " 	<< obj.wlm
    	<< "\nhm = " 	<< obj.hm
    	<< "\nkm = " 	<< obj.km
    	<< "\nolm = " 	<< obj.olm
    	<< "\ntpm = " 	<< obj.tpm
    	<< "\ntim = " 	<< obj.tim
    	<< "\ngev = " 	<< obj.gev
    	<< "\ngiv = " 	<< obj.giv
    	<< "\ngesp = " 	<< obj.gesp
    	<< "\ngec = " 	<< obj.gec
    	<< "\ngic = " 	<< obj.gic
    	<< "\ngecl = " 	<< obj.gecl
    	<< "\ngicl = " 	<< obj.gicl
    	<< "\ngeroc = " << obj.geroc
    	<< "\ngerol = " << obj.gerol
    	<< "\ngir = " 	<< obj.gir
    	<< "\nbm = " 	<< obj.bm
    	<< "\nbe = " 	<< obj.be
    	<< "\ngeci = " 	<< obj.geci
    	<< "\ngici = " 	<< obj.gici
    	<< "\ngeroci = "<< obj.geroci
    	<< "\ngeroli = "<< obj.geroli
    	<< "\ngiri = " 	<< obj.giri;
}
