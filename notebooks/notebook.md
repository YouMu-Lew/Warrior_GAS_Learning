# Notes

## Unreal Engine

### UE5 类名前缀含义对照表
在 Unreal Engine 5 (UE5) 中，类名的前缀字母是引擎编码规范的核心部分，它们代表了类的继承关系和基本类型。这些前缀不仅有助于代码的可读性，还与引擎的反射系统、内存管理和垃圾回收机制紧密集成。

| 前缀 | 继承自 | 核心职责与特性 | 典型示例 |
| :--- | :--- | :--- | :--- |
| **`U`** | `UObject` | **引擎对象基石**：支持垃圾回收、反射、序列化、复制等核心功能。 | `UStaticMeshComponent`, `UMaterial`, `UMyGameInstance` |
| **`A`** | `AActor` | **场景中的实体**：可被放置于关卡中，是组件的容器，拥有生命周期（`BeginPlay`, `Tick`, `EndPlay`）。 | `ACharacter`, `APawn`, `AMyTriggerVolume` |
| **`F`** | 无 (普通类/结构体) | **纯数据与工具**：通常是值类型，不支持引擎的反射系统，需手动管理内存。 | `FVector`, `FRotator`, `FMyDataStruct` |
| **`E`** | 无 (枚举) | **枚举类型**：定义一组命名的常量值。 | `ECollisionChannel`, `EMyAbilityType` |
| **`I`** | 无 (接口) | **接口契约**：定义一组函数，其他类可实现这些函数，实现多态。 | `IAbilitySystemInterface`, `UMyInterface` (实现类仍带U) |
| **`S`** | `SWidget` | **Slate UI元素**：用于构建编辑器UI和游戏内UMG的底层控件。 | `SButton`, `STextBlock` (主要在编辑器代码中使用) |
| **`T`** | 无 (模板类) | **模板容器**：类似于C++标准库的模板类。 | `TArray`, `TMap`, `TSharedPtr` |

### OwnerActor 和 AvatarActor

在UE5的Gameplay Ability System (GAS) 中，`OwnerActor`和`AvatarActor`是两个关键概念。为了帮你快速理解，下面这个表格概括了它们的核心区别：

| 特性维度 | OwnerActor (所有者Actor) | AvatarActor (化身Actor) |
| :--- | :--- | :--- |
| **核心职责** | **逻辑控制**与**数据存储** | **视觉表现**与**世界交互** |
| **典型对象** | PlayerState, PlayerController | Character, Pawn |
| **网络角色** | 通常为**Authority**（服务器权威端） | 可在客户端**预测**执行 |
| **生命周期** | **持久存在**（如PlayerState跨越关卡） | **可能被销毁重建**（如角色死亡重生） |
| **数据关联** | 存储**永久状态数据**（如等级、金币） | 存储**临时表现数据**（如当前动画状态） |

#### 🔗 二者如何协作

`OwnerActor`和`AvatarActor`在GAS中通过**初始化绑定**和**技能执行**进行协作：

-   **初始化绑定**：在角色（如`Character`）创建时，你需要调用`AbilitySystemComponent->InitAbilityActorInfo(OwnerActor, AvatarActor)`来建立两者的关联。这通常会在`Pawn`的`Controller`（控制器）设置后执行，例如将`PlayerState`（所有者）和`Character`自身（化身）传递给系统。
-   **技能执行**：当激活一个技能（如开枪）时：
    -   从`OwnerActor`获取**逻辑决策**信息（如是否允许开枪、计算伤害）。
    -   从`AvatarActor`获取**视觉表现**相关元素（如播放举枪动画、在枪口生成粒子特效）。

#### 🌐 网络同步机制

在多人游戏中，理解它们的网络同步机制至关重要：

| 网络角色 | OwnerActor | AvatarActor | 同步策略 |
| :--- | :--- | :--- | :--- |
| **Server** | 完全控制 | 完全控制 | Authority |
| **Client** | 只读副本 | 预测执行 | Autonomous Proxy |
| **Simulated** | 只读副本 | 模拟表现 | Simulated Proxy |

*此表基于GASDocumentation项目的解析和官方关于Actor角色与远程角色的说明。*

-   **权限控制**：关键的逻辑判断（如造成伤害）必须在`OwnerActor`端（且`Role`为`ROLE_Authority`时）执行，以确保游戏的公平性和一致性。
-   **预测与模拟**：`AvatarActor`在客户端可以进行**预测执行**（如移动和动画）以提升响应速度，如果预测失败，服务器会进行纠正。对于其他客户端上非自己控制的角色，其`AvatarActor`则表现为**模拟代理**（`ROLE_SimulatedProxy`），根据服务器同步的数据进行模拟。

#### 💡 实用技巧与常见问题

-   **正确获取Actor**：在技能或组件中，推荐使用GAS提供的辅助函数来获取正确的Actor引用：
    ```cpp 
    // 推荐使用内置辅助函数
    AActor* GetAvatarActorFromActorInfo(); // 获取化身Actor
    AActor* GetOwningActorFromActorInfo(); // 获取所有者Actor
    UAbilitySystemComponent* GetAbilitySystemComponentFromActorInfo();
    ```
-   **谨记权限检查**：在执行可能影响游戏状态的操作（如扣除血量、消耗物品）前，务必在服务器端进行权限验证：
    ```cpp
    // 在服务端验证权限
    if (GetOwningActorFromActorInfo()->GetLocalRole() == ROLE_Authority)
    {
        // 执行需要权威验证的逻辑
    }
    ```
-   **典型问题排查**：
    -   **技能无法激活或表现异常**：首先检查`InitAbilityActorInfo`中`OwnerActor`和`AvatarActor`的绑定是否正确设置。
    -   **网络同步延迟**：合理利用GAS的**预测机制**和**回滚功能**来处理客户端预测与服务器结果不一致的情况。

#### 总结

`OwnerActor`和`AvatarActor`的分离设计是GAS架构的核心优势之一，它实现了**逻辑控制**与**视觉表现**的解耦。理解并正确运用这两者的关系，对于构建健壮、可维护且网络同步高效的游戏技能系统至关重要。
