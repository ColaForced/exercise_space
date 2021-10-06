class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> matrix(n, vector<int>(n,0));
        int startx = 0, starty = 0;
        int i,j;
        int loop = n/2;
        int offset = 1;
        int count = 1;

        while(loop--)
        {
            i = startx; j = starty;
            for(; j < starty + n - offset; j++) matrix[i][j] = count++;
            for(; i < startx + n - offset; i++) matrix[i][j] = count++;
            for(; j > starty; j--) matrix[i][j] = count++;
            for(; i > startx; i--) matrix[i][j] = count++;

            offset += 2;
            startx += 1;
            starty += 1;
        }
        if (n%2) matrix[n/2][n/2] = count;

        return matrix;
    }
};