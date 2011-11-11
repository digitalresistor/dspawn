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

#include <sys/stat.h>
#include <unistd.h>

#include "gtest/gtest.h"

#include "directory.h"
#include "except.h"

TEST(test_directory, invalid_dir) {
    ASSERT_THROW(dspawn::directory("notadir"), dspawn::except::Errno);
}

TEST(test_directory, invalid_open_dir) {
    dspawn::directory mydir;

    ASSERT_THROW(mydir.opendir("notadir"), dspawn::except::Errno);
}

TEST(test_directory, valid_dir) {
    dspawn::directory mydir;

    ASSERT_NO_THROW(mydir.opendir("/tmp/"));
}

TEST(test_directory, path_name) {
    dspawn::directory mydir;

    ASSERT_NO_THROW(mydir.opendir("/tmp/"));

    ASSERT_EQ(mydir.basename(), std::string("tmp"));
}

TEST(test_directory, check_entries) {
    mkdir("/tmp/dspawn-tests/", 0700);

    dspawn::directory mydir;

    ASSERT_NO_THROW(mydir.opendir("/tmp/dspawn-tests/"));

    std::vector<std::string> entries = mydir.all_entries();

    ASSERT_EQ(entries.size(), static_cast<size_t>(2));

    rmdir("/tmp/dspawn-tests/");
}

