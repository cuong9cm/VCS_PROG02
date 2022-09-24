#include<bits/stdc++.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
using namespace std;

int main() {
    string user;
    cout << "Nhap ten user can tim: ";
    cin >> user;
    struct passwd *usr;
    struct group *gr;
    usr = getpwnam(user.c_str());
    gr = getgrnam(user.c_str());
    if (!usr) {
        cout << "Khong tim thay user" << endl;
        return 0;    
    }
    cout << "uid: " << usr->pw_uid;
    cout << "\ngid: " << usr->pw_gid;
    cout << "\ndir home: " << usr->pw_dir;
    cout << "\ngroup name: " << gr->gr_name;
    return 0;
}
