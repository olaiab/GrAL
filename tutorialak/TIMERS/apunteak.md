#### TIMER
- Zer da timer bat?
Plakaren elementu bat zerbait gertatzen den bakoitzeko zenbatzen duena (tick-ak).
- Zenbateko erresoluzioa dauka? X bit. Zenbateraino zenbatu daiteke orduan?
TIM1/TIM16/TIM17 16b (p710)
TIM2 32b (p810)
- Zer da preskalerra? Zenbat ms/s zenbatu ditzaket orduan timer bakarra erabilita?
A prescaler is an electronic counting circuit used to reduce a high-frequency signal to a lower, more manageable frequency through integer division. The prescaler takes the basic timer clock frequency (which may be the CPU clock frequency or may be some higher or lower frequency) and divides it by some value before feeding it to the timer, according to how the prescaler register(s) are configured.
TIM1: the prescaler can divide the counter clock frequency by any factor between 1 and 65536. It is based on a 16-bit counter controlled through a 16-bit register (in the TIMx_PSC register). It can be changed on the fly as this control register is buffered. The new prescaler ratio is taken into account at the next update event. PSC value
Figure 129 and Figure 130 give some examples of the counter behavior when the prescaler ratio is changed on the fly.

#### Plakako ezaugarriak
- **Clocks 7.2**
  - HSI16 16MHz RC oscillator clock
  - MSI RC oscillator clock from 100kHz to 48 MHz
  - HSE32 32MHz oscillator clock, with trimming capacitors.
  - Several prescalers can be used to configure the AHB frequencies (HCLK3/PCLK3, HCLK1, HCLK2), the high-speed APB2 (PCLK2) and the low-speed APB1 (PCLK1) domains. The maximum frequency of the AHB (HCLK3, HCLK1 and HCLK2), and the PCLK1 and the PCLK2 domains is 48 MHz.
  - Figure 27. Clock tree
    - PCLK1 to:
      - APB1
      - x1 or x2 →APB1 TIMx
    - PCLK2 to:
      - APB2
      - x1 or x2 →APB2 TIMx
  - Table 4. Memory map and peripheral register boundary addresses:
    - APB1: TIM2
    - APB2: TIM1, TIM16, TIM17 

|  bus |       timer      | timer f | timer bit | max count | denbora max seg | preskaler bit | denbora max psc seg |
|:----:|:----------------:|---------|-----------|-----------|-----------------|---------------|---------------------|
| APB1 |       TIM2       | 48MHz   | 32        | 2³²-1     | 89,45           | 16            | 5864062.015         |
| ABP2 | TIM1 TIM16 TIM17 | 48MHz   | 16        | 2¹⁶-1     | 0,001365        | 16            | 89.47848533         |

- Denbora max: Tmax = (maxcount+1)/f
- Denbora max prescaler = (maxcount+1)*(psc+1)/f
- fpresk = f/(PSC+1)

- **Adibidea**
  - PSC = 4799 
  - ARR = 1999
  - fprescalated = 48MHz / (4799+1) = 1kHz
  - Tprescalated = 1/1kHz = 1ms
  - Ttick = 1ms * (1999+1) = 2s

#### Erregistroak (TIM17)
```C
RCC   0x58000000 //p74
    RCC_APB1ENR RCC+0x060 //p328

TIM17 0x40014800 //p75
    TIM17_PSC   TIM17+0x28 //p922
    TIM17_ARR   TIM17+0x2C //p922
    TIM17_CR1   TIM17+0x00 //p911
    TIM17_DIER  TIM17+0x0C //p913
    TIM17_EGR   TIM17+0x14 //p915
    TIM17_SR    TIM17+0x10 //p914
```