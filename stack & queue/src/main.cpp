#include "raylib.h"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

#define MAX 10  

// Stack class
class Stack {
private:
    int* arr;
    int top;
    int maxSize;

public:
    Stack() {
        maxSize = MAX;
        arr = new int[maxSize];
        top = -1;
    }

    ~Stack() {
        delete[] arr;
    }

    void push(int value) {
        if (isFull()) {
            cout << "Stack Overflow! Cannot push " << value << endl;
            return;
        }
        arr[++top] = value;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow! No elements to pop." << endl;
            return -1;
        }
        return arr[top--];
    }

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == maxSize - 1;
    }

    int getTop() {
        return top;
    }

    int getElement(int index) {
        return arr[index];
    }

    // Reverse the stack
    void reverseStack() {
        int temp[MAX];
        int currentTop = top;

        // Pop elements into the temp array
        for (int i = 0; i <= currentTop; i++) {
            temp[i] = pop();
        }

        // Push elements back into the stack from the temp array
        for (int i = 0; i <= currentTop; i++) {
            push(temp[i]);
        }
    }
};

// Queue class
class Queue {
private:
    int* arr;
    int front;
    int rear;
    int maxSize;
    int count;

public:
    Queue() {
        maxSize = MAX;
        arr = new int[maxSize];
        front = 0;
        rear = -1;
        count = 0;
    }

    ~Queue() {
        delete[] arr;
    }

    void enqueue(int value) {
        if (isFull()) {
            cout << "Queue Overflow! Cannot enqueue " << value << endl;
            return;
        }
        rear = (rear + 1) % maxSize;
        arr[rear] = value;
        count++;
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow! No elements to dequeue." << endl;
            return -1;
        }
        int value = arr[front];
        front = (front + 1) % maxSize;
        count--;
        return value;
    }

    bool isEmpty() {
        return count == 0;
    }

    bool isFull() {
        return count == maxSize;
    }

    int getElement(int index) {
        return arr[(front + index) % maxSize];
    }

    int getCount() {
        return count;
    }

    // Reverse the queue
    void reverseQueue() {
        Stack tempStack;

        // Dequeue all elements and push to the stack
        while (!isEmpty()) {
            tempStack.push(dequeue());
        }

        // Push elements from the stack back to the queue
        while (!tempStack.isEmpty()) {
            enqueue(tempStack.pop());
        }
    }
};

// Main function
int main() {
    // Initialize stack and queue
    Stack stack;
    Queue queue;

    // Initialize Raylib window
    const int screenWidth = 800;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Stack and Queue Visualizer");

    SetTargetFPS(60);

    // Variables for handling user input
    char inputText[10] = "";
    int inputLength = 0;

    // Main game loop
    while (!WindowShouldClose()) {
        // Handle user input
        if (IsKeyPressed(KEY_BACKSPACE) && inputLength > 0) {
            inputText[--inputLength] = '\0';
        }

        int key = GetKeyPressed();
        if (key >= KEY_ZERO && key <= KEY_NINE && inputLength < 9) {
            inputText[inputLength++] = (char)key;
            inputText[inputLength] = '\0';
        }

        if (IsKeyPressed(KEY_ENTER) && inputLength > 0) {
            int value = atoi(inputText);
            stack.push(value);  // Push to stack
            queue.enqueue(value);  // Enqueue to queue
            inputLength = 0;
            inputText[0] = '\0';
        }

        if (IsKeyPressed(KEY_DOWN)) {
            stack.pop();  // Pop from stack
            queue.dequeue();  // Dequeue from queue
        }

        // Reverse the stack when the user presses 'S'
        if (IsKeyPressed(KEY_S)) {
            stack.reverseStack();  // Reverse the stack
        }

        // Reverse the queue when the user presses 'Q'
        if (IsKeyPressed(KEY_Q)) {
            queue.reverseQueue();  // Reverse the queue
        }

        // Drawing
        BeginDrawing();
        ClearBackground(DARKGRAY);

        DrawText("Type a number and press ENTER to push/enqueue, DOWN to pop/dequeue", 10, 20, 20, WHITE);
        DrawText(TextFormat("Current Input: %s", inputText), 10, 50, 20, WHITE);

        // Draw Queue
        DrawText("Queue:", 50, 120, 30, GREEN);
        for (int i = 0; i < queue.getCount(); i++) {
            int x = 50 + i * 60;  // Horizontally spaced
            int y = screenHeight / 2 - 20;  // Centered vertically
            DrawRectangle(x, y, 50, 40, GREEN);
            DrawText(TextFormat("%d", queue.getElement(i)), x + 15, y + 10, 22, WHITE);
        }

        // Draw Stack
        DrawText("Stack:", screenWidth - 150, 120, 30, BLUE);
        for (int i = 0; i <= stack.getTop(); i++) {
            int x = screenWidth - 125;  // Fixed horizontally to the right
            int y = screenHeight - (i + 1) * 50;  // Offset each element vertically
            DrawRectangle(x, y, 80, 40, BLUE);
            DrawText(TextFormat("%d", stack.getElement(i)), x + 30, y + 10, 22, WHITE);
        }

        const char* name = "Created by : Taha";  // Replace with your actual name
int textHeight = 20;  // Height of the text
DrawText(name, 10, screenHeight - textHeight - 10, 20, WHITE);  // 10 pixels from the left and bottom


        EndDrawing();
    }

    CloseWindow();
    return 0;
}
