#ifndef buffer_h
#define buffer_h

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int counter;

int display_buffer();
int init_buffer();
int insert_buffer(int buffer_content);
int remove_buffer();

#endif