#include <memory>
#include <iostream>

struct TreeNode {
    int value;
    std::shared_ptr<TreeNode> left;
    std::shared_ptr<TreeNode> right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

void preorderTraversal(const std::shared_ptr<TreeNode>& root) {
    if (root == nullptr) {
        return;
    }

    std::cout << root->value << " ";  // 先序遍历根节点
    preorderTraversal(root->left);    // 递归遍历左子树
    preorderTraversal(root->right);   // 递归遍历右子树
}

int main() {
    // 创建二叉树
    std::shared_ptr<TreeNode> root = std::make_shared<TreeNode>(1);
    root->left = std::make_shared<TreeNode>(2);
    root->right = std::make_shared<TreeNode>(3);
    root->left->left = std::make_shared<TreeNode>(4);
    root->left->right = std::make_shared<TreeNode>(5);

    // 前序遍历二叉树
    std::cout << "Preorder Traversal: ";
    preorderTraversal(root);
    std::cout << std::endl;

    return 0;
}
