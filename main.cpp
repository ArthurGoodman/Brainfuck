#include <iostream>
#include <string>
#include <stack>
#include <sstream>
using namespace std;

class Brainfuck
{
    static const int ms = 1024;

    unsigned char m[ms];
    unsigned char *a;
    unsigned i, b;
    stack<unsigned> t;

public:
    void error(string m) { cout << "error: " << m; throw 0; }

    void run(string p)
    {
        for(i = 0; i < ms; ++i) m[i] = 0;
        i = 0; a = m; t = stack<unsigned>();

        try
        {
            while(p[i]) switch(p[i++])
            {
            case '>': ++a; break;
            case '<': --a; break;
            case '+': ++*a; break;
            case '-': --*a; break;
            case '.': cout << (unsigned)(*a); break;
            case ',': { string l; unsigned i; getline(cin, l); istringstream s(l); s >> i; *a = i; break; }
            case '[':
            {
                t.push(i-1); if(*a) break;
                b = 0; while((p[i] && p[i] != ']') || b) { if(p[i] == '[') ++b; else if(p[i] == ']') --b; ++i; }
                if(p[i++] != ']') error("unmatched brackets");
                t.pop(); break;
            }
            case ']': if(!t.size()) error("unmatched brackets"); i = t.top(); t.pop(); break;
            case ' ': break;
            default: error(string("unknown character '") + p[i-1] + "'");
            }
        }
        catch(...) {}
    }
};

int main()
{
    string s;
    Brainfuck *b = new Brainfuck;

    while(1)
    {
        cout << "$ ";
        getline(cin, s); if(!cin) return 0;

        if(s.empty()) continue;
        else if(s == "exit") return 0;
        else if(s == "cls") { system("cls"); continue; }
        else { b->run(s); cout << endl; }

        cout << endl;
    }

    delete b; return 0;
}
