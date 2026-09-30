#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 100



typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;


TreeNode* createNode(int val) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// insert to binary search tree
TreeNode* Insert_bst(TreeNode* root, int val) {
    if (root == NULL) {
        return createNode(val);
    }
    if (val < root->data) {
        root->left = Insert_bst(root->left, val);
    } else if (val > root->data) {
        root->right = Insert_bst(root->right, val);
    }
    return root;
}

// Q2. Count leaves
int Count_leaves_Dynamic(TreeNode* root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    return Count_leaves_Dynamic(root->left) + Count_leaves_Dynamic(root->right);
}

// Q2. Depth of tree
int depth_Dynamic(TreeNode* root) {
    if (root == NULL) return 0;
    int leftDepth = depth_Dynamic(root->left);
    int rightDepth = depth_Dynamic(root->right);
    return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
}

// Q2. Check if p is father of q
bool is_father_Dynamic(TreeNode* root, int p, int q) {
    if (root == NULL) return false;
    if (root->data == p) {
        if ((root->left && root->left->data == q) || (root->right && root->right->data == q)) {
            return true;
        }
    }
    return is_father_Dynamic(root->left, p, q) || is_father_Dynamic(root->right, p, q);
}

// Q2. Check if p and q are siblings
bool is_sibling_Dynamic(TreeNode* root, int p, int q) {
    if (root == NULL) return false;
    if (root->left && root->right) {
        if ((root->left->data == p && root->right->data == q) || 
            (root->left->data == q && root->right->data == p)) {
            return true;
        }
    }
    return is_sibling_Dynamic(root->left, p, q) || is_sibling_Dynamic(root->right, p, q);
}

// Q3. Recursive Traversals
void inorder_recursive(TreeNode* root) {
    if (root != NULL) {
        inorder_recursive(root->left);
        printf("%d ", root->data);
        inorder_recursive(root->right);
    }
}

void preorder_recursive(TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder_recursive(root->left);
        preorder_recursive(root->right);
    }
}

void postorder_recursive(TreeNode* root) {
    if (root != NULL) {
        postorder_recursive(root->left);
        postorder_recursive(root->right);
        printf("%d ", root->data);
    }
}


typedef struct Stack {
    TreeNode* items[MAX_NODES];
    int top;
} Stack;

void initStack(Stack* s) { s->top = -1; }
bool isStackEmpty(Stack* s) { return s->top == -1; }
void pushStack(Stack* s, TreeNode* node) { s->items[++(s->top)] = node; }
TreeNode* popStack(Stack* s) { return s->items[(s->top)--]; }

// Q3. Non-Recursive Traversals
void inorder_nonrecursive(TreeNode* root) {
    Stack s;
    initStack(&s);
    TreeNode* curr = root;

    while (curr != NULL || !isStackEmpty(&s)) {
        while (curr != NULL) {
            pushStack(&s, curr);
            curr = curr->left;
        }
        curr = popStack(&s);
        printf("%d ", curr->data);
        curr = curr->right;
    }
}

void preorder_nonrecursive(TreeNode* root) {
    if (root == NULL) return;
    Stack s;
    initStack(&s);
    pushStack(&s, root);

    while (!isStackEmpty(&s)) {
        TreeNode* curr = popStack(&s);
        printf("%d ", curr->data);
        if (curr->right) pushStack(&s, curr->right);
        if (curr->left) pushStack(&s, curr->left);
    }
}

void postorder_nonrecursive(TreeNode* root) {
    if (root == NULL) return;
    Stack s1, s2;
    initStack(&s1);
    initStack(&s2);

    pushStack(&s1, root);
    while (!isStackEmpty(&s1)) {
        TreeNode* curr = popStack(&s1);
        pushStack(&s2, curr);
        if (curr->left) pushStack(&s1, curr->left);
        if (curr->right) pushStack(&s1, curr->right);
    }

    while (!isStackEmpty(&s2)) {
        printf("%d ", popStack(&s2)->data);
    }
}

// Q3. Level Order Traversal
void BFS(TreeNode* root) {
    if (root == NULL) return;
    TreeNode* queue[MAX_NODES];
    int front = 0, rear = 0;

    queue[rear++] = root;
    while (front < rear) {
        TreeNode* curr = queue[front++];
        printf("%d ", curr->data);

        if (curr->left) queue[rear++] = curr->left;
        if (curr->right) queue[rear++] = curr->right;
    }
}


