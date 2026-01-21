from PIL import Image
import os

# 批量转换
input_dir = r"F:\Pictures\temp"
output_dir = r"F:\Pictures\temp"

os.makedirs(output_dir, exist_ok=True)

for filename in os.listdir(input_dir):
    if filename.lower().endswith(".jfif"):
        in_path = os.path.join(input_dir, filename)
        out_path = os.path.join(
            output_dir,
            os.path.splitext(filename)[0] + ".jpg"
        )

        with Image.open(in_path) as img:
            img.save(out_path, "JPEG")

print("Done.")
