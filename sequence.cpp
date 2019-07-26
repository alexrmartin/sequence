#include <iostream>
#include <fstream>
#include <cstring>
#include "ArgumentManager.h"

using namespace std;

#define MAX_STRINGS 4

int LCS2(string *S, int *len);
int LCS3(string *S, int *len);
int LCS4(string *S, int *len);

int main(int argc, char *argv[]) {
    ArgumentManager am(argc, argv, ';');
    string infile = am.get("input");
    string outfile = am.get("output");

    string string_list[MAX_STRINGS] = {"", "", "", ""};

    int num = 0;
    ifstream in(infile);
    string line;
    while (getline(in, line)) {
        if (num > MAX_STRINGS) {
            break;
        }

        if (line == "") {
            continue;
        }

        string_list[num] = line;
        num++;
    }

    if (num == 0) {
        cout << "No strings found in file." << endl;
        return 1;
    }

    int len[num];
    for (int i = 0; i < num; i++) {
        len[i] = string_list[i].length();
    }

    int longest_sequence_len;
    if (num == 1) {
        longest_sequence_len = len[0];
    }
    else if (num == 2) {
        longest_sequence_len = LCS2(string_list, len);
    }
    else if (num == 3) {
        longest_sequence_len = LCS3(string_list, len);
    }
    else {
        longest_sequence_len = LCS4(string_list, len);
    }
        
    ofstream out;
    out.open(outfile);
    out << "Len: " << longest_sequence_len << endl;
    out.close();

    return 0;
}

int LCS4(string *S, int *len) {
    int ****L = new int***[len[0]+1];
    for (int i = 0; i <= len[0]; i++) {
        L[i] = new int**[len[1]+1];
        for (int j = 0; j <= len[1]; j++) {
            L[i][j] = new int*[len[2]+1];
            for (int k = 0; k <= len[2]; k++) {
                L[i][j][k] = new int[len[3]+1];
            }
        }
    }

    for (int i = 0; i <= len[0]; i++) {
        for (int j = 0; j <= len[1]; j++) {
            for (int k = 0; k <= len[2]; k++) {
                for (int l = 0; l <= len[3]; l++) {
                    if (i == 0 || j == 0 || k == 0 || l == 0) {
                        L[i][j][k][l] = 0;
                    }

                    else if (S[0][i-1] == S[1][j-1] && S[0][i-1] == S[2][k-1] && S[0][i-1] == S[3][l-1]) {
                        L[i][j][k][l] = L[i-1][j-1][k-1][l-1] + 1;
                    }

                    else {
                        L[i][j][k][l] = max(max(max(L[i-1][j][k][l], L[i][j-1][k][l]), L[i][j][k-1][l]), L[i][j][k][l-1]);
                    }
                }
            }
        }
    }

    return L[len[0]][len[1]][len[2]][len[3]];
}

int LCS3(string *S, int *len) {
    int ***L = new int**[len[0]+1];
    for (int i = 0; i <= len[0]; i++) {
        L[i] = new int*[len[1]+1];
        for (int j = 0; j <= len[1]; j++) {
            L[i][j] = new int[len[2]+1];
        }
    }

    for (int i = 0; i <= len[0]; i++) {
        for (int j = 0; j <= len[1]; j++) {
            for (int k = 0; k <= len[2]; k++) {
                    if (i == 0 || j == 0 || k == 0) {
                        L[i][j][k] = 0;
                    }

                    else if (S[0][i-1] == S[1][j-1] && S[0][i-1] == S[2][k-1]) {
                        L[i][j][k] = L[i-1][j-1][k-1] + 1;
                    }

                    else {
                        L[i][j][k] = max(max(L[i-1][j][k], L[i][j-1][k]), L[i][j][k-1]);
                    }
            }
        }
    }

    return L[len[0]][len[1]][len[2]];
}

int LCS2(string *S, int *len) {
    int **L = new int*[len[0]+1];
    for (int i = 0; i <= len[0]; i++) {
        L[i] = new int[len[1]+1];
    }

    for (int i = 0; i <= len[0]; i++) {
        for (int j = 0; j <= len[1]; j++) {
                    if (i == 0 || j == 0) {
                        L[i][j] = 0;
                    }

                    else if (S[0][i-1] == S[1][j-1]) {
                        L[i][j] = L[i-1][j-1] + 1;
                    }

                    else {
                        L[i][j] = max(L[i-1][j], L[i][j-1]);
                    }
        }
    }

    return L[len[0]][len[1]];
}
