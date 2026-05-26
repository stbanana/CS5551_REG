#pragma once


/* 寄存器结构 */

enum
{
    CS5551_REG_OS_CH0     = 0x0U, // 初始值 0x00000000  ADC 通道 0 Offset 设置
    CS5551_REG_GAIN_CH0   = 0x1U, // 初始值 0x02000000  ADC 通道 0 Gain 设置
    CS5551_REG_OS_CH1     = 0x2U, // 初始值 0x00000000  ADC 通道 1 Offset 设置
    CS5551_REG_GAIN_CH1   = 0x3U, // 初始值 0x02000000  ADC 通道 1 Gain 设置
    CS5551_REG_CONV_CONF0 = 0x4U, // 初始值 0x00000000  CONV_CONF00 与 CONV_CONF01 设置寄存器
    CS5551_REG_CONV_CONF1 = 0x5U, // 初始值 0x00000000  CONV_CONF10 与 CONV_CONF11 设置寄存器
    CS5551_REG_SYS_CONF0  = 0x6U, // 初始值 0x00000001  系统设置寄存器 0
    CS5551_REG_SYS_CONF1  = 0x7U, // 初始值 0x00000000  系统设置寄存器 1
    CS5551_REG_SYS_CONF2  = 0x8U, // 初始值 0x00000000  系统设置寄存器 2
    CS5551_REG_D_TARG     = 0x9U, // 初始值 0x3FFFFFFF  增益校准目标寄存器
    CS5551_REG_CONV_DATA  = 0xAU  // 初始值 无  转换数据寄存器
};

