public class Solution
{
    public long solution(int n)
    {
        long factoN = 1;
        long Nto2N = 1;

        for (int i = 1; i <= n; i++)
        {
            factoN *= i;
        }

        for (int i = n + 2;i <= 2 * n; i++)
        {
            Nto2N *= i;
        }

        return (long)(Nto2N / factoN);
    }
}