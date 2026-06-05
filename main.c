#include <stdio.h>
#include <stdlib.h>

struct Point { 
    int x; 
    int y; 
};

struct Node {
    int id;
    int type;
    int radius; 
    struct Point p[3]; 
    char label[50];
    struct Node *next;
};

int next_id = 1;

void draw_point(char canvas[40][80], int x, int y) {
    if (x >= 0 && x < 80 && y >= 0 && y < 40) {
        canvas[y][x] = '*';
    }
}

void draw_line(char canvas[40][80], int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int steps = dx;
    
    if (dy > dx) steps = dy;
    if (steps == 0) return;
    
    float x_inc = (float)(x2 - x1) / steps;
    float y_inc = (float)(y2 - y1) / steps;
    float x = x1;
    float y = y1;
    
    for (int i = 0; i <= steps; i++) {
        draw_point(canvas, (int)x, (int)y);
        x += x_inc; 
        y += y_inc;
    }
}

void draw_circle(char canvas[40][80], int cx, int cy, int radius) {
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 80; j++) {
            int dx = j - cx;
            int dy = i - cy;
            int distance = (dx * dx) + (dy * 2) * (dy * 2);
            int r_sq = radius * radius;
            
            if (distance >= r_sq - radius - 1 && distance <= r_sq + radius + 1) {
                draw_point(canvas, j, i);
            }
        }
    }
}

void draw_rectangle(char canvas[40][80], int x1, int y1, int x2, int y2) {
    draw_line(canvas, x1, y1, x2, y1); 
    draw_line(canvas, x2, y1, x2, y2);
    draw_line(canvas, x2, y2, x1, y2); 
    draw_line(canvas, x1, y2, x1, y1);
}

void draw_triangle(char canvas[40][80], int x1, int y1, int x2, int y2, int x3, int y3) {
    draw_line(canvas, x1, y1, x2, y2); 
    draw_line(canvas, x2, y2, x3, y3);
    draw_line(canvas, x3, y3, x1, y1); 
}

void show_canvas(struct Node *head, char canvas[40][80]) {
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 80; j++) canvas[i][j] = '_';
    }
    
    struct Node *curr = head;
    while (curr != NULL) {
        int x1 = curr->p[0].x;
        int y1 = curr->p[0].y;
        int x2 = curr->p[1].x;
        int y2 = curr->p[1].y;
        int x3 = curr->p[2].x;
        int y3 = curr->p[2].y;
        
        switch (curr->type) {
            case 0: 
                draw_line(canvas, x1, y1, x2, y2); 
                break;
            case 1: 
                draw_rectangle(canvas, x1, y1, x2, y2); 
                break;
            case 2: 
                draw_circle(canvas, x1, y1, curr->radius); 
                break;
            case 3:
                draw_triangle(canvas, x1, y1, x2, y2, x3, y3); 
                break;
        }
        curr = curr->next;
    }
    
    printf("\nCanvas:\n");
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 80; j++) printf("%c", canvas[i][j]);
        printf("\n");
    }
}

void get_input(struct Node *n) {
    switch (n->type) {
        case 0:
            printf("Line (x1 y1 x2 y2): "); 
            scanf("%d %d %d %d", &n->p[0].x, &n->p[0].y, &n->p[1].x, &n->p[1].y);
            break;
        case 1:
            printf("Rect (x1 y1 x2 y2): "); 
            scanf("%d %d %d %d", &n->p[0].x, &n->p[0].y, &n->p[1].x, &n->p[1].y);
            break;
        case 2:
            printf("Circle (cx cy radius): "); 
            scanf("%d %d %d", &n->p[0].x, &n->p[0].y, &n->radius);
            break;
        case 3:
            printf("Tri (x1 y1 x2 y2 x3 y3): "); 
            scanf("%d %d %d %d %d %d", &n->p[0].x, &n->p[0].y, &n->p[1].x, &n->p[1].y, &n->p[2].x, &n->p[2].y);
            break;
    }
}

void add_shape(struct Node **head) {
    struct Node *n = (struct Node *)malloc(sizeof(struct Node));
    
    printf("Type (0=Line, 1=Rect, 2=Circ, 3=Tri): "); 
    scanf("%d", &n->type);
    
    n->id = next_id++;
    get_input(n);
    
    printf("Label: "); 
    scanf("%s", n->label);
    
    n->next = *head; 
    *head = n;
}

void edit_shape(struct Node *head) {
    int id; 
    printf("Edit ID: "); 
    scanf("%d", &id);
    
    struct Node *curr = head;
    while (curr != NULL) {
        if (curr->id == id) {
            get_input(curr);
            return;
        }
        curr = curr->next;
    }
}

void delete_shape(struct Node **head) {
    int id; 
    printf("Delete ID: "); 
    scanf("%d", &id);
    
    struct Node *curr = *head;
    struct Node *prev = NULL;
    
    while (curr != NULL) {
        if (curr->id == id) {
            if (prev == NULL) {
                *head = curr->next; 
            } else {
                prev->next = curr->next;
            }
            
            free(curr); 
            return;
        }
        prev = curr; 
        curr = curr->next;
    }
}

void save_file(struct Node *head) {
    FILE *fp = fopen("shapes.txt", "w"); 
    if (fp == NULL) return;
    
    struct Node *curr = head;
    while (curr != NULL) {
        fprintf(fp, "%d %d %d %d %d %d %d %d %d %s\n", 
            curr->id, curr->type, curr->p[0].x, curr->p[0].y, 
            curr->p[1].x, curr->p[1].y, curr->p[2].x, curr->p[2].y, 
            curr->radius, curr->label);
        curr = curr->next;
    }
    fclose(fp);
}

void load_file(struct Node **head) {
    FILE *fp = fopen("shapes.txt", "r"); 
    if (fp == NULL) return;
    
    struct Node *n = (struct Node *)malloc(sizeof(struct Node));
    while (fscanf(fp, "%d %d %d %d %d %d %d %d %d %s", 
           &n->id, &n->type, &n->p[0].x, &n->p[0].y, 
           &n->p[1].x, &n->p[1].y, &n->p[2].x, &n->p[2].y, 
           &n->radius, n->label) == 10) {
           
        n->next = *head; 
        *head = n;
        if (n->id >= next_id) next_id = n->id + 1;
        
        n = (struct Node *)malloc(sizeof(struct Node));
    }
    free(n);
    fclose(fp);
}

int main() {
    struct Node *head = NULL; 
    char canvas[40][80]; 
    int choice;
    
    load_file(&head);
    
    while (1) {
        printf("\n1.Add 2.Edit 3.Delete 4.Show 5.Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) break;
        
        switch (choice) {
            case 1: add_shape(&head); break;
            case 2: edit_shape(head); break;
            case 3: delete_shape(&head); break;
            case 4: show_canvas(head, canvas); break;
            case 5:
                save_file(head);
                return 0;
            default: printf("Invalid choice!\n"); break;
        }
    }
    return 0;
}