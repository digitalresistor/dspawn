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

#ifndef DIRECTORY_ENTRY_H_54BF50B3883F0A
#define DIRECTORY_ENTRY_H_54BF50B3883F0A

#include <sys/stat.h>
#include <dirent.h>

#include <string>

namespace dspawn
{
    /**
     * @class directory_entry
     * @brief A single entry in a directory
     */
    class directory_entry 
    {
        public:
            directory_entry();
            directory_entry(struct dirent*);
            directory_entry(int i);
            virtual ~directory_entry();

            std::string name();
            ino_t file_number();

            bool operator==(const directory_entry& other);
            bool operator!=(const directory_entry& other);
    
        private:
            ino_t _d_fileno;
            std::string _d_name;
            /* data */
    };
    
    
} /* namespace dspawn */


#endif /* DIRECTORY_ENTRY_H_54BF50B3883F0A */

