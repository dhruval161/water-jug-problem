// Water Jug problem using breadth first search


#include <bits/stdc++.h>

using namespace std;


// A state defines ordered pair (x,y) which means 
// first jug contains x amount of water and second
// jug has y amount of water
struct state {
    int x, y;

    bool operator < (const state& that) const {
        if (x != that.x) return x < that.x;
        return y < that.y;
    }
};

int capacity_x, capacity_y, target;

void bfs(state start, stack <pair <state, int> >& path)   {
    queue <state> q;
    state goal = (state) {-1, -1};

    map <state, pair <state, int> > parent;

    q.push(start);
    parent[start] = make_pair(start, 0);

    while (!q.empty())    {
        state top = q.front();
        q.pop();

        // If the target state is found then end the bfs algorithm
        if (top.x == target || top.y == target) {
            goal = top;
            break;
        }

        
        // OPTION-1: Completely fill the first jug
        if (top.x < capacity_x)  {
            state child = (state) {capacity_x, top.y};
            if (parent.find(child) == parent.end()) {
                q.push(child);
                parent[child] = make_pair(top, 1);
            }
        }

        // OPTION-2: Completely fill the second jug
        if (top.y < capacity_y)  {
            state child = (state) {top.x, capacity_y};
            if (parent.find(child) == parent.end()) {
                q.push(child);
                parent[child] = make_pair(top, 2);
            }
        }

        // OPTION-3: Completely empty the first jug
        if (top.x > 0)  {
            state child = (state) {0, top.y};
            if (parent.find(child) == parent.end()) {
                q.push(child);
                parent[child] = make_pair(top, 3);
            }
        }

        // OPTION-4: Completely empty the second jug
        if (top.y > 0)  {
            state child = (state) {top.x, 0};
            if (parent.find(child) == parent.end()) {
                q.push(child);
                parent[child] = make_pair(top, 4);
            }
        }


        // OPTION-5: Fill the first jug till its capacity is reached or the second jug is empty 
        if (top.y > 0)  {
            state child = (state) {min(top.x + top.y, capacity_x), max(0, top.x + top.y - capacity_x)};
            if (parent.find(child) == parent.end()) {
                q.push(child);
                parent[child] = make_pair(top, 5);
            }
        }

        // OPTION-5: Fill the second jug till its capacity is reached or the first jug is empty
        if (top.x > 0)  {
            state child = (state) {max(0, top.x + top.y - capacity_y), min(top.x + top.y, capacity_y)};
            if (parent.find(child) == parent.end()) {
                q.push(child);
                parent[child] = make_pair(top, 6);
            }
        }
    }

    // Goal is not reachable
    if (goal.x == -1 || goal.y == -1)
        return;

    // Push the path from start to target onto a stack
    path.push(make_pair(goal, 0));
    while (parent[path.top().first].second != 0)
        path.push(parent[path.top().first]);
}


int main()  {
	
    freopen ("input.txt","r",stdin);
    stack <pair <state, int> > path;
    cin >> capacity_x;
    cin >> capacity_y;
    cin >> target;
    printf("%d\n",capacity_x);
    printf("%d\n",capacity_y);
    printf("%d\n",target);
    
    bfs((state) {0, 0}, path);
    if (path.empty())
    {
        printf("0\n");
        printf("Target cannot be reached.\n");
    }
    else   {
    	// Length of shortest path
    	int path_length = path.size();
        printf("1\n");
    	cout<<path_length -1<< endl;
    	
        vector <int> rules;
        state top;
        for(int i=0; i<path_length; i++){
            top = path.top().first;
            
            rules.push_back(path.top().second);
            path.pop();
            if(i==0){
            	continue;
            }
            else{
            	int rule = rules[i-1];
            	
            	if(rule==1){
            		cout << "Completely fill the first jug\n";
            			
            	}
            	else if(rule==2){
            		cout << "Completely fill the second jug\n";
            			
            	}
            	else if(rule==3){
            		cout << "Completely empty the first jug\n";
            		
            	}
            	else if(rule==4){
            		cout << "Completely empty the second jug\n";
            		
            	}
            	else if(rule==5){
            		if(top.x < capacity_x){
            			cout << "Pour all the water from second jug to first jug\n";
            		}
            		else{
            			cout << "Completely fill the first jug from second jug\n";
            		}

            		
            	}
            	else{
					if(top.y < capacity_y){
            			cout << "Pour all the water from first jug to second jug\n";
            		}
            		else{
            			cout << "Completely fill the second jug from first jug\n";
            		}            		
            	}

            	cout << top.x << endl;
            	cout << top.y << endl;
           		
            }
            
            
        }
    }

    return 0;
}