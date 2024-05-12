// insertion sort
#include <iostream>
using namespace std;

void insertion_sort (int a[], int n)
{
    int i, j, key;
    for (i = 1; i < n; i++)
    {
        key = a[i];
        j = i - 1;
        while (j >= 0 && key < a[j])
        {
            a[j + 1] = a [j];
            j = j - 1;
        }
        a[j + 1] = key;
    }
}

int main ()
{
    cout << "Enter number of Elements in array : ";
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++)
    {
        cout << "Element ["<<i+1<<"]: ";
        cin >> a[i];
    }

    cout << "Inputted Array : ";
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;

    insertion_sort(a, n);

    cout << "Sorted Array : ";
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}



//selection sort
#include <iostream>
using namespace std;

void selection_sort (int a[], int n)
{
    int i, j, least;
    for (i = 0; i < n - 1; i++)
    {
        least = i;
        for (j = i + 1; j < n; j++)
        {
            if (a[j] < a[least])
            {
                least = j;
            }
        }
        if (i != least)
        {
            swap (a[i], a[least]);
        }
    }
}

int main ()
{
    cout << "Enter number of Elements in array : ";
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++)
    {
        cout << "Element ["<<i+1<<"]: ";
        cin >> a[i];
    }

    cout << "Inputted Array : ";
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    
    selection_sort(a, n);

    cout << "Sorted Array : ";
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}


//bubble sort
#include <iostream>
using namespace std;

void bubble_sort (int a[], int n, int &c)
{
    bool flag = true;
    int i, j;
    for (i = 0; i < n - 1 && flag; i++)
    {
        for (j = n - 1, flag = false; j > i; j--)
        {
            c++;
            if (a[j] < a[j - 1])
            {
                swap (a[j], a[j - 1]);
                flag = true;
            }
        }
    }
}

int main ()
{
    cout << "Enter number of Elements in array : ";
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++)
    {
        cout << "Element ["<<i+1<<"]: ";
        cin >> a[i];
    }

    cout << "Inputted Array : ";
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    
    int c = 0;
    bubble_sort(a, n, c);

    cout << "Sorted Array : ";
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    cout << "Total Comparisons : " << c << endl; 
    return 0;
}


//merge sort

#include <iostream>
#include <climits>
using namespace std;

void merge(int a[], int beg, int mid, int end)
{
    int n1 = mid - beg + 1;
    int n2 = end - mid;

    int L[n1 + 1], R[n2 + 1];

    for (int i = 0; i < n1; i++)
    {
        L[i] = a[beg + i];
    }
    for (int j = 0; j < n2; j++)
    {
        R[j] = a[mid + j + 1];
    }
    L[n1] = INT_MAX;
    R[n2] = INT_MAX;

    int i = 0, j = 0;
    for (int k = beg; k <= end; k++)
    {
        if (L[i] <= R[j])
        {
            a[k] = L[i];
            i++;
        }
        else
        {
            a[k] = R[j];
            j++;
        }
    }
}

void merge_sort(int a[], int beg, int end)
{
    if (beg < end)
    {
        int mid = (beg + end) / 2;
        merge_sort(a, beg, mid);
        merge_sort(a, mid + 1, end);
        merge(a, beg, mid, end);
    }
}

int main ()
{
    cout << "Enter number of Elements in array : ";
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++)
    {
        cout << "Element ["<<i+1<<"]: ";
        cin >> a[i];
    }

    cout << "Inputted Array : ";
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
   
    merge_sort(a, 0, n);

    cout << "Sorted Array : ";
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}

//heap sort

#include <iostream>
using namespace std;

void max_heapify(int A[], int i, int heapsize) {
    int largest;
    int L = 2 * i + 1;
    int R = 2 * i + 2;

    if (L < heapsize && A[L] > A[i]) {
        largest = L;
    } else {
        largest = i;
    }

    if (R < heapsize && A[R] > A[largest]) {
        largest = R;
    }

    if (largest != i) {
        swap(A[i], A[largest]);
        max_heapify(A, largest, heapsize);
    }
}

