
import numpy as np
A=np.loadtxt("pruebas.txt",skiprows=0,dtype = "int")
#array = A;
array = []

def leer():
    for i in range(1,len(A)):
        array.append(A[i])

leer()#ojo para establecer el tamaño de new_array
#array = [5435,8606,9263 ,5398, 3231 ,6944, 3186, 1333 ,1626 ,245]
new_array = [0 for i in range(len(array))]

def counting_sort():
    num_max = array[0]
    for i in range(len(array)):
        if array[i] > num_max :
            num_max = array[i]

    counts = [0 for i in range(num_max+1)]

    for i in range(len(array)):
        counts[array[i]] = counts[array[i]]+1

    for i in range(num_max):#mismo tamaño
        counts[i+1] = counts[i] + counts[i+1]

    for i in range(len(array)):
        new_array[counts[array[i]]-1] = array[i];
        counts[array[i]] = counts[array[i]]-1


print(array)
counting_sort()
print(new_array)