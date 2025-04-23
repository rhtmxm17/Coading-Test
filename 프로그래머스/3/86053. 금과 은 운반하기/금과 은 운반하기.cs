using System;

public class Solution
{
    // parametric search

    public long solution(int a, int b, int[] g, int[] s, int[] w, int[] t)
    {
        long begin = 0; 
        long end = long.MaxValue >> 1; // 성공한 케이스의 시간을 저장
        long middle = (begin + end) >> 1; // 실패한 케이스의 시간을 저장


        while (begin != middle)
        {
            if(TryIt(middle, a, b, g, s, w, t))
            {
                end = middle;
                middle = (begin + end) >> 1;
            }
            else
            {
                begin = middle;
                middle = (begin + end) >> 1;
            }
        }

        return end;
    }

    static bool TryIt(long timeout, int goldReq, int silvReq, int[] gold, int[] silver, int[] weight, int[] timeReq)
    {
        int total_req = goldReq + silvReq;
        int index = gold.Length;
        for (int i = 0; i < index; i++)
        {
            long numOfCycle = Smoller((timeReq[i] + timeout) / (2 * timeReq[i]), int.MaxValue); // 시간 내 운반 가능 횟수
            int canCarryWeight = Smoller(numOfCycle * weight[i], int.MaxValue); // 시간 내 운반 가능 양

            total_req -= Smoller(canCarryWeight, (gold[i] + silver[i])); // 실제로 운반 한 양 차감
            goldReq -= Smoller(canCarryWeight , gold[i]);
            silvReq -= Smoller(canCarryWeight, silver[i]); 

            if (total_req <= 0 && goldReq <= 0 && silvReq <= 0) // 모든 요구량 충족시
                return true;
        }
        return false;
    }

    static int Smoller(long a, int b)
    {
        return a < b ? (int)a : b;
    }

    static int Smoller(int a, int b)
    {
        return a < b ? a : b;
    }
}