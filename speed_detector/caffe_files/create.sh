
#!/bin/bash

#rm -f train.txt

base_dir="/home/abhi/cmpe297/datasets/final/GTSRB"
out_file="train.txt"
for f in `find . -name "GT-*.csv"`
do
  name=`echo $f | awk -F/ '{OFS="/";$1="";$NF="";print $0;}'`
  awk -v name=$name -v pre=$base_dir '
    BEGIN {FS=";"; OFS=" "}
    {
      if (NR>1) {
        print pre name $1, $NF >> "train.txt"
      }
    }
  ' $f
done

shuf < train.txt > train_shuf.txt
split -l 32000 train_shuf.txt
mv xaa train.txt
mv xab val.txt
