#include<bits/stdc++.h>
#include <pwd.h>
#include <unistd.h>
using namespace std;

int main() {
    string user;
    cout << "Nhap ten user can tim: ";
    cin >> user;
    struct passwd *usr;
    usr = getpwnam(user.c_str());
    if (!usr) {
        cout << "Khong tim thay user" << endl;
        return 0;    
    }
    cout << "uid: " << usr->pw_uid;
    cout << " gid: " << usr->pw_gid;
    return 0;
}
