import os
from PIL import Image


def convert_webp_images(
    input_dir: str,
    output_dir: str,
    out_format: str = "jpg",
    jpg_quality: int = 95,
    bg_color=(255, 255, 255),
):
    """
    Convert all .webp images in input_dir to JPG or PNG.

    :param input_dir: directory containing webp images
    :param output_dir: directory to save converted images
    :param out_format: "jpg" or "png"
    :param jpg_quality: jpg quality (1-100)
    :param bg_color: background color for jpg (RGB tuple)
    """
    out_format = out_format.lower()
    assert out_format in ("jpg", "png"), "out_format must be 'jpg' or 'png'"

    os.makedirs(output_dir, exist_ok=True)

    for filename in os.listdir(input_dir):
        if not filename.lower().endswith(".webp"):
            continue

        in_path = os.path.join(input_dir, filename)
        name, _ = os.path.splitext(filename)
        out_path = os.path.join(output_dir, f"{name}.{out_format}")

        img = Image.open(in_path)

        # --- WebP -> PNG ---
        if out_format == "png":
            img.save(out_path, "PNG")

        # --- WebP -> JPG ---
        else:
            # 处理透明通道
            if img.mode in ("RGBA", "LA"):
                background = Image.new("RGB", img.size, bg_color)
                background.paste(img, mask=img.split()[-1])
                img = background
            else:
                img = img.convert("RGB")

            img.save(
                out_path,
                "JPEG",
                quality=jpg_quality,
                optimize=True,
                progressive=True,
            )

        print(f"[OK] {filename} -> {out_path}")


if __name__ == "__main__":
    # ===== 配置区 =====
    OUTPUT_FORMAT = "jpg"   # "jpg" or "png"
    INPUT_DIR = r"F:\Pictures\temp"
    OUTPUT_DIR = r"F:\Pictures\temp\convert_" + OUTPUT_FORMAT
    JPG_QUALITY = 95

    convert_webp_images(
        input_dir=INPUT_DIR,
        output_dir=OUTPUT_DIR,
        out_format=OUTPUT_FORMAT,
        jpg_quality=JPG_QUALITY,
    )
