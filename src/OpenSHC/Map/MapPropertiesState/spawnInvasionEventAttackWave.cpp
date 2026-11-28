#include "../../Map.func.hpp"
#include "../MapPropertiesState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"
#include "OpenSHC/Map/Units/UnitTypeInt.hpp"

namespace OpenSHC {
namespace Map {

    using Map::Units::UnitType;
    using Map::Units::UnitTypeInt;

    /*
      WARNING (jumptable): Heritage AFTER dead removal. Revisit: 0x01667ebc
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004C13F0
    void MapPropertiesState::spawnInvasionEventAttackWave()
    {
        byte(*pabVar1)[10];
        byte* pbVar2;
        int iVar3;
        char cVar4;
        int _sliderValue;
        int _unitCount;
        int _unitTypeOther;
        UnitTypeInt _unitType;
        char* eventVideoBik;
        char* eventWavFile;
        int local_10;
        int local_c;
        int _sliderIndex;
        DAT_TroopValueState::instance.attackInfo.inv_count = DAT_TroopValueState::instance.attackInfo.inv_count + 1;
        local_c = 0;
        local_10 = 0;
        if (0x31 < DAT_TroopValueState::instance.attackInfo.inv_count) {
            DAT_TroopValueState::instance.attackInfo.inv_count = 1;
        }
        MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::initializeAttackWaveSlot,
            DAT_TroopValueState::ptr)(DAT_TroopValueState::instance.attackInfo.inv_count, 0);
        DAT_TroopValueState::instance.attackInfo
            .attackWavePlayerIDArray[DAT_TroopValueState::instance.attackInfo.inv_count]
            = (char)this->invasionEventContent.crusaderArabian + 2;
        _sliderIndex = 0;
        do {
            _sliderValue = this->invasionEventContent.unitCountsPerUnitType[_sliderIndex];
            if (!_sliderValue)
                goto LAB_004c16b3;
            _unitTypeOther = 0;
            _unitType = ((UnitType)0);
            iVar3 = 0;
            switch (_sliderIndex) {
            case 0:
                _unitTypeOther = 3;
                _unitType = Map::Units::UT_E_ARCHER;
                break;
            case 1:
                _unitTypeOther = 7;
                _unitType = Map::Units::UT_E_XBOW;
                break;
            case 2:
                _unitTypeOther = 5;
                _unitType = Map::Units::UT_E_SPEAR;
                break;
            case 3:
                _unitTypeOther = 6;
                _unitType = Map::Units::UT_E_PIKE;
                break;
            case 4:
                _unitTypeOther = 9;
                _unitType = Map::Units::UT_E_MACE;
                break;
            case 5:
                _unitTypeOther = 8;
                _unitType = Map::Units::UT_E_SWORD;
                break;
            case 6:
                _unitTypeOther = 10;
                _unitType = Map::Units::UT_E_KNIGHT;
                iVar3 = 10;
                goto switchD_004c146e_caseD_18;
            case 7:
                _unitTypeOther = 4;
                _unitType = Map::Units::UT_E_LADDER;
                break;
            case 8:
                _unitTypeOther = 0xb;
                _unitType = Map::Units::UT_E_ENGINEER;
                break;
            case 9:
                _unitTypeOther = 0x16;
                _unitType = Map::Units::UT_S_CATAPULT;
                break;
            case 10:
                _unitTypeOther = 0x17;
                _unitType = Map::Units::UT_S_TREBUCHET;
                break;
            case 0xb:
                _unitTypeOther = 0x13;
                _unitType = Map::Units::UT_S_BATTERINGRAM;
                break;
            case 0xc:
                _unitTypeOther = 0x14;
                _unitType = Map::Units::UT_S_TOWER;
                break;
            case 0xd:
                _unitTypeOther = 0x15;
                _unitType = Map::Units::UT_S_SHIELD;
                break;
            case 0xe:
                _unitTypeOther = 0xc;
                _unitType = Map::Units::UT_E_MONK;
                break;
            case 0xf:
                _unitTypeOther = 2;
                _unitType = Map::Units::UT_TUNNELER;
                break;
            case 0x10:
                _unitTypeOther = 0x19;
                _unitType = Map::Units::UT_A_ARCHER;
                break;
            case 0x11:
                _unitTypeOther = 0x1a;
                _unitType = Map::Units::UT_A_SLAVE;
                break;
            case 0x12:
                _unitTypeOther = 0x1b;
                _unitType = Map::Units::UT_A_SLINGER;
                break;
            case 0x13:
                _unitTypeOther = 0x1c;
                _unitType = Map::Units::UT_A_ASSASSIN;
                break;
            case 0x14:
                _unitTypeOther = 0x1d;
                _unitType = Map::Units::UT_A_HARCHER;
                break;
            case 0x15:
                _unitTypeOther = 0x1e;
                _unitType = Map::Units::UT_A_SWORDSMAN;
                break;
            case 0x16:
                _unitTypeOther = 0x1f;
                _unitType = Map::Units::UT_A_FIRETHROWER;
                break;
            case 0x17:
                _unitTypeOther = 0x18;
                _unitType = Map::Units::UT_S_FBALLISTA;
                break;
            default:
                goto switchD_004c146e_caseD_18;
            }
            /*
              if a siege engine...
             */
            iVar3 = 10;
        switchD_004c146e_caseD_18:
            cVar4 = (char)_sliderValue;
            if (_unitTypeOther == 0x16) {
                pabVar1 = DAT_TroopValueState::instance.attackInfo.someSinglePlayerScore
                    + DAT_TroopValueState::instance.attackInfo.inv_count;
                (*pabVar1)[0] = (*pabVar1)[0] + cVar4;
            } else if (_unitTypeOther == 0x17) {
                pbVar2 = DAT_TroopValueState::instance.attackInfo
                             .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count]
                    + 1;
                *pbVar2 = *pbVar2 + cVar4;
            } else if (_unitTypeOther == 0x13) {
                pbVar2 = DAT_TroopValueState::instance.attackInfo
                             .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count]
                    + 2;
                *pbVar2 = *pbVar2 + cVar4;
            } else if (_unitTypeOther == 0x14) {
                pbVar2 = DAT_TroopValueState::instance.attackInfo
                             .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count]
                    + 3;
                *pbVar2 = *pbVar2 + cVar4;
            } else if (_unitTypeOther == 0x15) {
                pbVar2 = DAT_TroopValueState::instance.attackInfo
                             .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count]
                    + 4;
                *pbVar2 = *pbVar2 + cVar4;
            } else if (_unitTypeOther == 0x18) {
                pbVar2 = DAT_TroopValueState::instance.attackInfo
                             .someSinglePlayerScore[DAT_TroopValueState::instance.attackInfo.inv_count]
                    + 8;
                *pbVar2 = *pbVar2 + cVar4;
            } else {
                /*
                  if not a siege engine...
                 */
                _unitCount = _sliderValue / (_sliderValue / iVar3 + 1);
                while (0 < _sliderValue) {
                    if (_sliderValue < _unitCount) {
                        _unitCount = _sliderValue;
                    }
                    iVar3 = (&DAT_TroopValueState::instance.attackInfo
                            .unknownSignpostRelatedArray)[DAT_TroopValueState::instance.attackInfo.inv_count];
                    MACRO_CALL_MEMBER(
                        Map::Units::TribesState_Func::spawnUnitsIntoNewTribe, DAT_TribesState::ptr)(local_c,
                        _unitTypeOther, DAT_GameState::instance.mapAndTime.signpostsMapEdge[iVar3][local_10].x,
                        DAT_GameState::instance.mapAndTime.signpostsMapEdge[iVar3][local_10].y,
                        this->invasionEventContent.crusaderArabian + 2, (UnitType)((int)(_unitType)), ((UnitType)0),
                        _unitCount, 0);
                    local_c = local_c + 1;
                    local_10 = local_10 + 1;
                    _sliderValue = _sliderValue - _unitCount;
                    if (DAT_GameState::instance.mapAndTime.signpostsMapEdgeDataCounter <= local_10) {
                        local_10 = 0;
                    }
                }
            }
        LAB_004c16b3:
            _sliderIndex = _sliderIndex + 1;
            if (0x18 < _sliderIndex) {
                if (!this->invasionEventContent.crusaderArabian) {
                    eventWavFile = "infidel_attack.wav";
                    eventVideoBik = "sultan_nervous.bik";
                } else {
                    if (this->invasionEventContent.crusaderArabian != 1) {
                        this->eventsCount = 0;
                    }
                    eventWavFile = "arabian_attack.wav";
                    eventVideoBik = "good_soldier_nervous.bik";
                }
                MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playEventVideoBik,
                    DAT_VideoBikQueue::ptr)("", eventVideoBik, eventWavFile);
                this->eventsCount = 0;
            }
        } while (true);
    }

}
}
