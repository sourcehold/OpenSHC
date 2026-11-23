#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"
#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/Audio/SFX/SpeechEffectID.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/Units/UnitTypeShort.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_00b95b68.hpp"
#include "OpenSHC/Globals/DAT_00b95b6c.hpp"
#include "OpenSHC/Globals/DAT_00b96108.hpp"
#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TextEditorState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/INT_00b96124.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::Audio::SFX::SoundEffectID;
        using OpenSHC::Map::Buildings::BuildingTypeShort;
        using OpenSHC::Map::Units::UnitTypeShort;

        // FUNCTION: STRONGHOLDCRUSADER 0x00446C00
        void BuildingAndStatusMenu::MenuView_BuildingAndStatusMenu_Prepare()
        {
            int menuY = DAT_WindowAndDirectDraw::instance.resolutionY - 600;
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_640x480) {
                Menu* const menu = DAT_MenuHandlerState::instance.currentMenu;
                menu->xPosition = -698;
                menu->yPosition = menuY;
                DAT_MenuHandlerState::instance.x = -698;
            } else {
                int menuX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
                Menu* const menu = DAT_MenuHandlerState::instance.currentMenu;
                menu->xPosition = menuX;
                menu->yPosition = menuY;
                DAT_MenuHandlerState::instance.x = menuX;
            }
            DAT_MenuHandlerState::instance.y = menuY;
            MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(4);
            DAT_BuildingsState::instance.field_0x18e04c = 0;
            DAT_BuildingsState::instance.field_0x18e050 = 0;
            DAT_BuildingsState::instance.DAT_CurrentlyPlayingBuildingBik = 0;
            DAT_00b96108::instance = 0;
            DAT_00b95b68::instance = 0;
            if (DAT_GameCore::instance.activeMenuTab.tabType != OpenSHC::UI::Enums::BASMTT_PEASANT
                && (DAT_GameCore::instance.activeMenuTab.tabType < OpenSHC::UI::Enums::BASMTT_STATUS_OVERVIEW
                    || DAT_GameCore::instance.activeMenuTab.tabType > OpenSHC::UI::Enums::BASMTT_STATUS_RELIGION)) {
                int const buildingID = DAT_BuildingsState::instance.menuSelectedBuildingID;
                BuildingTypeShort const* const type = &DAT_BuildingsState::instance.buildings[buildingID].buildingType;
                if (DAT_RenderingDefinedData::instance
                            .BuildingHelpArray[DAT_BuildingsState::instance.buildings[buildingID].buildingType]
                        != 0
                    && MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::loadAndParseHelpFile,
                        DAT_TextEditorState::ptr)(DAT_RenderingDefinedData::instance
                            .BuildingHelpArray[DAT_BuildingsState::instance.buildings[buildingID].buildingType])) {
                    DAT_BuildingsState::instance.field_0x18e04c
                        = (undefined4)DAT_RenderingDefinedData::instance.BuildingHelpArray[*type];
                }
                if (DAT_RenderingDefinedData::instance.BuildingTgxSketchArray[*type] != 0) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                        DAT_RenderingDefinedData::instance.BuildingTgxSketchArray[*type]);
                    DAT_00b96108::instance = 1;
                }
                if (DAT_RenderingDefinedData::instance.BuildingBikArray[*type] != 0) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                        OpenSHC::IO::FRT_BINKS, DAT_RenderingDefinedData::instance.BuildingBikArray[*type]);
                    if (MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::doesFileOfActiveResourceExist,
                            DAT_ResourceManager::ptr)()
                        && !DAT_GameCore::instance.isBinkVideoPlaying) {
                        DAT_BuildingsState::instance.DAT_CurrentlyPlayingBuildingBik
                            = DAT_RenderingDefinedData::instance.BuildingBikArray[*type];
                        MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::playBINK,
                            DAT_BinkControlState::ptr)(0, DAT_BuildingsState::instance.DAT_CurrentlyPlayingBuildingBik,
                            1, 0, DAT_MenuHandlerState::instance.x + 571, DAT_MenuHandlerState::instance.y + 465, 1);
                        DAT_BuildingsState::instance.DAT_IsBuildingOrPeasantBinkPlaying = TRUE;
                    }
                }
                MACRO_CALL(OpenSHC::UI::Helpers_Func::HandleBuildingSelectionSpeech)(buildingID);
            }
            int const playerID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            DAT_GameState::instance.playerDataArray[playerID].timeTaxesOrRationsChange = 0;
            switch (DAT_GameCore::instance.activeMenuTab.tabType) {
            case OpenSHC::UI::Enums::BASMTT_KEEP_OR_MPMENU_IPX: {
                if (DAT_GameState::instance.playerDataArray[playerID]
                        .currentResources[OpenSHC::Game::Resources::RT_GOLD]
                    > (DAT_GameState::instance.playerDataArray[playerID].marketGold
                          + DAT_GameState::instance.playerDataArray[playerID].beforeLastMonthsGold)
                        + 40) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_TAXES_INCREASE1);
                } else if (DAT_GameState::instance.playerDataArray[playerID]
                               .currentResources[OpenSHC::Game::Resources::RT_GOLD]
                    > (DAT_GameState::instance.playerDataArray[playerID].marketGold
                        + DAT_GameState::instance.playerDataArray[playerID].beforeLastMonthsGold)) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_TAXES_INCREASE2);
                } else if (DAT_GameState::instance.playerDataArray[playerID]
                               .currentResources[OpenSHC::Game::Resources::RT_GOLD]
                    < (DAT_GameState::instance.playerDataArray[playerID].marketGold
                          + DAT_GameState::instance.playerDataArray[playerID].beforeLastMonthsGold)
                        - 40) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_TAXES_DECREASE2);
                } else if (DAT_GameState::instance.playerDataArray[playerID]
                               .currentResources[OpenSHC::Game::Resources::RT_GOLD]
                    < (DAT_GameState::instance.playerDataArray[playerID].marketGold
                        + DAT_GameState::instance.playerDataArray[playerID].beforeLastMonthsGold)) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_TAXES_DECREASE1);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_TAXES_CONSTANT);
                }
                break;
            }
            case OpenSHC::UI::Enums::BASMTT_GRANARY_OR_MPMENU_TCPIP:
                if (DAT_GameState::instance.playerDataArray[playerID].rationsSetting != 0) {
                    if (DAT_GameState::instance.playerDataArray[playerID].totalFood <= 0) {
                        // "The granary is empty sire"
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            s_food_warning5_wav_005a2acc);
                    } else {
                        int const before
                            = DAT_GameState::instance.playerDataArray[playerID].foodStorageLevelLastLastMonth;
                        int const level = DAT_GameState::instance.playerDataArray[playerID].foodStorageLevel;
                        if (before < level) {
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                                OpenSHC::Audio::SFX::SEID_FOOD_GROWING);
                        } else if (level < before) {
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                                OpenSHC::Audio::SFX::SEID_FOOD_FALLING);
                        }
                    }
                }
                break;
            case OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM:
                MACRO_CALL(OpenSHC::UI::Helpers_Func::SetEnoughGoldForRequestedUnitToTrueUnk)();
                break;
            case OpenSHC::UI::Enums::BASMTT_MERCENARYPOST:
                MACRO_CALL(OpenSHC::UI::Helpers_Func::DisableMercPostPortraits)();
                break;
            case OpenSHC::UI::Enums::BASMTT_ENGINEERSGUILD:
                MACRO_CALL(OpenSHC::UI::Helpers_Func::CheckIfEnoughGoldForLadderman)();
                break;
            case OpenSHC::UI::Enums::BASMTT_TUNNELERSGUILD:
                MACRO_CALL(OpenSHC::UI::Helpers_Func::CheckIfEnoughGoldForTunneler)();
                break;
            case OpenSHC::UI::Enums::BASMTT_FLETCHER:
            case OpenSHC::UI::Enums::BASMTT_BLACKSMITH:
            case OpenSHC::UI::Enums::BASMTT_POLETURNER:
                DAT_GameState::instance.playerDataArray[playerID].weaponRelated
                    = DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                          .producedItemType;
                break;
            case OpenSHC::UI::Enums::BASMTT_CHAPEL_AND_CHURCH:
                switch (DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                        .buildingType) {
                case OpenSHC::Map::Buildings::BT_CHAPEL:
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_CHAPEL_BELL);
                    break;
                case OpenSHC::Map::Buildings::BT_CHURCH:
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_CHURCH_BELL);
                    break;
                case OpenSHC::Map::Buildings::BT_CATHEDRAL:
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_CATHEDRAL_BELL);
                    break;
                }
                // "wedding_sketch.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_wedding_sketch_tgx_005a2ab8);
                break;
            case OpenSHC::UI::Enums::BASMTT_INN_OR_MPMMENU_UNK:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    OpenSHC::Audio::SFX::SEID_INN);
                break;
            case OpenSHC::UI::Enums::BASMTT_MILL:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    OpenSHC::Audio::SFX::SEID_MILL);
                break;
            case OpenSHC::UI::Enums::BASMTT_STABLES:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    (SoundEffectID)89);
                break;
            case OpenSHC::UI::Enums::BASMTT_CHOPPINGBLOCK:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    OpenSHC::Audio::SFX::SEID_PIKE_KILL);
                break;
            case OpenSHC::UI::Enums::BASMTT_STRETCHINGRACK:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    OpenSHC::Audio::SFX::SEID_STRETCHING_RACK);
                break;
            case OpenSHC::UI::Enums::BASMTT_CESSPIT:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    OpenSHC::Audio::SFX::SEID_FLIES);
                break;
            case OpenSHC::UI::Enums::BASMTT_GALLOWS:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    OpenSHC::Audio::SFX::SEID_GALLOWS);
                break;
            case OpenSHC::UI::Enums::BASMTT_DUNGEON:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    OpenSHC::Audio::SFX::SEID_DUNGEON);
                break;
            case OpenSHC::UI::Enums::BASMTT_OILSMELTER:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    OpenSHC::Audio::SFX::SEID_UNKNOWN_0x3D);
                break;
            case OpenSHC::UI::Enums::BASMTT_DAIRYFARM:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    (SoundEffectID)76);
                break;
            case OpenSHC::UI::Enums::BASMTT_PEASANT: {
                int const unitID = DAT_BuildingsState::instance.menuSelectedUnitID;
                UnitTypeShort const unitType = DAT_UnitsState::instance.units[unitID].unitType;
                DAT_00b95b6c::instance = -1;
                if (unitType == OpenSHC::Map::Units::UT_JESTER && (int)DAT_GameCore::instance.field_0x90 < 3) {
                    DAT_GameCore::instance.field_0x90++;
                }
                DAT_GameState::instance.mapAndTime.drunkenManStatus++;
                if (DAT_GameState::instance.mapAndTime.drunkenManStatus >= 32) {
                    DAT_GameState::instance.mapAndTime.drunkenManStatus = 0;
                }
                if (DAT_RenderingDefinedData::instance.ChimpTgxArray[unitType] != 0) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                        OpenSHC::IO::FRT_GFX, DAT_RenderingDefinedData::instance.ChimpTgxArray[unitType]);
                    if (MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::doesFileOfActiveResourceExist,
                            DAT_ResourceManager::ptr)()) {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(DAT_RenderingDefinedData::instance
                                .ChimpTgxArray[DAT_UnitsState::instance.units[unitID].unitType]);
                    } else {
                        DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                        // "chimp00_null.tgx"
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                            DAT_TextureRenderCoreObject::ptr)(s_chimp00_null_tgx_005a0c90);
                    }
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(DAT_RenderingDefinedData::instance
                        .ChimpTgxSketchArray[DAT_UnitsState::instance.units[unitID].unitType]);
                if (DAT_RenderingDefinedData::instance.ChimpHelpArray[DAT_UnitsState::instance.units[unitID].unitType]
                        != 0
                    && MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::loadAndParseHelpFile,
                        DAT_TextEditorState::ptr)(DAT_RenderingDefinedData::instance
                            .ChimpHelpArray[DAT_UnitsState::instance.units[unitID].unitType])) {
                    DAT_BuildingsState::instance.field_0x18e04c = (undefined4)(DAT_RenderingDefinedData::instance
                            .ChimpHelpArray[DAT_UnitsState::instance.units[unitID].unitType]);
                }
                if (DAT_RenderingDefinedData::instance.ChimpBikArray[DAT_UnitsState::instance.units[unitID].unitType]
                    != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName,
                        DAT_ResourceManager::ptr)(OpenSHC::IO::FRT_BINKS,
                        DAT_RenderingDefinedData::instance
                            .ChimpBikArray[DAT_UnitsState::instance.units[unitID].unitType]);
                    if (MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::doesFileOfActiveResourceExist,
                            DAT_ResourceManager::ptr)()
                        && !DAT_GameCore::instance.isBinkVideoPlaying) {
                        DAT_BuildingsState::instance.DAT_CurrentlyPlayingBuildingBik
                            = DAT_RenderingDefinedData::instance
                                  .ChimpBikArray[DAT_UnitsState::instance.units[unitID].unitType];
                        MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::playBINK,
                            DAT_BinkControlState::ptr)(0, DAT_BuildingsState::instance.DAT_CurrentlyPlayingBuildingBik,
                            1, 0, DAT_MenuHandlerState::instance.x + 571, DAT_MenuHandlerState::instance.y + 465, 1);
                        DAT_BuildingsState::instance.DAT_IsBuildingOrPeasantBinkPlaying = TRUE;
                    }
                }
                INT_00b96124::instance = 0;
                break;
            }
            case OpenSHC::UI::Enums::BASMTT_STATUS_OVERVIEW:
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                if (DAT_GameCore::instance.selectedLordTypeUnk == 0) {
                    // "shield1.tgx"
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(s_shield1_tgx_005a2aac);
                } else {
                    // "shield2.tgx"
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(s_shield2_tgx_005a2aa0);
                }
                break;
            case OpenSHC::UI::Enums::BASMTT_STATUS_POPULARITY: {
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                // "popularity_sketch.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_popularity_sketch_tgx_005a2a88);
                int const popularity
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .popularity
                    / 100;
                DAT_00b96108::instance = 1;
                if (popularity == 100) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_POP_POPULARITY1);
                } else if (popularity == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_POP_POPULARITY8);
                } else if (popularity < 20) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_POP_POPULARITY7);
                } else if (popularity < 40) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_POP_POPULARITY6);
                } else if (popularity < 50) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_POP_POPULARITY5);
                } else if (popularity < 60) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_POP_POPULARITY4);
                } else if (popularity < 80) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_POP_POPULARITY3);
                } else if (popularity < 100) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_POP_POPULARITY2);
                }
                break;
            }
            case OpenSHC::UI::Enums::BASMTT_STATUS_FEARFACTOR: {
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                // "fearfpos.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_fearfpos_tgx_005a2a78);
                // "fearfneg.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_fearfneg_tgx_005a2a68);
                int const fear
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .fearFactorLevel;
                if (fear != 0) {
                    if (fear <= -5) {
                        // "You are truly the cruelest tyrant in the kingdom your lordship"
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            SFX_CruellestTyrantInTheKingdom);
                    } else if (fear == -4) {
                        // "The people tremble at the very mention of your name sire"
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            SFX_PeopleTrembleAtYourName);
                    } else if (fear == -3) {
                        // "The people are very scared of you my liege"
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            SFX_PeopleAreVeryScared);
                    } else if (fear == -2) {
                        // "The people are frightened of you my lord"
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            SFX_PeopleAreFrightened);
                    } else if (fear == -1) {
                        // "The people are a little afraid of you my lord"
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            SFX_PeopleAreALittleAfraid);
                    } else if (fear == 1) {
                        // "The people trust you my lord"
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            SFX_PeopleTrustYouMyLord);
                    } else if (fear == 2) {
                        // "The people are not afraid of you at all my lord"
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            SFX_PeopleAreNotAfraidOfYouAtAll);
                    } else if (fear == 3) {
                        // "The people think you are fantastic liege"
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            SFX_PeopleThinkYouAreFantastic);
                    } else if (fear == 4) {
                        // "The people think you are really really nice sire"
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            SFX_PeopleThinkYouAreReallyNice);
                    } else if (fear >= 5) {
                        // "You are worshipped as the kindest man in all the kingdom my liege"
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            SFX_PeopleWorshipYouAsKindestMan);
                    }
                }
                break;
            }
            case OpenSHC::UI::Enums::BASMTT_STATUS_POPULATION:
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                // "popgraph.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_popgraph_tgx_005a2990);
                // "population_sketch.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_population_sketch_tgx_005a2978);
                break;
            case OpenSHC::UI::Enums::BASMTT_STATUS_FOOD:
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                // "food_sketch.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_food_sketch_tgx_005a2968);
                DAT_00b96108::instance = 1;
                break;
            case OpenSHC::UI::Enums::BASMTT_STATUS_ARMY:
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                // "armysbar.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_armysbar_tgx_005a2958);
                // "armybar.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_armybar_tgx_005a294c);
                // "armylbd.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_armylbd_tgx_005a2940);
                // "armyrbd.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_armyrbd_tgx_005a2934);
                // "armys1.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_armys1_tgx_005a2928);
                // "armys2.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_armys2_tgx_005a291c);
                // "armys3.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_armys3_tgx_005a2910);
                // "armys4.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_armys4_tgx_005a2904);
                // "armys5.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_armys5_tgx_005a28f8);
                // "armys6.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_armys6_tgx_005a28ec);
                // "armys7.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_armys7_tgx_005a28e0);
                // "armys8.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_armys8_tgx_005a28d4);
                // "armys9.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_armys9_tgx_005a28c8);
                // "armys10.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_armys10_tgx_005a28bc);
                // "armys11.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_armys11_tgx_005a28b0);
                // "armys12.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_armys12_tgx_005a28a4);
                // "armys13.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_armys13_tgx_005a2898);
                // "armys14.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_armys14_tgx_005a288c);
                // "armys15.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_armys15_tgx_005a2880);
                // "armys16.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_armys16_tgx_005a2874);
                // "armys17.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_armys17_tgx_005a2868);
                // "armys18.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_armys18_tgx_005a285c);
                // "armys19.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_armys19_tgx_005a2850);
                // "armys20.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_armys20_tgx_005a2844);
                // "armys21.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_armys21_tgx_005a2838);
                // "armys22.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_armys22_tgx_005a282c);
                // "armys23.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_armys23_tgx_005a2820);
                // "armys24.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_armys24_tgx_005a2814);
                // "armys25.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_armys25_tgx_005a2808);
                // "armys26.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_armys26_tgx_005a27fc);
                MACRO_CALL(OpenSHC::UI::Helpers_Func::CountPlayerUnitsByType)();
                break;
            case OpenSHC::UI::Enums::BASMTT_STATUS_RELIGION:
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                // "churchs.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_churchs_tgx_005a27f0);
                // "religion_sketch.tgx"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(s_religion_sketch_tgx_005a27dc);
                break;
            }
            if (DAT_BuildingsState::instance.field_0x18e04c != 0) {
                DAT_BuildingsState::instance.field_0x18e050
                    = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::findOrAddHelpSectionName,
                        DAT_TextEditorState::ptr)((char*)DAT_BuildingsState::instance.field_0x18e04c);
            }
            DAT_WindowAndDirectDraw::instance.pendingMenuRedraw = TRUE;
        }

    }
}
}
