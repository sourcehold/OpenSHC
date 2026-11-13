#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition3.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004C2280
    void MapPropertiesState::updateMilitaryCampaignMissionState()
    {
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .playerDeathRelated
            != 0) {
            if (DAT_BinkControlState::instance.binkObjPtrArray[1] == 0
                && DAT_VideoBikQueue::instance.storedMessages_0x924 == 0) {
                DAT_GameState::instance.mapAndTime.unknownCountdown01 -= 1;
            }
            if (DAT_GameState::instance.mapAndTime.unknownCountdown01 == 0) {
                DAT_VideoBikQueue::instance.storedMessages_0x924 = 0;
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
                    UI::Enums::MMT_NONE, FALSE);
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition2::ptr)(
                    UI::Enums::MMT_NONE, FALSE);
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition3::ptr)(
                    UI::Enums::MMT_NONE, FALSE);
                DAT_MenuTextInputState::instance.DAT_SomeTextArrayIndex = 9;
                MACRO_CALL_MEMBER(
                    UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
                if (DAT_GameCore::instance.gameMode_2 == 0) {
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .playerDeathRelated
                        == 1) {
                        MACRO_CALL_MEMBER(Game::GameCore_Func::incrementMissionProgress, DAT_GameCore::ptr)();
                        DAT_GameCore::instance.section1066 = 2;
                    }
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .playerDeathRelated
                        == 2) {
                        MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            UI::Enums::MVT_GAME_LOSTUnk, 0);
                        DAT_GameCore::instance.section1066 = 0;
                    }
                    MACRO_CALL(UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                        UI::Enums::DEID_MISSION_WIN_DEFEAT_BANNER, 0);
                }
                MACRO_CALL(UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                    UI::Enums::DEID_MISSION_WIN_DEFEAT_BANNER, 0);
            }
            return;
        }
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .lordKilledByPlayerID
            != 0) {
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .playerDeathRelated = 2;
            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::setAIControlStatusTo100000, DAT_UnitsState::ptr)();
            DAT_GameState::instance.mapAndTime.unknownCountdown01 = 240;
            if (DAT_GameCore::instance.gameMode_2 == 2 && DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == 0) {
                DAT_GameState::instance.mapAndTime.unknownCountdown01 = 640;
            }
            MACRO_CALL(UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                UI::Enums::DEID_MISSION_WIN_DEFEAT_BANNER, 2);
            if (DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab == UI::Enums::BMTT_SOLDIERS
                || DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab == 62) {
                DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab
                    = DAT_GameCore::instance.tabTypeSiegeSubset;
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_BUILD_MENU, 0);
            }
            DAT_TileMapState::instance.currentMapperCommand = Commands::M_MAPPER_NULL;
            if (DAT_UnitsState::instance.totalUnitsInSelection > 0) {
                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueEscapeCommand, DAT_UnitsState::ptr)();
                MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseCursorState, DAT_MouseState::ptr)();
            }
            return;
        }
        if (DAT_GameCore::instance.missionNumber1to20 == 16) {
            if (DAT_GameState::instance.mapAndTime.militaryCampaignStage == 0) {
                int hits = 0;
                for (int i = 1; i < 9; ++i) {
                    hits += DAT_GameState::instance.mapAndTime.emenyHitArray[i];
                }
                if (hits >= 8) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 1;
                    MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_NEW_TEXT2, 1),
                        (char*)s_good_soldier_nervous_bik_005aa81c, (char*)s_Ap_Milit21_wav_005aaa58);
                    DAT_GameState::instance.mapAndTime.yearCopy = DAT_GameState::instance.mapAndTime.year;
                    DAT_GameState::instance.mapAndTime.monthCopy = DAT_GameState::instance.mapAndTime.month + 3;
                    if (DAT_GameState::instance.mapAndTime.month >= 12) {
                        DAT_GameState::instance.mapAndTime.month -= 12;
                        DAT_GameState::instance.mapAndTime.year += 1;
                    }
                }
                if (DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID != 0) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 3;
                }
            } else if (DAT_GameState::instance.mapAndTime.militaryCampaignStage == 1) {
                if (DAT_GameState::instance.mapAndTime.month == DAT_GameState::instance.mapAndTime.monthCopy
                    && DAT_GameState::instance.mapAndTime.year == DAT_GameState::instance.mapAndTime.yearCopy) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 2;
                    MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_NEW_TEXT2, 2),
                        (char*)s_good_soldier_nervous_bik_005aa81c, (char*)s_Ap_Milit22_wav_005aaa48);
                    MACRO_CALL_MEMBER(MapPropertiesState_Func::spawnAttackWaveForPlayer, this)(2, 24, 5, 75, 10, 3);
                    DAT_GameState::instance.playerDataArray[2].currentWaveRandomAttackingStrength = 0;
                    DAT_GameState::instance.mapAndTime.yearCopy = DAT_GameState::instance.mapAndTime.year;
                    DAT_GameState::instance.mapAndTime.monthCopy = DAT_GameState::instance.mapAndTime.month + 1;
                    if (DAT_GameState::instance.mapAndTime.month >= 12) {
                        DAT_GameState::instance.mapAndTime.month -= 12;
                        DAT_GameState::instance.mapAndTime.year += 1;
                    }
                }
                if (DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID != 0) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 3;
                }
            } else if (DAT_GameState::instance.mapAndTime.militaryCampaignStage == 2) {
                if (DAT_GameState::instance.mapAndTime.month == DAT_GameState::instance.mapAndTime.monthCopy
                    && DAT_GameState::instance.mapAndTime.year == DAT_GameState::instance.mapAndTime.yearCopy) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 3;
                    MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_NEW_TEXT2, 3),
                        (char*)s_bad_arab_taunt_bik_005a7d2c, (char*)s_Ap_Milit23_wav_005aaa38);
                }
                if (DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID != 0) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 3;
                }
            } else if (DAT_GameState::instance.mapAndTime.militaryCampaignStage == 4) {
                if ((DAT_GameState::instance.mapAndTime.month == DAT_GameState::instance.mapAndTime.monthCopy
                        && DAT_GameState::instance.mapAndTime.year == DAT_GameState::instance.mapAndTime.yearCopy)
                    || DAT_GameState::instance.mapAndTime.year > DAT_GameState::instance.mapAndTime.yearCopy) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 5;
                    goto missionWon;
                }
            } else if (DAT_GameState::instance.mapAndTime.militaryCampaignStage == 3) {
                if (DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID != 0) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 4;
                    MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_NEW_TEXT2, 4),
                        (char*)s_good_soldier_taunt_bik_005aaa10, (char*)s_Ap_Milit24_wav_005aaa28);
                    DAT_GameState::instance.mapAndTime.yearCopy = DAT_GameState::instance.mapAndTime.year;
                    DAT_GameState::instance.mapAndTime.monthCopy = DAT_GameState::instance.mapAndTime.month + 1;
                    if (DAT_GameState::instance.mapAndTime.month >= 12) {
                        DAT_GameState::instance.mapAndTime.month -= 12;
                        DAT_GameState::instance.mapAndTime.year += 1;
                    }
                }
            }
        } else if (DAT_GameCore::instance.missionNumber1to20 == 17) {
            if (DAT_GameState::instance.mapAndTime.militaryCampaignStage == 0) {
                if (DAT_GameState::instance.mapAndTime.month == DAT_GameState::instance.mapAndTime.monthCopy
                    && DAT_GameState::instance.mapAndTime.year == DAT_GameState::instance.mapAndTime.yearCopy) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 1;
                    MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_NEW_TEXT2, 5),
                        (char*)s_good_soldier_nervous_bik_005aa81c, (char*)s_Ap_Milit25_wav_005aaa00);
                    DAT_GameState::instance.mapAndTime.yearCopy = DAT_GameState::instance.mapAndTime.year;
                    DAT_GameState::instance.mapAndTime.monthCopy = DAT_GameState::instance.mapAndTime.month + 2;
                    if (DAT_GameState::instance.mapAndTime.month >= 12) {
                        DAT_GameState::instance.mapAndTime.month -= 12;
                        DAT_GameState::instance.mapAndTime.year += 1;
                    }
                }
                if (DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID != 0) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 5;
                }
            } else if (DAT_GameState::instance.mapAndTime.militaryCampaignStage == 1) {
                if (DAT_GameState::instance.mapAndTime.month == DAT_GameState::instance.mapAndTime.monthCopy
                    && DAT_GameState::instance.mapAndTime.year == DAT_GameState::instance.mapAndTime.yearCopy) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 2;
                    MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_NEW_TEXT2, 6),
                        (char*)s_good_soldier_nervous_bik_005aa81c, (char*)s_Ap_Milit26_wav_005aa9f0);
                    MACRO_CALL_MEMBER(MapPropertiesState_Func::spawnAttackWaveForPlayer, this)(2, 72, 50, 71, 20, 3);
                    DAT_GameState::instance.playerDataArray[2].currentWaveRandomAttackingStrength = 0;
                }
                if (DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID != 0) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 5;
                }
            } else if (DAT_GameState::instance.mapAndTime.militaryCampaignStage == 2) {
                if (DAT_GameState::instance.playerDataArray[2].aiPlayerState == 4) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 3;
                    MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_NEW_TEXT2, 7),
                        (char*)s_bad_soldier_taunt_bik_005a7824, (char*)s_Ap_Milit27_wav_005aa9e0);
                }
                if (DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID != 0) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 5;
                }
            } else if (DAT_GameState::instance.mapAndTime.militaryCampaignStage == 3) {
                if (DAT_GameState::instance.playerDataArray[2].aiPlayerState == 8
                    || DAT_GameState::instance.playerDataArray[2].aiPlayerState == 9) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 4;
                    DAT_GameState::instance.mapAndTime.yearCopy = DAT_GameState::instance.mapAndTime.year;
                    DAT_GameState::instance.mapAndTime.monthCopy = DAT_GameState::instance.mapAndTime.month + 2;
                    if (DAT_GameState::instance.mapAndTime.month >= 12) {
                        DAT_GameState::instance.mapAndTime.month -= 12;
                        DAT_GameState::instance.mapAndTime.year += 1;
                    }
                }
                if (DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID != 0) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 5;
                }
            } else if (DAT_GameState::instance.mapAndTime.militaryCampaignStage == 4) {
                if (DAT_GameState::instance.mapAndTime.month == DAT_GameState::instance.mapAndTime.monthCopy
                    && DAT_GameState::instance.mapAndTime.year == DAT_GameState::instance.mapAndTime.yearCopy) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 5;
                    MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_NEW_TEXT2, 8),
                        (char*)s_good_soldier_taunt_bik_005aaa10, (char*)s_Ap_Milit28_wav_005aa9d0);
                }
                if (DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID != 0) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 5;
                }
            } else if (DAT_GameState::instance.mapAndTime.militaryCampaignStage == 6) {
                if ((DAT_GameState::instance.mapAndTime.month == DAT_GameState::instance.mapAndTime.monthCopy
                        && DAT_GameState::instance.mapAndTime.year == DAT_GameState::instance.mapAndTime.yearCopy)
                    || DAT_GameState::instance.mapAndTime.year > DAT_GameState::instance.mapAndTime.yearCopy) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 7;
                    goto missionWon;
                }
            } else if (DAT_GameState::instance.mapAndTime.militaryCampaignStage == 5) {
                if (DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID != 0) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 6;
                    MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_NEW_TEXT2, 9),
                        (char*)s_good_soldier_taunt_bik_005aaa10, (char*)s_Ap_Milit29_wav_005aa9c0);
                    DAT_GameState::instance.mapAndTime.yearCopy = DAT_GameState::instance.mapAndTime.year;
                    DAT_GameState::instance.mapAndTime.monthCopy = DAT_GameState::instance.mapAndTime.month + 1;
                    if (DAT_GameState::instance.mapAndTime.month >= 12) {
                        DAT_GameState::instance.mapAndTime.month -= 12;
                        DAT_GameState::instance.mapAndTime.year += 1;
                    }
                }
            }
        } else if (DAT_GameCore::instance.missionNumber1to20 == 18) {
            if (DAT_GameState::instance.mapAndTime.militaryCampaignStage == 0) {
                if (DAT_GameState::instance.mapAndTime.month == DAT_GameState::instance.mapAndTime.monthCopy
                    && DAT_GameState::instance.mapAndTime.year == DAT_GameState::instance.mapAndTime.yearCopy) {
                    DAT_GameState::instance.playerDataArray[2].currentWaveRandomAttackingStrength = 0;
                    DAT_GameState::instance.playerDataArray[3].currentWaveRandomAttackingStrength = 0;
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 1;
                    DAT_GameState::instance.playerDataArray[2].aiAttackCoordinationLevel = 1;
                    DAT_GameState::instance.playerDataArray[3].aiAttackCoordinationLevel = 1;
                }
            } else if (DAT_GameState::instance.mapAndTime.militaryCampaignStage == 1) {
                if (DAT_GameState::instance.playerDataArray[2].aiPlayerState >= 2
                    && DAT_GameState::instance.playerDataArray[3].aiPlayerState >= 2) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 2;
                    MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_NEW_TEXT2, 10),
                        (char*)s_good_soldier_nervous_bik_005aa81c, (char*)s_Ap_Milit30_wav_005aa9b0);
                }
                if (DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID != 0
                    && DAT_GameState::instance.playerDataArray[3].lordKilledByPlayerID != 0) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 3;
                }
            } else if (DAT_GameState::instance.mapAndTime.militaryCampaignStage == 2) {
                if (DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID != 0
                    || DAT_GameState::instance.playerDataArray[3].lordKilledByPlayerID != 0) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 3;
                    MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_NEW_TEXT2, 12),
                        (char*)s_good_soldier_taunt_bik_005aaa10, (char*)s_Ap_Milit32_wav_005aa9a0);
                }
            } else if (DAT_GameState::instance.mapAndTime.militaryCampaignStage == 3) {
                if (DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID != 0
                    && DAT_GameState::instance.playerDataArray[3].lordKilledByPlayerID != 0) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 4;
                    MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_NEW_TEXT2, 13),
                        (char*)s_good_soldier_taunt_bik_005aaa10, (char*)s_Ap_Milit33_wav_005aa990);
                    DAT_GameState::instance.mapAndTime.yearCopy = DAT_GameState::instance.mapAndTime.year;
                    DAT_GameState::instance.mapAndTime.monthCopy = DAT_GameState::instance.mapAndTime.month + 1;
                    if (DAT_GameState::instance.mapAndTime.month >= 12) {
                        DAT_GameState::instance.mapAndTime.month -= 12;
                        DAT_GameState::instance.mapAndTime.year += 1;
                    }
                }
            } else if (DAT_GameState::instance.mapAndTime.militaryCampaignStage == 4) {
                if ((DAT_GameState::instance.mapAndTime.month == DAT_GameState::instance.mapAndTime.monthCopy
                        && DAT_GameState::instance.mapAndTime.year == DAT_GameState::instance.mapAndTime.yearCopy)
                    || DAT_GameState::instance.mapAndTime.year > DAT_GameState::instance.mapAndTime.yearCopy) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 5;
                    goto missionWon;
                }
            }
        } else if (DAT_GameCore::instance.missionNumber1to20 == 19) {
            if (DAT_GameState::instance.mapAndTime.militaryCampaignStage == 0) {
                if (DAT_GameState::instance.mapAndTime.month == DAT_GameState::instance.mapAndTime.monthCopy
                    && DAT_GameState::instance.mapAndTime.year == DAT_GameState::instance.mapAndTime.yearCopy) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 1;
                    MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_NEW_TEXT2, 14),
                        (char*)s_bad_soldier_taunt_bik_005a7824, (char*)s_Ap_Milit34_wav_005aa980);
                    MACRO_CALL_MEMBER(MapPropertiesState_Func::spawnAttackWaveForPlayer, this)(2, 70, 8, 72, 22, 2);
                    DAT_GameState::instance.playerDataArray[2].currentWaveRandomAttackingStrength = 0;
                }
                if (DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID != 0
                    && DAT_GameState::instance.playerDataArray[3].lordKilledByPlayerID != 0) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 5;
                }
            } else if (DAT_GameState::instance.mapAndTime.militaryCampaignStage == 1) {
                if (DAT_GameState::instance.playerDataArray[2].aiPlayerState >= 2) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 2;
                    MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_NEW_TEXT2, 15),
                        (char*)s_good_soldier_nervous_bik_005aa81c, (char*)s_Ap_Milit35_wav_005aa970);
                }
                if (DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID != 0
                    && DAT_GameState::instance.playerDataArray[3].lordKilledByPlayerID != 0) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 5;
                }
            } else if (DAT_GameState::instance.mapAndTime.militaryCampaignStage == 2) {
                if (DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID != 0) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 3;
                    MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_NEW_TEXT2, 16),
                        (char*)s_good_soldier_taunt_bik_005aaa10, (char*)s_Ap_Milit36_wav_005aa960);
                    DAT_GameState::instance.mapAndTime.emenyHitArray[3] = 0;
                }
                if (DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID != 0
                    && DAT_GameState::instance.playerDataArray[3].lordKilledByPlayerID != 0) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 5;
                }
            } else if (DAT_GameState::instance.mapAndTime.militaryCampaignStage == 3) {
                if (DAT_GameState::instance.mapAndTime.emenyHitArray[3] >= 15) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 4;
                    MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_NEW_TEXT2, 17),
                        (char*)s_good_soldier_taunt_bik_005aaa10, (char*)s_Ap_Milit37_wav_005aa950);
                    MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_NEW_TEXT2, 18),
                        (char*)s_bad_soldier_taunt_bik_005a7824, (char*)s_Ap_Milit38_wav_005aa940);
                }
                if (DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID != 0
                    && DAT_GameState::instance.playerDataArray[3].lordKilledByPlayerID != 0) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 5;
                }
            } else if (DAT_GameState::instance.mapAndTime.militaryCampaignStage == 4) {
                if (DAT_GameState::instance.playerDataArray[3].lordKilledByPlayerID != 0) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 5;
                    DAT_GameState::instance.mapAndTime.yearCopy = DAT_GameState::instance.mapAndTime.year;
                    DAT_GameState::instance.mapAndTime.monthCopy = DAT_GameState::instance.mapAndTime.month + 1;
                    if (DAT_GameState::instance.mapAndTime.month >= 12) {
                        DAT_GameState::instance.mapAndTime.month -= 12;
                        DAT_GameState::instance.mapAndTime.year += 1;
                    }
                }
            } else if (DAT_GameState::instance.mapAndTime.militaryCampaignStage == 5) {
                if ((DAT_GameState::instance.mapAndTime.month == DAT_GameState::instance.mapAndTime.monthCopy
                        && DAT_GameState::instance.mapAndTime.year == DAT_GameState::instance.mapAndTime.yearCopy)
                    || DAT_GameState::instance.mapAndTime.year > DAT_GameState::instance.mapAndTime.yearCopy) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 6;
                    goto missionWon;
                }
            }
        } else if (DAT_GameCore::instance.missionNumber1to20 == 20) {
            BOOLEnum enemy3Down = FALSE;
            BOOLEnum enemy2Down = FALSE;
            BOOLEnum enemy4Down = FALSE;
            if (DAT_GameState::instance.mapAndTime.militaryCampaignStage == 0) {
                if (DAT_GameState::instance.mapAndTime.month == DAT_GameState::instance.mapAndTime.monthCopy
                    && DAT_GameState::instance.mapAndTime.year == DAT_GameState::instance.mapAndTime.yearCopy) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage = 1;
                    MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_NEW_TEXT2, 19),
                        (char*)s_good_soldier_nervous_bik_005aa81c, (char*)s_Ap_Milit39_wav_005aa930);
                }
            } else if (DAT_GameState::instance.mapAndTime.militaryCampaignStage == 1) {
                if (DAT_GameState::instance.playerDataArray[3].lordKilledByPlayerID != 0) {
                    enemy3Down = TRUE;
                    if ((1 & DAT_GameState::instance.mapAndTime.militaryCampaignFlags) == 0) {
                        DAT_GameState::instance.mapAndTime.militaryCampaignFlags |= 1;
                        DAT_GameState::instance.mapAndTime.yearCopy = DAT_GameState::instance.mapAndTime.year;
                        DAT_GameState::instance.mapAndTime.monthCopy = DAT_GameState::instance.mapAndTime.month + 1;
                        if (DAT_GameState::instance.mapAndTime.month >= 12) {
                            DAT_GameState::instance.mapAndTime.month -= 12;
                            DAT_GameState::instance.mapAndTime.year += 1;
                        }
                    } else if ((DAT_GameState::instance.mapAndTime.militaryCampaignFlags & 16) == 0
                        && DAT_GameState::instance.mapAndTime.month == DAT_GameState::instance.mapAndTime.monthCopy
                        && DAT_GameState::instance.mapAndTime.year == DAT_GameState::instance.mapAndTime.yearCopy) {
                        MACRO_CALL_MEMBER(
                            Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                            MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_NEW_TEXT2, 20),
                            (char*)s_good_soldier_taunt_bik_005aaa10, (char*)s_Ap_Milit40_wav_005aa920);
                        DAT_GameState::instance.mapAndTime.militaryCampaignFlags |= 16;
                    }
                }
                if (DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID != 0) {
                    enemy2Down = TRUE;
                    if ((2 & DAT_GameState::instance.mapAndTime.militaryCampaignFlags) == 0) {
                        DAT_GameState::instance.mapAndTime.militaryCampaignFlags |= 2;
                        DAT_GameState::instance.mapAndTime.yearCopy = DAT_GameState::instance.mapAndTime.year;
                        DAT_GameState::instance.mapAndTime.monthCopy = DAT_GameState::instance.mapAndTime.month + 1;
                        if (DAT_GameState::instance.mapAndTime.month >= 12) {
                            DAT_GameState::instance.mapAndTime.month -= 12;
                            DAT_GameState::instance.mapAndTime.year += 1;
                        }
                    } else if ((DAT_GameState::instance.mapAndTime.militaryCampaignFlags & 32) == 0
                        && DAT_GameState::instance.mapAndTime.month == DAT_GameState::instance.mapAndTime.monthCopy
                        && DAT_GameState::instance.mapAndTime.year == DAT_GameState::instance.mapAndTime.yearCopy) {
                        if (DAT_GameState::instance.playerDataArray[4].lordKilledByPlayerID == 0) {
                            MACRO_CALL_MEMBER(
                                Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_NEW_TEXT2, 21),
                                (char*)s_good_soldier_taunt_bik_005aaa10, (char*)s_Ap_Milit41_wav_005aa910);
                        }
                        DAT_GameState::instance.mapAndTime.militaryCampaignFlags |= 32;
                    }
                }
                if (DAT_GameState::instance.playerDataArray[4].lordKilledByPlayerID != 0) {
                    enemy4Down = TRUE;
                    if ((4 & DAT_GameState::instance.mapAndTime.militaryCampaignFlags) == 0) {
                        DAT_GameState::instance.mapAndTime.militaryCampaignFlags |= 4;
                        DAT_GameState::instance.mapAndTime.yearCopy = DAT_GameState::instance.mapAndTime.year;
                        DAT_GameState::instance.mapAndTime.monthCopy = DAT_GameState::instance.mapAndTime.month + 1;
                        if (DAT_GameState::instance.mapAndTime.month >= 12) {
                            DAT_GameState::instance.mapAndTime.month -= 12;
                            DAT_GameState::instance.mapAndTime.year += 1;
                        }
                    } else if ((DAT_GameState::instance.mapAndTime.militaryCampaignFlags & 64) == 0
                        && DAT_GameState::instance.mapAndTime.month == DAT_GameState::instance.mapAndTime.monthCopy
                        && DAT_GameState::instance.mapAndTime.year == DAT_GameState::instance.mapAndTime.yearCopy) {
                        if (DAT_GameState::instance.playerDataArray[2].lordKilledByPlayerID == 0) {
                            MACRO_CALL_MEMBER(
                                Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_NEW_TEXT2, 21),
                                (char*)s_good_soldier_taunt_bik_005aaa10, (char*)s_Ap_Milit41_wav_005aa910);
                        }
                        DAT_GameState::instance.mapAndTime.militaryCampaignFlags |= 64;
                    }
                }
                if (DAT_GameState::instance.playerDataArray[5].aiPlayerState >= 2
                    && DAT_GameState::instance.mapAndTime.field3183_0x27dc == 0) {
                    DAT_GameState::instance.mapAndTime.field3183_0x27dc = 1;
                    MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_NEW_TEXT2, 22),
                        (char*)s_good_soldier_taunt_bik_005aaa10, (char*)s_Ap_Milit42_wav_005aa900);
                }
                if (enemy3Down && enemy2Down && enemy4Down
                    && DAT_GameState::instance.playerDataArray[5].lordKilledByPlayerID != 0) {
                    DAT_GameState::instance.mapAndTime.militaryCampaignStage += 1;
                    MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_NEW_TEXT2, 23),
                        (char*)s__005a5339, (char*)s__005a5339);
                    goto missionWon;
                }
            }
        }
        return;

    missionWon:
        DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].playerDeathRelated
            = 1;
        DAT_GameState::instance.mapAndTime.unknownCountdown01 = 240;
        MACRO_CALL(UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
            UI::Enums::DEID_MISSION_WIN_DEFEAT_BANNER, 1);
        if (DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab == UI::Enums::BMTT_SOLDIERS
            || DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab == 62) {
            DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab = DAT_GameCore::instance.tabTypeSiegeSubset;
            MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(UI::Enums::MVT_BUILD_MENU, 0);
        }
        DAT_TileMapState::instance.currentMapperCommand = Commands::M_MAPPER_NULL;
        if (DAT_UnitsState::instance.totalUnitsInSelection > 0) {
            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
            MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueEscapeCommand, DAT_UnitsState::ptr)();
            MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseCursorState, DAT_MouseState::ptr)();
        }
    }

}
}
