"""Generates the GIFs for docs/wiki/engine/update-separate-area-tile-map.md.

The flood fill below mirrors PathFindingState::updateSeparateAreaTileMap (0x004995E0) on a toy
diamond map: same scan order, same seed test (low byte only), same neighbour order, tiles are
claimed when they are queued, zone sizes counted when they are dequeued.

Usage: python area_gifs.py [output-dir]

Writes into ../images next to this script unless an output directory is given. Needs Pillow, and
the Segoe UI and Consolas fonts from C:/Windows/Fonts.
"""

import os
import sys

from PIL import Image, ImageDraw, ImageFont

OUT = sys.argv[1] if len(sys.argv) > 1 else os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'images')
os.makedirs(OUT, exist_ok=True)

FONT = ImageFont.truetype('C:/Windows/Fonts/segoeui.ttf', 15)
FONT_B = ImageFont.truetype('C:/Windows/Fonts/seguisb.ttf', 17)
FONT_S = ImageFont.truetype('C:/Windows/Fonts/segoeui.ttf', 13)
MONO = ImageFont.truetype('C:/Windows/Fonts/consola.ttf', 14)
MONO_S = ImageFont.truetype('C:/Windows/Fonts/consola.ttf', 11)
MONO_B = ImageFont.truetype('C:/Windows/Fonts/consola.ttf', 20)

BG = (250, 250, 247)
INK = (34, 34, 34)
MUTED = (110, 110, 110)
GRID = (205, 200, 185)
GRASS = (232, 226, 200)
OFFMAP = (238, 238, 234)
TERRAIN = {
    'water': (84, 136, 196),
    'rock': (128, 128, 128),
    'tree': (58, 112, 58),
    'wall': (96, 78, 62),
    'gate': (150, 96, 46),
}
AREA = [None, (120, 190, 110), (235, 190, 70), (235, 120, 125), (175, 125, 215), (110, 200, 200)]


def tint(c, f=0.45):
    return tuple(int(v + (255 - v) * f) for v in c)


# --- the toy map: a diamond of 2, 4, ... 16, 16, ... 4, 2 tiles, like the real 2 .. 400 .. 2 ---

HALF = 8
SIZE = 2 * HALF


def row_len(y):
    return 2 * (y + 1) if y < HALF else 2 * (SIZE - y)


