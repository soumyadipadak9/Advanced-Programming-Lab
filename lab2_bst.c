#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


Node* insert(Node* root, int value) {
    if (root == NULL) return createNode(value);
    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);
    return root;
}

Node* search(Node* root, int key) {
    if (root == NULL || root->data == key) return root;
    if (key < root->data) return search(root->left, key);
    return search(root->right, key);
}

Node* findMin(Node* root) {
    while (root && root->left != NULL) root = root->left;
    return root;
}

Node* deleteNode(Node* root, int key) {
    if (root == NULL) return root;

    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}



void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

int getHeight(Node* root) {
    if (root == NULL) return -1;
    int leftH = getHeight(root->left);
    int rightH = getHeight(root->right);
    return 1 + (leftH > rightH ? leftH : rightH);
}

void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}



void runPart1And2() {
    printf("================ PART 1 & 2 DEMO ================\n");
    Node* root = NULL;
    int keys[] = {50, 30, 70, 20, 40, 60, 80, 10};
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++) root = insert(root, keys[i]);

    printf("Inorder Traversal:   "); inorder(root); printf("\n");
    printf("Preorder Traversal:  "); preorder(root); printf("\n");
    printf("Postorder Traversal: "); postorder(root); printf("\n");

   
    int searchKeys[] = {40, 99};
    for (int i = 0; i < 2; i++) {
        Node* found = search(root, searchKeys[i]);
        if (found) printf("Key %d: Found\n", searchKeys[i]);
        else printf("Key %d: Not Found\n", searchKeys[i]);
    }

    printf("\n--- Deletion Testing ---\n");
    printf("(i) Delete Leaf Node (10):\n");
    root = deleteNode(root, 10);
    printf("Inorder: "); inorder(root); printf("\n");

    printf("(ii) Delete Node with 1 Child (20):\n");
    root = deleteNode(root, 20);
    printf("Inorder: "); inorder(root); printf("\n");

    printf("(iii) Delete Node with 2 Children (50):\n");
    root = deleteNode(root, 50);
    printf("Inorder: "); inorder(root); printf("\n");

    freeTree(root);
}

void benchmark(int n) {
    int *arr = (int*)malloc(n * sizeof(int));
    
   
    char *types[] = {"Random", "Sorted", "Reverse-Sorted"};

    for (int t = 0; t < 3; t++) {
        
        for (int i = 0; i < n; i++) arr[i] = i + 1;

        if (t == 0) {
            for (int i = n - 1; i > 0; i--) {
                int j = rand() % (i + 1);
                int temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
            }
        } else if (t == 2) { 
            for (int i = 0; i < n / 2; i++) {
                int temp = arr[i]; arr[i] = arr[n - 1 - i]; arr[n - 1 - i] = temp;
            }
        }

       
        Node* root = NULL;
        clock_t start = clock();
        for (int i = 0; i < n; i++) root = insert(root, arr[i]);
        double buildTime = (double)(clock() - start) / CLOCKS_PER_SEC * 1000.0;

        int height = getHeight(root);

       
        start = clock();
        for (int i = 0; i < 1000; i++) {
            search(root, rand() % n);
        }
        double searchTime = (double)(clock() - start) / CLOCKS_PER_SEC * 1000.0;

        
        start = clock();
        for (int i = 0; i < 500; i++) {
            root = deleteNode(root, arr[i]);
        }
        double deleteTime = (double)(clock() - start) / CLOCKS_PER_SEC * 1000.0;

        printf("| %-5d | %-14s | %-6d | %-12.2f | %-13.2f | %-13.2f |\n", 
               n, types[t], height, buildTime, searchTime, deleteTime);

        freeTree(root);
    }
    free(arr);
}

int main() {
    srand(time(NULL));

   
    runPart1And2();

   
    printf("\n================ PART 3 BENCHMARK RESULTS ================\n");
    printf("| N     | Sequence Type  | Height | Build Time(ms)| Search Time(ms)| Delete Time(ms)|\n");
    printf("|-------|----------------|--------|---------------|----------------|----------------|\n");
    
    benchmark(1000);
    benchmark(5000);
    benchmark(10000);

    return 0;
}