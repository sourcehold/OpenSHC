#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Game::GameMode;
        using OpenSHC::Map::Units::UnitInstructionType;
        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0053E440
        int UnitsState::spawnUnit(int playerID, int displayColor, int microXPosition, int microYPosition,
            int terrainHeight, UnitType unitType)
        {
            /* Loop until we find free slot. */
            int _unitID = 1;
            for (; _unitID < 0x9c4; ++_unitID) {
                if (this->units[_unitID].logicalState == OpenSHC::Map::Units::ULS_INVISIBLE) {
                    break;
                }
                if (_unitID > 0x9c2) {
                    return 0;
                }
            }
            if ((int)this->maxUnitCount <= _unitID) {
                this->maxUnitCount = _unitID + 1;
            }
            this->units[_unitID].uid = DAT_GameCore::instance.uniqueGameObjectTracker;
            dword _time = DAT_GameCore::instance.mapTimeInTicks;
            DAT_GameCore::instance.uniqueGameObjectTracker = DAT_GameCore::instance.uniqueGameObjectTracker + 1;
            this->units[_unitID].logicalState = (UnitLogicState)1;
            this->units[_unitID].owner = (short)playerID;
            this->units[_unitID].terrainOrClimbHeight = (short)terrainHeight;
            this->units[_unitID].microXPosition = (short)microXPosition + 4;
            this->units[_unitID].time = _time;
            this->units[_unitID].calculatedOwnerPlayerIndex = (short)displayColor;
            this->units[_unitID].microYPosition = (short)microYPosition + 4;
            this->units[_unitID].facingDirection = 0;
            this->units[_unitID].displayColorPlayerID = (short)displayColor;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setUnitValues, this)(_unitID, unitType);
            if (unitType == OpenSHC::Map::Units::UT_S_TOWER) {
                this->units[_unitID].calculatedOwnerPlayerIndex = 0;
                this->units[_unitID].displayColorPlayerID = 0;
            } else if (unitType == OpenSHC::Map::Units::UT_CAGEDOG) {
                this->units[_unitID].calculatedOwnerPlayerIndex = 0;
            }
            short _y
                = (short)((this->units[_unitID].microYPosition + (this->units[_unitID].microYPosition >> 0x1f & 7U))
                    >> 3);
            this->units[_unitID].mimicCurrentYPosition = _y;
            this->units[_unitID].y = _y;
            this->units[_unitID].destinationY_2Unk = _y;
            short _x
                = (short)((this->units[_unitID].microXPosition + (this->units[_unitID].microXPosition >> 0x1f & 7U))
                    >> 3);
            this->units[_unitID].mimicCurrentXPosition = _x;
            this->units[_unitID].x = _x;
            this->units[_unitID].destinationX_2Unk = _x;
            this->units[_unitID].movementRelated = 8;
            this->units[_unitID].field105_0xe8 = 0;
            this->units[_unitID].targetingType = (UnitInstructionType)0;
            this->units[_unitID].tile = _x + DAT_ViewportRenderState::instance.translationMatrix[_y].addXgetTile;
            this->units[_unitID].fixedRng = SEC_RNG::instance.currentNumber2;
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            if (unitType == OpenSHC::Map::Units::UT_S_CATAPULT || unitType == OpenSHC::Map::Units::UT_S_TREBUCHET) {
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] == -1) {
                    if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
                        this->units[_unitID].stoneAmmunition = 0x28;
                    } else {
                        this->units[_unitID].stoneAmmunition = 0x14;
                    }
                } else {
                    this->units[_unitID].stoneAmmunition = 0x14;
                }
            } else if (unitType == OpenSHC::Map::Units::UT_S_MANGONEL) {
                if (DAT_TileMapState::instance.BuildingLayer[this->units[_unitID].tile] != 0) {
                    DAT_BuildingsState::instance
                        .buildings[DAT_TileMapState::instance.BuildingLayer[this->units[_unitID].tile]]
                        .containsSiegeMangonel1OrBallista2 = 1;
                }
            } else if (unitType == OpenSHC::Map::Units::UT_S_BALLISTA) {
                if (DAT_TileMapState::instance.BuildingLayer[this->units[_unitID].tile] != 0) {
                    DAT_BuildingsState::instance
                        .buildings[DAT_TileMapState::instance.BuildingLayer[this->units[_unitID].tile]]
                        .containsSiegeMangonel1OrBallista2 = 2;
                }
            } else if (unitType == OpenSHC::Map::Units::UT_CHILD) {
                if ((this->units[_unitID].fixedRng & 0x80) != 0) {
                    this->units[_unitID].spriteID = 0x81;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::assignNameToUnit, this)(_unitID);
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::commitPendingUnitPosition, this)(_unitID);
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::updateMicroPosition, this)(_unitID);
            return _unitID;
        }

    }
}
}
