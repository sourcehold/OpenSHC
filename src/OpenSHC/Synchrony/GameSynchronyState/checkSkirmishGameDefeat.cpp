#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Game/Player/PlayerData.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Commands::MappersEnum;
    using Game::GameMode;
    using Game::GameMode2;
    using UI::Enums::BuildingsAndStatusMenuTabType;
    using UI::Enums::DisplayElementID;
    using UI::Enums::MenuViewType;
    using WindowsHelper::Enums::BOOLEnum;
    using Game::Player::PlayerData;

    // FUNCTION: STRONGHOLDCRUSADER 0x00486600
    void GameSynchronyState::checkSkirmishGameDefeat()
    {
        bool bVar1;
        short sVar2;
        PlayerData* psVar3;
        int* piVar3;
        int* piVar4;
        int iVar4;
        int* piVar5;
        int _deadPlayerID;
        int iVar5;
        int* piVar6;
        int iVar7;
        int iVar8;
        short* psVar9;
        int iVar10;
        int* local_68;
        int iStack_48;
        int local_44[17];
        if (this->currentGameMode != Game::GM_SOLITARY) {
            _deadPlayerID = 1;
            psVar9 = &DAT_GameState::instance.playerDataArray[1].commemorationShrinePlacementCountdown;
            do {
                if ((0 < *psVar9) && (sVar2 = *psVar9 + -1, *psVar9 = sVar2, !sVar2)) {
                    MACRO_CALL_MEMBER(
                        Map::Navigation::PathFindingState_Func::placeCommemoratingStatueAtGoodLocation,
                        DAT_PathFindingState::ptr)(_deadPlayerID);
                }
                psVar9 = psVar9 + 0x1cfa;
                _deadPlayerID = _deadPlayerID + 1;
            } while ((int)psVar9 < 0x1180150);
            if ((DAT_GameCore::instance.gameMode_2 != Game::GM_CAMPAIGN_MISSION)
                && (!DAT_GameState::instance.mapAndTime.gameOver)) {
                if (DAT_GameCore::instance.unknownAlwaysZero) {
                    DAT_GameCore::instance.unknownAlwaysZero = 0;
                    piVar3 = &DAT_GameState::instance.playerDataArray[1].playerDeathRelated;
                    psVar3 = (Game::Player::PlayerData *)(&DAT_GameState::instance.mapAndTime.playerIsAlive + 1);
                    do {
                        psVar3->commemorationShrinePlacementCountdown = 0;
                        *piVar3 = 1;
                        psVar3 = (Game::Player::PlayerData *)(&psVar3->someKeepRelatedX2);
                        piVar3 = piVar3 + 0xe7d;
                    } while ((int)psVar3 < 0x117ef52);
                    DAT_GameState::instance.mapAndTime.gameOver = TRUE;
                    DAT_GameState::instance.mapAndTime.gameOverTime = timeGetTime();
                    DAT_GameState::instance.mapAndTime.playerIsAlive[this->currentPlayerSlotID] = 1;
                    DAT_GameCore::instance.skipStoreSKMasters = 0;
                    MACRO_CALL(UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(UI::Enums::DEID_WIN_DEFEAT_WINDOW, 1);
                }
                piVar3 = this->currentAIArray + 1;
                local_44[2] = 0;
                local_44[1] = 0;
                local_44[4] = 0;
                local_44[3] = 0;
                local_44[6] = 0;
                local_44[5] = 0;
                local_44[8] = 0;
                local_44[7] = 0;
                local_44[10] = 0;
                local_44[9] = 0;
                local_44[0xc] = 0;
                local_44[0xb] = 0;
                local_44[0xe] = 0;
                local_44[0xd] = 0;
                local_44[0x10] = 0;
                local_44[0xf] = 0;
                piVar5 = &DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID;
                local_68 = this->currentAIArray + 1;
                do {
                    if ((piVar3[-0x1b] != -1) || (*piVar3 != 0)) {
                        iVar7 = piVar3[-0x1e824d];
                        (&iStack_48)[iVar7 * 2] = (&iStack_48)[iVar7 * 2] + 1;
                        if (piVar5[-0xe7d] != 0) {
                            local_44[iVar7 * 2] = local_44[iVar7 * 2] + 1;
                        }
                    }
                    if ((piVar3[-0x1a] != -1) || (piVar3[1] != 0)) {
                        iVar7 = piVar3[-0x1e824c];
                        (&iStack_48)[iVar7 * 2] = (&iStack_48)[iVar7 * 2] + 1;
                        if (*piVar5 != 0) {
                            local_44[iVar7 * 2] = local_44[iVar7 * 2] + 1;
                        }
                    }
                    if ((piVar3[-0x19] != -1) || (piVar3[2] != 0)) {
                        iVar7 = piVar3[-0x1e824b];
                        (&iStack_48)[iVar7 * 2] = (&iStack_48)[iVar7 * 2] + 1;
                        if (piVar5[0xe7d] != 0) {
                            local_44[iVar7 * 2] = local_44[iVar7 * 2] + 1;
                        }
                    }
                    if ((piVar3[-0x18] != -1) || (piVar3[3] != 0)) {
                        iVar7 = piVar3[-0x1e824a];
                        (&iStack_48)[iVar7 * 2] = (&iStack_48)[iVar7 * 2] + 1;
                        if (piVar5[0x1cfa] != 0) {
                            local_44[iVar7 * 2] = local_44[iVar7 * 2] + 1;
                        }
                    }
                    piVar5 = piVar5 + 0x39f4;
                    piVar3 = piVar3 + 4;
                } while ((int)piVar5 < 0x1182390);
                iVar7 = 0;
                piVar3 = local_44 + 1;
                iVar5 = 0;
                iVar10 = 0;
                iVar4 = 3;
                do {
                    iVar8 = iVar7;
                    if (*piVar3 != 0) {
                        iVar10 = iVar10 + 1;
                        if (piVar3[1] == *piVar3) {
                            iVar5 = iVar5 + 1;
                        } else {
                            iVar8 = iVar4 + -2;
                        }
                    }
                    if (piVar3[2] != 0) {
                        iVar10 = iVar10 + 1;
                        if (piVar3[3] == piVar3[2]) {
                            iVar5 = iVar5 + 1;
                        } else {
                            iVar8 = iVar4 + -1;
                        }
                    }
                    iVar7 = iVar8;
                    if ((piVar3[4] != 0) && (iVar10 = iVar10 + 1, iVar7 = iVar4, piVar3[5] == piVar3[4])) {
                        iVar5 = iVar5 + 1;
                        iVar7 = iVar8;
                    }
                    if (piVar3[6] != 0) {
                        iVar10 = iVar10 + 1;
                        if (piVar3[7] == piVar3[6]) {
                            iVar5 = iVar5 + 1;
                        } else {
                            iVar7 = iVar4 + 1;
                        }
                    }
                    iVar8 = iVar4 + 2;
                    piVar3 = piVar3 + 8;
                    iVar4 = iVar4 + 4;
                } while (iVar8 < 9);
                local_44[0] = 0;
                local_44[1] = 0;
                local_44[2] = 0;
                local_44[3] = 0;
                local_44[4] = 0;
                local_44[5] = 0;
                local_44[6] = 0;
                local_44[7] = 0;
                if (iVar5 < iVar10 + -1) {
                    if (!DAT_GameCore::instance.mapU4Int0) {}
                    piVar4 = &DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID;
                    bVar1 = false;
                    piVar3 = local_68;
                    do {
                        if (((piVar3[-0x1b] != -1) || (*piVar3 != 0)) && (piVar4[-0xe7d] == 0)) {
                            iVar7 = piVar3[-0x1e824d];
                            bVar1 = true;
                        }
                        if (((piVar3[-0x1a] != -1) || (piVar3[1] != 0)) && (*piVar4 == 0)) {
                            iVar7 = piVar3[-0x1e824c];
                            bVar1 = true;
                        }
                        if (((piVar3[-0x19] != -1) || (piVar3[2] != 0)) && (piVar4[0xe7d] == 0)) {
                            iVar7 = piVar3[-0x1e824b];
                            bVar1 = true;
                        }
                        if (((piVar3[-0x18] != -1) || (piVar3[3] != 0)) && (piVar4[0x1cfa] == 0)) {
                            iVar7 = piVar3[-0x1e824a];
                            bVar1 = true;
                        }
                        piVar4 = piVar4 + 0x39f4;
                        piVar3 = piVar3 + 4;
                    } while ((int)piVar4 < 0x118241c);
                    if (!bVar1) {}
                } else {
                    DAT_GameCore::instance.unknownAlwaysZero = 0;
                }
                iVar4 = 1;
                piVar3 = local_68;
                do {
                    if (((piVar3[-0x1b] != -1) || (*piVar3 != 0)) && (piVar3[-0x1e824d] == iVar7)) {
                        (&iStack_48)[iVar4] = 1;
                    }
                    iVar4 = iVar4 + 1;
                    piVar3 = piVar3 + 1;
                } while (iVar4 < 9);
                piVar6 = &DAT_GameState::instance.playerDataArray[1].playerDeathRelated;
                psVar9 = DAT_GameState::instance.mapAndTime.playerIsAlive + 1;
                piVar3 = local_44;
                do {
                    if ((local_68[-0x1b] != -1) || (*local_68 != 0)) {
                        *psVar9 = (short)*piVar3;
                        DAT_GameState::instance.mapAndTime.gameOver = TRUE;
                        *piVar6 = 1;
                        DAT_GameState::instance.mapAndTime.gameOverTime = timeGetTime();
                        DAT_GameCore::instance.skipStoreSKMasters = 0;
                        MACRO_CALL(UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(UI::Enums::DEID_WIN_DEFEAT_WINDOW, 1);
                        if ((DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                                == UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM)
                            || (DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                                == UI::Enums::BASMTT_SIEGETENT_SHIELD)) {
                            DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab
                                = DAT_GameCore::instance.tabTypeSiegeSubset;
                            MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                UI::Enums::MVT_BUILD_MENU, 0);
                        }
                        DAT_TileMapState::instance.currentMapperCommand = Commands::M_MAPPER_NULL;
                        if (0 < DAT_UnitsState::instance.totalUnitsInSelection) {
                            MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                            MACRO_CALL_MEMBER(
                                Map::Units::UnitsState_Func::queueEscapeCommand, DAT_UnitsState::ptr)();
                            MACRO_CALL_MEMBER(
                                Input::MouseState_Func::resetMouseCursorState, DAT_MouseState::ptr)();
                        }
                    }
                    psVar9 = psVar9 + 1;
                    local_68 = local_68 + 1;
                    piVar3 = piVar3 + 1;
                    piVar6 = piVar6 + 0xe7d;
                } while ((int)psVar9 < 0x117ef52);
            }
        }
    }

}
}
