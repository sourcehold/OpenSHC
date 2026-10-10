#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/TrailType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/Units/UnitTypeInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_SH1_SiegeAdvancedMode.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Game::GameMode;
        using Game::GameMode2;
        using Game::TrailType;
        using Map::Units::UnitType;
        using Map::Units::UnitTypeInt;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00527440
        void TribesState::spawnQueuedReinforcementWaves()
        {
            int iVar3;
            dword dVar4;
            dword _tribeID1;
            int iVar5;
            int iVar6;
            int* piVar7;
            SiegeUnitCounts* pSVar8;
            int _siegeInfoSubIndex;
            int _playerID;
            int _nextDestination;
            int _tribeType;
            UnitTypeInt _unitType;
            int _destinationIndexTracker;
            int _unitType1Count;
            int local_4;
            int _playerID_2;
            int _count;
            int _destinationIndex;
            int _newCount;
            _tribeType = 0;
            bool bVar1 = false;
            _unitType = ((UnitType)0);
            _destinationIndexTracker = 0;
            bool bVar2 = false;
            if (DAT_GameCore::instance.gameMode_2 != Game::GM_EDITOR
                && DAT_GameCore::instance.gameMode_2 != Game::GM_SIEGE_THAT
                && (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY
                    || (((DAT_GameCore::instance.gameMode_2 == Game::GM_BUILDERUnk
                             || (DAT_GameCore::instance.gameMode_2 == Game::GM_CRUSADER_TUTORIAL))
                        || (0 < DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .keep.id))))
                && 0 <= DAT_GameState::instance.mapAndTime.countUpTo201) {
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::updateTribeUnitAssignments, this)();
                _playerID_2 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                if ((DAT_GameCore::instance.gameMode_2 == Game::GM_BUILDERUnk)
                    || (DAT_GameCore::instance.gameMode_2 == Game::GM_CRUSADER_TUTORIAL)) {
                    pSVar8 = &DAT_GameState::instance.mapAndTime.siegeInformation;
                    do {
                        iVar3 = 100;
                        if (!DAT_GameState::instance.mapAndTime.difficulty) {
                            if (_playerID_2 == 1) {
                                iVar3 = 0x43;
                            } else if (!DAT_SH1_SiegeAdvancedMode::instance) {
                            LAB_005279a0:
                                iVar3 = 167;
                            }
                        } else if (DAT_GameState::instance.mapAndTime.difficulty == 2) {
                            if (_playerID_2 == 1) {
                                iVar3 = 133;
                            } else if (!DAT_SH1_SiegeAdvancedMode::instance) {
                                iVar3 = 75;
                            }
                        } else if (DAT_GameState::instance.mapAndTime.difficulty == 3) {
                            if (_playerID_2 == 1)
                                goto LAB_005279a0;
                            if (!DAT_SH1_SiegeAdvancedMode::instance) {
                                iVar3 = 50;
                            }
                        }
                        pSVar8->archers = (pSVar8->archers * iVar3) / 100;
                        pSVar8 = (SiegeUnitCounts*)&pSVar8->crossbowmen;
                    } while ((int)pSVar8 < 0x117cea0);
                    _siegeInfoSubIndex = 0;
                    do {
                        if (DAT_GameState::instance.mapAndTime.startGoods[_siegeInfoSubIndex + 0x19] != 0) {
                            switch (_siegeInfoSubIndex) {
                            case 0:
                                _tribeType = 3;
                                _unitType = Map::Units::UT_E_ARCHER;
                                break;
                            case 1:
                                _tribeType = 7;
                                _unitType = Map::Units::UT_E_XBOW;
                                break;
                            case 2:
                                _tribeType = 5;
                                _unitType = Map::Units::UT_E_SPEAR;
                                break;
                            case 3:
                                _tribeType = 6;
                                _unitType = Map::Units::UT_E_PIKE;
                                break;
                            case 4:
                                _tribeType = 9;
                                _unitType = Map::Units::UT_E_MACE;
                                break;
                            case 5:
                                _tribeType = 8;
                                _unitType = Map::Units::UT_E_SWORD;
                                break;
                            case 6:
                                _tribeType = 10;
                                _unitType = Map::Units::UT_E_KNIGHT;
                                break;
                            case 7:
                                _tribeType = 4;
                                _unitType = Map::Units::UT_E_LADDER;
                                break;
                            case 8:
                                _tribeType = 0xb;
                                _unitType = Map::Units::UT_E_ENGINEER;
                                break;
                            case 9:
                                _tribeType = 0xc;
                                _unitType = Map::Units::UT_E_MONK;
                                break;
                            case 10:
                                _tribeType = 0x19;
                                _unitType = Map::Units::UT_A_ARCHER;
                                break;
                            case 0xb:
                                _tribeType = 0x1a;
                                _unitType = Map::Units::UT_A_SLAVE;
                                break;
                            case 0xc:
                                _tribeType = 0x1b;
                                _unitType = Map::Units::UT_A_SLINGER;
                                break;
                            case 0xd:
                                _tribeType = 0x1c;
                                _unitType = Map::Units::UT_A_ASSASSIN;
                                break;
                            case 0xe:
                                _tribeType = 0x1d;
                                _unitType = Map::Units::UT_A_HARCHER;
                                break;
                            case 0xf:
                                _tribeType = 0x1e;
                                _unitType = Map::Units::UT_A_SWORDSMAN;
                                break;
                            case 0x10:
                                _tribeType = 0x1f;
                                _unitType = Map::Units::UT_A_FIRETHROWER;
                                break;
                            case 0x11:
                                _tribeType = 0x18;
                                _unitType = Map::Units::UT_S_FBALLISTA;
                            }
                            do {
                                _count = DAT_GameState::instance.mapAndTime.startGoods[_siegeInfoSubIndex + 0x19];
                                int _nUnits = _count;
                                if (9 < _count) {
                                    _nUnits = 9;
                                }
                                DAT_GameState::instance.mapAndTime.startGoods[_siegeInfoSubIndex + 0x19]
                                    = _count - _nUnits;
                                _destinationIndex = _destinationIndexTracker;
                                if (39 < _destinationIndexTracker) {
                                    _destinationIndex = 0;
                                }
                                _nextDestination = _destinationIndexTracker + 1;
                                _tribeID1 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createTribeWithSpawnedUnit,
                                    this)((short)_destinationIndexTracker, (undefined4)((int)(_tribeType)),
                                    DAT_GameState::instance.mapAndTime.unitMoveDestinationXYPairs[0][_destinationIndex]
                                        .x,
                                    DAT_GameState::instance.mapAndTime.unitMoveDestinationXYPairs[0][_destinationIndex]
                                        .y,
                                    2, (UnitType)((int)(_unitType)), _nUnits);
                                _newCount = DAT_GameState::instance.mapAndTime.startGoods[_siegeInfoSubIndex + 0x19];
                                this->tribes[_tribeID1].unknownAttackRelatedUpdateCounter = 0x32;
                                _destinationIndexTracker = _nextDestination;
                            } while (_newCount);
                        }
                        _siegeInfoSubIndex = _siegeInfoSubIndex + 1;
                        iVar3 = DAT_MapPropertiesState::instance.SEC_Section1067.tunnelersCount;
                    } while (_siegeInfoSubIndex < 20);
                    while (iVar3) {
                        iVar6 = iVar3;
                        if (9 < iVar3) {
                            iVar6 = 9;
                        }
                        iVar5 = _destinationIndexTracker;
                        if (0x27 < _destinationIndexTracker) {
                            iVar5 = 0;
                        }
                        dVar4 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createTribeWithSpawnedUnit, this)(
                            (short)_destinationIndexTracker, 2,
                            DAT_GameState::instance.mapAndTime.unitMoveDestinationXYPairs[0][iVar5].x,
                            DAT_GameState::instance.mapAndTime.unitMoveDestinationXYPairs[0][iVar5].y, 2,
                            Map::Units::UT_TUNNELER, iVar6);
                        this->tribes[dVar4].unknownAttackRelatedUpdateCounter = 0x32;
                        iVar3 = iVar3 - iVar6;
                        _destinationIndexTracker = _destinationIndexTracker + 1;
                    }
                    DAT_GameState::instance.mapAndTime.countUpTo201 = -1;
                } else if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
                    DAT_GameState::instance.mapAndTime.countUpTo201
                        = DAT_GameState::instance.mapAndTime.countUpTo201 + 1;
                    if (200 < DAT_GameState::instance.mapAndTime.countUpTo201) {
                        DAT_GameState::instance.mapAndTime.countUpTo201 = 0;
                        iVar3 = 0;
                        while (true) {
                            if (iVar3 == 7) {
                                iVar3 = 8;
                            }
                            if (DAT_GameState::instance.mapAndTime.startGoods[iVar3 + 0x19] != 0)
                                break;
                            iVar3 = iVar3 + 1;
                            if (9 < iVar3)
                                goto LAB_005276b5;
                        }
                        switch (iVar3) {
                        case 0:
                            _tribeType = 3;
                            _unitType = Map::Units::UT_E_ARCHER;
                            break;
                        case 1:
                            _tribeType = 7;
                            _unitType = Map::Units::UT_E_XBOW;
                            break;
                        case 2:
                            _tribeType = 5;
                            _unitType = Map::Units::UT_E_SPEAR;
                            break;
                        case 3:
                            _tribeType = 6;
                            _unitType = Map::Units::UT_E_PIKE;
                            break;
                        case 4:
                            _tribeType = 9;
                            _unitType = Map::Units::UT_E_MACE;
                            break;
                        case 5:
                            _tribeType = 8;
                            _unitType = Map::Units::UT_E_SWORD;
                            break;
                        case 6:
                            _tribeType = 10;
                            _unitType = Map::Units::UT_E_KNIGHT;
                            break;
                        case 8:
                            _tribeType = 0xb;
                            _unitType = Map::Units::UT_E_ENGINEER;
                            break;
                        case 9:
                            _tribeType = 0xc;
                            _unitType = Map::Units::UT_E_MONK;
                        }
                        iVar6 = DAT_GameState::instance.mapAndTime.startGoods[iVar3 + 0x19];
                        _unitType1Count = iVar6;
                        if (9 < iVar6) {
                            _unitType1Count = 9;
                        }
                        _playerID = 1;
                        DAT_GameState::instance.mapAndTime.startGoods[iVar3 + 0x19] = iVar6 - _unitType1Count;
                        piVar7 = &DAT_GameState::instance.playerDataArray[1].campground.xEntry;
                        do {
                            if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_playerID] != -1)
                                || (DAT_GameSynchronyState::instance.currentAIArray[_playerID] != 0)) {
                                dVar4 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::spawnUnitsIntoNewTribe, this)(
                                    _destinationIndexTracker, _tribeType, (int)(*piVar7), (int)(piVar7[1]), _playerID,
                                    (UnitType)((int)(_unitType)), ((UnitType)0), _unitType1Count, 0);
                                this->tribes[dVar4].unknownAttackRelatedUpdateCounter = 0x32;
                                bVar2 = true;
                                _destinationIndexTracker = _destinationIndexTracker + 1;
                            }
                            _playerID = _playerID + 1;
                            piVar7 = piVar7 + 0xe7d;
                        } while (_playerID < 9);
                    LAB_005276b5:
                        iVar3 = 10;
                        while (DAT_GameState::instance.mapAndTime.startGoods[iVar3 + 0x19] == 0) {
                            iVar3 = iVar3 + 1;
                            if (0x13 < iVar3)
                                goto LAB_005277c5;
                        }
                        switch (iVar3) {
                        case 10:
                            _tribeType = 0x19;
                            _unitType = Map::Units::UT_A_ARCHER;
                            break;
                        case 0xb:
                            _tribeType = 0x1a;
                            _unitType = Map::Units::UT_A_SLAVE;
                            break;
                        case 0xc:
                            _tribeType = 0x1b;
                            _unitType = Map::Units::UT_A_SLINGER;
                            break;
                        case 0xd:
                            _tribeType = 0x1c;
                            _unitType = Map::Units::UT_A_ASSASSIN;
                            break;
                        case 0xe:
                            _tribeType = 0x1d;
                            _unitType = Map::Units::UT_A_HARCHER;
                            break;
                        case 0xf:
                            _tribeType = 0x1e;
                            _unitType = Map::Units::UT_A_SWORDSMAN;
                            break;
                        case 0x10:
                            _tribeType = 0x1f;
                            _unitType = Map::Units::UT_A_FIRETHROWER;
                            break;
                        case 0x11:
                            _tribeType = 0x18;
                            _unitType = Map::Units::UT_S_FBALLISTA;
                        }
                        iVar6 = DAT_GameState::instance.mapAndTime.startGoods[iVar3 + 0x19];
                        _unitType1Count = iVar6;
                        if (9 < iVar6) {
                            _unitType1Count = 9;
                        }
                        iVar5 = 1;
                        DAT_GameState::instance.mapAndTime.startGoods[iVar3 + 0x19] = iVar6 - _unitType1Count;
                        piVar7 = &DAT_GameState::instance.playerDataArray[1].campground.xEntry;
                        do {
                            if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar5] != -1)
                                || (DAT_GameSynchronyState::instance.currentAIArray[iVar5] != 0)) {
                                dVar4 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::spawnUnitsIntoNewTribe, this)(
                                    _destinationIndexTracker, _tribeType, (int)(*piVar7), (int)(piVar7[1]), iVar5,
                                    (UnitType)((int)(_unitType)), ((UnitType)0), _unitType1Count, 0);
                                this->tribes[dVar4].unknownAttackRelatedUpdateCounter = 0x32;
                                bVar2 = true;
                                _destinationIndexTracker = _destinationIndexTracker + 1;
                            }
                            iVar5 = iVar5 + 1;
                            piVar7 = piVar7 + 0xe7d;
                        } while (iVar5 < 9);
                    LAB_005277c5:
                        if (!bVar2) {
                            DAT_GameState::instance.mapAndTime.countUpTo201 = -1;
                        }
                    }
                } else if ((DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER)
                    || (!DAT_GameState::instance.mapAndTime.skirmishNoRushTicks)) {
                    DAT_GameState::instance.mapAndTime.countUpTo201
                        = DAT_GameState::instance.mapAndTime.countUpTo201 + 1;
                    iVar3 = 200;
                    if (DAT_GameCore::instance.gameMode_2 == Game::GM_SKIRMISH_AND_MULTIPLAYER
                        && DAT_GameCore::instance.isSkirmishTrail == TRUE
                        && DAT_GameCore::instance.currentTrailType == Game::TT_EXTREME) {
                        iVar3 = 0x32;
                    }
                    if (iVar3 < DAT_GameState::instance.mapAndTime.countUpTo201) {
                        DAT_GameState::instance.mapAndTime.countUpTo201 = 0;
                        local_4 = 1;
                        _unitType1Count = 0x14;
                        piVar7 = &DAT_GameState::instance.playerDataArray[1].campground.xEntry;
                        do {
                            if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[local_4] != -1)
                                || (DAT_GameSynchronyState::instance.currentAIArray[local_4] != 0)) {
                                iVar3 = 0;
                                do {
                                    if (iVar3 == 7) {
                                        iVar3 = 8;
                                    }
                                    if (*(int*)(DAT_GameState::instance.mapAndTime.unused_0x3ff00
                                            + (_unitType1Count + iVar3) * 4)
                                        != 0) {
                                        switch (iVar3) {
                                        case 0:
                                            _tribeType = 3;
                                            _unitType = Map::Units::UT_E_ARCHER;
                                            break;
                                        case 1:
                                            _tribeType = 7;
                                            _unitType = Map::Units::UT_E_XBOW;
                                            break;
                                        case 2:
                                            _tribeType = 5;
                                            _unitType = Map::Units::UT_E_SPEAR;
                                            break;
                                        case 3:
                                            _tribeType = 6;
                                            _unitType = Map::Units::UT_E_PIKE;
                                            break;
                                        case 4:
                                            _tribeType = 9;
                                            _unitType = Map::Units::UT_E_MACE;
                                            break;
                                        case 5:
                                            _tribeType = 8;
                                            _unitType = Map::Units::UT_E_SWORD;
                                            break;
                                        case 6:
                                            _tribeType = 10;
                                            _unitType = Map::Units::UT_E_KNIGHT;
                                            break;
                                        case 8:
                                            _tribeType = 0xb;
                                            _unitType = Map::Units::UT_E_ENGINEER;
                                            break;
                                        case 9:
                                            _tribeType = 0xc;
                                            _unitType = Map::Units::UT_E_MONK;
                                            break;
                                        case 10:
                                            _tribeType = 0x19;
                                            _unitType = Map::Units::UT_A_ARCHER;
                                            break;
                                        case 0xb:
                                            _tribeType = 0x1a;
                                            _unitType = Map::Units::UT_A_SLAVE;
                                            break;
                                        case 0xc:
                                            _tribeType = 0x1b;
                                            _unitType = Map::Units::UT_A_SLINGER;
                                            break;
                                        case 0xd:
                                            _tribeType = 0x1c;
                                            _unitType = Map::Units::UT_A_ASSASSIN;
                                            break;
                                        case 0xe:
                                            _tribeType = 0x1d;
                                            _unitType = Map::Units::UT_A_HARCHER;
                                            break;
                                        case 0xf:
                                            _tribeType = 0x1e;
                                            _unitType = Map::Units::UT_A_SWORDSMAN;
                                            break;
                                        case 0x10:
                                            _tribeType = 0x1f;
                                            _unitType = Map::Units::UT_A_FIRETHROWER;
                                            break;
                                        case 0x11:
                                            _tribeType = 0x18;
                                            _unitType = Map::Units::UT_S_FBALLISTA;
                                        }
                                        iVar6 = *(int*)(DAT_GameState::instance.mapAndTime.unused_0x3ff00
                                            + (_unitType1Count + iVar3) * 4);
                                        iVar5 = iVar6;
                                        if (9 < iVar6) {
                                            iVar5 = 9;
                                        }
                                        *(int*)(DAT_GameState::instance.mapAndTime.unused_0x3ff00
                                            + (_unitType1Count + iVar3) * 4) = iVar6 - iVar5;
                                        dVar4 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::spawnUnitsIntoNewTribe,
                                            this)(_destinationIndexTracker, _tribeType, (int)(*piVar7),
                                            (int)(piVar7[1]), local_4, (UnitType)((int)(_unitType)), ((UnitType)0),
                                            iVar5, 0);
                                        this->tribes[dVar4].unknownAttackRelatedUpdateCounter = 0x32;
                                        bVar1 = true;
                                        _destinationIndexTracker = _destinationIndexTracker + 1;
                                        break;
                                    }
                                    iVar3 = iVar3 + 1;
                                } while (iVar3 < 0x14);
                            }
                            _unitType1Count = _unitType1Count + 0x14;
                            local_4 = local_4 + 1;
                            piVar7 = piVar7 + 0xe7d;
                        } while (local_4 < 9);
                        if (!bVar1) {
                            DAT_GameState::instance.mapAndTime.countUpTo201 = -1;
                        }
                    }
                }
            }
        }

    }
}
}
