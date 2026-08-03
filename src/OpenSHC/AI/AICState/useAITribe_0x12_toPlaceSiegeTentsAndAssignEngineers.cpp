#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/AITypeInt.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::AI::AITypeInt;
    using OpenSHC::AI::Tribes::AITribeType;
    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::Map::Units::SomeTribeBehaviorType;
    using OpenSHC::Map::Units::UnitInstructionType;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004CEFD0
    void AICState ::useAITribe_0x12_toPlaceSiegeTentsAndAssignEngineers(int playerID)

    {

        AITypeInt AVar1;

        int iVar2;

        int _counterTill6;

        int _selectionID2;

        int iVar3;

        int* piVar4;

        MappersEnum _siegeEngineType;

        int iVar5;

        int _counterTill8;

        int _aiTribeID;

        int* _siegeEngineUnitType;

        int local_18;

        int _requiredEngineers;

        short _currentAttackWave;

        short _size;

        AVar1 = DAT_GameState::instance.playerDataArray[playerID].aiType;

        if (AVar1 != OpenSHC::AI::AIT_NULL) {

            _aiTribeID = (int)DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[0x12];

            if ((_aiTribeID != 0)
                && (DAT_TribesState::instance.tribes[_aiTribeID].uid
                    == DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[0x12])) {

                _size = DAT_TribesState::instance.tribes[_aiTribeID].size;

                local_18 = (int)_size;

                iVar3 = 0;

                _siegeEngineUnitType = (int*)((int)this + (AVar1 + ~OpenSHC::AI::AIT_NULL) * 0x2a4 + 0x214);

                piVar4 = _siegeEngineUnitType;

                iVar5 = 0;

                do {

                    if (*piVar4 < 1)
                        break;

                    iVar2 = 0;

                    do {

                        if (*piVar4 == DAT_SkirmishDefinedData::instance.SiegeEngineUnitType[iVar2]) {

                            _requiredEngineers
                                = DAT_SkirmishDefinedData::instance.SiegeEngineTypeRequiredEngineers[iVar2];

                            break;
                        }

                        iVar2 = iVar2 + 1;

                    } while (iVar2 < 6);

                    iVar2 = _requiredEngineers + iVar5;

                    if (local_18 < iVar2)
                        break;

                    iVar3 = iVar3 + 1;

                    piVar4 = piVar4 + 1;

                    iVar5 = iVar2;

                } while (iVar3 < 8);

                if (0 < iVar5) {

                    for (; (_size != 0 && (0 < iVar5)); iVar5 = iVar5 + -1) {

                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::TribesState_Func::popUnitFromTribe, DAT_TribesState::ptr)(_aiTribeID);

                        _size = DAT_TribesState::instance.tribes[_aiTribeID].size;
                    }

                    _counterTill8 = 0;

                    /*
                              fixme: parameter reuse */

                    _siegeEngineType = (MappersEnum)playerID;

                    do {

                        if (*_siegeEngineUnitType < 1) {

                            return;
                        }

                        _counterTill6 = 0;

                        do {

                            if (*_siegeEngineUnitType
                                == DAT_SkirmishDefinedData::instance.SiegeEngineUnitType[_counterTill6]) {

                                _requiredEngineers
                                    = DAT_SkirmishDefinedData::instance.SiegeEngineTypeRequiredEngineers[_counterTill6];

                                _siegeEngineType
                                    = (MappersEnum)
                                          DAT_SkirmishDefinedData::instance.SiegeEngineMappersEnums[_counterTill6];

                                break;
                            }

                            _counterTill6 = _counterTill6 + 1;

                        } while (_counterTill6 < 6);

                        if (local_18 < _requiredEngineers) {

                            return;
                        }

                        local_18 = local_18 - _requiredEngineers;

                        _selectionID2 = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addEngineersToSelection, this)(
                            playerID, _requiredEngineers);

                        if (_selectionID2 == 0) {

                            return;
                        }

                        _currentAttackWave = (short)DAT_GameState::instance.playerDataArray[playerID].currentAttackWave;

                        DAT_TribesState::instance.tribes[_selectionID2].tribeType = OpenSHC::AI::Tribes::AITT_ENGINEERS;

                        DAT_TribesState::instance.tribes[_selectionID2].tribeBehaviorType
                            = OpenSHC::Map::Units::STBT_0x410_SIEGE_EQUIPMENT_CONSTRUCTION;

                        DAT_TribesState::instance.tribes[_selectionID2].attackWave = _currentAttackWave;

                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::
                                              placeSiegeTentOrTunnelAtSuitableLocationAndAssignEngineers,
                            DAT_TroopValueState::ptr)(
                            _selectionID2, _siegeEngineType, (uint)((int)(60)), (UnitInstructionType)((int)(15)));

                        _counterTill8 = _counterTill8 + 1;

                        _siegeEngineUnitType = _siegeEngineUnitType + 1;

                    } while (_counterTill8 < 8);
                }
            }
        }

        return;
    }

}
}
