from timeit import default_timer

filer = open('arrays.txt', "r")
filew = open("selectionSortTime.txt","w")
#lectura de lineas
lines = []
for line in filer:
    lines.append(line)
filer.close()

def selection_sort(array):  
    for i in range(len(array)-1):
        primer = i
        for j in range(i+1, len(array)):
            if array[primer] > array[j]:
                primer = j

        array[primer], array[i] = array[i], array[primer]

if __name__ == "__main__":
    index = 0
    numArrays = int(lines[index])
    for i in range(numArrays):
        arr = []
        index +=1
        n = int(lines[index])
        index +=1
        aux = lines[index].split(" ")
        for j in range(n):
            arr.append(int(aux[j]))
            
        inicio = default_timer()
        selection_sort(arr)
        fin = default_timer()
        #print(arr)
        filew.writelines([str(n)," ",str(round(((fin-inicio)*1000),3)),"\n"])    
    filew.close()    
    
 """    

    from timer import Timer

filer = open('arraysanti.txt', "r")
filew = open("countingSortTime.txt","w")

#lectura de lineas
lines = []
for line in filer:
    lines.append(line)
filer.close()
#arreglo ordenado
array = []
max = 1000

def counting_sort(arr,n):
    count = [0 for i in range(max+1)]

    for i in range(n):
        count[arr[i]] += 1
 
    for i in range(max):
        count[i+1] = count[i] + count[i+1]

    for i in range(max,0,-1):
        count[i] = count[i-1]
    count[0] = 0
    
    newA = [0 for i in range(n)]

    for i in range(n):
        newA[count[arr[i]]] = arr[i]
        count[arr[i]] += 1
    array = newA


if __name__ == "__main__":
   
    index = 0
    numArrays = int(lines[index])
    for i in range(numArrays):
        arr = []
        index +=1
        n = int(lines[index])
        index +=1
        aux = lines[index].split(" ")
        for j in range(n):
            arr.append(int(aux[j]))
        
        t=Timer(n,filew)   
        t.start()
        counting_sort(arr,n)
        t.stop()
    filew.close() """
    