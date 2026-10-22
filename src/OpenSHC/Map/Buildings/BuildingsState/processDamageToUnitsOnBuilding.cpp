#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x004106D0
        void BuildingsState::processDamageToUnitsOnBuilding(int buildingID, int damagePercentage)
        {
            int const y = this->buildings[buildingID].y;
            int const x = this->buildings[buildingID].x;
            int const size = this->buildings[buildingID].widthOrHeight;
            int i = 0;
            do {
                MACRO_CALL_MEMBER(TileMapState_Func::getBuildingSizeIndexMappingData, DAT_TileMapState::ptr)(i, size);
                for (int unitID = (short)DAT_TileMapState::instance
                         .UnitLayer[DAT_ViewportRenderState::instance
                                        .translationMatrix[y + DAT_TileMapState::instance.buildingY]
                                        .addXgetTile
                             + DAT_TileMapState::instance.buildingX + x];
                    unitID != 0; unitID = (short)DAT_UnitsState::instance.units[unitID].nextUnitOnTheSameTile) {
                    int const maxHealth = DAT_UnitsState::instance.units[unitID].maxHealth;
                    DAT_UnitsState::instance.units[unitID].health += maxHealth * damagePercentage / -100;
                    if (DAT_UnitsState::instance.units[unitID].health <= 0) {
                        DAT_UnitsState::instance.units[unitID].health = 0;
                        DAT_UnitsState::instance.units[unitID].dying = 1;
                        DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                        DAT_UnitsState::instance.units[unitID].state.generic = Units::States::US_STONE_DEATH_01;
                    }
                    int healthPercentage;
                    if (maxHealth == 0) {
                        healthPercentage = 100;
                    } else {
                        healthPercentage = DAT_UnitsState::instance.units[unitID].health * 100 / maxHealth;
                    }
                    DAT_UnitsState::instance.units[unitID].healthPercentage = healthPercentage;
                    DAT_UnitsState::instance.units[unitID].healthbar = (short)healthPercentage / 10;
                }
                ++i;
            } while (i < DAT_TileMapState::instance.constructionTileCount);
        }

    }
}
}
