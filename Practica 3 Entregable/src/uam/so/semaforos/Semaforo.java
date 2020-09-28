package uam.so.semaforos;


public class Semaforo {

	private final int num_semaforo;
	private int contador_usados;

	public Semaforo(int num_semaforo) {
		this.num_semaforo = num_semaforo;
	}

	public synchronized void acquire() {
		while(!(recursoDisponible() && posibleWait())) {
			try {
				wait();
			} catch(InterruptedException e) {
			}
		}

		contador_usados++;
	}

	public synchronized void release() {
		if (contador_usados > 0) {
			contador_usados--;
			notifyAll();
		}
	}

	private boolean recursoDisponible() {
		return contador_usados < num_semaforo;
	}

	private boolean posibleWait() {
		return true;
	}
}
