Tianchi C++ library for Qt
天池共享源码库

项目讨论区网址：http://www.qtcn.org/bbs/thread-htm-fid-105.html
有任何建议或意见、有任何问题请发邮件到 qtcn_tianchi@groups.163.com


创建日期: 2013.03.28
  原创者: Jonix Fu / 圣域天子
电子邮件: jonix@qtcn.org


简介
    天池共享源码库（以下简称Tianchi），是一套采用 C++ 语言，并且基于 Qt framework 的扩展库。
    创建该库的目的是为了进一步简化使用 Qt 开发过程中的复杂性。

    Tianchi 将考虑涉及各功能模块的类库、控件、插件等。

    Tianchi 采用全部源代码提供方式进行共享和参与。

使用
    允许任何人或机构均将 Tianchi 用于学习、工作以及商业等法律允许的场合。
    发布软件时，必须明确说明软件中包含了Tianchi，以及相关信息。


免责声明
    任何人可以对 Tianchi 提供代码、并更新、测试、建议等，一旦将代码提交到 Tianchi 库中，
    自动视为向 Tianchi 进行代码所有权的授权行为，并允许 Tianchi 团队对其进行改进、扩展、
    整合、甚至删除。

    代码提供者需要自动确保提供的代码具体版权，一旦存在版权纠纷，所产生的一切法律后果，将全
    部由代码提供者自行承担。

    倘若代码版权人发现 Tianchi 存在未经授权的代码，请及时通知 Tianchi 团队进行删除操作。

    由于 Tianchi 团队无法对历史版本进行修正或再发布，因此只能承诺对下个正式发布版进行修订。



发布位置：
    https://github.com/qtcn/tianchi
    https://github.com/jonixfu/tianchi


使用说明：
    下载并将 Tianchi 库复制到指定位置。
    Windows 下建议为 D:\Projects\Tianchi

    编译静态链接库：
        打开并编译：D:\Projects\Tianchi\build\static\static.pro
        生成静态库：D:\Projects\Tianchi\output\qtx.y.z-platform-spec\static\

        ※ 编译静态链接库，或直接引入源码编译器，不要定义 TIANCHI_EXPORT 或 TIANCHI_IMPORT
           DEFINES -= TIANCHI_EXPORT
           DEFINES -= TIANCHI_IMPORT

    编译动态链接库：
        打开并编译：D:\Projects\Tianchi\build\shared\shared.pro
        生成静态库：D:\Projects\Tianchi\output\qtx.y.z-platform-spec\shared

        ※ 编译 dll 时请在 .pro 中添加：
           DEFINES += TIANCHI_EXPORT

        ※ 编译使用 tianchi.dll 的 exe 时请在 .pro 中添加：
        DEFINES += TIANCHI_IMPORT
 
        ※※ debug 版的 exe 请使用 debug 版的 dll (文件名末尾加有d字样)
             release 版的 exe 请使用 relase 版的 dll
             否则可能会出现运行错误。

    使用designer/qtcreator插件:
        打开并编译: D:\Projects\Tianchi\build\designerplugin\designerplugin.pro
        生成的插件文件在 D:\Projects\Tianchi\output\qtx.y.z-platform-spec\shared
                    目录下即(lib)tianchidesignerplugin.dll(so)，将其拷贝到$QTDIR
                    \plugins\designer目录下重启designer程序即可,将其拷贝到
                    QtCreator安装目录下的bin\designer目录下重启qtcreator即可

====================================================================================
天池共享资源库用户许可协议
====================================================================================

重要须知--请认真阅读：
------------------------------------------------------------------------------------
    在您使用本软件产品之前,请务必阅读此《协议》，本《用户许可协议》（以下称《协议》）
是您（个人或单一实体）与天池共享资源库开发组（以下称“版权人”）之间有关上述天池共享
资源库开发组软件产品的协议。

许可协议
------------------------------------------------------------------------------------
1、授予您下列权利
    本“软件产品”是基于 GNU LESSER GENERAL PUBLIC LICENSE V2 开源协议的基础上发布
的开源软件，允许动态链接库或静态链接库的方式使用，如果您对产品的代码有部分修改，在您
方便并条件允许的情况下，希望您发给我们一份修改后的代码片段副本，我们表示感谢。

2、复制、分发和传播
    您可以复制、分发和传播无限制数量的本软件产品，但您必须保证每一份复制、分发和传播
都必须是完整和真实的，包括所有有关本软件产品的软件、电子文档，版权和商标宣言，亦包括
本协议。本软件可以独立分发亦可随同其他软件一起分发，但如因此而引起任何问题，版权人将
不予承担任何责任。

