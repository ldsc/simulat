
add_executable(Simulat-SimuladorTelhaMestrado-v4 
CTermodinamica.cpp
CFuncaoCondutividade.cpp
CFuncaoDifusividade.cpp
CFuncaoAdsorcao.cpp
CFuncaoAdsorcao_Celso.cpp
CFuncaoAdsorcao_Pablo.cpp
CFuncoesClima.cpp
CFluido.cpp
CMeioPoroso_Telha.cpp
CSolver_TDMA.cpp
CMeioPoroso_Telha_Discretizada_TDMA.cpp
CTransferenciaCalorMassa.cpp
CFuncaoConteudoMassicoWl.cpp
CSimulador_Telha.cpp
CSimulador_Telha_GanhosEnergia.cpp
CInterface_SimuladorTelha.cpp
CGnuplot.cpp
main.cpp
)

install(TARGETS Simulat-SimuladorTelhaMestrado-v4 RUNTIME DESTINATION bin)

