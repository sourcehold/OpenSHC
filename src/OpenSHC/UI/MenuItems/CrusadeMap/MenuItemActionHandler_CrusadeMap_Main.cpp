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
        void CrusadeMap::MenuItemActionHandler_CrusadeMap_Main(int button, ...)
        {
            // Skip Current Mission: the trail's next mission is marked skipped with the chicken (-1200 months)
            if (button == 1000) {
                if (DAT_SkirmishTrailRelated1::instance <= 0) {
                    return;
                }
                // the trails have 50, 30 and 20 missions
                if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_FIRST_EDITION) {
                    int const mission = DAT_GameCore::instance.furthestSkirmishTrailMission;
                    if (mission >= countof(DAT_MissionDefinedData::instance.SkirmishTrailMissionPositions) - 1) {
                        return;
                    }
                    DAT_GameCore::instance.skirmishTrailProgress = mission;
                    if (DAT_GameCore::instance.skirmishTrailMonthsTakenOrChicken[mission] != -1) {
                        return;
                    }
                    DAT_GameCore::instance.skirmishTrailMonthsTakenOrChicken[mission] = -1200;
                    if (DAT_GameCore::instance.skirmishTrailProgress
                        == countof(DAT_MissionDefinedData::instance.SkirmishTrailMissionPositions) - 1) {
                        return;
                    }
                    ++DAT_GameCore::instance.skirmishTrailProgress;
                    ++DAT_GameCore::instance.furthestSkirmishTrailMission;
                    // this call and the code after it are repeated in each trail's branch, for the match
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::setStartDateUnk, DAT_GameCore::ptr)(1);
                    --DAT_SkirmishTrailRelated1::instance;
                    DWORD_00ed311c::instance = timeGetTime();
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setSoundWithVariation, DAT_SFXState::ptr)(
                        258, 100);
                    return;
                }
                if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_WARCHEST) {
                    int const mission = DAT_GameCore::instance.furthestWarchestTrailMission;
                    if (mission >= countof(DAT_MissionDefinedData::instance.WarchestTrailMissionPositions) - 1) {
                        return;
                    }
                    DAT_GameCore::instance.warchestTrailProgress = mission;
                    if (DAT_GameCore::instance.warchestTrailMonthsTakenOrChicken[mission] != -1) {
                        return;
                    }
                    DAT_GameCore::instance.warchestTrailMonthsTakenOrChicken[mission] = -1200;
                    if (DAT_GameCore::instance.warchestTrailProgress
                        == countof(DAT_MissionDefinedData::instance.WarchestTrailMissionPositions) - 1) {
                        return;
                    }
                    ++DAT_GameCore::instance.warchestTrailProgress;
                    ++DAT_GameCore::instance.furthestWarchestTrailMission;
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::setStartDateUnk, DAT_GameCore::ptr)(2);
                    --DAT_SkirmishTrailRelated1::instance;
                    DWORD_00ed311c::instance = timeGetTime();
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setSoundWithVariation, DAT_SFXState::ptr)(
                        258, 100);
                    return;
                }
                if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME) {
                    int const mission = DAT_GameCore::instance.furthestExtremeTrailMission;
                    if (mission >= 19) {
                        return;
                    }
                    DAT_GameCore::instance.extremeTrailProgress = mission;
                    if (DAT_GameCore::instance.extremeTrailMonthsTakenOrChicken[mission] != -1) {
                        return;
                    }
                    DAT_GameCore::instance.extremeTrailMonthsTakenOrChicken[mission] = -1200;
                    if (DAT_GameCore::instance.extremeTrailProgress == 19) {
                        return;
                    }
                    ++DAT_GameCore::instance.extremeTrailProgress;
                    ++DAT_GameCore::instance.furthestExtremeTrailMission;
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::setStartDateUnk, DAT_GameCore::ptr)(3);
                    --DAT_SkirmishTrailRelated1::instance;
                    DWORD_00ed311c::instance = timeGetTime();
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setSoundWithVariation, DAT_SFXState::ptr)(
                        258, 100);
                }
                return;
            }
            // the lord picked: his face goes into the player's face slot, then the mission briefing
            if (button == 10) {
                MACRO_CALL(OpenSHC::OS_Func::_memcpy)(DAT_TextureRenderCoreObject::instance.bitmapsFaces_0x94
                        + (DAT_GameSynchronyState::instance.currentPlayerSlotID + 19) * 66 * 64,
                    DAT_TextureRenderCoreObject::instance.bitmapsFaces_0x94
                        + (DAT_GameCore::instance.lordIconUnk - 2) * 66 * 64,
                    66 * 64 * sizeof(ushort));
                DAT_TextureRenderCoreObject::instance
                    .bitmapFaceSizes[DAT_GameSynchronyState::instance.currentPlayerSlotID + 19]
                    = 66 * 64 * sizeof(ushort);
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_CRUSADE_MISSION_INTRO, 0);
                return;
            }
            // back to the choice of crusade
            if (button == 11) {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_SELECT_CRUSADE, 0);
                return;
            }
            // a click on the map picks the mission under the mouse, up to the furthest one reached
            if (button == 1) {
                int const clickX = DAT_MouseState::instance.screenSpaceX - DAT_ButtonX::instance;
                int const clickY = DAT_MouseState::instance.screenSpaceY - DAT_ButtonY::instance;
                if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_FIRST_EDITION) {
                    for (int mission = 0;
                        mission < countof(DAT_MissionDefinedData::instance.SkirmishTrailMissionPositions); ++mission) {
                        if (mission > DAT_GameCore::instance.furthestSkirmishTrailMission) {
                            return;
                        }
                        int const left
                            = DAT_MissionDefinedData::instance.SkirmishTrailMissionPositions[mission][0] - 10;
                        int const top = DAT_MissionDefinedData::instance.SkirmishTrailMissionPositions[mission][1] - 10;
                        if (clickX >= left && clickX <= left + 20 && clickY >= top && clickY <= top + 20) {
                            DAT_GameCore::instance.skirmishTrailProgress = mission;
                            INT_00eb9b48::instance = 1;
                            DWORD_00ed27a8::instance = timeGetTime();
                            return;
                        }
                    }
                } else if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_WARCHEST) {
                    for (int mission = 0;
                        mission < countof(DAT_MissionDefinedData::instance.WarchestTrailMissionPositions); ++mission) {
                        if (mission > DAT_GameCore::instance.furthestWarchestTrailMission) {
                            return;
                        }
                        int const left
                            = DAT_MissionDefinedData::instance.WarchestTrailMissionPositions[mission][0] - 10;
                        int const top = DAT_MissionDefinedData::instance.WarchestTrailMissionPositions[mission][1] - 10;
                        if (clickX >= left && clickX <= left + 20 && clickY >= top && clickY <= top + 20) {
                            DAT_GameCore::instance.warchestTrailProgress = mission;
                            INT_00eb9b48::instance = 1;
                            DWORD_00ed27a8::instance = timeGetTime();
                            return;
                        }
                    }
                } else if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME) {
                    // only the first 20 of the 30 positions are missions
                    for (int mission = 0; mission < 20; ++mission) {
                        if (mission > DAT_GameCore::instance.furthestExtremeTrailMission) {
                            return;
                        }
                        int const left = DAT_MissionDefinedData::instance.ExtremeTrailMissionPositions[mission][0] - 10;
                        int const top = DAT_MissionDefinedData::instance.ExtremeTrailMissionPositions[mission][1] - 10;
                        if (clickX >= left && clickX <= left + 20 && clickY >= top && clickY <= top + 20) {
                            DAT_GameCore::instance.extremeTrailProgress = mission;
                            INT_00eb9b48::instance = 1;
                            DWORD_00ed27a8::instance = timeGetTime();
                            return;
                        }
                    }
                }
                return;
            }
            // the rankings
            if (button == 99) {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_RANKING_GAMES, 0);
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    OpenSHC::Audio::SFX::SEID_UNKNOWN_0xFD);
            }
        }

    }
}
}
