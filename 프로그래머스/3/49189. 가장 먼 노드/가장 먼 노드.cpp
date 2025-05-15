#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

int solution(int n, vector<vector<int>> edges)
{
    // 노드간 연결 상태를 나타내는 그래프
    // graph[n]의 요소는 n번 노드와 연결된 노드들의 목록
    vector<vector<int>> graph = vector<vector<int>>(n, vector<int>());
    for_each(edges.begin(), edges.end(), [&graph](vector<int> edge) 
    {
        // edges는 1부터 시잭되는 값으로 표현되기 때문에 0부터 시작하는 값으로 조정
        graph[edge[0] - 1].emplace_back(edge[1] - 1);
        graph[edge[1] - 1].emplace_back(edge[0] - 1);
    });

    // 큐에 넣은적 있는 노드를 true로 기록하는 배열
    vector<bool> enqued = vector<bool>(n, false);

    // 큐에 넣으면서 거리를 기록
    vector<int> distance = vector<int>(n, INT_MAX);

    // 방문 예정인 노드 목록
    // 거리에 가중치가 없는 문제이므로 새로 큐에 넣는 데이터가 기존의 큐에 들어있는 데이터보다 가까운 경우는 발생하지 않는다
    queue<int> toVisit = queue<int>();

    // 0번 노드 등록
    toVisit.push(0);
    distance[0] = 0;
    enqued[0] = true;

    // 마지막으로 방문한 노드를 확인하기 위해 '현재 노드' 변수를 while문 바깥으로 꺼냄
    int current = 0;

    // 다익스트라 알고리즘을 사용해 최단거리 탐색
    while (toVisit.empty() == false)
    {
        current = toVisit.front();
        toVisit.pop();

        for (int neighbor : graph[current])
        {
            // 이미 큐에 등록되었으면 건너뜀
            if (enqued[neighbor])
                continue;

            enqued[neighbor] = true;
            distance[neighbor] = distance[current] + 1;
            toVisit.push(neighbor);
        }
    }

    // 최대 거리와 동일한 거리의 노드 개수 확인
    int maxDistance = distance[current];

    int count = count_if(distance.begin(), distance.end(), [maxDistance](int d)
    {
        return d == maxDistance;
    });

    return count;
}