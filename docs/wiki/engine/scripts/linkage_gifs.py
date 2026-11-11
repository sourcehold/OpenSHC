"""Generates the GIFs for docs/wiki/engine/path-linkage-layer.md.

compute_linkage() mirrors PathFindingState::updatePathLinkageLayerBasedOnBuildingsUnk (0x004999C0),
transcribed from the original's disassembly: same tile modes, same neighbour tests in the same
order, same diagonal (corner) rules. The toy maps are square grids with made-up heights.

Usage: python linkage_gifs.py [output-dir]

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
MONO_S = ImageFont.truetype('C:/Windows/Fonts/consola.ttf', 12)
MONO_B = ImageFont.truetype('C:/Windows/Fonts/consola.ttf', 20)

BG = (250, 250, 247)
INK = (34, 34, 34)
MUTED = (110, 110, 110)
GRID = (205, 200, 185)
RED = (205, 55, 55)
GREEN = (40, 130, 60)
ARROW = (40, 90, 170)
HILITE = (255, 214, 102)

# LogicLayer flags (Logic1.hpp)
L_SEA = 0x1
L_STOCKPILE = 0x2
L_BORDER = 0x10
L_BORDER_EDGE = 0x20
L_WALL_OR_GATEHOUSE = 0x100
L_BUILDING = 0x400
L_STAIRS = 0x800
L_TREE = 0x1000
L_FORD = 0x200000
L_CRENEL_VARIATION = 0x400000
L_CLIMBABLE = 0x800000
L_KEEP = 0x10000000
IMPASSABLE = 0x4A5014B1

# direction index -> (name, bit, dx, dy); the order of directionTranslationMatrix[y][0..7]
DIRS = [('N', 0x01, 0, -1), ('NE', 0x02, 1, -1), ('E', 0x04, 1, 0), ('SE', 0x08, 1, 1),
        ('S', 0x10, 0, 1), ('SW', 0x20, -1, 1), ('W', 0x40, -1, 0), ('NW', 0x80, -1, -1)]


class Map:
    def __init__(self, w, h, ground=8):
        self.w, self.h = w, h
        self.logic = {}
        self.height = {}
        self.kind = {}
        for y in range(h):
            for x in range(w):
                self.set((x, y), 'ground', 0, ground)
        self.link = {}

    def set(self, xy, kind, logic, height):
        self.kind[xy] = kind
        self.logic[xy] = logic
        self.height[xy] = height

    def tiles(self):
        return [(x, y) for y in range(self.h) for x in range(self.w)]


def compute_linkage(m, t, trace=None):
    """One tile's linkage byte. No buildings, keeps or damage in the toy maps, so those inputs are 0."""
    L = m.logic[t]
    h = m.height[t]
    low, high = h - 16, h + 16
    keep_m = wall_m = stairs_m = ground_m = 0
    special = 0
    if L & L_CLIMBABLE:
        mode = 'ladder'
    elif L & L_KEEP:
        keep_m, special, mode = 1, 1, 'keep'
    elif L & (L_STOCKPILE | L_FORD):
        ground_m, mode = 1, 'ground'
    elif L & L_STAIRS:
        stairs_m, mode = 1, 'stairs'
    elif L & L_CRENEL_VARIATION:
        return 0, 0, 'blocked'
    elif L & L_WALL_OR_GATEHOUSE:
        wall_m, mode = 1, 'wall'
    elif L & IMPASSABLE:
        return 0, 0, 'blocked'
    else:
        ground_m, mode = 1, 'ground'
    link = 0
    blockers = 0
    nlogic = []
    for name, bit, dx, dy in DIRS:
        n = (t[0] + dx, t[1] + dy)
        Ln = m.logic.get(n, L_BORDER)  # beyond the toy map's edge: border tiles
        nlogic.append(Ln)
        why = None
        if Ln & L_FORD:
            pass
        elif Ln & L_STAIRS:
            if special == 1:
                why = 'keep -> stairs'
        elif Ln & L_STOCKPILE:
            if keep_m:
                why = 'keep -> stockpile'
        elif Ln & L_BUILDING:
            why = 'building'
        elif Ln & L_KEEP:
            blockers |= bit
        elif Ln & L_CRENEL_VARIATION:
            blockers |= bit
            why = 'crenel'
        elif Ln & L_WALL_OR_GATEHOUSE:
            blockers |= bit
        elif Ln & (L_BORDER | L_BORDER_EDGE):
            blockers |= bit
            why = 'map edge'
        elif Ln & IMPASSABLE:
            why = m.kind.get(n, 'impassable')
        if why is None:
            if Ln & L_KEEP:
                ok = keep_m or wall_m
                why = None if ok else 'keep'
            elif (Ln & L_WALL_OR_GATEHOUSE) and special:
                pass
            else:
                hn = m.height[n]
                if hn < low or hn > high:
                    why = 'height %d vs %d' % (hn, h)
        if why is None:
            link |= bit
        if trace is not None:
            trace.append((name, bit, n, why))
    raw = link
    if ground_m:
        if not link & 0x01 and blockers & 0x01:
            if not link & 0x04 and blockers & 0x04:
                link &= ~0x02
            if not link & 0x40 and blockers & 0x40:
                link &= ~0x80
        if not link & 0x10 and blockers & 0x10:
            if not link & 0x04 and blockers & 0x04:
                link &= ~0x08
            if not link & 0x40 and blockers & 0x40:
                link &= ~0x20
    else:
        WK = L_KEEP | L_WALL_OR_GATEHOUSE
        for a, c, d, clear in ((0, 1, 2, 0x02), (0, 7, 6, 0x80), (4, 3, 2, 0x08), (4, 5, 6, 0x20)):
            if (nlogic[a] & WK and nlogic[d] & WK and not nlogic[c] & WK and not nlogic[c] & L_STOCKPILE
                    and not nlogic[a] & L_STAIRS and not nlogic[d] & L_STAIRS):
                link &= ~clear
    return link, raw ^ link, mode


