#include <iostream>
#include <vector>
#include "map"
#include<fstream>
using namespace std;
//jiecheng
int jiecheng(int a){
    if(a==1){
        return 1;
    } else
        return jiecheng(a-1)*a;
}
vector<int> De(int a){
    vector<int> A;
    for (int i = 0; i <jiecheng(a-1); ++i) {
        A.push_back(i);
    }
    return A;
}
vector<vector<int>> DE2(vector<int> a){
    vector<vector<int>> b;
    for (int i = 0; i <a.size() ; ++i) {
        b.push_back(De(a[i]));
    }
    return b;
}
vector<vector<int>> C_mul(vector<vector<int>> A,vector<int> B) {
    vector<vector<int>> D;
    vector<int> C;

    for (int i = 0; i < A.size(); ++i) {
        for (int j = 0; j <B.size(); ++j) {
            C=A[i];
            C.push_back(B[j]);
            D.push_back(C);
        }
    }
    return  D;
}
vector<vector<int>> C_mul2(vector<vector<int>> deal){
    vector<vector<int>> out;
    for (int i = 0; i <deal[0].size() ; ++i) {
        for (int j = 0; j < deal[1].size(); ++j) {
            out.push_back({deal[0][i],deal[1][j]});
        }
    }
    for (int k = 2; k <deal.size(); ++k){
        out=C_mul(out,deal[k]);
    }
    return out;
}
bool find(int A,vector<int> B){
    for (int i = 0; i <B.size(); ++i) {
        if(B[i]==A){
            return true;
        }
    }
    return false;
}

map<int,int> buid(vector<vector<int>> A){
    map<int,int> a;
    for (int i = 0; i <A.size(); ++i) {
        for (int j = 0; j < A[i].size(); ++j) {
            if(j+1<A[i].size()){
                a[A[i][j]]=A[i][j+1];
            } else{
                a[A[i][A[i].size()-1]]=A[i][0];
            }
        }
    }
    return a;

}
vector<int> gian(map<int,int> mymap){
    vector<int> A;
    _Rb_tree_iterator<pair<const int, int>> iter;
    for(iter=mymap.begin(); iter!=mymap.end(); iter++)
        A.push_back(iter->first);
    return A;
}
vector<int> cal(int i,map<int,int> dic,vector<int> dic_key){
    vector<int> k;
    int A=dic[i];
    k.push_back(i);
    while (A!=i){
        if(find(A,dic_key)){
            k.push_back(A);
        }
        A=dic[A];
    }
    return k;

}
vector<vector<int>> fw(map<int,int> dic){
    vector<int> k;
    vector<vector<int>> j;
    while (!dic.empty()){
        k=cal(dic[gian(dic)[0]],dic,gian(dic));
        j.push_back(k);
        for (int i = 0; i <k.size(); ++i) {
            dic.erase(k[i]);
        }
    }
    return j;
}
map<int,int> calp(map<int,int>mapA,map<int,int>mapB){

    vector<int>gian_mapA=gian(mapA);
    vector<int>gian_mapB=gian(mapB);

    for(int i=0;i<gian(mapA).size();i++){
        if (find(mapA[gian(mapA)[i]],gian(mapB))){
            mapA[gian(mapA)[i]]=mapB[mapA[gian(mapA)[i]]];
        }

    }
    for (int j = 0; j <gian(mapB).size() ; ++j) {
        if(find(mapB[gian(mapB)[j]],gian(mapA))){
            mapB.erase(mapB[gian(mapB)[j]]);
        }
    }
    mapA.insert(mapB.begin(),mapB.end());
    return mapA;
}
void print_map(map<int,int> amap){
    for (const auto &i :amap ) {
        std::cout << i.first << ':' << i.second << ' ';
    }
    std::cout << '\n';
}
void print_outcome(vector<vector<int>> vec){
    for (int i = 0; i <vec.size(); ++i) {
        for (int j = 0; j < vec[i].size(); ++j) {
            if(vec[i].size()==1){
                cout<<"("<<vec[i][j]<<")";
            }
            else if (j==0){
                cout<<"("<<vec[i][j]<<",";
            }
            else if(j==vec[i].size()-1){
                cout<<vec[i][j]<<")";
            }
            else{
                cout<<vec[i][j]<<",";

            }
        }
    }
}
struct Edge{
    string name;
    int t_edge[2][2];//特征边
    int k;//计次第几条边
    int j=0;//正负性判断
    vector<vector<int>> r;//gama的对
};
struct Node{
    string name;
    vector<Node> neb_nodes;
    vector<Edge> edge_list;
    vector<vector<int>> circle_sort;
    vector<vector<int>> circle_sortmin;
    vector<int> cic_2;
    vector<int> cic;

};
#include <iostream>
#include <algorithm>
#include "vector"
using namespace std;
bool check_equal(int SIZE,int arrayA[],std::vector<int>arrayB){
    bool arraysEqual = true; // 标志变量
    int count = 0; //循环控制变量
//确定元素是否包含相同的数据
    while (arraysEqual && count < SIZE)
    {
        if (arrayA[count] != arrayB[count])
            arraysEqual = false;
        count++;
    }
    return arraysEqual;
}
bool if_circle(std::vector<int> a,std::vector<int> b,int size){
    using namespace std;
    bool mark = false;
    int c[size];
    int A[size];
    for (int j = 0; j <size; ++j) {
        c[j]=a[j];
    }
    for(int i=0;i<size;i++) {
        for (int k = 0; k < size; k++) {
            if (k + 1 < size) {
                A[k] = c[k + 1];
            } else {
                A[k] = c[0];
            }

        }
        if (check_equal(size, A, b)) {
            mark= true;
            return mark;
        }
        for (int j = 0; j <size; ++j) {
            c[j]=A[j];
        }

    }
    return mark;
}
vector<vector<int>> circle_sort(int dem){
    int nuu=dem;
    using namespace std;
    vector<int>B;
    int num[nuu];
    for (int n = 0; n < nuu; ++n) {
        num[n]=n+1;
    }
    vector<vector<int>>BB;
    do
    {
        for (int i = 0; i < nuu; ++i) {
            B.push_back(num[i]);
        }
        BB.push_back(B);
        B={};
    }while(next_permutation(num,num+nuu));
    vector<int> save;
    for (int j = 0; j < BB.size(); ++j) {
        for (int i = j+1; i < BB.size(); ++i) {
            if(BB[j][0]!=0){
                if(if_circle(BB[j],BB[i],BB[0].size())==1){
                    save.push_back(i);
                }
            }
        }
        for (int k = 0; k <save.size(); ++k) {
            BB[save[k]][0]=0;
        }
        save={};
    }
    vector<int> count;
    vector<vector<int>> count2;

    for (int l = 0; l < BB.size(); ++l) {
        for (int i = 0; i <BB[0].size(); ++i) {
            if(BB[l][0]!=0){
                count.push_back(BB[l][i]);
            }
        }
        if(!count.empty())
            count2.push_back(count);
        count={};
    }
    return count2;
}
int printVec(vector<vector<int>> count2){
    for (int m = 0; m <count2.size(); ++m) {
        for (int i = 0; i < count2[0].size(); ++i) {
            cout<<count2[m][i]<<" ";
        }
        cout<<endl;
    }
}




