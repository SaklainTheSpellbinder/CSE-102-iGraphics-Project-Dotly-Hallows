import os
from PIL import Image

def resize_images_in_folder(folder_path, size=(40, 40)):
    # List all files in the given folder
    for filename in os.listdir(folder_path):
        file_path = os.path.join(folder_path, filename)
        
        # Check if the file is an image (you can expand this check if needed)
        if filename.lower().endswith(('png', 'jpg', 'jpeg', 'gif', 'bmp')):
            try:
                # Open the image file
                with Image.open(file_path) as img:
                    # Convert image to RGB mode if it's not already (required for BMP)
                    img = img.convert('RGB')

                    # Resize the image
                    img_resized = img.resize(size)

                    # Create a new filename for the BMP file
                    new_filename = os.path.splitext(filename)[0] + '.bmp'
                    new_file_path = os.path.join(folder_path, new_filename)
                    
                    # Save the resized image as BMP
                    img_resized.save(new_file_path, 'BMP')
                    print(f"Resized and saved as BMP: {new_filename}")
            except Exception as e:
                print(f"Could not resize {filename}: {e}")

if __name__ == "__main__":
    folder_path = r"D:\\iGraphics-Project\\assets\\basilisk"
    resize_images_in_folder(folder_path)
