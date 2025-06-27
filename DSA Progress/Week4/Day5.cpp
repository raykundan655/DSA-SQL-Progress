// 1701. Average Waiting Time
class Solution {
public:
    double averageWaitingTime(vector<vector<int>>& cust) {
        deque<int>q;
        double waitt=0.0;
        for(int i=0;i<cust.size();i++){
             int arrival = cust[i][0];
            int process = cust[i][1];

                if( q.empty()||cust[i][0]>q.front()){
                    double pre=cust[i][0]+cust[i][1];
                    double wait=pre-arrival;
                    waitt+=wait;
                    q.push_front(pre);
                }
                else{
                    double pre=cust[i][1]+q.front();
                    double wait=pre-cust[i][0];
                      waitt+=wait;
                    q.push_front(pre);
                }
            
        }
        return waitt/cust.size();
    }
};

// 1823. Find the Winner of the Circular Game

class Solution {
public:
    int findTheWinner(int n, int k) {
        queue<int>q;
        for(int i=1;i<=n;i++){
            q.push(i);
        }
        while(q.size()>1){
            for(int i=1;i<k;i++){
                q.push(q.front());
                q.pop();
                // k-1  element go back in circle from starting
            }
            q.pop();
            // kth element are pop
        }

    // return the winner
        return q.front();

    }
};

