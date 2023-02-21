# Time:  O(n)
# Space: O(1)

class Solution(object):
    def equalSubstring(self, s, t, maxCost):
        """
        :type s: str
        :type t: str
        :type maxCost: int
        :rtype: int
        """
        left = 0
        for right in range(len(s)):
            maxCost -= abs(ord(s[right])-ord(t[right]))
            if maxCost < 0:
                maxCost += abs(ord(s[left])-ord(t[left]))
                left += 1
        # you can not use "right" outside the loop
        return (right+1)-left 
        
        #a proper return should look like this:
        return len(s) - left
