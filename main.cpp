#include "Stream/ClassRead.h"              // 头文件使用相对路径引入，等价于 Java 的 import
#include "oop/InstanceKlass.h"
#include "classFile/BootClassLoader.h"
#include "runtime/JavaThread.h"
#include "native/JavaNativeInterface.h"
#include "inteoreter/CodeRunBase.h"
#include "inteoreter/CodeRunNative.h"
#include "runtime/Threads.h"


using namespace std; // 为了使用 std::string 等标准库类型，直接引入整个命名空间

void startVM(); // 函数声明，告诉编译器后面会有 startVM 的定义

int main() {
    startVM(); // 调用无返回值函数，等价于 startVM(void)
    string name = "jvm/HelloJVM"; // std::string 类型的栈变量，构造时直接赋字面量
    JavaThread *javaThread = new JavaThread;// 模拟线程的创建；new 返回堆对象指针
    Threads::curThread = javaThread; // “::” 访问静态成员，类似 Java 的 Class.staticField
    InstanceKlass *klass = BootClassLoader::loadKlass(name);//加载HelloJVM类
    MethodInfo *m = JavaNativeInterface::getMethod(klass, "main", "([Ljava/lang/String;)V");//遍历klass所有的方法，找到main方法
    JavaNativeInterface::callStaticMethod(javaThread,m);//执行main方法
    return 0; // main 返回 0 表示进程正常结束
}
void startVM(){
    CodeRunBase::initCodeRun();// 初始化字节码解释器，把解析JVM指令的方法全部存入map,以便使用
    CodeRunNative::initCodeRun();// 初始化本地方法，把本地方法全部存入map,以便使用
}; // C++ 允许函数定义后面加分号，通常省略，这里保留原风格
