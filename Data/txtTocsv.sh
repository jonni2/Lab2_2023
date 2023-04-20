# This bash script CONVERTS txt to csv, SPACES to ',' and HEX to DEC

#!/bin/bash

path=$1 #path of file
filename="${path%.*}"
extension="${path#*.}"
csvpath="${filename}.csv"

echo "Converting txt to csv..."
sed 's/ /,/g' $path > $csvpath # Converts SPACES to ','

echo "Converting Hex to Dec..."
python3 HexToDec.py $csvpath

# rm $path
