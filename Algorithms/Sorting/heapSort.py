def heapify(arr, idx, delim):
    leftchild = 2*idx 
    rightchild = 2*idx + 1

    if rightchild >= delim:
        return 

    if arr[leftchild] > arr[rightchild] and arr[leftchild] > arr[idx]:
        # swapping
        arr[leftchild] , arr[idx] = arr[idx] ,arr[leftchild]
        heapify(arr, leftchild, delim)

    elif arr[rightchild] > arr[idx]:
        # swapping
        arr[rightchild] , arr[idx] = arr[idx] ,arr[rightchild]
        heapify(arr, rightchild, delim)

def heapsort(arr , n):
    # building max heap
    for i in range(n//2, -1 ,-1):
        heapify(arr, i, n-1)

    for i in range(n-1, -1, -1):
        arr[i] ,arr[0] = arr[0] , arr[i]
        heapify(arr, 0, i)
        

mylist = [1,2]
heapsort(mylist,len(mylist))

print(mylist)
    