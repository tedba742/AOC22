from collections import deque
from math import gcd
from functools import lru_cache

# Directions for blizzards
DIRECTION_MAP = {
    '>': (0, 1),
    '<': (0, -1),
    '^': (-1, 0),
    'v': (1, 0)
}

# Directions for movement (stay, up, down, left, right)
MOVE_DIRECTIONS = [(0, 0), (-1, 0), (1, 0), (0, -1), (0, 1)]

def parse_input(filename):
    with open(filename, 'r') as f:
        lines = f.readlines()
    grid = [list(line.strip()) for line in lines]
    return grid

def get_blizzards(grid):
    blizzards = []
    for i, row in enumerate(grid):
        for j, cell in enumerate(row):
            if cell in DIRECTION_MAP:
                blizzards.append((i, j, DIRECTION_MAP[cell]))
    return blizzards

def lcm(a, b):
    return abs(a * b) // gcd(a, b)

def precompute_blizzards(blizzards, rows, cols):
    cycle_length = lcm(rows - 2, cols - 2)
    blizzard_positions = [set() for _ in range(cycle_length)]
    
    for t in range(cycle_length):
        positions = set()
        for (x, y, (dx, dy)) in blizzards:
            new_x = (x + dx * t) % (rows - 2)
            new_y = (y + dy * t) % (cols - 2)
            if new_x == 0: new_x = rows - 2
            if new_x == rows - 1: new_x = 1
            if new_y == 0: new_y = cols - 2
            if new_y == cols - 1: new_y = 1
            positions.add((new_x, new_y))
        blizzard_positions[t] = positions

    return blizzard_positions

def is_valid(x, y, rows, cols, walls, blizzards_positions, time):
    cycle_time = time % len(blizzards_positions)
    if (x, y) in walls or (x, y) in blizzards_positions[cycle_time]:
        return False
    if x < 0 or y < 0 or x >= rows or y >= cols:
        return False
    return True

def find_shortest_path(grid):
    rows = len(grid)
    cols = len(grid[0])
    
    start = (0, grid[0].index('.'))
    goal = (rows - 1, grid[rows - 1].index('.'))
    
    walls = set()
    for i, row in enumerate(grid):
        for j, cell in enumerate(row):
            if cell == '#':
                walls.add((i, j))

    blizzards = get_blizzards(grid)
    blizzards_positions = precompute_blizzards(blizzards, rows, cols)

    queue = deque([(0, start)])
    visited = set([(0, start)])
    
    while queue:
        time, (x, y) = queue.popleft()
        
        if (x, y) == goal:
            return time
        
        for dx, dy in MOVE_DIRECTIONS:
            nx, ny = x + dx, y + dy
            next_state = (time + 1, (nx, ny))
            if next_state not in visited and is_valid(nx, ny, rows, cols, walls, blizzards_positions, time + 1):
                visited.add(next_state)
                queue.append(next_state)

    return -1

if __name__ == "__main__":
    grid = parse_input('input.txt')
    result = find_shortest_path(grid)
    print("Fewest number of minutes required to avoid the blizzards & reach the goal:", result)
