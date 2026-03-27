#include <stdlib.h>

#include "app.h"

int main(int argc, char *argv[]) {
    App app = {
        .window = NULL,
        .renderer = NULL,
        .texture = NULL
    };

    if (app_init(&app) != 0) {
        app_shutdown(&app);
        return EXIT_FAILURE;
    }

    app_run(&app);

    app_shutdown(&app);

    return EXIT_SUCCESS;
}