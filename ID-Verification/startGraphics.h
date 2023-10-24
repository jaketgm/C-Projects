void printCenteredLine(const char *text, int width, char border);

/************************************************************************************
 * Method: startGraphics: Creates a nice starting visual :)
 *
 * Input: None.
 *
 * Output: Starting Graphic Message.
 *
************************************************************************************/
void startGraphics() 
{
    system("clear"); // Clears the screen
    int width = 40;
    char border = '*';

    printf("****************************************\n");
    printCenteredLine("", width, border);
    printCenteredLine("WELCOME", width, border);
    printCenteredLine("TO", width, border);
    printCenteredLine("ID Verification!!", width, border);
    printCenteredLine("", width, border);
    printf("****************************************");
}

/************************************************************************************
 * Method: printCenteredLine: Perfectly alligns the text for the starting
 * graphic.
 *
 * Input: const char *text, int width, char border.
 *
 * Output: Alligned Text.
 *
************************************************************************************/
void printCenteredLine(const char *text, int width, char border) 
{
    int padding = (width - strlen(text) - 2) / 2;
    printf("%c%*s%-*s%c\n", border, padding, "", width - padding - 2, text, border);
}