---
name: mbus-descriptors
description: M-Bus 描述符实现（CEN/TR 17167 Annex G）
type: project
originSessionId: e3e53caf-73e3-4763-945d-efca9d29522e
---
# M-Bus 描述符

## 用途

描述符用于声明以下数据点字段的含义：
- Storage number → Storage interval descriptor
- Tariff → Tariff descriptor  
- Subunit → Subunit descriptor

描述符与数据点的链接通过 DIB (Data Information Block) 建立。

## Storage 描述符

### Storage Interval Descriptor

声明存储号范围用于历史值（周期性测量）：

| VIB | 说明 |
|-----|------|
| FDh 29h | 年间隔 |
| FDh 28h | 月间隔 |
| FDh 27h | 日间隔 |
| FDh 26h | 小时间隔 |
| FDh 25h | 分钟间隔 |
| FDh 24h | 秒间隔 |

- 值使用最老或最新测量值的存储号
- Tariff/function/subunit 字段设为 0
- 值编码为 type B

### Storage Range Descriptor

| VIB | 说明 |
|-----|------|
| FDh 20h | 循环存储起始号（最老值） |
| FDh 21h | 循环存储结束号（最新值） |
| FDh 22h | 存储块大小 |

## Subunit 描述符

编码: 01h FDh 23h xx

| 索引值 | 说明 |
|--------|------|
| 0 | 主寄存器（传统） |
| 1-4 | OBIS 值组 B=1~4（电表） |
| 5 | Tariff subunit |
| 6 | Minimum subunit |
| 7 | Maximum subunit |
| 8 | Data logger |
| 9 | Event logger |
| 10 | Test subunit |
| 11 | Calibration subunit |
| 12 | Adjustment subunit |
| 13-20 | Pulse collector 1~8 |
| 21-29 | Configuration subunit |
| 100-127 | 制造商特定 |

## Tariff 描述符

编码: 01h FDh 23h xx（与 subunit 相同 VIFE）

| 索引值 | 说明 |
|--------|------|
| 150 | 每日绝对时间（如 8:00-11:00） |
| 151 | 星期（如周六周日） |
| 152 | 月内日期（如每月15号） |
| 160-165 | 阈值基础（温度、流量、功率） |
| 190-192 | 消费基础（能量、体积、财务） |
| 210-212 | 组合 tariff |
| 230-233 | 正/负/供热/制冷能量 |
| 234-235 | 外部输入控制 |

## 使用规则

- Subunit descriptor 使用声明的 subunit 号，其他字段设为 0
- Tariff descriptor 使用声明的 tariff 号，其他字段设为 0
- 一个描述符对整个设备有效