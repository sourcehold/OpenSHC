#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Audio/SFX/SpeechEffectID.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UIDragDropDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Audio::SFX::SpeechEffectID;
        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00535BC0
        void UnitsState::playerMakeUnitSelection(int playerID, int tribeID)
        {
            this->unitCountOfSelection[playerID] = 0;
            for (DAT_CurrentUnitSlotID::instance = 1; (int)DAT_CurrentUnitSlotID::instance < (int)this->maxUnitCount;
                DAT_CurrentUnitSlotID::instance = DAT_CurrentUnitSlotID::instance + 1) {
                if (this->units[DAT_CurrentUnitSlotID::instance].logicalState == OpenSHC::Map::Units::ULS_NORMAL
                    && this->units[DAT_CurrentUnitSlotID::instance].dying == 0
                    && this->units[DAT_CurrentUnitSlotID::instance].owner == playerID
                    && MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::unitIsSelectedByPlayer,
                           DAT_TribesState::ptr)(DAT_CurrentUnitSlotID::instance)
                        != FALSE) {
                    this->units[DAT_CurrentUnitSlotID::instance].ifSelectedThenPlayerID = (short)playerID;
                    this->units[DAT_CurrentUnitSlotID::instance].selectionRelatedFlag = 1;
                    this->unitCountOfSelection[playerID] = this->unitCountOfSelection[playerID] + 1;
                }
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::snapshotSelectionTribeAndComputeStance,
                DAT_TribesState::ptr)(playerID);
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::removeSelectedUnitsFromTheirCurrentTribes,
                DAT_TribesState::ptr)(playerID);
            int _newTribeID = MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::TribesState_Func::createPlayerTribe, DAT_TribesState::ptr)(playerID, 1, tribeID);
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitsToTribeAndComputeMovementSpeed,
                DAT_TribesState::ptr)(playerID, _newTribeID);
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::importStoredInfoFromSlot0, DAT_TribesState::ptr)(
                playerID, _newTribeID);
            if (DAT_TribesState::instance.tribes[_newTribeID].owner
                != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                return;
            }
            UnitType _unitType = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getMajoritySelectedUnitType,
                DAT_TribesState::ptr)(_newTribeID, (int*)0x0);
            if (_unitType == OpenSHC::Map::Units::UT_S_CATAPULT || _unitType == OpenSHC::Map::Units::UT_S_TOWER
                || _unitType == OpenSHC::Map::Units::UT_S_BATTERINGRAM || _unitType == OpenSHC::Map::Units::UT_S_SHIELD
                || _unitType == OpenSHC::Map::Units::UT_S_BALLISTA || _unitType == OpenSHC::Map::Units::UT_S_FBALLISTA
                || _unitType == OpenSHC::Map::Units::UT_S_TREBUCHET
                || _unitType == OpenSHC::Map::Units::UT_S_MANGONEL) {
                int _siegeEngineUnitID = DAT_TribesState::instance.tribes[_newTribeID].selectionTargetUnitID;
                int _remainingEngineers
                    = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getRemainingRequiredEngineers,
                        DAT_UnitsState::ptr)(_siegeEngineUnitID);
                if (_remainingEngineers > 0) {
                    if (this->units[_siegeEngineUnitID]
                                .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                            == 0
                        || _remainingEngineers > 3) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeechEffect, DAT_SFXState::ptr)(
                            0xe);
                    } else if (_remainingEngineers == 1) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeechEffect, DAT_SFXState::ptr)(
                            0xb);
                    } else if (_remainingEngineers == 2) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeechEffect, DAT_SFXState::ptr)(
                            0xc);
                    } else if (_remainingEngineers == 3) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeechEffect, DAT_SFXState::ptr)(
                            0xd);
                    }
                    DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                    return;
                }
                if (_unitType == OpenSHC::Map::Units::UT_S_CATAPULT
                    || _unitType == OpenSHC::Map::Units::UT_S_TREBUCHET) {
                    if ((this->units[_siegeEngineUnitID].unitType == OpenSHC::Map::Units::UT_S_CATAPULT
                            || this->units[_siegeEngineUnitID].unitType == OpenSHC::Map::Units::UT_S_TREBUCHET)
                        && this->units[_siegeEngineUnitID].stoneAmmunition <= 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                            OpenSHC::Audio::SFX::SEID_RESOURCE_NEED25);
                        DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                        return;
                    }
                }
            }
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(_unitType, 0);
            DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
        }

    }
}
}
