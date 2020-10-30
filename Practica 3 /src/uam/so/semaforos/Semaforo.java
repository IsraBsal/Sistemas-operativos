package uam.so.semaforos;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.locks.LockSupport;

public class Semaforo {
	private ConcurrentLinkedQueue<Thread> cola = new ConcurrentLinkedQueue<Thread>();
	private int value;

	private Thread hilo=null;

	public Semaforo(int num_semaforo) {
		this.value = num_semaforo;
	}


	public void acquire() throws InterruptedException {
		if(value>0) {
			value--;	
		}
		else {
			//System.out.println("Entre al acquire en el else");
			hilo = Thread.currentThread();
			cola.add(hilo);
			LockSupport.park();

		}
	}

	public void release() {
		if(cola.isEmpty()) {
			value++;
			//System.out.println("Entre al release en el if");
		}
		else {
			//System.out.println("Entre al release en el ELSE");
			hilo=cola.remove();
			LockSupport.unpark(hilo);
		}
	}

}
