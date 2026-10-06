#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Commands::GameCommandType;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00536E30
        void UnitsState::giveMoveCommand(int tribeID, int x, int y, int patrol, int matchUnitSpeeds)
        {
            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = x;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam2 = y;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = tribeID;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam3 = patrol;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam4 = matchUnitSpeeds;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                OpenSHC::Commands::GCT_UNITS_MOVE);
            UnitType _mostFrequentUnitType
                = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getMajoritySelectedUnitType,
                    DAT_TribesState::ptr)(tribeID, (int*)0x0);
            dword _areaAtDestination
                = (short)DAT_TileMapState::instance
                      .PathConnectionLayer[DAT_ViewportRenderState::instance.viewportState.field24_0x60];
            uint _blockedAtDestination
                = DAT_TileMapState::instance.LogicLayer[DAT_ViewportRenderState::instance.viewportState.field24_0x60]
                & 0x10000100;
            int _canReachDestination = 0;
            int _combatUnitID
                = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::selectionContainsCombatUnit, this)(1);
            dword _areaAtUnit = (short)DAT_TileMapState::instance
                                    .PathConnectionLayer[DAT_UnitsState::instance.units[_combatUnitID].tile];
            if ((DAT_TileMapState::instance.LogicLayer[DAT_UnitsState::instance.units[_combatUnitID].tile]
                    & 0x40000000U)
                != 0) {
                return;
            }
            if (MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                    DAT_PathFindingState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID, _areaAtDestination,
                    _areaAtUnit,
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::canAUnitClimb, DAT_UnitsState::ptr)())
                != 0) {
                _canReachDestination = 1;
            }
            if (MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::selectionHasMobileAssaultUnits, DAT_UnitsState::ptr)()
                != 0) {
                int _destinationY = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent
                                        [DAT_ViewportRenderState::instance.viewportState.field24_0x60];
                int _destinationX = DAT_ViewportRenderState::instance.viewportState.field24_0x60
                    - DAT_ViewportRenderState::instance.translationMatrix[_destinationY].addXgetTile;
                if (_blockedAtDestination != 0
                    || MACRO_CALL_MEMBER(
                           OpenSHC::Map::Navigation::PathFindingState_Func::calculatePathKeepAndWallsGatesNotAllowed,
                           DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[_combatUnitID].x,
                           DAT_UnitsState::instance.units[_combatUnitID].y, _destinationX, _destinationY, 100000)
                        == 0) {
                    _canReachDestination = 0;
                }
            }
            if (matchUnitSpeeds == 0
                && (_mostFrequentUnitType == OpenSHC::Map::Units::UT_E_ARCHER
                    || _mostFrequentUnitType == OpenSHC::Map::Units::UT_E_XBOW
                    || _mostFrequentUnitType == OpenSHC::Map::Units::UT_S_CATAPULT)) {
                return;
            }
            if (DAT_TribesState::instance.tribes[tribeID].owner
                != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                return;
            }
            if (_mostFrequentUnitType == OpenSHC::Map::Units::UT_S_MANGONEL) {
                return;
            }
            if (_mostFrequentUnitType == OpenSHC::Map::Units::UT_S_BALLISTA) {
                return;
            }
            if (_mostFrequentUnitType == OpenSHC::Map::Units::UT_S_TREBUCHET) {
                return;
            }
            if (_canReachDestination != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::playUnitSelectionSound, DAT_TribesState::ptr)(
                    tribeID);
                if (MACRO_CALL_MEMBER(
                        OpenSHC::Audio::MSS::SoundSystem_Func::shouldSoundXNotBePlaying, DAT_SoundSystemState::ptr)()
                    != FALSE) {
                    return;
                }
                if (DAT_UnitsState::instance.units[_combatUnitID].unitType == OpenSHC::Map::Units::UT_E_ENGINEER
                    && DAT_UnitsState::instance.units[_combatUnitID].resourceToDeposit != 0) {
                    return;
                }
                int _leaderUnitID = DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID;
                int _distanceX = this->units[_leaderUnitID].x - x;
                int _distanceY = this->units[_leaderUnitID].y - y;
                if (_distanceX + 0x48U <= 0x90 && _distanceY + 0x48U <= 0x90) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                        _mostFrequentUnitType, 6);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                        _mostFrequentUnitType, 10);
                }
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                _mostFrequentUnitType, 9);
        }

    }
}
}
