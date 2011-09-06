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

#include "directory_entry.h"

namespace dspawn
{
    directory_entry::directory_entry() {}

    directory_entry::directory_entry(struct dirent *cd) {
        _d_name = std::string(cd->d_name);
        _d_fileno = cd->d_ino;

    }

    directory_entry::~directory_entry() {}

    bool directory_entry::operator==(const directory_entry& other) {
        return (
                (_d_fileno == other._d_fileno) &&
                (_d_name == other._d_name)
               );
    }

    bool directory_entry::operator!=(const directory_entry& other) {
        return !(*this == other);
    }

    std::string directory_entry::name() {
        return _d_name;
    }

    ino_t directory_entry::file_number() {
        return _d_fileno;
    }

} /* namespace dspawn */

