import os

def get_direction(a, b):
    if abs(b - a) > 0:
        return (b - a) / abs(b - a)
    return 0

def analyze(data : list) -> bool:
    int_data = [int(x) for x in data]
    global_dir = get_direction(int_data[0], int_data[1])
    if global_dir == 0:
        return False
    for i in range(len(data) - 1):
        if get_direction(int_data[i], int_data[i + 1]) != global_dir or abs(int_data[i + 1] - int_data[i]) > 3:
            return False
    return True


result = 0
with open(os.getcwd() + '\\Day 02\\aoc02.inp', 'r') as f:
    for line in f.readlines():
        if line[-1] == '\n':
            line = line[:-1]
        data = line.split(" ")
        result += analyze(data);

with open(os.getcwd() + '\\Day 02\\aoc02.out', 'w') as f:
    f.write(str(result))
