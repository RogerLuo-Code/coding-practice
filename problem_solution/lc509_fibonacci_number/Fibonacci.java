public class Fibonacci {
    private Integer[] cache;
    
    public int fibRecursive(int N) {
        if (N <= 1)
            return N;
        else {
            cache = new Integer[N + 1];
            cache[0] = 0;
            cache[1] = 1;
            return memoize(N);
        }    
    }
    
    private int memoize(int N) {
        if (cache[N] != null)
            return cache[N];
        else {
            cache[N] = memoize(N - 1) + memoize(N - 2);
            return cache[N];
        }      
    }

    public int fibRecursiveFast(int N) {
        if (N <= 1)
            return N;
        else {
            // int nCache = (int)(Math.log(N) / Math.log(2));
            cache = new Integer[N + 1];
            cache[0] = 0;
            cache[1] = 1;
            return memoizeFast(N);
        }   
    }
    
    private int memoizeFast(int N) {
        if (cache[N] != null)
            return cache[N];
        else {
            if (N % 2 == 0) {
                int m = N/2;
                cache[N] = (2*memoizeFast(m - 1) + memoizeFast(m))*memoizeFast(m);
                return cache[N];
            }
            else {
                int m = (N + 1)/2;
                cache[N] = memoizeFast(m - 1)*memoizeFast(m - 1) + memoizeFast(m)*memoizeFast(m);
                return cache[N];
            }
        }
    }
    
    public int fibIterative(int N) {
        if (N <= 1)
            return N;
        
        int fibPrev1 = 1;
        int fibPrev2 = 0;
        int fibCurr = 0; 
        
        for (int k = 2; k <= N; k++) {
            fibCurr = fibPrev1 + fibPrev2;
            fibPrev2 = fibPrev1;
            fibPrev1 = fibCurr;
        }
        
        return fibCurr;
    }

    public int fibMatrix(int N) {
        // Using matrix exponentiation
        // [[1, 1], [1, 0]]^n = [[fib(n+1), fib(n)], [fib(n), fib(n-1)]]
        if (N <= 1)
            return N;
        
        int[][] a = new int[][]{{1, 1}, {1, 0}};
        int[][] result = matrixPow(a, N);
        
        return result[1][0];
    }

    public int fibMatrixIterative(int N) {
        // Using matrix exponentiation
        // [[1, 1], [1, 0]]^n = [[fib(n+1), fib(n)], [fib(n), fib(n-1)]]
        if (N <= 1)
            return N;
        
        int[][] a = new int[][]{{1, 1}, {1, 0}};
        int[][] result = matrixPowIterative(a, N);
        
        return result[1][0];
    }

    private int[][] matrixPow(int[][] a, int n) {
        // assume n > 1
        if (a.length != a[0].length)
            return new int[0][];

        // Base case
        if (n == 1) {
            return a;    
        }

        int[][] half = matrixPow(a, n/2);
        if (n%2 == 0)
            return matrixMultiply(half, half);
        else
            return matrixMultiply(matrixMultiply(half, half), a);
    }

    private int[][] matrixPowIterative(int[][] a, int n) {
        // assume n > 1
        if (a.length != a[0].length)
            return new int[0][];

        int aRow = a.length;
        int[][] result = new int[aRow][aRow];
        for (int i = 0; i < aRow; i++){
            result[i][i] = 1;
        }
        
        if (n == 0)
            return result;

        if (n == 1)
            return a;

        for (; n > 0; n = n/2){
            if ((n & 0x1) == 1)
                result = matrixMultiply(result, a);
            
            a = matrixMultiply(a, a);
        }
        
        return result;
    }

    private int[][] matrixMultiply(int[][] a, int[][] b) {
        if (a == null || a.length == 0 || b == null || b.length == 0)
            return new int[0][];

        int aRow = a.length;
        int aCol = a[0].length;
        int bRow = b.length;
        int bCol = b[0].length;
        int[][] result = new int[aRow][bCol];

        // Requirement for matrix multiplication
        if (aCol != bRow)
            return new int[0][];

        // Matrix multiplication element by element    
        for (int i = 0; i < aRow; i++) {
            for (int j = 0; j < bCol; j++) {
                for (int k = 0; k < aCol; k++) {
                    result[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        return result;
    }

    public static void main(String[] args) {
        int[][] fibMatrix = new int[][]{{1, 1}, {1, 0}};
        Fibonacci fib = new Fibonacci();
        int[][] result = fib.matrixPow(fibMatrix, 6);
    }
    
}