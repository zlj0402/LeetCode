from wired_frame_generic import WiredFrame

class MbusFrameVerify(WiredFrame):
    def __init__(self, file_with_path: str):
        self.file = file_with_path
        self.__lines = []

    def __get_lines(self) -> None:
        try:
            with open(file=self.file, mode='r', encoding="utf-8") as f:
                for line in f.readlines():
                    self.__lines.append([int(x, 16) for x in line.split()])
        except FileNotFoundError:
            print("文件不存在")
        except UnicodeDecodeError:
            print("文件编码错误")
        except Exception as e:
            print(f"发生未知异常: {e}")

    def output(self) -> None:
        self.__get_lines()
        for i, line in enumerate(self.__lines):
            print(i, WiredFrame(line))
        