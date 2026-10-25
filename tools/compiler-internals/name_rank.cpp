// Which order does c2 iterate a set of asm-written locals in? One __asm block that writes every
// candidate name; `slot_probe.py name_rank.cpp --invocation 1` then prints the def-set in the
// order AddStackElement receives it, which is the hash order that breaks equal-weight slot ties
// (see msvc-backend.md, "The slot tiebreak, decoded"). Add names, rerun, read the order. It is
// only a ranking of the names present against each other: two names in one bucket keep their
// declaration order, so a new name is confirmed with a probe on the real function.
int nameRank(int p)
{
    int _budget; int _result; unsigned _ppIndex; int _direction; int _dirn; int _dir; int _heading;
    int _moveDir; int _dirIndex; int _step; int _facing; int _course; int _octant; int _way; int _turn;
    int _tile; int _cY; int _cX; int _tileIndex; int _curTile; int _cTile; int _tileNo; int _tilePos;
    int _distance; int _dist; int _radius; int _walk; int _first; int _row; int _rowEnd; int _readIndex;
    int _areaID; int _cLink; int _link; int _links; int _best; int _found; int _count; int _n;
    _budget = p; _result = p; _ppIndex = p; _direction = p; _dirn = p; _dir = p; _heading = p;
    _moveDir = p; _dirIndex = p; _step = p; _facing = p; _course = p; _octant = p; _way = p; _turn = p;
    _tile = p; _cY = p; _cX = p; _tileIndex = p; _curTile = p; _cTile = p; _tileNo = p; _tilePos = p;
    _distance = p; _dist = p; _radius = p; _walk = p; _first = p; _row = p; _rowEnd = p; _readIndex = p;
    _areaID = p; _cLink = p; _link = p; _links = p; _best = p; _found = p; _count = p; _n = p;
    __asm {
        mov dword ptr _budget, 1
        mov dword ptr _result, 1
        mov dword ptr _ppIndex, 1
        mov dword ptr _direction, 1
        mov dword ptr _dirn, 1
        mov dword ptr _dir, 1
        mov dword ptr _heading, 1
        mov dword ptr _moveDir, 1
        mov dword ptr _dirIndex, 1
        mov dword ptr _step, 1
        mov dword ptr _facing, 1
        mov dword ptr _course, 1
        mov dword ptr _octant, 1
        mov dword ptr _way, 1
        mov dword ptr _turn, 1
        mov dword ptr _tile, 1
        mov dword ptr _cY, 1
        mov dword ptr _cX, 1
        mov dword ptr _tileIndex, 1
        mov dword ptr _curTile, 1
        mov dword ptr _cTile, 1
        mov dword ptr _tileNo, 1
        mov dword ptr _tilePos, 1
        mov dword ptr _distance, 1
        mov dword ptr _dist, 1
        mov dword ptr _radius, 1
        mov dword ptr _walk, 1
        mov dword ptr _first, 1
        mov dword ptr _row, 1
        mov dword ptr _rowEnd, 1
        mov dword ptr _readIndex, 1
        mov dword ptr _areaID, 1
        mov dword ptr _cLink, 1
        mov dword ptr _link, 1
        mov dword ptr _links, 1
        mov dword ptr _best, 1
        mov dword ptr _found, 1
        mov dword ptr _count, 1
        mov dword ptr _n, 1
    }
    return _budget + _result + _ppIndex + _direction + _dirn + _dir + _heading + _moveDir + _dirIndex + _step
        + _facing + _course + _octant + _way + _turn + _tile + _cY + _cX + _tileIndex + _curTile + _cTile
        + _tileNo + _tilePos + _distance + _dist + _radius + _walk + _first + _row + _rowEnd + _readIndex
        + _areaID + _cLink + _link + _links + _best + _found + _count + _n;
}
