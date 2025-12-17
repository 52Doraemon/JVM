//
// Created by Arosy on 2021/12/11.
//

#ifndef JVM_JAVATHREAD_H
#define JVM_JAVATHREAD_H

#include "stack"
#include "JavaVFrame.h"
using namespace std;
/**
 * JavaThread 模拟 HotSpot 中的 Java 线程执行环境。
 * 它维护一个 C++ STL stack，用来保存当前线程上的 JavaVFrame（虚拟机栈帧）。
 * 每当解释器调用一个新方法，就会创建 JavaVFrame 并 push 进该栈；
 * 方法返回时再 pop，对应 JVM 规范中的“Java 栈”。
 */
class JavaThread {
public:
    stack<JavaVFrame*> stack; // 线程的虚拟机栈，栈元素为 JavaVFrame*
    /**
     * 返回栈顶元素并将其弹出，用于方法返回时回收当前帧。
     * @return 栈顶 JavaVFrame 指针；栈为空时行为未定义，需要调用方保证
     */
    JavaVFrame* getAndPop();
};


#endif //JVM_JAVATHREAD_H
