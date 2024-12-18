#include <stdio.h>
#include <string.h>

#define COMMONLIB_IMPLEMENTATION
#include <commonlib.h>

#define L_SYSTEM_IMPLEMENTATION
#include <l_system.h>

#define WIDTH 1280
#define HEIGHT 720

static Buffer buffer;
static Buffer temp;

static Rule rules[] = {
    (Rule) { '1', "11" },
    (Rule) { '0', "1[0]0" }
};
static const char* axiom = "0";

int main(void) {
    buffer_append(&buffer, axiom);

    print_rules(rules, ARRAY_LEN(rules));
    log_info("Axiom: '%s'", axiom);

    int N = 3;
    log_info("%d ITERATIONS", N);

    printf("--------------------------------------------------\n");
    log_info("0: '%s'", buffer.buff);
    for (int n = 1; n < N+1; ++n) {
        temp.size = 0;
        for (int i = 0; i < buffer.size; ++i) {
            char ch = buffer.buff[i];
            if (!handle_rule(rules, ARRAY_LEN(rules), ch, &temp)) {
                buffer_append_char(&temp, ch);
            }
        }
        swap_buffers(&buffer, &temp);
        log_info("%d: '%s'", n, buffer.buff);
    }
    return 0;
}
