/// -------------------  Bibliotecas --------------------------------
#include <cassert>
#include <fstream>			/// por causa ifstream e ofstream ponteiros arquivos
#include <iostream>			/// por causa rotinas entrada saída
#include <iomanip>			/// manipuladores, como setw()
#include <cmath>			/// por causa funções matemáticas

#include "CInterface.h"
#include "CFuncaoAdsorcao_Celso.h"
#include "CFuncaoAdsorcao_Pablo.h"
#include "CMeioPoroso_Telha.h"
using namespace std;

/// ---------------------------------------------------------------------------
/// Implementação função DadosDefault() 
/// inicia os dados físicos da classe CMeioPoroso_Telha, os com valores default.
void CMeioPoroso_Telha::DadosDefault( ) {
	 if( funcaoAdsorcao )
		 funcaoAdsorcao.reset();
	 switch ( tipo_material )
	 {
		 case 'P' :
		 case 'p' : funcaoAdsorcao = shared_ptr<CFuncaoAdsorcao_Pablo> (new CFuncaoAdsorcao_Pablo);
		 break;
		 case 'C' :
		 case 'c' : funcaoAdsorcao = shared_ptr<CFuncaoAdsorcao_Celso> (new CFuncaoAdsorcao_Celso);
		 break;
		 case 'A' :
		 case 'a' :
		 default:
					funcaoAdsorcao = shared_ptr<CFuncaoAdsorcao> (new CFuncaoAdsorcao);
		 break;
	 }
  assert( funcaoAdsorcao );
  funcaoDifusividade.DadosDefault();
  funcaoCondutividade.DadosDefault();
  funcaoAdsorcao->DadosDefault();

  if( tipo_material == 'c' or tipo_material == 'C' ) {
    rot = 1730;        /// 2070.0;
    ct = 1000.0;
    porosidade = 0.31;
    }
  else if( tipo_material == 'p' or tipo_material == 'P' ) {
    rot = 1710;
    ct = 1000.0;
    porosidade = 0.31;
    }
  else if( tipo_material != 'c' and tipo_material != 'C' and tipo_material != 'p' and tipo_material != 'P' ) {
    rot = 1875;      /// 2070.0;
    ct = 920.0;
    porosidade = 0.33098;
    }

  alfa = 0.63;
  emis =1.0;
  larg = 0.03;
  wli = wl_inicial;
  ki = funcaoCondutividade( wli );
}

/// ---------------------------------------------------------------------------
/// Implementação função leitura dos dados EntrarDadosObjeto
/// permite a entrada, pelo teclado, das variáveis básicas da telha.
void CMeioPoroso_Telha::EntrarDadosObjeto() {
	CInterface::Carimbo();
	cout << *this;
   char resp;
   cout << "\n\nUsar funcaoDifusividade, funcaoCondutividade, funcaoAdsorcao default (d) ou novos (n): ";
   cin.get( resp );
   cin.get();
   if( resp == 'n' or resp == 'N' ) {
	funcaoDifusividade.EntrarDadosFuncao();
	funcaoCondutividade.EntrarDadosFuncao();
	funcaoAdsorcao->EntrarDadosFuncao();
   }
   // Abaixo repete apresentação atributos na tela.
   cout	<< "\n==> Objeto CMeioPoroso_Telha -> Atributos:"
		<< "\ntipo_material = " 	<< tipo_material
		<< "\nrot = " 				<< rot
		<< "\nct = " 				<< ct
		<< "\nporosidade = " 		<< porosidade
		<< "\nalfa = " 				<< alfa
		<< "\nemis = " 				<< emis
		<< "\nlarg = " 				<< larg
		<< "\nwli = " 				<< wli
		<< "\nki = " 				<< ki;
   cout << "\nUsar rot, ct, porosidade, alfa, emis, larg, wli, ki, default (d) ou novos (n): ";
   cin.get( resp );
   cin.get();

   if( resp == 'n' or resp == 'N' ) {
		cout << "\nInforme o tipo_material ('C'= argamassa Celso; 'P' = argamassa Pablo; 'A' = cerâmica Bueno): ";
		cin >> tipo_material;
		cout << "\ndensidade da telha (Celso rot = 1730; Pablo rot = 1710; Bueno rot = 1875;)\nrot = "; 
		cin >> rot;
		cout << "\ncalor específico da telha (Celso ct = 1000.0; Pablo ct = 1000.0; Bueno ct = 920.0;)\nct = ";
		cin >> ct;
		cout << "\nporosidade da telha (Celso porosidade = 0.31; Pablo porosidade = 0.31; "
		     << "Bueno porosidade = 0.33098),\nporosidade = ";
		cin >> porosidade;
		cout << "\nCoeficiente de absorção a radiação solar,\nalfa = ";
		cin >> alfa;
		/// cout << "\nalfa (0.6) para telha sem adsorcao: ";
		/// cin >> alfai;
		cout << "\nCoeficiente de emissividade,\nemis = ";
		cin >> emis;
		cout << "\nLargura da telha,\nlarg = ";
		cin >> larg;
        cin.get();  /// pega o retorno de carro -> enter!

		cout << "\nEntrada dados associados a telha impermeável";
		cout << "\nEntre com o novo valor do conteúdo de massa mássico da telha impermeável, wli = ";
		cin >> wli;
		cin.get();
		ki = funcaoCondutividade( wli );	/// calcula ki em função wli
		cout << "Valor ki = funcaoCondutividade(" << wli << ") = "<< ki;
  }
}

/// Saída de dados do objeto para os (tela)
std::ostream& operator<<(std::ostream& os, CMeioPoroso_Telha& obj) {
  os 	<< "\n==> Objeto CMeioPoroso_Telha:"
		<< "\n==> Objeto CMeioPoroso_Telha -> Agregados:"
		<< obj.funcaoDifusividade
		<< obj.funcaoCondutividade
 		<< *(obj.funcaoAdsorcao)
		<< "\n==> Objeto CMeioPoroso_Telha -> Atributos:"
		<< "\ntipo_material = " 	<< obj.tipo_material
		<< "\nrot = " 				<< obj.rot
		<< "\nct = " 				<< obj.ct
		<< "\nporosidade = " 		<< obj.porosidade
		<< "\nalfa = " 				<< obj.alfa
		<< "\nemis = " 				<< obj.emis
		<< "\nlarg = " 				<< obj.larg
		<< "\nwli = " 				<< obj.wli
		<< "\nki = " 				<< obj.ki;
}
