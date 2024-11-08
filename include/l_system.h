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

void print_rules(Rule* rules, size_t rules_count);

#endif // __L_SYSTEM_H__

////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef L_SYSTEM_IMPLEMENTATION

void buffer_append(Buffer* buff, const char* data) {
    size_t data_len = strlen(data);
    ASSERT(buff->size + data_len <= (BUFF_SIZE-1));
    memcpy(buff->buff + buff->size, data, data_len);
    buff->size += data_len;
}

void print_rules(Rule* rules, size_t rules_count) {
    for (size_t i = 0; i < rules_count; i++) {
        printf("Rule: '%c' -> '%s'\n", rules[i].from, rules[i].to);
    }
}

#endif // L_SYSTEM_IMPLEMENTATION
