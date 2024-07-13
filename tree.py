#hocam animasyon kısmını anlamadım o yüzden ekranı açıp kapatırsam istediğiniz şekilde olur diye düşündüm
#20-75 Fırat Kaya


import matplotlib.pyplot as plt

class Node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None

class BinaryTree:
    def __init__(self):
        self.root = None
        self.fig, self.ax = plt.subplots(figsize=(8, 6))
        self.ax.set_title("2-3 ağaç yapısı")
        self.ax.axis('off')

    def ekle(self, data):
        if self.root is None:
            self.root = Node(data)
        else:
            self._ekle_oz(self.root, data)

    def _ekle_oz(self, node, data):
        if data < node.data:
            if node.left is None:
                node.left = Node(data)
            else:
                self._ekle_oz(node.left, data)
        else:
            if node.right is None:
                node.right = Node(data)
            else:
                self._ekle_oz(node.right, data)

    def cikar(self, data):
        self.root = self._cikar_oz(self.root, data)

    def _cikar_oz(self, node, data):
        if node is None:
            return node

        if data < node.data:
            node.left = self._cikar_oz(node.left, data)
        elif data > node.data:
            node.right = self._cikar_oz(node.right, data)
        else:
            if node.left is None:
                return node.right
            elif node.right is None:
                return node.left
            else:
                min_value = self.en_kucuk(node.right)
                node.data = min_value
                node.right = self._cikar_oz(node.right, min_value)
        return node

    def en_kucuk(self, node):
        while node.left is not None:
            node = node.left
        return node.data

    def gecis(self):
        values = []
        self.gecis_oz(self.root, values)
        return values

    def gecis_oz(self, node, values):
        if node is not None:
            self.gecis_oz(node.left, values)
            values.append(node.data)
            self.gecis_oz(node.right, values)

    def goster(self):
        self.ax.clear()
        self.ax.set_title("2-3 ağaç yapısı")
        self.ax.axis('off')
        self._goster_oz(self.root, 0, 0, 100)
        plt.pause(0.5)

    def _goster_oz(self, node, x, y, step):
        if node is not None:
            self.ax.text(x, y, str(node.data), style='italic', weight='bold', ha='center', va='center',
                    bbox={'facecolor': 'lightblue', 'edgecolor': 'gray', 'pad': 10})
            if node.left is not None:
                self.ax.plot([x, x - step], [y - 1, y - step], 'k-')
                self._goster_oz(node.left, x - step, y - step, step / 2)
            if node.right is not None:
                self.ax.plot([x, x + step], [y - 1, y - step], 'k-')
                self._goster_oz(node.right, x + step, y - step, step / 2)

tree = BinaryTree()

tree.ekle(5)
tree.goster()

tree.ekle(3)
tree.goster()

tree.ekle(7)
tree.goster()

tree.ekle(2)
tree.goster()

tree.ekle(4)
tree.goster()

tree.ekle(6)
tree.goster()

tree.ekle(8)
tree.goster()

tree.cikar(5)
tree.goster()

tree.cikar(4)
tree.goster()

tree.cikar(7)
tree.goster()

print("Ağacın son durumu:", tree.gecis())
