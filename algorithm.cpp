#pragma GCC optimize(3)
#include <bits/stdc++.h>

// data 1
#define File_IO1

// data 2
// #define File_IO2

// data 3
// #define File_IO3

using namespace std;

int n, high, low;
vector<unsigned int> s, d;
vector<int> deg;
vector<vector<int> > mask_val;

void get_col_matrix(vector<vector<int> > &A, int arg) {
    int id = -1;
    for (int i = 0; i < n; ++i) {
        if (arg>>i&1) {
            id = i;
            break;
        }
    }
    for (int i = id + 1; i < n; ++i) {
        if (arg>>i&1) {
            for (int j = 0; j < n; ++j) {
                A[j][i] ^= A[j][id];
            }
        }
    }
}

void get_row_matrix(vector<vector<int> > &A, int arg, int swp_id) {
    int id = -1;
    for (int i = 0; i < n; ++i) {
        if (arg>>i&1) {
            id = i;
            break;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (i == id) {
            continue;
        }
        if (arg>>i&1) {
            for (int j = 0; j < n; ++j) {
                A[i][j] ^= A[id][j];
            }
        }
    }
    if (swp_id != id) {
        for (int i = 0; i < n; ++i) {
            swap(A[id][i], A[swp_id][i]);
        }
    }
}

vector<unsigned int> get_col(vector<unsigned int> x, int arg) {
    int id = -1;
    for (int i = 0; i < n; ++i) {
        if (arg>>i&1) {
            id = i;
            break;
        }
    }
    vector<unsigned int> ans = x;
    vector<unsigned int> tmp_ans;
    int len = ans.size();
    tmp_ans.resize(len);
    for (int i = id + 1; i < n; ++i) {
        if (arg>>i&1) {
            for (int j = 0; j < len; ++j) {
                tmp_ans[j] = ans[j];
                ans[j] &= mask_val[id][j];
            }
            for (int j = 0; j < len; ++j) {
                if ((j<<5) + (1<<id) >= (1<<n)) {
                    ans[j] = 0;
                    continue;
                }
                int pg = ((j<<5) + (1<<id))>>5;
                int tmp = ((pg + 1)<<5) - (j<<5) - (1<<id);
                ans[j] = ans[pg]>>(32 - tmp);
                if (tmp < 32 && pg + 1 < len) {
                    ans[j] |= (ans[pg + 1]&((1<<32 - tmp) - 1))<<tmp;
                }
            }
            for (int j = 0; j < len; ++j) {
                tmp_ans[j] ^= mask_val[i][j]&ans[j];
                ans[j] &= ~mask_val[i][j];
            }
            for (int j = len - 1; j >= 0; --j) {
                if ((j<<5) - (1<<i) + 31 < 0) {
                    ans[j] = 0;
                    continue;
                }
                int pg = ((j<<5) - (1<<i) + 31)>>5;
                int tmp = (j<<5) - (1<<i) + 32 - (pg<<5);
                ans[j] = (ans[pg]&(unsigned int)((1ll<<tmp) - 1))<<(32 - tmp);
                if (tmp < 32 && pg >= 1) {
                    ans[j] |= ans[pg - 1]>>tmp;
                }
            }

            for (int j = 0; j < len; ++j) {
                ans[j] ^= tmp_ans[j];
            }
        }
    }
    return ans;
}

vector<unsigned int> get_row(vector<unsigned int> ans, int arg, int swp_id) {
    int id = -1;
    for (int i = 0; i < n; ++i) {
        if (arg>>i&1) {
            id = i;
            break;
        }
    }
    vector<unsigned int> tmp_ans;
    int len = ans.size();
    tmp_ans.resize(len);
    for (int i = id + 1; i < n; ++i) {
        if (arg>>i&1) {
            for (int j = 0; j < len; ++j) {
                tmp_ans[j] = ans[j];
                ans[j] &= mask_val[i][j];
            }

            for (int j = 0; j < len; ++j) {
                if ((j<<5) + (1<<i) >= (1<<n)) {
                    ans[j] = 0;
                    continue;
                }
                int pg = ((j<<5) + (1<<i))>>5;
                int tmp = ((pg + 1)<<5) - (j<<5) - (1<<i);
                ans[j] = ans[pg]>>(32 - tmp);
                if (tmp < 32 && pg + 1 < len) {
                    ans[j] |= (ans[pg + 1]&((1<<32 - tmp) - 1))<<tmp;
                }
            }

            for (int j = 0; j < len; ++j) {
                tmp_ans[j] ^= mask_val[id][j]&ans[j];
                ans[j] &= ~mask_val[id][j];
            }

            for (int j = len - 1; j >= 0; --j) {
                if ((j<<5) - (1<<id) + 31 < 0) {
                    ans[j] = 0;
                    continue;
                }
                int pg = ((j<<5) - (1<<id) + 31)>>5;
                int tmp = (j<<5) - (1<<id) + 32 - (pg<<5);
                ans[j] = (ans[pg]&(unsigned int)((1ll<<tmp) - 1))<<(32 - tmp);
                if (tmp < 32 && pg >= 1) {
                    ans[j] |= ans[pg - 1]>>tmp;
                }
            }

            for (int j = 0; j < len; ++j) {
                ans[j] ^= tmp_ans[j];
            }
        }
    }
    if (swp_id != id) {
        vector<int> tmp_ans1(len), tmp_ans2(len);
        for (int i = 0; i < len; ++i) {
            tmp_ans1[i] = (~mask_val[id][i])&mask_val[swp_id][i]&ans[i];
            tmp_ans2[i] = mask_val[id][i]&(~mask_val[swp_id][i])&ans[i];
        }

        if (swp_id > id) {
            int cha = (1<<swp_id) - (1<<id);
            for (int j = 0; j < len; ++j) {
                if ((j<<5) + cha >= (1<<n)) {
                    tmp_ans1[j] = 0;
                    continue;
                }
                int pg = ((j<<5) + cha)>>5;
                int tmp = ((pg + 1)<<5) - (j<<5) - cha;
                tmp_ans1[j] = tmp_ans1[pg]>>(32 - tmp);
                if (tmp < 32 && pg + 1 < len) {
                    tmp_ans1[j] |= (tmp_ans1[pg + 1]&((1<<32 - tmp) - 1))<<tmp;
                }
            }
            for (int j = len - 1; j >= 0; --j) {
                if ((j<<5) - cha + 31 < 0) {
                    tmp_ans2[j] = 0;
                    continue;
                }
                int pg = ((j<<5) - cha + 31)>>5;
                int tmp = (j<<5) - cha + 32 - (pg<<5);
                tmp_ans2[j] = (tmp_ans2[pg]&(unsigned int)((1ll<<tmp) - 1))<<(32 - tmp);
                if (tmp < 32 && pg >= 1) {
                    tmp_ans2[j] |= tmp_ans2[pg - 1]>>tmp;
                }
            }
        }
        else {
            int cha = (1<<id) - (1<<swp_id);
            for (int j = 0; j < len; ++j) {
                if ((j<<5) + cha >= (1<<n)) {
                    tmp_ans2[j] = 0;
                    continue;
                }
                int pg = ((j<<5) + cha)>>5;
                int tmp = ((pg + 1)<<5) - (j<<5) - cha;
                tmp_ans2[j] = tmp_ans2[pg]>>(32 - tmp);
                if (tmp < 32 && pg + 1 < len) {
                    tmp_ans2[j] |= (tmp_ans2[pg + 1]&((1<<32 - tmp) - 1))<<tmp;
                }
            }
            for (int j = len - 1; j >= 0; --j) {
                if ((j<<5) - cha + 31 < 0) {
                    tmp_ans1[j] = 0;
                    continue;
                }
                int pg = ((j<<5) - cha + 31)>>5;
                int tmp = (j<<5) - cha + 32 - (pg<<5);
                tmp_ans1[j] = (tmp_ans1[pg]&(unsigned int)((1ll<<tmp) - 1))<<(32 - tmp);
                if (tmp < 32 && pg >= 1) {
                    tmp_ans1[j] |= tmp_ans1[pg - 1]>>tmp;
                }
            }
        }
        for (int i = 0; i < len; ++i) {
            int tmp = (mask_val[id][i]&mask_val[swp_id][i]|(~mask_val[id][i])&(~mask_val[swp_id][i]))&ans[i];
            ans[i] = tmp|tmp_ans1[i]|tmp_ans2[i];
        }
    }
    return ans;
}

vector<set<vector<unsigned int> > > mp;
map<vector<unsigned int>, vector<int> > mp_que_operate_col;
vector<int> que_operate_row, que_operate_col;
vector<vector<int> > mask_id;

void insert_map(vector<unsigned int> x, int high, int low, int id) {
    for (int i = 0; i < mask_id[id].size(); ++i) {
        x[i] &= mask_id[id][i];
    }
    mp[id].insert(x);
    if (id == n - 1) {
        mp_que_operate_col[x] = que_operate_col;
    }
}

int check_map(vector<unsigned int> x, int high, int low, int id) {
    for (int i = 0; i < mask_id[id].size(); ++i) {
        x[i] &= mask_id[id][i];
    }
    int res = mp[id].count(x);
    if (res && id == n - 1) {
        que_operate_col = mp_que_operate_col[x];
    }
    return res;
}

void open_in_file(int id) {
    freopen("CON", "r", stdin);
    cin.clear();
    char file_name[25];
    int cnt = 0;
    file_name[cnt++] = '.';
    file_name[cnt++] = '/';
    if (!id) {
        file_name[cnt++] = '0';
    }
    while (id) {
        file_name[cnt++] = '0' + (id % 10);
        id /= 10;
    }
    file_name[cnt++] = '.';
    file_name[cnt++] = 't';
    file_name[cnt++] = 'x';
    file_name[cnt++] = 't';
    file_name[cnt] = 0;
    freopen(file_name, "r", stdin);
}

void open_out_file(int id) {
    freopen("CON", "w", stdout);
    cout.clear();
    char file_name[25];
    int cnt = 0;
    file_name[cnt++] = '.';
    file_name[cnt++] = '/';
    if (!id) {
        file_name[cnt++] = '0';
    }
    while (id) {
        file_name[cnt++] = '0' + (id % 10);
        id /= 10;
    }
    file_name[cnt++] = '.';
    file_name[cnt++] = 't';
    file_name[cnt++] = 'x';
    file_name[cnt++] = 't';
    file_name[cnt] = 0;
    freopen(file_name, "w", stdout);
}

int find_solution = 0;

void dfs_get_map(vector<unsigned int> x, int id) {
    if (id == n) {
        return ;
    }
    for (int i = 0; i < (1<<n - id - 1); ++i) {
        int mask = (i<<id + 1)|(1<<id);
        vector<unsigned int> y = get_col(x, mask);
        que_operate_col.push_back(mask);
        insert_map(y, high, low, id);
        dfs_get_map(y, id + 1);
        que_operate_col.pop_back();
    }
}

void dfs_check(vector<unsigned int> x, int id) {
    if (id == n) {
        cout << "Find solution!" << endl;
        find_solution = 1;
        return ;
    }
    for (int mask = (1<<id); mask < (1<<n); mask += (1<<id)) {
        vector<unsigned int> y = get_row(x, mask, id);
        if (check_map(y, high, low, id)) {
            que_operate_row.push_back(mask);
            dfs_check(y, id + 1);
            if (find_solution) {
                return ;
            }
            que_operate_row.pop_back();
        }
    }
}

vector<unsigned int> get_matrix(vector<vector<int> > A, vector<unsigned int> x) {
    vector<unsigned int> tmp_ans;
    tmp_ans.resize(((1<<n)+31)>>5);
    for (int i = 0; i < tmp_ans.size(); ++i) {
        tmp_ans[i] = 0;
    }

    for (int i = 0; i < (1<<n); ++i) {
        if (x[i>>5]>>(i&31)&1) {
            vector<unsigned int> ans;
            ans.resize(((1<<n)+31)>>5);
            for (int j = 0; j < ans.size(); ++j) {
                ans[j] = 0;
            }
            ans[0] = 1;
            for (int j = 0; j < n; ++j) {
                if (i>>j&1) {
                    vector<unsigned int> tmp1;
                    tmp1.resize(((1<<n)+31)>>5);
                    for (int k = 0; k < tmp1.size(); ++k) {
                        tmp1[k] = 0;
                    }
                    for (int k = 0; k < n; ++k) {
                        if (A[j][k]) {
                            for (int l = 0; l < (1<<n); ++l) {
                                if (ans[l>>5]>>(l&31)&1) {
                                    tmp1[(l|(1<<k))>>5] ^= ((unsigned int)1<<((l|(1<<k))&31));
                                }
                            }
                        }
                    }
                    ans = tmp1;
                }
            }
            for (int j = 0; j < (1<<n); ++j) {
                if (ans[j>>5]>>(j&31)&1) {
                    tmp_ans[j>>5] ^= ((unsigned int)1<<(j&31));
                }
            }
        }
    }
    return tmp_ans;
}

vector<vector<int> > get_inv(vector<vector<int> > A) {
    vector<vector<int> > ans(n, vector<int> (n, 0));
    for (int i = 0; i < n; ++i) {
        ans[i][i] = 1;
    }
    for (int i = 0; i < n; ++i) {
        int swp_id = i;
        for (int j = i; j < n; ++j) {
            if (A[j][i]) {
                swp_id = j;
                break;
            }
        }
        if (swp_id != i) {
            for (int j = 0; j < n; ++j) {
                swap(A[i][j], A[swp_id][j]);
                swap(ans[i][j], ans[swp_id][j]);
            }
        }
        for (int j = 0; j < n; ++j) {
            if (j != i && A[j][i]) {
                for (int k = i; k < n; ++k) {
                    A[j][k] ^= A[i][k];
                }
                for (int k = 0; k < n; ++k) {
                    ans[j][k] ^= ans[i][k];
                }
            }
        }
    }
    return ans;
}

vector<vector<int> > mul(vector<vector<int> > A, vector<vector<int> > B) {
    vector<vector<int> > ans(n, vector<int> (n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int tmp = 0;
            for (int k = 0; k < n; ++k) {
                tmp ^= (A[i][k]&B[k][j]);
            }
            ans[i][j] = tmp;
        }
    }
    return ans;
}

vector<unsigned int> get_constant(vector<unsigned int> x, int b) {
    for (int i = 0; i < n; ++i) {
        if (b>>i&1) {
            for (int j = 0; j < (1<<n); ++j) {
                if ((j>>i&1) && (x[j>>5]>>(j&31)&1)) {
                    int chg_id = (j^(1<<i));
                    x[chg_id>>5] ^= ((unsigned int)1<<(chg_id&31));
                }
            }
        }
    }
    return x;
}

int main() {
    #ifdef File_IO1
        freopen("./input1.txt", "r", stdin);
        freopen("./output1.txt", "w", stdout);
    #endif // File_IO
    #ifdef File_IO2
        freopen("./input2.txt", "r", stdin);
        freopen("./output2.txt", "w", stdout);
    #endif // File_IO
    #ifdef File_IO3
        freopen("./input3.txt", "r", stdin);
        freopen("./output3.txt", "w", stdout);
    #endif // File_IO
    clock_t start,end;
    start = clock();
    cin >> n >> high >> low;
    string sss, ddd;
    cin >> sss >> ddd;
    s.resize(((1<<n)+31)>>5);
    d.resize(((1<<n)+31)>>5);
    for (int i = 0; i < s.size(); ++i) {
        s[i] = d[i] = 0;
    }

    for (int i = 0; i < (1<<n); ++i) {
        s[i>>5] ^= ((unsigned int)(sss[i] - '0') << (i&31));
        d[i>>5] ^= ((unsigned int)(ddd[i] - '0') << (i&31));
    }

    deg.resize(1<<n);
    for (int i = 0; i < (1<<n); ++i) {
        deg[i] = __builtin_popcount(i);
    }

    mask_id.resize(n);
    for (int i = 0; i < n; ++i) {
        mask_id[i].clear();
        int t = 0;
        int tmp = 0;
        for (int j = 0; j < (1<<n); ++j) {
            if (j >= (1<<i + 1)) {
                ++t;
                if (t == 32) {
                    mask_id[i].push_back(tmp);
                    t = 0;
                    tmp = 0;
                }
                continue;
            }
            if (deg[j] >= low && deg[j] <= high) {
                tmp |= (1<<t);
            }
            ++t;
            if (t == 32) {
                mask_id[i].push_back(tmp);
                t = 0;
                tmp = 0;
            }
        }
        if (t) {
            mask_id[i].push_back(tmp);
        }
    }

    mask_val.resize(n);
    for (int i = 0; i < n; ++i) {
        mask_val[i].clear();
        int t = 0;
        int tmp = 0;
        for (int j = 0; j < (1<<n); ++j) {
            if (j>>i&1) {
                tmp |= (1<<t);
            }
            ++t;
            if (t == 32) {
                mask_val[i].push_back(tmp);
                t = 0;
                tmp = 0;
            }
        }
        if (t) {
            mask_val[i].push_back(tmp);
        }
    }
    mp.resize(n);
    for (int i = 0; i < n; ++i) {
        mp[i].clear();
    }
    find_solution = 0;
    que_operate_col.clear();
    dfs_get_map(s, 0);
    cout << "Get map done!" << endl;
    vector<unsigned int> ans_d;
    int b = -1;
    for (int i = 0; i < (1<<n); ++i) {
        if (__builtin_popcount(i) > 1) {
            continue;
        }
        vector<unsigned int> tmp_d = d;
        for (int j = 0; j < n; ++j) {
            if (i>>j&1) {
                for (int k = 0; k < (1<<n); ++k) {
                    if ((k>>j&1) && (tmp_d[k>>5]>>(k&31)&1)) {
                        int chg_id = k^(1<<j);
                        tmp_d[chg_id>>5] ^= ((unsigned int)1<<(chg_id&31));
                    }
                }
            }
        }
        que_operate_row.clear();
        find_solution = 0;
        dfs_check(tmp_d, 0);
        if (find_solution) {
            ans_d = tmp_d;
            b = i;
            break;
        }
    }
    end = clock();
    cout << "use time: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;
    vector<vector<int> > A(n, vector<int> (n, 0));
    for (int i = 0; i < n; ++i) {
        A[i][i] = 1;
    }

    vector<unsigned int> tmp1 = s;
    for (int i = 0; i < (int)que_operate_col.size(); ++i) {
        get_col_matrix(A, que_operate_col[i]);
        tmp1 = get_col(tmp1, que_operate_col[i]);
    }

    tmp1 = get_matrix(A, s);

    vector<vector<int> > AA(n, vector<int> (n));
    for (int i = 0; i < n; ++i) {
        AA[i][i] = 1;
    }
    vector<unsigned int> tmp2 = ans_d;
    for (int i = 0; i < (int)que_operate_row.size(); ++i) {
        get_row_matrix(AA, que_operate_row[i], i);
        tmp2 = get_row(tmp2, que_operate_row[i], i);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << AA[i][j] << " ";
        }
        cout << endl;
    }
    A = mul(A, AA);
    vector<unsigned int> tmp_ans = get_matrix(A, s);
    cout << ddd << endl;
    for (int i = 0; i < (1<<n); ++i) {
        cout << (tmp_ans[i>>5]>>(i&31)&1);
    }
    tmp_ans = get_constant(tmp_ans, b);
    cout << endl;
}
