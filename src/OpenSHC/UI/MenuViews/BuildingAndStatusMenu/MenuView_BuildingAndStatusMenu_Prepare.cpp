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
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/Units/UnitTypeShort.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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
        using OpenSHC::Audio::SFX::SpeechEffectID;
        using OpenSHC::IO::FileResourceType;
        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::Map::Buildings::BuildingTypeShort;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::UnitTypeShort;
        using OpenSHC::Rendering::ScreenResolutionEnum;
        using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Unable to use type for symbol _menuTab
         */
        /*
          WARNING: Enum "UnsortedBinkFlagInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00446C00
        void BuildingAndStatusMenu::MenuView_BuildingAndStatusMenu_Prepare()
        {
            UnitTypeShort* pUVar1;
            BuildingTypeShort BVar2;
            Menu* pMVar3;
            BOOLEnum BVar4;
            int iVar5;
            int iVar6;
            int iVar7;
            char* pcVar8;
            int _buildingIndex;
            int _playerId;
            int _currentPlayerGold;
            ActiveMenuTab _menuTab;
            BuildingTypeShort* _ptrToSelectedBuildingType;
            DAT_MenuHandlerState::instance.x = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            pMVar3 = DAT_MenuHandlerState::instance.currentMenu;
            DAT_MenuHandlerState::instance.y = DAT_WindowAndDirectDraw::instance.resolutionY + -600;
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_640x480) {
                (DAT_MenuHandlerState::instance.currentMenu)->xPosition = -0x2ba;
                pMVar3->yPosition = DAT_MenuHandlerState::instance.y;
                DAT_MenuHandlerState::instance.x = -0x2ba;
            } else {
                (DAT_MenuHandlerState::instance.currentMenu)->xPosition
                    = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
                pMVar3->yPosition = (undefined4)(DAT_MenuHandlerState::instance.y);
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(4);
            _buildingIndex = DAT_BuildingsState::instance.menuSelectedBuildingID;
            DAT_BuildingsState::instance.field24_0x18e04c = (undefined4)((char*)0x0);
            DAT_BuildingsState::instance.field25_0x18e050 = 0;
            DAT_BuildingsState::instance.DAT_CurrentlyPlayingBuildingBik = (char*)0x0;
            DAT_00b96108::instance = 0;
            DAT_00b95b68::instance = 0;
            if ((DAT_GameCore::instance.activeMenuTab.tabType != OpenSHC::UI::Enums::BASMTT_PEASANT)
                && (((int)DAT_GameCore::instance.activeMenuTab.tabType < 0x47
                    || (0x4f < (int)DAT_GameCore::instance.activeMenuTab.tabType)))) {
                _ptrToSelectedBuildingType
                    = &DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                           .buildingType;
                if ((DAT_RenderingDefinedData::instance.BuildingHelpArray[(short)DAT_BuildingsState::instance
                             .buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                             .buildingType]
                        != (char const*)0x0)
                    && (BVar4 = MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextEditorState_Func::loadAndParseHelpFile, DAT_TextEditorState::ptr)(
                            DAT_RenderingDefinedData::instance.BuildingHelpArray[(short)DAT_BuildingsState::instance
                                    .buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                                    .buildingType]),
                        BVar4 != FALSE)) {
                    DAT_BuildingsState::instance.field24_0x18e04c = (undefined4)(DAT_RenderingDefinedData::instance
                            .BuildingHelpArray[(short)*_ptrToSelectedBuildingType]);
                }
                if (DAT_RenderingDefinedData::instance.BuildingTgxSketchArray[(short)*_ptrToSelectedBuildingType]
                    != (char const*)0x0) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                        DAT_RenderingDefinedData::instance.BuildingTgxSketchArray[(short)*_ptrToSelectedBuildingType]);
                    DAT_00b96108::instance = 1;
                }
                if (DAT_RenderingDefinedData::instance.BuildingBikArray[(short)*_ptrToSelectedBuildingType]
                    != (char const*)0x0) {
                    MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName,
                        DAT_ResourceManager::ptr)(OpenSHC::IO::FRT_BINKS,
                        (char const*)((int)(DAT_RenderingDefinedData::instance
                                .BuildingBikArray[(short)*_ptrToSelectedBuildingType])));
                    BVar4 = MACRO_CALL_MEMBER(
                        OpenSHC::IO::ResourceManager_Func::doesFileOfActiveResourceExist, DAT_ResourceManager::ptr)();
                    if ((BVar4 != FALSE) && (DAT_GameCore::instance.isBinkVideoPlaying == 0)) {
                        DAT_BuildingsState::instance.DAT_CurrentlyPlayingBuildingBik
                            = DAT_RenderingDefinedData::instance.BuildingBikArray[(short)*_ptrToSelectedBuildingType];
                        MACRO_CALL_MEMBER(
                            OpenSHC::Rendering::Bink::BinkControlClass_Func::playBINK, DAT_BinkControlState::ptr)(0,
                            DAT_BuildingsState::instance.DAT_CurrentlyPlayingBuildingBik, 1, 0,
                            DAT_MenuHandlerState::instance.x + 0x23b, DAT_MenuHandlerState::instance.y + 0x1d1, 1);
                        DAT_BuildingsState::instance.DAT_IsBuildingOrPeasantBinkPlaying = TRUE;
                    }
                }
                MACRO_CALL(OpenSHC::UI::Helpers_Func::HandleBuildingSelectionSpeech)(_buildingIndex);
            }
            _menuTab = DAT_GameCore::instance.activeMenuTab;
            _playerId = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .timeTaxesOrRationsChange = 0;
            switch (_menuTab.tabType) {
            case OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM:
                MACRO_CALL(OpenSHC::UI::Helpers_Func::SetEnoughGoldForRequestedUnitToTrueUnk)();
                break;
            case OpenSHC::UI::Enums::BASMTT_KEEP_OR_MPMENU_IPX:
                _currentPlayerGold = DAT_GameState::instance.playerDataArray[_playerId].currentResources[0xf];
                iVar5 = DAT_GameState::instance.playerDataArray[_playerId].marketGold
                    + (int)DAT_GameState::instance.playerDataArray[_playerId].beforeLastMonthsGold;
                if (iVar5 + 0x28 < _currentPlayerGold) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_TAXES_INCREASE1);
                } else if (iVar5 < _currentPlayerGold) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_TAXES_INCREASE2);
                } else if (_currentPlayerGold < iVar5 + -0x28) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_TAXES_DECREASE2);
                } else if (_currentPlayerGold < iVar5) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_TAXES_DECREASE1);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_TAXES_CONSTANT);
                }
                break;
            case OpenSHC::UI::Enums::BASMTT_INN_OR_MPMMENU_UNK:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    OpenSHC::Audio::SFX::SEID_INN);
                break;
            case OpenSHC::UI::Enums::BASMTT_GRANARY_OR_MPMENU_TCPIP:
                if (DAT_GameState::instance.playerDataArray[_playerId].rationsSetting != 0) {
                    if (DAT_GameState::instance.playerDataArray[_playerId].totalFood < 1) {
                        /*
                          "The granary is empty sire"
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            "food_warning5.wav");
                    } else {
                        iVar6 = (int)DAT_GameState::instance.playerDataArray[_playerId].foodStorageLevelLastLastMonth;
                        iVar5 = DAT_GameState::instance.playerDataArray[_playerId].foodStorageLevel;
                        if (iVar6 < iVar5) {
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                                OpenSHC::Audio::SFX::SEID_FOOD_GROWING);
                        } else if (iVar5 < iVar6) {
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                                OpenSHC::Audio::SFX::SEID_FOOD_FALLING);
                        }
                    }
                }
                break;
            case OpenSHC::UI::Enums::BASMTT_FLETCHER:
            case OpenSHC::UI::Enums::BASMTT_BLACKSMITH:
            case OpenSHC::UI::Enums::BASMTT_POLETURNER:
                DAT_GameState::instance.playerDataArray[_playerId].weaponRelated
                    = (int)(short)DAT_BuildingsState::instance
                          .buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                          .producedItemType;
                break;
            case OpenSHC::UI::Enums::BASMTT_ENGINEERSGUILD:
                MACRO_CALL(OpenSHC::UI::Helpers_Func::CheckIfEnoughGoldForLadderman)();
                break;
            case OpenSHC::UI::Enums::BASMTT_TUNNELERSGUILD:
                MACRO_CALL(OpenSHC::UI::Helpers_Func::CheckIfEnoughGoldForTunneler)();
                break;
            case OpenSHC::UI::Enums::BASMTT_OILSMELTER:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    (OpenSHC::Audio::SFX::SoundEffectID)OpenSHC::Audio::SFX::SEID_UNKNOWN_0x3D);
                break;
            case OpenSHC::UI::Enums::BASMTT_DAIRYFARM:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    (OpenSHC::Audio::SFX::SoundEffectID)(OpenSHC::Audio::SFX::SEID_ARROW_BOUNCE
                        | OpenSHC::Audio::SFX::SEID_INN));
                break;
            case OpenSHC::UI::Enums::BASMTT_MILL:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    (OpenSHC::Audio::SFX::SoundEffectID)OpenSHC::Audio::SFX::SEID_MILL);
                break;
            case OpenSHC::UI::Enums::BASMTT_STABLES:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    (OpenSHC::Audio::SFX::SoundEffectID)(OpenSHC::Audio::SFX::SEID_ARROW_BOUNCE
                        | OpenSHC::Audio::SFX::SEID_DRAWBRIDGE_RAISED));
                break;
            case OpenSHC::UI::Enums::BASMTT_CHAPEL_AND_CHURCH:
                BVar2 = DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                            .buildingType;
                if (BVar2 == OpenSHC::Map::Buildings::BT_CHAPEL) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_CHAPEL_BELL);
                LAB_00446f2e:
                    pcVar8 = "wedding_sketch.tgx";
                } else if (BVar2 == OpenSHC::Map::Buildings::BT_CHURCH) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_CHURCH_BELL);
                    pcVar8 = "wedding_sketch.tgx";
                } else {
                    if (BVar2 != OpenSHC::Map::Buildings::BT_CATHEDRAL)
                        goto LAB_00446f2e;
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_CATHEDRAL_BELL);
                    pcVar8 = "wedding_sketch.tgx";
                }
                goto LAB_004475c3;
            case OpenSHC::UI::Enums::BASMTT_MERCENARYPOST:
                MACRO_CALL(OpenSHC::UI::Helpers_Func::DisableMercPostPortraits)();
                break;
            case OpenSHC::UI::Enums::BASMTT_GALLOWS:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    OpenSHC::Audio::SFX::SEID_GALLOWS);
                break;
            case OpenSHC::UI::Enums::BASMTT_PEASANT:
                pUVar1 = &DAT_UnitsState::instance.units[DAT_BuildingsState::instance.menuSelectedUnitID].unitType;
                DAT_00b95b6c::instance = 0xffffffff;
                if ((*pUVar1 == OpenSHC::Map::Units::UT_JESTER) && ((int)DAT_GameCore::instance.field33_0x90 < 3)) {
                    DAT_GameCore::instance.field33_0x90 = DAT_GameCore::instance.field33_0x90 + 1;
                }
                DAT_GameState::instance.mapAndTime.drunkenManStatus
                    = DAT_GameState::instance.mapAndTime.drunkenManStatus + 1;
                if (0x1f < DAT_GameState::instance.mapAndTime.drunkenManStatus) {
                    DAT_GameState::instance.mapAndTime.drunkenManStatus = 0;
                }
                if (DAT_RenderingDefinedData::instance.ChimpTgxArray[(short)*pUVar1] != (char const*)0x0) {
                    MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName,
                        DAT_ResourceManager::ptr)(OpenSHC::IO::FRT_GFX,
                        (char const*)((int)(DAT_RenderingDefinedData::instance.ChimpTgxArray[(short)*pUVar1])));
                    BVar4 = MACRO_CALL_MEMBER(
                        OpenSHC::IO::ResourceManager_Func::doesFileOfActiveResourceExist, DAT_ResourceManager::ptr)();
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    if (BVar4 == FALSE) {
                        pcVar8 = "chimp00_null.tgx";
                    } else {
                        pcVar8 = DAT_RenderingDefinedData::instance.ChimpTgxArray[(short)*pUVar1];
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(pcVar8);
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                    DAT_RenderingDefinedData::instance.ChimpTgxSketchArray[(short)*pUVar1]);
                if ((DAT_RenderingDefinedData::instance.ChimpHelpArray[(short)*pUVar1] != (char const*)0x0)
                    && (BVar4 = MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextEditorState_Func::loadAndParseHelpFile, DAT_TextEditorState::ptr)(
                            DAT_RenderingDefinedData::instance.ChimpHelpArray[(short)*pUVar1]),
                        BVar4 != FALSE)) {
                    DAT_BuildingsState::instance.field24_0x18e04c
                        = (undefined4)(DAT_RenderingDefinedData::instance.ChimpHelpArray[(short)*pUVar1]);
                }
                if (DAT_RenderingDefinedData::instance.ChimpBikArray[(short)*pUVar1] != (char const*)0x0) {
                    MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName,
                        DAT_ResourceManager::ptr)(OpenSHC::IO::FRT_BINKS,
                        (char const*)((int)(DAT_RenderingDefinedData::instance.ChimpBikArray[(short)*pUVar1])));
                    BVar4 = MACRO_CALL_MEMBER(
                        OpenSHC::IO::ResourceManager_Func::doesFileOfActiveResourceExist, DAT_ResourceManager::ptr)();
                    if ((BVar4 != FALSE) && (DAT_GameCore::instance.isBinkVideoPlaying == 0)) {
                        DAT_BuildingsState::instance.DAT_CurrentlyPlayingBuildingBik
                            = DAT_RenderingDefinedData::instance.ChimpBikArray[(short)*pUVar1];
                        MACRO_CALL_MEMBER(
                            OpenSHC::Rendering::Bink::BinkControlClass_Func::playBINK, DAT_BinkControlState::ptr)(0,
                            DAT_BuildingsState::instance.DAT_CurrentlyPlayingBuildingBik, 1, 0,
                            DAT_MenuHandlerState::instance.x + 0x23b, DAT_MenuHandlerState::instance.y + 0x1d1, 1);
                        DAT_BuildingsState::instance.DAT_IsBuildingOrPeasantBinkPlaying = TRUE;
                    }
                }
                INT_00b96124::instance = 0;
                break;
            case OpenSHC::UI::Enums::BASMTT_STATUS_OVERVIEW:
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                if (DAT_GameCore::instance.selectedLordTypeUnk == 0) {
                    pcVar8 = "shield1.tgx";
                } else {
                    pcVar8 = "shield2.tgx";
                }
                goto LAB_004475c3;
            case OpenSHC::UI::Enums::BASMTT_STATUS_POPULARITY:
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("popularity_sketch.tgx");
                iVar5 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .popularity;
                iVar6 = iVar5 >> 0x1f;
                iVar7 = iVar5 / 100 + iVar6;
                iVar5 = iVar7 - iVar6;
                DAT_00b96108::instance = 1;
                if (iVar5 == 100) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_POP_POPULARITY1);
                } else if (iVar7 == iVar6) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_POP_POPULARITY8);
                } else if (iVar5 < 0x14) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_POP_POPULARITY7);
                } else if (iVar5 < 0x28) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_POP_POPULARITY6);
                } else if (iVar5 < 0x32) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_POP_POPULARITY5);
                } else if (iVar5 < 0x3c) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_POP_POPULARITY4);
                } else if (iVar5 < 0x50) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_POP_POPULARITY3);
                } else if (iVar5 < 100) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_POP_POPULARITY2);
                }
                break;
            case OpenSHC::UI::Enums::BASMTT_STATUS_FEARFACTOR:
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("fearfpos.tgx");
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("fearfneg.tgx");
                iVar5 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .fearFactorLevel;
                if (iVar5 != 0) {
                    if (iVar5 < -4) {
                        /*
                          "You are truly the cruelest tyrant in the kingdom your lordship"
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            "general_fear1.wav");
                    } else if (iVar5 == -4) {
                        /*
                          "The people tremble at the very mention of your name sire"
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            "general_fear2.wav");
                    } else if (iVar5 == -3) {
                        /*
                          "The people are very scared of you my liege"
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            "general_fear3.wav");
                    } else if (iVar5 == -2) {
                        /*
                          "The people are frightened of you my lord"
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            "general_fear4.wav");
                    } else if (iVar5 == -1) {
                        /*
                          "The people are a little afraid of you my lord"
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            "general_fear5.wav");
                    } else if (iVar5 == 1) {
                        /*
                          "The people trust you my lord"
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            "general_fear6.wav");
                    } else if (iVar5 == 2) {
                        /*
                          "The people are not afraid of you at all my lord"
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            "general_fear7.wav");
                    } else if (iVar5 == 3) {
                        /*
                          "The people think you are fantastic liege"
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            "general_fear9.wav");
                    } else if (iVar5 == 4) {
                        /*
                          "The people think you are really really nice sire"
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            "general_fear8.wav");
                    } else if (4 < iVar5) {
                        /*
                          "You are worshipped as the kindest man in all the kingdom my liege"
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            "general_fear10.wav");
                    }
                }
                break;
            case OpenSHC::UI::Enums::BASMTT_STATUS_POPULATION:
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("popgraph.tgx");
                pcVar8 = "population_sketch.tgx";
                goto LAB_004475c3;
            case OpenSHC::UI::Enums::BASMTT_STATUS_FOOD:
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("food_sketch.tgx");
                DAT_00b96108::instance = 1;
                break;
            case OpenSHC::UI::Enums::BASMTT_STATUS_ARMY:
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("armysbar.tgx");
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("armybar.tgx");
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("armylbd.tgx");
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("armyrbd.tgx");
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("armys1.tgx");
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("armys2.tgx");
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("armys3.tgx");
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("armys4.tgx");
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("armys5.tgx");
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("armys6.tgx");
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("armys7.tgx");
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("armys8.tgx");
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("armys9.tgx");
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("armys10.tgx");
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("armys11.tgx");
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("armys12.tgx");
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("armys13.tgx");
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("armys14.tgx");
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("armys15.tgx");
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("armys16.tgx");
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("armys17.tgx");
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("armys18.tgx");
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("armys19.tgx");
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("armys20.tgx");
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("armys21.tgx");
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("armys22.tgx");
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("armys23.tgx");
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("armys24.tgx");
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("armys25.tgx");
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("armys26.tgx");
                MACRO_CALL(OpenSHC::UI::Helpers_Func::CountPlayerUnitsByType)();
                break;
            case OpenSHC::UI::Enums::BASMTT_STATUS_RELIGION:
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("churchs.tgx");
                pcVar8 = "religion_sketch.tgx";
            LAB_004475c3:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)(pcVar8);
                break;
            case OpenSHC::UI::Enums::BASMTT_CESSPIT:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    OpenSHC::Audio::SFX::SEID_FLIES);
                break;
            case OpenSHC::UI::Enums::BASMTT_DUNGEON:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    OpenSHC::Audio::SFX::SEID_DUNGEON);
                break;
            case OpenSHC::UI::Enums::BASMTT_STRETCHINGRACK:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    OpenSHC::Audio::SFX::SEID_STRETCHING_RACK);
                break;
            case OpenSHC::UI::Enums::BASMTT_CHOPPINGBLOCK:
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    OpenSHC::Audio::SFX::SEID_PIKE_KILL);
            }
            if (DAT_BuildingsState::instance.field24_0x18e04c != 0) {
                DAT_BuildingsState::instance.field25_0x18e050
                    = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::findOrAddHelpSectionName,
                        DAT_TextEditorState::ptr)((char*)DAT_BuildingsState::instance.field24_0x18e04c);
            }
            DAT_WindowAndDirectDraw::instance.field37_0xdc = 1;
        }

    }
}
}
