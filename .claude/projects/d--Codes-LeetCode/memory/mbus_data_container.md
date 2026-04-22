---
name: mbus-data-container
description: M-Bus 数据容器结构（CEN/TR 17167 Annex E）
type: project
originSessionId: e3e53caf-73e3-4763-945d-efca9d29522e
---
# M-Bus 数据容器

## 用途

将完整的无线 M-Bus 帧封装到有线 M-Bus 消息中传输。

典型应用场景：无线到有线 M-Bus 适配器（Radio to M-Bus adapter）。

## 数据结构

| 字段 | 值 | 说明 |
|-----|-----|------|
| DIF | 0Dh | 变长记录 |
| VIF | FDh | 扩展 VIF |
| VIFE | 3Bh 或 76h | 协议类型标识 |
| LVAR | 00h~BFh | 数据长度 |

## VIFE 值含义

- **3Bh**: 无线 M-Bus 协议数据容器
- **76h**: 制造商特定协议数据容器

## 无线 M-Bus 数据容器内容

- 从 L-field 和 C-field 开始的原始无线帧
- **不包括** CRC 块

## 分帧处理

当无线帧超过有线 M-Bus 报文最大长度时：
- 使用 DIF = 1Fh 表示"更多数据在下一报文"
- 通过 FCB 位翻转验证连续性

## 应用示例

无线适配器响应有线主站请求时：
- 有线帧包含适配器自身信息 + 无线仪表原始帧封装
- 后端系统可直接解封装并处理无线帧（包括解密）