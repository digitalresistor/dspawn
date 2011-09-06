/**
 * Copyright (c) 2011 Bert JW Regeer <bertjw@regeer.org>;
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

#ifndef EXCEPT_H_D3367A0CFCE990
#define EXCEPT_H_D3367A0CFCE990

#include <stdexcept>
#include <string>

namespace dspawn
{
    namespace except
    {
        class Errno : public std::runtime_error {
            private:
                int _errno;
                std::string _error_string;

            public:
                Errno(int _errno)
                    : std::runtime_error(""), _errno(_errno) {
                        char *errstr = strerror(_errno);
                        _error_string = std::string(errstr);
                    };
                virtual ~Errno() throw() { }
                virtual const char* what() const throw() {
                    return _error_string.c_str();
                }
        };

    } /* namespace except */

} /* namespace dspawn */


#endif /* EXCEPT_H_D3367A0CFCE990 */

