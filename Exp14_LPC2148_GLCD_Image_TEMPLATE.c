
#include <LPC214x.h>

#define DATA_MASK  0x00FF0000
#define EN         (1 << 10)
#define RW         (1 << 11)
#define RS         (1 << 25)
#define CS1        (1 << 26)
#define CS2        (1 << 27)
#define RESET      (1 << 24)

unsigned char screen[1024];

void delay(unsigned int t)
{
    unsigned int i, j;
    for(i = 0; i < t; i++)
        for(j = 0; j < 50; j++);
}

void strobe(void)
{
    IO0SET = EN;
    delay(5);
    IO0CLR = EN;
    delay(5);
}

void select_left(void)
{
    IO1SET = CS1;
    IO1CLR = CS2;
}

void select_right(void)
{
    IO1CLR = CS1;
    IO1SET = CS2;
}

void glcd_cmd(unsigned char cmd)
{
    IO1CLR = DATA_MASK | RS;
    IO1SET = ((unsigned int)cmd << 16);
    IO0CLR = RW;
    strobe();
}

void glcd_data(unsigned char data)
{
    IO1CLR = DATA_MASK;
    IO1SET = ((unsigned int)data << 16);
    IO1SET = RS;
    IO0CLR = RW;
    strobe();
}

void glcd_init(void)
{
    PINSEL0 &= ~((3 << 20) | (3 << 22));
    PINSEL2 = 0;

    IODIR0 |= EN | RW;
    IODIR1 |= DATA_MASK | RS | CS1 | CS2 | RESET;

    IO0CLR = EN | RW;

    IO1CLR = DATA_MASK | RS | RESET;
    delay(100);

    IO1SET = RESET;
    delay(100);

    select_left();
    glcd_cmd(0x3F);
    glcd_cmd(0xC0);

    select_right();
    glcd_cmd(0x3F);
    glcd_cmd(0xC0);
}

void set_pixel(unsigned int x, unsigned int y)
{
    unsigned int index;

    if(x >= 128 || y >= 64)
        return;

    index = (y / 8) * 128 + x;

    screen[index] |= (1 << (y % 8));
}

void draw_smiley(void)
{
    int x, y;
    int dx, dy;
    int d;

    /* Draw outer circle */
    for(y = 10; y <= 54; y++)
    {
        for(x = 42; x <= 86; x++)
        {
            dx = x - 64;
            dy = y - 32;
            d = dx * dx + dy * dy;

            if(d >= 430 && d <= 510)
                set_pixel(x, y);
        }
    }

    /* Left eye */
    for(y = 23; y <= 27; y++)
        for(x = 54; x <= 58; x++)
        {
            dx = x - 56;
            dy = y - 25;

            if(dx * dx + dy * dy <= 4)
                set_pixel(x, y);
        }

    /* Right eye */
    for(y = 23; y <= 27; y++)
        for(x = 70; x <= 74; x++)
        {
            dx = x - 72;
            dy = y - 25;

            if(dx * dx + dy * dy <= 4)
                set_pixel(x, y);
        }

    /* Smile */
    for(x = 55; x <= 73; x++)
    {
        dx = x - 64;
        y = 35 + (dx * dx) / 20;
        set_pixel(x, y);
    }
}

void display_screen(void)
{
    unsigned int page, col;

    for(page = 0; page < 8; page++)
    {
        select_left();

        glcd_cmd(0xB8 | page);
        glcd_cmd(0x40);

        for(col = 0; col < 64; col++)
            glcd_data(screen[page * 128 + col]);

        select_right();

        glcd_cmd(0xB8 | page);
        glcd_cmd(0x40);

        for(col = 64; col < 128; col++)
            glcd_data(screen[page * 128 + col]);
    }
}

int main(void)
{
    unsigned int i;

    glcd_init();

    for(i = 0; i < 1024; i++)
        screen[i] = 0x00;

    draw_smiley();
    display_screen();

    while(1);
}
