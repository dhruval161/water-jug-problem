#include <bits/stdc++.h>
#include <windows.h>

#define pii pair < int , int >
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
using namespace std;


// Clearing the screen in terminal
void clear() {
    COORD topLeft  = { 0, 0 };
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    SetConsoleCursorPosition(console, topLeft);
}


int capacity_x, capacity_y, target;
map < pii, pair < pii , int > > parent;
map < pii , int > dist;
pii goal=mkp(-1,-1);
bool found=false;

bool cmp( pair < pii , pii > a, pair < pii , pii > b)
{
	int g1= a.se.se;
	int g2= b.se.se;
	int h1=abs(a.fi.fi - target)+abs(a.fi.se - target);
	int h2=abs(b.fi.fi - target)+abs(b.fi.se - target);
	if(g1+h1 <= g2+h2) return true;
	else return false;
}
void aStarSearch( pii node)
{
	if(node.fi==target || node.se == target){
		found=true;
		goal=node;
		return ;
	}
	vector < pair < pii , pii > > v;
	
	v.pb(mkp(mkp(capacity_x,node.se),mkp(1,1+dist[node])));
	v.pb(mkp(mkp(node.fi,capacity_y),mkp(2,1+dist[node])));
	v.pb(mkp(mkp(0,node.se),mkp(3,1+dist[node])));
	v.pb(mkp(mkp(node.fi,0),mkp(4,1+dist[node])));
	v.pb(mkp(mkp(min(node.fi+node.se, capacity_x),max(0,node.fi+node.se - capacity_x)),mkp(5,1+dist[node])));
	v.pb(mkp(mkp(max(0,node.fi+node.se - capacity_y),min(node.fi+node.se,capacity_y)),mkp(6,1+dist[node])));
	sort(v.begin(),v.end(),cmp);
	for(int i=0; i<v.size(); i++){
		pair < pii , pii > a = v[i];
		if(found) return;
		if(parent.find(a.fi)!=parent.end()){
			continue;
		}		
		parent[a.fi]=mkp(node,a.se.fi);
		dist[a.fi]=1+dist[node];
		aStarSearch(a.fi);
	}

}


void draw_border()
{
	cout << endl;
	for (int i=0; i<168; i++){
		cout << "*";
	}
	cout << endl;
}

bool ok=false;
inline void WaitEnter() 
{ 	
	if(ok)
	cout << "Press Enter to continue..."; 
	while (std::cin.get()!='\n'); 
}

bool check(int a, int b, int c)
{
	
	if(c%(__gcd(a,b))!=0 || c>max(a,b)) return false;
	else return true;
}

int main()
{
	clear();
	cout << "Maximum capacity of first jug: ";
    cin >> capacity_x;
    cout << "Maximum capacity of second jug: ";
    cin >> capacity_y;
    cout << "Target amount to be achieved: ";
    cin >> target;
    draw_border();
    if( !check (capacity_x, capacity_y, target) ){
    	printf("\nTarget cannot be reached.\n");
    	return 0;
    }
	dist[mkp(0,0)]=0;
	parent[mkp(0,0)]=mkp(mkp(0,0),0);
	aStarSearch(mkp(0,0));
	stack < pii > st;
	pii a = goal;
	vector <int> rules;
	while(1){
		if(a!=mkp(0,0)){
			rules.pb(parent[a].se);
		}
		st.push(a);
		if(a==mkp(0,0)) break;
		a=parent[a].fi;
	}
	reverse(rules.begin(),rules.end());
	int tot=st.size();
	cout << "The number of steps to reach the goal state is "<<tot -1<< " steps." << endl;
	WaitEnter();
	ok=true;
	draw_border();
	pii top;
	for(int i=0; i<tot; i++){
		top = st.top();
		st.pop();
		if(i==0){
			cout << "INITIAL STATE\n";
            cout << "Amount of water in first jug: "<< top.fi << endl;
            cout << "Amount of water in second jug: "<< top.se << endl;
		}	
		else{
			int rule = rules[i-1];
            	cout << "STEP NUMBER: " << i << endl;
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
            		if(top.fi < capacity_x){
            			cout << "Pour all the water from second jug to first jug\n";
            		}
            		else{
            			cout << "Completely fill the first jug from second jug\n";
            		}

            		
            	}
            	else{
					if(top.se < capacity_y){
            			cout << "Pour all the water from first jug to second jug\n";
            		}
            		else{
            			cout << "Completely fill the second jug from first jug\n";
            		}            		
            	}

            	cout << "Amount of water in first jug: "<< top.fi << endl;
            	cout << "Amount of water in second jug: "<< top.se << endl;
		}
		WaitEnter();
		draw_border();
	}
	if(top.fi == target) cout << "The first jug contains the required amount of water\n";
    else cout << "The second jug contains the required amount of water\n";
		
	
		
	return 0;
}