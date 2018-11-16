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

struct state2 {
    int x, y, z;

    bool operator < (const state2& that) const {
        if (x != that.x) return x < that.x;
        if (y != that.y) return y < that.y;
        return z < that.z;
    }
};




int capacity_x, capacity_y,capacity_z, target;
int req_x,req_y,req_z ;
int total_water;

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
        if (top.x == req_x && top.y == req_y) {
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

void bfs2(state2 start, stack <pair <state2, int> >& path)   {
    queue <state2> q;
    state2 goal = (state2) {-1, -1 , -1};

    //cout<<capacity_z<<endl;

    map <state2, pair <state2, int> > parent;

    q.push(start);

    parent[start] = make_pair(start, 0);

    while (!q.empty())
    {
        state2 top = q.front();
        q.pop();
        //cout<<top.x<<" "<<top.y<<" "<<top.z<<endl;
        // If the target state is found then end the bfs algorithm
        if (top.x == req_x && top.y == req_y && top.z == req_z) {
            goal = top;
            break;
        }


        // OPTION-1: Completely fill the first jug
       if (top.x < capacity_x)  {
            state2 child = (state2) {capacity_x, top.y,top.z};
            if (parent.find(child) == parent.end()) {
                q.push(child);
                parent[child] = make_pair(top, 1);
            }
        }


        // OPTION-2: Completely fill the second jug
        if (top.y < capacity_y)  {
            state2 child = (state2) {top.x, capacity_y,top.z};
            if (parent.find(child) == parent.end()) {
                q.push(child);
                parent[child] = make_pair(top, 2);
            }
        }

        // OPTION-3: Completely fill the third jug
        if (top.z < capacity_z)  {
            state2 child = (state2) {top.x, top.y , capacity_z };
            if (parent.find(child) == parent.end()) {
                q.push(child);
                parent[child] = make_pair(top, 3);
            }
        }


        // OPTION-4: Completely empty the first jug
        if (top.x > 0)  {
            state2 child = (state2) {0, top.y , top.z};
            if (parent.find(child) == parent.end()) {
                q.push(child);
                parent[child] = make_pair(top, 4);
            }
        }

        // OPTION-5: Completely empty the second jug
        if (top.y > 0)  {
            state2 child = (state2) {top.x, 0,top.z};
            if (parent.find(child) == parent.end()) {
                q.push(child);
                parent[child] = make_pair(top, 5);
            }
        }

         // OPTION-6: Completely empty the third jug
        if (top.z > 0)  {
            state2 child = (state2) {top.x, top.y , 0};
            if (parent.find(child) == parent.end()) {
                q.push(child);
                parent[child] = make_pair(top, 6);
            }
        }


        // OPTION-7: Fill the first jug till its capacity is reached or the second jug is empty
        //(fill from second to first)
        if (top.y > 0)  {
            state2 child = (state2) {min(top.x + top.y, capacity_x), max(0, top.x + top.y - capacity_x),top.z};
            if (parent.find(child) == parent.end()) {
                q.push(child);
                parent[child] = make_pair(top, 7);
            }
        }



        // OPTION-8: Fill the first jug till its capacity is reached or the third jug is empty
        //(fill from third to first)
        if (top.z > 0)  {
            state2 child = (state2) {min(top.x + top.z, capacity_x),top.y,max(0, top.x + top.z - capacity_x) };
            if (parent.find(child) == parent.end()) {
                q.push(child);
                parent[child] = make_pair(top, 8);
            }
        }

        // OPTION-9: Fill the second jug till its capacity is reached or the first jug is empty
        //(fill from first to second)
        if (top.x > 0)  {
            state2 child = (state2) {max(0, top.x + top.y - capacity_y),min(top.x + top.y, capacity_y),top.z};
            if (parent.find(child) == parent.end()) {
                q.push(child);
                parent[child] = make_pair(top, 9);
            }
        }



        // OPTION-10: Fill the second jug till its capacity is reached or the third jug is empty
        //(fill from third to second)
        if (top.z > 0)  {
            state2 child = (state2) {top.x,min(top.y + top.z, capacity_y),max(0, top.y + top.z - capacity_y) };
            if (parent.find(child) == parent.end()) {
                q.push(child);
                parent[child] = make_pair(top, 10);
            }
        }

           // OPTION-11: Fill the third jug till its capacity is reached or the first jug is empty
        //(fill from first to third)
        if (top.x > 0)  {
            state2 child = (state2) {max(0, top.x + top.z - capacity_z),top.y,min(top.x + top.z, capacity_z)};
            if (parent.find(child) == parent.end()) {
                q.push(child);
                parent[child] = make_pair(top, 11);
            }
        }



        // OPTION-12: Fill the third jug till its capacity is reached or the second jug is empty
        //(fill from second to third)
        if (top.y > 0)  {
            state2 child = (state2) {top.x,max(0, top.y + top.z - capacity_z) ,min(top.y + top.z, capacity_z)};
            if (parent.find(child) == parent.end()) {
                q.push(child);
                parent[child] = make_pair(top, 12);
            }
        }


    }

    // Goal is not reachable
    if (goal.x == -1 || goal.y == -1 || goal.z == -1)
        return;

    // Push the path from start to target onto a stack
    path.push(make_pair(goal, 0));
    while (parent[path.top().first].second != 0)
        path.push(parent[path.top().first]);
}


void for_n2()
{

    cout<<0<<endl;
    stack <pair <state, int> > path;
    //cout<<"Please enter capacity of first jug"<<endl;
    cin >> capacity_x;
    cout<<capacity_x<<endl;
    //cout<<"Please enter capacity of second jug"<<endl;
    cin >> capacity_y;
    cout<<capacity_y<<endl;
    cout<<"inf"<<endl;
    //cout<<"Please enter desired amount of  water in first jug"<<endl;
    cin>>req_x;
    cout<<req_x<<endl;

    //cout<<"Please enter desired amount of  water in second jug"<<endl;
    cin>>req_y;
    cout<<req_y<<endl;

    if(req_x > capacity_x  || req_y > capacity_y || req_x < 0 || req_y < 0)
    {
        cout<<"0"<<endl;
        cout<<"Please enter valid amount"<<endl;
        return ;
    }

    bfs((state) {0, 0}, path);
    if (path.empty())
    {
        printf("0\n");
        printf("Target cannot be reached.\n");
    }
    else
    {
        // Length of shortest path
        cout<<1<<endl;
        int path_length = path.size();
        //printf("Required number of steps are: ");
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

}

void for_n3()
{
     stack < pair < state2 , int > > path;

    cout<<"Please enter capacity of first jug"<<endl;
    cin >> capacity_x;

    cout<<"Please enter capacity of second jug"<<endl;
    cin >> capacity_y;

    cout<<"Please enter capacity of third jug"<<endl;
    cin >> capacity_z;

    cout<<"Please enter desired amount of  water in first jug"<<endl;
    cin>>req_x;

    cout<<"Please enter desired amount of  water in second jug"<<endl;
    cin>>req_y;

    cout<<"Please enter desired amount of  water in third jug"<<endl;
    cin>>req_z;


    if(req_x > capacity_x  || req_y > capacity_y || req_z > capacity_z || req_x < 0 || req_y < 0 || req_z < 0)
    {
        cout<<"Please enter valid amount"<<endl;
        return ;
    }

    bfs2((state2) {0, 0, 0}, path);

    if (path.empty())
    {
        printf("0\n");
        printf("Target cannot be reached.\n");
    }
    else
    {
        // Length of shortest path
        int path_length = path.size();
         printf("Required number of steps are: \n");
         cout<<path_length -1<< endl;

        vector <int> rules;
        state2 top;
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
                    cout << "Completely fill the third jug\n";
                }
                else if(rule==4){
                    cout << "Completely empty the first jug\n";
                }
                else if(rule==5){
                    cout << "Completely empty the second jug\n";
                }
                else if(rule==6){
                    cout << "Completely empty the third jug\n";
                }
                else if(rule==7){
                    if(top.x < capacity_x){
                        cout << "Pour all the water from second jug to first jug\n";
                    }
                    else{
                        cout << "Completely fill the first jug from second jug\n";
                    }

                }
                else if(rule==8){

                    if(top.x < capacity_x){
                        cout << "Pour all the water from third jug to first jug\n";
                    }
                    else{
                        cout << "Completely fill the first jug from third jug\n";
                    }

                }
                else if(rule==9){

                    if(top.y < capacity_y){
                        cout << "Pour all the water from first jug to second jug\n";
                    }
                    else{
                        cout << "Completely fill the second jug from first jug\n";
                    }

                }
                else if(rule==10){
                  if(top.y < capacity_y){
                        cout << "Pour all the water from third jug to second jug\n";
                    }
                    else{
                        cout << "Completely fill the second jug from third jug\n";
                    }

                }
                else if(rule==11){
                  if(top.z < capacity_z){
                        cout << "Pour all the water from first jug to third jug\n";
                    }
                    else{
                        cout << "Completely fill the third jug from first jug\n";
                    }

                }
                else if(rule==12){
                  if(top.z < capacity_z){
                        cout << "Pour all the water from second jug to third jug\n";
                    }
                    else{
                        cout << "Completely fill the third jug from second jug\n";
                    }

                }
                cout << top.x << endl;
                cout << top.y << endl;
                cout << top.z << endl;
            }


        }
    }
}

