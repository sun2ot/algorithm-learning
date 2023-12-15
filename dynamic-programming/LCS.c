#include <stdio.h>
#include <string.h>

/**
 * 使用动态规划解决最长公共子序列问题
 * 
 * @param str1 字符串1
 * @param str2 字符串2
 */
void longestCommonSubsequence(char* str1, char* str2) {
    int m = strlen(str1);
    int n = strlen(str2);

    int dp[m + 1][n + 1];

    // 初始化dp数组的第一行和第一列
    for (int i = 0; i <= m; i++) {  
        dp[i][0] = 0;  
    }
    for (int j = 0; j <= n; j++) {
        dp[0][j] = 0;
    }

    // 计算dp数组的其他元素
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (str1[i - 1] == str2[j - 1]) {  // 两个子串的最后一个字符相同
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }

    // 构造最长公共子序列
    int lcsLength = dp[m][n];
    char lcs[lcsLength + 1];
    lcs[lcsLength] = '\0';

    int i = m, j = n;
    while (i > 0 && j > 0) {
        // 串的扫描和LCS的构建都是从右往左，倒着来
        if (str1[i - 1] == str2[j - 1]) {  // 两个串的尾部字符相等，说明该字符属于LCS
            lcs[lcsLength - 1] = str1[i - 1];
            i--;
            j--;
            lcsLength--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {  // 删去str1最后一个字符得到的LCS比删去str2最后一个字符得到的LCS长，因此i向前回溯
            i--;
        } else {
            j--;
        }
    }
    printf("LAS Length is: %d\n", dp[m][n]);
    printf("LCS is: %s\n", lcs);  // 注意，最长公共子序列并不唯一
}

int main() {
    char str1[] = "ABCBDAB";
    char str2[] = "BDCABA";

    longestCommonSubsequence(str1, str2);

    return 0;
}
