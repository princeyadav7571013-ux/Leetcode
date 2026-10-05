class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast != NULL && fast->next != NULL) {
            slow = slow->next;           // moves 1 step
            fast = fast->next->next;     // moves 2 steps

            if (slow == fast) {
                return true;
            }
        }

        return false;
    }
};