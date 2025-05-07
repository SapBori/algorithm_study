from collections import deque
import sys
from itertools import combinations
sys.setrecursionlimit(5000)
class Node:
    def __init__(self,root):
        self.root = root
        self.left_leaf = None 
        self.right_leaf = None
        self.left_path= ''
        self.right_path= ''
        self.visited = False

class Travel:
    def __init__(self):
        self.node_cnt, self.str_length = map(int, input().split())
        self.like_path = input()
        self.path_dict = {}
        self.name_list = []
        self.node_dict = {}
        self.node_dict['1'] = Node('1')
        self.name_list.append('1')
        self.dfs_result = []
        self.result = 0
        self.stack = []
        self.setup()
    def setup(self):
        for i in range(self.str_length):
            start, end, path = map(str, input().split())
            if int(start) > int(end):
                end,start = start, end
            self.path_dict[(start, end)] = path
            if start not in self.name_list:
                temp_node = Node(start)
                self.add_leaf(temp_node, end)      # 하위 노드에 먼저 넣어놓고 시작
                self.node_dict[start] = temp_node
                self.name_list.append(start)
            else :
                node = self.node_dict[start]
                self.add_leaf(node,end)
        root_node = self.node_dict['1']
        self.stack.append(root_node.root) # '2,3'이 들어감
        self.dfs("")
        self.partition()
        print(self.result)
    def add_leaf(self,node,leaf):
        if node.left_leaf is None:
            node.left_leaf = Node(leaf)
            self.node_dict[leaf] = node.left_leaf
            self.name_list.append(leaf)
        else :
            node.right_leaf = Node(leaf)
            self.node_dict[leaf] = node.right_leaf
            self.name_list.append(leaf)
    
    def dfs(self,path):
        while len(self.stack) >= 1:
            # print(self.stack)
            left_result = path
            right_result = path
            root = self.stack.pop(0) # 
            node = self.node_dict[root]
            if node.left_leaf is None and node.right_leaf is None:
                self.dfs_result.append(path)
            else :
                if node.left_leaf is not None :
                    left_result += self.path_dict[(root, node.left_leaf.root)]
                    # print(root, node.left_leaf.root, path)
                    self.stack.insert(0,node.left_leaf.root)
                    self.dfs(left_result)
                if node.right_leaf is not None:
                    right_result += self.path_dict[(root, node.right_leaf.root)]
                    # print(root, node.right_leaf.root, path)
                    self.stack.insert(0,node.right_leaf.root)
                    self.dfs(right_result)
    def partition(self):
        # 모든 길이의 부분집합 생성
        text = str(self.like_path)
        # 모든 길이의 부분집합 생성
        subsets = []
        for i in range(1, len(text) + 1):  # 길이 1부터 전체 길이까지
            subsets.extend([''.join(combo) for combo in combinations(text, i)])
        for target in self.dfs_result:
            if target in subsets:
                self.result += len(target)

        
T = Travel()
# print(T.node_dict['1'].right_leaf.root, T.node_dict['1'].left_leaf.root )