---
name: mbus-security-modes-examples
description: M-Bus 安全模式示例（CEN/TR 17167 Annex F）
type: project
originSessionId: e3e53caf-73e3-4763-945d-efca9d29522e
---
# M-Bus Security Modes 示例

## Security Mode 对照

| Mode | 算法 | 加密 | 认证 | MAC大小 | 说明 |
|------|-----|------|------|---------|------|
| 0 | 无 | ✗ | ✗ | 0 | 无安全 |
| 2 | DES-CBC | ✗ | ✗ | 0 | 已弃用 |
| 3 | DES-CBC | ✗ | ✗ | 0 | 已弃用 |
| 5 | AES-CBC-128 | ✓ | ✗ | 0 | 简单加密，IV≠0 |
| 7 | AES-CBC-128 | ✓ | ✓ | 2/4/8/12/16 | IV=0，需配合 AFL认证 |
| 8 | AES-CTR-128 | ✓ | ✓ | 4+2 | 双 MAC 设计 |
| 9 | AES-GCM-128 | ✓ | ✓ | 12 | 单次加密+认证 |
| 10 | AES-CCM-128 | ✓ | ✓ | 4/8/12/16 | 认证加密，优化开销 |

## Annex F 示例详情

### F.2 - Security Mode 5 示例

- 热费分配器 (HCA) 通过 RF-Adapter
- IV = M-Field + A-Field + Access No (16字节)
- AES-Verify: 2Fh || 2Fh 验证解密正确性

### F.3 - Security Mode 7 示例

- 燃气表 + RF Adapter + Gateway
- 使用 Key Derivation Function A
- Kenc/Kmac 从持久密钥派生
- IV = 0 (静态)
- AFL 提供 CMAC 认证

### F.4 - Security Mode 8 示例

- 双 MAC 设计: MAC_1 和 MAC_2
- MAC_1: 端到端完整性
- MAC_2: 通信伙伴级认证
- 可选 Transmission Time Stamp
- CTR 模式加密

### F.5 - Security Mode 9 示例

- AES-GCM 单次操作实现加密+认证
- IV = Fixed Field (8字节) + Invocation Field (4字节)
- Fixed Field = Manufacturer-ID || ID-No || Version || Device-Type
- Invocation Field = Message Counter

### F.6 - Security Mode 10 示例

- AES-CCM 模式
- Nonce = 13字节
- 认证 Tag 可选 4/8/12/16字节
- 无需填充字节

## F.7 特殊消息示例

- SND-IR: 安装请求消息
- CNF-IR: 安装确认消息
- SND-UD with acknowledge: 带确认的命令传输
- REQ-UD2: 请求数据
- SND-NKE: 链路复位
- SITP Key Transfer: 密钥传输协议示例
- SITP Secured Application Data: 端到端安全数据传输