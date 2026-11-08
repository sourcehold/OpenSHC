#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040C5F0
        void BuildingsState::getBuildingCost(MappersEnum commandBuildingType, int* pStone, int* pGold)
        {
            int const buildingType = MACRO_CALL_MEMBER(
                BuildingsState_Func::convertCommandBuildingTypeToBuildingType, this)(commandBuildingType);
            *pStone = this->buildingCosts[buildingType].requiredStone_0x4;
            *pGold = this->buildingCosts[buildingType].requiredGold;
            switch (commandBuildingType) {
            case Commands::M_MAPPER_PEOPLE_ARCHERS:
                *pGold = 12;
                break;
            case Commands::M_MAPPER_PEOPLE_SPEARMEN:
                *pGold = 8;
                break;
            case Commands::M_MAPPER_PEOPLE_PIKEMEN:
            case Commands::M_MAPPER_PEOPLE_MACEMEN:
            case Commands::M_MAPPER_PEOPLE_XBOWMEN:
            case Commands::M_MAPPER_PEOPLE_TUNNELERS:
                *pGold = 20;
                break;
            case Commands::M_MAPPER_PEOPLE_SWORDSMEN:
            case Commands::M_MAPPER_PEOPLE_KNIGHTS:
                *pGold = 40;
                break;
            case Commands::M_MAPPER_MOAT:
            case Commands::M_MAPPER_PEOPLE_LADDERMEN:
                *pGold = 1;
                break;
            case Commands::M_MAPPER_PEOPLE_ENGINEERS:
                *pGold = 30;
                break;
            case Commands::M_MAPPER_PEOPLE_MONKS:
                *pGold = 10;
                break;
            case Commands::M_MAPPER_PITCH_DITCH:
                *pGold = 2;
                break;
            case Commands::M_MAPPER_KILLING_PIT:
            case Commands::M_MAPPER_BRAZIER:
                *pGold = 5;
                break;
            case Commands::M_MAPPER_PEOPLE_CATAPULTS:
                *pGold = this->buildingCosts[BT_CATAPULT].requiredGold;
                break;
            case Commands::M_MAPPER_PEOPLE_TREBUCHETS:
                *pGold = this->buildingCosts[BT_TREBUCHET].requiredGold;
                break;
            case Commands::M_MAPPER_MANGONEL:
                *pGold = this->buildingCosts[BT_MANGONEL].requiredGold;
                break;
            case Commands::M_MAPPER_BALLISTA:
                *pGold = this->buildingCosts[BT_BALLISTA].requiredGold;
                break;
            case Commands::M_MAPPER_PEOPLE_PORTABLE_SHIELDS:
                *pGold = this->buildingCosts[BT_SHIELD].requiredGold;
                break;
            case Commands::M_MAPPER_PEOPLE_SIEGE_TOWERS:
                // The original reads entry 82 here and entry 83 for battering rams, so one of the two enums
                // probably has these names swapped.
                *pGold = this->buildingCosts[BT_BATTERINGRAM].requiredGold;
                break;
            case Commands::M_MAPPER_PEOPLE_BATTERING_RAMS:
                *pGold = this->buildingCosts[BT_SIEGETOWER].requiredGold;
                break;
            case Commands::M_MAPPER_PEOPLE_ARAB_BALLISTA:
                *pGold = this->buildingCosts[BT_FIREBALLISTA].requiredGold;
                break;
            }
        }

    }
}
}
