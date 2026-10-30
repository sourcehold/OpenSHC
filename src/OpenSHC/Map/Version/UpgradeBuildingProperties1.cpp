#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Buildings/Building.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Buildings::BuildingLogicalState;

    // FUNCTION: STRONGHOLDCRUSADER 0x0041A140
    void Version::UpgradeBuildingProperties1(int version)
    {
        for (int buildingID = 1; buildingID < 2000; ++buildingID) {
            if (DAT_BuildingsState::instance.buildings[buildingID].logicalState != (BuildingLogicalState)0) {
                int buildingType = DAT_BuildingsState::instance.buildings[buildingID].buildingType;
                // Only the lower half of spriteSheetID is written
                *(short*)&DAT_BuildingsState::instance.buildings[buildingID].spriteSheetID
                    = DAT_BuildingDefinedData::instance.Building_SpriteSheet_ID_Array_1[buildingType].shortValue;
                switch (buildingType) {
                case Buildings::BT_HOVEL:
                    if (version >= 140) {
                        break;
                    }
                default:
                    DAT_BuildingsState::instance.buildings[buildingID].spriteID
                        = DAT_BuildingDefinedData::instance.Building_Sprite_ID_Array_1[buildingType];
                    break;
                case Buildings::BT_UNKNOWN1:
                case Buildings::BT_GARDEN:
                case Buildings::BT_CESSPIT:
                case Buildings::BT_STATUE:
                case Buildings::BT_SHRINE:
                case Buildings::BT_POND:
                    break;
                }
                DAT_BuildingsState::instance.buildings[buildingID].visuallyActiveSpriteID
                    = DAT_BuildingDefinedData::instance.VisuallyActiveSpriteIDOffsets[buildingType];
                DAT_BuildingsState::instance.buildings[buildingID].gfxOffset
                    = DAT_BuildingDefinedData::instance.GFXOffsets[buildingType];
                DAT_BuildingsState::instance.buildings[buildingID].gfxOffset2
                    = DAT_BuildingDefinedData::instance.Building_Sprite_ID_Array_2[buildingType];
                DAT_BuildingsState::instance.buildings[buildingID].gfxOffset3
                    = DAT_BuildingDefinedData::instance.GFXOffsets3[buildingType];
                DAT_BuildingsState::instance.buildings[buildingID].unknownFlag4
                    = DAT_BuildingDefinedData::instance.BuildingFlag4Defaults[buildingType].byteValue;
                DAT_BuildingsState::instance.buildings[buildingID].spriteOffetX
                    = DAT_BuildingDefinedData::instance.SpriteOffsets1[buildingType][0][0];
                DAT_BuildingsState::instance.buildings[buildingID].spriteOffetY
                    = DAT_BuildingDefinedData::instance.SpriteOffsets1[buildingType][1][0];
                DAT_BuildingsState::instance.buildings[buildingID].animAdvanceThrottle
                    = DAT_BuildingDefinedData::instance.AnimAdvanceThrottles[buildingType];
                DAT_BuildingsState::instance.buildings[buildingID].spriteID2
                    = DAT_BuildingDefinedData::instance.SpriteIDs2[buildingType].shortValue;
                if (DAT_BuildingsState::instance.buildings[buildingID].currentHealth
                    == DAT_BuildingsState::instance.buildings[buildingID].maxHealth) {
                    DAT_BuildingsState::instance.buildings[buildingID].currentHealth
                        = DAT_BuildingsState::instance.buildings[buildingID].maxHealth
                        = DAT_BuildingDefinedData::instance.BuildingHP[buildingType].shortValue;
                }
                DAT_BuildingsState::instance.buildings[buildingID].oldVisualActiveState = -1;
            }
        }
    }

}
}