def rebuild(m):
    m.link = {t: compute_linkage(m, t)[0] for t in m.tiles()}


# --- drawing ---

KIND_FILL = {
    'ground': (232, 226, 200),
    'wall': (120, 104, 88),
    'stairs': (176, 150, 120),
    'water': (84, 136, 196),
    'tree': (232, 226, 200),
    'rock': (128, 128, 128),
}


def tile_box(xy, cell, ox, oy):
    x, y = xy
    return (ox + x * cell, oy + y * cell, ox + (x + 1) * cell - 1, oy + (y + 1) * cell - 1)


def draw_map(d, m, cell, ox, oy, show_height=True, links=None, hi=(), dim_links=False):
    for t in m.tiles():
        box = tile_box(t, cell, ox, oy)
        kind = m.kind[t]
        fill = KIND_FILL[kind]
        if t in hi:
            fill = tuple(int(a * 0.55 + b * 0.45) for a, b in zip(fill, HILITE))
        d.rectangle(box, fill=fill, outline=GRID)
        x0, y0, x1, y1 = box
        if kind == 'tree':
            r = cell * 0.28
            cx, cy = (x0 + x1) / 2, (y0 + y1) / 2
            d.ellipse((cx - r, cy - r, cx + r, cy + r), fill=(58, 112, 58))
        if show_height and kind in ('ground', 'wall', 'stairs'):
            light = kind == 'wall'
            d.text((x1 - 4, y1 - 3), str(m.height[t]), font=MONO_S,
                   fill=(235, 235, 235) if light else MUTED, anchor='rd')
    if links:
        draw_links(d, links, cell, ox, oy)


