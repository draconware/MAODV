#include<bits/stdc++.h>
using namespace std;

#define N 5

struct Request_Packet{
	int source;
	int destination;
	int seq_no;
	int hop_cnt;
	int flag;
	int previous;
};

struct Reply_Packet{
	int source;
	int hop_cnt;
	int seq_no;
	int flag;
};

struct Route_Table{
	int destination;
	int next;
	int seq_no;
};
	
int Graph[N+2][N+2];
vector<Route_Table> routing_table[N+2];
stack<int> st;
bool mark[N+2];

bool search_route_table(int node,int des,int no){
	for(int i=0;i<(int)routing_table[node].size();i++){ //routing table entry maintains all the routes that this node is involved in
		Route_Table rt = routing_table[node][i];
		if(rt.seq_no != no && rt.destination == des){ // here we check whether that node is containing a path that leads to destination "des"
			return true;
		}
	}
	return false;
}

Reply_Packet explore_path(Request_Packet rp){
	//cout<<rp.source<<endl;
	Reply_Packet rp1;
	int node = rp.source,par = rp.previous; //node here is current node and par is the parent node of node
	mark[node] = true;
	if(rp.destination == rp.source){
		st.push(rp.source);
		rp1.source = node;rp1.hop_cnt = 0;rp1.seq_no = rp.seq_no;rp1.flag = 1;
		return rp1;
	}

	int pos_sig=0; // pos_sig means all nodes which are not used before in exploring a path from s to d
	int neg_sig=0; // neg_sig means all nodes which are used before in exploring a path from s to d
	for(int i=1;i<=N;i++){
		if(i==node || i==par || Graph[i][node]==0){continue;}
		if(!search_route_table(i,rp.destination,rp.seq_no)){
			pos_sig++; // incrementing pos_sig if a node of this type found
		}else{
			neg_sig++; // incrementing neg_sig if node is not found participating in path previously
		}
	}

	int f=0;
	for(int i=1;i<=N;i++){
		if(i==node || i==par || Graph[node][i]==0 || mark[i]){continue;}
		if(search_route_table(i,rp.destination,rp.seq_no)){
			if(rp.flag == 1){ // in this case if previous path is available and till now explored path is different than we have found a new path
				rp.source = i;
				rp.hop_cnt++;
				rp.previous = node;
				rp1 = explore_path(rp);
				f=1;
			}else if(pos_sig==0){ // in this case if previous path is available and no new path is available 
				rp.source = i;
				rp.hop_cnt++;
				rp.previous = node;
				rp.flag = 1;
				rp1 = explore_path(rp);
				f=1;
			}
		}else{
			if(rp.flag==1){
				if(neg_sig>0){continue;} // Case if we are allowed to use explored paths 
				else{
					rp.source = i;
					rp.hop_cnt++;
					rp.previous = node;
					rp1 = explore_path(rp);
					f=1;
				}
			}else{
				rp.source = i;
				rp.hop_cnt++;
				rp.previous=node;
				rp.flag=1;
				rp1 = explore_path(rp);
				f=1;
			}
		}
		if(rp1.flag == 1){
			Route_Table rt;
			rt.destination = rp.destination;
			rt.next = rp1.source;
			rt.seq_no = rp.seq_no;
			st.push(node);
			routing_table[node].push_back(rt);
			rp1.source = node;
			rp1.hop_cnt++;
			mark[node] = false;
			return rp1;
		}
	}
	rp1.source = rp.source;
	rp1.hop_cnt = 0;
	rp1.seq_no = rp.seq_no;
	rp1.flag = 0;
	mark[node] = false;
	return rp1;
}

void find_path(int s,int d,int idx){
	for(int i=1;i<=N;i++){mark[i] = false;}
	Request_Packet rp;
	rp.source = s;
	rp.destination = d;
	rp.hop_cnt = 0;
	rp.seq_no = idx;
	rp.flag=0;
	rp.previous = s;
	explore_path(rp);
}

void maodv(int paths,int source,int destination){
	for(int i=0;i<paths;i++){
		find_path(source,destination,i+1);
		if(st.empty()){
			cout<<"PATH doesn't exist"<<endl;
			break; 
		}
		cout<<"PATH "<<i+1<<" --------------- "<<endl;
		while(!st.empty()){
			cout<<st.top()<<" ";
			st.pop();
		}
		cout<<endl;
	}
}

void generating_graph(){
	for(int i=2;i<=5;i++){
		Graph[1][i] = 1;
		Graph[i][1] = 1;
	}
	Graph[2][3] = Graph[2][5] =1;Graph[3][2] = Graph[5][2] = 1;
	Graph[3][5] = 1;Graph[5][3] = 1;
	Graph[4][5] = 1;Graph[5][4] = 1;
}

int main(){
	generating_graph(); //generating a N*N matrix which represents a graph

	int source,destination,paths;
	cout<<"Source : ";cin>>source;
	cout<<"Destination :";cin>>destination;
	cout<<"Paths Required :";cin>>paths;

	maodv(paths,source,destination); //give arguments as number of paths required, source node, destination node
}