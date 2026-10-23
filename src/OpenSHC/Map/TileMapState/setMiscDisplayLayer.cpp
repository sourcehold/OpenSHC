
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Buildings::BuildingType;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FB0C0
    void TileMapState::setMiscDisplayLayer(int buildingID)
    {
        int rotation = this->mapOrientation / 2;
        if (DAT_BuildingsState::instance.buildings[buildingID].unknownStockpileOrSignpostRelated == 0) {
            return;
        }

        int x = (short)DAT_BuildingsState::instance.buildings[buildingID].x;
        int y = (short)DAT_BuildingsState::instance.buildings[buildingID].y;
        uint size = DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight;
        OpenSHC::Map::Buildings::BuildingTypeShort type = DAT_BuildingsState::instance.buildings[buildingID].buildingType;
        int typeInt = (short)type;
        int offsetIndex = rotation + size * 4;
        int workerTile = DAT_TerrainDefinedData::instance.orientationRelativeBuildingTileOffset1[offsetIndex];
        int displayTile = DAT_TerrainDefinedData::instance.orientationRelativeBuildingTileOffset2[offsetIndex];
        int extraTile = -1;
        switch (typeInt) {
        case OpenSHC::Map::Buildings::BT_IRONMINE:
        case OpenSHC::Map::Buildings::BT_PITCHRIG:
        case OpenSHC::Map::Buildings::BT_HUNTERSHUT:
        case OpenSHC::Map::Buildings::BT_BLACKSMITH:
        case OpenSHC::Map::Buildings::BT_BREWERY:
        case OpenSHC::Map::Buildings::BT_OILSMELTER:
        case OpenSHC::Map::Buildings::BT_STABLES:
        case OpenSHC::Map::Buildings::BT_MANORHOUSE:
        case OpenSHC::Map::Buildings::BT_KEEPFOUR:
        case OpenSHC::Map::Buildings::BT_KEEPFIVE:
        case OpenSHC::Map::Buildings::BT_TUNNEL:
        case OpenSHC::Map::Buildings::BT_FIREBALLISTA:
        case OpenSHC::Map::Buildings::BT_MAYPOLE:
        case OpenSHC::Map::Buildings::BT_CATAPULT:
        case OpenSHC::Map::Buildings::BT_TREBUCHET:
        case OpenSHC::Map::Buildings::BT_BATTERINGRAM:
        case OpenSHC::Map::Buildings::BT_SIEGETOWER:
        case OpenSHC::Map::Buildings::BT_SHIELD:
        case OpenSHC::Map::Buildings::BT_UNKNOWN4:
            /* these carry the worker on the display tile and the display on the worker tile */
            workerTile = displayTile;
            displayTile = DAT_TerrainDefinedData::instance.orientationRelativeBuildingTileOffset1[offsetIndex];
            break;
        case OpenSHC::Map::Buildings::BT_DRAWBRIDGE:
            switch (rotation) {
            case 0:
                displayTile = 0x13;
                extraTile = 6;
                break;
            case 1:
                displayTile = 0x15;
                extraTile = 8;
                break;
            case 2:
                displayTile = 5;
                extraTile = 0x12;
                break;
            case 3:
                displayTile = 3;
                extraTile = 0x10;
            }
            break;
        case OpenSHC::Map::Buildings::BT_GALLOWS:
        case OpenSHC::Map::Buildings::BT_GIBBET:
            workerTile = -1;
        }

        if ((int)size < 3 && type != OpenSHC::Map::Buildings::BT_GIBBET && type != OpenSHC::Map::Buildings::BT_GALLOWS) {
            this->MiscDisplayLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x]
                = this->MiscDisplayLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x] | 4;
            return;
        }

        int index = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, size);
            index++;
            this->MiscDisplayLayer[DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile + x + this->buildingX]
                = this->MiscDisplayLayer[DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile + x
                      + this->buildingX]
                & 0xfff3;
        } while (index < this->constructionTileCount);

        index = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(index, size);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile + x + this->buildingX;
            if (typeInt == OpenSHC::Map::Buildings::BT_GRANARY) {
                this->MiscDisplayLayer[tile] = this->MiscDisplayLayer[tile] | 8;
            } else if (typeInt == OpenSHC::Map::Buildings::BT_ARMORY) {
                this->MiscDisplayLayer[tile] = this->MiscDisplayLayer[tile] | 8;
            } else if (index == workerTile) {
                this->MiscDisplayLayer[tile] = this->MiscDisplayLayer[tile] | 8;
                /* fixme: xPosition and the field after it are written as one int */
                *(int*)&DAT_BuildingsState::instance.buildings[buildingID].xPosition = tile;
            }
            if (index == displayTile) {
                this->MiscDisplayLayer[tile] = this->MiscDisplayLayer[tile] | 4;
                DAT_BuildingsState::instance.buildings[buildingID].miscDisplayLayerTile = tile;
            }
            if (index == extraTile) {
                this->MiscDisplayLayer[tile] = this->MiscDisplayLayer[tile] | 0xc;
                DAT_BuildingsState::instance.buildings[buildingID].miscDisplayLayerTile = tile;
            }
            index++;
        } while (index < this->constructionTileCount);
    }

}
}
