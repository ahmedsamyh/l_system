#ifndef __L_SYSTEM_H__
#define __L_SYSTEM_H__

// Transforms a character from -> to
typedef struct {
    char from;
    const char* to;
} Rule;

#define BUFF_SIZE (1024*2)
typedef struct {
    char buff[BUFF_SIZE];
    int size; // bytes occupied
} Buffer;

void buffer_append(Buffer* buff, const char* data);
void buffer_append_char(Buffer* buff, char ch);
void swap_buffers(Buffer* a, Buffer* b);

void print_rules(const Rule* rules, size_t rules_count);

// Returns false if not a rule, else true after handling the rule
bool handle_rule(const Rule* rules, size_t rules_count, char ch, Buffer* tmp);

#endif // __L_SYSTEM_H__

////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef L_SYSTEM_IMPLEMENTATION

void buffer_append(Buffer* buff, const char* data) {
    size_t data_len = strlen(data);
    ASSERT(buff->size + data_len <= (BUFF_SIZE-1));
    memcpy(buff->buff + buff->size, data, data_len);
    buff->size += data_len;
}

void buffer_append_char(Buffer* buff, char ch) {
    buff->buff[buff->size++] = ch;
}

void swap_buffers(Buffer* a, Buffer* b) {
    Buffer temp = {0};
    memcpy(temp.buff, a->buff, a->size);
    temp.size = a->size;
    memcpy(a->buff, b->buff, b->size);
    a->size = b->size;
    memcpy(b->buff, temp.buff, temp.size);
    b->size = temp.size;
}

bool handle_rule(const Rule* rules, size_t rules_count, char ch, Buffer* tmp) {
    for (size_t i = 0; i < rules_count; ++i) {
        if (rules[i].from == ch) {
            buffer_append(tmp, rules[i].to);
            return true;
        }
    }
    return false;
}

void print_rules(const Rule* rules, size_t rules_count) {
    for (size_t i = 0; i < rules_count; i++) {
        printf("Rule: '%c' -> '%s'\n", rules[i].from, rules[i].to);
    }
}

#endif // L_SYSTEM_IMPLEMENTATION
