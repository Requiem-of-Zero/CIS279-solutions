#ifndef LCSMATRIX_H
#define LCSMATRIX_H

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class LCSMatrix {
private:
   int rowCount, columnCount;
   vector<vector<int>> table;       // DP table of size rowCount x columnCount
   const string s1, s2;
   mutable unordered_map<string, unordered_set<string>> memo;

   // Recursive backtrace: all LCS strings ending at (i,j)
   unordered_set<string> backtrace(int i, int j) const {
      if (i < 0 || j < 0) {
         return { string("") };
      }
      string key = to_string(i) + "#" + to_string(j);
      auto it = memo.find(key);
      if (it != memo.end()) return it->second;
      unordered_set<string> result;
      if (s1[i] == s2[j]) {
         auto prev = backtrace(i-1, j-1);
         for (auto &str : prev) {
            result.insert(str + s1[i]);
         }
      } else {
         int up = (i>0 ? table[i-1][j] : 0);
         int left = (j>0 ? table[i][j-1] : 0);
         if (up > left) {
            result = backtrace(i-1, j);
         } else if (left > up) {
            result = backtrace(i, j-1);
         } else {
            auto a = backtrace(i-1, j);
            auto b = backtrace(i, j-1);
            result = std::move(a);
            result.insert(b.begin(), b.end());
         }
      }
      return memo[key] = result;
   }

public:
   LCSMatrix(const string &str1, const string &str2)
     : rowCount((int)str1.size()), columnCount((int)str2.size()),
     table(rowCount, vector<int>(columnCount, 0)),
       s1(str1), s2(str2)
   {
      for (int i = 0; i < rowCount; ++i) {
         for (int j = 0; j < columnCount; ++j) {
            if (s1[i] == s2[j]) {
               table[i][j] = 1 + ((i>0 && j>0) ? table[i-1][j-1] : 0);
            } else {
               int up   = (i>0 ? table[i-1][j] : 0);
               int left = (j>0 ? table[i][j-1] : 0);
               table[i][j] = (up > left ? up : left);
            }
         }
      }
   }

   int GetRowCount() const { return rowCount; }
   int GetColumnCount() const { return columnCount; }

   int GetEntry(int r, int c) const {
      if (r < 0 || c < 0 || r >= rowCount || c >= columnCount) return 0;
      return table[r][c];
   }

   unordered_set<string> GetLongestCommonSubsequences() const {
      memo.clear();
      if (rowCount == 0 || columnCount == 0) return {};
      int lcsLen = table[rowCount-1][columnCount-1];
      if (lcsLen == 0) return {};
      return backtrace(rowCount-1, columnCount-1);
   }
};

#endif // LCSMATRIX_H