void modified_bfs2(state2 start, stack <pair <state2, int> >& path)
{
    queue <state2> q;
    state2 goal = (state2) {-1, -1 , -1};

    //cout<<capacity_z<<endl;

    map <state2, pair <state2, int> > parent;

    q.push(start);

    parent[start] = make_pair(start, 0);

    while (!q.empty())
    {
        state2 top = q.front();
        q.pop();
        //cout<<top.x<<" "<<top.y<<" "<<top.z<<endl;
        // If the target state is found then end the bfs algorithm
        if (top.x == req_x && top.y == req_y ) {
            goal = top;
            break;
        }

        // OPTION-4: Completely empty the first jug
        if (top.x > 0)  {
            state2 child = (state2) {0, top.y , top.z};
            if (parent.find(child) == parent.end()) {
                q.push(child);
                parent[child] = make_pair(top, 4);
            }
        }

        // OPTION-5: Completely empty the second jug
        if (top.y > 0)  {
            state2 child = (state2) {top.x, 0,top.z};
            if (parent.find(child) == parent.end()) {
                q.push(child);
                parent[child] = make_pair(top, 5);
            }
        }



        // OPTION-7: Fill the first jug till its capacity is reached or the second jug is empty
        //(fill from second to first)
        if (top.y > 0)  {
            state2 child = (state2) {min(top.x + top.y, capacity_x), max(0, top.x + top.y - capacity_x),top.z};
            if (parent.find(child) == parent.end()) {
                q.push(child);
                parent[child] = make_pair(top, 7);
            }
        }



        // OPTION-8: Fill the first jug till its capacity is reached or the third jug is empty
        //(fill from third to first)
        if (top.z > 0)  {
            state2 child = (state2) {min(top.x + top.z, capacity_x),top.y,max(0, top.x + top.z - capacity_x) };
            if (parent.find(child) == parent.end()) {
                q.push(child);
                parent[child] = make_pair(top, 8);
            }
        }

        // OPTION-9: Fill the second jug till its capacity is reached or the first jug is empty
        //(fill from first to second)
        if (top.x > 0)  {
            state2 child = (state2) {max(0, top.x + top.y - capacity_y),min(top.x + top.y, capacity_y),top.z};
            if (parent.find(child) == parent.end()) {
                q.push(child);
                parent[child] = make_pair(top, 9);
            }
        }



        // OPTION-10: Fill the second jug till its capacity is reached or the third jug is empty
        //(fill from third to second)
        if (top.z > 0)  {
            state2 child = (state2) {top.x,min(top.y + top.z, capacity_y),max(0, top.y + top.z - capacity_y) };
            if (parent.find(child) == parent.end()) {
                q.push(child);
                parent[child] = make_pair(top, 10);
            }
        }


    }

    // Goal is not reachable
    if (goal.x == -1 || goal.y == -1 || goal.z == -1)
        return;

    // Push the path from start to target onto a stack
    path.push(make_pair(goal, 0));
    while (parent[path.top().first].second != 0)
        path.push(parent[path.top().first]);

}

