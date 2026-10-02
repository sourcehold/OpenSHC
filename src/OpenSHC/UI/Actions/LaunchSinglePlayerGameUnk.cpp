#include "../Actions.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/Scenario/BarracksRecruitabilityShort.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/Units/UnitTypeShort.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00b960dc.hpp"
#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapMissionType.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_SH1_SiegeAdvancedMode.hpp"
#include "OpenSHC/Globals/DAT_SiegeInformationArray.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UIDragDropDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/DWORD_00b95b1c.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Commands::GameCommandType;
    using OpenSHC::Map::MapType2;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Map::Units::UnitTypeShort;
    using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
    using OpenSHC::UI::Enums::MenuViewType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

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
    // FUNCTION: STRONGHOLDCRUSADER 0x0042C620
    void Actions::LaunchSinglePlayerGameUnk(int param_1)
    {
        byte(*pabVar1)[10];
        byte* pbVar2;
        char cVar3;
        short* psVar4;
        char* pcVar5;
        BOOLEnum BVar6;
        int iVar7;
        int iVar8;
        int iVar9;
        char* pcVar10;
        int _pointsMultiplier;
        UnitTypeShort* pUVar11;
        uint uVar12;
        MenuViewType menuID;
        int local_7e8;
        undefined4 local_7e4;
        char local_7e0[4];
        char local_7dc[1004];
        char _mapU3StringCopy[1004];
        uint local_4;
        iVar8 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        local_4 = MSVC_SecurityCookie::instance ^ (uint)&local_7e8;
        DAT_GameCore::instance.section1066 = 1;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
            OpenSHC::Commands::GCT_ASK_FOR_SLOT_ASSIGNMENT);
        DAT_MapPropertiesState::instance.SEC_XbowProducible_save = 1;
        DAT_MapPropertiesState::instance.SEC_PikeProducible_save = 1;
        DAT_MapPropertiesState::instance.SEC_SwordProducible_save = 1;
        DAT_MapPropertiesState::instance.SEC_BowProducible_save = 1;
        DAT_MapPropertiesState::instance.SEC_SpearProducible_save = 1;
        DAT_MapPropertiesState::instance.SEC_MaceProducible_save = 1;
        psVar4 = DAT_MapPropertiesState::instance.SEC_MercRecruitable;
        DAT_GameSynchronyState::instance.currentPlayerSlotID = iVar8;
        do {
            (((OpenSHC::Game::Scenario::BarracksRecruitabilityShort*)(psVar4 + -7))->recruitability).archers = 1;
            *psVar4 = 1;
            psVar4 = psVar4 + 1;
        } while ((int)psVar4 < 0x1653df6);
        if (param_1 == 0) {
            pcVar5 = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                DAT_ResourceManager::ptr)(DAT_MenuTextInputState::instance
                    .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                        + DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected + -1]);
            pcVar10 = local_7e0;
            do {
                cVar3 = *pcVar5;
                *pcVar10 = cVar3;
                pcVar5 = pcVar5 + 1;
                pcVar10 = pcVar10 + 1;
            } while (cVar3 != '\0');
            pcVar10 = (char*)((int)&local_7e4 + 3);
            do {
                pcVar5 = pcVar10;
                pcVar10 = pcVar5 + 1;
            } while (pcVar5[1] != '\0');
            strcpy(pcVar5 + 1, ".map");
        } else {
            iVar8 = 0;
            do {
                cVar3 = DAT_GameCore::instance.standaloneFilename[iVar8];
                local_7e0[iVar8] = cVar3;
                iVar8 = iVar8 + 1;
            } while (cVar3 != '\0');
            pcVar10 = (char*)((int)&local_7e4 + 3);
            do {
                pcVar5 = pcVar10;
                pcVar10 = pcVar5 + 1;
            } while (pcVar5[1] != '\0');
            strcpy(pcVar5 + 1, ".map");
            iVar8 = 0;
            do {
                cVar3 = DAT_GameCore::instance.standaloneFilename[iVar8];
                _mapU3StringCopy[iVar8] = cVar3;
                iVar8 = iVar8 + 1;
            } while (cVar3 != '\0');
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::MapPropertiesState_Func::loadMap, DAT_MapPropertiesState::ptr)(local_7e0);
        DAT_GameCore::instance.selectedLordType_2Unk = DAT_GameCore::instance.selectedLordTypeUnk;
        DAT_MapPropertiesState::instance.SEC_XbowProducible_save = 1;
        DAT_GameCore::instance.xbowProducible_logic = 1;
        DAT_MapPropertiesState::instance.SEC_BowProducible_save = 1;
        DAT_GameCore::instance.bowProducible_logic = 1;
        DAT_MapPropertiesState::instance.SEC_PikeProducible_save = 1;
        DAT_GameCore::instance.pikeProducible_logic = 1;
        DAT_MapPropertiesState::instance.SEC_SpearProducible_save = 1;
        DAT_GameCore::instance.spearProducible_logic = 1;
        DAT_MapPropertiesState::instance.SEC_SwordProducible_save = 1;
        DAT_GameCore::instance.swordProducible_logic = 1;
        DAT_MapPropertiesState::instance.SEC_MaceProducible_save = 1;
        DAT_GameCore::instance.maceProducible_logic = 1;
        switch (DAT_MapMissionType::instance) {
        case 0:
            DAT_GameCore::instance.missionDifficulty_0 = DAT_GameState::instance.mapAndTime.difficulty;
            break;
        case 1:
            DAT_GameCore::instance.missionDifficulty_1 = DAT_GameState::instance.mapAndTime.difficulty;
            break;
        case 2:
            DAT_GameCore::instance.missionDifficulty_2 = DAT_GameState::instance.mapAndTime.difficulty;
            break;
        case 3:
            DAT_GameCore::instance.missionDifficulty_3 = DAT_GameState::instance.mapAndTime.difficulty;
        }
        if (DAT_MapMissionType::instance == 2) {
            MACRO_CALL_MEMBER(OpenSHC::Map::MapPropertiesState_Func::createChainedMissionOutcomeEvents,
                DAT_MapPropertiesState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID);
        }
        DAT_GameState::instance.mapAndTime.mercRecruitable[0]
            = (int)DAT_MapPropertiesState::instance.SEC_MercRecruitable[0];
        DAT_GameState::instance.mapAndTime.mercRecruitable[1]
            = (int)DAT_MapPropertiesState::instance.SEC_MercRecruitable[1];
        DAT_GameState::instance.mapAndTime.mercRecruitable[2]
            = (int)DAT_MapPropertiesState::instance.SEC_MercRecruitable[2];
        DAT_GameState::instance.mapAndTime.mercRecruitable[3]
            = (int)DAT_MapPropertiesState::instance.SEC_MercRecruitable[3];
        DAT_GameState::instance.mapAndTime.euroRecruitable[0]
            = (int)DAT_MapPropertiesState::instance.barracksRecruitability.recruitability.archers;
        DAT_GameState::instance.mapAndTime.euroRecruitable[5]
            = (int)DAT_MapPropertiesState::instance.barracksRecruitability.recruitability.swordsmen;
        DAT_GameState::instance.mapAndTime.mercRecruitable[4]
            = (int)DAT_MapPropertiesState::instance.SEC_MercRecruitable[4];
        DAT_GameState::instance.mapAndTime.mercRecruitable[5]
            = (int)DAT_MapPropertiesState::instance.SEC_MercRecruitable[5];
        DAT_GameState::instance.mapAndTime.euroRecruitable[6]
            = (int)DAT_MapPropertiesState::instance.barracksRecruitability.recruitability.knights;
        DAT_GameState::instance.mapAndTime.euroRecruitable[1]
            = (int)DAT_MapPropertiesState::instance.barracksRecruitability.recruitability.crossbowmen;
        DAT_GameState::instance.mapAndTime.euroRecruitable[2]
            = (int)DAT_MapPropertiesState::instance.barracksRecruitability.recruitability.spearmen;
        DAT_GameState::instance.mapAndTime.euroRecruitable[3]
            = (int)DAT_MapPropertiesState::instance.barracksRecruitability.recruitability.pikemen;
        DAT_GameState::instance.mapAndTime.euroRecruitable[4]
            = (int)DAT_MapPropertiesState::instance.barracksRecruitability.recruitability.macemen;
        DAT_GameState::instance.mapAndTime.mercRecruitable[6]
            = (int)DAT_MapPropertiesState::instance.SEC_MercRecruitable[6];
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_0
            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[0] != 0);
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_1_a
            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[1] != 0);
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_1_b
            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[1] != 0);
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_2
            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[2] != 0);
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_a_and_6_b
            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[3] != 0);
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_b
            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[3] != 0);
        if (DAT_GameState::instance.mapAndTime.euroRecruitable[4] != 0) {
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_1_a = 1;
        }
        DAT_GameState::instance.mapAndTime.field2257_0xda8
            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[4] != 0);
        if (DAT_GameState::instance.mapAndTime.euroRecruitable[5] != 0) {
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_a_and_6_b = 1;
        }
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_6_a
            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[5] != 0);
        if (DAT_GameState::instance.mapAndTime.euroRecruitable[6] != 0) {
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_6_a = 1;
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_a_and_6_b = 1;
        }
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_6_c
            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[6] != 0);
        if (param_1 == 0) {
            pcVar10 = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                DAT_ResourceManager::ptr)(DAT_MenuTextInputState::instance
                    .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                        + DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected + -1]);
            pcVar5 = DAT_GameCore::instance.standaloneFilename;
            do {
                cVar3 = *pcVar10;
                *pcVar5 = cVar3;
                pcVar10 = pcVar10 + 1;
                pcVar5 = pcVar5 + 1;
            } while (cVar3 != '\0');
        } else {
            iVar8 = 0;
            do {
                cVar3 = _mapU3StringCopy[iVar8];
                DAT_GameCore::instance.standaloneFilename[iVar8] = cVar3;
                iVar8 = iVar8 + 1;
            } while (cVar3 != '\0');
        }
        DAT_GameState::instance.mapAndTime.unitJesterRelated = 0;
        DAT_GameState::instance.mapAndTime.unitLadyRelated = 0;
        if (DAT_MapMissionType::instance == 2) {
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::UnitsState_Func::triggerDeathAnimationForAllWildlife, DAT_UnitsState::ptr)();
            if (DAT_GameSynchronyState::instance.currentPlayerSlotID == 1) {
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[1] = 1;
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[2] = 2;
            } else {
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[1] = 2;
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[2] = 1;
            }
            if ((DAT_MapMissionType::instance == 2) && (DAT_GameSynchronyState::instance.currentPlayerSlotID == 1)) {
                _pointsMultiplier = 100;
                if (DAT_GameState::instance.mapAndTime.difficulty == 0) {
                    _pointsMultiplier = 66;
                } else if (DAT_GameState::instance.mapAndTime.difficulty == 2) {
                    _pointsMultiplier = 133;
                } else if (DAT_GameState::instance.mapAndTime.difficulty == 3) {
                    _pointsMultiplier = 166;
                }
                DAT_TroopValueState::instance.attackInfo.inv_count
                    = DAT_TroopValueState::instance.attackInfo.inv_count + 1;
                if (0x32 <= DAT_TroopValueState::instance.attackInfo.inv_count) {
                    DAT_TroopValueState::instance.attackInfo.inv_count = 1;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::initializeAttackWaveSlot,
                    DAT_TroopValueState::ptr)(DAT_TroopValueState::instance.attackInfo.inv_count, 1);
                iVar8 = DAT_MapPropertiesState::instance.SEC_Section1067.field0_0x0;
                DAT_TroopValueState::instance.attackInfo
                    .attackWavePlayerIDArray[DAT_TroopValueState::instance.attackInfo.inv_count] = 4;
                iVar8 = iVar8 * _pointsMultiplier;
                pabVar1 = DAT_TroopValueState::instance.attackInfo.someSinglePlayerScore
                    + DAT_TroopValueState::instance.attackInfo.inv_count;
                (*pabVar1)[0] = (*pabVar1)[0]
                    + (((char)(iVar8 / 100) + (char)(iVar8 >> 0x1f)) - (char)((longlong)iVar8 * 0x51eb851f >> 0x3f));
                iVar8 = DAT_MapPropertiesState::instance.SEC_Section1067.field1_0x4 * _pointsMultiplier;
                iVar9 = DAT_MapPropertiesState::instance.SEC_Section1067.field3_0xc * _pointsMultiplier;
                pbVar2 = DAT_TroopValueState::instance.attackInfo
                             .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count]
                    + 1;
                *pbVar2 = *pbVar2
                    + (((char)(iVar8 / 100) + (char)(iVar8 >> 0x1f)) - (char)((longlong)iVar8 * 0x51eb851f >> 0x3f));
                pbVar2 = DAT_TroopValueState::instance.attackInfo
                             .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count]
                    + 2;
                *pbVar2 = *pbVar2
                    + (((char)(iVar9 / 100) + (char)(iVar9 >> 0x1f)) - (char)((longlong)iVar9 * 0x51eb851f >> 0x3f));
                iVar8 = DAT_MapPropertiesState::instance.SEC_Section1067.field2_0x8 * _pointsMultiplier;
                iVar9 = DAT_MapPropertiesState::instance.SEC_Section1067.field4_0x10 * _pointsMultiplier;
                pbVar2 = DAT_TroopValueState::instance.attackInfo
                             .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count]
                    + 3;
                *pbVar2 = *pbVar2
                    + (((char)(iVar8 / 100) + (char)(iVar8 >> 0x1f)) - (char)((longlong)iVar8 * 0x51eb851f >> 0x3f));
                pbVar2 = DAT_TroopValueState::instance.attackInfo
                             .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count]
                    + 4;
                *pbVar2 = *pbVar2
                    + (((char)(iVar9 / 100) + (char)(iVar9 >> 0x1f)) - (char)((longlong)iVar9 * 0x51eb851f >> 0x3f));
                iVar8 = DAT_MapPropertiesState::instance.SEC_Section1067.field5_0x14 * _pointsMultiplier;
                pbVar2 = DAT_TroopValueState::instance.attackInfo
                             .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count]
                    + 8;
                *pbVar2 = *pbVar2
                    + (((char)(iVar8 / 100) + (char)(iVar8 >> 0x1f)) - (char)((longlong)iVar8 * 0x51eb851f >> 0x3f));
            }
        }
        if (DAT_SH1_SiegeAdvancedMode::instance == 0) {
            if (DAT_MapMissionType::instance != 2)
                goto LAB_0042ce38;
            if (DAT_GameSynchronyState::instance.currentPlayerSlotID == 2) {
                iVar8 = 0;
                do {
                    *(int*)((int)DAT_GameState::instance.mapAndTime.startGoods + iVar8 + 100)
                        = (*(int*)((int)DAT_MapPropertiesState::instance.SEC_StartingResources + iVar8 + 100) * 7) / 10;
                    iVar8 = iVar8 + 4;
                } while (iVar8 < 0x50);
                DAT_MapPropertiesState::instance.SEC_Section1067.tunnelersCount
                    = (DAT_MapPropertiesState::instance.SEC_Section1067.tunnelersCount * 7) / 10;
            }
        LAB_0042cc91:
            uVar12 = 1;
            pUVar11 = &DAT_UnitsState::instance.units[1].unitType;
            do {
                if ((pUVar11[-1] != OpenSHC::Map::Units::ULS_INVISIBLE)
                    && (*pUVar11 == OpenSHC::Map::Units::UT_PEASANT)) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::deleteUnit, DAT_UnitsState::ptr)(uVar12);
                }
                pUVar11 = pUVar11 + 0x248;
                uVar12 = uVar12 + 1;
            } while ((int)pUVar11 < 0x165141a);
        } else {
            if (DAT_MapMissionType::instance == 2) {
                DAT_GameState::instance.mapAndTime.siegeInformation.archers = DAT_SiegeInformationArray::instance[0];
                DAT_GameState::instance.mapAndTime.siegeInformation.field1_0x4 = DAT_SiegeInformationArray::instance[1];
                DAT_GameState::instance.mapAndTime.siegeInformation.field3_0xc = DAT_SiegeInformationArray::instance[3];
                DAT_GameState::instance.mapAndTime.siegeInformation.field4_0x10
                    = DAT_SiegeInformationArray::instance[4];
                DAT_GameState::instance.mapAndTime.siegeInformation.field6_0x18
                    = DAT_SiegeInformationArray::instance[6];
                DAT_GameState::instance.mapAndTime.siegeInformation.field7_0x1c
                    = DAT_SiegeInformationArray::instance[7];
                DAT_GameState::instance.mapAndTime.siegeInformation.field9_0x24
                    = DAT_SiegeInformationArray::instance[9];
                DAT_GameState::instance.mapAndTime.siegeInformation.field11_0x2c
                    = DAT_SiegeInformationArray::instance[0xb];
                DAT_GameState::instance.mapAndTime.siegeInformation.field2_0x8 = DAT_SiegeInformationArray::instance[2];
                DAT_GameState::instance.mapAndTime.siegeInformation.field12_0x30
                    = DAT_SiegeInformationArray::instance[0xc];
                DAT_GameState::instance.mapAndTime.siegeInformation.field13_0x34
                    = DAT_SiegeInformationArray::instance[0xd];
                DAT_GameState::instance.mapAndTime.siegeInformation.field5_0x14
                    = DAT_SiegeInformationArray::instance[5];
                DAT_GameState::instance.mapAndTime.siegeInformation.field14_0x38
                    = DAT_SiegeInformationArray::instance[0xe];
                DAT_GameState::instance.mapAndTime.siegeInformation.field15_0x3c
                    = DAT_SiegeInformationArray::instance[0xf];
                DAT_GameState::instance.mapAndTime.siegeInformation.field8_0x20
                    = DAT_SiegeInformationArray::instance[8];
                DAT_GameState::instance.mapAndTime.siegeInformation.field16_0x40
                    = DAT_SiegeInformationArray::instance[0x10];
                DAT_GameState::instance.mapAndTime.siegeInformation.field17_0x44
                    = DAT_SiegeInformationArray::instance[0x11];
                DAT_GameState::instance.mapAndTime.siegeInformation.field10_0x28
                    = DAT_SiegeInformationArray::instance[10];
                DAT_GameState::instance.mapAndTime.siegeInformation.field18_0x48
                    = DAT_SiegeInformationArray::instance[0x12];
                DAT_GameState::instance.mapAndTime.siegeInformation.field19_0x4c
                    = DAT_SiegeInformationArray::instance[0x13];
                DAT_MapPropertiesState::instance.SEC_Section1067.tunnelersCount
                    = DAT_SiegeInformationArray::instance[10];
                goto LAB_0042cc91;
            }
        LAB_0042ce38:
            if (DAT_MapMissionType::instance == 3) {
                if (DAT_GameState::instance.mapAndTime.difficulty != 0) {
                    BVar6 = MACRO_CALL_MEMBER(
                        OpenSHC::Map::MapPropertiesState_Func::mapHasCertainEvent, DAT_MapPropertiesState::ptr)();
                    if (BVar6 == FALSE) {
                        iVar9 = 0;
                        iVar8 = 0;
                        local_7e8 = 0;
                        psVar4 = &DAT_UnitsState::instance.units[1].dying;
                        do {
                            if ((((psVar4[-0x10a] == OpenSHC::Map::Units::ULS_NORMAL) && (*psVar4 == 0))
                                    && (psVar4[-0x105] == DAT_GameSynchronyState::instance.currentPlayerSlotID))
                                && (psVar4[2] != 0)) {
                                iVar7
                                    = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::getValueOfTroopType,
                                        DAT_TroopValueState::ptr)((OpenSHC::Map::Units::UnitType)((int)psVar4[-0x109]));
                                iVar9 = iVar9 + iVar7;
                            }
                            psVar4 = psVar4 + 0x248;
                        } while ((int)psVar4 < 0x165162c);
                        if (DAT_GameState::instance.mapAndTime.difficulty == 1) {
                            local_7e8 = 4;
                            iVar7 = (int)(iVar9 * -3 + (iVar9 * -3 >> 0x1f & 3U)) >> 2;
                        LAB_0042cf15:
                            iVar9 = iVar9 + iVar7;
                        } else if (DAT_GameState::instance.mapAndTime.difficulty == 2) {
                            local_7e8 = 3;
                            iVar9 = iVar9 + (iVar9 * -2) / 3;
                        } else if (DAT_GameState::instance.mapAndTime.difficulty == 3) {
                            local_7e8 = 2;
                            iVar7 = -(iVar9 / 2);
                            goto LAB_0042cf15;
                        }
                        local_7e4 = 0;
                        do {
                            uVar12 = 1;
                            psVar4 = &DAT_UnitsState::instance.units[1].dying;
                            do {
                                if (((psVar4[-0x10a] == OpenSHC::Map::Units::ULS_NORMAL) && (*psVar4 == 0))
                                    && ((psVar4[-0x105] == DAT_GameSynchronyState::instance.currentPlayerSlotID
                                        && ((psVar4[2] != 0 && (iVar8 = iVar8 + 1, iVar8 == local_7e8)))))) {
                                    iVar7 = MACRO_CALL_MEMBER(
                                        OpenSHC::Map::Units::TroopValueState_Func::getValueOfTroopType,
                                        DAT_TroopValueState::ptr)((OpenSHC::Map::Units::UnitType)((int)psVar4[-0x109]));
                                    iVar9 = iVar9 - iVar7;
                                    MACRO_CALL_MEMBER(
                                        OpenSHC::Map::Units::UnitsState_Func::deleteUnit, DAT_UnitsState::ptr)(uVar12);
                                    if (((psVar4[-0x109] == OpenSHC::Map::Units::UT_S_MANGONEL)
                                            || (psVar4[-0x109] == OpenSHC::Map::Units::UT_S_BALLISTA))
                                        && (DAT_TileMapState::instance.BuildingLayer[*(int*)(psVar4 + -0xe6)] != 0)) {
                                        DAT_BuildingsState::instance
                                            .buildings[DAT_TileMapState::instance
                                                    .BuildingLayer[*(int*)(psVar4 + -0xe6)]]
                                            .containsSiegeMangonel1OrBallista2 = 0;
                                    }
                                    if (iVar9 < 1) {
                                        local_7e4 = 10;
                                        break;
                                    }
                                    iVar8 = 0;
                                }
                                psVar4 = psVar4 + 0x248;
                                uVar12 = uVar12 + 1;
                            } while ((int)psVar4 < 0x165162c);
                            local_7e4 = local_7e4 + 1;
                        } while (local_7e4 < 3);
                    }
                    goto LAB_0042cff9;
                }
            } else {
            LAB_0042cff9:
                if (DAT_MapMissionType::instance == 2)
                    goto LAB_0042cc91;
            }
            DAT_GameState::instance.mapAndTime.siegeInformation.archers = 0;
            DAT_GameState::instance.mapAndTime.siegeInformation.field1_0x4 = 0;
            DAT_GameState::instance.mapAndTime.siegeInformation.field2_0x8 = 0;
            DAT_GameState::instance.mapAndTime.siegeInformation.field3_0xc = 0;
            DAT_GameState::instance.mapAndTime.siegeInformation.field4_0x10 = 0;
            DAT_GameState::instance.mapAndTime.siegeInformation.field5_0x14 = 0;
            DAT_GameState::instance.mapAndTime.siegeInformation.field6_0x18 = 0;
            DAT_GameState::instance.mapAndTime.siegeInformation.field7_0x1c = 0;
            DAT_GameState::instance.mapAndTime.siegeInformation.field8_0x20 = 0;
            DAT_GameState::instance.mapAndTime.siegeInformation.field9_0x24 = 0;
            DAT_GameState::instance.mapAndTime.siegeInformation.field10_0x28 = 0;
            DAT_GameState::instance.mapAndTime.siegeInformation.field11_0x2c = 0;
            DAT_GameState::instance.mapAndTime.siegeInformation.field12_0x30 = 0;
            DAT_GameState::instance.mapAndTime.siegeInformation.field13_0x34 = 0;
            DAT_GameState::instance.mapAndTime.siegeInformation.field14_0x38 = 0;
            DAT_GameState::instance.mapAndTime.siegeInformation.field15_0x3c = 0;
            DAT_GameState::instance.mapAndTime.siegeInformation.field16_0x40 = 0;
            DAT_GameState::instance.mapAndTime.siegeInformation.field17_0x44 = 0;
            DAT_GameState::instance.mapAndTime.siegeInformation.field18_0x48 = 0;
            DAT_GameState::instance.mapAndTime.siegeInformation.field19_0x4c = 0;
            DAT_MapPropertiesState::instance.SEC_Section1067.tunnelersCount = 0;
        }
        iVar8 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        if (DAT_MapMissionType::instance == 0) {
            DAT_GameState::instance.mapAndTime.unitJesterRelated = 0;
            iVar9 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .jesterIDUnk;
            if ((iVar9 != 0)
                && (DAT_UnitsState::instance.units[iVar9].uid
                    == DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .someUnitIDSelfRef_2)) {
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .jesterIDUnk = 0;
                DAT_UnitsState::instance.units[iVar9].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
                DAT_GameState::instance.playerDataArray[iVar8].someUnitIDSelfRef_2 = 0;
            }
            DAT_GameState::instance.mapAndTime.unitLadyRelated = 0;
            iVar9 = DAT_GameState::instance.playerDataArray[iVar8].ladyIDUnk;
            if ((iVar9 != 0)
                && (DAT_UnitsState::instance.units[iVar9].uid
                    == DAT_GameState::instance.playerDataArray[iVar8].someUnitIDSelfRef)) {
                DAT_GameState::instance.playerDataArray[iVar8].ladyIDUnk = 0;
                DAT_UnitsState::instance.units[iVar9].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
                DAT_GameState::instance.playerDataArray[iVar8].someUnitIDSelfRef = 0;
            }
        }
        if (iVar8 == 2) {
            DAT_GameState::instance.playerDataArray[2].currentResources[0xf]
                = DAT_GameState::instance.playerDataArray[2].currentResources[0xf]
                + DAT_GameState::instance.playerDataArray[2].startResources[0xf];
            DAT_GameState::instance.playerDataArray[2].startResources[0xf] = 0;
            DAT_GameState::instance.playerDataArray[2].beforeLastMonthsGold
                = (short)DAT_GameState::instance.playerDataArray[2].currentResources[0xf];
            DAT_GameState::instance.playerDataArray[2].lastMonthsGold
                = (short)DAT_GameState::instance.playerDataArray[2].currentResources[0xf];
        }
        if (DAT_GameCore::instance.mapU4Int1 != 0) {
            DAT_GameState::instance.playerDataArray[iVar8].currentResources[0xf] = 600;
            DAT_GameState::instance.playerDataArray[iVar8].startResources[0xf] = 0;
        }
        DAT_GameCore::instance.missionNumber1to20 = 0x1c;
        if (iVar8 == 1) {
            if (DAT_GameState::instance.playerDataArray[1].keep.id == 0)
                goto LAB_0042d095;
            iVar8 = (short)DAT_BuildingsState::instance.buildings[DAT_GameState::instance.playerDataArray[1].keep.id].x
                + 2;
            iVar9 = (short)DAT_BuildingsState::instance.buildings[DAT_GameState::instance.playerDataArray[1].keep.id].y
                + 2;
        } else if ((DAT_GameState::instance.mapAndTime.signpostEntryData[0].x == 0)
            || (iVar8 = DAT_GameState::instance.mapAndTime.signpostEntryData[0].x,
                iVar9 = DAT_GameState::instance.mapAndTime.signpostEntryData[0].y,
                DAT_GameState::instance.mapAndTime.signpostEntryData[0].y == 0))
            goto LAB_0042d095;
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::focusOnCoordinate,
            DAT_ViewportRenderState::ptr)(iVar8, iVar9);
    LAB_0042d095:
        MACRO_CALL_MEMBER(
            OpenSHC::Rendering::ViewportRenderState_Func::setViewportBasedOnMapSize, DAT_ViewportRenderState::ptr)();
        if (DAT_GameCore::instance.mapU4Int1 != 0) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::pathfindingUpdate_0x4a8ab0,
                DAT_PathFindingState::ptr)(0x1e);
        }
        if ((DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_INVASION) && (param_1 != 1)) {
            iVar8 = 10000;
            DAT_GameCore::instance.field22_0x64 = 0;
            menuID = OpenSHC::UI::Enums::MVT_SCENARIO_DESCRIPTION;
        } else {
            DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType = OpenSHC::UI::Enums::BASMTT_HUNTERSHUT;
            if (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_UNKNOWN_49_DOES_NOTHINGUnk) {
                iVar8 = 0;
            } else {
                iVar8 = 10000;
            }
            menuID = OpenSHC::UI::Enums::MVT_BUILD_MENU;
        }
        MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(menuID, iVar8);
        DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
        DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 1;
        DWORD_00b95b1c::instance = timeGetTime();
        DAT_00b960dc::instance = 1;
        ;
    }

}
}
