/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

class Solution {
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        if (root == nullptr) return {};

        vector<tuple<int, int, int>> nodes;
        queue<pair<TreeNode*, pair<int, int>>> q;

        q.push({root, {0, 0}});

        while (!q.empty()) {
            auto p = q.front();
            q.pop();

            TreeNode* node = p.first;
            int col = p.second.first;
            int row = p.second.second;

            nodes.push_back({col, row, node->val});

            if (node->left)
                q.push({node->left, {col - 1, row + 1}});

            if (node->right)
                q.push({node->right, {col + 1, row + 1}});
        }

        sort(nodes.begin(), nodes.end());

        vector<vector<int>> ans;
        int prevCol = INT_MIN;

        for (auto t : nodes) {
            int col = get<0>(t);
            int val = get<2>(t);

            if (col != prevCol) {
                ans.push_back({});
                prevCol = col;
            }

            ans.back().push_back(val);
        }

        return ans;
    }
};
