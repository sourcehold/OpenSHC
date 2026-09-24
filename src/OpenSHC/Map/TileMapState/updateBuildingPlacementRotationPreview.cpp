#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00504EE0
    void TileMapState::updateBuildingPlacementRotationPreview(int x, int y)
    {
        BOOLEnum const previousPlacementFail = this->buildingPlacementFail;
        this->buildingPlacementFail = FALSE;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::determineBuildingPlacementRotation, this)(x, y);
        this->buildingPlacementFail = previousPlacementFail;
    }

}
}
