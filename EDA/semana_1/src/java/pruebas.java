import java.io.*;
public class pruebas{
    public static void main(String[] args) {
        pruebas ob = new pruebas(); 
        int arr[] = {64,25,12,22,11}; 
        int count[] = new int[arr.length+1];
        for (int j = 0; j < arr.length; j++)
        {
            System.out.println(j+" "+arr[j]);     
        }

        System.out.println();
        count[0]++;
        for (int j = 0; j < count.length; j++)
        {
            System.out.println(count[j]);     
        }

        //ob.sort(arr,5); 
        //System.out.println("Sorted array"); 
       // ob.printArray(arr); 
        //System.out.println("Hola prros");    
/* 
        File archivo = null;
        FileReader fr = null;
        BufferedReader br = null;
        archivo = new File ("prueba.txt");
        fr = new FileReader (archivo);
        br = new BufferedReader(fr);

         // Lectura del fichero
         String linea;
         while((linea=br.readLine())!=null)
            System.out.println(linea); */
    }
}