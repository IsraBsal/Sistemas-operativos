package uam.so.semaforos;



public class PruebaSuma implements Runnable {
	static final int N=200000;
	static int suma=0;
	private String nombre; 
	private Semaforo s=null;

	public PruebaSuma( Semaforo s, String n) 
	{ 
		this.s = s; 
		nombre = n; 
	}

	public void run() 
	{ 
		System.out.println("Hilo: "+nombre);
		for(int i=0;i<N;i++)
		{ 
			s.acquire();//signal


			suma++;
			try {
				Thread.sleep(0);
			} catch (InterruptedException e) {

				e.printStackTrace();
			} 


			s.release();


		} 

	}






}
