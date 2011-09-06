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
#include <errno.h>

namespace dspawn
{
    directory::directory(std::string dir) {
        opendir(dir);
    }

    directory::directory(const char* dir) {
        opendir(std::string(dir));
    }

    directory::directory() {}

    directory::~directory() {}

    void directory::opendir(std::string dir) {
        char *full_path = new char[PATH_MAX + 1];

        if (::realpath(dir.c_str(), full_path) == 0) {
            throw except::Errno(errno);
        }

        _full_path = std::string(full_path);
        delete[] full_path;

        if (!_verify_is_dir(_full_path)) {
            throw except::not_a_directory();
        }
    }

    bool directory::is_dir(std::string dir) {
        return _verify_is_dir(dir);
    }

    std::string directory::path() {
        return _full_path;
    }

    std::string directory::basename() {
        if (_full_path.length() > 1) {
            std::string _temp;

            _temp.append(_full_path, _full_path.find_last_of("/") + 1, _full_path.length());
            return _temp;
        }
        else {
            return _full_path;
        }
    }

    std::string directory::dirname() {
        if (_full_path.length() > 1) {
            std::string _temp = _full_path;

            _temp.erase(_temp.find_last_of("/"));
            if (_temp.length() == 0) {
                return std::string("/");
            }
            return _temp;
        }
        else {
            return _full_path;
        }
    }

    std::vector<std::string> directory::all_entries() {
        return std::vector<std::string>();
    }

    directory::iterator directory::begin() {
        return iterator(_full_path);
    }

    directory::iterator directory::end() {
        return iterator(0);
    }

    bool directory::_verify_is_dir(std::string dir) {
        // Verify that we are actually dealing with a directory

        struct stat *_st = new struct stat;

        if (::stat(dir.c_str(), _st) != 0) {
            throw except::Errno(errno);
        }

        if (!(_st->st_mode & S_IFDIR)) {
            return false;
        }

        delete _st;

        return true;
    }

    /* Directory iterator below */

    directory_iterator::directory_iterator() {
        // This should never be instantiated. Ever.
        throw;
    }

    directory_iterator::directory_iterator(std::string dir) : _dir_entry(0) {
        _dir = ::opendir(dir.c_str());

        if (_dir == 0) throw except::Errno(errno);

        _read_next();
    }

    directory_iterator::directory_iterator(int end) : _dir(0), _entry(0), _dir_entry(0) {
    }

    directory_iterator::~directory_iterator() {
        if (_dir != 0) {
            if (::closedir(_dir) != 0) throw except::Errno(errno);
        }
    }

    directory_entry& directory_iterator::operator*() {
        return *_dir_entry;
    }

    const directory_iterator& directory_iterator::operator++() {
        _read_next();
        return *this;
    }

    void directory_iterator::_read_next() {
        errno = 0;

        _entry = readdir(_dir);

        if (_dir == 0 && errno != 0) {
            throw except::Errno(errno);
        }

        if (_dir_entry != 0) {
            delete _dir_entry;
        }

        // End of a directory.
        if (_entry == 0) {
            _dir_entry = 0;

            return;
        }

        _dir_entry = new directory_entry(_entry);

        return;
    }

    bool directory_iterator::operator!=(const directory_iterator& other) {
        if (_dir_entry == 0 && other._dir_entry == 0) return false;
        if (other._dir_entry == 0 && _dir_entry != 0) return true;

        return !(*_dir_entry == *(other._dir_entry));
    }

} /* namespace dspawn */

