#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00422C60
        void BuildingsState::spreadFireRandomlyToBuildings(int param_1, int param_2)
        {
            // Sets param_2 random buildings of player param_1 on fire. Very flammable buildings are 5 times as likely.
            if (param_2 <= 0 || DAT_GameState::instance.playerDataArray[param_1].campground.id <= 0) {
                return;
            }

            int weight = 0;
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState == 0 || this->buildings[i].logicalState == BLS_REMOVE
                    || this->buildings[i].owner != param_1 || this->buildings[i].fireDuration != 0
                    || this->buildings[i].cooldownTimer != 0) {
                    continue;
                }
                int flammability = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlammabilityFactor, this)(i);
                if (flammability != 0 && flammability != 4) {
                    ++weight;
                }
                if (flammability == 5) {
                    weight += 4;
                }
            }
            if (weight == 0) {
                return;
            }

            while (param_2 > 0 && weight > 0) {
                int pick = SEC_RNG::instance.currentNumber2 % weight;
                MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                for (int i = 1; i < this->maxBuildingsCount; ++i) {
                    if (this->buildings[i].logicalState == 0 || this->buildings[i].logicalState == BLS_REMOVE
                        || this->buildings[i].owner != param_1 || this->buildings[i].fireDuration != 0
                        || this->buildings[i].cooldownTimer != 0) {
                        continue;
                    }
                    int flammability = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlammabilityFactor, this)(i);
                    if (flammability == 0 || flammability == 4) {
                        continue;
                    }
                    --pick;
                    if (MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlammabilityFactor, this)(i)
                        == 5) {
                        pick -= 4;
                    }
                    if (pick < 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::lightUpBuilding, this)(i, 0, 0);
                        MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::setSpawnMoment,
                            DAT_MinimapViewState::ptr)((short)this->buildings[i].x, (short)this->buildings[i].y);
                        --weight;
                        // Note: the original checks building 2000 instead of the building set on fire
                        if (MACRO_CALL_MEMBER(
                                OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlammabilityFactor, this)(2000)
                            == 5) {
                            weight -= 4;
                        }
                        break;
                    }
                }
                --param_2;
            }
        }

    }
}
}
