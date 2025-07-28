#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define MAX 100

typedef struct Request {
    int id;
    char issue[MAX];
    int priority;
} Request;

typedef struct Queue {
    Request *requests;
    int capacity;
    int front;
    int rear;
} Queue;

Queue *createQueue(int capacity) {
    Queue * queue = (Queue *)malloc(sizeof(Queue));
    queue->requests = (Request *)malloc(sizeof(Request) * capacity);
    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = -1;
    return queue;
}

void enqueue(Queue * queue, Request request) {
    if (queue->rear == queue->capacity - 1) {
        printf("Queue is full\n");
        return;
    }
    queue->rear++;
    queue->requests[queue->rear] = request;
}

Request createRequest() {
    Request request;
    printf("Moi ban nhap ID yeu cau:\n");
    scanf("%d", &request.id);
    getchar();

    printf("Moi ban nhap yeu cau:\n");
    fgets(request.issue, MAX, stdin);
    request.issue[strcspn(request.issue, "\n")] = '\0';

    printf("Moi ban nhap do uu tien:\n");
    scanf("%d", &request.priority);
    getchar();
    return request;
}

int isEmpty(Queue * queue) {
    if (queue->front > queue->rear) {
        return 1;
    }
    return 0;
}

void dequeue(Queue* queue) {
    queue->front++;
    printf("Xu ly thanh cong yeu cau!\n");
}

void peek(Queue * queue) {
    printf("ID: %d\n", queue->requests[queue->front].id);
    printf("Request: %s\n", queue->requests[queue->front].issue);
    printf("Priority: %d\n", queue->requests[queue->front].priority);
}

void printRequests(Queue * queue) {
    for (int i = queue->front; i <= queue->rear; i++) {
        Request request = queue->requests[i];
        printf("ID: %d\n", request.id);
        printf("Request: %s\n", request.issue);
        printf("Priority: %d\n", request.priority);
    }
}

int main() {
    int choice;
    Queue *highQueue = createQueue(MAX);
    Queue *lowQueue = createQueue(MAX);

    do {
        printf("REQUEST SYSTEM\n");
        printf("1. Gui yeu cau ho tro\n");
        printf("2. Xu ly yeu cau\n");
        printf("3. Xem yeu cau gan nhat can xu ly\n");
        printf("4. Hien thi toan bo yeu cau\n");
        printf("5. Thoat\n");
        printf("Lua chon cua ban: \n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                Request request = createRequest();
                if (request.priority == 1) {
                    enqueue(highQueue, request);
                } else {
                    enqueue(lowQueue, request);
                }
                break;
            case 2:
                if (!isEmpty(highQueue)) {
                    dequeue(highQueue);
                } else {
                    if (!isEmpty(lowQueue)) {
                        dequeue(lowQueue);
                    } else {
                        printf("Khong co yeu cau nao nao!\n");
                    }
                }
                break;
            case 3:
                if (!isEmpty(highQueue)) {
                    peek(highQueue);
                } else {
                    if (!isEmpty(lowQueue)) {
                        peek(lowQueue);
                    } else {
                        printf("Khong co yeu cau nao!\n");
                    }
                }
                break;
            case 4:
                if (!isEmpty(highQueue)) {
                    printRequests(highQueue);
                }
                if (!isEmpty(lowQueue)) {
                    printRequests(lowQueue);
                }
                if (isEmpty(highQueue) && isEmpty(lowQueue)) {
                    printf("Khong co yeu cau nao!\n");
                }
                break;
            case 5:
                printf("Thoat chuong trinh!");
                return 0;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (choice != 5);
}