struct Smap{
    string name;
    int node_num;
    vector<vector<int>> matrix;
    vector<Node> node_list;
};

int main() {
    string node_;
    cout<<"请输入图的点名";
    cin>>node_;
    cout<<node_;
    cout<<"图的顶点数为:"<<node_.size();
    cout<<"请输入其稀疏矩阵:"<<endl;

    int size=node_.size();
    vector<Node> node_list;
    vector<Edge> edge_list;
    int a[size][size];
    int icount, jcount;
    // 利用双重循环遍历输出矩阵A
    for (icount=0;icount<size;icount++)
    {
        for (jcount=0;jcount<size;jcount++)
        {
            scanf("%d",&a[icount][jcount]);
        }
    }
    // 利用双重循环遍历输出矩阵B
    printf("邻接矩阵为:\n");
    for (icount=0;icount<size;icount++)
    {
        for (jcount=0;jcount<size;jcount++)
        {
            printf("%8d",a[icount][jcount]);
        }
        printf("\n");
    }
//    -------------------------------------------------------------------
    for (int i = 0; i < size; ++i) {
        Node node;
        node.name = node_[i];
        node_list.push_back(node);

    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (a[i][j] == 1) {
                node_list[i].neb_nodes.push_back(node_list[j]);

            }

        }
    }
    int k = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = i; j < size; ++j) {
            if (a[i][j] == 1) {
                Edge edge;
                edge.name = string(1, node_[i]) + string(1, node_[j]);
                edge.k = k;
                edge.t_edge[0][0] = k * 4 + 1;
                edge.t_edge[0][1] = k * 4 + 2;
                edge.t_edge[1][0] = k * 4 + 3;
                edge.t_edge[1][1] = k * 4 + 4;
                k += 1;
                edge_list.push_back(edge);
            }

        }

    }
    cout<<"含有的边为:"<<endl;
    for (int i = 0; i < edge_list.size(); i++) {
        cout << edge_list[i].name << "编号为"<<edge_list[i].k*4+1<<"到"<<edge_list[i].k*4+4<<endl;
    }
    for (int i = 0; i < node_list.size();i++) {
        for(int j=0;j<edge_list.size();j++){
            if(edge_list[j].name.find(node_list[i].name)!=edge_list[j].name.npos){
                node_list[i].edge_list.push_back(edge_list[j]);
            }
        }
    }
    cout<<"与各顶点关联的边为:"<<endl;
    for (int l = 0; l <node_list.size() ; ++l) {
        cout<<node_list[l].name<<" :";
        for(int j=0;j<node_list[l].edge_list.size();j++){
            cout<<node_list[l].edge_list[j].name+" ";
        }
        cout<<endl;
    }
    cout<<"输出的结果为:"<<endl;
    //存入所有edge的r
    vector<vector<int>> totaledge;
    for (int l1 = 0; l1 <edge_list.size() ; ++l1) {
        int a;
        cout<<"定义"<<edge_list[l1].name<<"正负为（0为正，负为1）：";
        cin>>a;
        edge_list[l1].j=a;
    }
    for (int i1 = 0; i1 <edge_list.size() ; ++i1) {
        if(edge_list[i1].j==0){
            vector<int> first;
            vector<int> second;
            first.push_back(edge_list[i1].t_edge[0][0]);
            first.push_back(edge_list[i1].t_edge[1][1]);
            second.push_back(edge_list[i1].t_edge[0][1]);
            second.push_back(edge_list[i1].t_edge[1][0]);
            totaledge.push_back(first);
            totaledge.push_back(second);

            edge_list[i1].r.push_back(first);
            edge_list[i1].r.push_back(second);

        } else{
            vector<int> first;
            vector<int> second;
            first.push_back(edge_list[i1].t_edge[0][0]);
            first.push_back(edge_list[i1].t_edge[1][0]);
            second.push_back(edge_list[i1].t_edge[0][1]);
            second.push_back(edge_list[i1].t_edge[1][1]);
            totaledge.push_back(first);
            totaledge.push_back(second);
            edge_list[i1].r.push_back(first);
            edge_list[i1].r.push_back(second);
        }
    }
    for (int m = 0; m<edge_list.size(); ++m) {
        if (edge_list[m].j == 0) {
            cout << "r" << edge_list[m].name << "=";
            cout << "(" << edge_list[m].t_edge[0][0] << "," <<
                 edge_list[m].t_edge[1][1] << ")";
            cout << "(" << edge_list[m].t_edge[0][1] << "," <<
                 edge_list[m].t_edge[1][0] << ")";
            cout << endl;
        } else {
            cout << "r" << edge_list[m].name << "=";
            cout << "(" << edge_list[m].t_edge[0][0] << "," <<
                 edge_list[m].t_edge[1][0] << ")";
            cout << "(" << edge_list[m].t_edge[0][1] << "," <<
                 edge_list[m].t_edge[1][1] << ")";
            cout << endl;
        }
    }
    vector<vector<int>> CC;
    for (int i = 0; i <node_list.size(); ++i) {
        vector<int> C;
        for (int j = 0; j <node_list[i].edge_list.size(); ++j) {
            int a;
            if(node_list[i].edge_list[j].name.find(node_list[i].name)==0){
                a=node_list[i].edge_list[j].t_edge[0][0];
            } else{
                a=node_list[i].edge_list[j].t_edge[1][1];
            }
            C.push_back(a);
            ;
        }
        node_list[i].cic=C;

        cout<<endl;
        CC.push_back(C);
    }

    for (int n = 0; n < CC.size(); ++n) {
        cout<<"∏"<<node_list[n].name<<"="<<"(";
        for (int i = 0; i < CC[0].size(); ++i) {
            if(i==CC[0].size()-1){
                cout<<CC[n][i];
            }
            else{
                cout<<CC[n][i]<<",";
            }
        }
        cout<<")"<<endl;
    }
    vector<vector<int>>BB;
    for (int i = 0; i <node_list.size(); ++i) {
        vector<int> C;
        for (int j = 0; j <node_list[i].edge_list.size(); ++j) {
            int a;
            if(node_list[i].edge_list[j].name.find(node_list[i].name)==0){
                a=node_list[i].edge_list[j].t_edge[0][1];
            } else{
                a=node_list[i].edge_list[j].t_edge[1][0];
            }
            C.push_back(a);

        }
        node_list[i].cic_2=C;
        BB.push_back(C);
    }
    for (int n = 0; n < BB.size(); ++n) {
        cout<<"α∏"<<node_list[n].name<<"="<<"(";
        for (int i = 0; i < BB[0].size(); ++i) {
            if(i==BB[0].size()-1){
                cout<<BB[n][i];
            }
            else{
                cout<<BB[n][i]<<",";
            }
        }
        cout<<")"<<endl;
    }
    for (int j1 = 0; j1 < node_list.size(); ++j1) {
        vector<vector<int>> circle_s=circle_sort(node_list[j1].edge_list.size());
        vector<int> tmp=node_list[j1].cic;
        vector<vector<int>> tmp3;
        for (int i = 0; i <circle_s.size() ; ++i) {
            vector<int> tmp2={};
            for (int j = 0; j <circle_s[0].size() ; ++j) {
                tmp2.push_back(tmp[circle_s[i][j]-1]);
            }
            tmp3.push_back(tmp2);
        }
        node_list[j1].circle_sort=tmp3;//circle_sort是每个点的圆排列表
    }
    int coutp=0;
    int coutpm=0;
    int coutpp=0;
    int coutppm=0;
    for (int j1 = 0; j1 < node_list.size(); ++j1) {
        vector<vector<int>> circle_s=circle_sort(node_list[j1].edge_list.size());
        vector<int> tmp=node_list[j1].cic_2;
        vector<vector<int>> tmp3;
        for (int i = 0; i <circle_s.size() ; ++i) {
            vector<int> tmp2={};
            for (int j = 0; j <circle_s[0].size() ; ++j) {
                tmp2.push_back(tmp[circle_s[i][j]-1]);
            }
            tmp3.push_back(tmp2);
        }
        node_list[j1].circle_sortmin=tmp3;
    }
    vector<int> fg;
    for (int k1 = 0; k1 <node_list.size(); ++k1) {
        fg.push_back(node_list[k1].edge_list.size());
    }
    vector<vector<int>> test=DE2(fg);
    vector<vector<int>> A=C_mul2(test);
    cout<<"开始了哦----------------------------"<<endl;
    map<int,int> storage;
    for (int l = 0; l < A.size(); ++l) {
        vector<vector<int>>cic3;
        for (int i = 0; i < A[0].size(); i++) {
            vector<int> cic2 =node_list[i].circle_sort[A[l][i]];
            cic3.push_back(cic2);
        }
        for (int j = 0; j < A[0].size(); ++j) {
            vector<int> cic2 =node_list[j].circle_sortmin[A[l][j]];
            cic3.push_back(cic2);
        }
        map<int,int> outcome=calp(buid(totaledge),buid(cic3));
        vector<vector<int>>out2=fw(outcome);
        print_outcome(out2);
        storage[out2.size()]+=1;
//        if(out2.size()==2){
//            coutp+=1;
//        }
//        if(out2.size()==4){
//            coutpm+=1;
//        }
//        if(out2.size()==8){
//            coutpp+=1;
//        }
        cout<<endl;
        cout<<"第"<<l+1<<"伦"<<endl;
    }
    vector<int>map_key=gian(storage);
    for(auto i:map_key){
        cout<<i<<"圈的有"<<storage[i]<<"个"<<endl;
    }

