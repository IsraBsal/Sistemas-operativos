package uam.so.semaforos;



public class MainSuma {
	static final int MAX_T = 4; 
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Semaforo s = new Semaforo(1);

		Thread[] t = new Thread[MAX_T];
				
		
		for(int i=0;i<MAX_T;i++) {

			t[i]=  new Thread(new PruebaSuma(s, "T"+i));
			t[i].start();
		}
		
		for(int i=0;i<MAX_T;i++){

			try {
				t[i].join();

			} catch (InterruptedException e) {

				System.out.println("Error: en la espera del hilo");
			}
		}
		
		System.out.println("Resultado final con sincronizacion (semaforo):"+PruebaSuma.suma);
		
	}

}
