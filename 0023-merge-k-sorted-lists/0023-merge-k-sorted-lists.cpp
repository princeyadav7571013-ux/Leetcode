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

    struct compare {
        bool operator()(ListNode* a, ListNode* b) {
            return a->val > b->val;
        }
    };

    ListNode* mergeKLists(vector<ListNode*>& lists) {

        priority_queue<ListNode*, vector<ListNode*>, compare> pq;

        // Put first node of every list into heap
        for (ListNode* node : lists) {
            if (node != nullptr) {
                pq.push(node);
            }
        }

        // Dummy node
        ListNode* dummy = new ListNode(-1);
        ListNode* tail = dummy;

        while (!pq.empty()) {

            // Get smallest node
            ListNode* smallest = pq.top();
            pq.pop();

            // Add it to answer
            tail->next = smallest;
            tail = tail->next;

            // Add next node of same list
            if (smallest->next != nullptr) {
                pq.push(smallest->next);
            }
        }

        return dummy->next;
    }
};