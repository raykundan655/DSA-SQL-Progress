// 901. Online Stock Span
class StockSpanner {
public:
   
    stack<pair<int,int>>obj;
    int count;
    StockSpanner() {
        
    }
    
    int next(int price) {
        count=1;
        while(!obj.empty()&&price>=obj.top().first){
            count+=obj.top().second;
            obj.pop();
           }
        
      
        obj.push({price,count});
        return count;
    }
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */


// 143. Reorder List
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
    void reorderList(ListNode* head) {
        stack<int>s;
        ListNode * fast=head;
        ListNode * slow=head;
        while( fast!=nullptr && fast->next!=nullptr){
           fast=fast->next->next;
           slow=slow->next;

        }
      // got middle node
        ListNode * curr=slow->next;
        slow->next=nullptr;
      
 // insert the element into stack after middle
        while(curr!=nullptr){
            s.push(curr->val);
            curr=curr->next;
        }

        ListNode*temp=head;
       while(!s.empty()){
        ListNode * newnode=new ListNode(s.top());
        s.pop();
        newnode->next=temp->next;
        temp->next=newnode;
        temp=newnode->next;
        if(temp==nullptr){
            break;
        }
       }


    }
};

// 1475. Final Prices With a Special Discount in a Shop(brute force)
class Solution {
public:
    vector<int> finalPrices(vector<int>& p) {
       vector<int>vec;
       for(int i=0;i<p.size();i++){
        int flag=false;
        for(int j=i+1;j<p.size();j++){
            if(p[j]<=p[i]){
                vec.push_back(p[i]-p[j]);
                flag=true;
                break;
            }

        }
        if(!flag){
            vec.push_back(p[i]);
        }
       }
       return vec;
    }
};


