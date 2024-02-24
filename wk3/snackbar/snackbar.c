// Practice using structs
// Practice writing a linear search function

/**
 * Beach Burger Shack has the following 10 items on their menu
 * Burger: $9.5
 * Vegan Burger: $11
 * Hot Dog: $5
 * Cheese Dog: $7
 * Fries: $5
 * Cheese Fries: $6
 * Cold Pressed Juice: $7
 * Cold Brew: $3
 * Water: $2
 * Soda: $2
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "cs50.h"

// Number of menu items
// Adjust this value (10) to number of items input below
#define NUM_ITEMS 10
// Line length of the longest menu item
#define LINE_LENGTH 30

// Menu itmes have item name and price
typedef struct
{
    string item;
    float price;
} menu_item;

// Array of menu items
menu_item menu[NUM_ITEMS];

// Add items to menu
int add_items(void);

// Calculate total cost
float get_cost(string item);

int main(void)
{
    add_items();

    printf("\nWelcome to Beach Burger Shack!\n");
    printf("Choose from the following menu to order. Press enter when done.\n\n");

    for (int i = 0; i < NUM_ITEMS; i++)
    {
        printf("%s: $%.2f\n", menu[i].item, menu[i].price);
    }
    printf("\n");

    float total = 0;
    while (true)
    {
        string item = get_string("Enter a food item: ");
        if (strlen(item) == 0)
        {
            printf("\n");
            break;
        }

        total += get_cost(item);
    }

    printf("Your total cost is: $%.2f\n", total);

    for (int i = 0; i < NUM_ITEMS; i++)
    {
        free(menu[i].item);
    }
}

// Add at least the first four items to the menu array
int add_items(void)
{
    /**
     * Beach Burger Shack has the following 10 items on their menu
     * Burger: $9.5
     * Vegan Burger: $11
     * Hot Dog: $5
     * Cheese Dog: $7
     * Fries: $5
     * Cheese Fries: $6
     * Cold Pressed Juice: $7
     * Cold Brew: $3
     * Water: $2
     * Soda: $2
     */
    FILE *full_menu = fopen("menu.md", "r");
    if (!full_menu)
        return 1;

    // FIXME this is where I left off.
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        char file_line[LINE_LENGTH];
        fgets(file_line, LINE_LENGTH, full_menu);
        char *char_to_find = strchr(file_line, ':');
        if (char_to_find != NULL)
        {
            int menu_item_length = char_to_find - file_line;
            menu[i].item = malloc((menu_item_length + 1) * sizeof(char));
            strncpy(menu[i].item, file_line, menu_item_length);
            menu[i].item[menu_item_length] = '\0';
        }

        // Code from ddb to copy a substring
        /* char *ptr = strchr(original_string, 'character_to_find'); */
        /* if (ptr != NULL) { */
        /*     int length = ptr - original_string; */
        /*     char substring[length + 1]; */
        /*     strncpy(substring, original_string, length); */
        /*     substring[length] = '\0'; */
        /* } */

        char *price = strstr(file_line, "$");
        price++;
        menu[i].price = atof(price);
    }

    fclose(full_menu);
    return 0;
}

// Search through the menu array to find an item's cost
float get_cost(string item)
{
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        if (!strcasecmp(item, menu[i].item))
        {
            return menu[i].price;
        }
    }
    return 0.0;
}
