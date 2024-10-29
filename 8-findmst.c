#include <stdio.h>
#include <stdlib.h>

#define MAX_EDGES 20
#define MAX_VERTICES 10

typedef struct {
    int start;
    int end;
    int weight;
} Edge;

typedef struct {
    int n;  // 정점의 개수
    int m;  // 간선의 개수
    Edge edges[MAX_EDGES];
} GraphType;

int parent[MAX_VERTICES];

void set_init(int n) {
    for (int i = 0; i < n; i++)
        parent[i] = -1;
}

// 경로 압축을 적용한 find 함수
int set_find(int curr) {
    if (parent[curr] == -1)
        return curr;
    return parent[curr] = set_find(parent[curr]);
}

void set_union(int a, int b) {
    int root1 = set_find(a);
    int root2 = set_find(b);
    if (root1 != root2)
        parent[root1] = root2;
}

// 정렬 기준을 통일하는 버블 정렬추가함
void bubble_sort(Edge edges[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight ||
                (edges[j].weight == edges[j + 1].weight && edges[j].start > edges[j + 1].start) ||
                (edges[j].weight == edges[j + 1].weight && edges[j].start == edges[j + 1].start && edges[j].end > edges[j + 1].end)) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

void quickKruskal(GraphType* g) {
    int edge_accepted = 0;
    int uset, vset;

    bubble_sort(g->edges, g->m);

    set_init(g->n);
    printf("Quick Based Kruskal\n");
    for (int i = 0; i < g->m && edge_accepted < g->n - 1; i++) {
        uset = set_find(g->edges[i].start);
        vset = set_find(g->edges[i].end);
        if (uset != vset) {
            printf("Edge (%d, %d) select %d\n", g->edges[i].start, g->edges[i].end, g->edges[i].weight);
            edge_accepted++;
            set_union(uset, vset);
        }
    }
    printf("\n");
}

// MinHeap 구조를 정렬과 일치하게 만들어줌
void minHeapify(Edge arr[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && (arr[left].weight < arr[smallest].weight ||
        (arr[left].weight == arr[smallest].weight && arr[left].start < arr[smallest].start) ||
        (arr[left].weight == arr[smallest].weight && arr[left].start == arr[smallest].start && arr[left].end < arr[smallest].end))) {
        smallest = left;
    }
    if (right < n && (arr[right].weight < arr[smallest].weight ||
        (arr[right].weight == arr[smallest].weight && arr[right].start < arr[smallest].start) ||
        (arr[right].weight == arr[smallest].weight && arr[right].start == arr[smallest].start && arr[right].end < arr[smallest].end))) {
        smallest = right;
    }
    if (smallest != i) {
        Edge temp = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = temp;
        minHeapify(arr, n, smallest);
    }
}

void buildMinHeap(Edge arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        minHeapify(arr, n, i);
}

Edge extractMin(Edge arr[], int* n) {
    Edge min = arr[0];
    arr[0] = arr[--(*n)];
    minHeapify(arr, *n, 0);
    return min;
}

void minHeapKruskal(GraphType* g) {
    int edge_accepted = 0;
    int uset, vset;
    int heapSize = g->m;

    // 동일하게 간선 정렬
    bubble_sort(g->edges, g->m);
    set_init(g->n);
    printf("MinHeap Based Kruskal\n");

    // 정렬된 간선을 사용하여 Kruskal 수행
    while (edge_accepted < g->n - 1 && heapSize > 0) {
        Edge minEdge = extractMin(g->edges, &heapSize);
        uset = set_find(minEdge.start);
        vset = set_find(minEdge.end);
        if (uset != vset) {
            printf("Edge (%d, %d) select %d\n", minEdge.start, minEdge.end, minEdge.weight);
            edge_accepted++;
            set_union(uset, vset);
        }
    }
    printf("\n");
}

void GenerateGraph(GraphType* g) {
    g->n = 10;  // 10개의 정점
    g->m = 18;  // 18개의 간선

    g->edges[0] = (Edge){ 2, 5, 1 };
    g->edges[1] = (Edge){ 3, 4, 2 };
    g->edges[2] = (Edge){ 1, 2, 3 };
    g->edges[3] = (Edge){ 2, 4, 4 };
    g->edges[4] = (Edge){ 3, 8, 5 };
    g->edges[5] = (Edge){ 3, 7, 6 };
    g->edges[6] = (Edge){ 2, 6, 7 };
    g->edges[7] = (Edge){ 9, 10, 10 };
    g->edges[8] = (Edge){ 5, 9, 13 };
    g->edges[9] = (Edge){ 8, 10, 15 };
    g->edges[10] = (Edge){ 1, 3, 11 };
    g->edges[11] = (Edge){ 1, 7, 12 };
    g->edges[12] = (Edge){ 7, 8, 13 };
    g->edges[13] = (Edge){ 4, 8, 14 };
    g->edges[14] = (Edge){ 4, 10, 16 };
    g->edges[15] = (Edge){ 5, 6, 9 };
    g->edges[16] = (Edge){ 6, 9, 17 };
    g->edges[17] = (Edge){ 4, 9, 18 };
}

int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    GenerateGraph(g);  // 그래프를 생성하는 함수

    quickKruskal(g);   // Quick 기반 Kruskal
    minHeapKruskal(g); // MinHeap 기반 Kruskal

    free(g);
    return 0;
}



