/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Entities.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Entities {

        void __cdecl UpdateArrowEntity();

        void __cdecl UpdateCatapultProjectileEntity();

        void __cdecl UpdatePebbleEntity();

        void __cdecl UpdateFirethrowSecondaryEntity();

        void __cdecl UpdateArrowsSecondaryEntity();

        void __cdecl UpdateCrossbowArrowEntity();

        void __cdecl UpdateEntity_20_37();

        void __cdecl UpdateEntity_21();

        void __cdecl UpdateEntity_PoisonCloud();

        void __cdecl UpdateEntity_CowFlying();

        void __cdecl UpdateEntity_26();

        void __cdecl UpdateEntity_27();

        void __cdecl UpdateEntity_28();

        uint __cdecl UpdateEntity_29();

        void __cdecl UpdateEntity_30();

        void __cdecl UpdateEntity_31();

        void __cdecl UpdateEntity_32();

        void __cdecl UpdateEntity_40();

        void __cdecl UpdateEntity_41();

        void __cdecl UpdateEntity_42_43();

        void __cdecl UpdateFlag_1_2_4_Entity();

        void __cdecl UpdateFlag3Entity();

        void __cdecl UpdateBrazierEntity();

        uint __cdecl SomeFireSpreadFunction(int param_1, int x, int y, int param_4, int param_5);

        uint __cdecl IgniteFireAtMiniTile(
            int playerID, int miniTileX, int miniTileY, int tileHeightMin8, int two, int fireIntensity);

        void __cdecl AFireSpreadFunction(int playerID, int x, int y, int height, int param_5, int param_6);

        void __cdecl UpdateFireEntity();

        void __cdecl UpdateFirethrowEntity();

        void __cdecl UpdateHeadsOnSpikesEntity();

        void __cdecl UpdateEntityType8();

        uint __cdecl IgniteFireAtMiniTile_Convenience(
            int playerID, int miniTileX, int miniTileY, int tileHeightMin8, int two);

        void __cdecl SetPlaceOnFire(int playerID, int x, int y, int height, int param_5);

    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
