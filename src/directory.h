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

#ifndef DIR_H_249449C78CE8FA
#define DIR_H_249449C78CE8FA

#include <vector>
#include <string>
#include <iterator>

#include <sys/stat.h>
#include <dirent.h>

#include "directory_entry.h"

namespace dspawn
{
    class directory_iterator;
    class directory;

    /**
     * @class directory
     * @brief Takes care of certain operations to do with directories
     *        such as reading them and providing a list of files in them.
     */
    class directory 
    {
        friend class directory_iterator;

        public:

            typedef directory_iterator iterator;

            directory(std::string dir);
            directory(const char* dir);
            directory();
            ~directory();

            bool opendir(std::string dir);

            std::vector<std::string> all_entries();
            

            iterator begin();
            iterator end();

        private:
            /* data */
            bool _verify_is_dir(std::string dir);

            std::string _full_path;
    };

    /**
     * @class directory_iterator
     * @brief An iterator that returns directory_entry's
     */
    class directory_iterator : public std::iterator<std::forward_iterator_tag, directory_entry> 
    {
        friend class directory;

        public:
            ~directory_iterator();

            directory_entry& operator*();
            const directory_iterator& operator++();
            bool operator!=(const directory_iterator other);
    
        private:
            /* data */
            directory_iterator();
            directory_iterator(std::string dir);
            directory_iterator(int end);

            void _read_next();

            DIR* _dir;
            struct dirent *_entry;
            directory_entry *_dir_entry;
    };
    

} /* namespace dspawn */


#endif /* DIR_H_249449C78CE8FA */

