#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Commands::GameCommandType;
        using OpenSHC::Game::GameMode;
        using OpenSHC::Map::Units::UnitLogicState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00535A30
        int UnitsState::createUnitSelection()
        {
            /* clear selected units */
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                400, '\0', this->selectedUnitsBitFlags);
            int _selectedCount = 0;
            for (DAT_CurrentUnitSlotID::instance = 1; (int)DAT_CurrentUnitSlotID::instance < (int)this->maxUnitCount;
                DAT_CurrentUnitSlotID::instance = DAT_CurrentUnitSlotID::instance + 1) {
                if (this->units[DAT_CurrentUnitSlotID::instance].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                    continue;
                }
                if (this->units[DAT_CurrentUnitSlotID::instance].dying != 0) {
                    continue;
                }
                if (this->units[DAT_CurrentUnitSlotID::instance].owner
                    != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    continue;
                }
                if (this->units[DAT_CurrentUnitSlotID::instance].isSelected == 0) {
                    continue;
                }
                if (this->units[DAT_CurrentUnitSlotID::instance].ifSelectedThenPlayerID
                        == DAT_GameSynchronyState::instance.currentPlayerSlotID
                    && DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
                    continue;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToSelected, DAT_TribesState::ptr)(
                    DAT_CurrentUnitSlotID::instance);
                _selectedCount = _selectedCount + 1;
            }
            if (_selectedCount == 0) {
                return 0;
            }
            DAT_TribesState::instance.DAT_CurrentTribeID
                = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getAvailableTribeID, DAT_TribesState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID);
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = DAT_TribesState::instance.DAT_CurrentTribeID;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                OpenSHC::Commands::GCT_UNITS_SELECT);
            return _selectedCount;
        }

    }
}
}
