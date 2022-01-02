#include <stdio.h>
#include <stdlib.h>

int abs(int a){
    if(a>0)
        return a;
    
    return (-1)*a;
}

int sq(int a){
    return a*a;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortedSquares(int* nums, int numsSize, int* returnSize){
    if(!numsSize)
        return NULL;
    
    *returnSize = numsSize;
    int* list = (int*)malloc(numsSize * sizeof(int));
    
    if(!list)
        return NULL;
    
    int i = 0;
    int j = numsSize-1;
    int n = numsSize-1;
    
    while(n >= 0){
        if(abs(nums[i]) > abs(nums[j])){
            list[n] = sq(nums[i]);
            printf("%d\n", list[n]);
            i += 1;
        }
        
        else{
            list[n] = sq(nums[j]);
            printf("%d\n", list[n]);
            j -= 1;
        }
        
        n -= 1;
    }
    
    return list;
}

int main(){
    int l[5] = {-4,-1,0,3,10};
    int retsize = 5;
    int* c = sortedSquares(l, 5, &retsize);
    
    
    for(int i=0; i<5; i++)
        printf("%d ", c[i]);
}