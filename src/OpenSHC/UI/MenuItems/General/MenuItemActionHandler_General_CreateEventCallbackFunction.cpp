#include "../General.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Audio::SFX::SoundEffectID;
        using OpenSHC::Commands::MappersEnum;
        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::Map::Buildings::BuildingTypeShort;
        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::Instructions::UnitMatchSpeedEnum;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Type propagation algorithm not settling
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
        // FUNCTION: STRONGHOLDCRUSADER 0x004C1770
        void General::MenuItemActionHandler_General_CreateEventCallbackFunction(int param_1, ...)
        {
            short sVar1;
            BuildingTypeShort BVar2;
            char* pcVar3;
            BOOLEnum BVar4;
            dword dVar5;
            dword dVar6;
            int iVar7;
            dword _param_1;
            uint x1;
            int unitSelectionIndex;
            uint y1;
            int iVar8;
            char** ppcVar9;
            char* pcVar10;
            dword dStack_4;
            iVar7 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            iVar8 = DAT_MapPropertiesState::instance.invasionEventContent.field49_0xa8;
            unitSelectionIndex = 0;
            switch (param_1) {
            case 9:
            case 0xdd:
                DAT_MapPropertiesState::instance.invasionEventContent.crusaderArabian = 0;
                return;
            case 10:
            case 0xde:
                DAT_MapPropertiesState::instance.invasionEventContent.crusaderArabian = 1;
                return;
            case 0xb:
                DAT_MapPropertiesState::instance.invasionEventContent.crusaderArabian = 2;
                return;
            case 0xc:
                DAT_MapPropertiesState::instance.invasionEventContent.crusaderArabian = 3;
                return;
            case 0xd:
            case 0xe:
            case 0xf:
            case 0x10:
            case 0x11:
            case 0x12:
            case 0x13:
            case 0x14:
            case 0x15:
            case 0x16:
            case 0x18:
            case 0x19:
            case 0x1a:
            case 0x1b:
            case 0x1c:
            case 0x1d:
            case 0x1e:
            case 0x1f:
            case 0x20:
            case 0x21:
            case 0x22:
            case 0x23:
            case 0x26:
            case 0x27:
            case 0x28:
            case 0x29:
            case 0x2a:
            case 0x2b:
            case 0x2c:
            case 0x2d:
            case 0x2f:
            case 0x30:
            case 0x31:
            case 0x32:
            case 0x33:
            case 0x34:
            case 0x35:
            case 0x36:
            case 0x37:
            case 0x38:
            case 0x39:
            case 0x3a:
            case 0x3b:
            case 0x3c:
            case 0x3d:
            case 0x3e:
            case 0x3f:
            case 0x40:
            case 0x41:
            case 0x42:
            case 0x43:
            case 0x44:
            case 0x45:
            case 0x46:
            case 0x47:
            case 0x48:
            case 0x49:
            case 0x4a:
            case 0x4b:
            case 0x4c:
            case 0x4d:
            case 0x4e:
            case 0x4f:
            case 0x50:
            case 0x51:
            case 0x52:
            case 0x53:
            case 0x54:
            case 0x55:
            case 0x56:
            case 0x58:
            case 0x59:
            case 0x5a:
            case 0x5b:
            case 0x5c:
            case 0x5d:
            case 0x5e:
            case 0x5f:
            case 0x60:
            case 0x61:
            case 0x62:
            case 99:
            case 100:
            case 0x65:
            case 0x66:
            case 0x67:
            case 0x68:
            case 0x69:
            case 0x6a:
            case 0x6b:
            case 0x6c:
            case 0x6d:
            case 0x6e:
            case 0x6f:
            case 0x70:
            case 0x71:
            case 0x72:
            case 0x73:
            case 0x74:
            case 0x75:
            case 0x76:
            case 0x77:
            case 0x78:
            case 0x79:
            case 0x7a:
            case 0x7b:
            case 0x7c:
            case 0x7d:
            case 0x7e:
            case 0x7f:
            case 0x80:
            case 0x81:
            case 0x82:
            case 0x83:
            case 0x84:
            case 0x86:
            case 0x87:
            case 0x88:
            case 0x89:
            case 0x8a:
            case 0x8c:
            case 0x8d:
            case 0x8e:
            case 0x93:
            case 0x97:
            case 0x98:
            case 0x99:
            case 0x9a:
            case 0x9b:
            case 0x9c:
            case 0x9d:
            case 0x9e:
            case 0x9f:
            case 0xa0:
            case 0xa1:
            case 0xa2:
            case 0xa3:
            case 0xa4:
            case 0xa5:
            case 0xa6:
            case 0xa7:
            case 0xa8:
            case 0xa9:
            case 0xaa:
            case 0xab:
            case 0xac:
            case 0xad:
            case 0xae:
            case 0xaf:
            case 0xb0:
            case 0xb1:
            case 0xb2:
            case 0xb4:
            case 0xb5:
            case 0xb6:
            case 0xb7:
            case 0xb8:
            case 0xb9:
            case 0xba:
            case 0xbb:
            case 0xbc:
            case 0xbd:
            case 0xbe:
            case 0xbf:
            case 0xc0:
            case 0xc1:
            case 0xc2:
            case 0xc3:
            case 0xc4:
            case 0xc5:
            case 0xc6:
            case 199:
            case 200:
            case 0xc9:
            case 0xca:
            case 0xcb:
            case 0xcc:
            case 0xcd:
            case 0xce:
            case 0xcf:
            case 0xd0:
            case 0xd1:
            case 0xd2:
            case 0xd3:
            case 0xd5:
            case 0xd6:
            case 0xd7:
            case 0xd8:
            case 0xd9:
            case 0xda:
            case 0xdb:
            case 0xdc:
                return;
            case 0x17:
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                    DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_TRIGGER_EVENT);
                return;
            case 0x25:
                dStack_4 = _param_1;
                switch (DAT_MapPropertiesState::instance.invasionEventContent.field44_0xa0) {
                case 0x8b:
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .someCount48 = 0x18;
                    iVar8 = DAT_GameState::instance.playerDataArray[iVar7].popularity;
                    if (6000 < iVar8) {
                        DAT_GameState::instance.playerDataArray[iVar7].popularity = (iVar8 + -6000) / 2 + 6000;
                    }
                    MACRO_CALL_MEMBER(
                        OpenSHC::Game::GameStateStructures_Func::spawnPoisonCloudsAtRandomStorageOrArmyBuilding,
                        DAT_GameState::ptr)(iVar7, DAT_MapPropertiesState::instance.invasionEventContent.field49_0xa8);
                    pcVar10 = "Random_Events2.wav";
                    iVar8 = 2;
                    ppcVar9 = DAT_MissionAestheticsDefinedData::instance.field1_0x4;
                    break;
                case 0x8c:
                case 0x8d:
                case 0x8e:
                case 0x8f:
                case 0x90:
                case 0x93:
                case 0x95:
                case 0x96:
                case 0x97:
                case 0x98:
                case 0x99:
                case 0x9a:
                case 0x9b:
                case 0x9c:
                case 0x9d:
                case 0x9e:
                case 0x9f:
                case 0xa0:
                case 0xa1:
                case 0xa2:
                case 0xa3:
                case 0xa4:
                case 0xa5:
                case 0xa6:
                case 0xa7:
                case 0xa8:
                case 0xa9:
                case 0xaa:
                case 0xab:
                case 0xac:
                case 0xad:
                case 0xae:
                case 0xaf:
                case 0xb0:
                case 0xb1:
                case 0xb2:
                    goto switchD_004c1bae_caseD_8c;
                case 0x91:
                    iVar8 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::findRecentOrSignpostSpawnLocation,
                        DAT_TribesState::ptr)(&dStack_4, (uint*)&param_1);
                    if ((iVar8 == 0)
                        || (BVar4 = MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::xyAreValid,
                                DAT_ViewportRenderState::ptr)(dStack_4, (uint)((int)(param_1))),
                            iVar8 = DAT_GameSynchronyState::instance.currentPlayerSlotID, BVar4 == FALSE))
                        goto switchD_004c1bae_caseD_8c;
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .someCount49 = 0xc;
                    iVar7 = DAT_GameState::instance.playerDataArray[iVar8].popularity;
                    if (6000 < iVar7) {
                        DAT_GameState::instance.playerDataArray[iVar8].popularity = (iVar7 + -6000) / 2 + 6000;
                    }
                    iVar8 = 0;
                    if (0 < DAT_MapPropertiesState::instance.invasionEventContent.field49_0xa8) {
                        do {
                            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::findRecentOrSignpostSpawnLocation,
                                DAT_TribesState::ptr)(&dStack_4, (uint*)&param_1);
                            dVar5 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::createAnimal,
                                DAT_TribesState::ptr)(OpenSHC::Commands::M_MAPPER_LION, (uint)((int)(dStack_4)),
                                (uint)((int)(param_1)),
                                (int)((int)((uint)
                                    * (byte*)(DAT_ViewportRenderState::instance.translationMatrix[param_1].addXgetTile
                                        + 0x1d32c38 + dStack_4))));
                            MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::setSpawnMoment,
                                DAT_MinimapViewState::ptr)(dStack_4, param_1);
                            iVar7 = DAT_MapPropertiesState::instance.invasionEventContent.field49_0xa8;
                            iVar8 = iVar8 + 1;
                            DAT_TribesState::instance.tribes[dVar5].unknownBool02 = 0;
                            DAT_TribesState::instance.tribes[dVar5].unknownBool01 = 1;
                        } while (iVar8 < iVar7);
                    }
                    pcVar10 = "Random_Events8.wav";
                    iVar8 = 8;
                    ppcVar9 = DAT_MissionAestheticsDefinedData::instance.field7_0x1c;
                    break;
                case 0x92:
                    BVar4 = MACRO_CALL_MEMBER(
                        OpenSHC::Game::GameStateStructures_Func::hasAnySignpost, DAT_GameState::ptr)();
                    if (BVar4 == FALSE)
                        goto switchD_004c1bae_caseD_8c;
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .someCount50 = 0x10;
                    DAT_TroopValueState::instance.attackInfo.inv_count
                        = DAT_TroopValueState::instance.attackInfo.inv_count + 1;
                    if (0x31 < DAT_TroopValueState::instance.attackInfo.inv_count) {
                        DAT_TroopValueState::instance.attackInfo.inv_count = 1;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::initializeAttackWaveSlot,
                        DAT_TroopValueState::ptr)(DAT_TroopValueState::instance.attackInfo.inv_count, 0);
                    DAT_TroopValueState::instance.attackInfo
                        .attackWavePlayerIDArray[DAT_TroopValueState::instance.attackInfo.inv_count] = 8;
                    iVar8
                        = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::pickRandomAccessibleSignpostEntry,
                            DAT_GameState::ptr)();
                    dVar5 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::createTribeWithSpawnedUnit,
                        DAT_TribesState::ptr)(0, 9, DAT_GameState::instance.mapAndTime.signpostEntryData[iVar8].x,
                        DAT_GameState::instance.mapAndTime.signpostEntryData[iVar8].y, 8,
                        OpenSHC::Map::Units::UT_E_MACE,
                        DAT_MapPropertiesState::instance.invasionEventContent.field49_0xa8 + 1);
                    MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::setSpawnMoment, DAT_MinimapViewState::ptr)(
                        DAT_GameState::instance.mapAndTime.signpostEntryData[iVar8].x,
                        DAT_GameState::instance.mapAndTime.signpostEntryData[iVar8].y);
                    if (0 < DAT_TribesState::instance.tribes[dVar5].size) {
                        do {
                            iVar8 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe,
                                DAT_TribesState::ptr)(dVar5, unitSelectionIndex);
                            sVar1 = DAT_TribesState::instance.tribes[dVar5].size;
                            unitSelectionIndex = unitSelectionIndex + 1;
                            DAT_UnitsState::instance.units[iVar8].calculatedOwnerPlayerIndex = 5;
                            DAT_UnitsState::instance.units[iVar8].logicalState = OpenSHC::Map::Units::ULS_NORMAL;
                        } while (unitSelectionIndex < sVar1);
                    }
                    pcVar10 = "Random_Events9.wav";
                    iVar8 = 9;
                    ppcVar9 = DAT_MissionAestheticsDefinedData::instance.field8_0x20;
                    break;
                case 0x94:
                    BVar4 = MACRO_CALL_MEMBER(
                        OpenSHC::Game::GameStateStructures_Func::hasAnySignpost, DAT_GameState::ptr)();
                    if (BVar4 == FALSE)
                        goto switchD_004c1bae_caseD_8c;
                    iVar8
                        = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::pickRandomAccessibleSignpostEntry,
                            DAT_GameState::ptr)();
                    dVar5 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::spawnUnitsAroundLocation,
                        DAT_TribesState::ptr)(3, DAT_GameState::instance.mapAndTime.signpostEntryData[iVar8].x,
                        DAT_GameState::instance.mapAndTime.signpostEntryData[iVar8].y,
                        (int)((int)(DAT_GameSynchronyState::instance.currentPlayerSlotID)),
                        OpenSHC::Map::Units::UT_E_ARCHER,
                        DAT_MapPropertiesState::instance.invasionEventContent.field49_0xa8);
                    param_1 = dVar5;
                    dVar6 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::spawnUnitsAroundLocation,
                        DAT_TribesState::ptr)(0xc, DAT_GameState::instance.mapAndTime.signpostEntryData[iVar8].x,
                        DAT_GameState::instance.mapAndTime.signpostEntryData[iVar8].y,
                        (int)((int)(DAT_GameSynchronyState::instance.currentPlayerSlotID)),
                        OpenSHC::Map::Units::UT_E_MONK, 1);
                    dStack_4 = dVar6;
                    MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::setSpawnMoment, DAT_MinimapViewState::ptr)(
                        DAT_GameState::instance.mapAndTime.signpostEntryData[iVar8].x,
                        DAT_GameState::instance.mapAndTime.signpostEntryData[iVar8].y);
                    DAT_TribesState::instance.tribes[dVar5].field134_0x27a = 0;
                    iVar8 = 0;
                    DAT_TribesState::instance.tribes[dVar6].field134_0x27a = 0;
                    if (0 < DAT_TribesState::instance.tribes[dVar5].size) {
                        do {
                            iVar7 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe,
                                DAT_TribesState::ptr)(param_1, iVar8);
                            sVar1 = DAT_TribesState::instance.tribes[dVar5].size;
                            iVar8 = iVar8 + 1;
                            DAT_UnitsState::instance.units[iVar7].calculatedOwnerPlayerIndex = 8;
                            DAT_UnitsState::instance.units[iVar7].logicalState = OpenSHC::Map::Units::ULS_NORMAL;
                        } while (iVar8 < sVar1);
                    }
                    iVar8 = 0;
                    if (0 < DAT_TribesState::instance.tribes[dVar6].size) {
                        do {
                            iVar7 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe,
                                DAT_TribesState::ptr)(dStack_4, iVar8);
                            sVar1 = DAT_TribesState::instance.tribes[dVar6].size;
                            iVar8 = iVar8 + 1;
                            DAT_UnitsState::instance.units[iVar7].calculatedOwnerPlayerIndex = 8;
                            DAT_UnitsState::instance.units[iVar7].logicalState = OpenSHC::Map::Units::ULS_NORMAL;
                        } while (iVar8 < sVar1);
                    }
                    iVar8
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .keep.id;
                    if (0 < iVar8) {
                        BVar2 = DAT_BuildingsState::instance.buildings[iVar8].buildingType;
                        x1 = 0;
                        y1 = 0;
                        if (BVar2 == OpenSHC::Map::Buildings::BT_MANORHOUSE) {
                            x1 = (int)(short)DAT_BuildingsState::instance.buildings[iVar8].x + 3;
                            y1 = (int)(short)DAT_BuildingsState::instance.buildings[iVar8].y + 8;
                        } else if ((BVar2 == OpenSHC::Map::Buildings::BT_STONEKEEP)
                            || (BVar2 == OpenSHC::Map::Buildings::BT_STRONGHOLD)) {
                            x1 = (int)(short)DAT_BuildingsState::instance.buildings[iVar8].x + 3;
                            y1 = (int)(short)DAT_BuildingsState::instance.buildings[iVar8].y + 3;
                        } else if (BVar2 == OpenSHC::Map::Buildings::BT_KEEPFOUR) {
                            x1 = (int)(short)DAT_BuildingsState::instance.buildings[iVar8].x + 4;
                            y1 = (int)(short)DAT_BuildingsState::instance.buildings[iVar8].y + 4;
                        } else if (BVar2 == OpenSHC::Map::Buildings::BT_KEEPFIVE) {
                            x1 = (int)(short)DAT_BuildingsState::instance.buildings[iVar8].x + 5;
                            y1 = (int)(short)DAT_BuildingsState::instance.buildings[iVar8].y + 5;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction,
                            DAT_TribesState::ptr)(param_1, x1, y1, 0, 0, OpenSHC::Map::Units::Instructions::UMSE_0);
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction,
                            DAT_TribesState::ptr)(dStack_4, x1, y1, 0, 0, OpenSHC::Map::Units::Instructions::UMSE_0);
                    }
                    pcVar10 = "Random_Events11.wav";
                    iVar8 = 0xb;
                    ppcVar9 = DAT_MissionAestheticsDefinedData::instance.field10_0x28;
                    break;
                case 0xb3:
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .someCount51 = 8;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::spreadFireRandomlyToBuildings,
                        DAT_BuildingsState::ptr)(iVar7, iVar8);
                    iVar8 = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::findFirstBuildingOfType, DAT_BuildingsState::ptr)(
                        DAT_GameSynchronyState::instance.currentPlayerSlotID, OpenSHC::Map::Buildings::BT_WELL);
                    if (iVar8 == 0) {
                        iVar8 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findFirstBuildingOfType,
                            DAT_BuildingsState::ptr)(
                            DAT_GameSynchronyState::instance.currentPlayerSlotID, OpenSHC::Map::Buildings::BT_WATERPOT);
                        pcVar10 = "general_message3.wav";
                        ppcVar9 = DAT_MissionAestheticsDefinedData::instance.field14_0x38;
                        if (iVar8 == 0) {
                            iVar8 = 0x11;
                        } else {
                            iVar8 = 0xf;
                        }
                    } else {
                        pcVar10 = "general_message3.wav";
                        iVar8 = 0xf;
                        ppcVar9 = DAT_MissionAestheticsDefinedData::instance.field14_0x38;
                    }
                    break;
                default:
                    goto LAB_004c19d6;
                }
                /*
                  added by script: "There is fire in the castle and we have not built any wells   my Liege!"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_ACTION, iVar8), (char*)((int)(ppcVar9)), pcVar10);
            switchD_004c1bae_caseD_8c:
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
                return;
            case 0x2e:
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                    DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_CREATE_OR_TRIGGER_INVASION);
                return;
            case 0x57:
                DAT_MapPropertiesState::instance.invasionEventContent.crusaderArabian = 4;
                return;
            case 0x85:
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    (int)((int)(SEC_RNG::instance.currentNumber2 % 9)),
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .campground.xEntry
                        * 8,
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .campground.yEntry
                        * 8,
                    (int)((int)((uint)DAT_TileMapState::instance.HeightLayer[DAT_GameState::instance
                            .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .campground.tileEntry])),
                    OpenSHC::Map::Units::UT_JUGGLER);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, (SEC_RNG::instance.currentNumber2 >> 3) % 9,
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .campground.xEntry
                        * 8,
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .campground.yEntry
                        * 8,
                    (UnitType)((int)((uint)DAT_TileMapState::instance.HeightLayer[DAT_GameState::instance
                            .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .campground.tileEntry])),
                    OpenSHC::Map::Units::UT_JUGGLER);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, (SEC_RNG::instance.currentNumber2 >> 6) % 9,
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .campground.xEntry
                        * 8,
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .campground.yEntry
                        * 8,
                    (UnitType)((int)((uint)DAT_TileMapState::instance.HeightLayer[DAT_GameState::instance
                            .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .campground.tileEntry])),
                    OpenSHC::Map::Units::UT_JUGGLER);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, (SEC_RNG::instance.currentNumber2 >> 9) % 9,
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .campground.xEntry
                        * 8,
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .campground.yEntry
                        * 8,
                    (UnitType)((int)((uint)DAT_TileMapState::instance.HeightLayer[DAT_GameState::instance
                            .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .campground.tileEntry])),
                    OpenSHC::Map::Units::UT_FIREEATER);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, (SEC_RNG::instance.currentNumber2 >> 0xc) % 9,
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .campground.xEntry
                        * 8,
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .campground.yEntry
                        * 8,
                    (UnitType)((int)((uint)DAT_TileMapState::instance.HeightLayer[DAT_GameState::instance
                            .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .campground.tileEntry])),
                    OpenSHC::Map::Units::UT_FIREEATER);
                pcVar10 = "Random_Events1.wav";
                iVar8 = 1;
                ppcVar9 = DAT_MissionAestheticsDefinedData::instance.field0_0x0;
                break;
            case 0x8b:
            case 0x91:
            case 0x92:
            case 0x94:
            case 0xb3:
                DAT_MapPropertiesState::instance.invasionEventContent.field44_0xa0 = param_1;
                DAT_MapPropertiesState::instance.invasionEventContent.field49_0xa8 = 1;
                switch (param_1) {
                case 0x8b:
                case 0x91:
                case 0xb3:
                    (*(int*)&DAT_MapPropertiesState::instance.invasionEventContent.padding_0xa4[0]) = 10;
                    break;
                case 0x92:
                case 0x94:
                    (*(int*)&DAT_MapPropertiesState::instance.invasionEventContent.padding_0xa4[0]) = 0x32;
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                        DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_TRIGGER_EVENT_SLIDER);
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                    DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_TRIGGER_EVENT_SLIDER);
                return;
            case 0x8f:
                MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::killEveryFifthTree, DAT_LandscapeState::ptr)();
                pcVar10 = "Random_Events6.wav";
                iVar8 = 6;
                ppcVar9 = DAT_MissionAestheticsDefinedData::instance.field5_0x14;
                break;
            case 0x90:
                iVar8
                    = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::hasAvailableSpawnSlotForWildlifeOrMercs,
                        DAT_TribesState::ptr)();
                if ((iVar8 == 0)
                    || ((iVar8
                        = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findBuildingOfTypeForPlayer,
                            DAT_BuildingsState::ptr)(
                            DAT_GameSynchronyState::instance.currentPlayerSlotID, OpenSHC::Map::Buildings::BT_HOPFARM),
                        iVar8 == 0
                            && (iVar8 = MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Buildings::BuildingsState_Func::findBuildingOfTypeForPlayer,
                                    DAT_BuildingsState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                                    OpenSHC::Map::Buildings::BT_WHEATFARM),
                                iVar8 == 0))))
                    goto LAB_004c19d6;
                DAT_GameState::instance.mapAndTime.eventCountdownRabbitInfestation = 1200;
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::TribesState_Func::spawnWildlifeOrMercAtAvailableSlot, DAT_TribesState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::setSpawnMoment, DAT_MinimapViewState::ptr)(
                    DAT_TribesState::instance.unknownX_01, DAT_TribesState::instance.unknownY_01);
                pcVar10 = "Random_Events7.wav";
                iVar8 = 7;
                ppcVar9 = DAT_MissionAestheticsDefinedData::instance.field6_0x18;
                break;
            case 0x95:
                DAT_GameState::instance.mapAndTime.unitLadyRelated = 1;
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .someCount52 = 0xc;
                if (10000 < DAT_GameState::instance.playerDataArray[iVar7].popularity) {
                    DAT_GameState::instance.playerDataArray[iVar7].popularity = 10000;
                }
                pcVar3 = "Random_Events12.wav";
                ppcVar9 = DAT_MissionAestheticsDefinedData::instance.field11_0x2c;
                /*
                  added by script: "The people rejoice at your forthcoming marriage, Sire."
                 */
                MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_ACTION, 0xc), (char*)((int)(ppcVar9)), pcVar3);
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    OpenSHC::Audio::SFX::SEID_CHAPEL_BELL);
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
                return;
            case 0x96:
                DAT_GameState::instance.mapAndTime.unitJesterRelated = 1;
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .someCount53 = 0x30;
                if (10000 < DAT_GameState::instance.playerDataArray[iVar7].popularity) {
                    DAT_GameState::instance.playerDataArray[iVar7].popularity = 10000;
                }
                pcVar10 = "Random_Events13.wav";
                iVar8 = 0xd;
                ppcVar9 = DAT_MissionAestheticsDefinedData::instance.field12_0x30;
                break;
            case 0xd4:
                /*
                  Invasion
                 */
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::MapPropertiesState_Func::spawnInvasionEventAttackWave, DAT_MapPropertiesState::ptr)();
            case 0x24:
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
                return;
            default:
                break;
            }
            /*
              added by script: "A ‘Travelling Fair’ has come to town, my Lord."
             */
            MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::AIMessageQueue_Func::playEventVideoBik, DAT_VideoBikQueue::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_ACTION, iVar8), (char*)((int)(ppcVar9)), pcVar10);
        LAB_004c19d6:
            MACRO_CALL_MEMBER(
                OpenSHC::UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
        }

    }
}
}
