#include "../../Map.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/UI/Enums/BuildMenuTabType.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition3.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"
#include "OpenSHC/Game/ScenarioEvents/ScenarioEventCondition.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
#include "OpenSHC/Map/Units/UnitTypeInt.hpp"
#include "OpenSHC/Map/Units/UnitTypeShort.hpp"

namespace OpenSHC {
namespace Map {

    using Audio::SFX::SoundEffectID;
    using Commands::MappersEnum;
    using DE::SHCDE::eTextSections;
    using Game::GameMode;
    using Game::GameMode2;
    using Map::MapType2;
    using Map::Buildings::BuildingLogicalState;
    using Map::Buildings::BuildingType;
    using Map::Units::UnitLogicState;
    using Map::Units::UnitType;
    using Map::Units::Instructions::UnitMatchSpeedEnum;
    using UI::Enums::BuildingsAndStatusMenuTabType;
    using UI::Enums::BuildMenuTabType;
    using UI::Enums::DisplayElementID;
    using UI::Enums::MenuModalType;
    using UI::Enums::MenuViewType;
    using WindowsHelper::Enums::BOOLEnum;
    using Game::ScenarioEvents::ScenarioEventCondition;
    using Map::Buildings::BuildingTypeShort;
    using Map::Units::UnitTypeInt;
    using Map::Units::UnitTypeShort;

