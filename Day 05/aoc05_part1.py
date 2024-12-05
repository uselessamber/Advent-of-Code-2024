checklist = {} # checklist[a] = ['b'] --> a | b

def process_list(instruction : str): # Processing instruction for print order a | b = a before b
    a, b = instruction.split('|')
    if a not in checklist.keys():
        checklist[a] = []
    checklist[a].append(b)

def valid(printed : list[str], current : str) -> bool: # Check if the current can be printed
    if current not in checklist.keys(): # If there is no pre-req, return True
        return True

    for item in printed: # If an item is about to be printed should have been printed earlier, list invalid
        if item in checklist[current]:
            return False
    
    return True # Condition checked out

def print_list(instruction : str) -> int:
    print_order = instruction.split(',')
    printed = []

    for item in print_order:
        if not valid(printed, item):
            return 0
        printed.append(item)

    return int(printed[((len(printed) + 1) // 2) - 1])


def readfile(fname : str):
    ans = 0
    with open(fname, "r") as f:
        mode = 0

        for line in f.readlines():
            if line[-1] == '\n':
                line = line[:-1]
            
            if line == '':
                mode = 1
            elif mode == 0:
                process_list(line)
            else:
                ans += print_list(line)
    return ans

with open("./Day 05/aoc05.out", "w") as f:
    f.write(str(readfile("./Day 05/aoc05.inp")))
