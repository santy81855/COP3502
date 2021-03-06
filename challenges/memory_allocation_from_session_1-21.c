#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Chair
{
    char *color;
} Chair;

typedef struct Classroom
{
    Chair **chairs;
} Classroom;

int main()
{
    // Create a classroom pointer that can store n chairs. Use scanf to ask the user what n is.
    int n;
    printf("How many chairs?\n");
    scanf("%d", &n);

    // Declare the classroom struct pointer and allocate 1 classroom struct into it
    Classroom *cb1;
    cb1 = (Classroom *)calloc(1, sizeof(Classroom));

    // Now that we have allocated a classroom struct, we have access to the chairs variable inside
    // Since chairs is a double pointer, we need to allocate n chair pointers into it
    cb1->chairs = (Chair **)malloc(sizeof(Chair *) * n);

    // We now have n chair pointers stores inside of cb1->chairs
    // We can access each chair pointer by using the brackets, so cb1->chairs[0], cb1->chairs[1], ... , cb1->chairs[n-1]

    // Since we have n chair pointers, we have to allocate 1 chair struct into each of those chair pointers
    // We can use a for loop to easily access each chair pointer
    for (int i = 0; i < n; i++)
        cb1->chairs[i] = (Chair *)calloc(1, sizeof(Chair));

    // Now that each chair pointer has been allocated a chair struct, we can access the color variable inside of each chair
    // But since color is a pointer itself, we have to allocate enough space to store the array of characters that is a color
    // Again, we can use a for loop to access each chair and allocate 21 chars so that we can store a 20 letter color at most.
    for (int i = 0; i < n; i++)
        cb1->chairs[i]->color = (char *)calloc(21, sizeof(char));
    /* Notice that we used the arrow to access the color because chairs is a double pointer, so we:
        -dereference it once with the brackets
        -dereference it a second time with the arrow to get to the values inside

        If chairs had been a single pointer, we would access colors as such:
            cb1->chairs[i].color

            The reason being that we woud only need to dereference it once since it would be a single pointer
     */
    // Now we can add a color to each chair by asking the user to input the colors
    printf("Enter the color of each of the %d chairs\n", n);
    for (int i = 0; i < n; i++)
        scanf("%s", cb1->chairs[i]->color);

    // Now let's print all of the chairs colors inside of our classroom
    for (int i = 0; i < n; i++)
        printf("Chair color 1: %s\n", cb1->chairs[i]->color);

    // The last thing left for us to do is to free all of the memory we used
    // We have to free in the reverse order that we allocated in.
    /* 
    The reason for this is that if we were to free in the same order that we allocated in, the first thing
    that we would free would be the classroom. If we freed the classroom first, we would immeadiately lose
    all access to all of the chairs inside before we could free them, and that would cause a memory leak
    */
    // First we free each color from each chair using the same exact method that we used to allocate each color
    for (int i = 0; i < n; i++)
        free(cb1->chairs[i]->color);

    // Then we free each chair pointer one by one using the same method that we used to allocate them
    for (int i = 0; i < n; i++)
        free(cb1->chairs[i]);

    // Then we free our array of chair pointers using the same method we used to allocate them
    free(cb1->chairs);

    // And lastly, we free the classroom pointer
    free(cb1);

    /*
    Now for some normal talk, we will just conceptually explain what we did in this code:

    We have a single classroom. We could have made it static (not a pointer), but we made it a pointer
    so that we could get some practice allocating. Inside of a classroom struct we have a double pointer
    of the Chair struct. This represents that we can have multiple chairs (an array) inside of each classroom.
    This could have been a single pointer and it would have worked out just as well, but we wanted it to be 
    more similar to the HW1 assignment, which involves a double pointer inside of a struct.

    Since we made it a double pointer, we have 2 allocations to take care of. The first one is where we make an 
    array of single chair pointers, and then the second one is where we allocate a single chair struct into each of those
    chair pointers that we created. As an aside, we could have given each of our n chair pointers enough space to store 
    multiple chairs themselves, which could potentially be useful for other programs, but in this one we just needed n 
    chairs total.

    Once we allocated all of the chair struct pointers to be able to store a single chair struct inside, we then had to 
    allocate enough memory to store each color as a character array inside of each chair struct. The reason we had to 
    do this was because we made the color variable inside of the chair struct a pointer. We could have made it static 
    like this: color[21]
    That would have made it so we would not have to allocate memory for each color inside of each chair, but again, we 
    did it this way to get more practice for the tricky homework assignments.
    */
    return 0;
}