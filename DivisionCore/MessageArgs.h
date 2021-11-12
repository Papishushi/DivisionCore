/**
  * @file MessageArgs.h
  * @author Daniel Molinero Lucas (Papishushi)
  * @section Copyright © <2021+> <Daniel Molinero Lucas (Papishushi)> MIT LICENSE
  * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
  * to deal in the Software without restriction, including without limitation the rights to use, copy,
  * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
  * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
  *
  * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
  *
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
  * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
  **/
#ifndef DIVISIONCORE_MESSAGEARGS_H
#define DIVISIONCORE_MESSAGEARGS_H

#include <string>
#include <cstdarg>
#include <vector>

namespace DivisionCore {
    namespace Core {
        struct MessageArgs {
        private:
            std::string methodName;
            bool selfApply;
            std::vector<void *> params = {};
        public:
            MessageArgs() = delete;

            MessageArgs(const std::string &_methodName, const bool _selfApply, const unsigned numberOfParams,
                        const void *_params = nullptr, ...) {
                va_list list;

                        va_start(list, _params);

                methodName = {_methodName};
                selfApply = _selfApply;

                for (int i = 0; i < numberOfParams; i++) {
                    params.insert(params.end(), va_arg(list, void*));
                }

                        va_end(list);
            }

            inline const std::string &getMethodName() const {
                return methodName;
            }

            inline bool isSelfApply() const {
                return selfApply;
            }

            inline const std::vector<void *> &getParams() const {
                return params;
            }
        };
    }
}
#endif //DIVISIONCORE_MESSAGEARGS_H
