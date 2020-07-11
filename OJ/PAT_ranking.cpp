/*
题目描述 PAT(1025 PAT Ranking)
Programming Ability Test (PAT) is organized by the College of Computer Science and Technology of Zhejiang University. Each test is supposed to run simultaneously in several places, and the ranklists will be merged immediately after the test. Now it is your job to write a program to correctly merge all the ranklists and generate the final rank.

Input Specification:
Each input file contains one test case. For each case, the first line contains a positive number N (≤100), the number of test locations. Then N ranklists follow, each starts with a line containing a positive integer K (≤300), the number of testees, and then K lines containing the registration number (a 13-digit number) and the total score of each testee. All the numbers in a line are separated by a space.

Output Specification:
For each test case, first print in one line the total number of testees. Then print the final ranklist in the following format:

registration_number final_rank location_number local_rank
The locations are numbered from 1 to N. The output must be sorted in nondecreasing order of the final ranks. The testees with the same score must have the same rank, and the output must be sorted in nondecreasing order of their registration numbers.

Sample Input:
2
5
1234567890001 95
1234567890005 100
1234567890003 95
1234567890002 77
1234567890004 85
4
1234567890013 65
1234567890011 25
1234567890014 100
1234567890012 85
Sample Output:
9
1234567890005 1 1 1
1234567890014 1 2 1
1234567890001 3 1 2
1234567890003 3 1 2
1234567890004 5 1 4
1234567890012 5 2 2
1234567890002 7 1 5
1234567890013 8 2 3
1234567890011 9 2 4
*/
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
struct Student{
    char registration_number[14];
    int location_number;
    int location_rank;
    int score;
}s[100 * 300];
bool cmp(const Student& x, const Student& y){
    if(x.score == y.score){
        return (strcmp(x.registration_number, y.registration_number) < 0);
    }
    return x.score > y.score;
}
int main(){
    int N;
    while(scanf("%d", &N) != EOF){
        int K;
        int idx = 0;
        for(int i = 1; i <= N; i++){
            scanf("%d", &K);
            for(int j = 1; j <= K; j++){
                scanf("%s%d", &s[idx].registration_number, &s[idx].score);
                s[idx].location_number = i;
                idx++;
            }
            sort(s + idx - K, s + idx, cmp);
            int rank = 1;
            s[idx - K].location_rank = rank;
            for(int k = 1; k < K; k++){
                if(s[idx - K + k].score < s[idx - K + k - 1].score)
                    rank = k + 1;
                s[idx - K + k].location_rank = rank;
            }
        }
        sort(s, s + idx, cmp);
        printf("%d\n", idx);
        int rank = 1;
        printf("%s %d %d %d\n", s[0].registration_number, rank, s[0].location_number, s[0].location_rank);
        for(int i = 1; i < idx; i++){
            if(s[i].score < s[i - 1].score)
                rank = i + 1;
            printf("%s %d %d %d\n", s[i].registration_number, rank, s[i].location_number, s[i].location_rank);
        }
    }
    return 0;
}
