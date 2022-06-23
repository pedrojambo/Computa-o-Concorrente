//classe da estrutura de dados (recurso) compartilhado entre as threads
class S {
    // Recurso compartilhado
    private int x;
    // Construtor
    S() {
        this.x = 0;
    }
    // Funcao utilizada pelas threads para incrementar o valor de x
    public void incrementar(int y){
        this.x = this.x + y;
    }
    // Funcao utilizada pelas threads para ler o valor de x
    public int getx(){
        return this.x;
    }
    // Funcao utilizada pelas threads para alterar o valor de x
    public void alterar(int y){
        this.x = y;
    }
}
// Monitor que implementa a logica do padrao leitores/escritores
class LE {
    private int leit, escr;

    // Construtor
    LE() {
        this.leit = 0; //leitores lendo (0 ou mais)
        this.escr = 0; //escritor escrevendo (0 ou 1)
    }

    // Entrada para leitores
    public synchronized void EntraLeitor (int id, int type) {
        //"type" serve para identificacao do tipo de thread na saida do programa
        try {
            while (this.escr > 0) {
                //if (this.escr > 0) {
                System.out.println ("le.T"+type+"Bloqueada("+id+")");
                wait();  //bloqueia pela condicao logica da aplicacao
            }
            this.leit++;  //registra que ha mais um leitor lendo
            System.out.println ("le.T"+type+"Lendo("+id+")");
        } catch (InterruptedException e) { }
    }

    // Saida para leitores
    public synchronized void SaiLeitor (int id, int type) {
        this.leit--; //registra que um leitor saiu
        if (this.leit == 0)
            this.notify(); //libera escritor (caso exista escritor bloqueado)
        System.out.println ("le.T"+type+"Saindo("+id+")");
    }

    // Entrada para escritores
    public synchronized void EntraEscritor (int id, int type) {
        try {
            while ((this.leit > 0) || (this.escr > 0)) {
                //if ((this.leit > 0) || (this.escr > 0)) {
                System.out.println ("le.T"+type+"Bloqueada("+id+")");
                wait();  //bloqueia pela condicao logica da aplicacao
            }
            this.escr++; //registra que ha um escritor escrevendo
            System.out.println ("le.T"+type+"Escrevendo("+id+")");
        } catch (InterruptedException e) { }
    }

    // Saida para escritores
    public synchronized void SaiEscritor (int id, int type) {
        this.escr--; //registra que o escritor saiu
        notifyAll(); //libera leitores e escritores (caso existam leitores ou escritores bloqueados)
        System.out.println ("le.T"+type+"Saindo("+id+")");
    }
}

//Aplicacao--------------------------------------------------------
// Escritor
class T1 extends Thread {
    int id; //identificador da thread
    int delay; //atraso bobo...
    LE monitor; //objeto monitor para coordenar a lógica de execução das threads
    S s; //estrutura contendo o recurso compartilhado

    // Construtor
    T1 (int id, int delayTime, LE m, S s) {
        this.id = id;
        this.delay = delayTime;
        this.monitor = m;
        this.s = s;
    }

    // Método executado pela thread
    public void run () {
        try {
            for (;;) {
                this.monitor.EntraEscritor(this.id, 1);
                this.s.incrementar(1);
                this.monitor.SaiEscritor(this.id, 1);
                sleep(this.delay); //atraso bobo...
            }
        } catch (InterruptedException e) { return; }
    }
}

//--------------------------------------------------------
//T2
class T2 extends Thread {
    int id; //identificador da thread
    int delay; //atraso bobo
    LE monitor; //objeto monitor para coordenar a lógica de execução das threads
    S s; //estrutura contendo o recurso compartilhado

    // Construtor
    T2 (int id, int delayTime, LE m, S s) {
        this.id = id;
        this.delay = delayTime;
        this.monitor = m;
        this.s = s;
    }

    // Método executado pela thread
    public void run () {
        try {
            for (;;) {
                this.monitor.EntraLeitor(this.id, 2);
                System.out.println("Valor de x: "+this.s.getx());
                if(this.s.getx()%2==0){
                    System.out.println("x é par!");
                }
                else{
                    System.out.println("x é ímpar!");
                }
                this.monitor.SaiLeitor(this.id, 2);
                sleep(this.delay);
            }
        } catch (InterruptedException e) { return; }
    }
}

//--------------------------------------------------------
//T3
class T3 extends Thread {
    int id; //identificador da thread
    int delay; //atraso bobo
    LE monitor; //objeto monitor para coordenar a lógica de execução das threads
    S s; //estrutura contendo o recurso compartilhado

    // Construtor
    T3 (int id, int delayTime, LE m, S s) {
        this.id = id;
        this.delay = delayTime;
        this.monitor = m;
        this.s = s;
    }

    // Método executado pela thread
    public void run () {
        double j=777777777.7, i;
        try {
            for (;;) {
                this.monitor.EntraLeitor(this.id, 3);
                System.out.println("Valor de x: "+this.s.getx());
                this.monitor.SaiLeitor(this.id, 3);
                for (i=0; i<100000000; i++) {j=j/2;} //...loop bobo
                this.monitor.EntraEscritor(this.id, 3);
                this.s.alterar(this.id);
                this.monitor.SaiEscritor(this.id, 3);
                sleep(this.delay);
            }
        } catch (InterruptedException e) { return; }
    }
}

//--------------------------------------------------------
// Classe principal
class Aplicacao {
    static final int A = 4;
    static final int B = 3;
    static final int C = 3;

    public static void main (String[] args) {
        // Cria uma instancia do recurso compartilhado
        S s = new S();

        int i;
        LE monitor = new LE();        // Monitor (objeto compartilhado entre leitores e escritores)
        T1[] a = new T1[A];           // Threads T1
        T2[] b = new T2[B];           // Threads T2
        T3[] c = new T3[C];           // Threads T2

        //inicia o log de saida
        System.out.println ("import verificaLE");
        System.out.println ("le = verificaLE.LE()");

        for (i=0; i<A; i++) {
            a[i] = new T1(i+1, (i+1)*500, monitor, s);
            a[i].start();
        }
        for (i=0; i<B; i++) {
            b[i] = new T2(i+1, (i+1)*500, monitor, s);
            b[i].start();
        }
        for (i=0; i<C; i++) {
            c[i] = new T3(i+1, (i+1)*500, monitor, s);
            c[i].start();
        }
    }
}