TreeNode* minValueNode(TreeNode* node) {
    TreeNode* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Q3. Delete a node from Binary Search Tree 
TreeNode* delete_bst(TreeNode* root, int key) {
    if (root == NULL) return root;

    if (key < root->data) {
        root->left = delete_bst(root->left, key);
    } else if (key > root->data) {
        root->right = delete_bst(root->right, key);
    } else {
        // Case 1 & 2: Node with 0 or 1 child
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        // Case 3: Node with 2 children
        TreeNode* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = delete_bst(root->right, temp->data);
    }
    return root;
}



// 2. SEQUENTIAL ARRAY REPRESENTATION 


typedef struct {
    int tree[MAX_NODES];
    bool exists[MAX_NODES];
} SeqTree;

void initSeqTree(SeqTree *st) {
    for (int i = 0; i < MAX_NODES; i++) {
        st->exists[i] = false;
    }
}

void setSeqNode(SeqTree *st, int index, int val) {
    st->tree[index] = val;
    st->exists[index] = true;
}

int Count_leaves_Seq(SeqTree *st, int idx) {
    if (idx >= MAX_NODES || !st->exists[idx]) return 0;
    int left = 2 * idx;
    int right = 2 * idx + 1;
    bool hasLeft = (left < MAX_NODES && st->exists[left]);
    bool hasRight = (right < MAX_NODES && st->exists[right]);

    if (!hasLeft && !hasRight) return 1;
    return Count_leaves_Seq(st, left) + Count_leaves_Seq(st, right);
}

int depth_Seq(SeqTree *st, int idx) {
    if (idx >= MAX_NODES || !st->exists[idx]) return 0;
    int leftDepth = depth_Seq(st, 2 * idx);
    int rightDepth = depth_Seq(st, 2 * idx + 1);
    return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
}

bool is_father_Seq(SeqTree *st, int p, int q) {
    for (int i = 1; i < MAX_NODES; i++) {
        if (st->exists[i] && st->tree[i] == p) {
            int left = 2 * i;
            int right = 2 * i + 1;
            if (left < MAX_NODES && st->exists[left] && st->tree[left] == q) return true;
            if (right < MAX_NODES && st->exists[right] && st->tree[right] == q) return true;
        }
    }
    return false;
}

bool is_sibling_Seq(SeqTree *st, int p, int q) {
    for (int i = 1; i < MAX_NODES; i++) {
        if (st->exists[i]) {
            int left = 2 * i;
            int right = 2 * i + 1;
            if (left < MAX_NODES && right < MAX_NODES && st->exists[left] && st->exists[right]) {
                if ((st->tree[left] == p && st->tree[right] == q) || 
                    (st->tree[left] == q && st->tree[right] == p)) {
                    return true;
                }
            }
        }
    }
    return false;
}


// 3. LINKED ARRAY REPRESENTATION (Static Memory Pool)


typedef struct {
    int data;
    int left;
    int right;
    bool used;
} LinkedArrayNode;

typedef struct {
    LinkedArrayNode nodes[MAX_NODES];
    int root;
} LinkedArrayTree;

void initLinkedArrayTree(LinkedArrayTree *lat) {
    lat->root = -1;
    for (int i = 0; i < MAX_NODES; i++) {
        lat->nodes[i].used = false;
        lat->nodes[i].left = -1;
        lat->nodes[i].right = -1;
    }
}

int allocateLATNode(LinkedArrayTree *lat, int val) {
    for (int i = 0; i < MAX_NODES; i++) {
        if (!lat->nodes[i].used) {
            lat->nodes[i].used = true;
            lat->nodes[i].data = val;
            lat->nodes[i].left = -1;
            lat->nodes[i].right = -1;
            return i;
        }
    }
    return -1;
}

int Count_leaves_LAT(LinkedArrayTree *lat, int idx) {
    if (idx == -1 || !lat->nodes[idx].used) return 0;
    int left = lat->nodes[idx].left;
    int right = lat->nodes[idx].right;

    if (left == -1 && right == -1) return 1;
    return Count_leaves_LAT(lat, left) + Count_leaves_LAT(lat, right);
}

int depth_LAT(LinkedArrayTree *lat, int idx) {
    if (idx == -1 || !lat->nodes[idx].used) return 0;
    int leftDepth = depth_LAT(lat, lat->nodes[idx].left);
    int rightDepth = depth_LAT(lat, lat->nodes[idx].right);
    return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
}

bool is_father_LAT(LinkedArrayTree *lat, int p, int q) {
    for (int i = 0; i < MAX_NODES; i++) {
        if (lat->nodes[i].used && lat->nodes[i].data == p) {
            int left = lat->nodes[i].left;
            int right = lat->nodes[i].right;
            if (left != -1 && lat->nodes[left].data == q) return true;
            if (right != -1 && lat->nodes[right].data == q) return true;
        }
    }
    return false;
}

bool is_sibling_LAT(LinkedArrayTree *lat, int p, int q) {
    for (int i = 0; i < MAX_NODES; i++) {
        if (lat->nodes[i].used) {
            int left = lat->nodes[i].left;
            int right = lat->nodes[i].right;
            if (left != -1 && right != -1) {
                if ((lat->nodes[left].data == p && lat->nodes[right].data == q) ||
                    (lat->nodes[left].data == q && lat->nodes[right].data == p)) {
                    return true;
                }
            }
        }
    }
    return false;
}



// MAIN FUNCTION TESTING ALL WORKSHEET OPERATIONS


int main() {
    printf("--- 1. DYNAMIC BINARY SEARCH TREE (BST) ---\n");
    TreeNode* root = NULL;

    int values[] = {50, 30, 70, 20, 40, 60, 80};
    printf("Inserting values into BST: ");
    for (int i = 0; i < 7; i++) {
        printf("%d ", values[i]);
        root = Insert_bst(root, values[i]);
    }
    printf("\n\n");

    printf("Recursive Traversals:\n");
    printf(" - Inorder   : "); inorder_recursive(root); printf("\n");
    printf(" - Preorder  : "); preorder_recursive(root); printf("\n");
    printf(" - Postorder : "); postorder_recursive(root); printf("\n\n");

    printf("Non-Recursive Traversals:\n");
    printf(" - Inorder   : "); inorder_nonrecursive(root); printf("\n");
    printf(" - Preorder  : "); preorder_nonrecursive(root); printf("\n");
    printf(" - Postorder : "); postorder_nonrecursive(root); printf("\n\n");

    printf("Level-Order Traversal (BFS):\n - BFS        : ");
    BFS(root);
    printf("\n\n");

    printf("Tree Properties (Dynamic Representation):\n");
    printf(" - Leaf Count : %d\n", Count_leaves_Dynamic(root));
    printf(" - Tree Depth : %d\n", depth_Dynamic(root));
    printf(" - Is 30 father of 20? %s\n", is_father_Dynamic(root, 30, 20) ? "Yes" : "No");
    printf(" - Is 30 father of 70? %s\n", is_father_Dynamic(root, 30, 70) ? "Yes" : "No");
    printf(" - Are 20 and 40 siblings? %s\n", is_sibling_Dynamic(root, 20, 40) ? "Yes" : "No");
    printf(" - Are 20 and 60 siblings? %s\n", is_sibling_Dynamic(root, 20, 60) ? "Yes" : "No");
    printf("\n");

    printf("Deleting Node 20 (Leaf Node):\n");
    root = delete_bst(root, 20);
    printf(" - Inorder after deleting 20: "); inorder_recursive(root); printf("\n");

    printf("Deleting Node 30 (Node with one child / two children):\n");
    root = delete_bst(root, 30);
    printf(" - Inorder after deleting 30: "); inorder_recursive(root); printf("\n");



    printf("--- 2. SEQUENTIAL ARRAY REPRESENTATION ---\n");
    SeqTree st;
    initSeqTree(&st);
    setSeqNode(&st, 1, 50);
    setSeqNode(&st, 2, 30);
    setSeqNode(&st, 3, 70);
    setSeqNode(&st, 4, 20);
    setSeqNode(&st, 5, 40);

    printf("Tree Properties (Sequential Array):\n");
    printf(" - Leaf Count : %d\n", Count_leaves_Seq(&st, 1));
    printf(" - Tree Depth : %d\n", depth_Seq(&st, 1));
    printf(" - Is 30 father of 40? %s\n", is_father_Seq(&st, 30, 40) ? "Yes" : "No");
    printf(" - Are 20 and 40 siblings? %s\n", is_sibling_Seq(&st, 20, 40) ? "Yes" : "No");
    printf("\n");

    printf("--- 3. LINKED ARRAY REPRESENTATION ---\n");
    LinkedArrayTree lat;
    initLinkedArrayTree(&lat);

    int r = allocateLATNode(&lat, 50);
    int n1 = allocateLATNode(&lat, 30);
    int n2 = allocateLATNode(&lat, 70);
    int n3 = allocateLATNode(&lat, 20);
    int n4 = allocateLATNode(&lat, 40);

    lat.root = r;
    lat.nodes[r].left = n1;
    lat.nodes[r].right = n2;
    lat.nodes[n1].left = n3;
    lat.nodes[n1].right = n4;

    printf("Tree Properties (Linked Array):\n");
    printf(" - Leaf Count : %d\n", Count_leaves_LAT(&lat, lat.root));
    printf(" - Tree Depth : %d\n", depth_LAT(&lat, lat.root));
    printf(" - Is 50 father of 70? %s\n", is_father_LAT(&lat, 50, 70) ? "Yes" : "No");
    printf(" - Are 20 and 40 siblings? %s\n", is_sibling_LAT(&lat, 20, 40) ? "Yes" : "No");
    printf("\n====================================================\n");

    return 0;
}