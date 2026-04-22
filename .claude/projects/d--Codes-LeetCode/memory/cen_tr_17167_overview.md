---
name: cen-tr-17167-overview
description: CEN/TR 17167-2018 技术报告概述，EN 13757系列的配套补充文档
type: project
originSessionId: e3e53caf-73e3-4763-945d-efca9d29522e
---
# CEN/TR 17167-2018 技术报告概述

## 文档性质

- **类型**: Technical Report (TR) - 技术报告，非强制标准
- **作用**: EN 13757-2, -3, -7 的配套补充文档，提供示例和补充信息
- **版本**: 2018年发布，替代原 EN 13757-3:2013 的部分附录

## 各附录内容与适用范围

| Annex | 内容 | wired | wireless | 说明 |
|-------|-----|-------|----------|------|
| **A** | 有线 M-Bus 链路层报文示例 | ✓ | ✗ | RSP-UD、波特率切换、应用选择等 |
| **B** | 次级搜索实现指令 | ✓ | ✗ | Wildcard search 流程图和实现逻辑 |
| **C** | 智能计量应用的用户反馈 | ✓ | ✓ | 分辨率、时间精度要求 |
| **D** | 安装与注册程序 | (标注错误) | ✓ 实际无线 | **文档存在编辑错误**，实际内容为无线专属的 SND-IR/CNF-IR 注册流程 |
| **E** | M-Bus 数据容器实现 | ✓ | ✓ | 无线帧封装到有线消息的数据结构 |
| **F** | 有线和无线 M-Bus 报文示例 | ✓ | ✓ | Security mode 5/7/8/9/10 详细示例 |
| **G** | 描述符实现 | ✓ | ✓ | Storage、Tariff、Subunit 描述符 |

## 文档缺陷

Annex D 被文档正文和表格错误标注为有线专属，但实际内容描述的是无线 M-Bus 的安装程序：
- SND-IR (Send Installation Request) - EN 13757-4 定义，无线专属
- CNF-IR (Confirm Installation Request) - 无线专属
- RF-Link feedback - 无线专属概念