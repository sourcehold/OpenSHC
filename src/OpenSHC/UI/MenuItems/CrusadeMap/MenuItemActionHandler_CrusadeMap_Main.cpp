#include "../CrusadeMap.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/Game/TrailType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MissionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishTrailRelated1.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DWORD_00ed27a8.hpp"
#include "OpenSHC/Globals/DWORD_00ed311c.hpp"
#include "OpenSHC/Globals/INT_00eb9b48.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004D8EC0
        void CrusadeMap::MenuItemActionHandler_CrusadeMap_Main(int param_1, ...)
        {
            int iVar1;
            int iVar2;
            dword dVar3;
            int iVar5;
            if (param_1 == 1000) {
                if ((int)DAT_SkirmishTrailRelated1::instance <= 0) {
                    return;
                }
                if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_FIRST_EDITION) {
                    iVar1 = DAT_GameCore::instance.furthestSkirmishTrailMission;
                    if (iVar1 >= 49) {
                        return;
                    }
                    DAT_GameCore::instance.skirmishTrailProgress = iVar1;
                    if (DAT_GameCore::instance.skirmishTrailMonthsTakenOrChicken[iVar1] != -1) {
                        return;
                    }
                    DAT_GameCore::instance.skirmishTrailMonthsTakenOrChicken[iVar1] = -1200;
                    if (DAT_GameCore::instance.skirmishTrailProgress == 49) {
                        return;
                    }
                    ++DAT_GameCore::instance.skirmishTrailProgress;
                    ++DAT_GameCore::instance.furthestSkirmishTrailMission;
                    iVar5 = 1;
                } else if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_WARCHEST) {
                    iVar1 = DAT_GameCore::instance.furthestWarchestTrailMission;
                    if (iVar1 >= 29) {
                        return;
                    }
                    DAT_GameCore::instance.warchestTrailProgress = iVar1;
                    if (DAT_GameCore::instance.warchestTrailMonthsTakenOrChicken[iVar1] != -1) {
                        return;
                    }
                    DAT_GameCore::instance.warchestTrailMonthsTakenOrChicken[iVar1] = -1200;
                    if (DAT_GameCore::instance.warchestTrailProgress == 29) {
                        return;
                    }
                    ++DAT_GameCore::instance.warchestTrailProgress;
                    ++DAT_GameCore::instance.furthestWarchestTrailMission;
                    iVar5 = 2;
                } else {
                    if (DAT_GameCore::instance.currentTrailType != OpenSHC::Game::TT_EXTREME) {
                        return;
                    }
                    iVar1 = DAT_GameCore::instance.furthestExtremeTrailMission;
                    if (iVar1 >= 19) {
                        return;
                    }
                    DAT_GameCore::instance.extremeTrailProgress = iVar1;
                    if (DAT_GameCore::instance.extremeTrailMonthsTakenOrChicken[iVar1] != -1) {
                        return;
                    }
                    DAT_GameCore::instance.extremeTrailMonthsTakenOrChicken[iVar1] = -1200;
                    if (DAT_GameCore::instance.extremeTrailProgress == 19) {
                        return;
                    }
                    ++DAT_GameCore::instance.extremeTrailProgress;
                    ++DAT_GameCore::instance.furthestExtremeTrailMission;
                    iVar5 = 3;
                }
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::setStartDateUnk, DAT_GameCore::ptr)(iVar5);
                --DAT_SkirmishTrailRelated1::instance;
                DWORD_00ed311c::instance = timeGetTime();
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setSoundWithVariation, DAT_SFXState::ptr)(
                    258, 100);
                return;
            } else {
                if (param_1 == 10) {
                    // copy bitmap of icon
                    MACRO_CALL(OpenSHC::OS_Func::_memcpy)(
                        (void*)((DAT_GameSynchronyState::instance.currentPlayerSlotID + 19) * 8448
                            + (int)DAT_TextureRenderCoreObject::instance.bitmapsFaces_0x94),
                        (void*)((DAT_GameCore::instance.lordIconUnk - 2) * 8448
                            + (int)DAT_TextureRenderCoreObject::instance.bitmapsFaces_0x94),
                        8448);
                    DAT_TextureRenderCoreObject::instance
                        .bitmapFaceSizes[DAT_GameSynchronyState::instance.currentPlayerSlotID + 19] = 8448;
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_CRUSADE_MISSION_INTRO, 0);
                }
                if (param_1 == 11) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_SELECT_CRUSADE, 0);
                }
                if (param_1 == 1) {
                    int _clickX = DAT_MouseState::instance.screenSpaceX - DAT_ButtonX::instance;
                    int _clickY = DAT_MouseState::instance.screenSpaceY - DAT_ButtonY::instance;
                    dword dVar4 = DAT_GameCore::instance.warchestTrailProgress;
                    iVar5 = DAT_GameCore::instance.extremeTrailProgress;
                    if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_FIRST_EDITION) {
                        dVar3 = 0;
                        do {
                            if ((int)dVar3 > DAT_GameCore::instance.furthestSkirmishTrailMission) {
                                return;
                            }
                            iVar1 = DAT_MissionDefinedData::instance.SkirmishTrailMissionPositions[dVar3][0];
                            iVar2 = DAT_MissionDefinedData::instance.SkirmishTrailMissionPositions[dVar3][1];
                            if (iVar1 - 10 <= _clickX && _clickX <= iVar1 + 10 && iVar2 + -_clickY >= 10
                                && _clickY <= iVar2 + 10) {
                            LAB_004d9190:
                                DAT_GameCore::instance.extremeTrailProgress = iVar5;
                                DAT_GameCore::instance.warchestTrailProgress = dVar4;
                                DAT_GameCore::instance.skirmishTrailProgress = dVar3;
                                INT_00eb9b48::instance = 1;
                                DWORD_00ed27a8::instance = timeGetTime();
                                return;
                            }
                            ++dVar3;
                        } while ((int)dVar3 < 50);
                    } else {
                        dVar3 = DAT_GameCore::instance.skirmishTrailProgress;
                        if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_WARCHEST) {
                            dVar4 = 0;
                            while ((int)dVar4 <= DAT_GameCore::instance.furthestWarchestTrailMission) {
                                iVar1 = DAT_MissionDefinedData::instance.WarchestTrailMissionPositions[dVar4][0];
                                iVar2 = DAT_MissionDefinedData::instance.WarchestTrailMissionPositions[dVar4][1];
                                if (iVar1 - 10 <= _clickX && _clickX <= iVar1 + 10 && iVar2 - 10 <= _clickY
                                    && _clickY <= iVar2 + 10)
                                    goto LAB_004d9190;
                                ++dVar4;
                                if ((int)dVar4 > 30) {
                                    return;
                                }
                            }
                        } else if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME) {
                            iVar5 = 0;
                            while (iVar5 <= DAT_GameCore::instance.furthestExtremeTrailMission) {
                                iVar1 = DAT_MissionDefinedData::instance.ExtremeTrailMissionPositions[iVar5][0];
                                iVar2 = DAT_MissionDefinedData::instance.ExtremeTrailMissionPositions[iVar5][1];
                                if (iVar1 - 10 <= _clickX && _clickX <= iVar1 + 10 && iVar2 + -_clickY >= 10
                                    && _clickY <= iVar2 + 10)
                                    goto LAB_004d9190;
                                ++iVar5;
                                if (20 < iVar5) {
                                    return;
                                }
                            }
                        }
                    }
                } else if (param_1 == 99) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_RANKING_GAMES, 0);
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_UNKNOWN_0xFD);
                }
            }
        }

    }
}
}
