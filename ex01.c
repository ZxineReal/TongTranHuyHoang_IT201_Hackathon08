#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <string.h>
#define MAX 100

typedef struct Student {
    int id;
    char name[50];
    bool status;
    int avg;
} Student;

typedef struct Node {
    Student data;
    struct Node* next;
    struct Node* prev;
} Node;

Student students[MAX];
int size = 0;
int isSort = 0;

int isDuplicate(int id) {
    for (int i = 0; i < size; i++) {
        if (students[i].id == id) {
            return 1;
        }
    }
    return 0;
}

void addStudent(int id, char* name, bool status, int avg) {
    students[size].id = id;
    strcpy(students[size].name, name);
    students[size].status = status;
    students[size].avg = avg;
    size++;
}

void printStudents() {
    if (size == 0) {
        printf("Danh sach sinh vien rong!\n");
        return;
    }
    for (int i = 0; i < size; i++) {
        printf("Student ID: %d\n", students[i].id);
        printf("Student Name: %s\n", students[i].name);
        printf("Student Status: %s\n", students[i].status == true ? "Dang hoat dong" : "Khong hoat dong");
        printf("Student Avg: %d\n", students[i].avg);
        printf("\n");
    }
    printf("\n");
}

void deleteStudent(int id) {
    int flag = 0;
    for (int i = 0; i < size; i++) {
        if (students[i].id == id) {
            for (int j = 0; j < size; j++) {
                students[j] = students[j + 1];
            }
            size--;
            flag = 1;
            printf("Xoa sinh vien thanh cong!\n");
        }
    }
    if (!flag) {
        printf("Khong tim thay sinh vien!\n");
        return;
    }
}

void updateStudent(int id) {
    int flag = 0;
    for (int i = 0; i < size; i++) {
        if (students[i].id == id) {
            getchar();
            printf("Moi ban nhap ten sinh vien moi:\n");
            fgets(students[i].name, sizeof(students[i].name), stdin);
            students[i].name[strcspn(students[i].name, "\n")] = '\0';

            printf("Moi ban nhap diem trung binh sinh vien:\n");
            scanf("%d", &students[i].avg);
            getchar();
            flag = 1;
        }
    }
    if (!flag) {
        printf("Khong tim thay sinh vien!\n");
        return;
    }
}

void updateStatusStudent(int id) {
    int flag = 0;
    for (int i = 0; i < size; i++) {
        if (students[i].id == id) {
            if (students[i].status == true) {
                students[i].status = false;
                printf("Thay doi trang thai sinh vien thanh khong hoat dong!\n");
                flag = 1;
            } else if (students[i].status == false) {
                students[i].status = true;
                printf("Thay doi trang thai sinh vien thanh dang hoat dong!\n");
                flag = 1;
            }
        }
    }
    if (!flag) {
        printf("Khth tim thay sinh vien!\n");
        return;
    }
}

void merge(Student arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Student* L = (Student*)malloc(n1 * sizeof(Student));
    Student* R = (Student*)malloc(n2 * sizeof(Student));

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];

    }
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].avg <= R[j].avg) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}


void mergeSortStudents(Student arr[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSortStudents(arr, left, mid);
        mergeSortStudents(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void mergeSort() {
    if (size <= 1) {
        printf("Danh sach sinh vien rong!\n");
        return;
    }

    mergeSortStudents(students, 0, size - 1);
    isSort = 1;
    printf("Sap xep sinh vien thanh cong!\n");
}

void findStudent(int id) {
    int flag = 0;
    if (isSort) {
        int low = 0;
        int high = size - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (students[mid].id == id) {
                printf("Da tim thay sinh vien bang binary search!\n");
                printf("ID: %d\n", students[mid].id);
                printf("Name: %s\n", students[mid].name);
                printf("Status: %s\n", students[mid].status == true ? "Dang hoat dong" : "Khong hoat dong");
                printf("Avg: %d\n", students[mid].avg);
                flag = 1;
                return;
            } else if (students[mid].id > id) {
                high = mid - 1;
            } else if (students[mid].id < id) {
                low = mid + 1;
            }
        }
    } else {
        for (int i = 0; i < size; i++) {
            if (students[i].id == id) {
                printf("Da tim thay sinh vien bang linear search!\n");
                printf("ID: %d\n", students[i].id);
                printf("Name: %s\n", students[i].name);
                printf("Status: %s\n", students[i].status == true ? "Dang hoat dong" : "Khong hoat dong");
                printf("Avg: %d\n", students[i].avg);
                flag = 1;
            }
        }
    }
    if (!flag) {
        printf("Khong tim thay sinh vien!\n");
        return;
    }
}

int main() {
    int choice;

    do {
        printf("STUDENT MANAGER\n");
        printf("1. Them sinh vien\n");
        printf("2. Hien thi danh sach sinh vien\n");
        printf("3. Xoa sinh vien\n");
        printf("4. Cap nhat thong tin sinh vien\n");
        printf("5. Thay doi trang thai sinh vien\n");
        printf("6. Sap xep sinh vien\n");
        printf("7. Tim kiem sinh vien\n");
        printf("8. Thoat chuong trinh\n");
        printf("Lua chon cua ban:\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                int id;
                char name[50];
                bool status;
                int avg;

                printf("Moi ban nhap vao ID sinh vien:\n");
                scanf("%d", &id);
                getchar();
                if (isDuplicate(id)) {
                    printf("ID da ton tai!\n");
                    break;
                }

                printf("Moi ban nhap vao ten sinh vien:\n");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';

                printf("Moi ban nhap vao diem trung binh:\n");
                scanf("%d", &avg);

                addStudent(id, name, true, avg);
                printf("Them sinh vien thanh cong!\n");
                break;
            case 2:
                printStudents();
                break;
            case 3:
                int deleteID;
                printf("Moi ban nhap ID sinh vien can xoa:\n");
                scanf("%d", &deleteID);
                deleteStudent(deleteID);
                break;
            case 4:
                int updateID;
                printf("Moi ban nhap id sinh vien can cap nhat:\n");
                scanf("%d", &updateID);
                updateStudent(updateID);
                break;
            case 5:
                int updateStatusID;
                printf("Moi ban nhap ID sinh vien can thay doi trang thai:\n");
                scanf("%d", &updateStatusID);
                updateStatusStudent(updateStatusID);
                break;
            case 6:
                mergeSort();
                break;
            case 7:
                int findID;
                printf("Moi ban nhap vao ID sinh vien can tim kiem:\n");;
                scanf("%d", &findID);
                findStudent(findID);
                break;
            case 8:
                return 0;
            default:
                printf("Lua chon khong hop le!\n");
        }

    } while (choice != 8);
}