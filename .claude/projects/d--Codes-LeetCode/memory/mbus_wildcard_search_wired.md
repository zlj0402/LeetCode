---
name: mbus-wildcard-search-wired
description: 有线 M-Bus 次级地址搜索实现（CEN/TR 17167 Annex B）
type: project
originSessionId: e3e53caf-73e3-4763-945d-efca9d29522e
---
# 有线 M-Bus Wildcard Search 实现

## 适用范围

- **有线 M-Bus 专属**（EN 13757-2）
- 用于主站发现总线上所有未知子表的次级地址

## 基本原理

使用通配符 (Fh) 逐位扫描 Identification Number：

- Identification Number (BCD): 每位可单独用 Fh 作为通配符
- Manufacturer/Version/Device Type (binary): 只能整字节用 FFh 作为通通符

## 搜索流程

1. 从 `0FFFFFFF` 开始，首位从 0 到 9 扫描
2. 无响应 → 继续扫描下一个值
3. 有响应 → 发送 REQ_UD2 获取次级地址
4. 有碰撞 → 进入下一位置细分搜索
5. 完成一个位置后，处理下一个位置

## 示例（4个仪表）

| 序号 | Identification No. | Manufacturer | Version | Device Type |
|-----|-------------------|-------------|---------|-------------|
| 1 | 14491001 | 1057 | 01 | 06 |
| 2 | 14491008 | 4567 | 01 | 06 |
| 3 | 32104833 | 2010 | 01 | 02 |
| 4 | 76543210 | 2010 | 01 | 03 |

搜索过程：
- `0FFFFFFF`: 无响应
- `1FFFFFFF`: 碰撞（No.1 和 No.2）
- `10FFFFFF` ~ `13FFFFFF`: 无响应
- `14FFFFFF`: 碰撞
- 细分至 `14491001` 和 `14491008` 分别获取
- `3FFFFFFF`: 获取 No.3
- `7FFFFFFF`: 获取 No.4

## 扩展搜索

可进一步搜索：
- Manufacturer code
- Version
- Device type
- Fabrication number（用于区分相同次级地址的仪表）

## 注意事项

- 需对所有使用的波特率执行搜索
- 碰撞检测依赖于主站的帧冲突检测能力
- 理论上可覆盖数百万种组合，但通过通配符策略高效收敛