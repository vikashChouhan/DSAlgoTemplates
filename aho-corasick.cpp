
int ids = 0;
struct trie {
    char ch;
    int id;
    bool is_end;
    unordered_map<char, trie*> next;
    
    trie* link;
    trie* par;
    unordered_map<char, trie*> lps;
    
    trie(char ch, trie *par, int id) {
        this->ch = ch;
        this->par = par;
        this->id = id;
        // lps = next = vector<trie*>();
        link = NULL;
        is_end = false;
    }
    
} *root = NULL;

void add(string s) {
    trie *p = root;
    for(char ch: s) {
        if(p->next.find(ch)==p->next.end()) {
            p->next[ch] = new trie(ch, p, ids++);
        }
        p = p->next[ch];
    }
    p->is_end = true;
}

trie* get_link(trie *p, char ch) {
    if(p==NULL) return root;
    if(p==root || p->par == root) {
        if(p!=root && root->next[ch]!=NULL)
            return root->next[ch];
        return root;
    }
    if(p->link == NULL || p->link->next[ch]==NULL)
        p->link = get_link(p->par, ch);
    
    return p->link;
}

void cal_lps() {
    queue<trie*> q;
    q.push(root);
    while(!q.empty()) {
        trie *f = q.front();
        q.pop();
        f->link = get_link(f->par, f->ch);
        for(auto &x: f->next)
            q.push(x.second);
    }
}

void find(string s) {
    trie *p = root;
    int i = 0;
    while(i<s.size()) {
        if(p->is_end)
            cout<<i-1<<" ";
            
        if(p->next[s[i]]!=NULL) {
            p = p->next[s[i]];
            i++;
        } else {
            p = p->link;
        }
    }
    if(p->is_end)
        cout<<s.size()-1<<" ";
}

void print(trie *p, int tab) {
    
    cout<<string(tab, '-');
    cout<<p->ch<<" "<<p->id<<" "<<p->link->id<<"\n";
    
    for(auto &x: p->next) {
        if(x.second!=NULL)
            print(x.second, tab+5);
    }
}

int main()
{
    root = new trie('.', NULL, 0);
    
    add("vikash");
    add("chouhan");
    add("is");
    add("here");
    add("the");
    
    cal_lps();
    print(root, 0);
    find("thevikashchouhanishere");
    return 0;
}
