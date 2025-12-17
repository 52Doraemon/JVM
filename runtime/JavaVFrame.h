//
// Created by Arosy on 2021/12/11.
//

#ifndef JVM_JAVAVFRAME_H
#define JVM_JAVAVFRAME_H
#include "stack"
#include "map"
#include "CommonValue.h"
using namespace std;

/**
 * JavaVFrame 表示一个 Java 方法的栈帧（Virtual Frame）。
 * - stack：对应 JVM 操作数栈，保存指令执行过程中的临时数据
 * - locals：对应局部变量表，key 为槽位索引，value 为 CommonValue*
 * 在方法调用时由 JavaNativeInterface 创建并压入 JavaThread 的栈顶。
 */
class JavaVFrame {
public:
    stack<CommonValue*> stack; // 方法执行过程的操作数栈
    map<int,CommonValue*> locals; // 局部变量表，包含参数和局部变量
    CommonValue* pop(); // 从操作数栈顶弹出一个值
    //todo:释放内存
};


#endif //JVM_JAVAVFRAME_H
