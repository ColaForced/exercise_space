#include <stack>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
private:
    bool res = false;

public:
    void backingTrace(vector<vector<char> >& matrix, vector<vector<int> > &used, int x, int y, int i, string &word)
    {
//        printf("x:%d, y:%d, i:%d, matrix[x][y]:%c, word[i]:%c\n",x, y, i, matrix[x][y], word[i]);
        if(i == word.size()){
            res = true;
            return;
        }
        if(matrix[x][y] != word[i]) return;

        int nx,ny;

        //up
        nx = x-1; ny = y;
        if(nx>=0 && !used[nx][ny])
        {
            used[x][y] = 1;
            backingTrace(matrix, used, nx,ny,i+1,word);
            used[x][y] = 0;
        }
        if(res) return;

        //down
        nx = x+1; ny = y;
        if(nx<used.size() && !used[nx][ny])
        {
            used[x][y] = 1;
            backingTrace(matrix, used, nx,ny,i+1,word);
            used[x][y] = 0;
        }
        if(res) return;

        //left
        nx = x; ny = y-1;
        if(ny>=0 && !used[nx][ny])
        {
            used[x][y] = 1;
            backingTrace(matrix, used, nx,ny,i+1,word);
            used[x][y] = 0;
        }
        if(res) return;

        //right
        nx = x; ny = y+1;
        if(nx<used[0].size() && !used[nx][ny])
        {
            used[x][y] = 1;
            backingTrace(matrix, used, nx,ny,i+1,word);
            used[x][y] = 0;
        }
        if(res) return;
    }


    bool hasPath(vector<vector<char> >& matrix, string word) {
        if(matrix.size() == 0) return false;
        if(word.size() == 0) return true;
        int row = matrix.size();
        int col = matrix[0].size();
        vector<vector<int> > used(row,vector<int>(col));
        for(int i=0; i<row; i++)
        {
            for(int j=0; j<col; j++)
            {
                if(matrix[i][j] == word[0])
                {
                    backingTrace(matrix, used, i, j, 0, word);
                    if(res) return res;
                }
            }
        }
        return res;
    }
};


int main()
{

    Solution sol;
    vector<vector<char> > nums = {{'a', 'b', 'c', 'e'},
                                  {'s', 'f', 'c', 's'},
                                  {'a', 'd', 'e', 'e'}};


    string word = "abcced";
    int res = sol.hasPath(nums, word);
    cout<<res;
}