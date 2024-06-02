import os

# List of file extensions or names to ignore
IGNORED_FILES = ['.DS_Store']

def get_file_size(file_path):
    return os.path.getsize(file_path)

def should_ignore(file_name):
    for pattern in IGNORED_FILES:
        if file_name == pattern:
            return True
    return False

def list_files(dir_path):
    total_size = 0
    file_sizes = []

    # First pass to calculate total size
    for root, dirs, files in os.walk(dir_path):
        for file in files:
            if should_ignore(file):
                continue
            file_path = os.path.join(root, file)
            size = get_file_size(file_path)
            total_size += size
            file_sizes.append((file_path, size))

    if total_size == 0:
        print("No files found or all files are empty.")
        return

    # Second pass to print sizes and percentages
    for file_path, size in file_sizes:
        percentage = (size / total_size) * 100
        print(f"Size of {file_path}: {size} bytes ({percentage:.2f}%)")

if __name__ == "__main__":
    import sys
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} <directory>")
        sys.exit(1)

    list_files(sys.argv[1])