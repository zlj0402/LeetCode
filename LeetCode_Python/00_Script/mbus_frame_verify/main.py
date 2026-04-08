from mbus_frame_verify import MbusFrameVerify
import os

def get_current_path() -> str:
	return os.path.abspath(os.path.dirname(__file__))

def main():
    target_file = "sample.text"
    file_with_path = os.path.join(get_current_path(), target_file)
    MbusFrameVerify(file_with_path).output()

if __name__ == "__main__":
    try:
        main()
    except Exception as e:
        print(f"{e}")