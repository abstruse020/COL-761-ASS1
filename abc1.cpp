#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <iterator>
#include <vector>
#include <set>
#include <algorithm>
#include <cstdlib>

using namespace std;

bool sortfun(const vector<int>& v1, const vector<int>& v2) {
    return to_string(v1[0]) < to_string(v2[0]);
}

int main(int argc, char **argv)
{
    int X = atoi(argv[1]);
    string f(argv[2]);
    ifstream f1;
    f1.open("webdocs.dat", ios::in);
    string transaction;
    int num_trans = 0;
    map<int, int> mp;
    // cout << "Starting to read transactions:" << endl;
    int i=0;
    vector<vector<int>> items;
    while(getline(f1, transaction))
    {
        // if(i%10000==0) cout << i << " ";
        // i++;
        stringstream ss(transaction);
        int x;
        while(ss >> x) {
            auto it = mp.find(x);
            if(it==mp.end()) mp.insert({x, 1});
            else it->second += 1;
        }
        num_trans++;
    }
    double cnt = X/100.0 * num_trans;
    for(auto it=mp.begin();it!=mp.end();it++) {
        if(it->second >= cnt) {
            vector<int> nw{it->first};
            items.push_back(nw);
        }
    }
    // cout << "Number of items: " << mp.size();
    // cout << "Num items above support: " << items.size();
    mp.clear();
    map<vector<int>,int> mp1;
    vector<vector<int>> next;
    // sort items
    sort(items.begin(),items.end(),sortfun);
    ofstream f2;
    f2.open(f+".txt");
    while(items.size()>0) {
        // set cursor to beginning
        f1.clear();
        f1.seekg(0);
        // write items to file
        for(auto it1=items.begin();it1!=items.end();it1++) {
            for(auto it2=(*it1).begin();it2!=(*it1).end();it2++) {
                f2 << *it2 << " ";
            }
            f2 << endl;
        }
        // create next itemsets from items
        for(auto it1=items.begin();it1!=items.end();it1++) {
            bool merge = true;
            // case 1 : 1,2,..,k-1,x  1,2,..,k-1,y
            for(auto it2=it1+1;it2!=items.end();it2++) {
                vector<int> v1 = *it1;
                vector<int> v2 = *it2;
                // if v1 and v2 have k-1 elements in common
                for(int i=0;i<v1.size()-1;i++) {
                    if(v1[i]!=v2[i]) {merge =false;break;}
                }
                
                if(!merge) break;
                vector<int> v = v1;
                v.push_back(v2[v2.size()-1]);
                next.push_back(v);
            }
        }
        items.clear();
        // iterate through each transaction
        // count must be more than support
        mp1.clear();
        for(int i=0;i<next.size();i++) mp1.insert({next[i], 0});
        while(getline(f1, transaction))
        {
            stringstream ss(transaction);
            int x;
            set<int> tmp;
            while(ss >> x) {
                tmp.insert(x);
            }
            // for each vector in next
            // if all elements are in tmp
            // increase count 
            for(int i=0;i<next.size();i++) {
                bool all = true;
                for(int j=0;j<next[i].size();j++) {
                    if(tmp.find(next[i][j]) == tmp.end()) {
                        all = false; break;
                    }
                }
                if(all) mp1.find(next[i])->second += 1;
            }
        }
        // add to items if value is greater than or equal to count
        for(int i=0;i<next.size();i++) {
            auto a = mp1.find(next[i]);
            if(a->second >= cnt) items.push_back(next[i]);
        }
        next.clear();
    }
    f1.close();
    return 0;
}