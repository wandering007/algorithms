/*************************************************************************
 *  Compilation:  javac Quick3wayBars.java
 *  Execution:    java Quick3wayBars M N
 *  Dependencies: StdDraw.java
 *  
 *  Sort N random real numbers between 0 and 1 using 3-way quicksort.
 *
 *  Visualize the results by ploting bars with heights proportional
 *  to the values.
 *
 *  % java Quick3wayBars 6 100
 *
 *  Comments
 *  --------
 *   - suggest removing the 10% default StdDraw border
 *   - if image is too large, it may not display properly but you can
 *     still save it to a file
 *
 *************************************************************************/

import java.util.TreeSet;

public class Quick3wayBars {
    private static int ROWS;
    private static int row = 0;
    private static int VERTICAL = 70;

    public static void sort(double[] a) {
        // StdRandom.shuffle(a);
        show(a, 0, 0, -1, a.length-1);
        sort(a, 0, a.length - 1);
        show(a, 0, 0, -1, a.length-1);
    }

    private static void sort(double[] a, int lo, int hi) {
        if (hi == lo) show(a, lo, lo, lo, lo);
        if (hi <= lo) return;
        int lt = lo, gt = hi;
        double v = a[lo];
        int i = lo;
        while (i <= gt) 
            if      (less(v, a[i])) exch(a, i, gt--);
            else if (less(a[i], v)) exch(a, lt++, i++);
            else                    i++;
        show(a, lo, lt, gt, hi);
        sort(a, lo, lt - 1);
        sort(a, gt + 1, hi);
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
        for (int i = 0; i < N; i++) {
            a[i] = ((int) (1 + Math.random() * M)) / (double) M;
        }

        // how many distinct values
        TreeSet<Double> set = new TreeSet<Double>();
        for (int i = 0; i < N; i++)
            set.add(a[i]);
        ROWS = set.size() + 2;

        // number of rows should be number of distinct entries + 2
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