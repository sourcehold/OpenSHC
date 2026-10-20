#include "../../../Map.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/Units/UnitTypeInt.hpp"

#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitType;
        using Map::Units::UnitTypeInt;

        // FUNCTION: STRONGHOLDCRUSADER 0x00521A90
        void TribesState::playUnitCombatSpeechForTarget(int selectionID, int unitID)
        {
            UnitTypeShort UVar2;
            int _otherUnitID;
            UnitTypeInt _ptrptrCurrentSelectionID;
            int _yDifference;
            int _otherX;
            int _xDifference;
            int _otherY;
            int sfxOffsetInArray;
            TribesState* _ptrCurrentSelectionID;
            uint _actionID;
            int _distance;
            TribesState* _ptrCurrentSelectionID_2;
            _ptrCurrentSelectionID = this;
            _otherUnitID
                = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::selectionContainsCombatUnit, DAT_UnitsState::ptr)(1);
            _ptrptrCurrentSelectionID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getMajoritySelectedUnitType,
                this)(selectionID, (int*)&_ptrCurrentSelectionID);
            _ptrCurrentSelectionID_2 = _ptrCurrentSelectionID;
            short sVar1 = DAT_TribesState::instance.tribes[selectionID].size;
            switch (_ptrptrCurrentSelectionID) {
            case Map::Units::UT_E_ARCHER:
            case Map::Units::UT_E_XBOW:
            case Map::Units::UT_A_ARCHER:
            case Map::Units::UT_A_SLINGER:
            case Map::Units::UT_A_HARCHER:
            case Map::Units::UT_A_FIRETHROWER:
                if (_ptrptrCurrentSelectionID == Map::Units::UT_E_ARCHER) {
                    _distance = DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[1]
                        * DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[1];
                } else if (_ptrptrCurrentSelectionID == Map::Units::UT_E_XBOW) {
                    _distance = DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[7]
                        * DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[7];
                } else if (_ptrptrCurrentSelectionID == Map::Units::UT_A_ARCHER) {
                    _distance = DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[1]
                        * DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[1];
                } else if (_ptrptrCurrentSelectionID == Map::Units::UT_A_SLINGER) {
                    _distance = DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[0x21]
                        * DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[0x21];
                } else if (_ptrptrCurrentSelectionID == Map::Units::UT_A_HARCHER) {
                    _distance = DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[1]
                        * DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[1];
                } else {
                    _distance = unitID;
                    if (_ptrptrCurrentSelectionID == Map::Units::UT_A_FIRETHROWER) {
                        _distance = DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[0x22]
                            * DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[0x22];
                    }
                }
                _xDifference = (int)DAT_UnitsState::instance.units[_otherUnitID].x
                    - (int)DAT_UnitsState::instance.units[unitID].x;
                _yDifference = (int)DAT_UnitsState::instance.units[_otherUnitID].y
                    - (int)DAT_UnitsState::instance.units[unitID].y;
                if (_distance < _xDifference * _xDifference + _yDifference * _yDifference) {
                    _actionID = 0x1e;
                } else {
                    _actionID = 0x19;
                }
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                    (Map::Units::UnitType)_ptrptrCurrentSelectionID, _actionID);
                if (_ptrptrCurrentSelectionID != Map::Units::UT_A_HARCHER) {}
                if (_ptrCurrentSelectionID == (TribesState*)0x1) {
                    _otherY = (int)DAT_UnitsState::instance.units[_otherUnitID].y;
                    _otherX = (int)DAT_UnitsState::instance.units[_otherUnitID].x;
                    sfxOffsetInArray = 0xea;
                } else if ((int)_ptrCurrentSelectionID < 5) {
                    _otherY = (int)DAT_UnitsState::instance.units[_otherUnitID].y;
                    _otherX = (int)DAT_UnitsState::instance.units[_otherUnitID].x;
                    sfxOffsetInArray = 0xeb;
                } else {
                    _otherY = (int)DAT_UnitsState::instance.units[_otherUnitID].y;
                    _otherX = (int)DAT_UnitsState::instance.units[_otherUnitID].x;
                    sfxOffsetInArray = 0xec;
                }
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                    _otherX, _otherY, sfxOffsetInArray);
                _otherX = 0x59;
                break;
            case Map::Units::UT_E_SPEAR:
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                    (Map::Units::UnitType)_ptrptrCurrentSelectionID, 0x15);
                if (sVar1 < 0xf) {
                    return;
                }
                _otherX = 0x14;
                break;
            case Map::Units::UT_E_PIKE:
            case Map::Units::UT_E_MACE:
            case Map::Units::UT_E_MONK:
                UVar2 = DAT_UnitsState::instance.units[unitID].unitType;
                if (UVar2 == Map::Units::UT_E_KNIGHT || UVar2 == Map::Units::UT_E_SWORD
                    || UVar2 == Map::Units::UT_LORD) {
                    _otherX = 0x11;
                } else {
                    _otherX = 0x15;
                }
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                    (Map::Units::UnitType)_ptrptrCurrentSelectionID, _otherX);
                if (sVar1 < 0xf) {
                    return;
                }
                _otherX = 0x14;
                break;
            case Map::Units::UT_E_SWORD:
                if (_ptrCurrentSelectionID == (TribesState*)0x1) {
                    _otherX = 0xad;
                } else if (_ptrCurrentSelectionID == (TribesState*)0x2) {
                    _otherX = 0xae;
                } else {
                    if ((int)_ptrCurrentSelectionID < 3)
                        goto LAB_00521d1b;
                    _otherX = 0xaf;
                }
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                    (int)DAT_UnitsState::instance.units[_otherUnitID].x,
                    (int)(DAT_UnitsState::instance.units[_otherUnitID].y), _otherX);
            LAB_00521d1b:
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                    (Map::Units::UnitType)_ptrptrCurrentSelectionID, 0x15);
                if (sVar1 < 0xf) {
                    return;
                }
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                    (int)DAT_UnitsState::instance.units[_otherUnitID].x,
                    (int)(DAT_UnitsState::instance.units[_otherUnitID].y), 0x14);
                return;
            case Map::Units::UT_E_KNIGHT:
                if (_ptrCurrentSelectionID == (TribesState*)0x1) {
                    _otherX = 0x56;
                LAB_00521c6f:
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                        (int)DAT_UnitsState::instance.units[_otherUnitID].x,
                        (int)(DAT_UnitsState::instance.units[_otherUnitID].y), _otherX);
                } else {
                    if ((_ptrCurrentSelectionID == (TribesState*)0x2)
                        || (_ptrCurrentSelectionID == (TribesState*)0x3)) {
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                            (int)DAT_UnitsState::instance.units[_otherUnitID].x,
                            (int)(DAT_UnitsState::instance.units[_otherUnitID].y), 0x57);
                    }
                    if (3 < (int)_ptrCurrentSelectionID_2) {
                        _otherX = 0x58;
                        goto LAB_00521c6f;
                    }
                }
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                    (int)DAT_UnitsState::instance.units[_otherUnitID].x,
                    (int)(DAT_UnitsState::instance.units[_otherUnitID].y), 0x59);
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                    (Map::Units::UnitType)_ptrptrCurrentSelectionID, 0x15);
                if (sVar1 < 0xf) {
                    return;
                }
                _otherX = 0xfa;
                break;
            default:
                UVar2 = DAT_UnitsState::instance.units[unitID].unitType;
                if (UVar2 != Map::Units::UT_E_KNIGHT && UVar2 != Map::Units::UT_E_SWORD
                    && UVar2 != Map::Units::UT_E_MACE && UVar2 != Map::Units::UT_E_PIKE
                    && UVar2 != Map::Units::UT_LORD) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                        (Map::Units::UnitType)_ptrptrCurrentSelectionID, 0x15);
                }
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                    (Map::Units::UnitType)_ptrptrCurrentSelectionID, 0x11);
            case Map::Units::UT_E_ENGINEER:
                return;
            case Map::Units::UT_A_SWORDSMAN:
                if (sVar1 < 0xf) {
                    return;
                }
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                    (int)DAT_UnitsState::instance.units[_otherUnitID].x,
                    (int)(DAT_UnitsState::instance.units[_otherUnitID].y), 0x14);
            }
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                (int)DAT_UnitsState::instance.units[_otherUnitID].x,
                (int)(DAT_UnitsState::instance.units[_otherUnitID].y), _otherX);
        }

    }
}
}
