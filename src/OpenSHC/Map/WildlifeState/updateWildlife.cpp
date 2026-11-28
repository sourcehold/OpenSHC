#include "../../Map.func.hpp"

#include "OpenSHC/Map/WildlifeState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {

    using Game::GameMode;

    // FUNCTION: STRONGHOLDCRUSADER 0x0052DF30
    void WildlifeState::updateWildlife()
    {
        WildlifeGridElement* piVar1;
        WildlifeGridElement* piVar2;
        int iVar3;
        WildlifeGridElement* piVar4;
        WildlifeGridElement* piVar5;
        int iVar6;
        int iVar7;
        if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
            piVar1 = &this->grid[0][0];
            iVar3 = 0x28;
            piVar5 = piVar1;
            iVar6 = iVar3;
            while (true) {
                do {
                    piVar5->field13_0x34 = 0;
                    piVar5->field20_0x50 = 0;
                    piVar5->field24_0x60 = 0;
                    piVar5->field25_0x64 = 0;
                    piVar5->field28_0x70 = piVar5->field28_0x70 / 100;
                    if (piVar5->chimps) {
                        if (piVar5->keeps) {
                            piVar5->field24_0x60 = 1;
                        }
                        if (piVar5->castlebuildings) {
                            piVar5->field24_0x60 = piVar5->field24_0x60 + 1;
                        }
                    }
                    piVar5 = piVar5 + 0x640;
                    iVar6 = iVar6 + -1;
                } while (iVar6);
                piVar1 = piVar1 + 0x28;
                iVar3 = iVar3 + -1;
                if (!iVar3)
                    break;
                iVar6 = 0x28;
                piVar5 = piVar1;
            }
            piVar4 = &this->grid[0][0];
            iVar3 = 0;
            do {
                iVar6 = 0;
                piVar2 = piVar4;
                do {
                    if (!piVar2->unstalkedUnitCount) {
                        if (piVar2->buildingTiles) {
                            iVar7 = 2;
                            goto LAB_0052dfdf;
                        }
                        if (piVar2->lionCount) {
                            iVar7 = 3;
                            goto LAB_0052dfdf;
                        }
                    } else {
                        iVar7 = 2;
                    LAB_0052dfdf:
                        MACRO_CALL_MEMBER(Map::WildlifeState_Func::floodFillField13FromCell, this)(
                            iVar6, iVar3, iVar7);
                    }
                    if (piVar2->farmFieldTiles) {
                        MACRO_CALL_MEMBER(Map::WildlifeState_Func::floodFillField20FromCell, this)(
                            iVar6, iVar3, 6);
                    }
                    iVar6 = iVar6 + 1;
                    piVar2 = piVar2 + 0x640;
                } while (iVar6 < 0x28);
                iVar3 = iVar3 + 1;
                piVar4 = piVar4 + 0x28;
            } while (iVar3 < 0x28);
        }
    }

}
}
