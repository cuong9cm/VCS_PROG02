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

	char* encrypt_password = crypt(currentPassword.c_str(), userInfo->sp_pwdp);
	if (strcmp(encrypt_password, userInfo->sp_pwdp) != 0) {
		cout << "Wrong passworld!" << endl;
		return 0;
	}
	string newPassword;
	cout << "Enter new password: ";
	cin >> newPassword;

 	encrypt_password = crypt(newPassword.c_str(), userInfo->sp_pwdp);
 	userInfo->sp_pwdp = encrypt_password;

	FILE *fileDest = fopen("/etc/shadow", "a");
	FILE *fileTemp = fopen("/tmp/shadow.tmp", "a");

	char* line;
	unsigned int len = 0;
	while (getline(&line, &len, fileDest) != -1) {
		if (strcmp(line, username.c_str()) != 0)
			putspent(userInfo, fileTemp);
			fputs(line, fileTemp);
	}

	cout << "\nSuccessfully";
	remove("/etc/shadow");
	rename("/tmp/shadow.tmp", "/etc/shadow");

	fclose(fileDest);
	fclose(fileTemp);
	return 0;
}
