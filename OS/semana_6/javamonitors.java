class BoundedBuffer<E>
{
  private static final int BUFFER_SIZE = 5;
  private int count, in, out;
  private E[] buffer;//crea un arreglo de buffer de tipo E
  public BoundedBuffer() {
    count = 0;
    in = 0;
    out = 0;
    buffer = (E[]) new Object[BUFFER_SIZE];
  }
  /* Producers call this method */
  public synchronized void insert(E item) {
  /* See Figure 7.11 */
    while (count == BUFFER_SIZE) {
      try {
        System.out.println("BUFFER FULL, PLEASE WAIT ME");
        wait();/*libera temporalmente el candado haciendo que dicho threads se va  a la cola de espera*/
        /*permitiendo que otro threads tome el control del monitor*/
      }catch (InterruptedException ie){
         System.out.println("Error dislock candado");
      }
    }
    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;
    count++;
    System.out.println("Guardado");
    notify();/*libera el candado del objeto thread quien lo llamo*/
  }

  /* Consumers call this method */
  public synchronized E remove() {
  /* See Figure 7.11 */
    E item;
    while (count == 0) {
      try {
        System.out.println("BUFFER EMPTY, PLEASE WAIT ME");
        wait();
      }catch (InterruptedException ie) {
         System.out.println("Error dislock candado");
      }
    }
    item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    count--;
    notify();/*libera el candado del objeto thread quien lo llamo*/
    /*ademas de eliminar el productor de la cola de espera y luego lo coloca como ejecutable*/
    return item;
  }
}


class Producer implements Runnable{
  private final BoundedBuffer buffer;
  public Producer(BoundedBuffer b)/*ese es un clase de tipo BoundedBuffer<E>*/
  {
    buffer = b;
  }
  public void run(){
    try{
      int i;
      for (i=1 ;i<=6 ;i++ ) {
        buffer.insert(i);
        System.out.println("RUN Producer");
        Thread.sleep(2000);
      }
    }catch (Exception ie) {
        System.out.println("Error function Producer");
    }
  }
}

class Consumer implements Runnable{
  private final BoundedBuffer buffer;

  public Consumer(BoundedBuffer b)/*ese es un clase de tipo BoundedBuffer<E>*/
  {
    buffer = b;
  }

  public void run(){
    try{
      int i;
      for (i=1 ;i<=6 ;i++ ) {
        System.out.println("Dato Consumido "+buffer.remove());
        Thread.sleep(2000);
      }
    }catch(Exception e) {
        System.out.println("Error function Producer");
    }
  }
}

class PCMain{
  public static void main(String[] args) {
      System.out.println("program starting");
      BoundedBuffer buffer = new BoundedBuffer();
      Thread producer = new Thread(new Producer(buffer));
      Thread consumer = new Thread(new Consumer(buffer));
      producer.start();
      consumer.start();

      try {
        producer.join();
        /*Ahora, si su hilo principal
        ejecuta esta línea T1.join ()//que es producer
        (el hilo principal ejecuta lo que haya escrito en el método principal)
        luego el hilo principal esperará a que el hilo T1 termine su ejecución*/
        //consumer.join();
        //consumer.interrupt();
      }catch (InterruptedException ie) {}
      System.out.println("End of Program");
  }
}

//*************** INFORMACION *****************//

/*Cuando invocamos el método join ()
en un hilo, el hilo que llama entra en un
estado de espera. Permanece en un estado de
espera hasta que termina el hilo referenciado.*/

//********************************************//
