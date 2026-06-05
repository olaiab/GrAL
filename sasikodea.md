#### Sasikodea

##### Botoiak: funtzioak deitu

``` C
Interrupzioak() //EXTI0_IRQHandler edo BSP
{
    if (botoia sakatuta) // rising edge
    {
        noizsakatu = HAL_GetTick();
        sakatutadago = 1;
    }

    else (botoia askatuta) // falling edge
    {
        if ((HAL_GetTick() - noizsakatu) < muga)
        {
            B2FLAG = 2;
        }
        
        sakatutadago = 0;
    }
}
// Botoia sakatu / mantendu 
// https://community.st.com/t5/stm32-mcus-products/detecting-long-button-press-on-stm32f3/td-p/353527
// https://stackoverflow.com/questions/25932299/stm32-rising-and-falling-button-interrupt-detection
// https://hackmd.io/28DLa48-QDO7-urGPrRLLw

main()
{
    ...
    while(1)
    {
        ...
        if (sakatutadago && B2FLAG == 0) // sakatuta dago eta ez da motza izan
        {
            if ((HAL_GetTick() - noizsakatu) > muga)
            {
                B2FLAG = 1;
            }
        }
        if (B2FLAG == 1) // Botoia mantendu
        {
            B2FLAG = 0;
            B2Mantendu();
        }

        if (B2FLAG == 2) // Botoia sakatu
        {
            B2FLAG = 0;
            B2Sakatu();
        }
    }
}
```

##### Botoiak: errutinak

```C
// global.h 

#ifndef GLOBAL_H
#define GLOBAL_H

// Egoerak
typedef enum{
    IDLE = 0,
    ENTRENA,
    PAUSA,
    GORDE
} egoerak;

extern volatile egoerak egoera;

// Datuak gordetzeko (pausa -> berrezarri)
typedef struct{
    uint32_t denbora_ms;
    float distantzia_m;
    float bb_abiadura_km;
    float split_s
    int paladak;
    uint8_t geldi;
} SesioDatuak;

extern SesioDatuak sesioa;

// Flag-ak
extern volatile uint8_t B2FLAG;
extern volatile uint8_t B3FLAG;

#endif

// botoiak.c

#include "global.h"

void B2Sakatu()
{
    match (egoera)
    {
        case IDLE:
            entrena_hasi();
            egoera = ENTRENA;
            break;
        case ENTRENA:
            entrena_pausa();
            egoera = PAUSA;
            break;
        case PAUSA:
            entrena(sesioa);
            egoera = ENTRENA;
            break;
        case GORDE:
            entrena_gorde();
            egoera = IDLE;
            break;
        default:
            break;
    }
}

void B2Mantendu()
{
    match (egoera)
    {
        case PAUSA:
            gorde_pantaila();
            egoera = GORDE;
            break;
        default:
            break;
    }
}


// adbz, entrenamendua.c
void entrena_hasi()
{
    Kronoa_martxan();
    GPS_martxan();
    Azel_martxan();

    sesioa.denbora_ms = 0;
    sesioa.distantzia_m = 0;
    sesioa.bb_abiadura_km = 0;
    sesioa.split_s = 0;
    sesioa.geldi = 0;
}
```

##### Beharrezko funtzioak, nun jarri eta zertarako

- **GPS**
  - GPS_Init(): main, GPSa hasieratzeko.
  - GPS_Receive(): UART-en etenen kontroladorean, lerro bat jaso bakoitzean tratatzeko.
  - fs: 10Hz

- **Azelerometroa**
  - AZ_Init(): main, hasieratzeko.
  - AZ_Datua(): erlojuaren etenetan? azelerometroari datuak eskatzeko frekuentzia zehatz batean + datuak tratatu paladak detektatzeko
  - fs: 50Hz 100Hz 

- **Kronoa**
  - CR_Init()
  - CR_Update(): erlojuaren etenetan
  
- **Pantaila**
  - Disp_Init()
  - Disp_Update(): eztakit nun, baino segunduro