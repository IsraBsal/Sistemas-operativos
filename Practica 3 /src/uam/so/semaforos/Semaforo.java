package uam.so.semaforos;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.LockSupport;

public class Semaforo {
	private ConcurrentLinkedQueue<Thread> cola = new ConcurrentLinkedQueue<Thread>();
	private final AtomicInteger value;
	private final int Num_permisos;

	private Thread propietario=null;


	public Semaforo(int num_semaforo) {
		value = new AtomicInteger(num_semaforo);
		Num_permisos=num_semaforo;
	}

	public void acquire() {
		boolean interrumpido = false;
		Thread hilo = Thread.currentThread();
		cola.add(hilo);
		//Dormimos a todos los procesos si no soy el del principio de la cola o no hay permisos
		while (cola.peek() !=hilo || value.getAndDecrement()<Num_permisos) { 
			value.getAndIncrement(); //Para no llegar a valores negativos y ciclarme
			LockSupport.park();
			//System.out.println("Thread: "+hilo.getId()+"-> Lock 1");
			if (Thread.interrupted()) // Verifica si el hilo fue interumpido
				interrumpido= true;
			
		}
		//Quitamos al hilo que esta al principio de la cola para que trabaje
		propietario=cola.remove(hilo);
		LockSupport.unpark(propietario);
		if (interrumpido)          // reassert interrupt status on exit
			hilo.interrupt(); 
	}

	public void release() {
		LockSupport.unpark(cola.peek());
		value.getAndIncrement();
	}



}
