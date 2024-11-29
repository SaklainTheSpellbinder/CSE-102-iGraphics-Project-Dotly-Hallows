from PIL import Image
import os

# Specify the path to the 'runanimation' folder
folder_path = r"H:\\iGraphics-Project\\assets\\harry"  # Use raw string to avoid escape sequence issues

# Define the background color to remove (e.g., white)
background_color = (103, 167, 141)

# Loop through each file in the folder
for filename in os.listdir(folder_path):
    # Check if the file is a .png
    if filename.endswith(".png"):
        # Define the full path to the file
        img_path = os.path.join(folder_path, filename)
        
        try:
            # Open the image and convert to RGBA for transparency support
            img = Image.open(img_path).convert("RGBA")
            
          
            
            # Define the new filename with .bmp extension
            bmp_filename = filename.replace(".png", ".bmp")
            bmp_path = os.path.join(folder_path, bmp_filename)
            
            # Save the image in BMP format
            img.save(bmp_path, "BMP")
            print(f"Converted {filename} to {bmp_filename} with background removed")
        
        except Exception as e:
            print(f"Error converting {filename}: {e}")

print("Conversion complete. All .png files have been converted to .bmp with background removed.")
