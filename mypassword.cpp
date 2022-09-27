#include <bits/stdc++.h>
#include <shadow.h>
#include <pwd.h>
#include <crypt.h>
#include <stdio.h>

using namespace std;

int main() {
	cout << "Enter username: ";
	string username;
	cin >> username;
	struct spwd *userInfo = getspnam(username.c_str());
	cout << "Changing password for " << username << endl;

	string currentPassword;
	cout << "Enter current password: ";
	cin >> currentPassword;

	string encrypt_password = crypt(currentPassword.c_str(), userInfo->sp_pwdp);
	if (strcmp(encrypt_password.c_str(), userInfo->sp_pwdp) != 0) {
		cout << "Wrong passworld!" << endl;
		return 0;
	}
	string newPassword;
	cout << "Enter new password: ";
	cin >> newPassword;

// 	encrypt_password = crypt(newPassword.c_str(), userInfo->sp_pwdp);
// 	userInfo->sp_pwdp = encrypt_password.c_str();

	char* newEncryptPassword = crypt(newPassword.c_str(), userInfo->sp_pwdp);
	userInfo->sp_pwdp = newEncryptPassword;
	
	FILE *fileDest = fopen("/etc/shadow", "r");
	FILE *fileTemp = fopen("/tmp/shadow.tmp", "w");

	char* line;
	size_t len = 0;
	while (getline(&line, &len, fileDest) != -1) {
		if (strstr(line, username.c_str()) != NULL) {
			putspent(userInfo, fileTemp);
		}
		else {
			fputs(line, fileTemp);
		}
	}

	cout << "\nSuccessfully";
	remove("/etc/shadow");
	rename("/tmp/shadow.tmp", "/etc/shadow");

	fclose(fileDest);
	fclose(fileTemp);
	return 0;
}
