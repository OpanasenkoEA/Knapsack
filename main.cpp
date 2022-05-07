
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <iterator>

using namespace std;

vector < vector<int64_t> > matrix;
vector<int64_t> w;


set<int64_t> knapsack(int64_t i, int64_t j)
{
    if (i==0)
    {
        set<int64_t> res;
        return res;
    }
    
    if (matrix[i][j] > matrix[i-1][j])
    {
        set<int64_t> res1;
        res1 = knapsack(i-1, j - w[i]);
        res1.insert(i);
        return res1;
    }
    else
    {
        set<int64_t>res2;
        res2 = knapsack(i-1, j);
        return res2;
    }


}



int main()
{
    string buf;

    cout << "Knapsack problem!" << endl;

    ifstream file("data/ks_100_0");
    getline(file, buf);
    //cout << buf << endl;

    int i_space = buf.find(' ');
    int64_t N = stoi(buf.substr(0, i_space));
    int64_t K = stoi(buf.substr(i_space+1));

    cout << "N=" << N << ", K=" << K << endl;

    vector<int64_t> v(N);
    w.resize(N);

    for (int64_t i=0; i < N; i++)
    {
        getline(file, buf);
        i_space = buf.find(' ');
        v[i] = stoi(buf.substr(0, i_space));
        w[i] = stoi(buf.substr(i_space+1));
    }


    for (int64_t i=0; i < N; i++)
        cout << v[i] << "\t" << w[i] << endl;



    file.close();


    matrix.resize(N, vector<int64_t>(K+1,0));

    //cout << "test " << max(matrix[5-1][7], matrix[5-1][7-w[5]] + v[5]) << endl;
    //int c = 0;
    for (int64_t i=1; i<N; i++)
    {
        for (int64_t j=0; j<K+1; j++)
        {


            //matrix[i][j] = c++;
            if (w[i] > j)
                matrix[i][j] = matrix[i-1][j];
            else
                matrix[i][j] = max(matrix[i-1][j], matrix[i-1][j-w[i]] + v[i]);

            //cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    set<int64_t> elements;
    elements = knapsack(N-1, K);

    cout << endl;

    vector<int64_t> x;
    x.resize(N, 0);




    set<int64_t>:: iterator it = elements.begin();
    for (int i=1; it != elements.end(); i++, it++)
        x[*it] = 1;


    int64_t total_weight = 0;

    for (int i=0; i< N; i++)
        if (x[i] == 1)
            total_weight += w[i];

    cout << matrix[N-1][K] << "\t" << K-total_weight << endl;
    for (int i=0; i<N; i++)
       cout << x[i] << " ";
    cout << endl;


    return 0;
}
