from collections import deque
import sys
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
        self.like_path = input().split()
        self.path_dict = {}
        self.name_list = []
        self.node_dict = {}
        self.node_dict['1'] = Node('1')
        self.name_list.append('1')
        self.dfs_result = []
        self.result = []
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
        self.dfs(root_node.root, root_node.left_leaf.root)
        self.dfs(root_node.root, root_node.right_leaf.root)
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
    
    def dfs(self, root, leaf=None):
        if leaf is not None:
            path = self.path_dict[(root,leaf)]
            print(root, leaf, path)
            left_result = path
            right_result = path
            node = self.node_dict[leaf]
            if node.left_leaf is None and node.right_leaf is None:
                return path
            else :
                left_result +=self.dfs(node.root,node.left_leaf.root)
                self.result.append(left_result)
                right_result += self.dfs(node.root,node.right_leaf.root)
                self.result.append(right_result)
        else :
            return

        
        
T = Travel()
# print(T.node_dict['1'].right_leaf.root, T.node_dict['1'].left_leaf.root )