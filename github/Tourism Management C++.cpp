#include <iostream>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) : data(value), left(NULL), right(NULL) {}
};

class BinaryTree {
private:
    TreeNode* root;

    TreeNode* findMin(TreeNode* node) {
        while (node->left != NULL) {
            node = node->left;
        }
        return node;
    }

    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == NULL) {
            return root;
        }

        if (key < root->data) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->data) {
            root->right = deleteNode(root->right, key);
        } else {
            // Node with only one child or no child
            if (root->left == NULL) {
                TreeNode* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == NULL) {
                TreeNode* temp = root->left;
                delete root;
                return temp;
            }

            // Node with two children: Get the inorder successor (smallest in the right subtree)
            TreeNode* temp = findMin(root->right);

            // Copy the inorder successor's content to this node
            root->data = temp->data;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->data);
        }
        return root;
    }

public:
    BinaryTree() : root(NULL) {}

    void insert(int key) {
        root = insertHelper(root, key);
    }

    void remove(int key) {
        root = deleteNode(root, key);
    }

    void inorderTraversal(TreeNode* node) {
        if (node != NULL) {
            inorderTraversal(node->left);
            std::cout << node->data << " ";
            inorderTraversal(node->right);
        }
    }

    void displayInorder() {
        inorderTraversal(root);
        std::cout << std::endl;
    }

private:
    TreeNode* insertHelper(TreeNode* node, int key) {
        if (node == NULL) {
            return new TreeNode(key);
        }

        if (key < node->data) {
            node->left = insertHelper(node->left, key);
        } else if (key > node->data) {
            node->right = insertHelper(node->right, key);
        }

        return node;
    } 
};

int main() {
    BinaryTree tree;

    int value;
    cout << "Enter the first number: ";
    cin >> value;
    tree.insert(value);

    cout << "Enter the second number: ";
    cin >> value;
    tree.insert(value);

    cout << "Enter the third number: ";
    cin >> value;
    tree.insert(value);

    std::cout << "Inorder traversal: ";
    tree.displayInorder();

    cout << "Enter the value to be deleted: ";
    cin >> value;
    tree.remove(value);

    std::cout << "Remaining values after deletion: ";
    tree.displayInorder();

    return 0;
}
