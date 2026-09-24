#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Units::States::UnitState;

        // FUNCTION: STRONGHOLDCRUSADER 0x004106D0
        void BuildingsState::processDamageToUnitsOnBuilding(int buildingID, int damageBonus)
        {
            // Damages all units standing on the building by damageBonus percent of their maximum health.
            // The original does not check the tile count before the first iteration.
            ushort x = this->buildings[buildingID].x;
            int t = 0;
            uint size = this->buildings[buildingID].widthOrHeight;
            ushort y = this->buildings[buildingID].y;
            do {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, DAT_TileMapState::ptr)(t, size);
                for (int unitID = (short)DAT_TileMapState::instance
                         .UnitLayer[DAT_ViewportRenderState::instance
                                        .translationMatrix[(short)y + DAT_TileMapState::instance.buildingY]
                                        .addXgetTile
                             + DAT_TileMapState::instance.buildingX + (short)x];
                    unitID != 0; unitID = (short)DAT_UnitsState::instance.units[unitID].nextUnitOnTheSameTile) {
                    int maxHealth = DAT_UnitsState::instance.units[unitID].maxHealth;
                    DAT_UnitsState::instance.units[unitID].health -= maxHealth * damageBonus / 100;
                    if (DAT_UnitsState::instance.units[unitID].health <= 0) {
                        DAT_UnitsState::instance.units[unitID].health = 0;
                        DAT_UnitsState::instance.units[unitID].dying = 1;
                        DAT_UnitsState::instance.units[unitID].animationCycleNumber = 0;
                        DAT_UnitsState::instance.units[unitID].state.generic
                            = OpenSHC::Map::Units::States::US_STONE_DEATH_01;
                    }
                    short healthPercentage;
                    if (maxHealth == 0) {
                        healthPercentage = 100;
                    } else {
                        healthPercentage = DAT_UnitsState::instance.units[unitID].health * 100 / maxHealth;
                    }
                    DAT_UnitsState::instance.units[unitID].healthPercentage = healthPercentage;
                    DAT_UnitsState::instance.units[unitID].healthbar = healthPercentage / 10;
                }
                ++t;
            } while (t < DAT_TileMapState::instance.constructionTileCount);
        }

    }
}
}
