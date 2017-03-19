import subprocess

model= 'cifar10_quick.prototxt'
test_net= 'cifar10_quick_iter_5000.caffemodel.h5'
mean= 'mean.binaryproto'
label= 'labels.txt'
image= 'input.ppm'
executable = './build/examples/cpp_classification/classification.bin'


labels = {'0': 'speed = 20', '1': 'speed = 30', '2': 'speed = 50', '3': 'speed = 60', '4': 'speed = 70', \
          '5': 'speed = 80', '6': 'end of speed 80', '7': 'speed = 100', '8': 'speed = 120', '9': 'no passing', \
          '10': 'no passsing for heavy vehicles', '11': 'priority', '12': 'priority road' , '13' : 'yield', \
          '14' : 'stop','15' : 'road closed', '16':'trucks prohibited', '17':'do not enter', '18':'danger' , \
          '19' : 'curve left', '20' : 'curve right', '21' : 'double curve', '22': 'speed breaker', \
          '23': 'loose gravel', '24': 'road narrow' , '25' : 'road work ahead', '26' : 'signal ahead', \
          '27' : 'pedestrian crossing', '28': 'watch for children', '29': 'bicycle crossing', \
          '30': 'snow', '31': 'animal crossing', '32' : 'end of all restrictions' ,'33' : 'right only', \
          '34': 'left only', '35': 'straight ahead', '36' : 'straight or right', '37' : 'straight or left', \
          '38': 'pass by on right', '39': 'pass by on left', '40': 'round about', '41': 'end of no passing', \
          '42': 'end of truck passing'}

args = [executable, model, test_net, mean, label, image]

out = subprocess.check_output(args)

out_list = (out.splitlines())

index = out_list[1].split()[2]
index = (index.decode()).strip('"')
print (labels[index])
