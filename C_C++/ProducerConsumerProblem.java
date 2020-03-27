class Buffer {
    int[] buf;
    int size;
    int count; // Bounded Buffer에 들어가있는 개수
    int in; // Buffer을 in(초깃값 : 0)
    int out;

    Buffer(int size) {
        buf = new int[size]; // Bounded Buffer(유한 크기)
        this.size = size;
        count = in = out = 0;
    }

    void insert(int item) {
        while (count == size) {
            // buffer is full
        }
        // buffer is !full
        buf[in] = item;
        in = (in + 1) % size;
        count++;
    }

    void remove() {
        while (count == 0) {
            // buffer is empty
        }
        int item = buf[out];
        out = (out + 1) % size;
        count--;
        return item;
    }

}

class Producer extends Thread {
    Buffer b;
    int N;

    Producer(Buffer b, int N) {
        this.b = b;
        this.N = N;
    }

    public void run() {
        for (int i = 0; i < N; i++)
            b.insert(i);
    }
}

class Consumer extends Thread {
    Buffer b;
    int N;

    Consumer(Buffer b, int N) {
        this.b = b;
        this.N = N;
    }

    public void run() {
        int item;
        for (int i = 0; i < N; i++)
            item = b.remove();
    }
}

class Test {
    public static void main(String[] args) {
        Buffer b = new Buffer(100);
        Producer p = new Producer(b, 10000); // 생산해서 넣고.. 10000번 반복
        Consumer c = new Consumer(b, 10000); // 10000번 소비
        p.start();
        c.start();
        try {
            p.join();
            c.join();
        } catch (InterruptedException e) {
        }
        System.out.println("Number of items in the buffer is " + b.count); // buf 몇개 남았는가. 정상적으로 동작했다면 0이 나와야 정상.
        // 동기화가 되지 않으면 0이 나오지 않음
    }
}