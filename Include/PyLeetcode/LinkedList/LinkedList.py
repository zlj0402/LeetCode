# Include/PyLeetcode/LinkedList/ListNode.py

from __future__ import annotations
from typing import List, Optional

print(">>> reverse_list module loaded")

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

    @staticmethod
    def print_list(node: Optional[ListNode]):
        cur = node
        values = []
        while cur:
            values.append(str(cur.val))
            cur = cur.next
        print(" -> ".join(values))

    @staticmethod
    def build_list(values: List[int]) -> Optional[ListNode]:
        """从 Python 列表构建链表"""
        dummy = ListNode()
        cur = dummy
        for v in values:
            cur.next = ListNode(v)
            cur = cur.next
        return dummy.next

    def to_list(self) -> List[int]:
        """将链表转换成 Python 列表"""
        cur = self
        out: List[int] = []
        while cur:
            out.append(cur.val)
            cur = cur.next
        return out

    def __repr__(self):
        return f"ListNode({self.val})"
