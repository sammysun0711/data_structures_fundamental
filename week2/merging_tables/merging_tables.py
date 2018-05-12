import sys

n, m = map(int, sys.stdin.readline().split())
lines = list(map(int, sys.stdin.readline().split()))
rank = [1] * n
parent = list(range(0, n))
max_size = max(lines)
max_size_history = []

def getParent(table):
    # find parent and compress path
    if table != parent[table]:
        parent[table] = getParent(parent[table])
    return parent[table]
'''
merge two table(tree) using heuristic union by rank
update rank and size
calculate max_table_size for each merge step
'''
def merge(des, src):
    global max_size
    i_des = getParent(des)
    i_src = getParent(src)
    if i_des != i_src:
        if rank[i_des] > rank[i_src]:
            lines[i_des] += lines[i_src]

            parent[i_src] = i_des
            lines[i_src] = 0
        else:
            lines[i_src] += lines[i_des]

            parent[i_des] = i_src
            lines[i_des] = 0
            if rank[i_des] == rank[i_src]:
                rank[i_src] += 1
    max_size = max(max(max_size, lines[i_des]), lines[i_src])

for i in range(m):
    destination, source = map(int, sys.stdin.readline().split())
    merge(destination - 1, source - 1)
    max_size_history.append(max_size)
for i in max_size_history:
    print i
