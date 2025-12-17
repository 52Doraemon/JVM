# Repository Guidelines

## 项目结构与模块规划
- `main.cpp` 负责启动 JVM 模拟器、初始化引导类加载器并默认执行 `HelloJVM`，可作为调试参考入口。
- `classFile/` 处理 `.class` 文件读取与解析（`BootClassLoader`、`ClassFileParser`），`Stream/` 提供底层读取工具。
- `oop/` 定义 JVM 元数据结构（如 `InstanceKlass`、`ConstantPool`、`MethodInfo` 及属性表）以映射规范。
- `inteoreter/` 存放字节码解释器、Native 桥接及指令表，`runtime/` 维护线程、栈帧、公共值等运行时实体。
- `native/` 与 `util/` 承载 JNI 封装与通用类型，新增模块请比照现有目录划分并同步更新 `CMakeLists.txt`。

## 构建、测试与开发命令
- 使用 CMake 3.16+：`cmake -S . -B build && cmake --build build`，CLion 默认的 `cmake-build-debug` 与之兼容。
- 编译后执行 `build/JVM`（或 IDE 目标）；确保 `.class` 文件位于 `BootClassLoader::prePath` 所指目录。
- 在构建目录运行 `ctest --output-on-failure` 进行冒烟测试；若添加新用例，请通过 CTest 统一管理。

## 代码风格与命名约定
- 遵循现有 C++11 风格：4 空格缩进、函数同行花括号、头文件需有 include guard。
- 类名使用帕斯卡命名（如 `InstanceKlass`），函数/变量采用驼峰命名（如 `loadKlass`），常量使用全大写（如 `MAGIC`）。
- 尽量保持 `.h/.cpp` 成对放置在对应目录，并在 `CMakeLists.txt` 中显式列出，避免隐式依赖。

## 测试准则
- 现阶段以场景测试为主，建议仿照 `jvm/HelloJVM.class` 准备输入并核对解释器输出。
- 若新增自动化测试，统一放置于独立目录，文件命名 `*Test.cpp`，并通过 CTest 暴露，保证 `cmake --build` 自动集成。
- 复杂修改（尤其涉及字节码或 Native）请在 PR 中附上手动复现步骤，方便回归。

## 提交与 PR 指南
- Git 历史以简洁祈使句为主（如 `执行引擎总结`、`UPDATEREADME`），建议 60 字符以内聚焦核心变更。
- 提交信息或 PR 描述需关联 Issue、说明影响面，并给出验证方式或截图（如更改打印输出）。
- PR 请主动提示风险点（类加载、JNI 调用等），并说明如需修改 `BootClassLoader::prePath` 的操作方式，便于 reviewer 运行。

## 安全与配置提示
- `BootClassLoader::prePath` 目前是绝对路径，推荐改由配置或环境变量注入，避免提交个人路径。
- 不要提交编译产物或 IDE 目录， `.class` 用例请说明生成方式，确保贡献者可以安全复现。
