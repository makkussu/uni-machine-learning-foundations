from queue import Queue, PriorityQueue
from time import time

class WorldEmulation:
    def __init__(self, map: list):
        self.map: list = map
        self.width: int = len(map[0])
        self.height: int = len(map)

    def get_char(self, pos: tuple):
        return self.map[pos[1]][pos[0]]

    def validate_move(self, pos: tuple) -> bool:
        return 0 <= pos[1] < self.height and 0 <= pos[0] < self.width and self.get_char(pos) != '*'
    
    def is_end(self, pos: tuple) -> bool:
        return self.map[pos[1]][pos[0]] == 'D'

MOVES = [(0, 1), (-1, 0), (0, -1), (1, 0)]

# Data for larger maps
MAP_NAME = ["cave300x300", "cave600x600", "cave900x900"]
GOAL_POS = [(257, 295), (595, 598), (895, 898)]
START_POS = (2, 2)

def read_file_to_list(file: str) -> list:
    map_data: list = []

    ## Remove H1 from the string when the program is started from H1 folder.
    ## It was added to please VSCode's Python extension :')
    with open(f'H1/data/{file}') as f:
        map_data = [l.strip() for l in f.readlines() if len(l) > 1]
    
    return map_data

def print_path(map: list, path: list):
    print(path)
    new_map: list = [list(word) for word in map]
    for el in path:
        new_map[el[1]][el[0]] = '.'

    for el in new_map:
        print(''.join(el) + '\n')

# Heurestic function
def h(node: tuple, goal: tuple):
    return abs(node[0] - goal[0]) + abs(node[1] - goal[1])

# BREADTH FIRST SEARCH
def BFS(world: WorldEmulation, start: tuple):
    frontier = Queue()
    frontier.put(start)
    came_from = {}
    came_from[start] = None
    path: list = []
    
    iterations: int = 0

    while not frontier.empty():
        current = frontier.get()
        iterations += 1

        if world.is_end(current):
            while current != start:
                path.append(current)
                current = came_from[current]
            path.append(start)

            print(f'BFS iterations: {iterations}')

            return path

        for step in MOVES:
            next_step = tuple(map(lambda x, y: x + y, current, step))
            if world.validate_move(next_step) and next_step not in came_from:
                frontier.put(next_step)
                came_from[next_step] = current

# GREEDY BFS
def GBFS(world: WorldEmulation, start: tuple, goal: tuple):
    frontier = PriorityQueue()
    frontier.put((0, start))
    came_from = {}
    came_from[start] = None
    path: list = []

    iterations: int = 0


    while not frontier.empty():
        _, current = frontier.get()
        iterations += 1

        if world.is_end(current):
            while current != start:
                path.append(current)
                current = came_from[current]
            path.append(start)

            print(f'GBFS iterations: {iterations}')

            return path

        for step in MOVES:
            next_step = tuple(map(lambda x, y: x + y, current, step))
            if world.validate_move(next_step) and next_step not in came_from:
                priority = h(goal, next_step)
                frontier.put((priority, next_step))
                came_from[next_step] = current

# ASTAR BFS
def ASTAR(world: WorldEmulation, start: tuple, goal: tuple):
    frontier = PriorityQueue()
    frontier.put((0, start))
    
    came_from = {}
    came_from[start] = None

    cost_so_far: dict[tuple, int] = {}
    cost_so_far[start] = 0

    path: list = []

    iterations: int = 0

    while not frontier.empty():
        _, current = frontier.get()
        iterations += 1

        if world.is_end(current):
            while current != start:
                path.append(current)
                current = came_from[current]
            path.append(start)

            print(f'ASTAR iterations: {iterations}')

            return path

        for step in MOVES:
            next_step = tuple(map(lambda x, y: x + y, current, step))
            new_cost = cost_so_far[current] + 1

            if world.validate_move(next_step) and next_step not in came_from:
                cost_so_far[next_step] = new_cost
                priority = new_cost + h(goal, next_step)
                frontier.put((priority, next_step))
                came_from[next_step] = current

def emulate_big_map(map_num: int) -> int:
    map: list = read_file_to_list(MAP_NAME[map_num])
    world: WorldEmulation = WorldEmulation(map)
    
    ## To emulate BFS/GBFS/ASTAR, uncomment the required
    ## function and comment the previous one

    # return len(BFS(world, START_POS))
    # return len(GBFS(world, START_POS, GOAL_POS[map_num]))
    return len(ASTAR(world, START_POS, GOAL_POS[map_num]))

start_time = time()
length = emulate_big_map(2)
end_time = time()

print(f'step length: {length}')
print(f'ms: {(end_time - start_time) * 1000}')