    // FUNCTION: STRONGHOLDCRUSADER 0x004C31A0
    void MapPropertiesState::processSingleplayerEvents()
    {
        int iVar1;
        byte(*pabVar2)[10];
        byte* pbVar3;
        byte bVar4;
        byte bVar5;
        UnitTypeShort UVar6;
        short sVar7;
        short sVar8;
        BuildingTypeShort BVar9;
        char* pcVar10;
        BOOLEnum BVar11;
        UnitTypeShort* pUVar12;
        BuildingTypeShort* pBVar13;
        dword tribeID;
        dword dVar14;
        ScenarioEventCondition* pSVar15;
        int _invasionAmplifier;
        InGameEventUnionVersion* pIVar16;
        char cVar17;
        int iVar18;
        uint uVar19;
        int _unitSpawnTotalAdjustment;
        int iVar20;
        int numInGroup;
        InGameEventUnionVersion* psVar21;
        int _unitAIBehaviourTypeUnk;
        int iVar21;
        int iVar22;
        uint y1;
        UnitTypeInt _unitType;
        bool bVar23;
        bool bVar24;
        char* pcVar25;
        char* pcVar26;
        char* pcVar27;
        int local_a0;
        int _eventIndex;
        int _subIndex;
        int _spawnUnitCount;
        int local_88;
        int local_80;
        uint uStack_7c;
        uint uStack_78;
        int _previousScenarioEventIndex;
        int local_70[10];
        int local_48[18];
        int _amplifiedUnitTotalForUnitType;
        int _crusaderOrArabian;
        int _repeatMonths;
        int _conditionOffset;
        int _counter;
        int _scenarioEventType;
        int _eventType;
        int* _pConditionIsMet;
        local_88 = 0;
        local_70[9] = DAT_GameState::instance.mapAndTime.signpostsMapEdgeDataCounter;
        _previousScenarioEventIndex = -1;
        if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
            if ((DAT_GameCore::instance.gameMode_2 != Game::GM_EDITOR)
                && (DAT_GameCore::instance.gameMode_2 != Game::GM_SIEGE_THAT)) {
                if (DAT_GameCore::instance.gameMode_2 == Game::GM_CRUSADER_TUTORIAL) {
                    MACRO_CALL(UI::Helpers_Func::UpdateTutorialStepAndProgress)();
                }
                if (DAT_GameCore::instance.section1095 != 1) {
                    if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .playerDeathRelated
                        == 0) {
                        if ((this->SEC_Section1081) && (0 < this->SEC_Section1080)) {
                            this->SEC_Section1080 = this->SEC_Section1080 + -1;
                        }
                        if (DAT_GameState::instance.mapAndTime.startOfDay) {
                            if (DAT_GameCore::instance.unknownAlwaysZero) {
                                DAT_GameState::instance
                                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .playerDeathRelated = 1;
                                DAT_GameCore::instance.unknownAlwaysZero = 0;
                                DAT_GameState::instance.mapAndTime.unknownCountdown01 = 10;
                            }
                            _pConditionIsMet = DAT_GameState::instance.mapAndTime.scenarioEventTimers;
                            do {
                                if ((*_pConditionIsMet != 0)
                                    && (iVar18 = *_pConditionIsMet + 1, *_pConditionIsMet = iVar18, 0x4b0 < iVar18)) {
                                    *_pConditionIsMet = 0;
                                }
                                _pConditionIsMet = _pConditionIsMet + 1;
                            } while ((int)_pConditionIsMet < 0x117ee60);
                            local_48[0] = -1;
                            local_48[1] = 0xffffffff;
                            local_48[2] = 0xffffffff;
                            local_48[3] = 0xffffffff;
                            local_48[4] = 0xffffffff;
                            local_48[5] = 0xffffffff;
                            local_48[6] = 0xffffffff;
                            local_48[7] = 0xffffffff;
                            local_48[8] = 0xffffffff;
                            local_80 = DAT_TroopValueState::instance.attackInfo.inv_count;
                            local_70[0] = 0;
                            local_48[9] = 0;
                            local_70[1] = 0;
                            local_48[10] = 0;
                            local_70[2] = 0;
                            local_48[0xb] = 0;
                            local_70[3] = 0;
                            local_48[0xc] = 0;
                            local_70[4] = 0;
                            local_48[0xd] = 0;
                            local_70[5] = 0;
                            local_48[0xe] = 0;
                            local_70[6] = 0;
                            local_48[0xf] = 0;
                            local_70[7] = 0;
                            local_48[0x10] = 0;
                            local_70[8] = 0;
                            local_48[0x11] = 0;
                            if ((((DAT_GameState::instance.mapAndTime.month == this->SEC_StartingMonth)
                                     && (DAT_GameState::instance.mapAndTime.year == this->SEC_StartingYear + 1))
                                    && (DAT_GameState::instance.gameTicksLoadBalancer == 1))
                                && ((!DAT_GameState::instance.mapAndTime.week
                                    && (bVar23 = false, 0 < this->eventsCount)))) {
                                _pConditionIsMet = &this->scenarioEvents[0].data.scenario.ScenarioEventType;
                                iVar18 = this->eventsCount;
                                do {
                                    if ((_pConditionIsMet[-3] == 3) && (*_pConditionIsMet == 0x1e)) {
                                        bVar23 = true;
                                    }
                                    _pConditionIsMet = _pConditionIsMet + 0x39;
                                    iVar18 = iVar18 + -1;
                                } while (iVar18);
                                if (bVar23) {
                                    /*
                                      if a fire warning event
                                     */
                                    iVar18 = 0;
                                    if (0 < DAT_BuildingsState::instance.maxBuildingsCount) {
                                        pBVar13 = &DAT_BuildingsState::instance.buildings[0].buildingType;
                                        do {
                                            if (((pBVar13[-1] != ((BuildingLogicalState)0))
                                                    && ((short)pBVar13[2]
                                                        == DAT_GameSynchronyState::instance.currentPlayerSlotID))
                                                && ((*pBVar13 == Map::Buildings::BT_WELL
                                                    || (*pBVar13 == Map::Buildings::BT_WATERPOT))))
                                                goto LAB_004c3637;
                                            iVar18 = iVar18 + 1;
                                            pBVar13 = pBVar13 + 0x196;
                                        } while (iVar18 < DAT_BuildingsState::instance.maxBuildingsCount);
                                    }
                                    pcVar27 = "general_message3.wav";
                                    pcVar25 = "ap_civil12.bik";
                                    /*
                                      "there are no wells in the castle my liege. should a fire break out, we are   int
                                      great danger."   added by script: "There are no wells in the castle my Liege.
                                      Should a fire   break out we would be in great danger."
                                     */
                                    pcVar10 = MACRO_CALL_MEMBER(
                                        Text::TextManager_Func::getTextStringInGroupAtOffset,
                                        DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ACTION, 0x12);
                                    MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                                        DAT_VideoBikQueue::ptr)(pcVar10, pcVar25, pcVar27);
                                }
                            }
                        LAB_004c3637:
                            _eventIndex = 0;
                            if (0 < this->eventsCount) {
                                do {
                                    iVar18 = this->scenarioEvents[_eventIndex].header.year;
                                    if ((DAT_GameState::instance.mapAndTime.year < iVar18)
                                        || ((DAT_GameState::instance.mapAndTime.year == iVar18
                                            && (DAT_GameState::instance.mapAndTime.month
                                                < this->scenarioEvents[_eventIndex].header.month))))
                                        break;
                                    /*
                                      "next Event"
                                     */
                                    if (this->scenarioEvents[_eventIndex].header.done != 0)
                                        goto LAB_004c5f28;
                                    _eventType = this->scenarioEvents[_eventIndex].header.tl_type;
                                    if (_eventType == 1) {
                                        /*
                                          Invasion
                                         */
                                        DAT_GameState::instance.mapAndTime.field3171_0x27a8 = 0;
                                        DAT_GameState::instance
                                            .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                            .aiControlStatusRelated = -200;
                                        /*
                                          invasion. ?
                                         */
                                        iVar18
                                            = local_48[this->scenarioEvents[_eventIndex].data.invasion.crusaderArabian];
                                        if (local_48[this->scenarioEvents[_eventIndex].data.invasion.crusaderArabian]
                                            == -1) {
                                            DAT_TroopValueState::instance.attackInfo.inv_count
                                                = DAT_TroopValueState::instance.attackInfo.inv_count + 1;
                                            if (0x31 < DAT_TroopValueState::instance.attackInfo.inv_count) {
                                                DAT_TroopValueState::instance.attackInfo.inv_count = 1;
                                            }
                                            MACRO_CALL_MEMBER(
                                                Map::Units::TroopValueState_Func::initializeAttackWaveSlot,
                                                DAT_TroopValueState::ptr)(
                                                DAT_TroopValueState::instance.attackInfo.inv_count,
                                                this->scenarioEvents[_eventIndex].data.invasion.messageMonth);
                                            local_48[this->scenarioEvents[_eventIndex].data.invasion.crusaderArabian]
                                                = DAT_TroopValueState::instance.attackInfo.inv_count;
                                            local_80 = DAT_TroopValueState::instance.attackInfo.inv_count;
                                            iVar18 = DAT_TroopValueState::instance.attackInfo.inv_count;
                                        }
                                        DAT_TroopValueState::instance.attackInfo.inv_count = iVar18;
                                        DAT_TroopValueState::instance.attackInfo
                                            .attackWavePlayerIDArray[DAT_TroopValueState::instance.attackInfo.inv_count]
                                            = *(char*)((int)&this->scenarioEvents[_eventIndex].data + 0x74) + 2;
                                        _subIndex = 0;
                                        do {
                                            /*
                                              if invasion.units[index] == 0 then index += 1 (break when not index <
                                              0x19)
                                             */
                                            iVar18 = *(
                                                int*)((int)&this->scenarioEvents[_eventIndex].data + _subIndex * 4 + 4);
                                            if (!iVar18)
                                                goto LAB_004c5db4;
                                            _unitAIBehaviourTypeUnk = 0;
                                            _unitType = ((UnitType)0);
                                            _unitSpawnTotalAdjustment = 0;
                                            switch (_subIndex) {
                                            case 0:
                                                _unitAIBehaviourTypeUnk = 3;
                                                _unitType = Map::Units::UT_E_ARCHER;
                                                break;
                                            case 1:
                                                _unitAIBehaviourTypeUnk = 7;
                                                _unitType = Map::Units::UT_E_XBOW;
                                                break;
                                            case 2:
                                                _unitAIBehaviourTypeUnk = 5;
                                                _unitType = Map::Units::UT_E_SPEAR;
                                                break;
                                            case 3:
                                                _unitAIBehaviourTypeUnk = 6;
                                                _unitType = Map::Units::UT_E_PIKE;
                                                break;
                                            case 4:
                                                _unitAIBehaviourTypeUnk = 9;
                                                _unitType = Map::Units::UT_E_MACE;
                                                break;
                                            case 5:
                                                _unitAIBehaviourTypeUnk = 8;
                                                _unitType = Map::Units::UT_E_SWORD;
                                                break;
                                            case 6:
                                                _unitAIBehaviourTypeUnk = 10;
                                                _unitType = Map::Units::UT_E_KNIGHT;
                                                _unitSpawnTotalAdjustment = 10;
                                                goto switchD_004c5b0c_default;
                                            case 7:
                                                _unitAIBehaviourTypeUnk = 4;
                                                _unitType = Map::Units::UT_E_LADDER;
                                                break;
                                            case 8:
                                                _unitAIBehaviourTypeUnk = 0xb;
                                                _unitType = Map::Units::UT_E_ENGINEER;
                                                break;
                                            case 9:
                                                _unitAIBehaviourTypeUnk = 0x16;
                                                _unitType = Map::Units::UT_S_CATAPULT;
                                                break;
                                            case 10:
                                                _unitAIBehaviourTypeUnk = 0x17;
                                                _unitType = Map::Units::UT_S_TREBUCHET;
                                                break;
                                            case 0xb:
                                                _unitAIBehaviourTypeUnk = 0x13;
                                                _unitType = Map::Units::UT_S_BATTERINGRAM;
                                                break;
                                            case 0xc:
                                                _unitAIBehaviourTypeUnk = 0x14;
                                                _unitType = Map::Units::UT_S_TOWER;
                                                break;
                                            case 0xd:
                                                _unitAIBehaviourTypeUnk = 0x15;
                                                _unitType = Map::Units::UT_S_SHIELD;
                                                break;
                                            case 0xe:
                                                _unitAIBehaviourTypeUnk = 0xc;
                                                _unitType = Map::Units::UT_E_MONK;
                                                break;
                                            case 0xf:
                                                _unitAIBehaviourTypeUnk = 2;
                                                _unitType = Map::Units::UT_TUNNELER;
                                                break;
                                            case 0x10:
                                                _unitAIBehaviourTypeUnk = 0x19;
                                                _unitType = Map::Units::UT_A_ARCHER;
                                                break;
                                            case 0x11:
                                                _unitAIBehaviourTypeUnk = 0x1a;
                                                _unitType = Map::Units::UT_A_SLAVE;
                                                _unitSpawnTotalAdjustment = 0x14;
                                                goto switchD_004c5b0c_default;
                                            case 0x12:
                                                _unitAIBehaviourTypeUnk = 0x1b;
                                                _unitType = Map::Units::UT_A_SLINGER;
                                                _unitSpawnTotalAdjustment = 0x14;
                                                goto switchD_004c5b0c_default;
                                            case 0x13:
                                                _unitAIBehaviourTypeUnk = 0x1c;
                                                _unitType = Map::Units::UT_A_ASSASSIN;
                                                _unitSpawnTotalAdjustment = 2;
                                                goto switchD_004c5b0c_default;
                                            case 0x14:
                                                _unitAIBehaviourTypeUnk = 0x1d;
                                                _unitType = Map::Units::UT_A_HARCHER;
                                                break;
                                            case 0x15:
                                                _unitAIBehaviourTypeUnk = 0x1e;
                                                _unitType = Map::Units::UT_A_SWORDSMAN;
                                                _unitSpawnTotalAdjustment = 8;
                                                goto switchD_004c5b0c_default;
                                            case 0x16:
                                                _unitAIBehaviourTypeUnk = 0x1f;
                                                _unitType = Map::Units::UT_A_FIRETHROWER;
                                                _unitSpawnTotalAdjustment = 4;
                                                goto switchD_004c5b0c_default;
                                            case 0x17:
                                                _unitAIBehaviourTypeUnk = 0x18;
                                                _unitType = Map::Units::UT_S_FBALLISTA;
                                                break;
                                            default:
                                                goto switchD_004c5b0c_default;
                                            }
                                            _unitSpawnTotalAdjustment = 10;
                                        switchD_004c5b0c_default:
                                            _invasionAmplifier = 100;
                                            if (!DAT_GameState::instance.mapAndTime.difficulty) {
                                                _invasionAmplifier = 50;
                                            } else if (DAT_GameState::instance.mapAndTime.difficulty == 2) {
                                                _invasionAmplifier = 140;
                                            } else if (DAT_GameState::instance.mapAndTime.difficulty == 3) {
                                                _invasionAmplifier = 200;
                                            }
                                            _amplifiedUnitTotalForUnitType = (_invasionAmplifier * iVar18) / 100;
                                            cVar17 = (char)_amplifiedUnitTotalForUnitType;
                                            if (_unitAIBehaviourTypeUnk == 0x16) {
                                                pabVar2 = DAT_TroopValueState::instance.attackInfo.someSinglePlayerScore
                                                    + DAT_TroopValueState::instance.attackInfo.inv_count;
                                                (*pabVar2)[0] = (*pabVar2)[0] + cVar17;
                                            } else if (_unitAIBehaviourTypeUnk == 0x17) {
                                                pbVar3 = DAT_TroopValueState::instance.attackInfo.someSinglePlayerScore
                                                             [DAT_TroopValueState::instance.attackInfo.inv_count]
                                                    + 1;
                                                *pbVar3 = *pbVar3 + cVar17;
                                            } else if (_unitAIBehaviourTypeUnk == 0x13) {
                                                pbVar3 = DAT_TroopValueState::instance.attackInfo.someSinglePlayerScore
                                                             [DAT_TroopValueState::instance.attackInfo.inv_count]
                                                    + 2;
                                                *pbVar3 = *pbVar3 + cVar17;
                                            } else if (_unitAIBehaviourTypeUnk == 0x14) {
                                                pbVar3 = DAT_TroopValueState::instance.attackInfo.someSinglePlayerScore
                                                             [DAT_TroopValueState::instance.attackInfo.inv_count]
                                                    + 3;
                                                *pbVar3 = *pbVar3 + cVar17;
                                            } else if (_unitAIBehaviourTypeUnk == 0x15) {
                                                pbVar3 = DAT_TroopValueState::instance.attackInfo.someSinglePlayerScore
                                                             [DAT_TroopValueState::instance.attackInfo.inv_count]
                                                    + 4;
                                                *pbVar3 = *pbVar3 + cVar17;
                                            } else if (_unitAIBehaviourTypeUnk == 0x18) {
                                                pbVar3 = DAT_TroopValueState::instance.attackInfo.someSinglePlayerScore
                                                             [DAT_TroopValueState::instance.attackInfo.inv_count]
                                                    + 8;
                                                *pbVar3 = *pbVar3 + cVar17;
                                            } else {
                                                _spawnUnitCount = _amplifiedUnitTotalForUnitType
                                                    / (_amplifiedUnitTotalForUnitType / _unitSpawnTotalAdjustment + 1);
                                                while (0 < _amplifiedUnitTotalForUnitType) {
                                                    if (_amplifiedUnitTotalForUnitType < _spawnUnitCount) {
                                                        _spawnUnitCount = _amplifiedUnitTotalForUnitType;
                                                    }
                                                    iVar18 = this->scenarioEvents[_eventIndex]
                                                                 .data.invasion.crusaderArabian;
                                                    iVar22 = local_48[iVar18 + 9];
                                                    local_48[iVar18 + 9] = iVar22 + 1;
                                                    iVar21 = (&DAT_TroopValueState::instance.attackInfo
                                                            .unknownSignpostRelatedArray)[DAT_TroopValueState::instance
                                                            .attackInfo.inv_count];
                                                    MACRO_CALL_MEMBER(
                                                        Map::Units::TribesState_Func::spawnUnitsIntoNewTribe,
                                                        DAT_TribesState::ptr)(iVar22, _unitAIBehaviourTypeUnk,
                                                        DAT_GameState::instance.mapAndTime
                                                            .signpostsMapEdge[iVar21][local_88]
                                                            .x,
                                                        DAT_GameState::instance.mapAndTime
                                                            .signpostsMapEdge[iVar21][local_88]
                                                            .y,
                                                        iVar18 + 2, (UnitType)((int)(_unitType)), ((UnitType)0),
                                                        _spawnUnitCount, 0);
                                                    local_88 = local_88 + 1;
                                                    _amplifiedUnitTotalForUnitType
                                                        = _amplifiedUnitTotalForUnitType - _spawnUnitCount;
                                                    if (local_70[9] <= local_88) {
                                                        local_88 = 0;
                                                    }
                                                }
                                            }
                                        LAB_004c5db4:
                                            _subIndex = _subIndex + 1;
                                        } while (_subIndex < 0x19);
                                        iVar18 = (&DAT_TroopValueState::instance.attackInfo.unknownSignpostRelatedArray)
                                            [DAT_TroopValueState::instance.attackInfo.inv_count];
                                        MACRO_CALL_MEMBER(UI::MinimapViewState_Func::setSpawnMoment,
                                            DAT_MinimapViewState::ptr)(
                                            DAT_GameState::instance.mapAndTime.signpostEntryData[iVar18].x,
                                            DAT_GameState::instance.mapAndTime.signpostEntryData[iVar18].y);
                                        DAT_TroopValueState::instance.attackInfo.inv_count = local_80;
                                        if ((!DAT_GameCore::instance.section1076)
                                            && (_crusaderOrArabian
                                                = this->scenarioEvents[_eventIndex].data.invasion.crusaderArabian,
                                                local_70[_crusaderOrArabian] == 0)) {
                                            local_70[_crusaderOrArabian] = 1;
                                            if (!_crusaderOrArabian) {
                                                pcVar25 = "infidel_attack.wav";
                                                pcVar10 = "sultan_nervous.bik";
                                            LAB_004c5e44:
                                                MACRO_CALL_MEMBER(
                                                    Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                                                    DAT_VideoBikQueue::ptr)("", pcVar10, pcVar25);
                                            } else if (_crusaderOrArabian == 1) {
                                                pcVar25 = "arabian_attack.wav";
                                                pcVar10 = "good_soldier_nervous.bik";
                                                goto LAB_004c5e44;
                                            }
                                            if ((DAT_GameCore::instance.currentMenuViewType
                                                    == UI::Enums::MVT_BUILD_MENU)
                                                && ((DAT_GameCore::instance.activeMenuTab.tabType
                                                        == UI::Enums::BASMTT_SIEGETENT_SIEGETOWER
                                                    || (DAT_GameCore::instance.activeMenuTab.tabType
                                                        == UI::Enums::BASMTT_SIEGETENT_SHIELD)))) {
                                                MACRO_CALL_MEMBER(Game::GameCore_Func::swapBuildMenuTab,
                                                    DAT_GameCore::ptr)();
                                                if (DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                                                    == UI::Enums::BASMTT_SIEGETENT_SIEGETOWER) {
                                                    if (DAT_GameCore::instance.currentMenuViewType
                                                        == UI::Enums::MVT_BUILD_MENU) {
                                                        DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                                                            = UI::Enums::BASMTT_HUNTERSHUT;
                                                    } else if (DAT_GameCore::instance.currentMenuViewType
                                                        == UI::Enums::MVT_MAP_EDITOR_LANDSCAPING) {
                                                        DAT_GameCore::instance.landscapingmenuMenuTabToSwitchTo = 0xe7;
                                                    }
                                                }
                                                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView,
                                                    DAT_GameCore::ptr)((UI::Enums::MenuViewType)DAT_GameCore::instance.currentMenuViewType, 0);
                                            }
                                        }
                                        _repeatMonths = this->scenarioEvents[_eventIndex].data.invasion.repeatMonths;
                                        if (!_repeatMonths) {
                                            this->scenarioEvents[_eventIndex].header.done = 1;
                                        } else {
                                            _pConditionIsMet = &this->scenarioEvents[_eventIndex].header.year;
                                            *_pConditionIsMet = *_pConditionIsMet + _repeatMonths / 0xc;
                                            iVar18 = this->scenarioEvents[_eventIndex].header.year;
                                            this->scenarioEvents[_eventIndex].header.month
                                                = this->scenarioEvents[_eventIndex].header.month + _repeatMonths % 0xc;
                                            iVar22 = this->scenarioEvents[_eventIndex].header.month;
                                            this->scenarioEvents[_eventIndex].header.pre_done = 0;
                                            if (0xb < iVar22) {
                                                this->scenarioEvents[_eventIndex].header.month = iVar22 + -0xc;
                                                this->scenarioEvents[_eventIndex].header.year = iVar18 + 1;
                                            }
                                            MACRO_CALL_MEMBER(
                                                Map::MapPropertiesState_Func::sortEventsByDate, this)();
                                            _eventIndex = _eventIndex + -1;
                                        }
                                        goto LAB_004c5f28;
                                    }
                                    if (_eventType == 2) {
                                        this->scenarioEvents[_eventIndex].header.done = 1;
                                        goto LAB_004c5f28;
                                    }
                                    if (_eventType != 3)
                                        goto LAB_004c5f28;
                                    iVar18 = this->scenarioEvents[_eventIndex].data.scenario.ScenarioEventType;
                                    if ((!iVar18) || (iVar18 == 0x1a)) {
                                        if (_previousScenarioEventIndex != -1) {
                                            this->scenarioEvents[_previousScenarioEventIndex].header.done = 1;
                                        }
                                        _previousScenarioEventIndex = _eventIndex;
                                    }
                                    local_a0 = 0;
                                    /*
                                      this is from invasion event code, ignore the meaning here
                                     */
                                    _spawnUnitCount = 0;
                                    for (_subIndex = 0; _subIndex < 40; _subIndex++) {
                                        _conditionOffset = _subIndex * 4;
                                        _counter = _spawnUnitCount;
                                        /*
                                          this condition is empty? then move to next condition
                                         */
                                        if (*(char*)((int)&this->scenarioEvents[_eventIndex].data + _subIndex * 4 + 0xf)
                                            == '\0')
                                            goto switchD_004c3756_caseD_18;
                                        _counter = _spawnUnitCount + 1;
                                        /*
                                          Extra event info at: 0x0165f028
                                         */
                                        _pConditionIsMet
                                            = &this->SEC_EventsExtra[_eventIndex].conditionIsTrue[_subIndex];
                                        *_pConditionIsMet = 0;
                                        switch (_subIndex) {
                                        case 0:
                                            local_a0 = _counter;
                                            break;
                                        case 1:
                                            iVar22 = MACRO_CALL_MEMBER(
                                                Map::MapPropertiesState_Func::getDifficultyMultipliedValue,
                                                this)((int)this->scenarioEvents[_eventIndex]
                                                    .data.scenario.conditions[1]
                                                    .value);
                                            iVar18 = DAT_GameState::instance
                                                         .playerDataArray[DAT_GameSynchronyState::instance
                                                                 .currentPlayerSlotID]
                                                         .currentPopulation;
                                            bVar24 = (iVar18 < iVar22);
                                            bVar23 = iVar18 - iVar22 < 0;
                                            goto LAB_004c3fc7;
                                        case 2:
                                            iVar18 = DAT_GameState::instance
                                                         .playerDataArray[DAT_GameSynchronyState::instance
                                                                 .currentPlayerSlotID]
                                                         .lordKilledByPlayerID;
                                            if (!iVar18)
                                                break;
                                            cVar17 = *(char*)((int)&this->scenarioEvents[_eventIndex].data
                                                + _conditionOffset + 0xe);
                                            if (((cVar17 != '\0') && (iVar18 != 10)) && (cVar17 + 1 != iVar18))
                                                goto LAB_004c37cd;
                                            goto LAB_004c3fcd;
                                        case 3:
                                            if (DAT_GameState::instance
                                                    .playerDataArray[DAT_GameSynchronyState::instance
                                                            .currentPlayerSlotID]
                                                    .playerRelatedFlag
                                                != 0) {
                                                *_pConditionIsMet = 1;
                                                local_a0 = local_a0 + 1;
                                                break;
                                            }
                                            goto LAB_004c37cd;
                                        case 4:
                                            iVar22 = MACRO_CALL_MEMBER(
                                                Map::MapPropertiesState_Func::getDifficultyMultipliedValue,
                                                this)((int)this->scenarioEvents[_eventIndex]
                                                    .data.scenario.conditions[4]
                                                    .value);
                                            iVar18 = DAT_GameState::instance
                                                         .playerDataArray[DAT_GameSynchronyState::instance
                                                                 .currentPlayerSlotID]
                                                         .currentResources[0xf];
                                            bVar24 = (iVar18 < iVar22);
                                            bVar23 = iVar18 - iVar22 < 0;
                                            goto LAB_004c3fc7;
                                        case 5:
                                            iVar18 = MACRO_CALL_MEMBER(
                                                Map::MapPropertiesState_Func::getDifficultyMultipliedValue,
                                                this)((int)this->scenarioEvents[_eventIndex]
                                                    .data.scenario.conditions[5]
                                                    .value);
                                            cVar17 = *(char*)((int)&this->scenarioEvents[_eventIndex].data
                                                + _conditionOffset + 0xe);
                                            if (cVar17 == '\0') {
                                                iVar22 = DAT_GameState::instance
                                                             .playerDataArray[DAT_GameSynchronyState::instance
                                                                     .currentPlayerSlotID]
                                                             .currentResources[10]
                                                    + DAT_GameState::instance
                                                          .playerDataArray[DAT_GameSynchronyState::instance
                                                                  .currentPlayerSlotID]
                                                          .currentResources[0xb]
                                                    + DAT_GameState::instance
                                                          .playerDataArray[DAT_GameSynchronyState::instance
                                                                  .currentPlayerSlotID]
                                                          .currentResources[0xc]
                                                    + DAT_GameState::instance
                                                          .playerDataArray[DAT_GameSynchronyState::instance
                                                                  .currentPlayerSlotID]
                                                          .currentResources[0xd];
                                                bVar24 = (iVar22 < iVar18);
                                                bVar23 = iVar22 - iVar18 < 0;
                                            } else {
                                            LAB_004c38d2:
                                                iVar22 = (int)cVar17;
                                                if (iVar22 == 8) {
                                                    iVar22 = 7;
                                                }
                                                iVar22 = DAT_GameState::instance
                                                             .playerDataArray[DAT_GameSynchronyState::instance
                                                                     .currentPlayerSlotID]
                                                             .currentResources[iVar22];
                                                bVar24 = (iVar22 < iVar18);
                                                bVar23 = iVar22 - iVar18 < 0;
                                            }
                                            goto LAB_004c3fc7;
                                        case 6:
                                        case 0x11:
                                            iVar18 = MACRO_CALL_MEMBER(
                                                Map::MapPropertiesState_Func::getDifficultyMultipliedValue,
                                                this)((int)*(short*)((int)&this->scenarioEvents[_eventIndex].data
                                                + _subIndex * 4 + 0xc));
                                            cVar17 = *(char*)((int)&this->scenarioEvents[_eventIndex].data
                                                + _conditionOffset + 0xe);
                                            if (cVar17 != '\0')
                                                goto LAB_004c38d2;
                                            iVar22 = DAT_GameState::instance
                                                         .playerDataArray[DAT_GameSynchronyState::instance
                                                                 .currentPlayerSlotID]
                                                         .currentResources[0x11]
                                                + DAT_GameState::instance
                                                      .playerDataArray[DAT_GameSynchronyState::instance
                                                              .currentPlayerSlotID]
                                                      .currentResources[0x12]
                                                + DAT_GameState::instance
                                                      .playerDataArray[DAT_GameSynchronyState::instance
                                                              .currentPlayerSlotID]
                                                      .currentResources[0x13]
                                                + DAT_GameState::instance
                                                      .playerDataArray[DAT_GameSynchronyState::instance
                                                              .currentPlayerSlotID]
                                                      .currentResources[0x14]
                                                + DAT_GameState::instance
                                                      .playerDataArray[DAT_GameSynchronyState::instance
                                                              .currentPlayerSlotID]
                                                      .currentResources[0x15]
                                                + DAT_GameState::instance
                                                      .playerDataArray[DAT_GameSynchronyState::instance
                                                              .currentPlayerSlotID]
                                                      .currentResources[0x16]
                                                + DAT_GameState::instance
                                                      .playerDataArray[DAT_GameSynchronyState::instance
                                                              .currentPlayerSlotID]
                                                      .currentResources[0x17]
                                                + DAT_GameState::instance
                                                      .playerDataArray[DAT_GameSynchronyState::instance
                                                              .currentPlayerSlotID]
                                                      .currentResources[0x18];
                                            bVar24 = (iVar22 < iVar18);
                                            bVar23 = iVar22 - iVar18 < 0;
                                            goto LAB_004c3fc7;
                                        case 7:
                                            iVar18 = MACRO_CALL_MEMBER(
                                                Map::MapPropertiesState_Func::getDifficultyMultipliedValue,
                                                this)((int)this->scenarioEvents[_eventIndex]
                                                    .data.scenario.conditions[7]
                                                    .value);
                                            cVar17 = *(char*)((int)&this->scenarioEvents[_eventIndex].data
                                                + _conditionOffset + 0xe);
                                            if (cVar17 != '\0')
                                                goto LAB_004c38d2;
                                            iVar22 = DAT_GameState::instance
                                                         .playerDataArray[DAT_GameSynchronyState::instance
                                                                 .currentPlayerSlotID]
                                                         .currentResources[0xe]
                                                + DAT_GameState::instance
                                                      .playerDataArray[DAT_GameSynchronyState::instance
                                                              .currentPlayerSlotID]
                                                      .currentResources[2]
                                                + DAT_GameState::instance
                                                      .playerDataArray[DAT_GameSynchronyState::instance
                                                              .currentPlayerSlotID]
                                                      .currentResources[3]
                                                + DAT_GameState::instance
                                                      .playerDataArray[DAT_GameSynchronyState::instance
                                                              .currentPlayerSlotID]
                                                      .currentResources[4]
                                                + DAT_GameState::instance
                                                      .playerDataArray[DAT_GameSynchronyState::instance
                                                              .currentPlayerSlotID]
                                                      .currentResources[6]
                                                + DAT_GameState::instance
                                                      .playerDataArray[DAT_GameSynchronyState::instance
                                                              .currentPlayerSlotID]
                                                      .currentResources[7]
                                                + DAT_GameState::instance
                                                      .playerDataArray[DAT_GameSynchronyState::instance
                                                              .currentPlayerSlotID]
                                                      .currentResources[9];
                                            bVar24 = (iVar22 < iVar18);
                                            bVar23 = iVar22 - iVar18 < 0;
                                        LAB_004c3fc7:
                                            if (bVar24 == bVar23) {
                                            LAB_004c3fcd:
                                                *_pConditionIsMet = 1;
                                                local_a0 = local_a0 + 1;
                                            } else {
                                            LAB_004c37cd:
                                                *_pConditionIsMet = 0;
                                            }
                                            break;
                                        case 8:
                                            if (DAT_GameState::instance
                                                    .playerDataArray[DAT_GameSynchronyState::instance
                                                            .currentPlayerSlotID]
                                                    .totalEnemyUnitsCount
                                                == 0) {
                                                _scenarioEventType
                                                    = this->scenarioEvents[_eventIndex].data.scenario.ScenarioEventType;
                                                if (((_scenarioEventType == 0x1a) || (!_scenarioEventType))
                                                    || (_scenarioEventType == 0x17)) {
                                                    iVar18 = _eventIndex + 1;
                                                    if (iVar18 < this->eventsCount) {
                                                        pSVar15 = this->scenarioEvents[_eventIndex + 1]
                                                                      .data.scenario.conditions
                                                            + 0x19;
                                                        do {
                                                            if (((*(const int*)&pSVar15[-0x1e] == 1)
                                                                    && (*(const int*)pSVar15 == 0))
                                                                && (pSVar15[-0x1d].value == 0))
                                                                goto switchD_004c3756_caseD_18;
                                                            iVar18 = iVar18 + 1;
                                                            pSVar15 = pSVar15 + 0x39;
                                                        } while (iVar18 < this->eventsCount);
                                                    }
                                                    *_pConditionIsMet = 1;
                                                    local_a0 = local_a0 + 1;
                                                } else {
                                                    *_pConditionIsMet = 1;
                                                    local_a0 = local_a0 + 1;
                                                }
                                            }
                                            break;
                                        case 9:
                                            BVar11 = MACRO_CALL_MEMBER(
                                                Game::GameStateStructures_Func::checkKeepEnclosed,
                                                DAT_GameState::ptr)(
                                                DAT_GameSynchronyState::instance.currentPlayerSlotID);
                                            if (!BVar11)
                                                goto LAB_004c37cd;
                                            *_pConditionIsMet = 1;
                                            local_a0 = local_a0 + 1;
                                            break;
                                        case 10:
                                            iVar18 = 0;
                                            if (DAT_UnitsState::instance.maxUnitCount < 2)
                                                goto LAB_004c3fcd;
                                            pUVar12 = &DAT_UnitsState::instance.units[1].unitType;
                                            iVar22 = DAT_UnitsState::instance.maxUnitCount - 1;
                                            do {
                                                if ((pUVar12[-1] == Map::Units::ULS_NORMAL)
                                                    && (*pUVar12 == Map::Units::UT_LIONSHWOLF)) {
                                                    iVar18 = iVar18 + 1;
                                                }
                                                pUVar12 = pUVar12 + 0x248;
                                                iVar22 = iVar22 + -1;
                                            } while (iVar22);
                                            if (iVar18)
                                                goto LAB_004c37cd;
                                            *_pConditionIsMet = 1;
                                            local_a0 = local_a0 + 1;
                                            break;
                                        case 0xb:
                                            if (DAT_GameState::instance
                                                    .playerDataArray[DAT_GameSynchronyState::instance
                                                            .currentPlayerSlotID]
                                                    .totalEnemyUnitsCount
                                                == 0)
                                                goto LAB_004c37cd;
                                            *_pConditionIsMet = 1;
                                            local_a0 = local_a0 + 1;
                                            break;
                                        case 0xc:
                                            iVar18 = 0;
                                            if (DAT_UnitsState::instance.maxUnitCount < 2)
                                                goto LAB_004c3fcd;
                                            pUVar12 = &DAT_UnitsState::instance.units[1].unitType;
                                            iVar22 = DAT_UnitsState::instance.maxUnitCount - 1;
                                            do {
                                                if (((((pUVar12[-1] == Map::Units::ULS_NORMAL)
                                                          && ((short)pUVar12[4]
                                                              == DAT_GameSynchronyState::instance.currentPlayerSlotID))
                                                         && (*(byte*)(pUVar12 + 0x14f) == 0))
                                                        && (((((pUVar12[0x165] == 0
                                                                   && (UVar6 = *pUVar12,
                                                                       UVar6 != Map::Units::UT_E_LADDER))
                                                                  && ((UVar6 != Map::Units::UT_E_ENGINEER
                                                                      || (pUVar12[0x17d] != 0))))
                                                                 && ((UVar6 != Map::Units::UT_S_TOWER
                                                                     && (UVar6
                                                                         != Map::Units::UT_S_BATTERINGRAM))))
                                                            && (UVar6 != Map::Units::UT_S_SHIELD))))
                                                    && ((((UVar6 != Map::Units::UT_S_MANGONEL
                                                              && (UVar6 != Map::Units::UT_S_BALLISTA))
                                                             && (UVar6 != Map::Units::UT_S_CATAPULT))
                                                        && ((UVar6 != Map::Units::UT_S_FBALLISTA
                                                            && (UVar6 != Map::Units::UT_S_TREBUCHET)))))) {
                                                    iVar18 = iVar18 + 1;
                                                }
                                                pUVar12 = pUVar12 + 0x248;
                                                iVar22 = iVar22 + -1;
                                            } while (iVar22);
                                            if (iVar18)
                                                goto LAB_004c37cd;
                                            *_pConditionIsMet = 1;
                                            local_a0 = local_a0 + 1;
                                            break;
                                        case 0xd:
                                            cVar17 = *(char*)((int)&this->scenarioEvents[_eventIndex].data
                                                + _conditionOffset + 0xe);
                                            if (cVar17 == '\0') {
                                                if ((int)this->scenarioEvents[_eventIndex]
                                                        .data.scenario.conditions[0xd]
                                                        .value
                                                    <= DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[0]
                                                        + DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[1]
                                                        + DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[2]
                                                        + DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[3]
                                                        + DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[4]
                                                        + DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[5]
                                                        + DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[6]
                                                        + DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[7]
                                                        + DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[8]) {
                                                    DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[0] = 0;
                                                    DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[1] = 0;
                                                    DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[2] = 0;
                                                    DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[3] = 0;
                                                    DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[4] = 0;
                                                    DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[5] = 0;
                                                    DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[6] = 0;
                                                    DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[7] = 0;
                                                    DAT_GameState::instance.mapAndTime.hitsDealtToPlayerArray[8] = 0;
                                                    this->SEC_EventsExtra[_eventIndex].conditionIsTrue[13] = 1;
                                                    local_a0 = local_a0 + 1;
                                                }
                                            } else if (((byte)(cVar17 - 1U) < 4)
                                                && ((int)this->scenarioEvents[_eventIndex]
                                                        .data.scenario.conditions[0xd]
                                                        .value
                                                    <= DAT_GameState::instance.mapAndTime.emenyHitArray[cVar17 + -8])) {
                                                DAT_GameState::instance.mapAndTime.emenyHitArray[cVar17 + -8] = 0;
                                                *_pConditionIsMet = 1;
                                                local_a0 = local_a0 + 1;
                                            }
                                            break;
                                        case 0xe:
                                            cVar17 = *(char*)((int)&this->scenarioEvents[_eventIndex].data
                                                + _conditionOffset + 0xe);
                                            if (cVar17 == '\0') {
                                                if ((int)this->scenarioEvents[_eventIndex]
                                                        .data.scenario.conditions[0xe]
                                                        .value
                                                    <= DAT_GameState::instance.mapAndTime.emenyHitArray[0]
                                                        + DAT_GameState::instance.mapAndTime.emenyHitArray[1]
                                                        + DAT_GameState::instance.mapAndTime.emenyHitArray[2]
                                                        + DAT_GameState::instance.mapAndTime.emenyHitArray[3]
                                                        + DAT_GameState::instance.mapAndTime.emenyHitArray[4]
                                                        + DAT_GameState::instance.mapAndTime.emenyHitArray[5]
                                                        + DAT_GameState::instance.mapAndTime.emenyHitArray[6]
                                                        + DAT_GameState::instance.mapAndTime.emenyHitArray[7]
                                                        + DAT_GameState::instance.mapAndTime.emenyHitArray[8]) {
                                                    DAT_GameState::instance.mapAndTime.emenyHitArray[0] = 0;
                                                    DAT_GameState::instance.mapAndTime.emenyHitArray[1] = 0;
                                                    DAT_GameState::instance.mapAndTime.emenyHitArray[2] = 0;
                                                    DAT_GameState::instance.mapAndTime.emenyHitArray[3] = 0;
                                                    DAT_GameState::instance.mapAndTime.emenyHitArray[4] = 0;
                                                    DAT_GameState::instance.mapAndTime.emenyHitArray[5] = 0;
                                                    DAT_GameState::instance.mapAndTime.emenyHitArray[6] = 0;
                                                    DAT_GameState::instance.mapAndTime.emenyHitArray[7] = 0;
                                                    DAT_GameState::instance.mapAndTime.emenyHitArray[8] = 0;
                                                    this->SEC_EventsExtra[_eventIndex].conditionIsTrue[14] = 1;
                                                    local_a0 = local_a0 + 1;
                                                }
                                            } else if (((byte)(cVar17 - 1U) < 4)
                                                && ((int)this->scenarioEvents[_eventIndex]
                                                        .data.scenario.conditions[0xe]
                                                        .value
                                                    <= DAT_GameState::instance.mapAndTime.emenyHitArray[cVar17 + 1])) {
                                                DAT_GameState::instance.mapAndTime.emenyHitArray[cVar17 + 1] = 0;
                                                *_pConditionIsMet = 1;
                                                local_a0 = local_a0 + 1;
                                            }
                                            break;
                                        case 0xf:
                                            if (DAT_GameState::instance
                                                    .playerDataArray[DAT_GameSynchronyState::instance
                                                            .currentPlayerSlotID]
                                                    .totalEnemyUnitsCount
                                                == 0) {
                                                *_pConditionIsMet = 1;
                                                local_a0 = local_a0 + 1;
                                            } else {
                                                if (((DAT_GameCore::instance.gameMode_2 != Game::GM_BUILDERUnk)
                                                        || (this->SEC_U3_MapType2_1 != Map::MT_SIEGE))
                                                    || ((DAT_GameSynchronyState::instance.currentPlayerSlotID != 1
                                                        || (BVar11 = MACRO_CALL_MEMBER(
                                                                Map::Units::TroopValueState_Func::isAttackWaveComplete,
                                                                DAT_TroopValueState::ptr)(),
                                                            !BVar11))))
                                                    goto LAB_004c37cd;
                                                *_pConditionIsMet = 1;
                                                local_a0 = local_a0 + 1;
                                            }
                                            break;
                                        case 0x10:
                                            if (DAT_GameState::instance.mapAndTime.cathedralRelated1 == 1) {
                                                *_pConditionIsMet = 1;
                                                local_a0 = local_a0 + 1;
                                            }
                                            break;
                                        case 0x12:
                                            if (DAT_GameCore::instance.gameMode_2 != Game::GM_BUILDERUnk) {
                                                iVar18 = 0;
                                                if (DAT_BuildingsState::instance.maxBuildingsCount < 2)
                                                    goto LAB_004c37cd;
                                                pBVar13 = &DAT_BuildingsState::instance.buildings[1].buildingType;
                                                iVar22 = DAT_BuildingsState::instance.maxBuildingsCount + -1;
                                                do {
                                                    if (((pBVar13[-1] != ((BuildingLogicalState)0))
                                                            && (*pBVar13 == Map::Buildings::BT_DAIRYFARM))
                                                        && (pBVar13[0x65] == 0)) {
                                                        iVar18 = iVar18 + 1;
                                                    }
                                                    pBVar13 = pBVar13 + 0x196;
                                                    iVar22 = iVar22 + -1;
                                                } while (iVar22);
                                                bVar24 = (iVar18 < 4);
                                                bVar23 = iVar18 + -4 < 0;
                                                goto LAB_004c3fc7;
                                            }
                                            break;
                                        case 0x13:
                                            if (DAT_GameCore::instance.gameMode_2 != Game::GM_BUILDERUnk) {
                                                iVar18 = 0;
                                                if (DAT_BuildingsState::instance.maxBuildingsCount < 2)
                                                    goto LAB_004c37cd;
                                                pBVar13 = &DAT_BuildingsState::instance.buildings[1].buildingType;
                                                iVar22 = DAT_BuildingsState::instance.maxBuildingsCount + -1;
                                                do {
                                                    if ((((pBVar13[-1] != ((BuildingLogicalState)0))
                                                             && (*pBVar13 == Map::Buildings::BT_INN))
                                                            && (pBVar13[0x65] == 0))
                                                        && (0 < (short)pBVar13[0xef])) {
                                                        iVar18 = iVar18 + 1;
                                                    }
                                                    pBVar13 = pBVar13 + 0x196;
                                                    iVar22 = iVar22 + -1;
                                                } while (iVar22);
                                                bVar24 = (iVar18 < 2);
                                                bVar23 = iVar18 + -2 < 0;
                                                goto LAB_004c3fc7;
                                            }
                                            break;
                                        case 0x14:
                                            sVar7 = DAT_GameState::instance
                                                        .playerDataArray[DAT_GameSynchronyState::instance
                                                                .currentPlayerSlotID]
                                                        .previousBlessedPeoplePercentage;
                                            sVar8 = this->scenarioEvents[_eventIndex]
                                                        .data.scenario.conditions[0x14]
                                                        .value;
                                            bVar24 = (sVar7 < sVar8);
                                            bVar23 = (short)(sVar7 - sVar8) < 0;
                                            goto LAB_004c3deb;
                                        case 0x15:
                                            iVar18 = MACRO_CALL_MEMBER(
                                                Game::GameStateStructures_Func::computeAleCoverage,
                                                DAT_GameState::ptr)(
                                                DAT_GameSynchronyState::instance.currentPlayerSlotID);
                                            iVar22 = (int)this->scenarioEvents[_eventIndex]
                                                         .data.scenario.conditions[0x15]
                                                         .value;
                                            bVar24 = (iVar18 < iVar22);
                                            bVar23 = iVar18 - iVar22 < 0;
                                            goto LAB_004c3deb;
                                        case 0x16:
                                            if (DAT_GameState::instance
                                                    .playerDataArray[DAT_GameSynchronyState::instance
                                                            .currentPlayerSlotID]
                                                    .fearFactorLevel
                                                <= -(int)this->scenarioEvents[_eventIndex]
                                                    .data.scenario.conditions[0x16]
                                                    .value) {
                                                *_pConditionIsMet = 1;
                                                local_a0 = local_a0 + 1;
                                            }
                                            break;
                                        case 0x17:
                                            iVar22 = (int)this->scenarioEvents[_eventIndex]
                                                         .data.scenario.conditions[0x17]
                                                         .value;
                                            iVar18 = DAT_GameState::instance
                                                         .playerDataArray[DAT_GameSynchronyState::instance
                                                                 .currentPlayerSlotID]
                                                         .fearFactorLevel;
                                            bVar24 = (iVar18 < iVar22);
                                            bVar23 = iVar18 - iVar22 < 0;
                                        LAB_004c3deb:
                                            if (bVar24 == bVar23) {
                                                *_pConditionIsMet = 1;
                                                local_a0 = local_a0 + 1;
                                            }
                                            break;
                                        case 0x27:
                                            if (local_a0 == _spawnUnitCount) {
                                                MACRO_CALL(UI::DisplayElements_Func::
                                                        CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                                                    UI::Enums::DEID_TIME_UNTIL_VICTORY, 1);
                                                if (!this->SEC_Section1081) {
                                                    this->SEC_Section1080
                                                        = *(short*)((int)&this->scenarioEvents[_eventIndex].data + 0xa8)
                                                        * 800;
                                                    this->SEC_Section1090 = this->SEC_Section1080;
                                                }
                                                this->SEC_Section1081 = 1;
                                                if (this->SEC_Section1080 < 1) {
                                                    *_pConditionIsMet = 1;
                                                    local_a0 = local_a0 + 1;
                                                }
                                            } else {
                                                if (this->SEC_Section1081) {
                                                    MACRO_CALL(UI::DisplayElements_Func::
                                                            CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                                                        UI::Enums::DEID_TIME_UNTIL_VICTORY, 0);
                                                }
                                                this->SEC_Section1081 = 0;
                                            }
                                        }
                                    switchD_004c3756_caseD_18:
                                        _spawnUnitCount = _counter;
                                    }
                                    if (((*(short*)((int)&this->scenarioEvents[_eventIndex].data + 8) != 0)
                                            || (!local_a0))
                                        && (local_a0 < _spawnUnitCount))
                                        goto LAB_004c5f28;
                                    iVar18 = this->scenarioEvents[_eventIndex].data.scenario.ScenarioEventType;
                                    this->scenarioEvents[_eventIndex].header.done = 1;
                                    DAT_GameState::instance.mapAndTime.scenarioEventTimers[iVar18] = 1;
                                    iVar18 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                                    switch (this->scenarioEvents[_eventIndex].data.scenario.ScenarioEventType) {
                                    case 0:
                                        if (DAT_GameState::instance
                                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                                .playerDeathRelated
                                            == 0) {
                                            iVar18 = _eventIndex + 1;
                                            if (iVar18 < this->eventsCount) {
                                                _pConditionIsMet = &this->scenarioEvents[_eventIndex + 1]
                                                                        .data.scenario.ScenarioEventType;
                                                do {
                                                    if (((_pConditionIsMet[-3] == 3)
                                                            && (((*_pConditionIsMet == 0 || (*_pConditionIsMet == 0x1a))
                                                                && (_pConditionIsMet[-4]
                                                                    <= DAT_GameState::instance.mapAndTime.year))))
                                                        && ((DAT_GameState::instance.mapAndTime.year
                                                                != _pConditionIsMet[-4]
                                                            || (_pConditionIsMet[-5]
                                                                < DAT_GameState::instance.mapAndTime.month))))
                                                        goto switchD_004c382e_caseD_2;
                                                    iVar18 = iVar18 + 1;
                                                    _pConditionIsMet = _pConditionIsMet + 0x39;
                                                } while (iVar18 < this->eventsCount);
                                            }
                                            if (((DAT_GameCore::instance.gameMode_2
                                                     == Game::GM_CAMPAIGN_MISSION)
                                                    || (DAT_GameCore::instance.gameMode_2
                                                        == Game::GM_ECONOMIC_CAMPAIGN_SH1))
                                                || (DAT_GameCore::instance.gameMode_2
                                                    == Game::GM_BUILDERUnk)) {
                                                DAT_GameState::instance
                                                    .playerDataArray[DAT_GameSynchronyState::instance
                                                            .currentPlayerSlotID]
                                                    .playerDeathRelated = 1;
                                                DAT_GameState::instance.mapAndTime.unknownCountdown01 = 0xf0;
                                                MACRO_CALL(UI::DisplayElements_Func::
                                                        CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                                                    UI::Enums::DEID_MISSION_WIN_DEFEAT_BANNER, 1);
                                                if ((DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                                                        == UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM)
                                                    || (DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                                                        == UI::Enums::BASMTT_SIEGETENT_SHIELD)) {
                                                    DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab
                                                        = DAT_GameCore::instance.tabTypeSiegeSubset;
                                                    MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView,
                                                        DAT_GameCore::ptr)(UI::Enums::MVT_BUILD_MENU, 0);
                                                }
                                                DAT_TileMapState::instance.currentMapperCommand
                                                    = Commands::M_MAPPER_NULL;
                                                if (0 < DAT_UnitsState::instance.totalUnitsInSelection) {
                                                    MACRO_CALL_MEMBER(
                                                        Map::Units::UnitsState_Func::deselectAllUnitsOneByOne,
                                                        DAT_UnitsState::ptr)();
                                                    MACRO_CALL_MEMBER(
                                                        Map::Units::UnitsState_Func::queueEscapeCommand,
                                                        DAT_UnitsState::ptr)();
                                                    MACRO_CALL_MEMBER(
                                                        Input::MouseState_Func::resetMouseCursorState,
                                                        DAT_MouseState::ptr)();
                                                }
                                                if (*(char*)((int)&this->scenarioEvents[_eventIndex].data + 0x13)
                                                    == '\0') {
                                                    if (*(char*)((int)&this->scenarioEvents[_eventIndex].data + 0x1f)
                                                        == '\0') {
                                                        if ((((*(char*)((int)&this->scenarioEvents[_eventIndex].data
                                                                   + 0x23)
                                                                  == '\0')
                                                                 && (*(char*)((int)&this->scenarioEvents[_eventIndex]
                                                                                  .data
                                                                         + 0x27)
                                                                     == '\0'))
                                                                && (*(char*)((int)&this->scenarioEvents[_eventIndex]
                                                                                 .data
                                                                        + 0x2b)
                                                                    == '\0'))
                                                            && (*(char*)((int)&this->scenarioEvents[_eventIndex].data
                                                                    + 0x53)
                                                                == '\0')) {
                                                            this->field133_0x145d8 = 1;
                                                            MACRO_CALL_MEMBER(
                                                                Map::MapPropertiesState_Func::sortEventsByDate,
                                                                this)();
                                                        } else {
                                                            this->field133_0x145d8 = 3;
                                                            MACRO_CALL_MEMBER(
                                                                Map::MapPropertiesState_Func::sortEventsByDate,
                                                                this)();
                                                        }
                                                    } else {
                                                        this->field133_0x145d8 = 2;
                                                        MACRO_CALL_MEMBER(
                                                            Map::MapPropertiesState_Func::sortEventsByDate,
                                                            this)();
                                                    }
                                                } else {
                                                    this->field133_0x145d8 = 1;
                                                    MACRO_CALL_MEMBER(
                                                        Map::MapPropertiesState_Func::sortEventsByDate,
                                                        this)();
                                                }
                                                break;
                                            }
                                        }
                                        goto switchD_004c382e_caseD_2;
                                    case 1:
                                        if ((DAT_GameState::instance
                                                    .playerDataArray[DAT_GameSynchronyState::instance
                                                            .currentPlayerSlotID]
                                                    .playerDeathRelated
                                                == 0)
                                            && ((
                                                (DAT_GameCore::instance.gameMode_2 == Game::GM_CAMPAIGN_MISSION
                                                    || (DAT_GameCore::instance.gameMode_2
                                                        == Game::GM_ECONOMIC_CAMPAIGN_SH1))
                                                || (DAT_GameCore::instance.gameMode_2
                                                    == Game::GM_BUILDERUnk)))) {
                                            DAT_GameState::instance
                                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                                .playerDeathRelated = 2;
                                            MACRO_CALL_MEMBER(
                                                Map::Units::UnitsState_Func::setAIControlStatusTo100000,
                                                DAT_UnitsState::ptr)();
                                            DAT_GameState::instance.mapAndTime.unknownCountdown01 = 0xf0;
                                            if ((DAT_GameCore::instance.gameMode_2 == Game::GM_BUILDERUnk)
                                                && (this->SEC_U3_MapType2_1 == Map::MT_SIEGE)) {
                                                DAT_GameState::instance.mapAndTime.unknownCountdown01 = 0x280;
                                            }
                                            MACRO_CALL(UI::DisplayElements_Func::
                                                    CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                                                UI::Enums::DEID_MISSION_WIN_DEFEAT_BANNER, 2);
                                            if ((DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                                                    == UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM)
                                                || (DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                                                    == UI::Enums::BASMTT_SIEGETENT_SHIELD)) {
                                                DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab
                                                    = DAT_GameCore::instance.tabTypeSiegeSubset;
                                                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView,
                                                    DAT_GameCore::ptr)(UI::Enums::MVT_BUILD_MENU, 0);
                                            }
                                            DAT_TileMapState::instance.currentMapperCommand
                                                = Commands::M_MAPPER_NULL;
                                            if (0 < DAT_UnitsState::instance.totalUnitsInSelection) {
                                                MACRO_CALL_MEMBER(
                                                    Map::Units::UnitsState_Func::deselectAllUnitsOneByOne,
                                                    DAT_UnitsState::ptr)();
                                                MACRO_CALL_MEMBER(
                                                    Map::Units::UnitsState_Func::queueEscapeCommand,
                                                    DAT_UnitsState::ptr)();
                                                MACRO_CALL_MEMBER(
                                                    Input::MouseState_Func::resetMouseCursorState,
                                                    DAT_MouseState::ptr)();
                                                MACRO_CALL_MEMBER(
                                                    Map::MapPropertiesState_Func::sortEventsByDate, this)();
                                                break;
                                            }
                                        }
                                    default:
                                        goto switchD_004c382e_caseD_2;
                                    case 3:
                                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::flagTribesOfType,
                                            DAT_TribesState::ptr)(0xe);
                                        MACRO_CALL_MEMBER(
                                            Map::MapPropertiesState_Func::sortEventsByDate, this)();
                                        break;
                                    case 4:
                                        iVar18 = this->scenarioEvents[_eventIndex].data.scenario.actionData;
                                        if (!iVar18) {
                                            iVar18 = 1;
                                        }
                                        MACRO_CALL_MEMBER(
                                            Map::Units::TribesState_Func::consumeFlaggedTribesOfType,
                                            DAT_TribesState::ptr)(0xe, iVar18);
                                        MACRO_CALL_MEMBER(
                                            Map::MapPropertiesState_Func::sortEventsByDate, this)();
                                        break;
                                    case 5:
                                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::spawnUnit,
                                            DAT_UnitsState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                                            (int)((int)(SEC_RNG::instance.currentNumber2 % 9)),
                                            DAT_GameState::instance
                                                    .playerDataArray[DAT_GameSynchronyState::instance
                                                            .currentPlayerSlotID]
                                                    .campground.xEntry
                                                * 8,
                                            DAT_GameState::instance
                                                    .playerDataArray[DAT_GameSynchronyState::instance
                                                            .currentPlayerSlotID]
                                                    .campground.yEntry
                                                * 8,
                                            (int)((int)((
                                                uint)DAT_TileMapState::instance.HeightLayer[DAT_GameState::instance
                                                    .playerDataArray[DAT_GameSynchronyState::instance
                                                            .currentPlayerSlotID]
                                                    .campground.tileEntry])),
                                            Map::Units::UT_JUGGLER);
                                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::spawnUnit,
                                            DAT_UnitsState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                                            (SEC_RNG::instance.currentNumber2 >> 3) % 9,
                                            DAT_GameState::instance
                                                    .playerDataArray[DAT_GameSynchronyState::instance
                                                            .currentPlayerSlotID]
                                                    .campground.xEntry
                                                * 8,
                                            DAT_GameState::instance
                                                    .playerDataArray[DAT_GameSynchronyState::instance
                                                            .currentPlayerSlotID]
                                                    .campground.yEntry
                                                * 8,
                                            (UnitType)((int)((
                                                uint)DAT_TileMapState::instance.HeightLayer[DAT_GameState::instance
                                                    .playerDataArray[DAT_GameSynchronyState::instance
                                                            .currentPlayerSlotID]
                                                    .campground.tileEntry])),
                                            Map::Units::UT_JUGGLER);
                                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::spawnUnit,
                                            DAT_UnitsState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                                            (SEC_RNG::instance.currentNumber2 >> 6) % 9,
                                            DAT_GameState::instance
                                                    .playerDataArray[DAT_GameSynchronyState::instance
                                                            .currentPlayerSlotID]
                                                    .campground.xEntry
                                                * 8,
                                            DAT_GameState::instance
                                                    .playerDataArray[DAT_GameSynchronyState::instance
                                                            .currentPlayerSlotID]
                                                    .campground.yEntry
                                                * 8,
                                            (UnitType)((int)((
                                                uint)DAT_TileMapState::instance.HeightLayer[DAT_GameState::instance
                                                    .playerDataArray[DAT_GameSynchronyState::instance
                                                            .currentPlayerSlotID]
                                                    .campground.tileEntry])),
                                            Map::Units::UT_JUGGLER);
                                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::spawnUnit,
                                            DAT_UnitsState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                                            (SEC_RNG::instance.currentNumber2 >> 9) % 9,
                                            DAT_GameState::instance
                                                    .playerDataArray[DAT_GameSynchronyState::instance
                                                            .currentPlayerSlotID]
                                                    .campground.xEntry
                                                * 8,
                                            DAT_GameState::instance
                                                    .playerDataArray[DAT_GameSynchronyState::instance
                                                            .currentPlayerSlotID]
                                                    .campground.yEntry
                                                * 8,
                                            (UnitType)((int)((
                                                uint)DAT_TileMapState::instance.HeightLayer[DAT_GameState::instance
                                                    .playerDataArray[DAT_GameSynchronyState::instance
                                                            .currentPlayerSlotID]
                                                    .campground.tileEntry])),
                                            Map::Units::UT_FIREEATER);
                                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::spawnUnit,
                                            DAT_UnitsState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                                            (SEC_RNG::instance.currentNumber2 >> 0xc) % 9,
                                            DAT_GameState::instance
                                                    .playerDataArray[DAT_GameSynchronyState::instance
                                                            .currentPlayerSlotID]
                                                    .campground.xEntry
                                                * 8,
                                            DAT_GameState::instance
                                                    .playerDataArray[DAT_GameSynchronyState::instance
                                                            .currentPlayerSlotID]
                                                    .campground.yEntry
                                                * 8,
                                            (UnitType)((int)((
                                                uint)DAT_TileMapState::instance.HeightLayer[DAT_GameState::instance
                                                    .playerDataArray[DAT_GameSynchronyState::instance
                                                            .currentPlayerSlotID]
                                                    .campground.tileEntry])),
                                            Map::Units::UT_FIREEATER);
                                        pcVar25 = "Random_Events1.wav";
                                        pcVar26 = DAT_MissionAestheticsDefinedData::instance.RandomEvent1VideoName;
                                        /*
                                          "a travelling fair has come to town my lord"   added by script: "A ‘Travelling
                                          Fair’ has come to town, my Lord."
                                         */
                                        pcVar10 = MACRO_CALL_MEMBER(
                                            Text::TextManager_Func::getTextStringInGroupAtOffset,
                                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ACTION, 1);
                                        MACRO_CALL_MEMBER(
                                            Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                                            DAT_VideoBikQueue::ptr)(pcVar10, pcVar26, pcVar25);
                                        bVar4 = this->scenarioEvents[_eventIndex].data.scenario.repeat;
                                        if ((!bVar4)
                                            || (bVar5 = this->scenarioEvents[_eventIndex].data.scenario.repeatMonths,
                                                bVar5 == 1))
                                            goto switchD_004c382e_caseD_2;
                                        if (bVar5 != 10) {
                                            this->scenarioEvents[_eventIndex].data.scenario.repeatMonths = bVar5 - 1;
                                        }
                                        uVar19 = (uint)bVar4;
                                        this->scenarioEvents[_eventIndex].header.done = 0;
                                        if (3 < uVar19) {
                                            uVar19
                                                = uVar19 + (int)SEC_RNG::instance.currentNumber2 % ((int)uVar19 >> 2);
                                        }
                                        this->scenarioEvents[_eventIndex].header.year
                                            = DAT_GameState::instance.mapAndTime.year + (int)uVar19 / 0xc;
                                        iVar18 = uVar19 + DAT_GameState::instance.mapAndTime.month
                                            + ((int)uVar19 / 0xc) * -0xc;
                                        this->scenarioEvents[_eventIndex].header.month = iVar18;
                                        if (0xb < iVar18) {
                                            _pConditionIsMet = &this->scenarioEvents[_eventIndex].header.year;
                                            *_pConditionIsMet = *_pConditionIsMet + 1;
                                            this->scenarioEvents[_eventIndex].header.month = iVar18 + -0xc;
                                        }
                                    LAB_004c4621:
                                        MACRO_CALL_MEMBER(
                                            Map::MapPropertiesState_Func::sortEventsByDate, this)();
                                        _eventIndex = _eventIndex + -1;
                                        break;
                                    case 6:
                                        DAT_GameCore::instance.isTimeHalted = TRUE;
                                        MACRO_CALL_MEMBER(
                                            Map::MapPropertiesState_Func::sortEventsByDate, this)();
                                        break;
                                    case 7:
                                        DAT_GameCore::instance.isTimeHalted = FALSE;
                                        MACRO_CALL_MEMBER(
                                            Map::MapPropertiesState_Func::sortEventsByDate, this)();
                                        break;
                                    case 8:
                                        MACRO_CALL_MEMBER(
                                            Game::GameStateStructures_Func::switchPlayerOwnership,
                                            DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID);
                                        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::
                                                              setupBarracksCampgroundPositions,
                                            DAT_BuildingsState::ptr)(
                                            DAT_GameSynchronyState::instance.currentPlayerSlotID);
                                        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::
                                                              setupMercenaryPostCampgroundPositions,
                                            DAT_BuildingsState::ptr)(
                                            DAT_GameSynchronyState::instance.currentPlayerSlotID);
                                        MACRO_CALL_MEMBER(
                                            Map::Units::UnitsState_Func::triggerStoneTowerDeathForPlayer,
                                            DAT_UnitsState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID);
                                        MACRO_CALL_MEMBER(
                                            Map::Buildings::BuildingsState_Func::countPlayerResources,
                                            DAT_BuildingsState::ptr)(
                                            DAT_GameSynchronyState::instance.currentPlayerSlotID);
                                        DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                                            = UI::Enums::BASMTT_HUNTERSHUT;
                                        DAT_GameCore::instance.secondaryActiveMenuTabToSwitchTo.tabType
                                            = UI::Enums::BASMTT_HUNTERSHUT;
                                        DAT_GameCore::instance.tabTypeSiegeSubset = UI::Enums::BMTT_CASTLE;
                                        if (((DAT_GameCore::instance.currentMenuViewType
                                                 == UI::Enums::MVT_BUILD_MENU)
                                                && ((DAT_GameCore::instance.activeMenuTab.tabType
                                                        != UI::Enums::BASMTT_STOCKS
                                                    || (MACRO_CALL_MEMBER(
                                                            Game::GameCore_Func::switchToMenuView,
                                                            DAT_GameCore::ptr)(UI::Enums::MVT_BUILD_MENU, 0),
                                                        DAT_GameCore::instance.currentMenuViewType
                                                            == UI::Enums::MVT_BUILD_MENU))))
                                            && ((DAT_GameCore::instance.activeMenuTab.tabType
                                                    == UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM
                                                || (DAT_GameCore::instance.activeMenuTab.tabType
                                                    == UI::Enums::BASMTT_SIEGETENT_SHIELD)))) {
                                            DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                                                = UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM;
                                            MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView,
                                                DAT_GameCore::ptr)(UI::Enums::MVT_BUILD_MENU, 0);
                                        }
                                        iVar22 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                                        iVar18
                                            = DAT_GameState::instance
                                                  .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                                  .lordID;
                                        if ((!iVar18)
                                            || (DAT_GameState::instance
                                                    .playerDataArray[DAT_GameSynchronyState::instance
                                                            .currentPlayerSlotID]
                                                    .lordUID
                                                == DAT_UnitsState::instance.units[iVar18].uid))
                                            goto switchD_004c382e_caseD_2;
                                        DAT_GameState::instance
                                            .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                            .lordID = 0;
                                        DAT_GameState::instance.playerDataArray[iVar22].lordUID = 0;
                                        MACRO_CALL_MEMBER(
                                            Map::MapPropertiesState_Func::sortEventsByDate, this)();
                                        break;
                                    case 9:
                                        DAT_GameCore::instance.xbowProducible_logic = 1;
                                        MACRO_CALL_MEMBER(
                                            Map::MapPropertiesState_Func::sortEventsByDate, this)();
                                        break;
                                    case 0xb:
                                        DAT_GameState::instance
                                            .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                            .someCount48 = 0x18;
                                        iVar22 = DAT_GameState::instance.playerDataArray[iVar18].popularity;
                                        if (6000 < iVar22) {
                                            DAT_GameState::instance.playerDataArray[iVar18].popularity
                                                = (iVar22 + -6000) / 2 + 6000;
                                        }
                                        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::
                                                              spawnPoisonCloudsAtRandomStorageOrArmyBuilding,
                                            DAT_GameState::ptr)(
                                            iVar18, this->scenarioEvents[_eventIndex].data.scenario.actionData);
                                        pcVar25 = "Random_Events2.wav";
                                        pcVar26 = DAT_MissionAestheticsDefinedData::instance.RandomEvent2VideoName;
                                        /*
                                          added by script: "Plague has descended on our castle your lordship."
                                         */
                                        pcVar10 = MACRO_CALL_MEMBER(
                                            Text::TextManager_Func::getTextStringInGroupAtOffset,
                                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ACTION, 2);
                                        MACRO_CALL_MEMBER(
                                            Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                                            DAT_VideoBikQueue::ptr)(pcVar10, pcVar26, pcVar25);
                                        bVar4 = this->scenarioEvents[_eventIndex].data.scenario.repeat;
                                        if ((!bVar4)
                                            || (bVar5 = this->scenarioEvents[_eventIndex].data.scenario.repeatMonths,
                                                bVar5 == 1))
                                            goto switchD_004c382e_caseD_2;
                                        if (bVar5 != 10) {
                                            this->scenarioEvents[_eventIndex].data.scenario.repeatMonths = bVar5 - 1;
                                        }
                                        uVar19 = (uint)bVar4;
                                        this->scenarioEvents[_eventIndex].header.done = 0;
                                        if (3 < uVar19) {
                                            uVar19
                                                = uVar19 + (int)SEC_RNG::instance.currentNumber2 % ((int)uVar19 >> 2);
                                        }
                                        this->scenarioEvents[_eventIndex].header.year
                                            = DAT_GameState::instance.mapAndTime.year + (int)uVar19 / 0xc;
                                        iVar18 = uVar19 + DAT_GameState::instance.mapAndTime.month
                                            + ((int)uVar19 / 0xc) * -0xc;
                                        this->scenarioEvents[_eventIndex].header.month = iVar18;
                                        if (iVar18 < 0xc)
                                            goto LAB_004c4621;
                                        _pConditionIsMet = &this->scenarioEvents[_eventIndex].header.year;
                                        *_pConditionIsMet = *_pConditionIsMet + 1;
                                        this->scenarioEvents[_eventIndex].header.month = iVar18 + -0xc;
                                        MACRO_CALL_MEMBER(
                                            Map::MapPropertiesState_Func::sortEventsByDate, this)();
                                        _eventIndex = _eventIndex + -1;
                                        break;
                                    case 0xc:
                                        iVar18 = MACRO_CALL_MEMBER(
                                            Map::Buildings::BuildingsState_Func::findBuildingOfTypeForPlayer,
                                            DAT_BuildingsState::ptr)(
                                            DAT_GameSynchronyState::instance.currentPlayerSlotID,
                                            Map::Buildings::BT_WHEATFARM);
                                        if (iVar18) {
                                            MACRO_CALL_MEMBER(
                                                Map::Buildings::BuildingsState_Func::harmWheatFarmsOfPlayer,
                                                DAT_BuildingsState::ptr)(
                                                DAT_GameSynchronyState::instance.currentPlayerSlotID);
                                            pcVar25 = "Random_Events3.wav";
                                            pcVar26 = DAT_MissionAestheticsDefinedData::instance.RandomEvent3VideoName;
                                            /*
                                              added by script: "A pestilence is devastating our wheat crops, Sire."
                                             */
                                            pcVar10 = MACRO_CALL_MEMBER(
                                                Text::TextManager_Func::getTextStringInGroupAtOffset,
                                                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ACTION, 3);
                                            MACRO_CALL_MEMBER(
                                                Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                                                DAT_VideoBikQueue::ptr)(pcVar10, pcVar26, pcVar25);
                                        }
                                        bVar4 = this->scenarioEvents[_eventIndex].data.scenario.repeat;
                                        if ((!bVar4)
                                            || (bVar5 = this->scenarioEvents[_eventIndex].data.scenario.repeatMonths,
                                                bVar5 == 1))
                                            goto switchD_004c382e_caseD_2;
                                        if (bVar5 != 10) {
                                            this->scenarioEvents[_eventIndex].data.scenario.repeatMonths = bVar5 - 1;
                                        }
                                        uVar19 = (uint)bVar4;
                                        this->scenarioEvents[_eventIndex].header.done = 0;
                                        if (3 < uVar19) {
                                            uVar19
                                                = uVar19 + (int)SEC_RNG::instance.currentNumber2 % ((int)uVar19 >> 2);
                                        }
                                        this->scenarioEvents[_eventIndex].header.year
                                            = DAT_GameState::instance.mapAndTime.year + (int)uVar19 / 0xc;
                                        iVar18 = uVar19 + DAT_GameState::instance.mapAndTime.month
                                            + ((int)uVar19 / 0xc) * -0xc;
                                        this->scenarioEvents[_eventIndex].header.month = iVar18;
                                        if (iVar18 < 0xc)
                                            goto LAB_004c4621;
                                        _pConditionIsMet = &this->scenarioEvents[_eventIndex].header.year;
                                        *_pConditionIsMet = *_pConditionIsMet + 1;
                                        this->scenarioEvents[_eventIndex].header.month = iVar18 + -0xc;
                                        MACRO_CALL_MEMBER(
                                            Map::MapPropertiesState_Func::sortEventsByDate, this)();
                                        _eventIndex = _eventIndex + -1;
                                        break;
                                    case 0xd:
                                        iVar18 = MACRO_CALL_MEMBER(
                                            Map::Buildings::BuildingsState_Func::findBuildingOfTypeForPlayer,
                                            DAT_BuildingsState::ptr)(
                                            DAT_GameSynchronyState::instance.currentPlayerSlotID,
                                            Map::Buildings::BT_HOPFARM);
                                        if (iVar18) {
                                            MACRO_CALL_MEMBER(
                                                Map::Buildings::BuildingsState_Func::harmHopFarmsOfPlayer,
                                                DAT_BuildingsState::ptr)(
                                                DAT_GameSynchronyState::instance.currentPlayerSlotID);
                                            pcVar25 = "Random_Events4.wav";
                                            pcVar26 = DAT_MissionAestheticsDefinedData::instance.RandomEvent4VideoName;
                                            /*
                                              added by script: "Our hops plants are overrun with hop weevil, the crop is
                                              ruined, My Liege."
                                             */
                                            pcVar10 = MACRO_CALL_MEMBER(
                                                Text::TextManager_Func::getTextStringInGroupAtOffset,
                                                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ACTION, 4);
                                            MACRO_CALL_MEMBER(
                                                Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                                                DAT_VideoBikQueue::ptr)(pcVar10, pcVar26, pcVar25);
                                        }
                                        bVar4 = this->scenarioEvents[_eventIndex].data.scenario.repeat;
                                        if ((!bVar4)
                                            || (bVar5 = this->scenarioEvents[_eventIndex].data.scenario.repeatMonths,
                                                bVar5 == 1))
                                            goto switchD_004c382e_caseD_2;
                                        if (bVar5 != 10) {
                                            this->scenarioEvents[_eventIndex].data.scenario.repeatMonths = bVar5 - 1;
                                        }
                                        uVar19 = (uint)bVar4;
                                        this->scenarioEvents[_eventIndex].header.done = 0;
                                        if (3 < uVar19) {
                                            uVar19
                                                = uVar19 + (int)SEC_RNG::instance.currentNumber2 % ((int)uVar19 >> 2);
                                        }
                                        this->scenarioEvents[_eventIndex].header.year
                                            = DAT_GameState::instance.mapAndTime.year + (int)uVar19 / 0xc;
                                        iVar18 = uVar19 + DAT_GameState::instance.mapAndTime.month
                                            + ((int)uVar19 / 0xc) * -0xc;
                                        this->scenarioEvents[_eventIndex].header.month = iVar18;
                                        if (iVar18 < 0xc)
                                            goto LAB_004c4621;
                                        _pConditionIsMet = &this->scenarioEvents[_eventIndex].header.year;
                                        *_pConditionIsMet = *_pConditionIsMet + 1;
                                        this->scenarioEvents[_eventIndex].header.month = iVar18 + -0xc;
                                        MACRO_CALL_MEMBER(
                                            Map::MapPropertiesState_Func::sortEventsByDate, this)();
                                        _eventIndex = _eventIndex + -1;
                                        break;
                                    case 0xe:
                                        iVar18 = MACRO_CALL_MEMBER(
                                            Map::Buildings::BuildingsState_Func::findBuildingOfTypeForPlayer,
                                            DAT_BuildingsState::ptr)(
                                            DAT_GameSynchronyState::instance.currentPlayerSlotID,
                                            Map::Buildings::BT_APPLEFARM);
                                        if (iVar18) {
                                            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::
                                                                  harmAppleFarmTreesOfPlayer,
                                                DAT_BuildingsState::ptr)(
                                                DAT_GameSynchronyState::instance.currentPlayerSlotID);
                                            pcVar27 = "Random_Events5.wav";
                                            pcVar25 = "";
                                            /*
                                              added by script: "Our apple orchards are barren, my lord.  The people
                                              suspect   witchcraft."
                                             */
                                            pcVar10 = MACRO_CALL_MEMBER(
                                                Text::TextManager_Func::getTextStringInGroupAtOffset,
                                                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ACTION, 5);
                                            MACRO_CALL_MEMBER(
                                                Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                                                DAT_VideoBikQueue::ptr)(pcVar10, pcVar25, pcVar27);
                                            MACRO_CALL_MEMBER(
                                                Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                                                DAT_VideoBikQueue::ptr)("",
                                                (char*)((int)(DAT_MissionAestheticsDefinedData::instance.RandomEvent5VideoName)),
                                                "");
                                        }
                                        bVar4 = this->scenarioEvents[_eventIndex].data.scenario.repeat;
                                        if ((!bVar4)
                                            || (bVar5 = this->scenarioEvents[_eventIndex].data.scenario.repeatMonths,
                                                bVar5 == 1))
                                            goto switchD_004c382e_caseD_2;
                                        if (bVar5 != 10) {
                                            this->scenarioEvents[_eventIndex].data.scenario.repeatMonths = bVar5 - 1;
                                        }
                                        uVar19 = (uint)bVar4;
                                        this->scenarioEvents[_eventIndex].header.done = 0;
                                        if (3 < uVar19) {
                                            uVar19
                                                = uVar19 + (int)SEC_RNG::instance.currentNumber2 % ((int)uVar19 >> 2);
                                        }
                                        this->scenarioEvents[_eventIndex].header.year
                                            = DAT_GameState::instance.mapAndTime.year + (int)uVar19 / 0xc;
                                        iVar18 = uVar19 + DAT_GameState::instance.mapAndTime.month
                                            + ((int)uVar19 / 0xc) * -0xc;
                                        this->scenarioEvents[_eventIndex].header.month = iVar18;
                                        if (iVar18 < 0xc)
                                            goto LAB_004c4621;
                                        _pConditionIsMet = &this->scenarioEvents[_eventIndex].header.year;
                                        *_pConditionIsMet = *_pConditionIsMet + 1;
                                        this->scenarioEvents[_eventIndex].header.month = iVar18 + -0xc;
                                        MACRO_CALL_MEMBER(
                                            Map::MapPropertiesState_Func::sortEventsByDate, this)();
                                        _eventIndex = _eventIndex + -1;
                                        break;
                                    case 0xf:
                                        MACRO_CALL_MEMBER(Map::LandscapeState_Func::killEveryFifthTree,
                                            DAT_LandscapeState::ptr)();
                                        pcVar25 = "Random_Events6.wav";
                                        pcVar26 = DAT_MissionAestheticsDefinedData::instance.RandomEvent6VideoName;
                                        /*
                                          added by script: "Sire, woodcutters report that the recent drought has killed
                                          off many trees."
                                         */
                                        pcVar10 = MACRO_CALL_MEMBER(
                                            Text::TextManager_Func::getTextStringInGroupAtOffset,
                                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ACTION, 6);
                                        MACRO_CALL_MEMBER(
                                            Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                                            DAT_VideoBikQueue::ptr)(pcVar10, pcVar26, pcVar25);
                                        bVar4 = this->scenarioEvents[_eventIndex].data.scenario.repeat;
                                        if ((!bVar4)
                                            || (bVar5 = this->scenarioEvents[_eventIndex].data.scenario.repeatMonths,
                                                bVar5 == 1))
                                            goto switchD_004c382e_caseD_2;
                                        if (bVar5 != 10) {
                                            this->scenarioEvents[_eventIndex].data.scenario.repeatMonths = bVar5 - 1;
                                        }
                                        uVar19 = (uint)bVar4;
                                        this->scenarioEvents[_eventIndex].header.done = 0;
                                        if (3 < uVar19) {
                                            uVar19
                                                = uVar19 + (int)SEC_RNG::instance.currentNumber2 % ((int)uVar19 >> 2);
                                        }
                                        this->scenarioEvents[_eventIndex].header.year
                                            = DAT_GameState::instance.mapAndTime.year + (int)uVar19 / 0xc;
                                        iVar18 = uVar19 + DAT_GameState::instance.mapAndTime.month
                                            + ((int)uVar19 / 0xc) * -0xc;
                                        this->scenarioEvents[_eventIndex].header.month = iVar18;
                                        if (iVar18 < 0xc)
                                            goto LAB_004c4621;
                                        _pConditionIsMet = &this->scenarioEvents[_eventIndex].header.year;
                                        *_pConditionIsMet = *_pConditionIsMet + 1;
                                        this->scenarioEvents[_eventIndex].header.month = iVar18 + -0xc;
                                        MACRO_CALL_MEMBER(
                                            Map::MapPropertiesState_Func::sortEventsByDate, this)();
                                        _eventIndex = _eventIndex + -1;
                                        break;
                                    case 0x10:
                                        iVar18 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::
                                                                       hasAvailableSpawnSlotForWildlifeOrMercs,
                                            DAT_TribesState::ptr)();
                                        if ((iVar18)
                                            && ((iVar18 = MACRO_CALL_MEMBER(
                                                     Map::Buildings::BuildingsState_Func::findBuildingOfTypeForPlayer,
                                                     DAT_BuildingsState::ptr)(
                                                     DAT_GameSynchronyState::instance.currentPlayerSlotID,
                                                     Map::Buildings::BT_HOPFARM),
                                                iVar18 != 0
                                                    || (iVar18 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::
                                                                                       findBuildingOfTypeForPlayer,
                                                            DAT_BuildingsState::ptr)(
                                                            DAT_GameSynchronyState::instance.currentPlayerSlotID,
                                                            Map::Buildings::BT_WHEATFARM),
                                                        iVar18 != 0)))) {
                                            DAT_GameState::instance.mapAndTime.eventCountdownRabbitInfestation = 1200;
                                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::
                                                                  spawnWildlifeOrMercAtAvailableSlot,
                                                DAT_TribesState::ptr)();
                                            MACRO_CALL_MEMBER(UI::MinimapViewState_Func::setSpawnMoment,
                                                DAT_MinimapViewState::ptr)(DAT_TribesState::instance.unknownX_01,
                                                DAT_TribesState::instance.unknownY_01);
                                            pcVar25 = "Random_Events7.wav";
                                            pcVar26 = DAT_MissionAestheticsDefinedData::instance.RandomEvent7VideoName;
                                            /*
                                              added by script: "Rabbits are breeding at an alarming rate Liege.  Our
                                              crops   are threatened."
                                             */
                                            pcVar10 = MACRO_CALL_MEMBER(
                                                Text::TextManager_Func::getTextStringInGroupAtOffset,
                                                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ACTION, 7);
                                            MACRO_CALL_MEMBER(
                                                Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                                                DAT_VideoBikQueue::ptr)(pcVar10, pcVar26, pcVar25);
                                        }
                                        bVar4 = this->scenarioEvents[_eventIndex].data.scenario.repeat;
                                        if ((!bVar4)
                                            || (bVar5 = this->scenarioEvents[_eventIndex].data.scenario.repeatMonths,
                                                bVar5 == 1))
                                            goto switchD_004c382e_caseD_2;
                                        if (bVar5 != 10) {
                                            this->scenarioEvents[_eventIndex].data.scenario.repeatMonths = bVar5 - 1;
                                        }
                                        uVar19 = (uint)bVar4;
                                        this->scenarioEvents[_eventIndex].header.done = 0;
                                        if (3 < uVar19) {
                                            uVar19
                                                = uVar19 + (int)SEC_RNG::instance.currentNumber2 % ((int)uVar19 >> 2);
                                        }
                                        this->scenarioEvents[_eventIndex].header.year
                                            = DAT_GameState::instance.mapAndTime.year + (int)uVar19 / 0xc;
                                        iVar18 = uVar19 + DAT_GameState::instance.mapAndTime.month
                                            + ((int)uVar19 / 0xc) * -0xc;
                                        this->scenarioEvents[_eventIndex].header.month = iVar18;
                                        if (iVar18 < 0xc)
                                            goto LAB_004c4621;
                                        _pConditionIsMet = &this->scenarioEvents[_eventIndex].header.year;
                                        *_pConditionIsMet = *_pConditionIsMet + 1;
                                        this->scenarioEvents[_eventIndex].header.month = iVar18 + -0xc;
                                        MACRO_CALL_MEMBER(
                                            Map::MapPropertiesState_Func::sortEventsByDate, this)();
                                        _eventIndex = _eventIndex + -1;
                                        break;
                                    case 0x11:
                                        iVar18 = MACRO_CALL_MEMBER(
                                            Map::Units::TribesState_Func::findRecentOrSignpostSpawnLocation,
                                            DAT_TribesState::ptr)(&uStack_78, &uStack_7c);
                                        if ((iVar18)
                                            && (BVar11
                                                = MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::xyAreValid,
                                                    DAT_ViewportRenderState::ptr)(uStack_78, uStack_7c),
                                                iVar18 = DAT_GameSynchronyState::instance.currentPlayerSlotID,
                                                BVar11)) {
                                            DAT_GameState::instance
                                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                                .someCount49 = 0xc;
                                            iVar22 = DAT_GameState::instance.playerDataArray[iVar18].popularity;
                                            if (6000 < iVar22) {
                                                DAT_GameState::instance.playerDataArray[iVar18].popularity
                                                    = (iVar22 + -6000) / 2 + 6000;
                                            }
                                            iVar18 = 0;
                                            if (0 < this->scenarioEvents[_eventIndex].data.scenario.actionData) {
                                                do {
                                                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::
                                                                          findRecentOrSignpostSpawnLocation,
                                                        DAT_TribesState::ptr)(&uStack_78, &uStack_7c);
                                                    dVar14 = MACRO_CALL_MEMBER(
                                                        Map::Units::TribesState_Func::createAnimal,
                                                        DAT_TribesState::ptr)(Commands::M_MAPPER_LION,
                                                        uStack_78, uStack_7c,
                                                        (int)((int)((uint)
                                                            * (byte*)(DAT_ViewportRenderState::instance
                                                                          .translationMatrix[uStack_7c]
                                                                          .addXgetTile
                                                                + 0x1d32c38 + uStack_78))));
                                                    MACRO_CALL_MEMBER(
                                                        UI::MinimapViewState_Func::setSpawnMoment,
                                                        DAT_MinimapViewState::ptr)(uStack_78, (int)((int)(uStack_7c)));
                                                    iVar18 = iVar18 + 1;
                                                    DAT_TribesState::instance.tribes[dVar14].unknownBool02 = 0;
                                                    DAT_TribesState::instance.tribes[dVar14].unknownBool01 = 1;
                                                } while (iVar18
                                                    < this->scenarioEvents[_eventIndex].data.scenario.actionData);
                                            }
                                            pcVar27 = "";
                                            pcVar25 = "";
                                            /*
                                              added by script: "I have alarming reports that lions are abroad in the
                                              land.   People are scared my Lord."
                                             */
                                            pcVar10 = MACRO_CALL_MEMBER(
                                                Text::TextManager_Func::getTextStringInGroupAtOffset,
                                                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ACTION, 8);
                                            MACRO_CALL_MEMBER(
                                                Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                                                DAT_VideoBikQueue::ptr)(pcVar10, pcVar25, pcVar27);
                                        }
                                        bVar4 = this->scenarioEvents[_eventIndex].data.scenario.repeat;
                                        if ((!bVar4)
                                            || (bVar5 = this->scenarioEvents[_eventIndex].data.scenario.repeatMonths,
                                                bVar5 == 1))
                                            goto switchD_004c382e_caseD_2;
                                        if (bVar5 != 10) {
                                            this->scenarioEvents[_eventIndex].data.scenario.repeatMonths = bVar5 - 1;
                                        }
                                        uVar19 = (uint)bVar4;
                                        this->scenarioEvents[_eventIndex].header.done = 0;
                                        if (3 < uVar19) {
                                            uVar19
                                                = uVar19 + (int)SEC_RNG::instance.currentNumber2 % ((int)uVar19 >> 2);
                                        }
                                        this->scenarioEvents[_eventIndex].header.year
                                            = DAT_GameState::instance.mapAndTime.year + (int)uVar19 / 0xc;
                                        iVar18 = uVar19 + DAT_GameState::instance.mapAndTime.month
                                            + ((int)uVar19 / 0xc) * -0xc;
                                        this->scenarioEvents[_eventIndex].header.month = iVar18;
                                        if (iVar18 < 0xc)
                                            goto LAB_004c4621;
                                        _pConditionIsMet = &this->scenarioEvents[_eventIndex].header.year;
                                        *_pConditionIsMet = *_pConditionIsMet + 1;
                                        this->scenarioEvents[_eventIndex].header.month = iVar18 + -0xc;
                                        MACRO_CALL_MEMBER(
                                            Map::MapPropertiesState_Func::sortEventsByDate, this)();
                                        _eventIndex = _eventIndex + -1;
                                        break;
                                    case 0x12:
                                        BVar11
                                            = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::hasAnySignpost,
                                                DAT_GameState::ptr)();
                                        if (BVar11) {
                                            DAT_GameState::instance
                                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                                .someCount50 = 0x10;
                                            DAT_TroopValueState::instance.attackInfo.inv_count
                                                = DAT_TroopValueState::instance.attackInfo.inv_count + 1;
                                            if (0x31 < DAT_TroopValueState::instance.attackInfo.inv_count) {
                                                DAT_TroopValueState::instance.attackInfo.inv_count = 1;
                                            }
                                            MACRO_CALL_MEMBER(
                                                Map::Units::TroopValueState_Func::initializeAttackWaveSlot,
                                                DAT_TroopValueState::ptr)(
                                                DAT_TroopValueState::instance.attackInfo.inv_count, 0);
                                            DAT_TroopValueState::instance.attackInfo.attackWavePlayerIDArray
                                                [DAT_TroopValueState::instance.attackInfo.inv_count] = 8;
                                            iVar18 = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::
                                                                           pickRandomAccessibleSignpostEntry,
                                                DAT_GameState::ptr)();
                                            dVar14 = MACRO_CALL_MEMBER(
                                                Map::Units::TribesState_Func::createTribeWithSpawnedUnit,
                                                DAT_TribesState::ptr)(0, 9,
                                                DAT_GameState::instance.mapAndTime.signpostEntryData[iVar18].x,
                                                DAT_GameState::instance.mapAndTime.signpostEntryData[iVar18].y, 8,
                                                Map::Units::UT_E_MACE,
                                                this->scenarioEvents[_eventIndex].data.scenario.actionData + 1);
                                            MACRO_CALL_MEMBER(UI::MinimapViewState_Func::setSpawnMoment,
                                                DAT_MinimapViewState::ptr)(
                                                DAT_GameState::instance.mapAndTime.signpostEntryData[iVar18].x,
                                                DAT_GameState::instance.mapAndTime.signpostEntryData[iVar18].y);
                                            iVar18 = 0;
                                            if (0 < DAT_TribesState::instance.tribes[dVar14].size) {
                                                do {
                                                    iVar22 = MACRO_CALL_MEMBER(
                                                        Map::Units::TribesState_Func::getUnitIDForIndexInTribe,
                                                        DAT_TribesState::ptr)(dVar14, iVar18);
                                                    sVar7 = DAT_TribesState::instance.tribes[dVar14].size;
                                                    iVar18 = iVar18 + 1;
                                                    DAT_UnitsState::instance.units[iVar22].calculatedOwnerPlayerIndex
                                                        = 5;
                                                    DAT_UnitsState::instance.units[iVar22].logicalState
                                                        = Map::Units::ULS_NORMAL;
                                                } while (iVar18 < sVar7);
                                            }
                                            pcVar25 = "Random_Events9.wav";
                                            pcVar26 = DAT_MissionAestheticsDefinedData::instance.RandomEvent9VideoName;
                                            /*
                                              added by script: "Bandits are operating near the castle Lordship."
                                             */
                                            pcVar10 = MACRO_CALL_MEMBER(
                                                Text::TextManager_Func::getTextStringInGroupAtOffset,
                                                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ACTION, 9);
                                            MACRO_CALL_MEMBER(
                                                Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                                                DAT_VideoBikQueue::ptr)(pcVar10, pcVar26, pcVar25);
                                        }
                                        bVar4 = this->scenarioEvents[_eventIndex].data.scenario.repeat;
                                        if ((!bVar4)
                                            || (bVar5 = this->scenarioEvents[_eventIndex].data.scenario.repeatMonths,
                                                bVar5 == 1))
                                            goto switchD_004c382e_caseD_2;
                                        if (bVar5 != 10) {
                                            this->scenarioEvents[_eventIndex].data.scenario.repeatMonths = bVar5 - 1;
                                        }
                                        uVar19 = (uint)bVar4;
                                        this->scenarioEvents[_eventIndex].header.done = 0;
                                        if (3 < uVar19) {
                                            uVar19
                                                = uVar19 + (int)SEC_RNG::instance.currentNumber2 % ((int)uVar19 >> 2);
                                        }
                                        this->scenarioEvents[_eventIndex].header.year
                                            = DAT_GameState::instance.mapAndTime.year + (int)uVar19 / 0xc;
                                        iVar18 = uVar19 + DAT_GameState::instance.mapAndTime.month
                                            + ((int)uVar19 / 0xc) * -0xc;
                                        this->scenarioEvents[_eventIndex].header.month = iVar18;
                                        if (iVar18 < 0xc)
                                            goto LAB_004c4621;
                                        _pConditionIsMet = &this->scenarioEvents[_eventIndex].header.year;
                                        *_pConditionIsMet = *_pConditionIsMet + 1;
                                        this->scenarioEvents[_eventIndex].header.month = iVar18 + -0xc;
                                        MACRO_CALL_MEMBER(
                                            Map::MapPropertiesState_Func::sortEventsByDate, this)();
                                        _eventIndex = _eventIndex + -1;
                                        break;
                                    case 0x13:
                                        iVar18 = MACRO_CALL_MEMBER(
                                            Map::Buildings::BuildingsState_Func::findBuildingOfTypeForPlayer,
                                            DAT_BuildingsState::ptr)(
                                            DAT_GameSynchronyState::instance.currentPlayerSlotID,
                                            Map::Buildings::BT_DAIRYFARM);
                                        if (iVar18) {
                                            MACRO_CALL_MEMBER(
                                                Map::Units::UnitsState_Func::setRandomNumberOnCows,
                                                DAT_UnitsState::ptr)(
                                                DAT_GameSynchronyState::instance.currentPlayerSlotID);
                                            MACRO_CALL_MEMBER(
                                                Map::Buildings::BuildingsState_Func::setDairyFarmCheeseCounter,
                                                DAT_BuildingsState::ptr)(
                                                DAT_GameSynchronyState::instance.currentPlayerSlotID);
                                            pcVar27 = "Random_Events10.wav";
                                            pcVar25 = "";
                                            /*
                                              added by script: "Our cows have been struck down by a strange malady, my
                                              lord."
                                             */
                                            pcVar10 = MACRO_CALL_MEMBER(
                                                Text::TextManager_Func::getTextStringInGroupAtOffset,
                                                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ACTION, 10);
                                            MACRO_CALL_MEMBER(
                                                Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                                                DAT_VideoBikQueue::ptr)(pcVar10, pcVar25, pcVar27);
                                            MACRO_CALL_MEMBER(
                                                Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                                                DAT_VideoBikQueue::ptr)("",
                                                (char*)((int)(DAT_MissionAestheticsDefinedData::instance.RandomEvent10VideoName)),
                                                "");
                                        }
                                        bVar4 = this->scenarioEvents[_eventIndex].data.scenario.repeat;
                                        if ((!bVar4)
                                            || (bVar5 = this->scenarioEvents[_eventIndex].data.scenario.repeatMonths,
                                                bVar5 == 1))
                                            goto switchD_004c382e_caseD_2;
                                        if (bVar5 != 10) {
                                            this->scenarioEvents[_eventIndex].data.scenario.repeatMonths = bVar5 - 1;
                                        }
                                        uVar19 = (uint)bVar4;
                                        this->scenarioEvents[_eventIndex].header.done = 0;
                                        if (3 < uVar19) {
                                            uVar19
                                                = uVar19 + (int)SEC_RNG::instance.currentNumber2 % ((int)uVar19 >> 2);
                                        }
                                        this->scenarioEvents[_eventIndex].header.year
                                            = DAT_GameState::instance.mapAndTime.year + (int)uVar19 / 0xc;
                                        iVar18 = uVar19 + DAT_GameState::instance.mapAndTime.month
                                            + ((int)uVar19 / 0xc) * -0xc;
                                        this->scenarioEvents[_eventIndex].header.month = iVar18;
                                        if (iVar18 < 0xc)
                                            goto LAB_004c4621;
                                        _pConditionIsMet = &this->scenarioEvents[_eventIndex].header.year;
                                        *_pConditionIsMet = *_pConditionIsMet + 1;
                                        this->scenarioEvents[_eventIndex].header.month = iVar18 + -0xc;
                                        MACRO_CALL_MEMBER(
                                            Map::MapPropertiesState_Func::sortEventsByDate, this)();
                                        _eventIndex = _eventIndex + -1;
                                        break;
                                    case 0x14:
                                        BVar11
                                            = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::hasAnySignpost,
                                                DAT_GameState::ptr)();
                                        if (BVar11) {
                                            iVar18 = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::
                                                                           pickRandomAccessibleSignpostEntry,
                                                DAT_GameState::ptr)();
                                            iVar22 = 0;
                                            dVar14 = MACRO_CALL_MEMBER(
                                                Map::Units::TribesState_Func::createTribeWithSpawnedUnit,
                                                DAT_TribesState::ptr)(0, 3,
                                                DAT_GameState::instance.mapAndTime.signpostEntryData[iVar18].x,
                                                DAT_GameState::instance.mapAndTime.signpostEntryData[iVar18].y,
                                                (int)((int)(DAT_GameSynchronyState::instance.currentPlayerSlotID)),
                                                Map::Units::UT_E_ARCHER,
                                                this->scenarioEvents[_eventIndex].data.scenario.actionData);
                                            tribeID = MACRO_CALL_MEMBER(
                                                Map::Units::TribesState_Func::createTribeWithSpawnedUnit,
                                                DAT_TribesState::ptr)(0, 0xc,
                                                DAT_GameState::instance.mapAndTime.signpostEntryData[iVar18].x,
                                                DAT_GameState::instance.mapAndTime.signpostEntryData[iVar18].y,
                                                (int)((int)(DAT_GameSynchronyState::instance.currentPlayerSlotID)),
                                                Map::Units::UT_E_MONK, 1);
                                            MACRO_CALL_MEMBER(UI::MinimapViewState_Func::setSpawnMoment,
                                                DAT_MinimapViewState::ptr)(
                                                DAT_GameState::instance.mapAndTime.signpostEntryData[iVar18].x,
                                                DAT_GameState::instance.mapAndTime.signpostEntryData[iVar18].y);
                                            DAT_TribesState::instance.tribes[dVar14].pendingScatterMove = 0;
                                            DAT_TribesState::instance.tribes[tribeID].pendingScatterMove = 0;
                                            if (0 < DAT_TribesState::instance.tribes[dVar14].size) {
                                                do {
                                                    iVar18 = MACRO_CALL_MEMBER(
                                                        Map::Units::TribesState_Func::getUnitIDForIndexInTribe,
                                                        DAT_TribesState::ptr)(dVar14, iVar22);
                                                    sVar7 = DAT_TribesState::instance.tribes[dVar14].size;
                                                    iVar22 = iVar22 + 1;
                                                    DAT_UnitsState::instance.units[iVar18].calculatedOwnerPlayerIndex
                                                        = 8;
                                                    DAT_UnitsState::instance.units[iVar18].logicalState
                                                        = Map::Units::ULS_NORMAL;
                                                } while (iVar22 < sVar7);
                                            }
                                            iVar18 = 0;
                                            if (0 < DAT_TribesState::instance.tribes[tribeID].size) {
                                                do {
                                                    iVar22 = MACRO_CALL_MEMBER(
                                                        Map::Units::TribesState_Func::getUnitIDForIndexInTribe,
                                                        DAT_TribesState::ptr)(tribeID, iVar18);
                                                    DAT_UnitsState::instance.units[iVar22].calculatedOwnerPlayerIndex
                                                        = 8;
                                                    DAT_UnitsState::instance.units[iVar22].logicalState
                                                        = Map::Units::ULS_NORMAL;
                                                    iVar18 = iVar18 + 1;
                                                } while (iVar18 < DAT_TribesState::instance.tribes[tribeID].size);
                                            }
                                            iVar18 = DAT_GameState::instance
                                                         .playerDataArray[DAT_GameSynchronyState::instance
                                                                 .currentPlayerSlotID]
                                                         .keep.id;
                                            if (0 < iVar18) {
                                                BVar9 = DAT_BuildingsState::instance.buildings[iVar18].buildingType;
                                                uVar19 = 0;
                                                y1 = 0;
                                                if (BVar9 == Map::Buildings::BT_MANORHOUSE) {
                                                    uVar19
                                                        = (int)(short)DAT_BuildingsState::instance.buildings[iVar18].x
                                                        + 3;
                                                    y1 = (int)(short)DAT_BuildingsState::instance.buildings[iVar18].y
                                                        + 8;
                                                } else if (BVar9 == Map::Buildings::BT_STONEKEEP) {
                                                    uVar19
                                                        = (int)(short)DAT_BuildingsState::instance.buildings[iVar18].x
                                                        + 3;
                                                    y1 = (int)(short)DAT_BuildingsState::instance.buildings[iVar18].y
                                                        + 3;
                                                } else if (BVar9 == Map::Buildings::BT_STRONGHOLD) {
                                                    uVar19
                                                        = (int)(short)DAT_BuildingsState::instance.buildings[iVar18].x
                                                        + 3;
                                                    y1 = (int)(short)DAT_BuildingsState::instance.buildings[iVar18].y
                                                        + 3;
                                                } else if (BVar9 == Map::Buildings::BT_KEEPFOUR) {
                                                    uVar19
                                                        = (int)(short)DAT_BuildingsState::instance.buildings[iVar18].x
                                                        + 4;
                                                    y1 = (int)(short)DAT_BuildingsState::instance.buildings[iVar18].y
                                                        + 4;
                                                } else if (BVar9 == Map::Buildings::BT_KEEPFIVE) {
                                                    uVar19
                                                        = (int)(short)DAT_BuildingsState::instance.buildings[iVar18].x
                                                        + 5;
                                                    y1 = (int)(short)DAT_BuildingsState::instance.buildings[iVar18].y
                                                        + 5;
                                                }
                                                MACRO_CALL_MEMBER(
                                                    Map::Units::TribesState_Func::giveTribeMoveInstruction,
                                                    DAT_TribesState::ptr)(dVar14, uVar19, y1, 0, 0,
                                                    Map::Units::Instructions::UMSE_0);
                                                MACRO_CALL_MEMBER(
                                                    Map::Units::TribesState_Func::giveTribeMoveInstruction,
                                                    DAT_TribesState::ptr)(tribeID, uVar19, y1, 0, 0,
                                                    Map::Units::Instructions::UMSE_0);
                                            }
                                            pcVar25 = "Random_Events11.wav";
                                            pcVar26 = DAT_MissionAestheticsDefinedData::instance.RandomEvent11VideoName;
                                            /*
                                              added by script: "Some outlaws from the woods have returned to our cause,
                                              my   lord."
                                             */
                                            pcVar10 = MACRO_CALL_MEMBER(
                                                Text::TextManager_Func::getTextStringInGroupAtOffset,
                                                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ACTION, 0xb);
                                            MACRO_CALL_MEMBER(
                                                Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                                                DAT_VideoBikQueue::ptr)(pcVar10, pcVar26, pcVar25);
                                        }
                                        bVar4 = this->scenarioEvents[_eventIndex].data.scenario.repeat;
                                        if ((!bVar4)
                                            || (bVar5 = this->scenarioEvents[_eventIndex].data.scenario.repeatMonths,
                                                bVar5 == 1))
                                            goto switchD_004c382e_caseD_2;
                                        if (bVar5 != 10) {
                                            this->scenarioEvents[_eventIndex].data.scenario.repeatMonths = bVar5 - 1;
                                        }
                                        uVar19 = (uint)bVar4;
                                        this->scenarioEvents[_eventIndex].header.done = 0;
                                        if (3 < uVar19) {
                                            uVar19
                                                = uVar19 + (int)SEC_RNG::instance.currentNumber2 % ((int)uVar19 >> 2);
                                        }
                                        this->scenarioEvents[_eventIndex].header.year
                                            = DAT_GameState::instance.mapAndTime.year + (int)uVar19 / 0xc;
                                        iVar18 = uVar19 + DAT_GameState::instance.mapAndTime.month
                                            + ((int)uVar19 / 0xc) * -0xc;
                                        this->scenarioEvents[_eventIndex].header.month = iVar18;
                                        if (iVar18 < 0xc)
                                            goto LAB_004c4621;
                                        _pConditionIsMet = &this->scenarioEvents[_eventIndex].header.year;
                                        *_pConditionIsMet = *_pConditionIsMet + 1;
                                        this->scenarioEvents[_eventIndex].header.month = iVar18 + -0xc;
                                        MACRO_CALL_MEMBER(
                                            Map::MapPropertiesState_Func::sortEventsByDate, this)();
                                        _eventIndex = _eventIndex + -1;
                                        break;
                                    case 0x15:
                                        DAT_GameState::instance.mapAndTime.unitLadyRelated = 1;
                                        DAT_GameState::instance
                                            .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                            .someCount52 = 0xc;
                                        if (10000 < DAT_GameState::instance.playerDataArray[iVar18].popularity) {
                                            DAT_GameState::instance.playerDataArray[iVar18].popularity = 10000;
                                        }
                                        pcVar25 = "Random_Events12.wav";
                                        pcVar26 = DAT_MissionAestheticsDefinedData::instance.RandomEvent12VideoName;
                                        /*
                                          added by script: "The people rejoice at your forthcoming marriage, Sire."
                                         */
                                        pcVar10 = MACRO_CALL_MEMBER(
                                            Text::TextManager_Func::getTextStringInGroupAtOffset,
                                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ACTION, 0xc);
                                        MACRO_CALL_MEMBER(
                                            Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                                            DAT_VideoBikQueue::ptr)(pcVar10, pcVar26, pcVar25);
                                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::setUpSFXToPlayUnk,
                                            DAT_SFXState::ptr)(Audio::SFX::SEID_CHAPEL_BELL);
                                        MACRO_CALL_MEMBER(
                                            Map::MapPropertiesState_Func::sortEventsByDate, this)();
                                        break;
                                    case 0x16:
                                        DAT_GameState::instance.mapAndTime.unitJesterRelated = 1;
                                        DAT_GameState::instance
                                            .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                            .someCount53 = 0x30;
                                        if (10000 < DAT_GameState::instance.playerDataArray[iVar18].popularity) {
                                            DAT_GameState::instance.playerDataArray[iVar18].popularity = 10000;
                                        }
                                        pcVar25 = "Random_Events13.wav";
                                        pcVar26 = DAT_MissionAestheticsDefinedData::instance.RandomEvent13VideoName;
                                        /*
                                          added by script: "A Jester has arrived at the castle Liege.  I have taken the
                                          liberty of offering him employment."
                                         */
                                        pcVar10 = MACRO_CALL_MEMBER(
                                            Text::TextManager_Func::getTextStringInGroupAtOffset,
                                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ACTION, 0xd);
                                        MACRO_CALL_MEMBER(
                                            Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                                            DAT_VideoBikQueue::ptr)(pcVar10, pcVar26, pcVar25);
                                        MACRO_CALL_MEMBER(
                                            Map::MapPropertiesState_Func::sortEventsByDate, this)();
                                        break;
                                    case 0x17:
                                        if (((DAT_GameCore::instance.gameMode_2 != Game::GM_CAMPAIGN_MISSION)
                                                && (this->scenarioEvents[_eventIndex].header.year == 0x43d))
                                            && (this->scenarioEvents[_eventIndex].header.month == 0xb)) {
                                            dVar14 = MACRO_CALL_MEMBER(
                                                Map::Units::TribesState_Func::createTribeWithSpawnedUnit,
                                                DAT_TribesState::ptr)(0, 3, 0x85, 0x116,
                                                (int)((int)(DAT_GameSynchronyState::instance.currentPlayerSlotID)),
                                                Map::Units::UT_E_ARCHER, 0x14);
                                            sVar7 = DAT_TribesState::instance.tribes[dVar14].size;
                                            DAT_TribesState::instance.tribes[dVar14].pendingScatterMove = 3;
                                            if (0 < sVar7) {
                                                iVar18 = 0;
                                                do {
                                                    iVar22 = iVar18 + 1;
                                                    iVar18 = MACRO_CALL_MEMBER(
                                                        Map::Units::TribesState_Func::getUnitIDForIndexInTribe,
                                                        DAT_TribesState::ptr)(dVar14, iVar18);
                                                    sVar7 = DAT_TribesState::instance.tribes[dVar14].size;
                                                    DAT_UnitsState::instance.units[iVar18].calculatedOwnerPlayerIndex
                                                        = 6;
                                                    iVar18 = iVar22;
                                                } while (iVar22 < sVar7);
                                                MACRO_CALL_MEMBER(
                                                    Map::MapPropertiesState_Func::sortEventsByDate, this)();
                                                break;
                                            }
                                        }
                                        goto switchD_004c382e_caseD_2;
                                    case 0x18:
                                        DAT_GameCore::instance.section1076 = 0;
                                        MACRO_CALL_MEMBER(
                                            Map::MapPropertiesState_Func::sortEventsByDate, this)();
                                        break;
                                    case 0x19:
                                        DAT_GameCore::instance.section1076 = 1;
                                        MACRO_CALL_MEMBER(
                                            Map::MapPropertiesState_Func::sortEventsByDate, this)();
                                        break;
                                    case 0x1a:
                                        if (DAT_GameState::instance
                                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                                .playerDeathRelated
                                            == 0) {
                                            iVar18 = _eventIndex + 1;
                                            if (iVar18 < this->eventsCount) {
                                                _pConditionIsMet = &this->scenarioEvents[_eventIndex + 1]
                                                                        .data.scenario.ScenarioEventType;
                                                do {
                                                    if ((_pConditionIsMet[-3] == 3)
                                                        && ((((*_pConditionIsMet == 0 || (*_pConditionIsMet == 0x1a))
                                                                 && (_pConditionIsMet[-4]
                                                                     <= DAT_GameState::instance.mapAndTime.year))
                                                            && ((DAT_GameState::instance.mapAndTime.year
                                                                    != _pConditionIsMet[-4]
                                                                || (_pConditionIsMet[-5]
                                                                    < DAT_GameState::instance.mapAndTime.month))))))
                                                        goto switchD_004c382e_caseD_2;
                                                    iVar18 = iVar18 + 1;
                                                    _pConditionIsMet = _pConditionIsMet + 0x39;
                                                } while (iVar18 < this->eventsCount);
                                            }
                                            this->scenarioEvents[_eventIndex].header.done = 0;
                                            this->scenarioEvents[_eventIndex].data.scenario.ScenarioEventType = 0;
                                            this->scenarioEvents[_eventIndex].header.year
                                                = DAT_GameState::instance.mapAndTime.year;
                                        LAB_004c4072:
                                            iVar18 = DAT_GameState::instance.mapAndTime.month;
                                            iVar22 = DAT_GameState::instance.mapAndTime.month + 1;
                                            this->scenarioEvents[_eventIndex].header.month = iVar22;
                                            if (0xb < iVar22) {
                                                _pConditionIsMet = &this->scenarioEvents[_eventIndex].header.year;
                                                *_pConditionIsMet = *_pConditionIsMet + 1;
                                                this->scenarioEvents[_eventIndex].header.month = iVar18 + -0xb;
                                                MACRO_CALL_MEMBER(
                                                    Map::MapPropertiesState_Func::sortEventsByDate, this)();
                                                break;
                                            }
                                        }
                                        goto switchD_004c382e_caseD_2;
                                    case 0x1b:
                                        if (DAT_GameState::instance
                                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                                .playerDeathRelated
                                            == 0) {
                                            this->scenarioEvents[_eventIndex].header.done = 0;
                                            this->scenarioEvents[_eventIndex].data.scenario.ScenarioEventType = 1;
                                            this->scenarioEvents[_eventIndex].header.year
                                                = DAT_GameState::instance.mapAndTime.year;
                                            goto LAB_004c4072;
                                        }
                                        goto switchD_004c382e_caseD_2;
                                    case 0x1c:
                                        iVar18 = 0;
                                        if (0 < this->eventsCount) {
                                            pSVar15 = this->scenarioEvents[0].data.scenario.conditions + 0x19;
                                            do {
                                                if ((*(const int*)&pSVar15[-0x1e] == 1)
                                                    && (*(const int*)pSVar15 != 0)) {
                                                    pSVar15->value = 0;
                                                    pSVar15->subType = 0;
                                                    pSVar15->enabled = 0;
                                                    pSVar15[-0x1d].value = 1;
                                                    pSVar15[-0xffffffff0000001f].value = 0x49d;
                                                    pSVar15[-0xffffffff0000001f].subType = 0;
                                                    pSVar15[-0xffffffff0000001f].enabled = 0;
                                                }
                                                iVar18 = iVar18 + 1;
                                                pSVar15 = pSVar15 + 0x39;
                                            } while (iVar18 < this->eventsCount);
                                        }
                                    switchD_004c382e_caseD_2:
                                        MACRO_CALL_MEMBER(
                                            Map::MapPropertiesState_Func::sortEventsByDate, this)();
                                        break;
                                    case 0x1d:
                                        if (DAT_GameState::instance
                                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                                .totalFood
                                            != 0) {
                                            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::
                                                                  applyFoodLossPercentageToPlayer,
                                                DAT_BuildingsState::ptr)(
                                                DAT_GameSynchronyState::instance.currentPlayerSlotID,
                                                this->scenarioEvents[_eventIndex].data.scenario.actionData);
                                            pcVar10 = "general_message3.wav";
                                            if (this->scenarioEvents[_eventIndex].data.scenario.actionData == 100) {
                                                iVar18 = 0x10;
                                            } else {
                                                iVar18 = 0xe;
                                            }
                                            pcVar26 = DAT_MissionAestheticsDefinedData::instance.RandomEvent14VideoName;
                                            /*
                                              added by script: "Thieves have stolen some food from our granary."
                                             */
                                            pcVar25 = MACRO_CALL_MEMBER(
                                                Text::TextManager_Func::getTextStringInGroupAtOffset,
                                                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ACTION, iVar18);
                                            MACRO_CALL_MEMBER(
                                                Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                                                DAT_VideoBikQueue::ptr)(pcVar25, pcVar26, pcVar10);
                                        }
                                        bVar4 = this->scenarioEvents[_eventIndex].data.scenario.repeat;
                                        if ((!bVar4)
                                            || (bVar5 = this->scenarioEvents[_eventIndex].data.scenario.repeatMonths,
                                                bVar5 == 1))
                                            goto switchD_004c382e_caseD_2;
                                        if (bVar5 != 10) {
                                            this->scenarioEvents[_eventIndex].data.scenario.repeatMonths = bVar5 - 1;
                                        }
                                        uVar19 = (uint)bVar4;
                                        this->scenarioEvents[_eventIndex].header.done = 0;
                                        if (3 < uVar19) {
                                            uVar19
                                                = uVar19 + (int)SEC_RNG::instance.currentNumber2 % ((int)uVar19 >> 2);
                                        }
                                        this->scenarioEvents[_eventIndex].header.year
                                            = DAT_GameState::instance.mapAndTime.year + (int)uVar19 / 0xc;
                                        iVar18 = uVar19 + DAT_GameState::instance.mapAndTime.month
                                            + ((int)uVar19 / 0xc) * -0xc;
                                        this->scenarioEvents[_eventIndex].header.month = iVar18;
                                        if (iVar18 < 0xc)
                                            goto LAB_004c4621;
                                        _pConditionIsMet = &this->scenarioEvents[_eventIndex].header.year;
                                        *_pConditionIsMet = *_pConditionIsMet + 1;
                                        this->scenarioEvents[_eventIndex].header.month = iVar18 + -0xc;
                                        MACRO_CALL_MEMBER(
                                            Map::MapPropertiesState_Func::sortEventsByDate, this)();
                                        _eventIndex = _eventIndex + -1;
                                        break;
                                    case 0x1e:
                                        DAT_GameState::instance
                                            .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                            .someCount51 = 8;
                                        MACRO_CALL_MEMBER(
                                            Map::Buildings::BuildingsState_Func::spreadFireRandomlyToBuildings,
                                            DAT_BuildingsState::ptr)(
                                            iVar18, this->scenarioEvents[_eventIndex].data.scenario.actionData);
                                        iVar18 = MACRO_CALL_MEMBER(
                                            Map::Buildings::BuildingsState_Func::findFirstBuildingOfType,
                                            DAT_BuildingsState::ptr)(
                                            DAT_GameSynchronyState::instance.currentPlayerSlotID,
                                            Map::Buildings::BT_WELL);
                                        if (!iVar18) {
                                            iVar18 = MACRO_CALL_MEMBER(
                                                Map::Buildings::BuildingsState_Func::findFirstBuildingOfType,
                                                DAT_BuildingsState::ptr)(
                                                DAT_GameSynchronyState::instance.currentPlayerSlotID,
                                                Map::Buildings::BT_WATERPOT);
                                            if (!iVar18) {
                                                iVar18 = 0x11;
                                            } else {
                                                iVar18 = 0xf;
                                            }
                                        } else {
                                            iVar18 = 0xf;
                                        }
                                        pcVar25 = "general_warning16.wav";
                                        pcVar26 = DAT_MissionAestheticsDefinedData::instance.RandomEvent15VideoName;
                                        /*
                                          added by script: "There is fire in the castle and we have not built any wells
                                          my Liege!"
                                         */
                                        pcVar10 = MACRO_CALL_MEMBER(
                                            Text::TextManager_Func::getTextStringInGroupAtOffset,
                                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_ACTION, iVar18);
                                        MACRO_CALL_MEMBER(
                                            Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                                            DAT_VideoBikQueue::ptr)(pcVar10, pcVar26, pcVar25);
                                        bVar4 = this->scenarioEvents[_eventIndex].data.scenario.repeat;
                                        if ((!bVar4)
                                            || (bVar5 = this->scenarioEvents[_eventIndex].data.scenario.repeatMonths,
                                                bVar5 == 1))
                                            goto switchD_004c382e_caseD_2;
                                        if (bVar5 != 10) {
                                            this->scenarioEvents[_eventIndex].data.scenario.repeatMonths = bVar5 - 1;
                                        }
                                        uVar19 = (uint)bVar4;
                                        this->scenarioEvents[_eventIndex].header.done = 0;
                                        if (3 < uVar19) {
                                            uVar19
                                                = uVar19 + (int)SEC_RNG::instance.currentNumber2 % ((int)uVar19 >> 2);
                                        }
                                        this->scenarioEvents[_eventIndex].header.year
                                            = DAT_GameState::instance.mapAndTime.year + (int)uVar19 / 0xc;
                                        iVar18 = uVar19 + DAT_GameState::instance.mapAndTime.month
                                            + ((int)uVar19 / 0xc) * -0xc;
                                        this->scenarioEvents[_eventIndex].header.month = iVar18;
                                        if (iVar18 < 0xc)
                                            goto LAB_004c4621;
                                        _pConditionIsMet = &this->scenarioEvents[_eventIndex].header.year;
                                        *_pConditionIsMet = *_pConditionIsMet + 1;
                                        this->scenarioEvents[_eventIndex].header.month = iVar18 + -0xc;
                                        MACRO_CALL_MEMBER(
                                            Map::MapPropertiesState_Func::sortEventsByDate, this)();
                                        _eventIndex = _eventIndex + -1;
                                    }
                                LAB_004c5f28:
                                    _eventIndex = _eventIndex + 1;
                                } while (_eventIndex < this->eventsCount);
                            }
                            iVar18 = DAT_GameState::instance.mapAndTime.month + 3;
                            local_88 = DAT_GameState::instance.mapAndTime.year;
                            if (0xb < iVar18) {
                                iVar18 = DAT_GameState::instance.mapAndTime.month + -9;
                                local_88 = DAT_GameState::instance.mapAndTime.year + 1;
                            }
                            local_70[0] = 0;
                            local_70[1] = 0;
                            local_70[2] = 0;
                            local_70[3] = 0;
                            local_70[4] = 0;
                            local_70[5] = 0;
                            local_70[6] = 0;
                            local_70[7] = 0;
                            local_70[8] = 0;
                            _eventIndex = 0;
                            if (0 < this->eventsCount) {
                                psVar21 = &this->scenarioEvents[0];
                                do {
                                    if ((((local_88 == psVar21->header.year) && (iVar18 == psVar21->header.month))
                                            && ((!psVar21->header.pre_done
                                                && ((iVar22 = psVar21->header.tl_type, psVar21->header.pre_done = 1,
                                                    iVar22 == 1
                                                        && (DAT_GameState::instance.mapAndTime.field3171_0x27a8 = 1,
                                                            DAT_GameCore::instance.section1076 == 0))))))
                                        && (iVar22 = (psVar21->data).invasion.crusaderArabian, local_70[iVar22] == 0)) {
                                        iVar20 = 0;
                                        iVar1 = iVar22 * 4;
                                        numInGroup = iVar1 + 1;
                                        iVar21 = 5;
                                        _pConditionIsMet = (psVar21->data).invasion.unitCountsPerUnitType + 3;
                                        do {
                                            iVar20 = iVar20 + _pConditionIsMet[-3] + _pConditionIsMet[-2]
                                                + _pConditionIsMet[-1] + _pConditionIsMet[1] + *_pConditionIsMet;
                                            iVar21 = iVar21 + -1;
                                            _pConditionIsMet = _pConditionIsMet + 5;
                                        } while (iVar21);
                                        if (0x18 < iVar20) {
                                            if (iVar20 < 0x4b) {
                                                numInGroup = iVar1 + 2;
                                            } else if (iVar20 < 0x96) {
                                                numInGroup = iVar1 + 3;
                                            } else {
                                                numInGroup = iVar1 + 4;
                                            }
                                        }
                                        local_70[iVar22] = 1;
                                        if (!iVar22) {
                                            pcVar26 = (&DAT_MissionAestheticsDefinedData::instance
                                                    .field59_0xec)[numInGroup];
                                            pcVar10 = "good_arab_nervous.bik";
                                        } else {
                                            if (iVar22 != 1)
                                                goto LAB_004c609a;
                                            pcVar26 = (&DAT_MissionAestheticsDefinedData::instance
                                                    .field59_0xec)[numInGroup];
                                            pcVar10 = "good_soldier_nervous.bik";
                                        }
                                        pcVar25 = MACRO_CALL_MEMBER(
                                            Text::TextManager_Func::getTextStringInGroupAtOffset,
                                            DAT_TextManagerObject::ptr)(
                                            DE::SHCDE::TEXT_SANDS_OF_TIME, numInGroup);
                                        MACRO_CALL_MEMBER(
                                            Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                                            DAT_VideoBikQueue::ptr)(pcVar25, pcVar10, pcVar26);
                                    }
                                LAB_004c609a:
                                    _eventIndex = _eventIndex + 1;
                                    psVar21 = psVar21 + 0x72;
                                } while (_eventIndex < this->eventsCount);
                            }
                            if ((DAT_GameState::instance.gameTicksLoadBalancer == 0x97)
                                && (DAT_GameState::instance.mapAndTime.week == 3)) {
                                iVar22 = DAT_GameState::instance.mapAndTime.month + 1;
                                iVar18 = DAT_GameState::instance.mapAndTime.year;
                                if (0xb < iVar22) {
                                    iVar22 = DAT_GameState::instance.mapAndTime.month + -0xb;
                                    iVar18 = DAT_GameState::instance.mapAndTime.year + 1;
                                }
                                iVar21 = 0;
                                if (0 < this->eventsCount) {
                                    pIVar16 = this->scenarioEvents;
                                    do {
                                        if (((iVar18 == (pIVar16->header).year) && (iVar22 == (pIVar16->header).month))
                                            && ((pIVar16->header).tl_type == 1)) {
                                            DAT_GameState::instance.mapAndTime.gameEventRelatedCountdown = 40;
                                        }
                                        iVar21 = iVar21 + 1;
                                        pIVar16 = pIVar16 + 1;
                                    } while (iVar21 < this->eventsCount);
                                }
                            }
                        }
                    } else {
                        if ((DAT_BinkControlState::instance.binkObjPtrArray[1] == (HBINK)0x0)
                            && (!DAT_VideoBikQueue::instance.storedMessages_0x924)) {
                            DAT_GameState::instance.mapAndTime.unknownCountdown01
                                = DAT_GameState::instance.mapAndTime.unknownCountdown01 + -1;
                        }
                        if (!DAT_GameState::instance.mapAndTime.unknownCountdown01) {
                            DAT_VideoBikQueue::instance.storedMessages_0x924 = 0;
                            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                                DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_NONE, FALSE);
                            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                                DAT_MenuModalComposition2::ptr)(UI::Enums::MMT_NONE, FALSE);
                            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                                DAT_MenuModalComposition3::ptr)(UI::Enums::MMT_NONE, FALSE);
                            DAT_MenuTextInputState::instance.DAT_SomeTextArrayIndex = 9;
                            MACRO_CALL_MEMBER(UI::MenuTextInputState_Func::clearAnyOtherModalDialogs,
                                DAT_MenuTextInputState::ptr)();
                            if (DAT_GameCore::instance.gameMode_2 == Game::GM_CAMPAIGN_MISSION) {
                                if (DAT_GameState::instance
                                        .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                        .playerDeathRelated
                                    == 1) {
                                    MACRO_CALL_MEMBER(
                                        Game::GameCore_Func::incrementMissionProgress, DAT_GameCore::ptr)();
                                    DAT_GameCore::instance.section1066 = 2;
                                }
                                if (DAT_GameState::instance
                                        .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                        .playerDeathRelated
                                    == 2) {
                                    MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView,
                                        DAT_GameCore::ptr)(UI::Enums::MVT_GAME_LOSTUnk, 0);
                                    DAT_GameCore::instance.section1066 = 0;
                                }
                                MACRO_CALL(UI::DisplayElements_Func::
                                        CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                                    UI::Enums::DEID_MISSION_WIN_DEFEAT_BANNER, 0);
                                MACRO_CALL(UI::DisplayElements_Func::
                                        CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                                    UI::Enums::DEID_MISSION_WIN_DEFEAT_BANNER, 0);
                            }
                            if (DAT_GameCore::instance.gameMode_2 != Game::GM_ECONOMIC_CAMPAIGN_SH1) {
                                if (DAT_GameCore::instance.gameMode_2 == Game::GM_BUILDERUnk) {
                                    if (DAT_GameCore::instance.field24_0x6c) {
                                        DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 7;
                                        MACRO_CALL(UI::MenuItems::General_Func::
                                                MenuItemActionHandler_General_LaunchOrQuitMultiplayerGameUnk)(0x16);
                                        MACRO_CALL(UI::DisplayElements_Func::
                                                CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                                            UI::Enums::DEID_MISSION_WIN_DEFEAT_BANNER, 0);
                                    }
                                    if (DAT_GameState::instance
                                            .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                            .playerDeathRelated
                                        == 1) {
                                        if ((int)this->SEC_U3_MapType2_1 < 2) {
                                            MACRO_CALL_MEMBER(
                                                Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                                UI::Enums::MVT_MISSION_FINISHED_TRANSITION, 0);
                                        } else {
                                            DAT_GameCore::instance.section1095 = 1;
                                            DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 0x2f;
                                            MACRO_CALL_MEMBER(
                                                UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                                                DAT_MenuTextInputState::ptr)(UI::Enums::MMT_QUIT_DIALOG);
                                        }
                                    }
                                    if (DAT_GameState::instance
                                            .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                            .playerDeathRelated
                                        == 2) {
                                        MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView,
                                            DAT_GameCore::ptr)(UI::Enums::MVT_GAME_LOSTUnk, 0);
                                    }
                                    DAT_GameCore::instance.section1066 = 2;
                                }
                                MACRO_CALL(UI::DisplayElements_Func::
                                        CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                                    UI::Enums::DEID_MISSION_WIN_DEFEAT_BANNER, 0);
                            }
                            if (DAT_GameState::instance
                                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .playerDeathRelated
                                == 1) {
                                MACRO_CALL_MEMBER(Game::GameCore_Func::incrementMission, DAT_GameCore::ptr)();
                            }
                            if (DAT_GameState::instance
                                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .playerDeathRelated
                                == 2) {
                                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                                    UI::Enums::MVT_GAME_LOSTUnk, 0);
                            }
                            MACRO_CALL(
                                UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                                UI::Enums::DEID_MISSION_WIN_DEFEAT_BANNER, 0);
                            MACRO_CALL(
                                UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                                UI::Enums::DEID_MISSION_WIN_DEFEAT_BANNER, 0);
                        }
                    }
                }
            }
        } else if (DAT_GameCore::instance.gameMode_2 == Game::GM_CAMPAIGN_MISSION) {
            MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::updateMilitaryCampaignMissionState, this)();
        }
    }

}
}
