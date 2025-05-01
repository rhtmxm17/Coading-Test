#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
1원, 2원, 5원이 있다면 n원(n>5)을 거슬러주는 방법의 수는

(n-1원을 거슬러주는 방법)
+ (2원, 5원만으로 n-2원을 거슬러주는 방법)
+ (5원만으로 n-5원을 거슬러주는 방법)


## 1차시도(재귀 사용)

함수 선언부
int CasesOfChange(int n, vector<int>::const_iterator begin, vector<int>::const_iterator end)

재귀 호출부
for (auto iter = begin; iter != end; iter++)
{
    cases += CasesOfChange(n - *iter, iter, end);
}

=> 반복해서 검증하는 케이스가 대량 발생

## 2차 시도(2차원 배열 채우기)

1행에는 동전 한 가지만을 쓰는 경우의 수
2행에는 1행에 추가로 동전 한 가지를 쓰는 경우의 수
3행에는 2행에 추가로 동전 한 가지를 쓰는 경우의 수
...

배열 선언부
vector<vector<int>> changes(money.size(), vector<int>(n, 0));

*/

int solution(int n, vector<int> money)
{
    //sort(money.begin(), money.end());
    vector<vector<int>> changes(money.size(), vector<int>(n + 1, 0));

    // 동전 한 가지만 쓰는 케이스(이전 행이 존재하지 않는 케이스)
    int first_coin = money.front();
    for (int i = 0; i <= n; i += first_coin)
    {
        changes[0][i] = 1;
    }

    const int money_size = money.size();
    for (int raw = 1; raw < money_size; raw++)
    {
        const int coin = money[raw];
        changes[raw][0] = 1; // 거스름돈 0원을 돌려주는 경우의 수는 항상 1
        for (int col = 1; col <= n; col++)
        {
            int change = changes[raw - 1][col];
            if (col - coin >= 0)
                change += changes[raw][col - coin];
            changes[raw][col] = change;
        }
    }

    return changes.back().back();
}

//int CasesOfChange(int n, vector<int>::const_iterator begin, vector<int>::const_iterator end)
//{
//    // 거스름돈이 음수인 케이스는 없다
//    if (n < 0)
//        return 0;
//
//    // 거스름돈이 0인 케이스는 1가지
//    else if (n == 0)
//        return 1;
//
//    else
//    {
//        int cases = 0;
//
//        for (auto iter = begin; iter != end; iter++)
//        {
//            // 반복문이 진행될수록 사용하는 동전의 범위가 적어짐
//            cases += CasesOfChange(n - *iter, iter, end);
//        }
//        return cases % 1'000'000'007; // 제한사항
//    }
//}