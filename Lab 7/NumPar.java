import java.util.ArrayList;

class S {
    //recurso compartilhado
    private ArrayList<Integer> vetor;
    private int x;
    //construtor
    public S(ArrayList<Integer> V) {
        this.vetor=V;
        this.x=0;
    }
    //operacao de leitura sobre o recurso compartilhado
    public int get(int i){
        return this.vetor.get(i);
    }
    //operacao para incremento do valor de numeros pares
    public synchronized int par(){
        return this.x++;
    }
    //operacao para retorno do numero de pares
    public int getPar(){
        return this.x;
    }
    //operacao para receber tamanho da lista do arraylist
    public int tamanho(){
        return this.vetor.size();
    }
}


class T extends Thread {
    //identificador da thread
    private int id;
    //objeto compartilhado com outras threads
    S s;
    //construtor
    public T(int tid, S s){
        this.id = tid;
        this.s = s;
    }

    //metodo main da thread
    public void run(){
        for(int i=id; i < this.s.tamanho(); i+=NumPar.N){
            if(((this.s.get(i))%2)==0){
                s.par();
            }
        }
    }
}


public class NumPar {
    static final int N = 4;
    static final int TAM = 10000;

    public static void main(String[] args) {
        //reserva espaço para um vetor de threads
        Thread[] threads = new Thread[N];
        //cria arraylist que sera utilizada
        ArrayList<Integer> x = new ArrayList<Integer>();
        //inicia arraylist
        for(int i=0; i<TAM; i++){
            x.add(i);
        }
        //cria uma instancia do recurso compartilhado
        S s = new S(x);
        //cria as threads da aplicacao
        for (int i=0; i<threads.length;i++){
            threads[i] = new T(i, s);
        }
        //inicia as threads
        for (int i=0; i<threads.length; i++){
            threads[i].start();
        }
        //espera pelo termino de todas as threads
        for (int i=0; i<threads.length; i++){
            try{ threads[i].join(); } catch (InterruptedException e) {return;}
        }

        System.out.println("Quantidade de pares: "+ s.getPar());
    }
}
