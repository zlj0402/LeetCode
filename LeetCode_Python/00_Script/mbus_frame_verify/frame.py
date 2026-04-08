from abc import ABC, abstractclassmethod
from enum import Enum

class Frame:
    START_OF_SHORT_FRAME = 0x10
    START_OF_LONG_FRAME = 0x68
    END_OF_FRAME = 0x16

    SIZE_OF_SHORT_FRAME_BASE = 5
    SIZE_OF_LONG_FRAME_BASE = 9

    class Format(Enum):
        FIXED = 0
        VARIABLE = 1
        SINGLE_ACK = 2

    def __init__(self, frame_lst: list):
        self._src = frame_lst
        self._format = None

    @abstractclassmethod
    def verify(self) -> bool:
        pass

    @property
    def format(self) -> str:
        return "None" if self._format == None else self._format.name

    @abstractclassmethod
    def __str__(self):
        return f"Format: {self.format}, src: {' '.join(f'{x:02x}' for x in self._src)}"