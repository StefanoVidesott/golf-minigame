#!/bin/bash

# Check if the "context" file already exists
if [ -f "context.md" ]; then
    echo "context.md already exists. Removing it..."
    rm context.md
else
    echo "context.md does not exist. Creating a new one..."
fi

# Create the "context.md" file
touch context.md
echo "Creating context.md file..."
# Find all files in the "include" directory and its subdirectories
echo "Engine and game using SFML 3.0.1" >> context.md
find "./src" -type f | grep -v "include/" | while read -r file; do
    # Get the file name without the path
    filename=$(basename "$file")
    #only process files with specific extensions
    if [[ ! "$filename" =~ \.(cpp|hpp)$ ]]; then
        continue
    fi
    # Get the content of the file
    content=$(cat "$file")
    # Write the filename and content to the "context.md" file
    echo "# File: $filename" >> context.md
    echo "$content" >> context.md
    echo "" >> context.md
done

tree src -L 3 -I "build/" -I "res/" -I "tools/" >> context.md

echo "context.md file created successfully."