def draw_links(d, links, cell, ox, oy):
    """Two-way links as one line between tile centres, one-way links as an arrow."""
    for t, b in links.items():
        x0, y0, x1, y1 = tile_box(t, cell, ox, oy)
        cx, cy = (x0 + x1) / 2, (y0 + y1) / 2
        for name, bit, dx, dy in DIRS:
            if not b & bit:
                continue
            n = (t[0] + dx, t[1] + dy)
            back = links.get(n, 0) & DIRS[(DIRS.index((name, bit, dx, dy)) + 4) % 8][1]
            if n not in links:  # neighbour not computed yet: show the bit as a plain arrow
                draw_arrows(d, t, bit, cell, ox, oy, color=ARROW, width=2, frac=0.62)
            elif back:
                if (dy, dx) > (0, 0):  # draw each two-way pair once
                    d.line((cx, cy, cx + dx * cell, cy + dy * cell), fill=ARROW, width=2)
            else:
                draw_arrows(d, t, bit, cell, ox, oy, color=RED, width=2, frac=0.8)
    for t, b in links.items():
        if b:
            x0, y0, x1, y1 = tile_box(t, cell, ox, oy)
            cx, cy = (x0 + x1) / 2, (y0 + y1) / 2
            d.ellipse((cx - 3, cy - 3, cx + 3, cy + 3), fill=ARROW)


def draw_arrows(d, t, b, cell, ox, oy, color=ARROW, width=2, frac=0.44):
    x0, y0, x1, y1 = tile_box(t, cell, ox, oy)
    cx, cy = (x0 + x1) / 2, (y0 + y1) / 2
    for name, bit, dx, dy in DIRS:
        if not b & bit:
            continue
        L = cell * frac * (1.0 if dx == 0 or dy == 0 else 1.25)
        n = (dx * dx + dy * dy) ** 0.5
        ux, uy = dx / n, dy / n
        ex, ey = cx + ux * L, cy + uy * L
        sx, sy = cx + ux * cell * 0.12, cy + uy * cell * 0.12
        d.line((sx, sy, ex, ey), fill=color, width=width)
        hx, hy = -uy, ux
        s = cell * 0.09
        d.polygon([(ex, ey), (ex - ux * s * 1.6 + hx * s, ey - uy * s * 1.6 + hy * s),
                   (ex - ux * s * 1.6 - hx * s, ey - uy * s * 1.6 - hy * s)], fill=color)


def byte_row(d, x, y, b, active=None):
    names = ['NW', 'W', 'SW', 'S', 'SE', 'E', 'NE', 'N']
    for i, nm in enumerate(names):
        bit = (b >> (7 - i)) & 1
        bx = x + i * 34
        on = active == nm
        d.rectangle((bx, y, bx + 28, y + 28), fill=(255, 235, 235) if on else (255, 255, 255),
                    outline=RED if on else GRID, width=3 if on else 1)
        d.text((bx + 14, y + 14), str(bit), font=MONO_B, fill=INK, anchor='mm')
        d.text((bx + 14, y + 40), nm, font=FONT_S, fill=MUTED, anchor='mm')


def save(frames, durations, name):
    frames[0].save(os.path.join(OUT, name), save_all=True, append_images=frames[1:], duration=durations,
                   loop=0, optimize=True)


# --- GIF 1: one tile, the height rule ---

