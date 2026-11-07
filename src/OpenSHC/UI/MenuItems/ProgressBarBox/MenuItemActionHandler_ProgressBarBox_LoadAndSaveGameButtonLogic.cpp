// disable deprecation warnings for strcpy and strcat
#pragma warning(disable : 4996)

#include "../ProgressBarBox.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/IO/FilePackager.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"
#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"
#include "OpenSHC/Audio/SFX/SpeechEffectID.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/Text/TextArrayIndexType.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/string-macros.hpp"

#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapDefinedData.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"
#include "OpenSHC/Globals/DAT_WallAndPitchState.hpp"
#include "OpenSHC/Globals/FilePackagerObj.hpp"
#include "OpenSHC/Globals/INT_00b95b64.hpp"
#include "OpenSHC/Globals/INT_00b960e4.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004950B0
        void ProgressBarBox::MenuItemActionHandler_ProgressBarBox_LoadAndSaveGameButtonLogic(int param_1, ...)
        {
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                && DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                && DAT_GameSynchronyState::instance.saveRelated) {
                return;
            }
            // The original copies the name and appends the extension inline, so the macros are used here.
            char fileName[1008]; // the size of the original's buffer
            switch (DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter) {
            case 32:
            case 46:
                // save
                DAT_UserTextHandlerState::instance.allowUserTextInput = 0;
                MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                    OpenSHC::Text::TAIT_TWO__FILTER_A);
                DAT_UserTextHandlerState::instance.allowUserTextInput = 1;
                if (DAT_MenuTextInputState::instance.DAT_ArrayOfMapU3EndInt2) {
                    strcpy(fileName,
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::UserTextHandler_Func::getCurrentText, DAT_UserTextHandlerState::ptr)());
                    // ".tmp"
                    strcat(fileName, S__TMP_005A75A8);
                    MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName,
                        DAT_ResourceManager::ptr)(OpenSHC::IO::FRT_MAPS, fileName);
                } else if (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_MAP_EDITOR_PROPERTIES
                    || DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_UNUSED_CREATE_SIEGE) {
                    strcpy(fileName,
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::UserTextHandler_Func::getCurrentText, DAT_UserTextHandlerState::ptr)());
                    // ".map"
                    strcat(fileName, S__MAP_005A2294);
                    MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName,
                        DAT_ResourceManager::ptr)(OpenSHC::IO::FRT_MAPS, fileName);
                } else if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY
                    || DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                    strcpy(fileName,
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::UserTextHandler_Func::getCurrentText, DAT_UserTextHandlerState::ptr)());
                    // ".sav"
                    strcat(fileName, S__SAV_005A75A0);
                    MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName,
                        DAT_ResourceManager::ptr)(OpenSHC::IO::FRT_UNKNOWN, fileName);
                } else if (DAT_GameSynchronyState::instance.isHost) {
                    strcpy(fileName, DAT_GameSynchronyState::instance.shortMapName);
                    // ".msv"
                    strcat(fileName, S__MSV_005A7498);
                    MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName,
                        DAT_ResourceManager::ptr)(OpenSHC::IO::FRT_UNKNOWN, fileName);
                } else {
                    strcpy(fileName, DAT_GameSynchronyState::instance.shortMapName);
                    // ".msv"
                    strcat(fileName, S__MSV_005A7498);
                    MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName,
                        DAT_ResourceManager::ptr)(OpenSHC::IO::FRT_UNKNOWN, fileName);
                }
                DAT_UserTextHandlerState::instance.allowUserTextInput = 0;
                MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                    OpenSHC::Text::TAIT_NINE__FILTER_B);
                DAT_UserTextHandlerState::instance.allowUserTextInput = 1;
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                    OpenSHC::Audio::SFX::SEID_GENERAL_SAVING);
                FilePackagerObj::instance.loadAndSaveBarFunc
                    = MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderLoadAndSaveBar);
                MACRO_CALL_MEMBER(OpenSHC::IO::FilePackager_Func::writeMapOrSaveFile, FilePackagerObj::ptr)(
                    DAT_MapDefinedData::instance.MapSectionAddressArray);
                INT_00b95b64::instance = 1;
                DAT_WallAndPitchState::instance.countdown = 0;
                DAT_MenuTextInputState::instance.field_0xa4 = 1;
                if ((DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY)
                    || (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
                }
                if (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_MAP_EDITOR_PROPERTIES) {
                    MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::loadMapHeaders, DAT_ResourceManager::ptr)(
                        FALSE);
                }
                break;
            case 31: {
                // load
                int const index = DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionIndex
                    + DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset;
                DAT_VideoBikQueue::instance.storedMessages_0x924 = 0;
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition2::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                if (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_UNUSED_CREATE_SIEGE) {
                    strcpy(fileName,
                        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                            DAT_ResourceManager::ptr)(DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[index]));
                    MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::setTextEntryAndUpdateCursor,
                        DAT_UserTextHandlerState::ptr)(OpenSHC::Text::TAIT_TWO__FILTER_A, fileName);
                    // ".tmp"
                    strcat(fileName, S__TMP_005A75A8);
                    MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName,
                        DAT_ResourceManager::ptr)(OpenSHC::IO::FRT_MAPS, fileName);
                } else if (DAT_GameCore::instance.currentMenuViewType != OpenSHC::UI::Enums::MVT_CUSTOM_SCENARIOS) {
                    if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                        && DAT_GameSynchronyState::instance.currentGameMode
                            != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                        if (DAT_GameSynchronyState::instance.isHost) {
                            strcpy(fileName, DAT_GameSynchronyState::instance.shortMapName);
                            MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::setTextEntryAndUpdateCursor,
                                DAT_UserTextHandlerState::ptr)(OpenSHC::Text::TAIT_TWO__FILTER_A, fileName);
                            // ".msv"
                            strcat(fileName, S__MSV_005A7498);
                            MACRO_CALL_MEMBER(
                                OpenSHC::Map::TileMapState_Func::setupAllMapSections, DAT_TileMapState::ptr)();
                            MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName,
                                DAT_ResourceManager::ptr)(OpenSHC::IO::FRT_UNKNOWN, fileName);
                        } else {
                            strcpy(fileName, DAT_GameSynchronyState::instance.shortMapName);
                            MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::setTextEntryAndUpdateCursor,
                                DAT_UserTextHandlerState::ptr)(OpenSHC::Text::TAIT_TWO__FILTER_A, fileName);
                            // ".msv"
                            strcat(fileName, S__MSV_005A7498);
                            MACRO_CALL_MEMBER(
                                OpenSHC::Map::TileMapState_Func::setupAllMapSections, DAT_TileMapState::ptr)();
                            MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName,
                                DAT_ResourceManager::ptr)(OpenSHC::IO::FRT_UNKNOWN, fileName);
                        }
                    } else {
                        strcpy(fileName,
                            MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                                DAT_ResourceManager::ptr)(
                                DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[index]));
                        MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::setTextEntryAndUpdateCursor,
                            DAT_UserTextHandlerState::ptr)(OpenSHC::Text::TAIT_TWO__FILTER_A, fileName);
                        // ".sav"
                        strcat(fileName, S__SAV_005A75A0);
                        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName,
                            DAT_ResourceManager::ptr)(OpenSHC::IO::FRT_UNKNOWN, fileName);
                    }
                } else {
                    strcpy(fileName,
                        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                            DAT_ResourceManager::ptr)(DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[index]));
                    MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::setTextEntryAndUpdateCursor,
                        DAT_UserTextHandlerState::ptr)(OpenSHC::Text::TAIT_TWO__FILTER_A, fileName);
                    // ".map"
                    strcat(fileName, S__MAP_005A2294);
                    MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName,
                        DAT_ResourceManager::ptr)(OpenSHC::IO::FRT_MAPS, fileName);
                }
                DAT_SoundSystemState::instance.streamFlagsUnkAndLoopCount_0x34[4] = 0;
                DAT_SoundSystemState::instance.streamFlagsUnkAndLoopCount_0x34[3] = 0;
                MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                    OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_1);
                MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                    OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_2);
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                    OpenSHC::Audio::SFX::SEID_GENERAL_LOADING);
                FilePackagerObj::instance.loadAndSaveBarFunc
                    = MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderLoadAndSaveBar);
                MACRO_CALL_MEMBER(OpenSHC::IO::FilePackager_Func::readMapOrSavFile, FilePackagerObj::ptr)(
                    DAT_MapDefinedData::instance.MapSectionAddressArray);
                INT_00b95b64::instance = 1;
                DAT_GameCore::instance.isBinkVideoPlaying = 0;
                DAT_BuildingsState::instance.DAT_IsBuildingOrPeasantBinkPlaying = FALSE;
                MACRO_CALL_MEMBER(
                    OpenSHC::Rendering::Bink::BinkControlClass_Func::stopAllBinkPlayback, DAT_BinkControlState::ptr)();
                DAT_SoundSystemState::instance.currentSoundID_0x3278 = -1;
                MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::setSomeSoundTime, DAT_SoundSystemState::ptr)();
                if (DAT_SoundSystemState::instance.sec_Section1055_0x3274 < 0) {
                    DAT_SoundSystemState::instance.sec_Section1055_0x3274 = 0;
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::Audio::MSS::SoundSystem_Func::setupVolumeAndSoundID, DAT_SoundSystemState::ptr)(
                    (OpenSHC::DE::SHCDE::eMusicIDs)(DAT_SoundSystemState::instance.sec_Section1055_0x3274));
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::prepareMap, DAT_TileMapState::ptr)();
                MACRO_CALL_MEMBER(
                    OpenSHC::Rendering::Bink::AIMessageQueue_Func::playNextStoredBinkVideo, DAT_VideoBikQueue::ptr)();
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
                DAT_MenuTextInputState::instance.dialogResult = 1;
                MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                    OpenSHC::UI::Enums::DEID_MISSION_WIN_DEFEAT_BANNER, 0);
                MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                    OpenSHC::UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO, 0);
                MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                    OpenSHC::UI::Enums::DEID_PLAYER_INFO_ON_HOVER, 0);
                MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                    OpenSHC::UI::Enums::DEID_WIN_DEFEAT_WINDOW, 0);
                if (DAT_MenuModalComposition2::instance.activeModalDialogID
                    == OpenSHC::UI::Enums::MMT_DISPLAY_AI_LORD_MESSAGE) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition2::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                }
                DAT_UnitsState::instance.lastSelectedUnitID = 0;
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::clearSelectionCountsAndPlayerIDs, DAT_UnitsState::ptr)();
                if (DAT_GameCore::instance.currentMenuViewType != OpenSHC::UI::Enums::MVT_UNUSED_CREATE_SIEGE) {
                    if (DAT_GameCore::instance.currentMenuViewType != OpenSHC::UI::Enums::MVT_CUSTOM_SCENARIOS) {
                        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                            && DAT_GameSynchronyState::instance.currentGameMode
                                != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                            DAT_GameCore::instance.gameMode_2 = OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER;
                            MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                OpenSHC::UI::Enums::MVT_UNKNOWN_33, 0);
                        } else {
                            int const soundID = DAT_SoundSystemState::instance.currentSoundID_0x3278;
                            DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                                = OpenSHC::UI::Enums::BASMTT_HUNTERSHUT;
                            MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
                            if (soundID > 0) {
                                DAT_SoundSystemState::instance.currentSoundID_0x3278 = soundID;
                            }
                            for (int i = 0; i < countof(DAT_GameSynchronyState::instance.currentPlayerFullIDArray);
                                ++i) {
                                DAT_GameSynchronyState::instance.currentPlayerFullIDArray[i] = -1;
                            }
                            if (!DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                                DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
                            }
                            DAT_GameSynchronyState::instance
                                .currentPlayerFullIDArray[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 1;
                            if (DAT_GameSynchronyState::instance.currentGameMode
                                == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                                DAT_GameCore::instance.lordIcons[1] = DAT_GameCore::instance.lordIconUnk;
                                if (DAT_GameCore::instance.lordIconUnk >= 2) {
                                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                                        DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_SHARE_AIV_HASH);
                                }
                            }
                        }
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                            OpenSHC::UI::Enums::MVT_MAP_EDITOR_PROPERTIES, 0);
                        for (int i = 0; i < countof(DAT_GameSynchronyState::instance.currentPlayerFullIDArray); ++i) {
                            DAT_GameSynchronyState::instance.currentPlayerFullIDArray[i] = -1;
                        }
                        if (!DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                            DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
                        }
                        DAT_GameSynchronyState::instance
                            .currentPlayerFullIDArray[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 1;
                        INT_00b960e4::instance = 1;
                        DAT_GameCore::instance.gameMode_2 = OpenSHC::Game::GM_EDITOR;
                        for (int i = 1; i < countof(DAT_GameState::instance.playerDataArray); ++i) {
                            DAT_GameState::instance.playerDataArray[i].playerDeathRelated = 0;
                        }
                    }
                }
                break;
            }
            }
            MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
        }

    }
}
}
