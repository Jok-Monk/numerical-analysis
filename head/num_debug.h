#ifndef NUM_DEBUG_H
#define NUM_DEBUG_H

#include <stdio.h>
#include <math.h>
#include <time.h>

// ================== 调试系统配置 ==================
#define DEBUG_LEVEL 3  // 0=关闭, 1=基础, 2=详细, 3=全量
#define FLOAT_TOLERANCE 1e-12  // 浮点比较容差

// ================== 核心调试宏 ==================
#if DEBUG_LEVEL > 0
// 基础调试输出（自动捕获位置信息）
#define LOG(fmt, ...) \
    fprintf(stderr, "[NUM] %s:%d (%s) | " fmt, \
            __FILE__, __LINE__, __func__, ##__VA_ARGS__)

// 自动变量追踪（自动显示变量名和值）
#define TRACE(var, fmt) \
    LOG("追踪变量: "#var" = "fmt"\n", var)

// 容错浮点比较（自动处理精度问题）
#define FLOAT_EQ(a, b) \
    (fabs((a)-(b)) < FLOAT_TOLERANCE)

// 增强断言（带错误码返回）
#define SAFE_ASSERT(expr, err_code) \
    do { \
        if (!(expr)) { \
            LOG("断言失败: "#expr"\n"); \
            return err_code; \
        } \
    } while(0)

#else
// 禁用调试时替换为空
#define LOG(...)
#define TRACE(...)
#define FLOAT_EQ(a, b) ((a)==(b))
#define SAFE_ASSERT(...)
#endif

// ================== 进阶调试工具 ==================
#if DEBUG_LEVEL >= 2
// 迭代过程跟踪
#define ITER_LOG(iter, fmt, ...) \
    LOG("[迭代%d] "fmt, iter, ##__VA_ARGS__)

// 内存检查（自动检查指针有效性）
#define MEM_CHECK(ptr) \
    do { \
        if ((ptr) == NULL) { \
            LOG("内存分配失败: "#ptr"\n"); \
            return ERROR_MEMORY; \
        } \
    } while(0)
#endif

#if DEBUG_LEVEL >= 3
// 性能计时器（自动计算作用域耗时）
#define TIME_SCOPE() \
    clock_t _start_time_##__LINE__ = clock(); \
    for(; (void)(clock() - _start_time_##__LINE__); )

// 数据快照（记录数组/向量状态）
#define SNAPSHOT_ARR(name, arr, len, fmt) \
    do { \
        LOG("数据快照: "#name"\n"); \
        for(int _i=0; _i<(len); _i++) \
            fprintf(stderr, "  [%d] "fmt"\n", _i, (arr)[_i]); \
    } while(0)
#endif

// ================== 错误码定义 ==================
#define SUCCESS           0
#define ERROR_INVALID_ARG 1
#define ERROR_NUMERICAL   2
#define ERROR_MEMORY      3

#endif // NUM_DEBUG_H