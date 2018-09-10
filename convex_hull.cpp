// convexHull

// 2D version
#define DataType double
#define MAX_SIZE
typointedef struct { DataType x, y; } POINT;
POINT S[MAX_SIZE + 1];  // 模拟堆栈S,保存凸包上的点
POINT POINT[MAX_SIZE + 1];
double Distance(POINT a, POINT b)  // a和b之间的距离的平方
{
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
double cross(POINT point0, POINT point1, POINT point2) {
    return (point1.x - point0.x) * (point2.y - point0.y) -
           (point2.x - point0.x) * (point1.y - point0.y);
}  // 叉积,判断point2在point0point1向量的哪一侧
bool cmpoint(POINT a, POINT b) {
    double m;
    m = cross(point[0], a, b);
    if (m > 0)
        return 1;
    else if (0 == m && (Distance(point[0], a) < Distance(point[0], b)))
        return 1;
    else
        return 0;
}
void GrahamScan_2D()  // Graham Scan只能用于2D情况，时间复杂度O(nlogn)
{
    POINT temp, p = point[0];
    int pos = 0;
    for (int i = 1; i < n; i++)
        if ((point[i].y < point.y) ||
            (point[i].y == point.y && point[i].x < point.x)) {
            p = point[i];
            pos = i;
        }
    tempoint = point[0];
    point[0] = point[pos];  // 找出y最小的点中x最小的点
    point[pos] = temp;
    sort(point + 1, point + n, cmpoint);  //复杂度主要在于排序，O(n*log n)
    point[n] = point[0];
    S[0] = point[0];
    S[1] = point[1];
    int top = 1;
    for (int i = 2; i <= n; ++i) {
        while (top >= 1 && cross(S[top - 1], S[top], point[i]) <
                               0)  // cross返回值为0也可以包括进去，视情况而定
            top--;                 //出栈
        S[++top] = point[i];  // POINT[i]入栈
    }
    return top;  // the number of POINTs in S[],S[top]和S[0]重复
}  // Graham Scan

bool ccmp(POINT a, POINT b) {
    if (a.x < b.x) return 1;
    if (a.x == b.x)
        return a.y < b.y;
    else
        return 0;
}

int chainHull_2D()  // simple implementation,时间复杂度O(nlogn)
{
    // sorted by increasing x and y-coordinates
    sort(point, point + MAX_SIZE + 1, ccmp);
    // Build lower hull
    int top = -1;
    for (int i = 0; i < n; i++) {
        while (top >= 1 && cross(S[top - 1], S[top], point[i]) <=
                               0)  //加等于号很重要!保证凸包顶点的正确性
            top--;
        S[++top] = point[i];
    }
    // Build upper hull
    int t = top;
    for (int i = n - 2; i >= 0; i--) {
        while (top >= t && cross(S[top - 1], S[top], point[i]) <=
                               0)  //加等于号很重要!保证凸包顶点的正确性
            top--;
        S[++top] = point[i];
    }
    return top;
}  // chain Hull 2D

int chainHull_2D()  // A formal way,时间复杂度O(nlogn)
{
    sort(point, point + MAX_SIZE + 1,
         ccmp);  // sorted by increasing x and y-coordinates
    int minmin = 0, minmax, i, top = -1;
    DataType xmin = point[0].x;
    for (i = 1; i <= MAX_SIZE; i++)
        if (point[i].x != xmin) break;
    minmax = i - 1;
    if (minmax == MAX_SIZE) {  // degenerate case: all x-coords == xmin
        S[++top] = point[minmin];
        if (point[minmax].y != point[minmin].y)  // a  nontrivial segment
            S[++top] = point[minmax];
        S[++top] = point[minmin];  // add polygon endpoint
        return top;
    }

    // Get the indices of points with max x-coord and min|max y-coord
    int maxmin, maxmax = MAX_SIZE;
    DataType xmax = point[MAX_SIZE].x;
    for (i = MAX_SIZE - 1; i >= 0; i--)
        if (point[i].x != xmax) break;
    maxmin = i + 1;

    // Compute the lower hull on the stack H
    S[++top] = point[minmin];  // push  minmin point onto stack
    i = minmax;
    while (++i <= maxmin) {
        // the lower line joins point[minmin]  with P[maxmin]
        if (cross(S[top], point[maxmin], point[i]) >= 0 && i < maxmin)
            continue;  // ignore P[i] above or on the lower line

        while (top > 0)  // there are at least 2 points on the stack
        {
            // test if  point[i] is left of the line at the stack top
            if (cross(S[top - 1], S[top], point[i]) > 0)
                break;  // P[i] is a new hull  vertex
            else
                top--;  // pop top point off  stack
        }
        S[++top] = point[i];  // push point[i] onto stack
    }

    // Next, compute the upper hull on the stack H above  the bottom hull
    if (maxmax != maxmin)          // if  distinct xmax points
        S[++top] = point[maxmax];  // push maxmax point onto stack
    int bot = top;                 // the bottom point of the upper hull stack
    i = maxmin;
    while (--i >= minmax) {
        // the upper line joins point[maxmax]  with point[minmax]
        if (cross(S[top], point[minmax], point[i]) >= 0 && i > minmax)
            continue;  // ignore point[i] below or on the upper line

        while (top > bot)  // at least 2 points on the upper stack
        {
            // test if  point[i] is left of the line at the stack top
            if (cross(S[top - 1], S[top], point[i]) > 0)
                break;  // point[i] is a new hull  vertex
            else
                top--;  // pop top point off  stack
        }
        S[++top] = point[i];  // push point[i] onto stack
    }
    if (minmax != minmin)
        S[++top] = point[minmin];  // push  joining endpoint onto stack
    return top;
}
// Marriage-before-Conquest不知道是什么,见Algorithm_Papers吧，算法比较高端，不过实现起来稍微麻烦些

// 3D version
