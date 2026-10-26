from PIL import Image
import os

input_dir = r"C:\Users\20924\Desktop\temp\self"
output_dir = r"C:\Users\20924\Desktop\temp\self"

os.makedirs(output_dir, exist_ok=True)

for filename in os.listdir(input_dir):
    if filename.lower().endswith(".png"):
        in_path = os.path.join(input_dir, filename)
        out_path = os.path.join(
            output_dir,
            os.path.splitext(filename)[0] + ".jpg"
        )

        with Image.open(in_path) as img:
            dpi = img.info.get("dpi", (72, 72))

            if img.mode in ("RGBA", "LA") or (img.mode == "P" and "transparency" in img.info):
                rgba = img.convert("RGBA")
                bg = Image.new("RGB", rgba.size, (255, 255, 255))
                bg.paste(rgba, mask=rgba.split()[3])
                out_img = bg
            else:
                out_img = img.convert("RGB")

            out_img.save(
                out_path,
                "JPEG",
                quality=100,
                subsampling=0,
                optimize=False,
                dpi=dpi
            )

print("Done.")