void modified_for_n3()
{
     stack < pair < state2 , int > > path;

    cout<<1<<endl;
    //cout<<"Please enter capacity of first jug"<<endl;
    cin >> capacity_x;
    cout<<capacity_x<<endl;
    //cout<<"Please enter capacity of second jug"<<endl;
    cin >> capacity_y;
    cout<<capacity_y<<endl;
    //cout<<"Please enter total Amount of Water in source jug"<<endl;
    cin >> capacity_z;
    cout<<capacity_z<<endl;

    //cout<<"Please enter desired amount of  water in first jug"<<endl;
    cin>>req_x;
    cout<<req_x<<endl;
    //cout<<"Please enter desired amount of  water in second jug"<<endl;
    cin>>req_y;
    cout<<req_y<<endl;



    if(req_x > capacity_x  || req_y > capacity_y  || req_x < 0 || req_y < 0 )
    {
        cout<<"0"<<endl;
        cout<<"Please enter valid amount"<<endl;
        return ;
    }

    modified_bfs2((state2) {0, 0, capacity_z}, path);

    if (path.empty())
    {
        printf("0\n");
        printf("Target cannot be reached.\n");
    }
    else
    {
        // Length of shortest path
        cout<<1<<endl;
        int path_length = path.size();
         //printf("Required number of steps are: \n");
         cout<<path_length -1<< endl;

        vector <int> rules;
        state2 top;
        for(int i=0; i<path_length; i++){
            top = path.top().first;

            rules.push_back(path.top().second);
            path.pop();
            if(i==0){
                continue;
            }
            else{
                int rule = rules[i-1];

                if(rule==4){
                    cout << "Completely empty the first jug\n";
                }
                else if(rule==5){
                    cout << "Completely empty the second jug\n";
                }
                else if(rule==6){
                    cout << "Completely empty the third jug\n";
                }
                else if(rule==7){
                    if(top.x < capacity_x){
                        cout << "Pour all the water from second jug to first jug\n";
                    }
                    else{
                        cout << "Completely fill the first jug from second jug\n";
                    }

                }
                else if(rule==8){

                    if(top.x < capacity_x){
                        cout << "Pour all the water from source to first jug\n";
                    }
                    else{
                        cout << "Completely fill the first jug from source\n";
                    }

                }
                else if(rule==9){

                    if(top.y < capacity_y){
                        cout << "Pour all the water from first jug to second jug\n";
                    }
                    else{
                        cout << "Completely fill the second jug from first jug\n";
                    }

                }
                else if(rule==10){
                  if(top.y < capacity_y){
                        cout << "Pour all the water from source to second jug\n";
                    }
                    else{
                        cout << "Completely fill the second jug from source\n";
                    }

                }


                cout << top.x << endl;
                cout << top.y << endl;
                cout << top.z << endl;
            }


        }
    }

}

int main()  {

    //freopen ("input.txt","r",stdin);
    //freopen ("output1.txt","w",stdout);


    int n;
    //cout<<"Please enter number of jugs you want to use, 2 or 3"<<endl;
    cin>>n;
    if(n!=2 && n!=3)
    {
            cout<<"Please enter valid number"<<endl;
            return 0;
    }


    if(n==2)
    {
       // cout<<"Is amount of water limited or not? Press 1 if limited , 0 otherwise"<<endl;
        int temp;
        cin>>temp;
        if(temp==1)
        {
               modified_for_n3();
        }
        else if(temp==0)
        {

        for_n2();
        }
        else
        {
            cout<<"Enter a valid number"<<endl;
            return 0;
        }
    }
    else if(n==3)
    {
        for_n3();
    }

    return 0;
}
