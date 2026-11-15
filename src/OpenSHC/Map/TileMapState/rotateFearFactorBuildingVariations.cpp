#include "../TileMapState.func.hpp"

#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Map/Enums/EditorRockType.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F8300
    void TileMapState::rotateFearFactorBuildingVariations()
    {
        int now = timeGetTime();
        if (this->editorRockType == OpenSHC::Map::Enums::ERT_BIGROCK5) {
            if (this->rockOrientation == OpenSHC::Map::Enums::MO_NORTH) {
                this->rockOrientation = OpenSHC::Map::Enums::MO_EAST;
            } else if (this->rockOrientation == OpenSHC::Map::Enums::MO_EAST) {
                this->rockOrientation = OpenSHC::Map::Enums::MO_SOUTH;
            } else if (this->rockOrientation == OpenSHC::Map::Enums::MO_SOUTH) {
                this->rockOrientation = OpenSHC::Map::Enums::MO_WEST;
            } else {
                this->rockOrientation = OpenSHC::Map::Enums::MO_NORTH;
            }
        }
        if (now < this->lastTime + 1000) {
            return;
        }

        this->lastTime = now;
        if (this->gateOrientationVariant == 80) {
            this->gateOrientationVariant = 81;
        } else {
            this->gateOrientationVariant = 80;
        }
        if (this->editorRockType == OpenSHC::Map::Enums::ERT_NONE) {
            if (this->rockOrientation == OpenSHC::Map::Enums::MO_NORTH) {
                this->rockOrientation = OpenSHC::Map::Enums::MO_EAST;
            } else if (this->rockOrientation == OpenSHC::Map::Enums::MO_EAST) {
                this->rockOrientation = OpenSHC::Map::Enums::MO_SOUTH;
            } else if (this->rockOrientation == OpenSHC::Map::Enums::MO_SOUTH) {
                this->rockOrientation = OpenSHC::Map::Enums::MO_WEST;
            } else {
                this->rockOrientation = OpenSHC::Map::Enums::MO_NORTH;
            }
        }

        switch (DAT_TileMapState::instance.currentMapperCommand) {
        case OpenSHC::Commands::M_MAPPER_GARDEN1:
        case OpenSHC::Commands::M_MAPPER_GARDEN2:
        case OpenSHC::Commands::M_MAPPER_GARDEN3:
        case OpenSHC::Commands::M_MAPPER_GARDEN4:
        case OpenSHC::Commands::M_MAPPER_GARDEN5:
        case OpenSHC::Commands::M_MAPPER_GARDEN7:
        case OpenSHC::Commands::M_MAPPER_GARDEN8:
        case OpenSHC::Commands::M_MAPPER_GARDEN10:
        case OpenSHC::Commands::M_MAPPER_GARDEN11:
        case OpenSHC::Commands::M_MAPPER_CESS_PIT1:
        case OpenSHC::Commands::M_MAPPER_CESS_PIT2:
        case OpenSHC::Commands::M_MAPPER_CESS_PIT3:
        case OpenSHC::Commands::M_MAPPER_STATUE1:
        case OpenSHC::Commands::M_MAPPER_STATUE2:
        case OpenSHC::Commands::M_MAPPER_STATUE3:
        case OpenSHC::Commands::M_MAPPER_STATUE4:
        case OpenSHC::Commands::M_MAPPER_SHRINE1:
        case OpenSHC::Commands::M_MAPPER_POND1:
        case OpenSHC::Commands::M_MAPPER_POND3_LARGE1:
            DAT_TileMapState::instance.currentMapperCommand
                = (MappersEnum)(DAT_TileMapState::instance.currentMapperCommand + OpenSHC::Commands::M_MAPPER_AREA);
            return;
        case OpenSHC::Commands::M_MAPPER_GARDEN6:
            DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_GARDEN1;
            return;
        case OpenSHC::Commands::M_MAPPER_GARDEN9:
            DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_GARDEN7;
            return;
        case OpenSHC::Commands::M_MAPPER_GARDEN12:
            DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_GARDEN10;
            return;
        case OpenSHC::Commands::M_MAPPER_STATUE5:
            DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_STATUE1;
            return;
        case OpenSHC::Commands::M_MAPPER_POND2_SMALL:
            DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_POND1;
            return;
        case OpenSHC::Commands::M_MAPPER_POND4_LARGE2:
            DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_POND3_LARGE1;
            return;
        case OpenSHC::Commands::M_MAPPER_SHRINE2:
            DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_SHRINE1;
            return;
        case OpenSHC::Commands::M_MAPPER_CESS_PIT4:
            DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_CESS_PIT1;
            return;
        }
    }

}
}
