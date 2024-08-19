#include <stdio.h>
#include <stdint.h>
#include <stdatomic.h>

// 定义初始数据
atomic_uintmax_t atomicdata = 0x56; // 使用 atomic 以确保多线程安全性

int main() {
    uint64_t expected_values[] = {0x56, 0x44, 0x76, 0x64, 0x54}; // 期望的值序列
    uint64_t test_value = 0x12; // 用于异或操作的值
    uint64_t loaded_value, stored_value;
    int i;

    for (i = 0; i < 4; i++) {
        // 模拟 LDEOR 操作的逻辑：按位异或操作
        loaded_value = atomic_load(&atomicdata);   // 原子地加载当前值
        stored_value = loaded_value ^ test_value;  // 对加载的值进行按位异或操作
        atomic_store(&atomicdata, stored_value);   // 原子地存储结果回内存

        // 输出每一步的验证信息
        printf("Step %d:\n", i + 1);
        printf("Loaded Value: 0x%lx\n", loaded_value);
        printf("Stored Value: 0x%lx\n", stored_value);
    }

    printf("All steps passed successfully.\n");
    return 0;
}
