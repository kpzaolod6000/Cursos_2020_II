import java.io.*;//importando clases para entrada y salida (IN OUT)
public class selection_sort {
    int array[];
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
               array = new int[values.length-1];
               
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
    //void select_sort(int array[]){
    void select_sort(){
        int primer;
        int temp;
        for(int i = 0; i < array.length-1; i++)
        {
            primer = i;
            for (int j = i+1; j < array.length; j++)
            {
                if(array[primer] > array[j])
                    primer = j;
            }
            temp = array[primer];
            array[primer] = array[i];
            array[i] = temp;
        }

    }
  
    //void print(int array[]) 
    void print() 
    { 
        for (int i=0; i<array.length; ++i) 
            System.out.print(array[i]+" "); 
        System.out.println(); 
    } 
    public static void main(String[] args) {
        selection_sort sort = new selection_sort();
    /* 
        int array[] = {5435,8606,9263,5398,3231,6944,3186,1333,1626,245}; 
        sort.select_sort(array);  
        sort.print(array); */
        sort.lectura();
        long inicio = System.nanoTime();
        sort.select_sort();
        long fin = System.nanoTime();
        double dif = (double) (fin - inicio) * (1.0e-6);
        //sort.print();

        System.out.println(dif);
    }

}