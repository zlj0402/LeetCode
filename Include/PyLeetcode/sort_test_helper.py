import random
import time
from typing import List, Protocol, TypeVar

class SupportsLE(Protocol):
    def __le__(self, other: 'SupportsLE') -> bool: ...

T = TypeVar('T', bound=SupportsLE)

class SortTestHelper:
    @staticmethod
    def generate_random_array(n: int, range_l: int, range_r: int) -> List[int]:
        """生成 n 个元素的随机数组, 每个元素的范围为 [range_l, range_r]"""
        if range_l > range_r:
            raise ValueError("range_l should not be greater than range_r")
        random.seed(time.time())
        return [random.randint(range_l, range_r) for _ in range(n)]

    @staticmethod
    def generate_nearly_ordered_array(n: int, swap_times: int) -> List[int]:
        """生成一个近乎有序的数组: 先排好序, 再随机交换 swap_times 对元素"""
        arr = list(range(n))
        random.seed(time.time())
        for _ in range(swap_times):
            posx = random.randint(0, n - 1)
            posy = random.randint(0, n - 1)
            arr[posx], arr[posy] = arr[posy], arr[posx]
        return arr

    @staticmethod
    def generate_ordered_array(n: int, ascending: bool = True) -> List[int]:
        """生成一个有序的数组 [0..n-1] 或 [n-1..0]"""
        return list(range(n)) if ascending else list(range(n - 1, -1, -1))

    @staticmethod
    def copy_array(arr: List[T]) -> List[T]:
        """拷贝一个数组并返回新数组（浅拷贝）"""
        return arr.copy()

    @staticmethod
    def print_array(arr: List[T]) -> None:
        """打印数组内容"""
        print(" ".join(str(x) for x in arr))

    @staticmethod
    def is_sorted(arr: List[T]) -> bool:
        """辅助：检查数组是否已排序（升序）"""
        return all(arr[i] <= arr[i+1] for i in range(len(arr) - 1))