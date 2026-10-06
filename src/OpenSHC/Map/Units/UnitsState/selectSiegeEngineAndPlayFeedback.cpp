#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Audio/SFX/SpeechEffectID.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UIDragDropDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Audio::SFX::SpeechEffectID;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00535E20
        void UnitsState::selectSiegeEngineAndPlayFeedback(int playerID, int unitID, int tribeID)
        {
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::removeUnitFromTribe, DAT_TribesState::ptr)(
                unitID, DAT_UnitsState::instance.units[unitID].tribeID);
            this->units[unitID].isSelected = 1;
            this->units[unitID].selectionRelatedFlag = 1;
            this->units[unitID].ifSelectedThenPlayerID = (short)playerID;
            this->unitCountOfSelection[playerID] = this->unitCountOfSelection[playerID] + 1;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToTribeAndUpdateTribeMovementSpeed,
                DAT_TribesState::ptr)(playerID, unitID, tribeID);
            if (DAT_TribesState::instance.tribes[tribeID].owner
                == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                UnitType _unitType = (UnitType)(short)this->units[unitID].unitType;
                if (_unitType == OpenSHC::Map::Units::UT_S_CATAPULT || _unitType == OpenSHC::Map::Units::UT_S_TOWER
                    || _unitType == OpenSHC::Map::Units::UT_S_BATTERINGRAM
                    || _unitType == OpenSHC::Map::Units::UT_S_SHIELD || _unitType == OpenSHC::Map::Units::UT_S_BALLISTA
                    || _unitType == OpenSHC::Map::Units::UT_S_FBALLISTA
                    || _unitType == OpenSHC::Map::Units::UT_S_TREBUCHET
                    || _unitType == OpenSHC::Map::Units::UT_S_MANGONEL) {
                    int _siegeEngineUnitID = DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID;
                    int _remainingEngineers
                        = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getRemainingRequiredEngineers,
                            DAT_UnitsState::ptr)(_siegeEngineUnitID);
                    if (_remainingEngineers > 0) {
                        if (DAT_UnitsState::instance.units[_siegeEngineUnitID]
                                    .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                                == 0
                            || _remainingEngineers > 3) {
                            MACRO_CALL_MEMBER(
                                OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeechEffect, DAT_SFXState::ptr)(0xe);
                        } else if (_remainingEngineers == 1) {
                            MACRO_CALL_MEMBER(
                                OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeechEffect, DAT_SFXState::ptr)(0xb);
                        } else if (_remainingEngineers == 2) {
                            MACRO_CALL_MEMBER(
                                OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeechEffect, DAT_SFXState::ptr)(0xc);
                        } else if (_remainingEngineers == 3) {
                            MACRO_CALL_MEMBER(
                                OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeechEffect, DAT_SFXState::ptr)(0xd);
                        }
                    } else if ((_unitType == OpenSHC::Map::Units::UT_S_CATAPULT
                                   || _unitType == OpenSHC::Map::Units::UT_S_TREBUCHET)
                        && DAT_UnitsState::instance.units[_siegeEngineUnitID].stoneAmmunition < 1) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                            OpenSHC::Audio::SFX::SEID_RESOURCE_NEED25);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                            _unitType, 0);
                    }
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                        _unitType, 0);
                }
            }
            DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
        }

    }
}
}
