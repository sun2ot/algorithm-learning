#include <stdio.h>

/**
 * 二分查找算法
 * 在有序数组中查找目标元素的索引
 * 
 * @param nums 有序数组
 * @param size 数组大小
 * @param target 目标元素
 * @return 目标元素的索引，如果不存在则返回-1
 */
int binarySearch(int nums[], int size, int target) {
    
    int left = 0; // 左边界
    int right = size - 1; // 右边界

    while (left <= right) {
        // 因为是升序，所以可以保证 right>=left
        int mid = left + (right - left) / 2;

        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1; // 如果目标元素不存在于数组中，则返回-1
}

int main() {
    int nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(nums) / sizeof(nums[0]);
    int target = 5;

    int index = binarySearch(nums, size, target);

    if (index != -1) {
        printf("目标元素 %d 在数组中的索引位置为: %d\n", target, index);
    } else {
        printf("目标元素 %d 不存在于数组中\n", target);
    }

    return 0;
}
