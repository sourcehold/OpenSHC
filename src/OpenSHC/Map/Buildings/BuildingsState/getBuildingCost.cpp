#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040C5F0
        void BuildingsState::getBuildingCost(MappersEnum commandBuildingType, int* pStone, int* pGold)
        {
            BuildingType buildingType = MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType, this)(
                commandBuildingType);
            *pStone = this->buildingCosts[buildingType].requiredStone_0x4;
            *pGold = this->buildingCosts[buildingType].requiredGold;
            switch (commandBuildingType) {
            case OpenSHC::Commands::M_MAPPER_PEOPLE_ARCHERS:
                *pGold = 12;
                return;
            case OpenSHC::Commands::M_MAPPER_PEOPLE_SPEARMEN:
                *pGold = 8;
                return;
            case OpenSHC::Commands::M_MAPPER_PEOPLE_PIKEMEN:
            case OpenSHC::Commands::M_MAPPER_PEOPLE_MACEMEN:
            case OpenSHC::Commands::M_MAPPER_PEOPLE_XBOWMEN:
            case OpenSHC::Commands::M_MAPPER_PEOPLE_TUNNELERS:
                *pGold = 20;
                return;
            case OpenSHC::Commands::M_MAPPER_PEOPLE_SWORDSMEN:
            case OpenSHC::Commands::M_MAPPER_PEOPLE_KNIGHTS:
                *pGold = 40;
                return;
            case OpenSHC::Commands::M_MAPPER_MOAT:
            case OpenSHC::Commands::M_MAPPER_PEOPLE_LADDERMEN:
                *pGold = 1;
                return;
            case OpenSHC::Commands::M_MAPPER_PEOPLE_ENGINEERS:
                *pGold = 30;
                return;
            case OpenSHC::Commands::M_MAPPER_PEOPLE_MONKS:
                *pGold = 10;
                return;
            case OpenSHC::Commands::M_MAPPER_PITCH_DITCH:
                *pGold = 2;
                return;
            case OpenSHC::Commands::M_MAPPER_KILLING_PIT:
            case OpenSHC::Commands::M_MAPPER_BRAZIER:
                *pGold = 5;
                return;
            case OpenSHC::Commands::M_MAPPER_PEOPLE_CATAPULTS:
                *pGold = this->buildingCosts[BT_CATAPULT].requiredGold;
                return;
            case OpenSHC::Commands::M_MAPPER_PEOPLE_TREBUCHETS:
                *pGold = this->buildingCosts[BT_TREBUCHET].requiredGold;
                return;
            case OpenSHC::Commands::M_MAPPER_MANGONEL:
                *pGold = this->buildingCosts[BT_MANGONEL].requiredGold;
                return;
            case OpenSHC::Commands::M_MAPPER_BALLISTA:
                *pGold = this->buildingCosts[BT_BALLISTA].requiredGold;
                return;
            case OpenSHC::Commands::M_MAPPER_PEOPLE_PORTABLE_SHIELDS:
                *pGold = this->buildingCosts[BT_SHIELD].requiredGold;
                return;
            case OpenSHC::Commands::M_MAPPER_PEOPLE_SIEGE_TOWERS:
                *pGold = this->buildingCosts[BT_BATTERINGRAM].requiredGold;
                return;
            // Note: the battering ram and siege tower costs are swapped (or their building types are)
            case OpenSHC::Commands::M_MAPPER_PEOPLE_BATTERING_RAMS:
                *pGold = this->buildingCosts[BT_SIEGETOWER].requiredGold;
                return;
            case OpenSHC::Commands::M_MAPPER_PEOPLE_ARAB_BALLISTA:
                *pGold = this->buildingCosts[BT_FIREBALLISTA].requiredGold;
                return;
            }
        }

    }
}
}
