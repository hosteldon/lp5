#include <iostream>
#include <queue>
#include <omp.h>
#include <iomanip>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

class BreadthFS {
public:
    Node* insert(Node* root, int data);
    void bfsTreeView(Node* root);
};

Node* BreadthFS::insert(Node* root, int data) {
    if (!root)
        return new Node(data);
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();
        if (!temp->left) {
            temp->left = new Node(data);
            return root;
        }
        else
            q.push(temp->left);
        if (!temp->right) {
            temp->right = new Node(data);
            return root;
        }
        else
            q.push(temp->right);
    }
    return root;
}

void BreadthFS::bfsTreeView(Node* root) {
    if (!root) return;
    queue<Node*> q;
    q.push(root);
    int level = 0;
    cout << "\nBFS Traversal using OpenMP (Tree View):\n";
    while (!q.empty()) {
        int size = q.size();
        cout << setw(8 * (4 - level)) << "";
        for (int i = 0; i < size; i++) {
            Node* node;
            {
                node = q.front();
                q.pop();
                cout << node->data << "\t";
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        cout << "\n";
        level++;
    }
}

int main() {
    Node* root = nullptr;
    BreadthFS tree;
    int data;
    char ans;
    do {
        cout << "\nEnter data: ";
        cin >> data;
        root = tree.insert(root, data);
        cout << "Do you want to insert one more node? (y/n): ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');
    tree.bfsTreeView(root);
    return 0;
}
