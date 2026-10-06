#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Commands::MappersEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004F8300
    void TileMapState::rotateFearFactorBuildingVariations()
    {
        /*
          currentMapperCommand is reached through the global instance's absolute address, and the
          switch below is the original's byte table at 0x004F847C into the jump table at 0x004F8454,
          biased by M_MAPPER_GARDEN1. The "- 1 & 6" forms are the original's setcc/dec/and idiom.
        */
        DWORD now = timeGetTime();
        if (this->field80_0x554894 == 5) {
            if (this->rockOrientation == 0) {
                this->rockOrientation = 2;
            } else if (this->rockOrientation == 2) {
                this->rockOrientation = 4;
            } else {
                this->rockOrientation = (this->rockOrientation != 4) - 1 & 6;
            }
        }
        if ((int)(this->lastTime + 1000) > (int)now) {
            return;
        }

        this->lastTime = now;
        this->field78_0x55488c = (this->field78_0x55488c == 0x50) + 0x50;
        if (this->field80_0x554894 == 0) {
            if (this->rockOrientation == 0) {
                this->rockOrientation = 2;
            } else if (this->rockOrientation == 2) {
                this->rockOrientation = 4;
            } else {
                this->rockOrientation = (this->rockOrientation != 4) - 1 & 6;
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
