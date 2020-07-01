/*
 * A slight adaptation of Przemysław Uznański's codebase for generating convex geometries
 * by conversion from antimatroids.
 *
 * See Przemysław Uznański blog:
 * https://paracombinatorics.wordpress.com/2013/04/14/enumeration-of-antimatroids-part-iii/
 *
 * Alexander Frederiksen
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned long long ull;
typedef unsigned int us;


int n = 3;
int N = 1<<n;

const int factorial[] = {1,1,2,6,24,120,720,5040};

/* converts antimatroid to convex geometry (: */
void matroid_to_convexgeo(ull matroid)
{
    cout << "{" << endl;
    for (unsigned int i = 0; i < N; i++)
    {
        int is_matroid_set = (matroid >> i) & 0x01;
        if (is_matroid_set)
        {
            // convert antimatroid to convex geo (take complement)
            int convex_set = ~i;

            cout << "  { ";
            for (unsigned int j = 0; j < n; j++)
            {
                if ((convex_set >> j) & 0x01)
                {
                    cout << (char) ('a' + j) << " ";
                }
            }
            cout << "}" << endl;
        }
    } 
    cout << "}" << endl;
}

class u128
{
    public:
        ull low;
        ull high;
        u128(ull _low=0, ull _high = 0)
        {
            low = _low;
            high = _high;
        }

        bool operator<(const u128& b) const
        {
            return (high==b.high) ? (low<b.low) : (high<b.high);
        }

        bool operator==(const u128& b) const
        {
            return (high==b.high) && (low==b.low);
        }

        u128 operator~() const
        {
            return u128(~low,~high);
        }

        u128 operator&(const u128& b) const
        {
            return u128(low&b.low, high&b.high);
        }

        u128 operator|=(const u128& b)
        {
            low |= b.low;
            high |= b.high;
            return *this;
        }
        u128 operator&=(const u128& b)
        {
            low &= b.low;
            high &= b.high;
            return *this;
        }

        void setbit(unsigned i)
        {
            if(i<64)
                low |= (1ull << i);
            else
                high |= (1ull << (i-64));
        }

        void erasebit(unsigned i)
        {
            if(i<64)
                low &= ~(1ull << i);
            else
                high &= ~(1ull << (i-64));
        }

        bool getbit(unsigned i) const
        {
            return (i<64) ? (low & (1ull << i)) : (high & (1ull << (i-64)));
        }

        void print() const
        {
            matroid_to_convexgeo(low);
        }
};

const int magic = 2000003;
int hash_(const u128& X)
{
    int ret = (X.low%magic)+(X.high%magic);
    return ret<magic?ret:ret-magic;
}
class hashtable
{
    public:
        vector<vector<u128> > table;
        int size;
        hashtable()
        {
            table.resize(magic);
            size = 0;
        }
        void insert(const u128& X)
        {
            int h = hash_(X);
            bool ok = true;
            for(auto& i : table[h])
                if(i==X)
                {
                    ok = false;
                    break;
                }
            if(ok)
            {
                table[h].push_back(X);
                size++;
            }
        }
};


vector<vector<int> > perms;
int psize;
vector<vector<int> > ap;
//vector<int> order;
vector<u128> pred;
vector<u128> succ;

int apply(vector<int> p, int x)
{
    int y = 0;
    for(int i=0;i<n;i++)
        if(x & (1<<i))
            y |= 1<<p[i];
    return y;
}

pair<u128,vector<int> > _reduce(const u128& X)
{
    u128 R;
    vector<int> C = {0};
    vector<int> nC;
    C.reserve(psize);
    nC.reserve(psize);
    R.setbit(0);
    int i=1;
    for(int bit=0;bit<n;bit++)
    {
        int ss = C.size();
        C.resize(ss*(n-bit));
        for(int it=ss;it<ss*(n-bit);it++)
            C[it] = C[it-ss]+factorial[n-1-bit];
        for(;i<(1<<(bit+1));i++)
        {
            nC.clear();
            bool v = false;
            for(auto& t : C)
            {
                bool nv = X.getbit(ap[i][t]);
                if(nv > v)
                {
                    nC.clear();
                    v = nv;
                    R.setbit(i);
                }
                if(nv == v)
                {
                    nC.push_back(t);
                }
            }
            swap(nC,C);
        }
    }
    return make_pair(R,C);
}
u128 reduce(const u128& X)
{
    return _reduce(X).first;
}
vector<int> aut(const u128& X)
{
    return _reduce(X).second;
}


long long ans = 0;
long long ans2 = 0;

vector<u128> onestep(const vector<u128> P)            
{
    hashtable nL;
    for(auto& S : P)
    {
        vector<int> automorph = aut(S);
        ans += psize/automorph.size();
        ans2 += 1;

        cout << ans2 << "." << endl;
        S.print();

        u128 mask(0,0);
        for(int I=1;I<N-1;I++)
            if(S.getbit(I))
                for(int J=1;J<I;J++)
                    if(S.getbit(J))
                    {
                        int IJ = I|J;
                        if(IJ != I && IJ != J)
                            mask.setbit(IJ);
                    }


        mask = S & ~mask;
        u128 f1,f2;
        for(int I=0;I<N;I++)
            if(S.getbit(I))
            {
                f2 |= succ[I] & f1;
                f1 |= succ[I];
            }
        f1 &= ~f2 & S;
        for(int I=0;I<N;I++)
            if(f1.getbit(I))
                mask = mask & ~pred[I];

        for(int I=1;I<N-1;I++)
            if(mask.getbit(I))
            {
                for(int a=0;a<automorph.size();a++)
                    mask.erasebit(ap[I][automorph[a]]);
                u128 nS = S;
                nS.erasebit(I);
                nL.insert(reduce(nS));
            }
    }
    vector<u128> ret;
    for(auto& v : nL.table)
        for(auto& x : v)
            ret.push_back(x);
    return ret;
}


int main()
{
    cout << "Size of base set? ";
    cin >> n;
    N = 1 << n;

    

    pred.resize(N);
    succ.resize(N);
    for(int I=0;I<N;I++)
        for(int i=0;i<n;i++)
            if(I & (1<<i))
                pred[I].setbit(I & ~(1<<i));
            else
                succ[I].setbit(I | (1<<i));
    
    vector<int> start;
    for(int i=0;i<n;i++)
        start.push_back(i);
    do
    {
        perms.push_back(start);
    }
    while(next_permutation(start.begin(),start.end()));
    psize = perms.size();
   
    ap.resize(N, vector<int>(psize));
    for(int p=0;p<psize;p++)
        for(int i=0;i<N;i++)
            ap[i][p] = apply(perms[p], i);

    u128 seed;
    for(int i=0;i<N;i++)
        seed.setbit(i);

    vector<u128> L(1,seed);

    while(!L.empty())
        L = onestep(L);

    cout << "Yay!" << endl;
    cout << ans << " total convex geometries and " << ans2 << " non-isomorphic geometries found!" << endl;
}
