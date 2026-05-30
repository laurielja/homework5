#include<bits/extc++.h>
#include<windows.h>
using namespace std;
using namespace chrono;
bool sameFile(const string& A, const string& B) {
    ifstream f1(A), f2(B);

    char c1, c2;

    while (true) {
        bool ok1 = bool(f1 >> c1);
        bool ok2 = bool(f2 >> c2);

        if (ok1 != ok2) return false;
        if (!ok1) return true;

        if (c1 != c2) return false;
    }
}
int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    string s;
    cin>>s;
    cout<<"执行文件"<<s<<".exe:"<<endl<<endl;
    for (int i = 1; i <= 6; i++) {
        auto strin = "samples/sample" + to_string(i) + ".in";
        auto strout = "samples/" + s + "/sample" + to_string(i) + ".out";
        auto strans = "samples/sample" + to_string(i) + ".ans";
        //cout<<strin<<" "<<strout<<" "<<strans<<endl;
        auto cmd = s + ".exe < " + strin + " > " + strout;
        cout<<"执行"<<i<<":"<<endl;
        cout<<"输入文件:"<<strin<<endl;
        cout<<"输出文件:"<<strout<<endl;
        auto start = high_resolution_clock::now();
        system(cmd.c_str());
        auto end = high_resolution_clock::now();
        cout<<"执行结果:";
        if (sameFile(strans, strout))
            cout<<"Accepted"<<endl;
        else
            cout<<"Wrong Answer"<<endl;
        cout<<"执行时间:";
        cout<<duration_cast<milliseconds>(end - start).count()<<"ms"<<endl<<endl;
    }

    return 0;

}