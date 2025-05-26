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

	// s를 최대한 균등하게 나누기 위해서 divided로 나눠준 후, 나머지를 뒤에서부터 1씩 더하는 방법을 사용
	int divided = s / n;
	int remainder = s % n;

	vector<int> answer;
	answer.reserve(n); // 미리 공간 확보

	// divided 값을 갖는 n - remainder 개의 원소
	vector<int> first(n - remainder, divided);
	// divided + 1 값을 갖는 remainder 개의 원소
	vector<int> second(remainder, divided + 1);

	// 두 배열을 합침
	answer.insert(answer.end(), first.begin(), first.end());
	answer.insert(answer.end(), second.begin(), second.end());

    return answer;
}