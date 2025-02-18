from sys import exit

class Node:
    __slots__ = (
        'val',
        'left',
        'right'
    )

    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None

s = input()
it = iter(s)
try:
    root = Node(next(it))
except StopIteration:
    print('Empty tree')
    exit(1)

for c in it:
    node = root
    while True:
        if c > node.val:
            if node.right:
                node = node.right
            else:
                node.right = Node(c)
                break
        else:
            if node.left:
                node = node.left
            else:
                node.left = Node(c)
                break

def inorder(root: Node):
    if not root: return ()
    return inorder(root.left) + (root.val,) + inorder(root.right)

print(inorder(root))