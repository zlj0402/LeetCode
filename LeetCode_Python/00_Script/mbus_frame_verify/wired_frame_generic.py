from enum import Enum

from frame import Frame

class WiredFrame(Frame):

    class ErrReason(Enum):
        NOT_IN_RANGE = 0
        START_ERROR = 1
        LENGTH_ERROR = 2
        CHECK_SUM_ERROR = 3
        END_ERROR = 4
        
    def __init__(self, frame_lst: list):
        super().__init__(frame_lst)
        self.__reason = None
        self.__verify()

    def __verify(self) -> bool:
        if self._src.__len__() == 1 and self._src[0] == 0xE5:
            self._format = Frame.Format.SINGLE_ACK
            return True
        elif self._src[0] == Frame.START_OF_LONG_FRAME:
            return self.__is_valid_varaible_frame() != None
        elif self._src[0] == Frame.START_OF_SHORT_FRAME:
            return self.__is_valid_fixed_frame() != None
        else:
            self.__reason = self.ErrReason.START_ERROR
            return False

    def __is_valid_fixed_frame(self) -> bool:
        if len(self._src) < Frame.SIZE_OF_SHORT_FRAME_BASE or \
            len(self._src) > Frame.SIZE_OF_SHORT_FRAME_BASE + 1:
            self.__reason = self.ErrReason.NOT_IN_RANGE
        if self._src[-2] != sum(self._src[1:-2]):
            self.__reason = self.ErrReason.CHECK_SUM_ERROR
        if self._src[-1] != Frame.END_OF_FRAME:
            self.__reason = self.ErrReason.END_ERROR
        self._format = Frame.Format.FIXED

    def __is_valid_varaible_frame(self) -> bool:
        if len(self._src) < Frame.SIZE_OF_LONG_FRAME_BASE:
            self.__reason = self.ErrReason.NOT_IN_RANGE
        if self._src[0] != self._src[3]:
            self.__reason = self.ErrReason.START_ERROR
        if self._src[1] != self._src[2] or self._src[1] != len(self._src[4:-2]):
            self.__reason = self.ErrReason.LENGTH_ERROR
        if self._src[-2] != sum(self._src[4:-2]):
            self.__reason = self.ErrReason.CHECK_SUM_ERROR
        if self._src[-1] != Frame.END_OF_FRAME:
            self.__reason = self.ErrReason.END_ERROR
        self._format = Frame.Format.VARIABLE
        return self._format
    
    def __str__(self):
        return f"Format: {self.format}, src: {' '.join(f'{x:02x}' for x in self._src)}" \
        if self._format != None else f"Format: {self.format}, Reason: {self.ErrReason.name}, src: {' '.join(f'{x:02x}' for x in self._src)}"
    