using System;
using System.Text;

public class Solution
{
    //   u
    // l   r
    //   d

    // dict: d l r u

    // n, x, r : UD
    // m, y, c : LR

    public string solution(int n, int m, int x, int y, int r, int c, int k)
    {
        const int UD = 0;
        const int LR = 1;

        int[] current = new int[2];
        int[] vecOut = new int[2]; // 출구를 향하는 벡터

        // 계산 편의를 위해 좌하단이 0, 0인 좌표 평면으로 변환
        current[UD] = n - x;
        current[LR] = y - 1;
        vecOut[UD] = -(r - x);
        vecOut[LR] = c - y;

        // 달성 불가능한 거리 조건 예외처리
        int distance = Math.Abs(vecOut[UD]) + Math.Abs(vecOut[LR]);
        if (distance > k || (k - distance) % 2 == 1)
            return "impossible";

        StringBuilder sb = new StringBuilder(k);

        // 목적지에 가는데 쓰고도 남을 왕복 행동수
        int surplus = (k - distance) >> 1;

        // 사전순으로 가능한 먼저 삽입한다.

        // 가능한 d 삽입
        if (vecOut[UD] < 0)
        {
            sb.Append('d', -vecOut[UD]);

            current[UD] += vecOut[UD];
            vecOut[UD] = 0;
        }

        // 더 내려갈 수 있는 여분의 공간 또는 행동
        int additionalDown = current[UD] < surplus ? current[UD] : surplus;

        sb.Append('d', additionalDown);
        current[UD] -= additionalDown; // 
        vecOut[UD] += additionalDown;  // 좌표 갱신
        surplus -= additionalDown; // 행동수 차감

        // 가능한 l 삽입
        if (vecOut[LR] < 0)
        {
            sb.Append('l', -vecOut[LR]);

            current[LR] += vecOut[LR];
            vecOut[LR] = 0;
        }

        int additionalLeft = current[LR] < surplus ? current[LR] : surplus;

        sb.Append('l', additionalLeft);
        current[LR] -= additionalLeft;
        vecOut[LR] += additionalLeft;
        surplus -= additionalLeft;

        // 0, 0까지 갔는데도 행동 여분이 있다면
        // 그 횟수만큼 ud보다 사전순으로 앞서는 rl 삽입
        for (int i = 0; i < surplus; i++)
        {
            sb.Append("rl");
        }


        if (vecOut[LR] > 0)
        {
            sb.Append('r', vecOut[LR]);
        }

        if (vecOut[UD] > 0)
        {
            sb.Append('u', vecOut[UD]);
        }

        Console.WriteLine(sb.Length == k);

        return sb.ToString();
    }
}