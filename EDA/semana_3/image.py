import cv2
import numpy as np

def bintodecil(a):
    bnr = bin(a).replace('0b','')
    x = bnr[::-1] #this reverses an array
    while len(x) < 8:
        x += '0'
    bnr = x[::-1]
    return bnr
''' 
def deciltobin(numero_binario):
	numero_decimal = 0 
	for posicion, digito_string in enumerate(numero_binario[::-1]):
    	numero_decimal += int(digito_string) * 2 ** posicion
	return numero_decimal '''
    
#x = np.random.randint(0,5,(500,500))
#img = cv2.imread('',0)
image = cv2.imread("/home/judal/Imágenes/Wallpapers/color.png")
ver= image[415,554]
#ver= image[2000,2000]
print(image.size)
print(len(image))
print(len(image[:,1]))#fila 
print(len(image[1,:]))#columna
rows = len(image[:,1])
column = len(image[:,1])
#print(pixel[0])
np.pixel = []
#k = []
matriz = []
for i in range(10):
    for j in range(10):
        pixel= image[i,j]
        print(pixel)
        for k in range(3):
            #aux = []
            print(bintodecil(pixel[k]))
            numero = int(bintodecil(pixel[k]), 2)
            print(numero)
            #matriz.append(aux)
        #print(matriz)
            

#print(ver) 

'''   
import cv2
import numpy as np

img = cv2.imread('sample.jpg',0)
rows,cols = img.shape
k = []
for i in range(rows):
    for j in range(cols):
        k.append(img[i,j])
print k 
'''