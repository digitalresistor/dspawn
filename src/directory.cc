/**
 * Copyright (c) 2011 Bert JW Regeer;
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

#include "directory.h"

#include <stdlib.h>

namespace dspawn
{
    directory::directory(std::string dir) {
        if (!verify_is_dir(dir)) {
            throw;
        }

        _dir = opendir(dir.c_str());
    }

    directory::directory(const char* dir) {
        if (!verify_is_dir(std::string(dir))) {
            throw;
        }

        _dir = opendir(dir);
    }

    directory::directory() {}

    directory::~directory() {
    }

    std::vector<std::string> directory::all_entries() {
        return std::vector<std::string>();
    }

    directory::iterator directory::begin() {
        return iterator();
    }

    directory::iterator directory::end() {
        return iterator();
    }

    bool directory::verify_is_dir(std::string dir) {
        // Verify that we are actually dealing with a directory

        struct stat *_st = new struct stat;

        if (!stat(dir.c_str(), _st)) {
            return false;
        }

        if (!(_st->st_mode & S_IFDIR)) {
            return false;
        }

        delete _st;

        return true;
    }

    /* Directory iterator below */

    directory_iterator::directory_iterator() {
    }

    directory_iterator::~directory_iterator() {
    }
} /* namespace dspawn */

