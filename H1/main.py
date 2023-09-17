from queue import Queue

class WorldEmulation:
    def __init__(self, map: list):
        self.map: list = map
        self.width: int = len(map[0])
        self.height: int = len(map)

    def get_char(self, pos: tuple):
        return self.map[pos[0]][pos[1]]

    def validate_move(self, pos: tuple) -> bool:
        return 0 <= pos[0] < self.height and 0 <= pos[1] < self.width and self.get_char(pos) != '*'
    
    def is_end(self, pos: tuple) -> bool:
        return self.map[pos[0]][pos[1]] == 'D'

lava_map1 = [
    "      **               **      ",
    "     ***     D        ***      ",
    "     ***                       ",
    "                      *****    ",
    "           ****      ********  ",
    "           ***          *******",
    " **                      ******",
    "*****             ****     *** ",
    "*****              **          ",
    "***                            ",
    "              **         ******",
    "**            ***       *******",
    "***                      ***** ",
    "                               ",
    "                s              ",
]

lava_map2 = [
    "     **********************    ",
    "   *******   D    **********   ",
    "   *******                     ",
    " ****************    **********",
    "***********          ********  ",
    "            *******************",
    " ********    ******************",
    "********                   ****",
    "*****       ************       ",
    "***               *********    ",
    "*      ******      ************",
    "*****************       *******",
    "***      ****            ***** ",
    "                               ",
    "                s              ",
]
start_row=14
start_col=16

start = (start_row, start_col)
world: WorldEmulation = WorldEmulation(lava_map1)
MOVES = [(0, 1), (-1, 0), (0, -1), (1, 0)]

def BFS(start: tuple):
    frontier = Queue()
    frontier.put(start)
    came_from = {}
    came_from[start] = None
    path: list = []

    while not frontier.empty():
        current = frontier.get()

        if world.is_end(current):
            while current != start:
                path.append(current)
                current = came_from[current]
            path.append(start)
            return path

        for step in MOVES:
            next_step = tuple(map(lambda x, y: x + y, current, step))
            if world.validate_move(next_step) and next_step not in came_from:
                frontier.put(next_step)
                came_from[next_step] = current


def print_path(map: list, path: list):
    print(path)
    new_map: list = [list(word) for word in map]
    for el in path:
        new_map[el[0]][el[1]] = '.'

    for el in new_map:
        print(''.join(el) + '\n')

print_path(lava_map1, BFS(start))