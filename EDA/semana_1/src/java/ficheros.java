import java.io.*;//importando clases para entrada y salida (IN OUT)
public class ficheros {
    int array[];
    void lectura() {
        File archivo = null;
        FileReader fr = null;
        BufferedReader br = null;
  
        try {
           archivo = new File ("prueba.txt");
           fr = new FileReader (archivo);
           br = new BufferedReader(fr);
  
           // Lectura del fichero
           String linea;
           //int i = 0;
           int x;
           while((linea=br.readLine())!=null){
               System.out.println(linea);
               String[] values = linea.split(" ");
               array = new int[values.length-1];
               
               for(int j = 0;j<values.length-1;j++){
                   x = Integer.parseInt(values[j+1]);
                   array[j] = x;
   
               }
               //array[i] = values;
               //i++;
            }

            for (int j=0; j < array.length ;j++ )
            {  
                System.out.print(array[j]+" ");
            }
            System.out.println();

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

     public static void main(String[] args) {
        ficheros sort = new ficheros();
        sort.lectura();
    }
    
}