3、限制和保护条款
    未经特别许可，不得出租或租赁本"软件产品"。

4、免责声明
    本软件版权人特此申明对本软件产品之使用不提供任何保证。版权人将不对任何用户保证本
软件产品的适用性，不保证无故障产生，不对任何用户使用此软件所遭遇到的任何理论上的或实
际上的损失承担负责。使用本软件产品由用户自己承担风险。

5、附加条款
    您可能阅读到其他语言（指自然语言，如：英语）的《协议》副本，由于不同语言之间的翻
译可能会产生与原始《协议》语义或内容上的差异，由此产生的差异均以简体中文语言版本为基
准。
    天池共享资源库开发组对以上各项条款内容的拥有最终解释权。



====================================================================================
欢迎参与天池共享源码库(Tianchi)的工作
====================================================================================

您可以:
  1. 提供资金支持。
  2. 提供免费、可开源的代码。请不要涉及版权、隐私、商业机密、专利等特殊源码。
  3. 修改、更新已有的代码。
  4. 对现有代码进行编译、测试，或提出建议。
  5. 制作、更新共享库的文档。


天池共享源码库的目标：
  1. 天池共享源码库(Tianchi) 基于 Qt 库进行扩展和延伸。
  2. 尽可能支持所有Qt支持的操作系统和编译器。
  3. 提供动态库、静态库和直接编译使用。
  4. 所有源代码以 GBK 的编码格式保存，以便兼容简体中文，并支持所有编译器。


参与规则：
    文档要求：
        1. 所有项目中文字条款和规则，以 .txt 方式保存。
        2. 需要图文说明的文档，尽可能采用常用文档格式，如 .doc, .xls, .ppt 等。

    代码规范：
      1. 除特殊约定以外，所有类，全部在全局中，并以Tc为前缀。
      2. 全局函数，或放在类中(静态成员函数)，或放在Tc名字空间或其子名字空间下
      3. 枚举类型，或定义在类中，或定义在Tc名字空间或其子名字空间下。
      4. 目录、文件名均小写，文件名与主要类名保持一致。
      5. 自定义类成员变量名加前缀为 m_ 。若要定义Private类，请参考include/tianchi/gui/tclineedit.h和src/gui/tclineedit.cpp
      6. 方法名的命名方式参照 Qt 标准，首字母小写，其它单词首字母大写，中间不含下划线（_)
      7. 类成员的 get 方法不含 get 前缀，但 set 方法全部包含 set 前缀
      8. 除头文件防重复包含的预定义名外，其它预编译条件禁止使用 #ifndef ，请改为 #ifdef 或 #if defined(...)
      9. 对于函数定义中不使用的参数，使用Q_UNUSED(xxx)来消除编译警告信息
     10. 对于要固定基本类型的变量或常量，请使用qint8, quint8, qint16, qint32, qlonglong, qint64等，避免使用__int64等类型
     11. 判断编译器请使用Q_CC_GNU,Q_CC_MSVC类宏,判断操作系统平台请使用Q_OS_WIN, Q_OS_WIN32, Q_OS_WIN64之类的宏
     12. 在同时兼容Qt4和Qt5的代码中,禁止使用C++11特性
     13. 在代码中禁止使用Qt定义的关键字,而是使用宏代替,比如signals/Q_SIGNALS,   slots/Q_SLOTS, emit/Q_EMIT, foeach/Q_FOREACH
     14. 类设计尽量保持二进制兼容(可采用Private类设计), 对于不可复制的类,请使用Q_DISABLE_COPY宏说明
     15. 允许参与者在源码的注释部分包括自己的名字和简介
     16. 对为 public 接口进行用途和用法说明，共享库最终使用 doxygen 输出使用文档，请遵循 doxygen 的语法要求。
     17. 源码发布格式统一采用 AStyle 方式整理，对参与人员不作强制要求，但请尽量保持代码有较高可读性。
     18. 《天池》核心团队有权在正式版发布时，修改、删除其中的代码，并且不对更新者进行说明或解析。



约定目录与文件：
    建议工程目录：
        Windows:
            D:\Projects\tianchi

    Doxygen 配置文件：
        D:\Projects\tianchi\design\tianchi.doxygen
        http://sourceforge.net/projects/doxygen/

    AStyle 配置文件：
        D:\Projects\tianchi\design\tianchi.astyle
        http://sourceforge.net/projects/astyle/

    参与人员列表：
        D:\Projects\tianchi\design\members.txt
