# 控制组STM32培训3 —— Timer
---
# 一、 Systick定时器
## 1. 简介
`Cortex‐M3`处理器内部包含了一个简单的定时器。因为所有的CM3芯片都带有这个定时器，软件在不同CM3器件间的移植工作得以化简。该定时器的时钟源可以是内部时钟，或者是外部时钟。不过，STCLK的具体来源则由芯片设计者决定，因此不同产品之间的时钟频率可能会大不相同，你需要查找芯片的器件手册来决定选择什么作为时钟源。`Cortex-M3`的内核中包含一个 SysTick 时钟。SysTick 为一个 24 位递减计数器，SysTick 设定初值并使能后，每经过 1 个系统时钟周期，计数值就减 1。计数到 0 时，SysTick 计数器自动重装初值并继续计数，同时内部的 COUNTFLAG 标志会置位，触发中断 (如果中断使能情况下)。

---

## 2. Systick中寄存器
|名称|地址|类型|
|:--:|:--:|:--:|
|STK_CTRL|0xE000E010|控制寄存器|	
|STK_LOAD|0xE000E014|重载寄存器|	
|STK_VAL|0xE000E018|当前值寄存器|	
|STK_CALRB|0xE000E01C|校准值寄存器|

---
### 2.1 STK_CTRL控制寄存器
![40%](/Users/hunto/Downloads/图片%201.png)
* 第0位：ENABLE，Systick 使能位  
`0`:关闭Systick功能； `1`:开启Systick功能	
* 第1位：TICKINT，Systick 中断使能位
`0`:关闭Systick中断；`1`:开启Systick中断
* 第2位：CLKSOURCE，Systick时钟源选择
`0`:使用HCLK/8 作为Systick时钟；
`1`:使用HCLK作为Systick时钟	
* 第16位：COUNTFLAG，Systick计数比较标志，如果在上次读取本寄存器后，SysTick 已经数到了0，则该位为1。如果读取该位，该位将自动清零

---

### 2.2 STK_LOAD重载寄存器
![40%](/Users/hunto/Downloads/图片%202.png)
Systick是一个递减的定时器，当定时器递减至0时，重载寄存器中的值就会被重装载，继续开始递减。STK_LOAD  重载寄存器是个24位的寄存器最大计数0xFFFFFF。

### 2.3 STK_VAL当前值寄存器
![40%](/Users/hunto/Downloads/图片%203.png)
也是个24位的寄存器，读取时返回当前倒计数的值，写它则使之清零，同时还会清除在SysTick 控制及状态寄存器中的COUNTFLAG 标志。

---

## 3. 使用Systick实现延时功能
* Systick初始化
  ```C
  u32 fac_us;  // 延时1ns需要的滴答次数
  u16 fac_ms;  // 延时1ms需要的滴答次数
  void delay_init()
  {
      /* 选择外部时钟  HCLK/8 */
      SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	
      /* 外部时钟为系统时钟的1/8 （8M晶振，CPU频率72M） */
      fac_us = SystemCoreClock / 8000000;	
      fac_ms = (u16)fac_us*1000;
  }	
  ```
---

* 延时函数
  ```C
  void delay_us(u32 nus)
  {		
      u32 temp;	    	 
      SysTick->LOAD = nus*fac_us; // 加载计数	  		 
      SysTick->VAL = 0x00; // 清空计数器
      SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ; // 开始倒数
      do
      {
          temp = SysTick->CTRL;
      }while((temp & 0x01) && 
             !(temp & (1 << 16)));	// 等待时间到达 
      SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;	// 关闭计数器
      SysTick->VAL = 0X00;  // 清空计数器	 
  }
  ```
  
---
  ```C
  void delay_ms(u16 nms)
  {	 		  	  
      u32 temp;		   
      SysTick->LOAD=(u32)nms*fac_ms;				
      SysTick->VAL =0x00;						
      SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;
      do
      {
          temp=SysTick->CTRL;
      }while((temp&0x01)&&!(temp&(1<<16)));		  
      SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	
      SysTick->VAL =0X00;       				 	    
  } 
  ```
