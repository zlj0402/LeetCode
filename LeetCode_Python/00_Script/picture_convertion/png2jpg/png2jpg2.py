
from PIL import Image
import os
from rembg import remove, new_session

input_dir = r"C:\Users\20924\Desktop\temp\self"
output_dir = r"C:\Users\20924\Desktop\temp\self"

# 证件照底色
BG_COLORS = {
    "white": (255, 255, 255),
    "blue": (67, 142, 219),
    "red": (255, 0, 0),
}

# 这里改成你要的底色
BG_COLOR = BG_COLORS["blue"]

os.makedirs(output_dir, exist_ok=True)

# 人像分割模型，放在循环外，只加载一次
session = new_session("u2net_human_seg")

for filename in os.listdir(input_dir):
    if filename.lower().endswith(".png"):
        in_path = os.path.join(input_dir, filename)
        out_path = os.path.join(
            output_dir,
            os.path.splitext(filename)[0] + ".jpg"
        )

        with Image.open(in_path) as img:
            dpi = img.info.get("dpi", (72, 72))

            # 统一转 RGBA
            img_rgba = img.convert("RGBA")

            # 自动抠图，得到透明背景人像
            foreground = remove(img_rgba, session=session)

            # 新建纯色背景
            bg = Image.new("RGBA", foreground.size, BG_COLOR + (255,))

            # 合成：底色 + 人像
            out_img = Image.alpha_composite(bg, foreground).convert("RGB")

            out_img.save(
                out_path,
                "JPEG",
                quality=100,
                subsampling=0,
                optimize=False,
                dpi=dpi
            )

print("Done.")