void build_max_heap(int A[], int length) {
    for (int i = length / 2 - 1; i >= 0; i--) {
        max_heapify(A, i, length);
    }
}

void heap_sort(int A[], int length) {
    build_max_heap(A, length);
    for (int i = length - 1; i > 0; i--) {
        swap(A[0], A[i]);
        max_heapify(A, 0, i);
    }
}

int main() {
    cout << "Enter number of Elements in array : ";
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++) {
        cout << "Element [" << i + 1 << "]: ";
        cin >> a[i];
    }

    cout << "Inputted Array : ";
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    heap_sort(a, n);

    cout << "Sorted Array : ";
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}


//quick sort

#include <iostream>
using namespace std;

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = partition(arr, low, high);
        quick_sort(arr, low, pivot - 1);
        quick_sort(arr, pivot + 1, high);
    }
}

int main() {
    cout << "Enter number of Elements in array : ";
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++) {
        cout << "Element [" << i + 1 << "]: ";
        cin >> a[i];
    }

    cout << "Inputted Array : ";
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    quick_sort(a, 0, n - 1);

    cout << "Sorted Array : ";
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}


//radix sort

#include <iostream>
#include <vector>
using namespace std;

int findMax(int arr[], int n) {
    int max_element = arr[0];

    for (int i = 1; i < n; i++) {
        if (arr[i] > max_element) {
            max_element = arr[i];
        }
    }

    return max_element;
}

void countsort(int A[], int B[], int n, int exp) {
    int C[10] = {0};

    for (int j = 0; j < n; j++) {
        C[(A[j] / exp) % 10]++;
    }

    for (int i = 1; i < 10; i++) {
        C[i] += C[i - 1];
    }

    for (int j = n - 1; j >= 0; j--) {
        B[C[(A[j] / exp) % 10] - 1] = A[j];
        C[(A[j] / exp) % 10]--;
    }
}