//    cout<<"----------------------------------------------测试"<<endl;
//    cout<<"-----------------------------负方向";
//    cout<<"开始了哦----------------------------"<<endl;
//    for (int l = 0; l < A.size(); ++l) {
//        for (int i = 0; i < A[0].size(); i++) {
//            vector<int> cic2 =node_list[i].circle_sortmin[A[l][i]];
//            vector<vector<int>>cic3;
//            cic3.push_back(cic2);
//            for (int k1 = 0; k1 < edge_list.size(); ++k1) {
//                vector<vector<int>> p_vec = edge_list[k1].r;
//                map<int,int> outcome=calp(buid(p_vec),buid(cic3));
//                vector<vector<int>>out2=fw(outcome);
//                print_outcome(out2);
//                cout<<endl;
//
//            }
//        }
//        cout<<"第"<<l+1<<"伦"<<endl;
//    }
//    for (int k1 = 0; k1 < edge_list.size(); ++k1) {
//        vector<vector<int>> p_vec=edge_list[k1].r;
//        for (int i = 0; i <node_list.size(); ++i) {
//            for (int j = 0; j < node_list[i].circle_sortmin.size(); ++j) {
//                vector<int> cic2=node_list[i].circle_sortmin[j];
//                vector<vector<int>>cic3;
//                cic3.push_back(cic2);
//                map<int,int> outcome=calp(buid(p_vec),buid(cic3));
//                vector<vector<int>>out2=fw(outcome);
//                cout<<endl;
////                cout<<out2.size();
////                if(out2.size()==2){
////                    coutpp+=1;
////                }
////                if(out2.size()==3){
////                    coutppm+=1;
////                }
//                print_outcome(out2);
//            }
//        }
//    }
//    cout<<"正轮换括号个数为2的个数为："<<coutp;
//    cout<<"正轮换括号个数为3的个数为："<<coutpm;
//    cout<<"正轮换括号个数为2的个数为："<<coutpp;
//    cout<<"正轮换括号个数为3的个数为："<<coutpm;
    ofstream file;
    file.open("outcome.txt",ofstream::app);
for(auto i:map_key){
        file<<i<<"圈的有"<<storage[i]<<"个"<<endl;
    }
  file.close();

    return 0;

}
