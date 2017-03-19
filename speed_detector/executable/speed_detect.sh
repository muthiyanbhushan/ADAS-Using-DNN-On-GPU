
image=00169.ppm
cascade=/home/ubuntu/datasets/final/GTSRB/Final_Training/data_haar/cascade.xml

rm input.ppm output.ppm

./speedDetector --cascade $cascade $image

convert output.ppm -resize 32x32 input.ppm

python classify.py