def one_tile_gif():
    m = Map(5, 5)
    # a stair run climbing to a wall in the north-east, a tree in the south-west
    for x in range(5):
        m.set((x, 0), 'wall', L_WALL_OR_GATEHOUSE, 56)
    m.set((3, 1), 'stairs', L_STAIRS, 44)
    m.set((3, 2), 'stairs', L_STAIRS, 32)
    m.set((3, 3), 'stairs', L_STAIRS, 20)
    m.set((1, 3), 'tree', L_TREE, 8)
    m.height[(1, 1)] = 14
    m.height[(2, 3)] = 10
    t = (2, 2)
    trace = []
    final, _, mode = compute_linkage(m, t, trace)
    C = 92
    OX, OY = 30, 96
    W, H = OX + 5 * C + 40 + 330, OY + 5 * C + 30
    frames, durations = [], []
    link = 0
    verdict = {}

    def frame(title, sub, active=None, dur=1200):
        im = Image.new('RGB', (W, H), BG)
        d = ImageDraw.Draw(im)
        d.text((OX, 16), title, font=FONT_B, fill=INK)
        d.text((OX, 44), sub, font=FONT, fill=MUTED)
        hi = [t] + ([active[2]] if active else [])
        draw_map(d, m, C, OX, OY, hi=hi)
        draw_arrows(d, t, link, C, OX, OY, width=4)
        for n, (ok, text) in verdict.items():
            x0, y0, x1, y1 = tile_box(n, C, OX, OY)
            d.text(((x0 + x1) / 2, y0 + 14), text, font=FONT_S, fill=GREEN if ok else RED, anchor='mm')
        x0, y0, x1, y1 = tile_box(t, C, OX, OY)
        d.rectangle((x0, y0, x1, y1), outline=INK, width=3)
        if active:
            d.rectangle(tile_box(active[2], C, OX, OY), outline=RED, width=4)
        px, py = OX + 5 * C + 40, OY
        d.text((px, py), 'centre tile: %s, height %d' % (mode, m.height[t]), font=FONT_B, fill=INK)
        py += 28
        d.text((px, py), 'a neighbour is linked if its', font=FONT, fill=INK)
        py += 20
        d.text((px, py), 'height is within %d .. %d' % (m.height[t] - 16, m.height[t] + 16), font=FONT,
               fill=INK)
        py += 36
        d.text((px, py), 'PathLinkageLayer[centre]', font=FONT_B, fill=INK)
        py += 28
        byte_row(d, px, py, link, active=active[0] if active else None)
        py += 60
        d.text((px, py), '= 0x%02X' % link, font=MONO, fill=INK)
        py += 34
        for line in ['neighbours are tested in the', 'order N, NE, E, SE, S, SW, W, NW',
                     '(bit 0x01 ... bit 0x80)', '', 'the numbers are made-up heights']:
            d.text((px, py), line, font=FONT_S, fill=MUTED)
            py += 19
        frames.append(im)
        durations.append(dur)

    frame('Linking one tile to its neighbours',
          'The byte starts at 0. Each neighbour that passes the tests sets one bit.', dur=2600)
    for name, bit, n, why in trace:
        frame('%s: height %d' % (name, m.height[n]) if m.kind[n] != 'tree' else '%s: a tree' % name,
              'is it reachable from height %d?' % m.height[t], active=(name, bit, n), dur=900)
        if why is None:
            link |= bit
            verdict[n] = (True, 'linked')
            sub = 'yes: set bit 0x%02X' % bit
        else:
            verdict[n] = (False, 'too high' if why.startswith('height') and m.height[n] > m.height[t]
                          else ('too low' if why.startswith('height') else why))
            sub = 'no: %s' % ('the height differs by more than 16' if why.startswith('height')
                              else 'trees, rocks, water and buildings are never linked')
        frame('%s: %s' % (name, 'linked' if why is None else 'not linked'), sub, active=(name, bit, n), dur=1300)
    assert link == final
    frame('Result: 0x%02X' % link,
          'The low stair (20) is a step up of 12, so it is linked. The higher stairs (32, 44) are not.', dur=4500)
    save(frames, durations, 'linkage-one-tile.gif')


# --- GIF 2: the full pass over a toy map ---

def scene():
    m = Map(12, 8)
    for x in range(2, 10):
        m.set((x, 2), 'wall', L_WALL_OR_GATEHOUSE, 56)
    m.set((5, 3), 'stairs', L_STAIRS, 44)
    m.set((5, 4), 'stairs', L_STAIRS, 32)
    m.set((5, 5), 'stairs', L_STAIRS, 20)
    for xy in [(1, 5), (9, 5), (10, 0), (3, 6)]:
        m.set(xy, 'tree', L_TREE, 8)
    for xy in [(10, 4), (11, 4), (10, 5), (11, 5), (11, 3)]:
        m.set(xy, 'water', L_SEA, 0)
    return m


