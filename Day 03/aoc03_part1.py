import re
import os

pattern = "mul\\([0-9]{1,3},[0-9]{1,3}\\)"
input_string = "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))"

def multiply(input : str):
    find_num = "[0-9]{1,3}"
    multiplicant = re.findall(find_num, input)
    return int(multiplicant[0]) * int(multiplicant[1])

ans = 0
with open(os.getcwd() + '\\Day 03\\aoc03.inp', 'r') as f:
    for line in f.readlines():
        input_string = line
        if input_string[:-1] == '\n':
            input_string = input_string[:-1]
        res = re.findall(pattern, input_string)
        # print(len(res))
        ans += sum([multiply(s) for s in res])

with open(os.getcwd() + '\\Day 03\\aoc03.out', 'w') as f:
    f.write(str(ans))