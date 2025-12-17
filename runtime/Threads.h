//
// Created by Arosy on 2022/2/6.
//

#ifndef JVM_THREADS_H
#define JVM_THREADS_H


#include "JavaThread.h"

/**
 * 线程管理器：
 * 在这个轻量级实现里仅维护一个全局静态指针，指向当前正在运行的 JavaThread。
 * main.cpp 会在启动虚拟机时创建 JavaThread，并赋值给 Threads::curThread，
 * 后续解释执行、Native 调用等都通过该指针访问线程的栈、局部变量等运行时数据。
 */
class Threads {
public:
    /**
     * 指向当前线程对象的静态成员。
     * 相当于 HotSpot 的 Threads::current() 简化版，提供全局访问入口。
     */
    static JavaThread* curThread;
};


#endif //JVM_THREADS_H
