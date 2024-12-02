import os

for i in range(1, 25):
    os.mkdir(f"./Day {(i + 1):02d}")
    with open(f"./Day {(i + 1):02d}/aoc{(i + 1):02d}.inp", "w") as f:
        pass
    with open(f"./Day {(i + 1):02d}/aoc{(i + 1):02d}.out", "w") as f:
        pass
    with open(f"./Day {(i + 1):02d}/aoc{(i + 1):02d}_part1.py", "w") as f:
        pass
    with open(f"./Day {(i + 1):02d}/aoc{(i + 1):02d}_part1.cpp", "w") as f:
        pass
    with open(f"./Day {(i + 1):02d}/aoc{(i + 1):02d}_part1.java", "w") as f:
        pass
    with open(f"./Day {(i + 1):02d}/aoc{(i + 1):02d}_part2.py", "w") as f:
        pass
    with open(f"./Day {(i + 1):02d}/aoc{(i + 1):02d}_part2.cpp", "w") as f:
        pass
    with open(f"./Day {(i + 1):02d}/aoc{(i + 1):02d}_part2.java", "w") as f:
        pass

with open(".gitignore", "w") as f:
    for i in range(25):
        f.write(f"Day {(i + 1):02d}/aoc{(i + 1):02d}.inp\n")
        f.write(f"Day {(i + 1):02d}/aoc{(i + 1):02d}.out\n")