package uam.so.semaforos;




class Complejo {

	double imaginaria;
	double real;
	
	Complejo(double real, double imaginaria){
		
		this.imaginaria= imaginaria;
		this.real = real;
		
	}

	double getImaginaria() {
		return imaginaria;
	}

	void setImaginaria(double imaginaria) {
		this.imaginaria = imaginaria;
	}

	double getReal() {
		return real;
	}

	public void setReal(double real) {
		this.real = real;
	}
	
	static Complejo suma(Complejo a, Complejo b){
		
		
		return new Complejo(a.getReal()+b.getReal(), a.getImaginaria()+b.getImaginaria());
		
	}
	
	static Complejo mult(Complejo a, Complejo b){
		
		
		return new Complejo((a.getReal()*b.getReal())-(a.getImaginaria()*b.getImaginaria()),(a.getReal()*b.getImaginaria())+(a.getImaginaria()*b.getReal()));
		
	}
	
	static double abs(Complejo a){
		
		return Math.sqrt(Math.pow(a.getReal(), 2.0)+Math.pow(a.getImaginaria(), 2.0));
		
	}
}