ROWS = []  # per row: (first tile, first absolute column, length)
_t = 0
for _y in range(SIZE):
    L = row_len(_y)
    ROWS.append((_t, HALF - L // 2, L))
    _t += L
TILES = _t
TILE_XY = []
for _y, (_first, _c0, _L) in enumerate(ROWS):
    for _i in range(_L):
        TILE_XY.append((_c0 + _i, _y))
XY_TILE = {xy: t for t, xy in enumerate(TILE_XY)}

terrain = {}
for y in range(2, 14):
    terrain[(5, y)] = 'water'  # a river splits off the west bank
for xy in [(10, 3), (11, 3), (10, 4), (10, 5), (11, 5), (12, 5), (13, 5)]:
    terrain[xy] = 'rock'  # a rocky ring leaves a two-tile pocket at (11,4)-(12,4)
for xy in [(8, 2), (9, 5), (13, 8), (6, 13), (3, 7), (3, 9)]:
    terrain[xy] = 'tree'
for c in range(6, 11):  # a castle wall ring with one gatehouse
    terrain[(c, 7)] = 'wall'
    terrain[(c, 11)] = 'wall'
for r in range(8, 11):
    terrain[(6, r)] = "wall"
    terrain[(10, r)] = "wall"
terrain[(8, 11)] = "gate"
for xy in terrain:
    assert xy in XY_TILE, xy

# linkage bits and the order the fill tries them in (west, east, north row, south row)
BITS = {'N': 0x01, 'NE': 0x02, 'E': 0x04, 'SE': 0x08, 'S': 0x10, 'SW': 0x20, 'W': 0x40, 'NW': 0x80}
DELTA = {'N': (0, -1), 'NE': (1, -1), 'E': (1, 0), 'SE': (1, 1), 'S': (0, 1), 'SW': (-1, 1), 'W': (-1, 0),
         'NW': (-1, -1)}
ORDER = ['W', 'E', 'NW', 'N', 'NE', 'SW', 'S', 'SE']


def is_open(xy):
    return xy in XY_TILE and xy not in terrain  # a closed gatehouse blocks like a wall


def linkage(t):
    if not is_open(TILE_XY[t]):
        return 0
    x, y = TILE_XY[t]
    b = 0
    for d, (dx, dy) in DELTA.items():
        if is_open((x + dx, y + dy)):
            b |= BITS[d]
    return b


# the toy linkage ignores diagonal corner-cutting, so make sure the map never relies on it
for (x, y) in TILE_XY:
    for dx in (-1, 1):
        for dy in (-1, 1):
            if is_open((x, y)) and is_open((x + dx, y + dy)):
                assert is_open((x + dx, y)) or is_open((x, y + dy)), (x, y, dx, dy)

LINK = [linkage(t) for t in range(TILES)]


def neighbour(t, d):
    x, y = TILE_XY[t]
    dx, dy = DELTA[d]
    return XY_TILE.get((x + dx, y + dy))


# --- drawing helpers ---

CELL = 30
MX, MY = 20, 64
PANEL_X = MX + SIZE * CELL + 30
W, H = PANEL_X + 330, MY + SIZE * CELL + 70


def cell_box(xy, cell=CELL, ox=MX, oy=MY):
    x, y = xy
    return (ox + x * cell, oy + y * cell, ox + (x + 1) * cell - 1, oy + (y + 1) * cell - 1)


def draw_terrain(d, xy, box):
    kind = terrain.get(xy)
    if kind is None:
        return
    x0, y0, x1, y1 = box
    if kind == 'tree':
        d.rectangle(box, fill=GRASS)
        d.ellipse((x0 + 5, y0 + 5, x1 - 5, y1 - 5), fill=TERRAIN['tree'])
    elif kind == 'gate':
        d.rectangle(box, fill=TERRAIN['gate'])
        d.text(((x0 + x1) / 2, (y0 + y1) / 2), 'G', font=FONT_B, fill=(255, 255, 255), anchor='mm')
    else:
        d.rectangle(box, fill=TERRAIN[kind])


def legend(d, x, y, items):
    for label, kind in items:
        box = (x, y, x + 16, y + 16)
        if kind in TERRAIN:
            fake = (-99, -99)
            terrain[fake] = kind
            draw_terrain(d, fake, box)
            del terrain[fake]
        else:
            d.rectangle(box, fill=kind)
        d.rectangle(box, outline=GRID)
        d.text((x + 24, y + 8), label, font=FONT_S, fill=INK, anchor='lm')
        y += 22
    return y


# --- GIF 1: the whole update on the toy map ---

def flood_fill_gif():
    frames, durations = [], []
    area = [0] * TILES
    queued = set()  # claimed but not yet taken off the queue
    zone = [0] * 1000

    def frame(title, sub, cur=None, scan=None, new=(), checked=(), q=None, rd=0, wr=0, area_id=None, dur=200,
              done=None):
        im = Image.new('RGB', (W, H), BG)
        d = ImageDraw.Draw(im)
        d.text((MX, 14), title, font=FONT_B, fill=INK)
        d.text((MX, 38), sub, font=FONT, fill=MUTED)
        for yy in range(SIZE):
            for xx in range(SIZE):
                box = cell_box((xx, yy))
                t = XY_TILE.get((xx, yy))
                if t is None:
                    d.rectangle(box, fill=OFFMAP)
                    continue
                a = area[t]
                d.rectangle(box, fill=GRASS if a == 0 else (tint(AREA[a]) if t in queued else AREA[a]))
                draw_terrain(d, (xx, yy), box)
                d.rectangle(box, outline=GRID)
        for t in checked:
            x0, y0, x1, y1 = cell_box(TILE_XY[t])
            d.rectangle((x0 + 1, y0 + 1, x1 - 1, y1 - 1), outline=(200, 60, 60), width=2)
        for t in new:
            x0, y0, x1, y1 = cell_box(TILE_XY[t])
            d.rectangle((x0 + 1, y0 + 1, x1 - 1, y1 - 1), outline=(255, 255, 255), width=2)
        if cur is not None:
            d.rectangle(cell_box(TILE_XY[cur]), outline=INK, width=3)
        if scan is not None:
            x0, y0, x1, y1 = cell_box(TILE_XY[scan])
            d.rectangle((x0 - 2, y0 - 2, x1 + 2, y1 + 2), outline=(220, 40, 40), width=3)

        px, py = PANEL_X, MY
        if scan is not None:
            x, y = TILE_XY[scan]
            d.text((px, py), 'scan:  tile %3d   (row %d)' % (scan, y), font=MONO, fill=INK)
        py += 22
        d.text((px, py), 'areaID:  %s' % ('-' if area_id is None else area_id), font=MONO, fill=INK)
        py += 22
        if q is not None:
            d.text((px, py), 'queue:  read %d  write %d' % (rd, wr), font=MONO, fill=INK)
            py += 20
            pending = q[rd:wr]
            cells = 14
            for i in range(cells):
                bx = px + i * 21
                box = (bx, py, bx + 18, py + 18)
                if i < len(pending):
                    d.rectangle(box, fill=tint(AREA[area_id]), outline=GRID)
                    d.text((bx + 9, py + 9), str(pending[i]), font=MONO_S, fill=INK, anchor='mm')
                else:
                    d.rectangle(box, outline=GRID)
            if len(pending) > cells:
                d.text((px + cells * 21, py + 9), '+%d' % (len(pending) - cells), font=MONO_S, fill=MUTED,
                       anchor='lm')
            py += 30
        else:
            py += 50
        d.text((px, py), 'zoneSizesArray', font=FONT_B, fill=INK)
        py += 26
        for a in range(1, len(AREA)):
            if zone[a] == 0 and (area_id is None or a != area_id or done is not None):
                continue
            d.rectangle((px, py, px + 16, py + 16), fill=AREA[a], outline=GRID)
            d.text((px + 24, py + 8), '[%d] = %d' % (a, zone[a]), font=MONO, fill=INK, anchor='lm')
            py += 22
        if done is not None:
            py += 8
            for line in done:
                d.text((px, py), line, font=MONO, fill=INK)
                py += 20
        legend(d, px, MY + SIZE * CELL - 5 * 22 + 6,
               [('river / sea', 'water'), ('rocks', 'rock'), ('tree', 'tree'), ('wall', 'wall'),
                ('gatehouse (closed)', 'gate')])
        d.text((MX, MY + SIZE * CELL + 12),
               'pale = claimed and waiting in the queue,  solid = taken off the queue and counted',
               font=FONT_S, fill=MUTED)
        d.text((MX, MY + SIZE * CELL + 32),
               'white outline = claimed this step,  red outline = linked but already has an area',
               font=FONT_S, fill=MUTED)
        frames.append(im)
        durations.append(dur)

    frame('updateSeparateAreaTileMap on a toy map',
          'All area IDs are cleared to 0. Every gatehouse is treated as closed.', dur=2500)

    area_id = 1
    for first in range(TILES):
        xy = TILE_XY[first]
        if (area[first] & 0xFF) != 0:
            frame('1. Scan for a seed', 'tile %d already belongs to area %d: skip' % (first, area[first]),
                  scan=first, area_id=area_id, dur=45)
            continue
        if xy in terrain:
            frame('1. Scan for a seed', 'tile %d is %s: cannot start an area here' % (first, terrain[xy]),
                  scan=first, area_id=area_id, dur=350)
            continue
        queue = [first]
        rd, wr = 0, 1
        area[first] = area_id
        queued.add(first)
        frame('2. Seed found: start area %d' % area_id,
              'tile %d is open and unclaimed. Claim it and put it in the queue.' % first,
              scan=first, new=[first], q=queue, rd=rd, wr=wr, area_id=area_id, dur=1600)
        while rd != wr:
            t = queue[rd]
            zone[area_id] += 1
            queued.discard(t)
            new, checked = [], []
            for dname in ORDER:
                if not (LINK[t] & BITS[dname]):
                    continue
                n = neighbour(t, dname)
                if area[n] != 0:
                    checked.append(n)
                    continue
                area[n] = area_id
                queued.add(n)
                queue.append(n)
                wr += 1
                new.append(n)
            rd += 1
            frame('3. Flood fill area %d' % area_id,
                  'take tile %d off the queue, count it, claim its unclaimed linked neighbours' % t,
                  cur=t, scan=first, new=new, checked=checked, q=queue, rd=rd, wr=wr, area_id=area_id,
                  dur=260 if len(queue) > 12 else 600)
        frame('4. Queue empty: area %d is complete (%d tiles)' % (area_id, zone[area_id]),
              'areaID becomes %d and the scan carries on after tile %d' % (area_id + 1, first),
              scan=first, area_id=area_id, dur=1800)
        area_id += 1
        if area_id >= 1000:
            break
    total = sum(zone[1:1000])
    frame('5. Done', 'Every open tile now carries the ID of the area it belongs to.',
          area_id=area_id,
          done=['totalZones = %d' % area_id, 'sum        = %d' % total], dur=6000)
    frames[0].save(os.path.join(OUT, 'area-flood-fill.gif'), save_all=True, append_images=frames[1:],
                   duration=durations, loop=0, optimize=True)
    return area


# --- GIF 2: one tile, its eight neighbours and its linkage byte ---

def neighbour_gif():
    C = 110
    OX, OY = 40, 100
    w, h = OX + 3 * C + 40 + 380, OY + 3 * C + 60
    # the centre tile is linked everywhere except north (tree) and south-west (water)
    link = 0xFF & ~(BITS['N'] | BITS['SW'])
    claimed = {'W', 'SE'}  # already part of the area being filled
    look = {'N': 'tree', 'SW': 'water'}
    state = {}
    frames, durations = [], []

    def frame(caption, sub, active=None, dur=1200):
        im = Image.new('RGB', (w, h), BG)
        d = ImageDraw.Draw(im)
        d.text((OX, 16), caption, font=FONT_B, fill=INK)
        d.text((OX, 42), sub, font=FONT, fill=MUTED)
        for dname, (dx, dy) in list(DELTA.items()) + [('C', (0, 0))]:
            box = (OX + (dx + 1) * C, OY + (dy + 1) * C, OX + (dx + 2) * C - 1, OY + (dy + 2) * C - 1)
            x0, y0, x1, y1 = box
            fill = GRASS
            if dname == 'C' or dname in claimed or state.get(dname) == 'claimed':
                fill = AREA[2] if dname in claimed or dname == 'C' else tint(AREA[2])
            d.rectangle(box, fill=fill)
            if dname in look:
                kind = look[dname]
                if kind == 'tree':
                    d.ellipse((x0 + 25, y0 + 25, x1 - 25, y1 - 25), fill=TERRAIN['tree'])
                else:
                    d.rectangle(box, fill=TERRAIN['water'])
            d.rectangle(box, outline=GRID, width=2)
            if dname == 'C':
                d.text(((x0 + x1) / 2, (y0 + y1) / 2), 'current', font=FONT_B, fill=INK, anchor='mm')
            else:
                d.text((x0 + 8, y0 + 6), dname, font=FONT_B, fill=INK)
                d.text((x1 - 8, y0 + 8), '0x%02X' % BITS[dname], font=MONO_S, fill=MUTED, anchor='ra')
                if dname in ORDER:
                    d.text((x0 + 8, y1 - 22), '#%d' % (ORDER.index(dname) + 1), font=FONT_S, fill=MUTED)
                s = state.get(dname)
                if s:
                    color = {'claimed': (40, 120, 40), 'no link': (200, 60, 60), 'has area': (200, 60, 60)}[s]
                    cy = (y0 + y1) / 2 + 8
                    tw = d.textlength(s, font=FONT_B)
                    d.rounded_rectangle(((x0 + x1) / 2 - tw / 2 - 6, cy - 13, (x0 + x1) / 2 + tw / 2 + 6, cy + 13),
                                        radius=6, fill=(255, 255, 255), outline=color)
                    d.text(((x0 + x1) / 2, cy), s, font=FONT_B, fill=color, anchor='mm')
        if active:
            dx, dy = DELTA[active]
            d.rectangle((OX + (dx + 1) * C, OY + (dy + 1) * C, OX + (dx + 2) * C - 1, OY + (dy + 2) * C - 1),
                        outline=(220, 40, 40), width=5)
        px, py = OX + 3 * C + 40, OY
        d.text((px, py), 'PathLinkageLayer[current]', font=FONT_B, fill=INK)
        py += 30
        names = ['NW', 'W', 'SW', 'S', 'SE', 'E', 'NE', 'N']
        for i, nm in enumerate(names):
            bit = (link >> (7 - i)) & 1
            bx = px + i * 42
            on = active == nm
            d.rectangle((bx, py, bx + 36, py + 36), fill=(255, 235, 235) if on else (255, 255, 255),
                        outline=(220, 40, 40) if on else GRID, width=3 if on else 1)
            d.text((bx + 18, py + 18), str(bit), font=MONO_B, fill=INK, anchor='mm')
            d.text((bx + 18, py + 48), nm, font=FONT_S, fill=MUTED, anchor='mm')
        py += 70
        d.text((px, py), '= 0x%02X   (bit 7 ... bit 0)' % link, font=MONO, fill=INK)
        py += 40
        lines = ['for each neighbour, in order #1 .. #8:',
                 '  bit clear?        -> no link, skip',
                 '  area ID != 0?     -> already has area, skip',
                 '  otherwise         -> write area ID,',
                 '                       append to the queue']
        for line in lines:
            d.text((px, py), line, font=MONO, fill=INK)
            py += 20
        frames.append(im)
        durations.append(dur)

    frame('Expanding one tile', 'Green = the area being filled. The current tile was just taken off the queue.',
          dur=2600)
    for dname in ORDER:
        frame('Neighbour #%d: %s' % (ORDER.index(dname) + 1, dname), 'test bit 0x%02X of the linkage byte'
              % BITS[dname], active=dname, dur=1100)
        if not (link & BITS[dname]):
            state[dname] = 'no link'
            sub = 'the bit is 0: a unit cannot step %s from here' % dname
        elif dname in claimed:
            state[dname] = 'has area'
            sub = 'the bit is 1, but the tile already has an area ID'
        else:
            state[dname] = 'claimed'
            sub = 'the bit is 1 and the tile has no area yet: claim it and queue it'
        frame('Neighbour #%d: %s' % (ORDER.index(dname) + 1, dname), sub, active=dname, dur=1500)
    frame('Done with this tile', 'Four neighbours were claimed and are now waiting in the queue.', dur=3500)
    frames[0].save(os.path.join(OUT, 'area-neighbours.gif'), save_all=True, append_images=frames[1:],
                   duration=durations, loop=0, optimize=True)


# --- GIF 3: how the diamond is stored and how the scan keeps track of the row ---

def diamond_gif():
    half = 4
    size = 2 * half
    rows = []
    t = 0
    for y in range(size):
        L = 2 * (y + 1) if y < half else 2 * (size - y)
        rows.append((t, half - L // 2, L))
        t += L
    total = t
    xy = []
    for y, (f, c0, L) in enumerate(rows):
        for i in range(L):
            xy.append((c0 + i, y))
    lookup = {p: i for i, p in enumerate(xy)}
    C = 46
    OX, OY = 30, 90
    w, h = OX + size * C + 40 + 400, OY + size * C + 40
    frames, durations = [], []

    def frame(title, sub, scan=None, focus=None, panel=(), dur=500):
        im = Image.new('RGB', (w, h), BG)
        d = ImageDraw.Draw(im)
        d.text((OX, 16), title, font=FONT_B, fill=INK)
        d.text((OX, 44), sub, font=FONT, fill=MUTED)
        nb = {}
        if focus is not None:
            fx, fy = xy[focus]
            for dname, (dx, dy) in DELTA.items():
                n = lookup.get((fx + dx, fy + dy))
                if n is not None:
                    nb[n] = dname
        for y in range(size):
            row_first = rows[y][0]
            d.text((OX - 8, OY + y * C + C / 2), str(y), font=FONT_S, fill=MUTED, anchor='rm')
            for x in range(size):
                box = (OX + x * C, OY + y * C, OX + (x + 1) * C - 1, OY + (y + 1) * C - 1)
                i = lookup.get((x, y))
                if i is None:
                    d.rectangle(box, fill=OFFMAP)
                    continue
                fill = GRASS
                if scan is not None and i < scan:
                    fill = tint(AREA[2], 0.55)
                if scan is not None and rows[xy[scan][1]][0] <= i < rows[xy[scan][1]][0] + rows[xy[scan][1]][2]:
                    fill = tint(AREA[2], 0.25) if i != scan else fill
                if i in nb:
                    fill = tint(AREA[3], 0.3)
                if i == focus:
                    fill = AREA[3]
                d.rectangle(box, fill=fill, outline=GRID)
                d.text(((box[0] + box[2]) / 2, (box[1] + box[3]) / 2 - (7 if i in nb else 0)), str(i), font=MONO,
                       fill=INK, anchor='mm')
                if i in nb:
                    d.text(((box[0] + box[2]) / 2, box[3] - 9), nb[i], font=MONO_S, fill=MUTED, anchor='mm')
                if i == row_first:
                    d.line((box[0], box[1] + 3, box[0], box[3] - 3), fill=(40, 40, 40), width=3)
        if scan is not None:
            x, y = xy[scan]
            d.rectangle((OX + x * C - 2, OY + y * C - 2, OX + (x + 1) * C + 1, OY + (y + 1) * C + 1),
                        outline=(220, 40, 40), width=3)
        px, py = OX + size * C + 40, OY
        for line in panel:
            d.text((px, py), line, font=MONO, fill=INK)
            py += 21
        frames.append(im)
        durations.append(dur)

    frame('How the map is stored', 'A diamond of rows 2, 4, 6, 8, 8, 6, 4, 2 tiles long, numbered row by row '
          '(the real map: 2 .. 400 .. 2).',
          panel=['tile numbers run left to right,', 'row after row, with no gaps:', '',
                 '%d tiles in this toy' % total, '80400 tiles in the game', '',
                 'the thick bar marks the first', 'tile of each row'], dur=4000)
    row = 0
    for i in range(total):
        if row + 1 < size and i >= rows[row + 1][0]:
            row += 1
        nxt = rows[row + 1][0] if row + 1 < size else total
        frame('The scan walks the tiles in number order',
              'It only needs to notice when it crosses into the next row.', scan=i,
              panel=['_first = %d' % i, '_row   = %d' % row, '',
                     'next row starts at tile %d' % nxt, '(translationMatrix[%d]' % (row + 1),
                     '   .firstTileOfRow)', '',
                     'when _first reaches it:', '  _row += 1'], dur=320)
    for focus in (lookup[(2, 2)], lookup[(3, 5)]):
        fx, fy = xy[focus]
        up = lookup[(fx, fy - 1)] - focus
        dn = lookup[(fx, fy + 1)] - focus
        L = rows[fy][2]
        frame('Finding the eight neighbours of tile %d (row %d, %d tiles long)' % (focus, fy, L),
              'West and east are -1 and +1. Above and below depend on the row lengths.', focus=focus,
              panel=['W   = tile - 1', 'E   = tile + 1', '',
                     'above = tile %+d' % up, 'below = tile %+d' % dn, '',
                     'NW, N, NE = above -1, 0, +1', 'SW, S, SE = below -1, 0, +1', '',
                     'the game keeps the row offsets in', 'directionTranslationMatrix[row]',
                     '  [row][0] = %+d   (above)' % up, '  [row][4] = %+d   (below)' % dn], dur=6000)
    frames[0].save(os.path.join(OUT, 'area-diamond-layout.gif'), save_all=True, append_images=frames[1:],
                   duration=durations, loop=0, optimize=True)


if __name__ == '__main__':
    final = flood_fill_gif()
    neighbour_gif()
    diamond_gif()
    sizes = {}
    for t in range(TILES):
        sizes[final[t]] = sizes.get(final[t], 0) + 1
    print('areas:', sorted(sizes.items()))
    for f in sorted(os.listdir(OUT)):
        print(f, os.path.getsize(os.path.join(OUT, f)))
