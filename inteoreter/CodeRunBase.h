//
// Created by Arosy on 2021/12/13.
//

#ifndef JVM_CODERUNBASE_H
#define JVM_CODERUNBASE_H
#include "ByteCode.h"
#include "BytecodeStream.h"
#include "../runtime/JavaThread.h"

/**
 * CODERUN 是“函数指针类型别名”：
 *   typedef void (*CODERUN)(...);
 * 等价于告诉编译器：“CODERUN 表示一个指针，它指向返回 void、参数为
 * (JavaThread*, BytecodeStream*, int&) 的函数”。这样我们就可以像使用普通类型一样
 * 声明数组 `CODERUN run[256]`，把每条指令对应的函数地址放进去。
 *
 * 参数含义：
 *  - javaThread：当前执行的 Java 线程，便于取出栈帧
 *  - bytecodeStream：当前方法的字节码流，用于读取操作数
 *  - index：字节码偏移（引用传参，函数内部可修改以跳转到下一条指令）
 */
typedef void (*CODERUN)(JavaThread *javaThread, BytecodeStream *bytecodeStream , int& index);

class CodeRunBase {
public:
    /**
     * 完整拆解：
     * 1. CODERUN 是 typedef 定义的函数指针别名，相当于 “指向 void(JavaThread*, BytecodeStream*, int&) 的函数”。
     *    写成 CODERUN x; 就是声明一个函数指针变量，可以指向 funcGETSTATIC 这类实现。
     * 2. CODERUN run[256]; 代表有 256 个这样的函数指针，等价于同时声明 run0...run255，只是用数组方便通过 opcode 索引。
     * 3. static 修饰说明它是 CodeRunBase 的静态成员，全局只有一份，可通过 CodeRunBase::run[i] 在任意位置访问。
     * 4. JVM 指令的 opcode 占 1 字节，范围 0~255，因此数组长度设为 256，确保每个 opcode 都能直接映射到对应的处理函数。
     * 综上：run 被当成 opcode -> 指令处理函数的查找表，initCodeRun() 会填充关系，解释器运行时执行 run[opcode](...) 即可。
     */
    static CODERUN run[256];
    static void initCodeRun(); // 启动时初始化 run[]，注册所有指令
    static void funcNOP(JavaThread *javaThread, BytecodeStream *bytecodeStream , int& index); // nop
    static void funcGETSTATIC(JavaThread *javaThread, BytecodeStream *bytecodeStream , int& index); // 取静态字段
    static void funcPUTSTATIC(JavaThread *javaThread, BytecodeStream *bytecodeStream , int& index); // 写静态字段
    static void funcLDC(JavaThread *javaThread, BytecodeStream *bytecodeStream , int& index); // 常量入栈
    static void funcICONST0(JavaThread *javaThread, BytecodeStream *bytecodeStream , int& index); // 推入 int 常量 0
    static void funcDUP(JavaThread *javaThread, BytecodeStream *bytecodeStream , int& index); // 栈顶复制
    static void funcALOAD0(JavaThread *javaThread, BytecodeStream *bytecodeStream , int& index); // 加载局部变量 0
    static void funcALOAD1(JavaThread *javaThread, BytecodeStream *bytecodeStream , int& index); // 加载局部变量 1
    static void funcNEW(JavaThread *javaThread, BytecodeStream *bytecodeStream , int& index); // 创建对象
    static void funcINVOKEVIRTUAL(JavaThread *javaThread, BytecodeStream *bytecodeStream , int& index); // 虚方法调用
    static void funcINVOKESPECIAL(JavaThread *javaThread, BytecodeStream *bytecodeStream , int& index); // 特殊方法调用
    static void funcRETURN(JavaThread *javaThread, BytecodeStream *bytecodeStream , int& index); // 返回
    /**
     * 根据方法描述符解析参数个数与类型，从 JavaVFrame 中准备参数数组。
     * @param descriptor JVM 方法描述符
     * @param jf 当前栈帧，用于读取局部变量或操作数栈
     * @param paramCount 输出参数个数（不包含 this）
     * @return 指向 char* 数组的指针，供调用指令传入 JNI 桥接层
     */
    static char **getParams(string descriptor, JavaVFrame *jf, int &paramCount);


};


#endif //JVM_CODERUNBASE_H
