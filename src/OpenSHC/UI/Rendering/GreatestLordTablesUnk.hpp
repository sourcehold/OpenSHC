#pragma once

namespace OpenSHC {
namespace UI {
    namespace Rendering {

#pragma pack(push, 1)
        // The tables behind the Greatest Lord screen (RenderGreatestLordScreen's locals), one entry per player slot
        // (index 0 unused). The original keeps them in one block of the stack frame, and its statistic orders are
        // filled by one strided loop, so they are one struct rather than separate arrays.
        // SIZE: 0x000002F4
        struct GreatestLordTablesUnk {

            int points[9]; // 0x00000000 length: 36
            int stars[9]; // 0x00000024 length: 36
            int overallOrder[9]; // 0x00000048 length: 36
            int kills[9]; // 0x0000006C length: 36
            int losses[9]; // 0x00000090 length: 36
            // Player order per statistic, best first: 0 kills, 1 buildings burned, 2 food, 3 gold, 4 max population,
            // 5 wood, 6 stone, 7 iron, 8 pitch, 9 unused, 10 losses, 11 weapons, 12 buildings lost, 13 troops,
            // 14 goods received, 15 goods sent.
            int statOrder[16][9]; // 0x000000B4 length: 576
        };
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(GreatestLordTablesUnk) == 0x2F4, GreatestLordTablesUnk);
    } // namespace Rendering
} // namespace UI
} // namespace OpenSHC
