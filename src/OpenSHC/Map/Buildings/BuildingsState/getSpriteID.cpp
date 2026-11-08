#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Commands::MappersEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00409F50
        int BuildingsState::getSpriteID(MappersEnum commandBuildingType)
        {
            if (commandBuildingType >= OpenSHC::Commands::M_MAPPER_GARDEN1
                && commandBuildingType <= OpenSHC::Commands::M_MAPPER_GARDEN12) {
                return DAT_BuildingDefinedData::instance
                           .GardenVariations[commandBuildingType - OpenSHC::Commands::M_MAPPER_GARDEN1]
                    + DAT_BuildingDefinedData::instance.Building_Sprite_ID_Array_1[BT_GARDEN];
            }
            if (commandBuildingType >= OpenSHC::Commands::M_MAPPER_CESS_PIT1
                && commandBuildingType <= OpenSHC::Commands::M_MAPPER_CESS_PIT4) {
                return DAT_BuildingDefinedData::instance
                           .CesspitVariations[commandBuildingType - OpenSHC::Commands::M_MAPPER_CESS_PIT1]
                    + DAT_BuildingDefinedData::instance.Building_Sprite_ID_Array_1[BT_CESSPIT];
            }
            if (commandBuildingType >= OpenSHC::Commands::M_MAPPER_STATUE1
                && commandBuildingType <= OpenSHC::Commands::M_MAPPER_STATUE5) {
                return DAT_BuildingDefinedData::instance
                           .StatueVariations[commandBuildingType - OpenSHC::Commands::M_MAPPER_STATUE1]
                    + DAT_BuildingDefinedData::instance.Building_Sprite_ID_Array_1[BT_STATUE];
            }
            if (commandBuildingType >= OpenSHC::Commands::M_MAPPER_SHRINE1
                && commandBuildingType <= OpenSHC::Commands::M_MAPPER_SHRINE5) {
                return DAT_BuildingDefinedData::instance
                           .ShrineVariations[commandBuildingType - OpenSHC::Commands::M_MAPPER_SHRINE1]
                    + DAT_BuildingDefinedData::instance.Building_Sprite_ID_Array_1[BT_SHRINE];
            }
            if (commandBuildingType >= OpenSHC::Commands::M_MAPPER_POND1
                && commandBuildingType <= OpenSHC::Commands::M_MAPPER_POND4_LARGE2) {
                return DAT_BuildingDefinedData::instance
                           .PondVariations[commandBuildingType - OpenSHC::Commands::M_MAPPER_POND1]
                    + DAT_BuildingDefinedData::instance.Building_Sprite_ID_Array_1[BT_POND];
            }
            return DAT_BuildingDefinedData::instance.Building_Sprite_ID_Array_1[MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType, this)(
                commandBuildingType)];
        }

    }
}
}
