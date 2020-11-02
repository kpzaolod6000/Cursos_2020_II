//package com.ficheros.java;
import java.io.*;
public class counting_sort {
    public static int array[];
    void lectura() {
        File archivo = null;
        FileReader fr = null;
        BufferedReader br = null;
  
        try {
           archivo = new File ("pruebas.txt");
           fr = new FileReader (archivo);
           br = new BufferedReader(fr);
  
           // Lectura del fichero
           String linea;
           //int i = 0;
           int x;
           while((linea=br.readLine())!=null){
               //System.out.println(linea);
               String[] values = linea.split(" ");
               array = new int[values.length-1];//estableciendo el tamaño
               
               for(int j = 0;j<values.length-1;j++){
                   x = Integer.parseInt(values[j+1]);
                   array[j] = x;
   
               }
               //array[i] = values;
               //i++;
            }

            /* for (int j=0; j < array.length ;j++ )
            {  
                System.out.print(array[j]+" ");
            }
            System.out.println(); */

        }
        catch(Exception e){
           e.printStackTrace();
        }finally{ 
           try{                    
              if( null != fr ){   
                 fr.close();     
              }                  
           }catch (Exception e2){ 
              e2.printStackTrace();
           }
        }
     }
    //int[] count_sort(int array[],int new_array[]){
    int[] count_sort(int new_array[]){
        
        int num_max = array[0];
        for (int i = 1; i < array.length; i++)
        {
            if(array[i] > num_max)
                num_max = array[i];
        }
        int count[]=new int[10000+1];//verificar tamaño

        for (int j=0; j < array.length ;j++ )
        {  
            count[array[j]]++;
        }
        for (int i=0; i < num_max ;i++ )//fijar el rango 
        {  
            count[i+1] = count[i] + count[i+1];
        }
        
        for (int i = 0; i < array.length ; i++)
        {
            new_array[count[array[i]]-1] = array[i];
            count[array[i]]--;
        }
        return new_array;
    }

    void print(int new_array[]){
        for(int i=0;i<new_array.length;i++)
            System.out.print(new_array[i]+" "); 
        System.out.println(); 
    }

    public static void main(String[] args) {
        counting_sort sort = new counting_sort(); 
        //int array[] = {5435,8606,9263,5398,3231,6944,3186,1333,1626,245}; 
        sort.lectura();
        int aux[] = new int[array.length];

        long inicio = System.nanoTime();
        int[] new_array = sort.count_sort(aux);  
        long fin = System.nanoTime();
        double dif = (double) (fin - inicio) * (1.0e-6);

        //sort.print(new_array); 
        System.out.println(dif); 
    }
}
