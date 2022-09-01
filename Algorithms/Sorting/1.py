def findMaxMin(ara, left, right) :
    if(left == right) :
        return [ara[right],ara[left]] ;
    mid = (left+right) //2 
    [a,b] = findMaxMin(ara,left,mid)
    [c,d] = findMaxMin(ara,mid+1, right) 

    return [max(a,c),min(b,d)] ;

li=[10,6,9,12,7,8,888,15]
[maxi,mini] = findMaxMin(li,0,7)
print([maxi,mini])