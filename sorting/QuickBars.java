/*************************************************************************
 *  Compilation:  javac QuickBars.java
 *  Execution:    java QuickBars M N
 *  Dependencies: StdDraw.java
 *  
 *  Sort N random real numbers between 0 and 1 using quicksort with
 *  cutoff to insertion sort and median-of-3 partitioning.
 *
 *  Visualize the results by ploting bars with heights proportional
 *  to the values.
 *
 *  % java QuickBars 1000 75
 *
 *  Comments
 *  --------
 *   - suggest removing the 10% default StdDraw border
 *   - if image is too large, it may not display properly but you can
 *     still save it to a file
 *
 *************************************************************************/


public class QuickBars {
    private static int ROWS;
    private static int row = 0;
    private static int VERTICAL = 70;
    private static int CUTOFF = 8;

    // partition the subarray a[lo .. hi] by returning an index j
    // so that a[lo .. j-1] <= a[j] <= a[j+1 .. hi]
    private static int partition(double[] a, int lo, int hi) {
        int i = lo;
        int j = hi + 1;
        double v = a[lo];
        while (true) { 

            // find item on lo to swap
            while (less(a[++i], v))
                if (i == hi) break;

            // find item on hi to swap
            while (less(v, a[--j]))
                if (j == lo) break;      // redundant since a[lo] acts as sentinel

            // check if pointers cross
            if (i >= j) break;

            exch(a, i, j);
        }

        // put v = a[j] into position
        exch(a, lo, j);

        // with a[lo .. j-1] <= a[j] <= a[j+1 .. hi]
        return j;
    }

    public static void sort(double[] a) {
        // StdRandom.shuffle(a);
        show(a, 0, 0, -1, a.length-1);
        sort(a, 0, a.length - 1);
        show(a, 0, 0, -1, a.length-1);
    }

    // quicksort the subarray from a[lo] to a[hi]
    private static void sort(double[] a, int lo, int hi) { 
        // cutoff to insertion sort
        int N = hi - lo + 1;
        if (N <= CUTOFF) {
            insertionSort(a, lo, hi);
            // show(a, lo, -1, -1, hi);
            return;
        }

        int m = median3(a, lo, lo + N/2, hi);
        exch(a, m, lo);

        int j = partition(a, lo, hi);
        show(a, lo, j, j, hi);
        sort(a, lo, j-1);
        sort(a, j+1, hi);
    }

    // sort from a[lo] to a[hi] using insertion sort
    private static void insertionSort(double[] a, int lo, int hi) {
        for (int i = lo; i <= hi; i++)
            for (int j = i; j > lo && less(a[j], a[j-1]); j--)
                exch(a, j, j-1);
    }


    // return the index of the median element among a[i], a[j], and a[k]
    private static int median3(double[] a, int i, int j, int k) {
        return (less(a[i], a[j]) ?
               (less(a[j], a[k]) ? j : less(a[i], a[k]) ? k : i) :
               (less(a[k], a[j]) ? j : less(a[k], a[i]) ? k : i));
    }


    private static boolean less(double v, double w) {
        return v < w;
    }

    private static void exch(double[] a, int i, int j) {
        double t = a[i];
        a[i] = a[j];
        a[j] = t;
    }

    // draw one row of trace
    private static void show(double[] a, int lo, int lt, int gt, int hi) {
        double y = ROWS - row - 1;
        for (int k = 0; k < a.length; k++) {
            if      (k < lo)             StdDraw.setPenColor(StdDraw.LIGHT_GRAY);
            else if (k > hi)             StdDraw.setPenColor(StdDraw.LIGHT_GRAY);
            else if (k >= lt && k <= gt) StdDraw.setPenColor(StdDraw.BOOK_RED);
            else                         StdDraw.setPenColor(StdDraw.BLACK);
            StdDraw.filledRectangle(k, y + a[k]*.25, .25, a[k]*.25);
        }
        row++;
    }

    public static void main(String[] args) {
        int M = Integer.parseInt(args[0]);
        int N = Integer.parseInt(args[1]);
        double[] a = new double[N];
        double[] b = new double[N];
        for (int i = 0; i < N; i++) {
            a[i] = ((int) (1 + Math.random() * M)) / (double) M;
            b[i] = a[i];
        }


        // precompute the number of rows
        StdDraw.show(0);
        ROWS = 0;
        sort(b);
        ROWS = row;
        row = 0;
        StdDraw.clear();

        StdDraw.setCanvasSize(800, ROWS*VERTICAL);
        StdDraw.show(0);
        StdDraw.square(.5, .5, .5);
        StdDraw.setXscale(-1, N);
        StdDraw.setYscale(-0.5, ROWS);
        StdDraw.show(0);
        sort(a);
        StdDraw.show(0);
    }
}
