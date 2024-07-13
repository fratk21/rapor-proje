class Node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None


class BinaryTree:
    def __init__(self):
        self.root = None

    def insert(self, data):
        if self.root is None:
            self.root = Node(data)
        else:
            self._insert_recursive(self.root, data)

    def _insert_recursive(self, node, data):
        if data < node.data:
            if node.left is None:
                node.left = Node(data)
            else:
                self._insert_recursive(node.left, data)
        else:
            if node.right is None:
                node.right = Node(data)
            else:
                self._insert_recursive(node.right, data)

    def remove(self, data):
        self.root = self._remove_recursive(self.root, data)

    def _remove_recursive(self, node, data):
        if node is None:
            return node

        if data < node.data:
            node.left = self._remove_recursive(node.left, data)
        elif data > node.data:
            node.right = self._remove_recursive(node.right, data)
        else:
            if node.left is None:
                return node.right
            elif node.right is None:
                return node.left
            else:
                min_value = self._find_min_value(node.right)
                node.data = min_value
                node.right = self._remove_recursive(node.right, min_value)
        return node

    def _find_min_value(self, node):
        while node.left is not None:
            node = node.left
        return node.data

    def inorder_traversal(self):
        self._inorder_recursive(self.root)

    def _inorder_recursive(self, node):
        if node is not None:
            self._inorder_recursive(node.left)
            print(node.data, end=" ")
            self._inorder_recursive(node.right)


# Ağaç örneğini oluştur
tree = BinaryTree()

# Ekleme işlemleri
tree.insert(5)
tree.insert(3)
tree.insert(7)
tree.insert(2)
tree.insert(4)
tree.insert(6)
tree.insert(8)

# Ağacın son durumu
print("Ağacın son durumu:")
tree.inorder_traversal()

# Çıkarma işlemi
tree.remove(5)

# Ağacın son durumu
print("\n5 çıkarıldıktan sonra ağacın son durumu:")
tree.inorder_traversal()
