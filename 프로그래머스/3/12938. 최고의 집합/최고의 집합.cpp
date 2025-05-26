#include <string>
#include <vector>

using namespace std;

vector<int> solution(int n, int s)
{
	// 원소의 합 s가 원소의 개수 n보다 작으면 자연수 조건을 만족할 수 없음
	if (s < n)
	{
		return vector<int>(1, -1);
	}

	int divided = s / n;
	int remainder = s % n;

	// s를 최대한 균등하게 나누기 위해서 divided로 나눠준 후, 나머지를 뒤에서부터 1씩 더함
	vector<int> answer(n, divided);
	for (int i = 0; i < remainder; ++i)
	{
		answer[n - 1 - i] += 1;
	}

    return answer;
}