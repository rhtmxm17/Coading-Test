using System;
using System.Collections.Generic;

public class Solution
{
    private const int ALPHABET_NUM = 26;

    public string solution(long n, string[] bans)
    {
        long fullDictN = n; // 꽉 찬 사전이었다면 몇 번째 글자인지
        long[] banIndexes = new long[bans.Length];
        for (int i = 0; i < bans.Length; i++)
        {
            banIndexes[i] = SpellToIndex(bans[i]);
        }
        Array.Sort(banIndexes);

        // n번째 주문 앞에 삭제된 주문의 개수 구하기
        // 삭제된 주문을 정렬해두었으므로 시작 위치는 이진탐색을 사용

        int banned = Array.BinarySearch(banIndexes, fullDictN);
        if (banned < 0)
            banned = ~banned; // 찾지 못한 경우 보수 취하기
        else
            banned++; // 일치한 경우 그 다음위치에서 탐색 시작해야하므로 1 추가

        fullDictN = n + banned;

        while (banned < banIndexes.Length)
        {
            if (banIndexes[banned] > fullDictN)
                break;

            banned++;
            fullDictN++;
        }

        // 찾은 위치의 번호를 사전 문자열로 변환

        List<char> answer = new List<char>();
        while (fullDictN > 0)
        {
            fullDictN--;
            answer.Add((char)(fullDictN % ALPHABET_NUM + 'a')); // 나머지가 0 ~ 25 => a ~ z
            fullDictN /= ALPHABET_NUM;
        }

        answer.Reverse(); // 가장 작은 자릿수가 먼저 담겼으므로 반전

        return new string(answer.ToArray());
    }


    // 주문이 꽉 찬 사전에서 몇번째인지 반환
    public static long SpellToIndex(string spell)
    {
        long index = 0;

        long digitBase = 1; // 자릿수 숫자 (26^n)
        for (int i = spell.Length - 1; i >= 0; i--)
        {
            index += (spell[i] - 'a' + 1) * digitBase; // a ~ z => 1 ~ 26
            digitBase *= ALPHABET_NUM;
        }

        return index;
    }
}