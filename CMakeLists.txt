cmake_minimum_required(VERSION 3.16)
project(JVM)

set(CMAKE_CXX_STANDARD 11)

# 1. 先创建可执行文件目标 JVM
add_executable(JVM
        main.cpp
        Stream/ClassRead.cpp Stream/ClassRead.h
        oop/InstanceKlass.cpp oop/InstanceKlass.h
        classFile/ClassFileParser.cpp classFile/ClassFileParser.h
        oop/ConstantPool.cpp oop/ConstantPool.h
        util/BasicType.h
        oop/InterfacesInfo.cpp oop/InterfacesInfo.h
        oop/FieldsInfo.cpp oop/FieldsInfo.h
        oop/CodeAttributeInfo.cpp oop/CodeAttributeInfo.h
        inteoreter/BytecodeStream.cpp inteoreter/BytecodeStream.h
        oop/MethodInfo.cpp oop/MethodInfo.h
        oop/LineNumberTable.cpp oop/LineNumberTable.h
        oop/LocalVariableTable.cpp oop/LocalVariableTable.h
        oop/AttributeInfo.cpp oop/AttributeInfo.h
        classFile/BootClassLoader.cpp classFile/BootClassLoader.h
        runtime/JavaThread.cpp runtime/JavaThread.h
        runtime/JavaVFrame.cpp runtime/JavaVFrame.h
        native/JavaNativeInterface.cpp native/JavaNativeInterface.h
        inteoreter/BytecodeInterpreter.cpp inteoreter/BytecodeInterpreter.h
        inteoreter/CodeRunBase.cpp inteoreter/CodeRunBase.h
        inteoreter/ByteCode.h
        runtime/CommonValue.cpp runtime/CommonValue.h
        inteoreter/ByteType.h
        oop/InstanceOop.cpp oop/InstanceOop.h
        inteoreter/CodeRunNative.cpp inteoreter/CodeRunNative.h
        runtime/Threads.cpp runtime/Threads.h
)

# 2. 目标创建好了，现在如果是 Windows，就把 ws2_32 链接上去
if(WIN32)
    target_link_libraries(JVM ws2_32)
endif()