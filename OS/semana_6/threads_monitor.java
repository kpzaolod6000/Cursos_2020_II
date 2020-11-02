import java.util.*;

public class Teste {
	public static void main(String[] args){
    final Integer i = 3;
		List<Integer> lista = new ArrayList<Integer>();

		Runnable task = () -> {
  			/* Los productores y consumidores interactúan con BoundedBuffer aquí. */

			while(true){
				System.out.println("Solo tengo acceso a variables final");
				System.out.println("Tamaño de la lista: " + lista.size());

				lista.add(5);

				try{
					Thread.sleep(i*1000);
				}
				catch(Exception e){
					System.err.println("No se durmió");
				}

			}
		};
		new Thread(task).start();
	}
}
