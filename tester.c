#include <stdio.h>
#include <cs50.h>



int main(void)
{
    int input[3][3][3] = {{{ 0,10,25}, { 0,10,30}, {40,60,80}},
                          {{20,30,90}, {30,40,100},{80,70,90}},
                          {{20,20,40}, {30,10,30}, {50,40,10}}};
    RGBTRIPLE finalinput[3][3];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            RGBTRIPLE temp;
            temp.rgbtRed = input[i][j][0];
            temp.rgbtBlue = input[i][j][1];
            temp.rgbtGreen = input[i][j][2];
            finalinput[i][j] = temp;
        }
    }
    edges(3, 3, finalinput);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            
        }
    }
}
