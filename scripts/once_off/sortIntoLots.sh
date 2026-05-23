#!/bin/bash

folder="C:\\Users\\David\\Videos\\YT_UPLOADS"
extension="mp4"
count=0
folderCount=1
filesPerFolder=15

# Iterate over the MP4 files
for file in "$folder"/*."$extension"; do
    ((count++))

    if ((count > filesPerFolder)); then
        count=1
        ((folderCount++))
    fi

    destinationFolder="$folder/LOT$folderCount"
    mkdir -p "$destinationFolder"
    mv "$file" "$destinationFolder"
done

echo "Sorting complete."