def full_pass_gif():
    m = scene()
    C = 50
    OX, OY = 24, 78
    W, H = OX + m.w * C + 30 + 300, OY + m.h * C + 50
    frames, durations = [], []
    done = {}

    def frame(title, sub, cur=None, dur=150, info=()):
        im = Image.new('RGB', (W, H), BG)
        d = ImageDraw.Draw(im)
        d.text((OX, 14), title, font=FONT_B, fill=INK)
        d.text((OX, 40), sub, font=FONT, fill=MUTED)
        draw_map(d, m, C, OX, OY, links=done, hi=[cur] if cur else ())
        if cur:
            d.rectangle(tile_box(cur, C, OX, OY), outline=INK, width=3)
            draw_arrows(d, cur, done.get(cur, 0), C, OX, OY, color=(200, 60, 40), width=3)
        px, py = OX + m.w * C + 30, OY
        for line in info:
            d.text((px, py), line, font=MONO, fill=INK)
            py += 21
        lg = OY + m.h * C - 4 * 22
        for label, kind in [('wall (height 56)', 'wall'), ('stairs', 'stairs'), ('tree', 'tree'),
                            ('water', 'water')]:
            box = (px, lg, px + 16, lg + 16)
            d.rectangle(box, fill=KIND_FILL[kind], outline=GRID)
            if kind == 'tree':
                d.ellipse((px + 4, lg + 4, px + 12, lg + 12), fill=(58, 112, 58))
            d.text((px + 24, lg + 8), label, font=FONT_S, fill=INK, anchor='lm')
            lg += 22
        d.text((OX, OY + m.h * C + 12), 'numbers: tile heights (made up).  line: a link in both directions.  arrow: a bit whose neighbour '
               'is not done yet', font=FONT_S, fill=MUTED)
        frames.append(im)
        durations.append(dur)

    frame('Building the whole layer', 'updatePathLinkageLayerForEachBuildingAtEachTile visits every tile once.',
          dur=2500)
    for t in m.tiles():
        b, removed, mode = compute_linkage(m, t)
        done[t] = b
        frame('Tile (%d, %d): %s' % (t[0], t[1], mode),
              'compute its byte from its own logic and height and those of its 8 neighbours', cur=t,
              info=['tile    (%d, %d)' % t, 'mode    %s' % mode, 'height  %d' % m.height[t], '',
                    'linkage 0x%02X' % b, '        {:08b}'.format(b)],
              dur=140 if b in (0, 0xFF) else 260)
    frame('Done', 'Ground is linked to ground, wall to wall, and the stairs join the two levels.',
          info=['links form a graph:', 'tiles are the nodes,', 'links are the edges'], dur=6000)
    save(frames, durations, 'linkage-full-pass.gif')


# --- GIF 3: the diagonal (corner) rule ---

def corner_gif():
    left = Map(3, 3)
    left.set((1, 0), 'wall', L_WALL_OR_GATEHOUSE, 56)
    left.set((2, 1), 'wall', L_WALL_OR_GATEHOUSE, 56)
    right = Map(3, 3)
    right.set((1, 0), 'tree', L_TREE, 8)
    right.set((2, 1), 'tree', L_TREE, 8)
    t = (1, 1)
    C = 96
    OXL, OXR, OY = 30, 30 + 3 * C + 80, 100
    W, H = OXR + 3 * C + 30, OY + 3 * C + 110
    frames, durations = [], []
    lb, lrem, _ = compute_linkage(left, t)
    rb, rrem, _ = compute_linkage(right, t)
    assert lrem == 0x02 and rrem == 0

    def frame(title, sub, lbyte, rbyte, mark=False, dur=2500):
        im = Image.new('RGB', (W, H), BG)
        d = ImageDraw.Draw(im)
        d.text((OXL, 16), title, font=FONT_B, fill=INK)
        d.text((OXL, 44), sub, font=FONT, fill=MUTED)
        for m, ox, b, label in ((left, OXL, lbyte, 'two walls'), (right, OXR, rbyte, 'two trees')):
            draw_map(d, m, C, ox, OY, show_height=False)
            draw_arrows(d, t, b, C, ox, OY, width=4)
            d.rectangle(tile_box(t, C, ox, OY), outline=INK, width=3)
            d.text((ox + 1.5 * C, OY + 3 * C + 18), label, font=FONT_B, fill=INK, anchor='mm')
        if mark:
            x0, y0, x1, y1 = tile_box((2, 0), C, OXL, OY)
            d.line((x0 + 20, y0 + 20, x1 - 20, y1 - 20), fill=RED, width=6)
            d.line((x0 + 20, y1 - 20, x1 - 20, y0 + 20), fill=RED, width=6)
        d.text((OXL, OY + 3 * C + 46), 'left:  N and E are walls: blockers, and not linked  ->  NE removed',
               font=MONO, fill=INK)
        d.text((OXL, OY + 3 * C + 68), 'right: trees are not blockers                    ->  NE stays',
               font=MONO, fill=INK)
        frames.append(im)
        durations.append(dur)

    frame('The corner rule', 'First every neighbour is tested on its own, as before.', lb | lrem, rb | rrem)
    frame('The corner rule', 'NE is reachable by height, but it is squeezed between two walls.', lb | lrem,
          rb | rrem, mark=True)
    frame('The corner rule', 'So the NE bit is cleared. Between two trees the diagonal is kept.', lb, rb,
          dur=5000)
    save(frames, durations, 'linkage-corner-rule.gif')


