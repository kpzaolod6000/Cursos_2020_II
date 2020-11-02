
class Producer implements Runnable{
  private int count = 0;
  public synchronized void suma(){
    int n = count;
    count = n+1;
    System.out.println("I am a thread "+count);
    try{
      Thread.sleep(2000);
    }catch (InterruptedException ie) {;}
    notify();
  }
  public void run(){
    suma();
  }
  public static void main(String[] args) {
    //Runnable ru = new Task();
    Thread worker = new Thread(new Producer());
    worker.start();
    Thread worker1 = new Thread(new Producer());
    worker1.start();

    /*try{
      worker.join();
    }catch (InterruptedException ie) {;}*/
  }

}
