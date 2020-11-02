#array = [5435,8606,9263 ,5398, 3231 ,6944, 3186, 1333 ,1626 ,245]

import numpy as np
from timeit import default_timer

A=np.loadtxt("pruebas.txt",skiprows=0,dtype = "int")
#array = A;
array = []

def leer():
    for i in range(1,len(A)):
        array.append(A[i])


def selection_sort(array):  
    for i in range(len(array)-1):
        primer = i
        for j in range(i+1, len(array)):
            if array[primer] > array[j]:
                primer = j

        array[primer], array[i] = array[i], array[primer]

leer()
#print(array)
inicio = default_timer()
selection_sort(array)
fin = default_timer()

#print(array)
print((fin - inicio))