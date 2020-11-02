x = 1
if x == 1:
    # indented four spaces
    print("x is 1.")

''' 
f = open('prueba.txt', 'r')
array = []
lineas = f.readlines()
for x in lineas:
    num = x.split()
    array.append(int(num))

for x in array:
    print(x)
 '''

import numpy as np
A=np.loadtxt("prueba.txt",skiprows=0,dtype = "int")
print(A)
for x in A:
    print(x)
print(len(A))

array = []

def leer():
    for i in range(1,len(A)):
        array.append(A[i])
    
leer()
print(array)