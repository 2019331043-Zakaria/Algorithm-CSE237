const int N = 5e5 + 6;


struct Segmentree
{

#define lc (node << 1)
#define rc ((node << 1) | 1)

    vector<ll>tree;
    vector<ll>lazy;

    Segmentree()
    {
        tree.resize(4 * N);
        lazy.resize(4 * N);
        fill(tree.begin(), tree.end(), 0);
        fill(lazy.begin(), lazy.end(), 0);
    }

    void push(ll node, ll b, ll e)
    {
        if (lazy[node] == 0)
            return ;

        tree[node] += lazy[node];

        if (b != e)
        {
            lazy[lc] += lazy[node];
            lazy[rc] += lazy[node];
        }

        lazy[node] = 0;
    }

    void build(ll node, ll b, ll e) {

        if (b == e) {
            tree[node] = 0;
            lazy[node] = 0;
            return;
        }



        ll mid = (b + e) >> 1;
        build(2 * node, b, mid);
        build(2 * node + 1, mid + 1, e);

        tree[node] = tree[lc] + tree[rc];

    }
    void update(ll node, ll b, ll e, ll l, ll r, ll x)
    {

        push(node, b, e);

        if (l > e || r < b)
            return ;

        if (l <= b && r >= e)
        {
            lazy[node] += x;
            push(node, b, e);
            return ;
        }

        ll mid = (b + e) >> 1;
        update(lc, b, mid, l, r, x);
        update(rc, mid + 1, e, l, r, x);

        tree[node] = tree[lc] + tree[rc];
    }

    ll query(ll node, ll b, ll e, ll idx)
    {

        push(node, b, e);

        if (b > idx || e < idx)
            return 0;

        if (b == e && b == idx)
        {
            return tree[node];
        }

        ll mid = (b + e) >> 1;
        return query(lc, b, mid, idx) + query(rc, mid + 1, e, idx);
    }

};