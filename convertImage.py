from PIL import Image

# Use just the filenames since they are in the current directory
input_path = "image.ppm"
output_path = "image.png"

with Image.open(input_path) as img:
    img.save(output_path, "PNG")

print(f"Successfully converted {input_path} to {output_path} in the current directory!")