typedef struct
{
    union
    {
        uint32_t raw;
        struct
        {
            uint32_t os:32; // Offset 校准值， 默认值 0x00000000
            /*
            0x00000000: 偏差 0
            0x20000000: 偏差 正半量程 (+0.50)
            0x3FFFFFFF: 偏差 正满量程 (+1.00)
            0xE0000000: 偏差 负半量程 (-0.50)
            0xC0000000: 偏差 负满量程 (-1.00)
            */
        } bits;
    } os_ch0;

    union
    {
        uint32_t raw;
        struct
        {
            uint32_t gain:32; // 增益校准值， 默认值 0x02000000
            /*
            0x02000000: Gain = 1.00
            0x03000000: Gain = 1.50
            0x01000000: Gain = 0.5
            0x04000000: Gain = 2.00
            */
        } bits;
    } gain_ch0;

    union
    {
        uint32_t raw;
        struct
        {
            uint32_t os:32;
        } bits;
    } os_ch1;

    union
    {
        uint32_t raw;
        struct
        {
            uint32_t gain:32;
        } bits;
    } gain_ch1;

    union
    {
        uint32_t raw;
        struct
        {
            uint32_t CONV_CONF00:16; // 低16 转换设置 0 默认值 0x0000
            uint32_t CONV_CONF01:16; // 高16 转换设置 1 默认值 0x0000
        } bits;
    } conv_conf0;

    union
    {
        uint32_t raw;
        struct
        {
            uint32_t CONV_CONF10:16; // 低16 转换设置 2 默认值 0x0000
            uint32_t CONV_CONF11:16; // 高16 转换设置 3 默认值 0x0000
        } bits;
    } conv_conf1;

    union
    {
        uint32_t raw;
        struct
        {
            uint32_t RS_V:1; // 复位有效标志
            /*
            0: 上次复位失败，主控 MCU 需要重新进行全局复位
            1: 上次复位成功
            */
            uint32_t ERR_C:1; // ADC 转换错误，此寄存器会在主控 MCU 读取此寄存器后自动清 0
            /*
            0：无错误
            1：ADC 转换错误  未转换完成(SDO 未变为 0)前就被打断 或 ADC 转换结果发生溢出(overflow)
            */
            uint32_t ERR_CKS:1; // SPI 同位或和校验错误，此寄存器会在主控 MCU 读取此寄存器后自动清 0
            /*
            0：无错误
            1：SPI 同位或和校验错误
            */
            uint32_t PW_LV:1; // 芯片电源欠压检测
            /*
            0：无欠压
            1：芯片电源欠压 3V 以下
            */
            uint32_t res0:1;
            uint32_t OT_S:1; // Offset 自校准标志位，此位与 SYS_CONF1 的 SHI 位同步变化
            /*
            0：自校准未进行
            1：自校准正在进行
            */
            uint32_t res1:2;
            uint32_t PHA :8; // ADC 码流相位延时选择
            /*
            0x00:不延时 n：延后n个ADC时钟
            */
            uint32_t CSHIGH_MODE:1; // SPI 片选模式选择
            /*
            0: 关闭 SPI 片选信号可置 1 模式，当芯片处于连续转换模式时,只要 SPI 片选信号置 1，即会退出连续转换模式
            1: 开启 SPI 片选信号可置 1 模式，当连续转换模式时,当 SPI 片选置 1，不会退出连续转换模式。当SPI 片选再度置 0 时，会继续之前的连续转换模式，直到收到停止连续转换模式指令
            */
            uint32_t res2  :5;
            uint32_t CKS_EN:1; // SPI 和校验使能
            /*
            0：关闭
            1：开启
            */
            uint32_t res3  :2;
            uint32_t HBF_EN:1; // Halfband 滤波器开关选择
            /*
            0: 关闭 Halfband 滤波器
            1: 开启 Halfband 滤波器
            */
            uint32_t OGS:1; // 校准寄存器选择
            /*
            0: 由 CONV_CONFx 寄存器中的 CHS 决定
            1: 由 CONV_CONFx 寄存器中的 OGSEL 决定
            */
            uint32_t res4  :4;
            uint32_t RS_SYS:1; // 系统全局复位(不包含 SPI 接口部分)，此位被写 1 之后，会进行系统全局复位，此位会在 10 ms 后自动清 0。
            /*
            写入 0: 无效果
            写入 1: 开始全局复位
            读取 0: 全局复位已完成
            读取 1: 全局复位进行中
            */

        } bits;
    } sys_conf0;

    union
    {
        uint32_t raw;
        struct
        {
            uint32_t res0   :4;
            uint32_t CKMODE0:1; // 需配置为 1
            uint32_t CKMODE1:1; // 在 51.2kHz 的码率设置时，不管发起的是单次转换还是连续转换模式，该位必须配置为 1.如果发起的是单次转换模式，800Hz 以上的码率设置时，该位也必须配置为 1

            uint32_t IDT    :2; // 仪表放大器的电流消耗设置。在需要降低功耗的应用场合可配置此寄存器为 01 或 10。
            /*
            00: 默认功耗
            01: -33%
            10: -50%
            11: -60%
            */
            uint32_t ADITA:2; // ADC 电路 A 部分的电流消耗设置，正常情况下需设置为 10。在需要降低功耗的应用场合，可在降 低 ADC 工作频率的基础上（见 SYS_CONF2），配置此寄存器为 01。
            /*
            00: 默认功耗
            01: -50%
            10: +50%
            11: 禁止
            */
            uint32_t ADITB:2; // ADC 电路 B 部分的电流消耗设置，正常情况下需设置为 10。在需要降低功耗的应用场合，可在降 低 ADC 工作频率的基础上（见 SYS_CONF2），配置此寄存器为 01。
            /*
            00: 默认功耗
            01: -50%
            10: +50%
            11: 禁止
            */
            uint32_t res1     :3;
            uint32_t GAIN_MODE:1; // 当 ADC 增益选择为小于等于 16 倍时，需将此 BIT 置’1’，大于 16 倍时为默认的’0’

            uint32_t ADCPDN   :1; // ADC 模拟模块使能，上电后主控 MCU 需设置该 BIT 为’1’以打开 ADC
            /*
            读取 0: ADC 已关闭
            读取 1: ADC 已使能
            写入 0: 无作用
            写入 1: 使能 ADC
            */
            uint32_t TMPPDN:1; // 温度传感器使能，此寄存器在开始 ADC 转换时，会自动更新为 CONV_CONFx 寄存器内的 TMPEN 设定值
            /*
            0: 温度传感器已关闭
            1: 温度传感器已使能
            */
            uint32_t res2:2;
            uint32_t GA  :3; //ADC 增益选择，此寄存器在开始 ADC 转换时，会自动更新为 CONV_CONFx 寄存器内的 GA 设定 值
            /*
            0x0: x64
            0x1: x128
            0x2: x16
            0x3: x32
            0x4: x4
            0x5: x8
            0x6: x1
            0x7: x2
            */
            uint32_t res3:1;
            uint32_t OD  :1; //ADC 开路检测选择，此寄存器在开始 ADC 转换时，会自动更新为 CONV_CONFx 寄存器内的 OD设定值
            uint32_t CHS :1; //ADC 通道选择，此寄存器在开始 ADC 转换时，会自动更新为 CONV_CONFx 寄存器内的 CHS 设定值
            /*
            0: 选择 ADC 通道 0
            1: 选择 ADC 通道 1
            */
            uint32_t res4:1;
            uint32_t VRS :1; // ADC 基准源选择
            /*
            0:使用外部基准源，VREF+和 VREF-为基准源输入
            1:使用内部 BGP 电路作为基准源，基准电压约 1.2V，典型温度系数 10ppm/℃，从 VREF+和VREF-引脚输出。外部 VREF+和 VREF-之间需加 1 个 1uF 去耦电容。
            */
            uint32_t SHI:1; //输入信号短路，该 BIT 与 SYS_CONF0 里的 OT_S 同步变化
            /*
            读取 0: 内部短路功能已关闭
            读取 1: 内部短路已使能
            写入 0: 无作用
            写入 1: 强制使能内部短路
            */
            uint32_t FR_SEL:1; // 频率模式选择
            /*
            0: 50Hz 模式，对应 ADC 时钟 819.2kHz（系统频率除以 6）
            1: 60Hz 模式，对应 ADC 时钟 983.04kHz（系统频率除以 5）
            */
            uint32_t POWD:1; // 低功耗模式选择
            /*
            0: 正常模式
            1: 低功耗模式，此模式下芯片功耗小于 1uA
            */
            uint32_t RCHPDN:1; // 内部高频 RC 时钟开关，此寄存器受晶体时钟监测结果控制，如果监测到连续 200ms 没有晶体时 钟，则将自动将此寄存器置 1，打开 RCH 时钟并将系统时钟切换至 RCH。
            /*
            读取 0: RCH 模块已被关闭
            读取 1：RCH 模块已被打开
            写入 0: 无作用
            写入 1: 强制打开 RCH 模块，但是并不会将系统时钟切换到 RCH
            */
        } bits;
    } sys_conf1;

    union
    {
        uint32_t raw;
        struct
        {
            uint32_t res0   :6;
            uint32_t VCMTRIM:1; // 输入信号共模电压调节
            /*
            0: 默认值
            1: 调节输入信号共模电压，在输入信号共模低于 0.5V 时配置为’1’
            */
            uint32_t res1  :1;
            uint32_t RCTRIM:4; // 高频 RC 时钟的频率调节。
            /*
            芯片内部 RCH 时钟在-40~85 度范围内随温度的频率变化小于 1%，但芯片之间的 RCH 频率存在固
            有偏差。如系统应用在无晶体的场合，且希望 RCH 频率精度较高时，需要 MCU 做额外校正，校正
            值配置到此寄存器。有晶体的应用场合则无需配置此寄存器。
            0000:默认值; 0001:-2.5%;
            0010: -5%; 0011: -7.5%;
            0100: -10%; 0101: -12.5%;
            0110: -15%; 0111: -17.5%
            1000: +20%; 1001: +17.5%;
            1010: +15%; 1011: +12.5%;
            1100: +10%; 1101: +7.5%;
            1110: +5%; 1111: +2.5%
            */
            uint32_t BGP_MODE:1; // 内部基准电压源(BGP)的模式，在使用内部 BGP 作为 ADC 基准源时，建议配置为 1
            /*
            0:默认模式
            1:低 offset 模式
            */
            uint32_t res2 :3;
            uint32_t DMODE:2; // DMODE 设置
            /*
            在资料率 DR 设置为 400Hz 及以下时，建议配置为’10’；DR 在 400Hz~6.4kHz
            时，配置为’00’;DR 在 12.8kHz 及以上时，配置为’11’。
            00:12.8k; 01:6.4k;10:800; 11:无
            */
            uint32_t res3   :2;
            uint32_t REFTRIM:3; // 内部基准电压源(BGP)的温度系数调节
            /*
            000:默认值;
            001:+10ppm/℃;
            010:+20ppm/℃;
            011:+30ppm/℃;
            100:+30ppm/℃;
            101:-30ppm/℃; (建议设定值)
            110:-20ppm/℃;
            111:-10ppm/℃
            */
            uint32_t res4     :6;
            uint32_t REFTRIM_L:1; // 内部基准电压源(BGP)的温度系数调节
            /*
            0: 默认值
            1: +45ppm/℃
            */
            uint32_t res5    :1;
            uint32_t ADCKDIV2:1; // ADC 工作频率选择，正常情况下采用默认值即可。
            /*
            该 BIT 设 1 后，CONV_CONFx 寄存器里 DR 所
            对应的 ADC 数据率也会相应除以 2。在 ADC 精度足够，但功耗更为敏感的应用领域，可将该 BIT
            设为 1 后，再将 ADITA<1:0>设置为 01，以及 IDT<1:0>设置为 10，以降低芯片功耗。此时 ADC
            的 ENOB 将下降约 1BIT。
            0: 819.2kHz (50Hz 模式下，60Hz 模式下则乘 1.2)
            1: 409.6kHz
            */

        } bits;
    } sys_conf2;

    union
    {
        uint32_t raw;
        struct
        {
            uint32_t D_TARG:32; // 系统 Gain 校准之 ADC 期望值
            /*
            0x20000000: 正半量程 (+0.50)
            0x3FFFFFFF: 正满量程 (+1.00)
            0xE0000000: 负半量程 (-0.50)
            0xC0000000: 负满量程 (-1.00)
            */
        } bits;
    } d_targ;

    union
    {
        uint32_t raw;
        struct
        {
            uint32_t DATA:31; // ADC 转换结果
            /*
            bit[31:1]，bit[0]为当次数据所的信号信道。bit[31:1]为
            31 位有符号补码，高 2 位为符号位，将 bit[0]补 0 后，bit [31:0]的结果:
            0x20000000: 正半量程 (+0.50)
            0x3FFFFFFF: 正满量程 (+1.00)
            0xE0000000: 负半量程 (-0.50)
            0xC0000000: 负满量程 (-1.00)
            */
            uint32_t CHL:1; // 表示该次转换的通道选择
            /*
            0: 该次转换为通道 0
            1: 该次转换为通道 1
            */
        } bits;
    } conv_data; // 只读
} cs5551_reg_map_t;

extern cs5551_reg_map_t CS5551_Regs;

