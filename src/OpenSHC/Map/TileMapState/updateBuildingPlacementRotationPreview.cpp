#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00504EE0
    void TileMapState::updateBuildingPlacementRotationPreview(int param_1, int param_2)
    {
        BOOLEnum _previous = this->buildingPlacementFail;
        this->buildingPlacementFail = FALSE;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::determineBuildingPlacementRotation, this)(param_1, param_2);
        this->buildingPlacementFail = _previous;
    }

}
}
