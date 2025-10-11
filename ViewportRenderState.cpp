#include "ViewportRenderState.h"

//FUNCTION: STRONGHOLDCRUSADER 0x00401000
BOOL ViewportRenderState::xyAreValid(uint x, uint y)
{
  if (((x <= MAP_XY_LIMIT_INCLUSIVE) && (y <= MAP_XY_LIMIT_INCLUSIVE)) &&
    (this->DAT_BinaryTileMap400x400[y * MAP_XY_LIMIT + x] != '\0'))
  {
    return 1;
  }
  return 0;
}