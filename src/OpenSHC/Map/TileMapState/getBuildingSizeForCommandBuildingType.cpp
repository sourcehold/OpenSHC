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
    // FUNCTION: STRONGHOLDCRUSADER 0x004FA550
    int TileMapState::getBuildingSizeForCommandBuildingType(MappersEnum commandBuildingType)
    {
        /*
          The original dispatches through a byte index table at 0x004FA614 (0x147 entries, biased by
          M_MAPPER_UNDUGMOAT) into a jump table at 0x004FA5DC, which is what MSVC emits for a dense
          switch; Ghidra could not normalise it and rendered the dispatch as a read through an
          unnamed pointer array. The case groups below are that byte table, decoded.

          field159_0x5549b8 is written through the global instance, not through this, which is how
          the original addresses it.
        */
        switch (commandBuildingType) {
        case OpenSHC::Commands::M_MAPPER_FLETCHER:
        case OpenSHC::Commands::M_MAPPER_HOVEL:
        case OpenSHC::Commands::M_MAPPER_BAKER:
        case OpenSHC::Commands::M_MAPPER_BREWER:
        case OpenSHC::Commands::M_MAPPER_GRANARY:
        case OpenSHC::Commands::M_MAPPER_ARMOURY:
        case OpenSHC::Commands::M_MAPPER_POLETURNER:
        case OpenSHC::Commands::M_MAPPER_BLACKSMITH:
        case OpenSHC::Commands::M_MAPPER_ARMOURER:
        case OpenSHC::Commands::M_MAPPER_TANNER:
        case OpenSHC::Commands::M_MAPPER_IRON_MINE:
        case OpenSHC::Commands::M_MAPPER_PITCH_WORKINGS:
        case OpenSHC::Commands::M_MAPPER_TOWER2:
        case OpenSHC::Commands::M_MAPPER_GARDEN10:
        case OpenSHC::Commands::M_MAPPER_GARDEN11:
        case OpenSHC::Commands::M_MAPPER_GARDEN12:
        case OpenSHC::Commands::M_MAPPER_OIL_SMELTER:
        case (MappersEnum)258:
        case (MappersEnum)259:
        case (MappersEnum)260:
        case OpenSHC::Commands::M_MAPPER_WATERPOT:
            return 4;
        case OpenSHC::Commands::M_MAPPER_STORES:
        case OpenSHC::Commands::M_MAPPER_TRADEPOST:
        case OpenSHC::Commands::M_MAPPER_BARRACKS_EURO:
        case OpenSHC::Commands::M_MAPPER_BARRACKS_ARAB:
        case OpenSHC::Commands::M_MAPPER_ENGINEERS_GUILD:
        case OpenSHC::Commands::M_MAPPER_TUNNELERS_GUILD:
        case OpenSHC::Commands::M_MAPPER_INN:
        case OpenSHC::Commands::M_MAPPER_GATE_INNER:
        case OpenSHC::Commands::M_MAPPER_DRAWBRIDGE:
        case OpenSHC::Commands::M_MAPPER_TOWER3:
        case OpenSHC::Commands::M_MAPPER_GATE_STONE1A:
        case OpenSHC::Commands::M_MAPPER_GATE_STONE1B:
        case OpenSHC::Commands::M_MAPPER_OUTPOST_EURO:
        case OpenSHC::Commands::M_MAPPER_OUTPOST_ARAB:
        case OpenSHC::Commands::M_MAPPER_CESS_PIT1:
        case OpenSHC::Commands::M_MAPPER_CESS_PIT2:
        case OpenSHC::Commands::M_MAPPER_CESS_PIT3:
        case OpenSHC::Commands::M_MAPPER_CESS_PIT4:
        case OpenSHC::Commands::M_MAPPER_DUNGEON:
        case OpenSHC::Commands::M_MAPPER_DUNKING_STOOL:
        case OpenSHC::Commands::M_MAPPER_DANCING_BEAR:
        case OpenSHC::Commands::M_MAPPER_POND1:
        case OpenSHC::Commands::M_MAPPER_POND2_SMALL:
            return 5;
        case OpenSHC::Commands::M_MAPPER_QUARRY:
        case OpenSHC::Commands::M_MAPPER_STABLES:
        case OpenSHC::Commands::M_MAPPER_HEALER:
        case OpenSHC::Commands::M_MAPPER_CHURCH1:
        case OpenSHC::Commands::M_MAPPER_TOWER4:
        case OpenSHC::Commands::M_MAPPER_TOWER5:
        case OpenSHC::Commands::M_MAPPER_POND3_LARGE1:
        case OpenSHC::Commands::M_MAPPER_POND4_LARGE2:
            return 6;
        case OpenSHC::Commands::M_MAPPER_WOODSMAN:
        case OpenSHC::Commands::M_MAPPER_TUNNEL:
        case OpenSHC::Commands::M_MAPPER_TUNNEL_CONSTRUCTION:
        case OpenSHC::Commands::M_MAPPER_MILL:
        case OpenSHC::Commands::M_MAPPER_HUNTER:
        case OpenSHC::Commands::M_MAPPER_TOWER1:
        case OpenSHC::Commands::M_MAPPER_GATE_WOOD1A:
        case OpenSHC::Commands::M_MAPPER_GATE_WOOD1B:
        case OpenSHC::Commands::M_MAPPER_GATE_WOOD1C:
        case OpenSHC::Commands::M_MAPPER_GATE_WOOD1D:
        case OpenSHC::Commands::M_MAPPER_GARDEN7:
        case OpenSHC::Commands::M_MAPPER_GARDEN8:
        case OpenSHC::Commands::M_MAPPER_GARDEN9:
        case OpenSHC::Commands::M_MAPPER_MAYPOLE:
        case OpenSHC::Commands::M_MAPPER_STOCKS:
        case OpenSHC::Commands::M_MAPPER_CATAPULT:
        case OpenSHC::Commands::M_MAPPER_TREBUCHET:
        case OpenSHC::Commands::M_MAPPER_SIEGE_TOWER:
        case OpenSHC::Commands::M_MAPPER_BATTERING_RAM:
        case OpenSHC::Commands::M_MAPPER_PORTABLE_SHIELD:
        case OpenSHC::Commands::M_MAPPER_BURNING_STAKE:
        case OpenSHC::Commands::M_MAPPER_RACK_STRETCHING:
        case OpenSHC::Commands::M_MAPPER_CHOPPING_BLOCK:
        case OpenSHC::Commands::M_MAPPER_DOG_CAGE:
        case OpenSHC::Commands::M_MAPPER_WELL:
        case OpenSHC::Commands::M_MAPPER_ARAB_BALLISTA:
            return 3;
        case OpenSHC::Commands::M_MAPPER_KEEP1:
        case OpenSHC::Commands::M_MAPPER_KEEP2:
        case OpenSHC::Commands::M_MAPPER_GATE_MAIN:
        case OpenSHC::Commands::M_MAPPER_GATE_STONE2A:
        case OpenSHC::Commands::M_MAPPER_GATE_STONE2B:
            return 7;
        case OpenSHC::Commands::M_MAPPER_CAMP_FIRE:
        case OpenSHC::Commands::M_MAPPER_KILLING_PIT:
        case OpenSHC::Commands::M_MAPPER_PITCH_DITCH:
        case (MappersEnum)248:
        case (MappersEnum)249:
        case (MappersEnum)250:
        case (MappersEnum)251:
        case OpenSHC::Commands::M_MAPPER_SHRINE5:
            return 1;
        case OpenSHC::Commands::M_MAPPER_KEEP3:
        case OpenSHC::Commands::M_MAPPER_APPLEFARM:
            return 0xb;
        case OpenSHC::Commands::M_MAPPER_WHEATFARM:
        case OpenSHC::Commands::M_MAPPER_HOPSFARM:
        case OpenSHC::Commands::M_MAPPER_CHURCH2:
            return 9;
        case OpenSHC::Commands::M_MAPPER_CHURCH3:
            return 0xd;
        case OpenSHC::Commands::M_MAPPER_CATTLEFARM:
            return 0xa;
        case OpenSHC::Commands::M_MAPPER_UNDUGMOAT:
        case OpenSHC::Commands::M_MAPPER_DUGMOAT:
        case OpenSHC::Commands::M_MAPPER_MOAT:
        case OpenSHC::Commands::M_MAPPER_ANTIMOAT:
            DAT_TileMapState::instance.field159_0x5549b8 = 1;
            return 2;
        case OpenSHC::Commands::M_MAPPER_OXENBASE:
        case OpenSHC::Commands::M_MAPPER_SIGNPOST:
        case OpenSHC::Commands::M_MAPPER_GATE_POSTERN:
        case OpenSHC::Commands::M_MAPPER_GARDEN1:
        case OpenSHC::Commands::M_MAPPER_GARDEN2:
        case OpenSHC::Commands::M_MAPPER_GARDEN3:
        case OpenSHC::Commands::M_MAPPER_GARDEN4:
        case OpenSHC::Commands::M_MAPPER_GARDEN5:
        case OpenSHC::Commands::M_MAPPER_GARDEN6:
        case OpenSHC::Commands::M_MAPPER_GALLOWS:
        case (MappersEnum)252:
        case (MappersEnum)253:
        case (MappersEnum)254:
        case (MappersEnum)255:
        case (MappersEnum)256:
        case (MappersEnum)257:
        case OpenSHC::Commands::M_MAPPER_GIBBET:
        case OpenSHC::Commands::M_MAPPER_STATUE1:
        case OpenSHC::Commands::M_MAPPER_STATUE2:
        case OpenSHC::Commands::M_MAPPER_STATUE3:
        case OpenSHC::Commands::M_MAPPER_STATUE4:
        case OpenSHC::Commands::M_MAPPER_STATUE5:
        case OpenSHC::Commands::M_MAPPER_SHRINE1:
        case OpenSHC::Commands::M_MAPPER_SHRINE2:
        case OpenSHC::Commands::M_MAPPER_SHRINE3:
        case OpenSHC::Commands::M_MAPPER_SHRINE4:
            return 2;
        case OpenSHC::Commands::M_MAPPER_FLAG_TYPE0:
        case OpenSHC::Commands::M_MAPPER_FLAG_TYPE1:
        case OpenSHC::Commands::M_MAPPER_FLAG_TYPE2:
        case OpenSHC::Commands::M_MAPPER_FLAG_TYPE3:
        case OpenSHC::Commands::M_MAPPER_HEADS:
        case OpenSHC::Commands::M_MAPPER_BRAZIER:
        case OpenSHC::Commands::M_MAPPER_MANGONEL:
        case OpenSHC::Commands::M_MAPPER_BALLISTA:
        case OpenSHC::Commands::M_MAPPER_PEOPLE_ARCHERS:
        case OpenSHC::Commands::M_MAPPER_PEOPLE_SPEARMEN:
        case OpenSHC::Commands::M_MAPPER_PEOPLE_PIKEMEN:
        case OpenSHC::Commands::M_MAPPER_PEOPLE_MACEMEN:
        case OpenSHC::Commands::M_MAPPER_PEOPLE_XBOWMEN:
        case OpenSHC::Commands::M_MAPPER_PEOPLE_SWORDSMEN:
        case OpenSHC::Commands::M_MAPPER_PEOPLE_KNIGHTS:
        case OpenSHC::Commands::M_MAPPER_PEOPLE_LADDERMEN:
        case OpenSHC::Commands::M_MAPPER_PEOPLE_ENGINEERS:
        case OpenSHC::Commands::M_MAPPER_PEOPLE_ENGINEERS_POTS:
        case OpenSHC::Commands::M_MAPPER_PEOPLE_MONKS:
        case OpenSHC::Commands::M_MAPPER_PEOPLE_CATAPULTS:
        case OpenSHC::Commands::M_MAPPER_PEOPLE_TREBUCHETS:
        case OpenSHC::Commands::M_MAPPER_PEOPLE_BATTERING_RAMS:
        case OpenSHC::Commands::M_MAPPER_PEOPLE_SIEGE_TOWERS:
        case OpenSHC::Commands::M_MAPPER_PEOPLE_PORTABLE_SHIELDS:
        case OpenSHC::Commands::M_MAPPER_PEOPLE_TUNNELERS:
        case OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINT1:
        case OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINT2:
        case OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINT3:
        case OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINT4:
        case OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINT5:
        case OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINT6:
        case OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINT7:
        case OpenSHC::Commands::M_MAPPER_PEOPLE_ARAB_BOW:
        case OpenSHC::Commands::M_MAPPER_PEOPLE_ARAB_SLAVE:
        case OpenSHC::Commands::M_MAPPER_PEOPLE_ARAB_SLINGER:
        case OpenSHC::Commands::M_MAPPER_PEOPLE_ARAB_ASSASIN:
        case OpenSHC::Commands::M_MAPPER_PEOPLE_ARAB_HORSEMAN:
        case OpenSHC::Commands::M_MAPPER_PEOPLE_ARAB_SWORDSMAN:
        case OpenSHC::Commands::M_MAPPER_PEOPLE_ARAB_GRENADIER:
        case OpenSHC::Commands::M_MAPPER_PEOPLE_ARAB_BALLISTA:
        case OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM1:
        case OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM2:
        case OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM3:
        case OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM4:
        case OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM5:
        case OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM6:
        case OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM7:
        case OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINTE1:
        case OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINTE2:
        case OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINTT1:
        case OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINTK1:
            return 0;
        }
        return -1;
    }

}
}
