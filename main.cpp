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

    bool format; // char or int

    void error(string m) { cout << "error: " << m; throw 0; }

public:
    Brainfuck() : format(false) {}

    void setFormat(bool f) { format = f; }

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
            case '.': if(format) cout << (unsigned)*a; else cout << *a;  break;
            case ',': { string l; unsigned i; getline(cin, l); istringstream s(l); s >> i; if(format) *a = i; else *a = (unsigned char)i; break; }
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

        if(s.empty());
        else if(s == "exit") return 0;
        else if(s == "cls") system("cls");
        else if(s == "help")
        {
            cout << "Commands:\n"
                 << "  exit \t\t Close the program.\n"
                 << "  cls \t\t Clear the screen.\n"
                 << "  help \t\t Show help information.\n"
                 << "  int \t\t Set IO mode to int.\n"
                 << "  char \t\t Set IO mode to char.\n\n";
        }
        else if(s == "char") b->setFormat(false);
        else if(s == "int") b->setFormat(true);
        else { b->run(s); cout << "\n\n"; }
    }

    delete b; return 0;
}