void radixsort(int arr[], int n) {
    int max_element = findMax(arr, n);

    for (int exp = 1; exp <= max_element; exp *= 10) {
        int output[n];
        countsort(arr, output, n, exp);
        for (int i = 0; i < n; i++) {
            arr[i] = output[i];
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    radixsort(arr.data(), n);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}


// count sort

// Counting sort in C++ programming

#include <iostream>
using namespace std;

void countSort(int array[], int size) {
  // The size of count must be at least the (max+1) but
  // we cannot assign declare it as int count(max+1) in C++ as
  // it does not support dynamic memory allocation.
  // So, its size is provided statically.
  int output[10];
  int count[10];
  int max = array[0];

  // Find the largest element of the array
  for (int i = 1; i < size; i++) {
    if (array[i] > max)
      max = array[i];
  }

  // Initialize count array with all zeros.
  for (int i = 0; i <= max; ++i) {
    count[i] = 0;
  }

  // Store the count of each element
  for (int i = 0; i < size; i++) {
    count[array[i]]++;
  }

  // Store the cummulative count of each array
  for (int i = 1; i <= max; i++) {
    count[i] += count[i - 1];
  }

  // Find the index of each element of the original array in count array, and
  // place the elements in output array
  for (int i = size - 1; i >= 0; i--) {
    output[count[array[i]] - 1] = array[i];
    count[array[i]]--;
  }

  // Copy the sorted elements into original array
  for (int i = 0; i < size; i++) {
    array[i] = output[i];
  }
}

// Function to print an array
void printArray(int array[], int size) {
  for (int i = 0; i < size; i++)
    cout << array[i] << " ";
  cout << endl;
}

// Driver code
int main() {
  int array[] = {4, 2, 2, 8, 3, 3, 1};
  int n = sizeof(array) / sizeof(array[0]);
  countSort(array, n);
  printArray(array, n);
}


// bfs

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void BFS(vector<vector<int>>& graph, int start) {
    int numVertices = graph.size();
    vector<bool> discovered(numVertices, false);
    queue<int> L;
    L.push(start);
    discovered[start] = true;

    int traversalOrder[numVertices]; 
    int traversalIndex = 0; 

    while (!L.empty()) {
        int u = L.front();
        L.pop();
        traversalOrder[traversalIndex++] = u; 

        for (int v : graph[u]) {
            if (!discovered[v]) {
                discovered[v] = true;
                cout << "Edge: (" << u << "," << v << ")" << endl;
                L.push(v);
            }
        }
    }
    cout << "BFS Traversal: ";
    for (int i = 0; i < traversalIndex; ++i) {
        cout << traversalOrder[i] << " ";
    }
    cout << endl;
}

int main() {
    vector<vector<int>> graph = {
        {1, 2},     
        {0, 3, 4}, 
        {0, 4, 5},  
        {1},       
        {1, 2},    
        {2}
    };

    int startVertex = 0;

    cout << "BFS Traversal starting from vertex " << startVertex << ":\n";
    BFS(graph, startVertex);

    return 0;
}


//dfs

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<int> DFS(vector<vector<int>>& adjList, int source) {
    int n = adjList.size();
    vector<bool> explored(n, false); 
    vector<int> parent(n, -1); 

    stack<int> S; 
    S.push(source); 

    cout << "DFS Traversal: ";

    while (!S.empty()) {
        int u = S.top();
        S.pop();

        if (!explored[u]) {
            cout << u << " ";
            
            explored[u] = true;

            for (int v : adjList[u]) {
                if (!explored[v]) {
                    // cout << "(" << u << ", " << v << ")\n";

                    S.push(v); 
                    parent[v] = u; 
                }
            }
        }
    }
}


int main() {
    int n;
    cout << "Enter the number of vertices: ";
    cin >> n;

    vector<vector<int>> adjList(n);

    cout << "Enter the edges (enter -1 to stop):\n";
    int u, v;
    while (true) {
        cin >> u;
        if (u == -1) break;
        cin >> v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    int source;
    cout << "Enter the source vertex: ";
    cin >> source;

    DFS(adjList, source);

    return 0;
}



//knapsack

#include <iostream>
#include <algorithm>

using namespace std;

struct Item {
    int weight;
    int value;
};

int knapsack(int W, const Item items[], int n) {
    int dp[n + 1][W + 1];

    cout << "DP array table:" << endl;
    cout << "\t";
    for (int w = 0; w <= W; ++w) {
        cout << "W=" << w << "\t";
    }
    cout << endl;
    for (int i = 0; i <= n; ++i) {
        cout << "Item " << i << "\t";
        for (int w = 0; w <= W; ++w) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (items[i - 1].weight <= w) {
                dp[i][w] = max(dp[i - 1][w], items[i - 1].value + dp[i - 1][w - items[i - 1].weight]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
            cout << dp[i][w] << "\t";
        }
        cout << endl;
    }
    cout << endl;

    return dp[n][W];
}

int main() {
    int n;
    cout << "Enter the number of items: ";
    cin >> n;

    Item items[n];
    for (int i = 0; i < n; ++i) {
        cout << "Enter weight and value of item " << i + 1 << ": ";
        cin >> items[i].weight >> items[i].value;
    }

    int W;
    cout << "Enter the knapsack capacity: ";
    cin >> W;

    cout << "Weight\tValue\tValue/Weight" << endl;
    for (int i = 0; i < n; ++i) {
        cout << items[i].weight << "\t" << items[i].value << "\t" << static_cast<double>(items[i].value) / items[i].weight << endl;
    }

    cout << "Maximum value that can be obtained: " << knapsack(W, items, n) << endl;

    return 0;
}


//prims

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

// Structure to represent a vertex
struct Vertex {
    int key;
    int parent;
    bool inMST;
    Vertex() : key(INF), parent(-1), inMST(false) {}
};

// Function to find the vertex with minimum key value
int findMinKey(const vector<Vertex> &vertices) {
    int minKey = INF;
    int minIndex = -1;
    for (int i = 0; i < vertices.size(); i++) {
        if (!vertices[i].inMST && vertices[i].key < minKey) {
            minKey = vertices[i].key;
            minIndex = i;
        }
    }
    return minIndex;
}

// Function to print the adjacency matrix
void printAdjMatrix(const vector<vector<int>> &graph) {
    cout << "Adjacency Matrix:" << endl;
    for (const auto &row : graph) {
        for (int weight : row) {
            if (weight == INF)
                cout << "INF ";
            else
                cout << weight << " ";
        }
        cout << endl;
    }
}

// Function to print the MST edges
void printMST(const vector<Vertex> &vertices) {
    cout << "Minimum Spanning Tree (MST):" << endl;
    cout << "Edge \t Weight" << endl;
    for (int i = 1; i < vertices.size(); ++i) {
        cout << vertices[i].parent << " - " << i << "\t  " << vertices[i].key << endl;
    }
}

// Prim's algorithm to find Minimum Spanning Tree
void MST_Prim(vector<vector<int>> &graph, int startVertex) {
    int V = graph.size(); // Number of vertices
    vector<Vertex> vertices(V);

    // Initialize vertices
    for (int i = 0; i < V; ++i) {
        vertices[i].key = INF;
        vertices[i].parent = -1;
    }

    vertices[startVertex].key = 0;

    for (int count = 0; count < V - 1; ++count) {
        int u = findMinKey(vertices);
        vertices[u].inMST = true;

        for (int v = 0; v < V; ++v) {
            if (graph[u][v] && !vertices[v].inMST && graph[u][v] < vertices[v].key) {
                vertices[v].parent = u;
                vertices[v].key = graph[u][v];
            }
        }
    }

    // Print Adjacency Matrix and MST
    printAdjMatrix(graph);
    printMST(vertices);
}

int main() {
    int V;
    cout << "Enter the number of vertices: ";
    cin >> V;

    // Initialize the graph with all edges as INF
    vector<vector<int>> graph(V, vector<int>(V, INF));

    cout << "Enter the weights for edges ('0' for no edge):" << endl;
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            cout << "Enter weight for edge from vertex " << i << " to vertex " << j << ": ";
            cin >> graph[i][j];
        }
    }

    int startVertex;
    cout << "Enter the starting vertex (0-based indexing): ";
    cin >> startVertex;

    MST_Prim(graph, startVertex);

    return 0;
}


//strassen

#include <iostream>

using namespace std;

void strassenMatrixMultiply2x2(int A[2][2], int B[2][2], int C[2][2]) {
    int a11 = A[0][0], a12 = A[0][1], a21 = A[1][0], a22 = A[1][1];
    int b11 = B[0][0], b12 = B[0][1], b21 = B[1][0], b22 = B[1][1];

    int P = (a11 + a22) * (b11 + b22);
    int Q = (a21 + a22) * b11;
    int R = a11 * (b12 - b22);
    int S = a22 * (b21 - b11);
    int T = (a11 + a12) * b22;
    int U = (a21 - a11) * (b11 + b12);
    int V = (a12 - a22) * (b21 + b22);

    C[0][0] = P + S - T + V;
    C[0][1] = R + T;
    C[1][0] = Q + S;
    C[1][1] = P + R - Q + U;
}

int main() {
    int A[2][2], B[2][2], C[2][2];

    cout << "Enter elements of Matrix A (2x2):\n";
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            cout << "Enter element A[" << i << "][" << j << "]: ";
            cin >> A[i][j];
        }
    }

    cout << "Enter elements of Matrix B (2x2):\n";
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            cout << "Enter element B[" << i << "][" << j << "]: ";
            cin >> B[i][j];
        }
    }

    strassenMatrixMultiply2x2(A, B, C);

    cout << "Matrix A:\n";
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "Matrix B:\n";
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            cout << B[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "Matrix C (A * B) using Strassen algorithm:\n";
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
