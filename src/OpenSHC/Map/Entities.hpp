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

        void __stdcall UpdateArrowEntity();

        void __stdcall UpdateCatapultProjectileEntity();

        void __stdcall UpdatePebbleEntity();

        void __stdcall UpdateFirethrowSecondaryEntity();

        void __stdcall UpdateArrowsSecondaryEntity();

        void __stdcall UpdateCrossbowArrowEntity();

        void __stdcall UpdateEntity_20_37();

        void __stdcall UpdateEntity_21();

        void __stdcall UpdateEntity_PoisonCloud();

        void __stdcall UpdateEntity_CowFlying();

        void __stdcall UpdateEntity_26();

        void __stdcall UpdateEntity_27();

        void __stdcall UpdateEntity_28();

        uint __stdcall UpdateEntity_29();

        void __stdcall UpdateEntity_30();

        void __stdcall UpdateEntity_31();

        void __stdcall UpdateEntity_32();

        void __stdcall UpdateEntity_40();

        void __stdcall UpdateEntity_41();

        void __stdcall UpdateEntity_42_43();

        void __stdcall UpdateFlag_1_2_4_Entity();

        void __stdcall UpdateFlag3Entity();

        void __stdcall UpdateBrazierEntity();

        uint __cdecl SomeFireSpreadFunction(int param_1, int x, int y, int param_4, int param_5);

        uint __cdecl IgniteFireAtMiniTile(
            int playerID, int miniTileX, int miniTileY, int tileHeightMin8, int two, int fireIntensity);

        void __cdecl AFireSpreadFunction(int playerID, int x, int y, int height, int param_5, int param_6);

        void __cdecl UpdateFireEntity();

        void __stdcall UpdateFirethrowEntity();

        void __stdcall UpdateHeadsOnSpikesEntity();

        void __stdcall UpdateEntityType8();

        uint __cdecl IgniteFireAtMiniTile_Convenience(
            int playerID, int miniTileX, int miniTileY, int tileHeightMin8, int two);

        void __cdecl SetPlaceOnFire(int playerID, int x, int y, int height, int param_5);

    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
