/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        
        vector<int> ans = {-1, -1};

        if (head == nullptr || head->next == nullptr ||
            head->next->next == nullptr) {
            return ans;
        }

        ListNode* prevNode = head;
        ListNode* curr = head->next;

        int pos = 1;

        int first = -1;
        int prevCritical = -1;

        int minDist = INT_MAX;
        int maxDist = -1;

        while (curr->next != nullptr) {

            int prevValue = prevNode->val;
            int currValue = curr->val;
            int nextValue = curr->next->val;

            // Check whether current node is a critical point
            if ((currValue > prevValue && currValue > nextValue) ||
                (currValue < prevValue && currValue < nextValue)) {

                // First critical point
                if (first == -1) {
                    first = pos;
                } 
                else {
                    // Distance from previous critical point
                    minDist = min(minDist, pos - prevCritical);

                    // Distance from first critical point
                    maxDist = pos - first;
                }

                prevCritical = pos;
            }

            prevNode = curr;
            curr = curr->next;
            pos++;
        }

        if (first == -1 || minDist == INT_MAX) {
            return {-1, -1};
        }

        return {minDist, maxDist};
    }
};