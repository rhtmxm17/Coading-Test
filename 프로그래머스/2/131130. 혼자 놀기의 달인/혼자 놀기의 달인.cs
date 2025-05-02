public class Solution
{
    public int solution(int[] cards)
    {
        bool[] used = new bool[cards.Length]; // 특정 그룹에 사용된 카드인지 기록
        int biggestGroup = 0;
        int secondGroup = 0;

        for (int i = 0; i < cards.Length; i++) // i: 그룹 순회를 시작할 카드의 인덱스
        {
            if (used[i])
                continue;

            used[i] = true;
            int groupSize = 1;

            for (int j = cards[i] - 1; j != i; j = cards[j] - 1) // j: 현재 순회중인 인덱스
            {
                used[j] = true;
                groupSize++;
            }

            if (biggestGroup < groupSize)
            {
                secondGroup = biggestGroup;
                biggestGroup = groupSize;
            }
            else if (secondGroup < groupSize)
            {
                secondGroup = groupSize;
            }
        }

        return biggestGroup * secondGroup;
    }
}