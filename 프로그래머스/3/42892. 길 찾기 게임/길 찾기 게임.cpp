#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Node
{
    int x;
    int y;
    int id;
};

void Search(vector<Node>* sortedNodeInfo, vector<Node>::iterator node, int rangeMin, int rangeMax, vector<int>* preorder, vector<int>* postorder);

vector<vector<int>> solution(vector<vector<int>> nodeinfo)
{
    vector<vector<int>> answer = vector<vector<int>>(2, vector<int>());

    // 순회 결과의 길이는 노드의 개수와 같을 것이므로 예약
    answer[0].reserve(nodeinfo.size());
    answer[1].reserve(nodeinfo.size());

    // 노드의 번호, 좌표 정보를 묶어서 관리
    vector<Node> indexedNodeinfo = vector<Node>(nodeinfo.size());

    for (int i = 0; i < nodeinfo.size(); i++)
    {
        Node& curNode = indexedNodeinfo[i];
        curNode.id = i + 1; // 노드 번호는 1부터 시작
        curNode.x = nodeinfo[i][0];
        curNode.y = nodeinfo[i][1];
    }

    sort(indexedNodeinfo.begin(), indexedNodeinfo.end(), [](Node lVal, Node rVal) // comp
    {
        // y좌표가 같을 경우 x좌표로 정렬
        if (lVal.y == rVal.y)
            return lVal.x < rVal.x;
        // 1번 원소(y좌표)가 큰 순서로 정렬
        else
            return lVal.y > rVal.y;
    });

    Search(&indexedNodeinfo, indexedNodeinfo.begin(), 0, 100'000, &(answer[0]), &(answer[1]));

    return answer;

}

void Search(vector<Node>* sortedNodeInfo, vector<Node>::iterator node, int rangeMin, int rangeMax, vector<int>* preorder, vector<int>* postorder)
{
    const Node& curNode = *node;

    int nextLevelY = -1;

    // 트리 순회 과정에서 해당 노드에 진입한 시점
    // 전위 탐색 목록에 등록
    preorder->emplace_back(curNode.id);

    // 다음 수준의 노드 탐색
    auto iterNextLevelNode = node;
    for (; iterNextLevelNode != sortedNodeInfo->end(); iterNextLevelNode++)
    {
        if ((*iterNextLevelNode).y != curNode.y)
        {
            nextLevelY = (*iterNextLevelNode).y;
            break;
        }
    }

    // subtree 탐색 및 순회, 잘못된 노드 위치가 주어지는 경우는 없다는 제한사항에 의거해 한쪽의 subtree가 여럿 생기는 경우는 고려하지 않음
    // 현재 노드가 마지막 수준이었다면 루프 0회로 탈출
    for (; iterNextLevelNode != sortedNodeInfo->end(); iterNextLevelNode++)
    {
        int nextNodeX = (*iterNextLevelNode).x;

        // 다다음 수준에 진입했다면 루프 종료
        if ((*iterNextLevelNode).y != nextLevelY)
            break;

        // left subtree 순회
        if (rangeMin <= nextNodeX && nextNodeX < curNode.x)
        {
            Search(sortedNodeInfo, iterNextLevelNode, rangeMin, curNode.x - 1, preorder, postorder);
            continue;
        }

        // right subtree 순회
        if (curNode.x < nextNodeX && nextNodeX <= rangeMax)
        {
            Search(sortedNodeInfo, iterNextLevelNode, curNode.x + 1, rangeMax, preorder, postorder);
            break;
        }
    }

    // 트리 순회 과정에서 해당 노드를 벗어나는 시점
    // 후위 탐색 목록에 등록
    postorder->emplace_back(curNode.id);
    return;
}
