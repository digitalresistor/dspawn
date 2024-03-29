/**
 * Copyright (c) 2011-2012 Bert JW Regeer;
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
**/

#include <iostream>

#include <unistd.h>

#include <ev++.h>

#include "version.h"
#include "directory.h"

void signal_int(ev::sig& signal, int) {
    signal.loop.break_loop();
}

int main(int argc, const char *argv[]) {
    bool background = false;
    unsigned int debug = 0;
    std::string service_dir;


    argv++; argc--; // Skip over the first entry, the program name
    do {
        if (*argv == 0) {
            break;
        }

        // If the first character in the string is not - we exit the loop
        if (*argv[0] != '-') {
            break;
        }

        if (!strcmp(*argv, "--")) {
            argv++; argc--;
            break;
        }

        if (!strncmp(*argv, "-d", 2)) {
            // The debug option was used ... lets count how many times
            const char *curpos = (*argv) + 1;

            while (*curpos == 'd') {
                debug++;
                curpos++;
            }
            continue;
        }

        if (!strcmp(*argv, "-B")) {
            background = true;
            continue;
        }

        if (!strcmp(*argv, "--version")) {
            std::cerr << "dspawn version: " << VERSION << std::endl;
            return 0;
        }

        std::cerr << "Unknown option: " << *argv << std::endl;
    } while (argv++, argc--);

    if (argc == 0) {
        std::cerr << "Missing directory where services are located. Exiting." << std::endl;
        return 1;
    }
    else {
        service_dir = std::string(*argv);
    }

    // Set our directory to the root
    if (dspawn::directory::is_dir(service_dir)) {
        ::chdir(service_dir.c_str());
    } else {
        std::cerr << "Service directory does not exist. Exiting." << std::endl;
        return 1;
    }
    // Modify our umask
    umask(0);

    // If we are backgrounding, do it before we set up the services...
    if (background) {
        // Fork and quit if we are the parent
        if (fork() != 0) _exit(0);

        // Become a session leader
        setsid();

        // if (fork() != 0) _exit(0); // Not required to double fork, need to find a good reason as to why we would want to
    }

    ev::default_loop loop;

    ev::sig sig_int;
    sig_int.set<signal_int>();
    sig_int.start(SIGINT);

    loop.run(0);

    return 0;
}
