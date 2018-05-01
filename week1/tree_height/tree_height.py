# python3

import sys
import threading


# final solution
""" Compute height of a given tree
Height of a (rooted) tree is the maximum depth of a node,
or the maximum distance from a leaf to the root. 
"""
class TreeHeight:
    def __init__(self, nodes):
        self.num = len(nodes)
        self.parent = nodes
        self.depths = [0] * self.num

    def path_len(self, node_id):
        """ Returns path length from given node to root."""
        parent = self.parent[node_id]
        if parent == -1:
            return 1

        if self.depths[node_id]:
            return self.depths[node_id]

        self.depths[node_id] = 1 + self.path_len(self.parent[node_id])
        return self.depths[node_id]

    def compute_height(self):
        """ Computes the tree height."""
        return max([self.path_len(i) for i in range(self.num)])

'''
# original solution
def compute_height(n, parents):
    # Replace this code with a faster implementation
    max_height = 0
    for vertex in range(n):
        height = 0
        current = vertex
        while current != -1:
            height += 1
            current = parents[current]
        max_height = max(max_height, height)
    return max_height
'''

'''
# alternativ solution, explicit build tree and use recursiv compute_height,
# not use cache to store intermediate depth of node,not quick as original solution
def build_tree(root_node, nodes):
    children = [
        build_tree(child, nodes)
        for child, node in enumerate(nodes)
        if node == root_node
    ]
    print(children)
    return {'key': root_node, 'children':children}


def compute_height(tree):
    return 1 + max((compute_height(child) for child in tree['children']), default=-1)
'''

def main():
    '''
    n = int(input())
    parents = list(map(int, input().split()))
    print(compute_height(n, parents))
    '''

    input()
    nodes = list(map(int, input().split()))
    tree = TreeHeight(nodes)
    print(tree.compute_height())
# In Python, the default limit on recursion depth is rather low,
# so raise it here for this problem. Note that to take advantage
# of bigger stack, we have to launch the computation in a new thread.
sys.setrecursionlimit(10**7)  # max depth of recursion
threading.stack_size(2**27)   # new thread will get stack of such size
threading.Thread(target=main).start()