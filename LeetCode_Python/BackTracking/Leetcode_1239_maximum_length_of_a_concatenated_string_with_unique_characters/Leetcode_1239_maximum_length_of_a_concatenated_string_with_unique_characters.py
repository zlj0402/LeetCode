from typing import List

# error -- version
class Solution:
    def isValid(self, mask, s, res) -> bool:
        valid = True
        invalidIdx = 0
        for i in range(s.__len__()):
            if not valid: break
            invalidIdx += 1
            c = s[i]
            res.append(c)
            lastMask = mask
            
            mask ^= (1 << (ord(c) - ord('a')))
            if mask < lastMask:
                valid = False

        if valid: return True

        self.delMask(mask, s, res, invalidIdx)

        return False

    def delMask(self, mask, s, res, len):
        for i in range(len):
            mask ^= (1 << (ord(s[i]) - ord('a')))
            res.pop()

    def maxLength(self, arr: List[str]) -> int:
        res = []
        maxLen = 0
        size = arr.__len__()
        mask = 0

        def dfs(i: int) -> None:
            nonlocal maxLen, size, mask, res
            if res.__len__() > maxLen:
                maxLen = res.__len__()
            for j in range(i, size):
                valid = self.isValid(mask, arr[j], res)
                dfs(j + 1)
                if valid:
                    self.delMask(mask, arr[j], res, arr[j].__len__())
        dfs(0)

        return maxLen
    

# chat
class Solution:
    def maxLength(self, arr: List[str]) -> int:
        maxLen = 0

        def dfs(idx: int, mask: int, length: int) -> None:
            nonlocal maxLen
            maxLen = max(maxLen, length)

            for i in range(idx, len(arr)):
                curMask = 0
                valid = True

                # 计算当前字符串的 mask
                for c in arr[i]:
                    bit = 1 << (ord(c) - ord('a'))
                    # 字符串自身有重复 或 与已有 mask 冲突
                    if curMask & bit or mask & bit:
                        valid = False
                        break
                    curMask |= bit

                if valid:
                    dfs(i + 1, mask | curMask, length + len(arr[i]))

        dfs(0, 0, 0)
        return maxLen