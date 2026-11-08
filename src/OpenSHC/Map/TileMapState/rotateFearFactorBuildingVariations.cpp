#include "../TileMapState.func.hpp"

#include "OpenSHC/Commands/MappersEnum.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Commands::MappersEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F8300
    void TileMapState::rotateFearFactorBuildingVariations()
    {
        DWORD now = timeGetTime();
        if (this->editorRockType == 5) {
            if (this->rockOrientation == 0) {
                this->rockOrientation = 2;
            } else if (this->rockOrientation == 2) {
                this->rockOrientation = 4;
            } else if (this->rockOrientation == 4) {
                this->rockOrientation = 6;
            } else {
                this->rockOrientation = 0;
            }
        }
        if ((int)now < (int)(this->lastTime + 1000)) {
            return;
        }

        this->lastTime = now;
        if (this->gateOrientationVariant == 80) {
            this->gateOrientationVariant = 81;
        } else {
            this->gateOrientationVariant = 80;
        }
        if (this->editorRockType == 0) {
            if (this->rockOrientation == 0) {
                this->rockOrientation = 2;
            } else if (this->rockOrientation == 2) {
                this->rockOrientation = 4;
            } else if (this->rockOrientation == 4) {
                this->rockOrientation = 6;
            } else {
                this->rockOrientation = 0;
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
