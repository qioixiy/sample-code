/**
 * url: http://blog.csdn.net/bailyzheng/article/details/11883591
 */

void WriteByte(u8_t dat)
{
    u8_t i;
    for(i=0;i<8;i++)
    {
        SCKN = 0;
        asm("nop");
        if(dat&0x80)
        {
            SIN = 1;
        }
        else
            SIN = 0;
        dat <<= 1;
        asm("nop");
        SCKN = 1;
        asm("nop");
    }
    SCKN=0; //空闲状态为低电平
}

u8_t ReadByte(void)
{
    u8_t i,dat;
    SCKN=0;
    dat1=0;
    for(i=0;i<8;i++)
    {
        SCKN=1;
        dat1 <<=1;
        dat1 |= SON;
        SCKN=0;
    }
    return dat;
}