# --- GIF 4: a wall section is removed, only the 3x3 block around it is recomputed ---

def breach_gif():
    m = Map(9, 6)
    for x in range(9):
        m.set((x, 2), 'wall', L_WALL_OR_GATEHOUSE, 56)
    rebuild(m)
    C = 58
    OX, OY = 24, 80
    W, H = OX + m.w * C + 30 + 290, OY + m.h * C + 40
    frames, durations = [], []
    hole = (4, 2)
    block = [(hole[0] + dx, hole[1] + dy) for dy in (-1, 0, 1) for dx in (-1, 0, 1)]

    def frame(title, sub, hi=(), cur=None, info=(), dur=1300):
        im = Image.new('RGB', (W, H), BG)
        d = ImageDraw.Draw(im)
        d.text((OX, 14), title, font=FONT_B, fill=INK)
        d.text((OX, 40), sub, font=FONT, fill=MUTED)
        draw_map(d, m, C, OX, OY, links=m.link, hi=hi)
        if cur:
            draw_arrows(d, cur, m.link[cur], C, OX, OY, color=(200, 60, 40), width=3)
            d.rectangle(tile_box(cur, C, OX, OY), outline=INK, width=3)
        px, py = OX + m.w * C + 30, OY
        for line in info:
            d.text((px, py), line, font=MONO, fill=INK)
            py += 21
        d.text((OX, OY + m.h * C + 10), 'line: a link in both directions.  red arrow: a one-way link, because only '
               'one of the two bytes is updated yet', font=FONT_S, fill=MUTED)
        frames.append(im)
        durations.append(dur)

    frame('A wall splits the map', 'No arrow crosses the wall: the height difference is too large.',
          info=['ground height 8', 'wall height   56'], dur=3000)
    m.set(hole, 'ground', 0, 8)
    frame('One wall tile is destroyed', 'Its LogicLayer and height change, but the linkage bytes are still old.',
          hi=[hole], info=['tile (4, 2)', 'now ground, height 8', '', 'its byte and its', 'neighbours\' bytes',
                           'are out of date'], dur=3000)
    frame('updatePathLinkagesInAllEightDirections', 'Recompute the tile itself and its eight neighbours.',
          hi=block, info=['only these 9 bytes can', 'involve the changed tile'], dur=2500)
    for t in block:
        m.link[t] = compute_linkage(m, t)[0]
        frame('updatePathLinkagesInAllEightDirections', 'tile (%d, %d)' % t, hi=block, cur=t,
              info=['tile    (%d, %d)' % t, 'linkage 0x%02X' % m.link[t], '        {:08b}'.format(m.link[t])],
              dur=800)
    frame('A gap in the wall', 'Units can now step through the gap, in both directions.',
          hi=[hole], dur=5000)
    save(frames, durations, 'linkage-wall-breach.gif')


if __name__ == '__main__':
    one_tile_gif()
    full_pass_gif()
    corner_gif()
    breach_gif()
    for f in sorted(os.listdir(OUT)):
        if f.startswith('linkage'):
            print(f, os.path.getsize(os.path.join(OUT, f)))
